#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
// 🔹 Wi-Fi beállítások
const char* ssid = "HUAWEI_B535_C19F"; //"PL@NDBS";//"Telek2023";
const char* password = "435L8Em6LGm"; // "Jelszo2007118";//"Mariaudvar2023";

// 🔹 MQTT broker beállítások (pl. HiveMQ Cloud)
const char* mqtt_server = "7ebd81b67c5d4be68971905b7c0ad248.s1.eu.hivemq.cloud";  // HiveMQ Cloud esetén
const int mqtt_port = 8883;  // TLS biztonságos kapcsolat
const char* mqtt_user = "admin";
const char* mqtt_password = "Manage2000";
const char* mqtt_topic = "test2";  // Feliratkozási téma
const int relayPin = 13;
int status=0;
WiFiClientSecure espClient;
PubSubClient client(espClient);

// 🔹 Üzenetfogadó függvény
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("📩 Üzenet érkezett [");
  Serial.print(topic);
  Serial.print("]: ");

  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if (status==0) {
    digitalWrite(relayPin, HIGH);
    status = 1;
  }
  else {
    digitalWrite(relayPin, LOW);
    status=0;
  }
    

}

// 🔹 Wi-Fi kapcsolat létrehozása
void setup_wifi() {
  delay(10);
  Serial.println("🔗 Wi-Fi csatlakozás...");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\n✅ Wi-Fi csatlakozva!");
}

// 🔹 MQTT kapcsolódás és újracsatlakozás
void reconnect() {
  while (!client.connected()) {
    Serial.print("🔄 MQTT kapcsolódás...");
    
    if (client.connect("ESP32_Client", mqtt_user, mqtt_password)) {
      Serial.println("✅ MQTT csatlakozva!");
      client.subscribe(mqtt_topic);  // Feliratkozás a témára
    } else {
      Serial.print("❌ Hiba, kód: ");
      Serial.print(client.state());
      Serial.println("  Újrapróbálkozás 5 másodperc múlva...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();

  espClient.setInsecure();  // Ha nincs saját tanúsítványod
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
    pinMode(relayPin, OUTPUT);// set pin as output
    digitalWrite(relayPin, HIGH); // set initial state OFF for low trigger relay

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
/*
  String message = "Hello from ESP32!";
  if (client.publish("test", message.c_str())) {
    Serial.println("Message Published");
  }

  delay(5000);  // Publish every 5 seconds  
  */
}
