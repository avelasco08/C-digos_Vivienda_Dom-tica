#include <Keypad.h>

const byte NUM_FILAS = 4;  // Número de filas de la matriz de teclas
const byte NUM_COLUMNAS = 4;  // Número de columnas de la matriz de teclas

char teclas[NUM_FILAS][NUM_COLUMNAS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte filasPines[NUM_FILAS] = {23, 22, 21, 19};  // Pines conectados a las filas
byte columnasPines[NUM_COLUMNAS] = {18, 17, 16, 15};  // Pines conectados a las columnas

Keypad keypad = Keypad(makeKeymap(teclas), filasPines, columnasPines, NUM_FILAS, NUM_COLUMNAS);

const byte PIR_PIN = 12;  // Pin del sensor PIR
const byte LED_PIN = 13;  // Pin del LED de la alarma
const byte BUZZER_PIN = 14;  // Pin del zumbador (ajustar según la conexión)

const unsigned long TIMEOUT = 15000;  // Tiempo límite en milisegundos
const unsigned long INPUT_TIMEOUT = 5000;  // Tiempo límite para introducir cada tecla en milisegundos

bool validSequence = false;  // Indica si se ha ingresado una secuencia válida
bool sequenceEntered = false;  // Variable para controlar si se ha introducido correctamente la secuencia
byte currentSequenceIndex = 0;  // Índice de la posición actual en la secuencia ingresada
unsigned long lastInputMillis = 0;  // Tiempo del último input ingresado
unsigned long startMillis = 0;  // Tiempo de inicio de la detección de movimiento del PIR
bool pirTriggered = false;  // Indica si el PIR ha detectado movimiento

void setup() {
  pinMode(PIR_PIN, INPUT);  // Configurar el pin del PIR como entrada
  pinMode(LED_PIN, OUTPUT);  // Configurar el pin del LED de la alarma como salida
  pinMode(BUZZER_PIN, OUTPUT);  // Configurar el pin del zumbador como salida
  Serial.begin(115200);
}

void loop() {
  if (digitalRead(PIR_PIN) == HIGH) {
    Serial.println("Se a detectado movimiento");

  } else {
     Serial.println("No se a detectado movimiento");
  }
  if (!pirTriggered) {
    while (digitalRead(PIR_PIN) == LOW) {
      delay(100);  // Esperar hasta que se detecte movimiento en el PIR
    }
    pirTriggered = true;
    startMillis = millis();  // Registrar el tiempo de inicio de la detección de movimiento
  }
 
  char key = keypad.getKey();  // Leer la tecla presionada en el teclado
  if (key) {
    if (key == '2') {
      if (currentSequenceIndex == 0 || (currentSequenceIndex == 3 && millis() - lastInputMillis <= INPUT_TIMEOUT)) {
        currentSequenceIndex = 1;  // Avanzar en la secuencia si se presiona '2' en los momentos adecuados
        lastInputMillis = millis();  // Actualizar el tiempo del último input ingresado
      } else {
        resetSequence(true);  // Reiniciar la secuencia si se presiona '2' en un momento incorrecto
      }
    } else if (key == '7') {
      if (currentSequenceIndex == 1 && millis() - lastInputMillis <= INPUT_TIMEOUT) {
        currentSequenceIndex = 2;  // Avanzar en la secuencia si se presiona '7' en los momentos adecuados
        lastInputMillis = millis();  // Actualizar el tiempo del último input ingresado
      } else {
        resetSequence(true);  // Reiniciar la secuencia si se presiona '7' en un momento incorrecto
      }
    } else if (key == '6') {
      if (currentSequenceIndex == 2 && millis() - lastInputMillis <= INPUT_TIMEOUT) {
        currentSequenceIndex = 3;  // Avanzar en la secuencia si se presiona '6' en los momentos adecuados
        lastInputMillis = millis();  // Actualizar el tiempo del último input ingresado
      } else {
        resetSequence(true);  // Reiniciar la secuencia si se presiona '6' en un momento incorrecto
      }
    } else if (key == '8') {
      if (currentSequenceIndex == 3 && millis() - lastInputMillis <= INPUT_TIMEOUT) {
        validSequence = true;  // Marcar la secuencia como válida si se presiona '8' en los momentos adecuados
        lastInputMillis = millis();  // Actualizar el tiempo del último input ingresado
      } else {
        resetSequence(true);  // Reiniciar la secuencia si se presiona '8' en un momento incorrecto
      }
    } else {
      resetSequence(true);  // Reiniciar la secuencia si se presiona una tecla diferente
    }
  }

  if (validSequence) {
    digitalWrite(LED_PIN, HIGH);  // Encender el LED de la alarma
    sequenceEntered = true;  // Se ha introducido correctamente la secuencia
    delay(30000);
    resetSequence(false);
    
  } else {
    digitalWrite(LED_PIN, LOW);  // Apagar el LED de la alarma
    if (!sequenceEntered && millis() - startMillis >= TIMEOUT && pirTriggered) {
      // Tiempo límite excedido y la secuencia no se ha introducido correctamente, activamos el zumbador
      digitalWrite(BUZZER_PIN, HIGH);
      delay(500);
      digitalWrite(BUZZER_PIN, LOW);
      delay(500);
      digitalWrite(BUZZER_PIN, HIGH);
      delay(500);
      digitalWrite(BUZZER_PIN, LOW);
      delay(500);
      digitalWrite(BUZZER_PIN, HIGH);
      delay(500);
      digitalWrite(BUZZER_PIN, LOW);
      delay(500);
      digitalWrite(BUZZER_PIN, HIGH);
      delay(500);
      digitalWrite(BUZZER_PIN, LOW);
      delay(1000);
      resetSequence(false);
     
    }
   
  }
}
void resetSequence(bool action1) {
  if (action1) {
  currentSequenceIndex = 0;  // Reiniciar el índice de la secuencia
  validSequence = false;  // Marcar la secuencia como no válida
  sequenceEntered = false;  // Marcar la secuencia como no introducida correctamente
  } else {
    pirTriggered = false;  // Marcar el PIR como no detectado
    digitalWrite(PIR_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
}


