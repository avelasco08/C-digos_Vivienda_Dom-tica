#define trigPin 9   // Definir el pin de trigger como 9
#define echoPin 10  // Definir el pin de echo como 10

int distance;  // Variable para almacenar la distancia medida

void setup() {
  Serial.begin(115200);  // Iniciar la comunicación serie a una velocidad de 115200 baudios
  pinMode(trigPin, OUTPUT);  // Configurar el pin de trigger como salida
  pinMode(echoPin, INPUT);   // Configurar el pin de echo como entrada
}

void loop() {
  digitalWrite(trigPin, LOW);  // Asegurarse de que el pin de trigger está en bajo
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  // Enviar un pulso de 10 microsegundos al pin de trigger
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  distance = pulseIn(echoPin, HIGH);  // Medir la duración del eco y calcular la distancia
  distance = distance / 58;  // Convertir la duración a centímetros
  Serial.print("Distancia: ");
  Serial.print(distance);
  if (distance >= 0 && distance <= 135) {  // Si la distancia está entre 92 y 120 cm, hay tres productos
    Serial.println(" - Hay tres productos");
  } else if (distance >= 136 && distance <= 235) {  // Si la distancia está entre 155 y 165 cm, hay dos productos
    Serial.println(" - Hay dos productos");
  } else if (distance >= 236 && distance <= 280) {  // Si la distancia está entre 275 y 285 cm, hay un producto
    Serial.println(" - Hay un producto");
  } else if (distance >= 285) {
    Serial.println(" - No hay productos");
  }
  delay(500);  // Esperar medio segundo antes de realizar otra medición
}
