#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define BLYNK_TEMPLATE_ID "TMPL5DJDGmJmx"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"

char auth[] = "GzC7xRfxXuUO-wMjYRHEIF0FC7p9q_lp";
char ssid[] = "VIRGIN-Telco_81D0";
char password[] = "PTsxSQtbcCDhbt";

int ledPin = 21;
BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  Blynk.begin(auth, ssid, password);
  timer.setInterval(10000L, ledToggle);  // Cambiar el estado del LED cada 10 segundos
}

void loop() {
  Blynk.run();
  timer.run();
}

void ledToggle() {
  static bool ledState = false;
  ledState = !ledState;
  digitalWrite(ledPin, ledState);

  if (ledState) {
    Blynk.notify("El LED está encendido");
  } else {
    Blynk.notify("El LED está apagado");
  }
}
