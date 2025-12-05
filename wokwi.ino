#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// --- WiFi ---
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// --- MQTT ---
const char* mqtt_server = "100.28.226.153";  // MQTT IP
WiFiClient espClient;
PubSubClient client(espClient);

// --- DHT ---
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// --- LDR ---
#define LDRPIN 34
#define LEDPIN 2

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi conectado");
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado ao MQTT");
    } else {
      delay(10000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int ldrValue = analogRead(LDRPIN);

  // Publica no MQTT
  String payload = "{\"temperatura\":" + String(temp) +
                   ",\"umidade\":" + String(hum) +
                   ",\"luminosidade\":" + String(ldrValue) + "}";
  client.publish("futuro_trabalho/sensores", payload.c_str());

  // Alerta simples: acende LED se temperatura > 28°C
  if (temp > 28) {
    digitalWrite(LEDPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
  }

  Serial.println(payload);
  delay(10000);
}
