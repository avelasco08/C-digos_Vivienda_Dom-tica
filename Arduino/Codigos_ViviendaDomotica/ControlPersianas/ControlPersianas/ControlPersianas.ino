#include <Servo.h>  // Incluir la biblioteca para controlar el servo
#include <Time.h>   // Incluir la biblioteca para obtener la hora

Servo servoMotor;  // Crear un objeto de tipo Servo para controlar el servo
const int sensorluz = A0;  // Pin para leer el sensor de luz
const int posicion_0_grados = 0;  // Posición en grados del servo (0 grados)
const int posicion_180_grados = 180;  // Posición en grados del servo (180 grados)
int luzvalor;  // Variable para almacenar el valor de la lectura del sensor de luz
int mananahora = 7;  // Hora de la mañana
int tardehora = 15;  // Hora de la tarde
int tardehora2 = 17;  // Segunda hora de la tarde
int nochehora = 21;  // Hora de la noche
int hour();  // Declaración de la función para obtener la hora actual

void setup() {
  servoMotor.attach(11);  // Asociar el servo al pin 11
  servoMotor.write(posicion_0_grados);  // Posicionar el servo en 0 grados
}

void loop() {
  luzvalor = analogRead(sensorluz);  // Leer el valor analógico del sensor de luz
  int horaActual = hour();  // Obtener la hora actual

  // Control del servo en función de la hora del día
  if (horaActual >= mananahora || horaActual < tardehora) {
    servoMotor.write(posicion_180_grados);  // Mover el servo a 180 grados
  }
  if (horaActual >= tardehora || horaActual < tardehora2) {
    servoMotor.write(posicion_0_grados);  // Mover el servo a 0 grados
  }
  if (horaActual >= tardehora2 || horaActual < nochehora) {
    servoMotor.write(posicion_180_grados);  // Mover el servo a 180 grados
  }
  if (horaActual >= nochehora || horaActual < mananahora) {
    servoMotor.write(posicion_0_grados);  // Mover el servo a 0 grados
  }
}
