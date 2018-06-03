/*

  41427981 - Sergio A. Montini Jr. 05J
  31638236 - Sabrinna Delgado 05F
  31535879 - Lucas Pafume 05F

*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Servo.h>
#define DHTPIN 5     // Pino digital da qual está conectado
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define SERVO 15 // Porta digital no NodeMCU

//const char* ssid = "cmnm";
//const char* password = "St4rW4rs";
const char* ssid = "SSID";
const char* password = "SENHA";
const char* mqtt_server = "broker.hivemq.com";

int rainPin = 4;
int greenLED = 12;
int redLED = 14;
//int thresholdValue = 0;
int pos = 65; // Posição Servo

DHT dht(DHTPIN, DHTTYPE);
Servo s; // Variável Servo

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  pinMode(rainPin, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  Serial.begin(9600);
  Serial.println("Sensor DHT OK");
  dht.begin();
  s.attach(SERVO);
  s.write(pos);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
//  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());
}

//void callback(char* topic, byte* payload, unsigned int length) {
//  Serial.print("Valor recebido do Broker (Posição do servo): [");
//  Serial.print(topic);
//  Serial.print("] ");
//  for (int i = 0; i < length; i++) {
//    Serial.print((char)payload[i]);
//  }
//  Serial.println();
//  
//}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Estabelecendo conexão via MQTT...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("conectado");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
//    client.subscribe("inTopic");
//      client.subscribe("cmnm/servo");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" tente novamente em 5 segundos");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  
  delay(150);
  int sensorValue = digitalRead(rainPin);
  if (sensorValue == 0) {
    Serial.println("Clima Molhado");
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    s.write(0);

    client.publish("cmnm/clima", "Chovendo");    
  }
  else {
    Serial.println("Clima Seco");
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    s.write(pos);
 
    client.publish("cmnm/clima", "Seco");   
  }

  // Wait a few seconds between measurements.
  delay(3000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Falha ao ler o sensor DHT!");
    return;
  }

  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Umidade: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" C\t");
  Serial.print("Índice de calor: ");
  Serial.print(hic);
  Serial.print(" C\t");

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    
      String str_temp = String(t);
//      //sprintf(str_rain,rainSensor);
      str_temp.toCharArray(msg, 4);
      client.publish("cmnm/temperatura", msg);

      String str_hum = String(h);
      str_hum.toCharArray(msg, 4);
      client.publish("cmnm/humidade", msg);

      String str_hic = String(hic);
      str_hic.toCharArray(msg, 4);
      client.publish("cmnm/indicecalor", msg);

  }

}

