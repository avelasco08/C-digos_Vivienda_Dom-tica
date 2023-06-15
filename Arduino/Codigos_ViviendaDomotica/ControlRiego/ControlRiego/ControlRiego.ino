const int sensorpin = A0;    // Pin analógico para leer la humedad
const int ledverde = 10;    // Pin para el LED verde
const int ledrojo = 11;     // Pin para el LED rojo
const int motor = A1;       // Pin analógico para el control del motor
int humedad;                // Variable para almacenar el valor de humedad

void setup() {
  pinMode(motor, OUTPUT);     // Configurar el pin del motor como salida
  pinMode(sensorpin, INPUT);  // Configurar el pin del sensor de humedad como entrada
  pinMode(ledverde, OUTPUT);  // Configurar el pin del LED verde como salida
  pinMode(ledrojo, OUTPUT);   // Configurar el pin del LED rojo como salida
}

void loop() {
  humedad = analogRead(sensorpin);  // Leer el valor de humedad del sensor analógico

  if (humedad < 500) {
    digitalWrite(ledrojo, HIGH);   // Encender el LED rojo
    digitalWrite(ledverde, LOW);   // Apagar el LED verde
  } else {
    digitalWrite(ledrojo, LOW);    // Apagar el LED rojo
    digitalWrite(ledverde, HIGH);  // Encender el LED verde
  }
}

