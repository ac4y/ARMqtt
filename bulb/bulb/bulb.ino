#define LED_PIN 26  // A LED-et a GPIO26-ra kötöttük

void setup() {
  pinMode(LED_PIN, OUTPUT); // LED kimenetként beállítása
}

void loop() {
  digitalWrite(LED_PIN, HIGH); // LED bekapcsol
  delay(500);                  // 500 ms várakozás
  digitalWrite(LED_PIN, LOW);  // LED kikapcsol
  delay(500);                  // 500 ms várakozás
}
