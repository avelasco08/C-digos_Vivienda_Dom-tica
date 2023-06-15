const int led = 9;  // Declara una constante llamada 'led' y le asigna el valor 9 para indicar el pin del LED.
const int pir = 6;  // Declara una constante llamada 'pir' y le asigna el valor 6 para indicar el pin del sensor PIR.

void setup()
{
  pinMode(led, OUTPUT);  // Configura el pin del LED como salida.
  pinMode(pir, INPUT);   // Configura el pin del sensor PIR como entrada.
}

void loop()
{
  int valuepir = digitalRead(pir);  // Lee el valor del sensor PIR y lo guarda en la variable 'valuepir'.

  if (valuepir == HIGH) {  // Si el valor leído del sensor PIR es alto (detecta movimiento):
    digitalWrite(led, HIGH);  // Enciende el LED.
    delay(10000);  // Espera durante 10 segundos.

  } else {  // Si el valor leído del sensor PIR es bajo (no detecta movimiento):
    digitalWrite(led, LOW);  // Apaga el LED.
  }

  delay(500);  // Espera durante 500 milisegundos antes de repetir el bucle.
}
