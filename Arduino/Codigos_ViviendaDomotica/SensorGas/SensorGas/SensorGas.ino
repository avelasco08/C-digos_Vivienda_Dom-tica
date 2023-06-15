int gasPin = 2;       // Pin para leer el sensor de gas
int buzzerPin = 7;   // Pin para el zumbador

int limiteGas = 500;  // Valor límite para la detección de gas

void soundBuzzer(unsigned long frequency) {
  tone(buzzerPin, frequency);  // Activar el zumbador con la frecuencia especificada
  delay(1000);                // Esperar 1 segundo
  noTone(buzzerPin);          // Desactivar el zumbador
}

void setup() {
  pinMode(buzzerPin, OUTPUT);  // Configurar el pin del zumbador como salida
  pinMode(gasPin, INPUT);      // Configurar el pin del sensor de gas como entrada
}

void loop() {
  int gas = analogRead(gasPin);  // Leer el valor analógico del sensor de gas

  if (gas > limiteGas) {  // Si el valor de gas es mayor al límite establecido
    digitalWrite(buzzerPin, HIGH);  // Encender el zumbador
    delay(1000);                     // Esperar 1 segundo
    digitalWrite(buzzerPin, LOW);   // Apagar el zumbador
    delay(1000);                    // Esperar 1 segundo
  } else {
    digitalWrite(buzzerPin, LOW);  // Apagar el zumbador
  }
}

