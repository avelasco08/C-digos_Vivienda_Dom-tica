#include <ESP32Servo.h>
#include <Keypad.h>

const byte POSICION_90_GRADOS = 90;
const byte FILAS = 4;
const byte COLUMNAS = 4;
char teclas[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte pinesFilas[FILAS] = {23, 22, 21, 19};
byte pinesColumnas[COLUMNAS] = {18, 17, 16, 15};
Keypad keypad = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

const byte LED_VERDE = 10;
Servo servoMotor;
unsigned long tiempoInicio = 0;
bool leyendoTeclas = false;
bool pulsada1 = false;
bool pulsada2 = false;
bool pulsada7 = false;
bool pulsada6 = false;
bool pulsada8 = false;

const unsigned long RESET_TIMEOUT = 20000; // Tiempo límite para restablecer la secuencia en milisegundos
unsigned long sequenceStartMillis = 0; // Variable para almacenar el tiempo de inicio de la secuencia

void setup() {
  pinMode(LED_VERDE, OUTPUT);
  servoMotor.attach(2); // En el pin 34 no funcionaba tener cuidado en cual funciona y cual no
  servoMotor.write(0);
}

void loop() {
  char tecla = keypad.getKey();
  if (tecla != NO_KEY) {
    if (!leyendoTeclas) {
      tiempoInicio = millis();
      leyendoTeclas = true;
    }
    if (tecla != '#' && tecla != '2' && tecla != '7' && tecla != '6' && tecla != '8') {
      pulsada1 = false;
      pulsada2 = false;
      pulsada7 = false;
      pulsada6 = false;
      pulsada8 = false;
      leyendoTeclas = false;
    } else {
      switch (tecla) {
        case '#':
          pulsada1 = true;
          break;
        case '2':
          if (pulsada1 && millis() - tiempoInicio < 5000) {
            pulsada2 = true;
          } else {
            resetSequence();
          }
          break;
        case '7':
          if (pulsada2 && millis() - tiempoInicio < 5000) {
            pulsada7 = true;
          } else {
            resetSequence();
          }
          break;
        case '6':
          if (pulsada7 && millis() - tiempoInicio < 5000) {
            pulsada6 = true;
          } else {
            resetSequence();
          }
          break;
        case '8':
          if (pulsada6 && millis() - tiempoInicio < 5000) {
            pulsada8 = true;
          } else {
            resetSequence();
          }
          break;
        default:
          resetSequence();
      }
    }
  }

  if (pulsada1 && pulsada2 && pulsada7 && pulsada6 && pulsada8) {
    digitalWrite(LED_VERDE, HIGH);
    servoMotor.write(POSICION_90_GRADOS);
    
    if (!leyendoTeclas) {
      // Iniciamos el temporizador de restablecimiento de la secuencia
      if (sequenceStartMillis == 0) {
        sequenceStartMillis = millis();
      }
      
      // Verificamos si ha pasado el tiempo límite para restablecer la secuencia
      if (millis() - sequenceStartMillis >= RESET_TIMEOUT) {
        resetSequence();
      }
    }
    
  } else {
    digitalWrite(LED_VERDE, LOW);
    servoMotor.write(0);
    sequenceStartMillis = 0;
  }
}

void resetSequence() {
  pulsada1 = false;
  pulsada2 = false;
  pulsada7 = false;
  pulsada6 = false;
  pulsada8 = false;
  leyendoTeclas = false;
  sequenceStartMillis = 0;
}