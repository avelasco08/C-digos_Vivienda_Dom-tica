#include <Keypad.h>

const byte NUM_FILAS = 4;
const byte NUM_COLUMNAS = 4;

char teclas[NUM_FILAS][NUM_COLUMNAS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte filasPines[NUM_FILAS] = {23, 22, 21, 19};
byte columnasPines[NUM_COLUMNAS] = {18, 17, 16, 15};

Keypad keypad = Keypad(makeKeymap(teclas), filasPines, columnasPines, NUM_FILAS, NUM_COLUMNAS);

const byte PIR_PIN = 12;
const byte LED_PIN = 13;
const byte BUZZER_PIN = 4; // Cambia el número de pin según la conexión del zumbador

const unsigned long TIMEOUT = 15000; // tiempo límite en milisegundos
const unsigned long INPUT_TIMEOUT = 5000; // tiempo límite para introducir cada tecla en milisegundos

bool validSequence = false;
bool sequenceEntered = false; // Variable para controlar si se ha introducido correctamente la secuencia
byte currentSequenceIndex = 0;
unsigned long lastInputMillis = 0;
unsigned long startMillis = 0;
bool pirTriggered = false;


void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  if (!pirTriggered) {
    while (digitalRead(PIR_PIN) == LOW) {
      delay(100);
    }
    pirTriggered = true;
    startMillis = millis();
  }
 
  char key = keypad.getKey();
  if (key) {
    if (key == '2') {
      if (currentSequenceIndex == 0 || (currentSequenceIndex == 3 && millis() - lastInputMillis <= INPUT_TIMEOUT)) {
        currentSequenceIndex = 1;       // Avanzamos en la secuencia si se presiona '2' en los momentos adecuados
        lastInputMillis = millis();     // Actualizamos el tiempo del último input ingresado
      } else {
        resetSequence();                // Reiniciamos la secuencia si se presiona '2' en un momento incorrecto
      }
    } else if (key == '7') {
      if (currentSequenceIndex == 1 && millis() - lastInputMillis <= INPUT_TIMEOUT) {
        currentSequenceIndex = 2;       // Avanzamos en la secuencia si se presiona '4' en los momentos adecuados
        lastInputMillis = millis();     // Actualizamos el tiempo del último input ingresado
      } else {
        resetSequence();                // Reiniciamos la secuencia si se presiona '4' en un momento incorrecto
      }
    } else if (key == '6') {
      if (currentSequenceIndex == 2 && millis() - lastInputMillis <= INPUT_TIMEOUT) {
        currentSequenceIndex = 3;       // Avanzamos en la secuencia si se presiona '6' en los momentos adecuados
        lastInputMillis = millis();     // Actualizamos el tiempo del último input ingresado
      } else {
        resetSequence();                // Reiniciamos la secuencia si se presiona '6' en un momento incorrecto
      }
    } else if (key == '8') {
      if (currentSequenceIndex == 3 && millis() - lastInputMillis <= INPUT_TIMEOUT) {
        validSequence = true;           // Marcamos la secuencia como válida si se presiona '8' en los momentos adecuados
        lastInputMillis = millis();     // Actualizamos el tiempo del último input ingresado
      } else {
        resetSequence();                // Reiniciamos la secuencia si se presiona '8' en un momento incorrecto
      }
    } else {
      resetSequence();                  // Reiniciamos la secuencia si se presiona una tecla diferente
    }
  }

  if (validSequence) {
    digitalWrite(LED_PIN, HIGH); // Encendemos el LED de la alarma
    sequenceEntered = true; // Se ha introducido correctamente la secuencia
    // Aquí puedes agregar el código adicional que deseas ejecutar cuando se cumple la secuencia válida.
    // Por ejemplo, enviar un mensaje a la web
  } else {
    digitalWrite(LED_PIN, LOW);  // Apagamos el LED de la alarma
    if (!sequenceEntered && millis() - startMillis >= TIMEOUT && pirTriggered) {
      // Tiempo límite excedido y la secuencia no se ha introducido correctamente, activamos el zumbador
      digitalWrite(BUZZER_PIN, HIGH);
       delay(500);
       digitalWrite(BUZZER_PIN, LOW);
         delay(1000);
         digitalWrite(BUZZER_PIN, HIGH);
       delay(500);
       digitalWrite(BUZZER_PIN, LOW);
         delay(1000);
      // Puedes agregar más tonos o ajustar la duración según tus necesidades
    }
    // Aquí puedes agregar el código adicional que deseas ejecutar cuando NO se cumple la secuencia válida.
    // Por ejemplo, enviar un mensaje a la web
  }
}

void resetSequence() {
  currentSequenceIndex = 0;
  validSequence = false;
  sequenceEntered = false;
  lastInputMillis = 0;
  pirTriggered = false;
}
