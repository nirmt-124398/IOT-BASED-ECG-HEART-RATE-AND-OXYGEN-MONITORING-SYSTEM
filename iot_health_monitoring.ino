#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define WIFISSID "YOUR_WIFI_NAME"
#define PASSWORD "YOUR_WIFI_PASSWORD"
#define TOKEN "YOUR_UBIDOTS_TOKEN"
#define MQTT_CLIENT_NAME "myecgsensor"
#define DEVICE_LABEL "remote-patient-health-monitoring"
#define ONE_WIRE_BUS 2
#define REPORTING_PERIOD_MS 1000
#define SENSOR A0

char mqttBroker[] = "industrial.api.ubidots.com";
char payload[100];
char topic[150];

PulseOximeter pox;
uint32_t tsLastReport = 0;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
WiFiClient ubidots;
PubSubClient client(ubidots);

void onBeatDetected() {}

void reconnect() {
  while (!client.connected()) {
    if (!client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      delay(2000);
    }
  }
}

void publishValue(const char* label, float value) {
  char str[16];
  dtostrf(value, 4, 2, str);
  sprintf(topic, "/v1.6/devices/%s", DEVICE_LABEL);
  sprintf(payload, "{\"%s\": {\"value\": %s}}", label, str);
  client.publish(topic, payload);
  client.loop();
}

void setup() {
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(SENSOR, INPUT);
  Serial.begin(115200);
  sensors.begin();
  sensors.setResolution(9);
  WiFi.begin(WIFISSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  digitalWrite(D7, HIGH);
  Serial.println(WiFi.localIP());
  client.setServer(mqttBroker, 1883);
  if (!pox.begin()) {
    Serial.println("MAX30100 not found");
  }
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  pox.update();

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    tsLastReport = millis();

    float ecg = analogRead(SENSOR);
    float heartRate = pox.getHeartRate();
    float spo2 = pox.getSpO2();
    sensors.requestTemperatures();
    float tempC = sensors.getTempCByIndex(0);
    float tempF = (tempC * 1.8) + 32;

    publishValue("myecg", ecg);
    publishValue("temperature", tempF);

    bool fingerOn = (heartRate > 0 && spo2 > 0);
    if (fingerOn) {
      publishValue("heartrate", heartRate);
      publishValue("SPo2", spo2);
    }

    bool abnormal = (tempF > 99) ||
                    (fingerOn && (spo2 < 95 || heartRate < 65 || heartRate > 100));
    digitalWrite(D8, abnormal ? HIGH : LOW);
    digitalWrite(D6, abnormal ? LOW : HIGH);
  }
}
