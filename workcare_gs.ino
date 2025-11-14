#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"

// Pinos
const int DHT_PIN = 15;
const int LED_PIN = 2;  // pode ser LED interno do ESP32

// Objetos
DHTesp dht;
WiFiClient espClient;
PubSubClient client(espClient);

// Wi-Fi do Wokwi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Broker MQTT público
const char* mqttServer = "broker.hivemq.com";
const int   mqttPort   = 1883;

// Controle de tempo
unsigned long inicioTrabalho = 0;
const unsigned long LIMITE_TRABALHO_MS = 50UL * 60UL * 1000UL;
unsigned long ultimoEnvio = 0;

void conectaWiFi() {
  Serial.print("Conectando ao WiFi ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void conectaMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando ao broker MQTT...");
    String clientId = "workcare-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("conectado!");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando de novo em 2s...");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando WorkCare IoT...");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  dht.setup(DHT_PIN, DHTesp::DHT22);

  conectaWiFi();
  client.setServer(mqttServer, mqttPort);

  inicioTrabalho = millis();
}

void loop() {
  // Garante que Wi-Fi e MQTT fiquem conectados
  if (WiFi.status() != WL_CONNECTED) {
    conectaWiFi();
  }
  if (!client.connected()) {
    conectaMQTT();
  }
  client.loop();

  unsigned long agora = millis();

  // Envia a cada 5 segundos
  if (agora - ultimoEnvio >= 5000) {
    ultimoEnvio = agora;

    // Lê o sensor
    TempAndHumidity data = dht.getTempAndHumidity();
    float temperatura = data.temperature;
    float umidade = data.humidity;

    // Tempo de trabalho em ms
    unsigned long tempoTrabalho = agora - inicioTrabalho;
    float tempoTrabalhoSeg = tempoTrabalho / 1000.0;

    bool ambienteRuim = temperatura > 28.0;
    bool tempoExagerado = tempoTrabalho > LIMITE_TRABALHO_MS;

    bool precisaAlerta = ambienteRuim || tempoExagerado;

    // LED
    digitalWrite(LED_PIN, precisaAlerta ? HIGH : LOW);

    // Debug Serial
    Serial.println("---- STATUS ----");
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");

    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println(" %");

    Serial.print("Tempo de trabalho: ");
    Serial.print(tempoTrabalhoSeg);
    Serial.println(" s");

    if (ambienteRuim) {
      Serial.println("Ambiente desconfortável (muito quente).");
    }
    if (tempoExagerado) {
      Serial.println("Tempo de trabalho passou do limite (simulado).");
    }
    if (!precisaAlerta) {
      Serial.println("Tudo ok. Ambiente e tempo dentro do normal.");
    } else {
      Serial.println("ALERTA: precisa de pausa ou ajuste no ambiente!");
    }

    // Monta payload JSON
    String payload = "{";
    payload += "\"temperatura\":" + String(temperatura, 1) + ",";
    payload += "\"umidade\":" + String(umidade, 1) + ",";
    payload += "\"tempo_trabalho_s\":" + String(tempoTrabalhoSeg, 1) + ",";
    payload += "\"alerta\":" + String(precisaAlerta ? "true" : "false");
    payload += "}";

    Serial.print("Publicando MQTT: ");
    Serial.println(payload);

    // Publica no tópico
    client.publish("workcare/estacao1/sensores", payload.c_str());
    Serial.println("----------------\n");
  }
}
