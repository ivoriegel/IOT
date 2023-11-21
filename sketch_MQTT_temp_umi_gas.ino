#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <WiFiClientSecure.h>
#include <WebServer.h>
#include <NTPClient.h>
#include <WiFiManager.h>  // Adiciona a biblioteca WiFiManager


#define DHTTYPE DHT11  // DHT 11
#define MAX_LEN 50
int redLed = 32;
int greenLed = 26;
int Gas_analog = 39;
int Gas_digital = 4;
int sensorThreshold = 20; // 250 valor padrão diminuir para disparar com fumaça
unsigned long previousMillis = 0;
const long interval = 15000;  // Intervalo de leitura e exibição de dados 15 segundos
int DHTPin = 33;
int relePin = 23;
int valvePin;
bool releState;
String macaddress;
String hora_captura;




/* Put your SSID & Password */
//const char* ssid = "CLARO_2GDAEF04";   // Enter SSID here CLARO_2GDAEF04 moto g(6) 5049
//const char* password = "8BDAEF04Ivo";  // Enter Password here 8BDAEF04Ivo 271102niver
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");



/* MQTT Broker configuração */
const char* mqtt_server = "c6ce1af45cca4e2699b2eff083bc5a9a.s1.eu.hivemq.cloud"; // replace with your broker URL
const char* mqtt_username = "ivo.riegel";
const char* mqtt_password = "mqttUdesc2023";
const int mqtt_port = 8883;
const char* sensor1_topic = "gas";
const char* sensor2_topic = "temperatura";
const char* sensor3_topic = "umidade";
const char* sensor4_topic = "valvula";
const char* sensor5_topic = "rele";
const char* sensor6_topic = "macaddress";
const char* sensor7_topic = "hora_captura";


const char* root_ca = \
 "-----BEGIN CERTIFICATE-----\n" \
"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\n" \
"-----END CERTIFICATE-----\n";

WiFiClientSecure espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;

WebServer server(80);
// DHT Sensor
DHT dht(DHTPin, DHTTYPE);
float Temperature;
float Humidity;
int valveState = LOW;


void setup() {
  Serial.begin(9600);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(Gas_digital, INPUT);
  pinMode(relePin, OUTPUT);

  WiFiManager wifiManager;  // Cria uma instância do WiFiManager
  wifiManager.autoConnect("AutoConnectAP");  // Tenta conectar-se ao WiFi, se falhar, inicia um ponto de acesso

  delay(100);
  pinMode(DHTPin, INPUT);
  dht.begin();
  

  Serial.println("###################################");
  //Serial.print("Conectando rede: "+String(ssid));

  // Connect to your local Wi-Fi network
  String ssid = wifiManager.getWiFiSSID();
  String password = wifiManager.getWiFiPass();
  WiFi.begin(ssid, password);
  timeClient.begin();
  timeClient.setTimeOffset(-10800);

  espClient.setCACert(root_ca);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Check Wi-Fi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectando rede: "+String(ssid));
  Serial.println("WiFi Conectada com Sucesso..!");
  Serial.print("Acesso no IPv4: ");
  Serial.println(WiFi.localIP());
  Serial.print("Acesso no IPv6: ");
  Serial.println(WiFi.localIPv6());

}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  server.handleClient();
  unsigned long currentMillis = millis();
  
  timeClient.update();
  hora_captura = timeClient.getFormattedTime();
  macaddress = WiFi.macAddress();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int gasValue = analogRead(Gas_analog);
    int gassensorDigital = digitalRead(Gas_digital);
    Temperature = dht.readTemperature();  // Gets the values of the temperature
    Humidity = dht.readHumidity(); // Gets the values of the umidity

  
    if (gasValue > sensorThreshold) {
      Serial.println("Gás digital: "+ String(gassensorDigital));
      Serial.println("Presença de Gás: "+ String(gasValue));
      Serial.println("Temperatura: "+ String(Temperature));
      Serial.println("Umidade: "+ String(Humidity));
      valveState = HIGH; //Ativa a Válvula 
      Serial.println("Válvula: "+ String(valveState)); 
      releState = HIGH;         
      digitalWrite(relePin, HIGH);
      Serial.println("Relé: "+ String(releState));
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, HIGH);

      
      Serial.println("Meu macAddress: "+ macaddress);
      Serial.println("Hora caputra: "+ hora_captura);
    } else {
      Serial.println("Gás digital: "+ String(gassensorDigital));
      Serial.println("Sem Gás: "+ String(gasValue));
      Serial.println("Temperatura: "+ String(Temperature));
      Serial.println("Umidade: "+ String(Humidity));
      valveState = LOW; //Desativa a Válvula  
      Serial.println("Válvula: "+ String(valveState));
      releState = LOW;          
      digitalWrite(relePin, LOW);
      Serial.println("Relé: "+ String(releState));
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed, LOW);

      Serial.println("Meu macAddress: "+ macaddress);
      Serial.println("Hora caputra: "+ hora_captura);
    }

    // Publish sensor data to MQTT topics
    publishMessage(sensor1_topic, String(gasValue), true);
    publishMessage(sensor2_topic, String(Temperature), true);
    publishMessage(sensor3_topic, String(Humidity), true);
    publishMessage(sensor4_topic, String(valveState),true);
    publishMessage(sensor5_topic, String(releState),true);
    publishMessage(sensor6_topic, String(macaddress),true);
    publishMessage(sensor7_topic, String(hora_captura),true);
  }
}




void reconnect() {
  while (!client.connected()) {
    Serial.println("#######Tentando conexão MQTT#######");
    String clientId = "ESP32Client-"; // Create a random client ID
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("#####Conectado ao Broker MQTT!#####");
      client.subscribe(sensor1_topic); // subscribe to the topics here
      client.subscribe(sensor2_topic); // subscribe to the topics here
      client.subscribe(sensor3_topic); // subscribe to the topics here
      client.subscribe(sensor4_topic); // subscribe to the topics here
      client.subscribe(sensor5_topic); // subscribe to the topics here
      client.subscribe(sensor6_topic); // subscribe to the topics here
    } else {
      Serial.print("Falha na conexão com, rc=");
      Serial.print(client.state());
      Serial.println(" Tente novamente em 5 segundos");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
   Serial.print("Messagem recebida do topico: ");
   Serial.println(topic);

   String message = "";
   for(int i = 0; i < length; i++){
    message += (char)payload[i];
   }
   if(strcmp(topic, sensor4_topic) == 0){
    int receivedValveState = message.toInt();
    if(receivedValveState == 1){
      digitalWrite(relePin, HIGH);
      Serial.println("Relé: Ligado!");
    }else{
      digitalWrite(relePin, LOW);
      Serial.println("Relé: Desligado!");
    }
   }
   //Serial.println("Mensagem: "+ message);
}

void publishMessage(const char* topic, String payload, boolean retained) {
  if (client.publish(topic, payload.c_str(), retained)) {
    Serial.println("Message published [" + String(topic) + "]: " + payload);
  }
}


