#include <ESP32Servo.h>
#include <Keypad.h>

const byte POSICION_90_GRADOS = 90;  // Posición en grados para el servo
const byte FILAS = 4;  // Número de filas en el teclado
const byte COLUMNAS = 4;  // Número de columnas en el teclado
char teclas[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};  // Definición de las teclas del teclado
byte pinesFilas[FILAS] = {23, 22, 21, 19};  // Pines utilizados para las filas del teclado
byte pinesColumnas[COLUMNAS] = {18, 17, 16, 15};  // Pines utilizados para las columnas del teclado
Keypad keypad = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);  // Crear un objeto Keypad con la configuración definida

const byte LED_VERDE = 10;  // Pin utilizado para el LED verde
Servo servoMotor;  // Objeto para controlar el servo
unsigned long tiempoInicio = 0;  // Tiempo de inicio para el control de la secuencia
bool leyendoTeclas = false;  // Bandera para indicar si se están leyendo las teclas
bool pulsada1 = false;  // Bandera para indicar si se ha pulsado la tecla 1
bool pulsada2 = false;  // Bandera para indicar si se ha pulsado la tecla 2
bool pulsada7 = false;  // Bandera para indicar si se ha pulsado la tecla 7
bool pulsada6 = false;  // Bandera para indicar si se ha pulsado la tecla 6
bool pulsada8 = false;  // Bandera para indicar si se ha pulsado la tecla 8

const unsigned long RESET_TIMEOUT = 20000;  // Tiempo límite para restablecer la secuencia en milisegundos
unsigned long sequenceStartMillis = 0;  // Variable para almacenar el tiempo de inicio de la secuencia

void setup() {
  pinMode(LED_VERDE, OUTPUT);  // Configurar el pin del LED verde como salida
  servoMotor.attach(2);  // Conectar el servo al pin 2 (ajustar según la configuración del hardware)
  servoMotor.write(0);  // Inicializar el servo en la posición 0 grados
}

void loop() {
  char tecla = keypad.getKey();  // Obtener la tecla pulsada del teclado
  if (tecla != NO_KEY) {
    if (!leyendoTeclas) {
      tiempoInicio = millis();  // Almacenar el tiempo de inicio si no se estaban leyendo las teclas
      leyendoTeclas = true;  // Establecer la bandera de lectura de teclas a verdadero
    }
    if (tecla != '#' && tecla != '2' && tecla != '7' && tecla != '6' && tecla != '8') {
      pulsada1 = false;  // Reiniciar las banderas si se pulsa una tecla inválida
      pulsada2 = false;
      pulsada7 = false;
      pulsada6 = false;
      pulsada8 = false;
      leyendoTeclas = false;  // Dejar de leer las teclas
    } else {
      switch (tecla) {
        case '#':
          pulsada1 = true;  // Marcar la tecla 1 como pulsada
          break;
        case '2':
          if (pulsada1 && millis() - tiempoInicio < 5000) {
            pulsada2 = true;  // Marcar la tecla 2 como pulsada si se pulsa después de la tecla 1 en menos de 5 segundos
          } else {
            resetSequence();  // Restablecer la secuencia si no se cumplen las condiciones
          }
          break;
        case '7':
          if (pulsada2 && millis() - tiempoInicio < 5000) {
            pulsada7 = true;  // Marcar la tecla 7 como pulsada si se pulsa después de la tecla 2 en menos de 5 segundos
          } else {
            resetSequence();  // Restablecer la secuencia si no se cumplen las condiciones
          }
          break;
        case '6':
          if (pulsada7 && millis() - tiempoInicio < 5000) {
            pulsada6 = true;  // Marcar la tecla 6 como pulsada si se pulsa después de la tecla 7 en menos de 5 segundos
          } else {
            resetSequence();  // Restablecer la secuencia si no se cumplen las condiciones
          }
          break;
        case '8':
          if (pulsada6 && millis() - tiempoInicio < 5000) {
            pulsada8 = true;  // Marcar la tecla 8 como pulsada si se pulsa después de la tecla 6 en menos de 5 segundos
          } else {
            resetSequence();  // Restablecer la secuencia si no se cumplen las condiciones
          }
          break;
        default:
          resetSequence();  // Restablecer la secuencia si se pulsa una tecla inválida
      }
    }
  }

  if (pulsada1 && pulsada2 && pulsada7 && pulsada6 && pulsada8) {
    digitalWrite(LED_VERDE, HIGH);  // Encender el LED verde
    servoMotor.write(POSICION_90_GRADOS);  // Mover el servo a la posición 90 grados
    
    if (!leyendoTeclas) {
      // Iniciar el temporizador de restablecimiento de la secuencia
      if (sequenceStartMillis == 0) {
        sequenceStartMillis = millis();
      }
      
      // Verificar si ha pasado el tiempo límite para restablecer la secuencia
      if (millis() - sequenceStartMillis >= RESET_TIMEOUT) {
        resetSequence();  // Restablecer la secuencia
      }
    }
    
  } else {
    digitalWrite(LED_VERDE, LOW);  // Apagar el LED verde
    servoMotor.write(0);  // Volver el servo a la posición inicial
    sequenceStartMillis = 0;  // Reiniciar el tiempo de inicio de la secuencia
  }
}

void resetSequence() {
  pulsada1 = false;  // Reiniciar todas las banderas y la secuencia
  pulsada2 = false;
  pulsada7 = false;
  pulsada6 = false;
  pulsada8 = false;
  leyendoTeclas = false;
  sequenceStartMillis = 0;
}
