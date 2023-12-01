#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <TimeLib.h>

const char *mqtt_server = "c6ce1af45cca4e2699b2eff083bc5a9a.s1.eu.hivemq.cloud";
const char *mqtt_username = "ivo.riegel";
const char *mqtt_password = "mqttUdesc2023";
const int mqtt_port = 8883;
const char *sensor4_topic = "valvula";
const char *date_topic = "data_acionamento";
const char *time_topic = "hora_acionamento";
const char *mac_topic = "mac_address";



const char* root_ca = \
 "-----BEGIN CERTIFICATE-----\n" \
"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\n" \
"-----END CERTIFICATE-----\n";

BearSSL::WiFiClientSecure espClient;
PubSubClient client(espClient);
WiFiManager wifiManager;

int Solenoid = 13;
bool solenoidState = false;              // Estado atual da solenoide
bool lastSolenoidState = false;          // Estado anterior da solenoide
unsigned long lastSolenoidTime = 0;      // Último tempo em que a solenoide foi acionada

void setup()
{
    Serial.begin(9600);
    delay(10);
    pinMode(Solenoid, OUTPUT);
    digitalWrite(Solenoid, LOW);

    // Inicializar o WiFiManager
    wifiManager.autoConnect("Dispositivo-8266");

    Serial.println("WiFi Conectada com Sucesso!");
    Serial.print("Acesso no IPv4: ");
    Serial.println(WiFi.localIP());

    espClient.setInsecure();
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);

    // Configurar e sincronizar o relógio interno do ESP8266
    configTime(-3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
}

void loop()
{
    // Obter a data e a hora atual
    time_t now;
    struct tm timeinfo;
    if (getLocalTime(&timeinfo))
    {
        char dateBuffer[20];
        char timeBuffer[20];
        strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", &timeinfo);
        strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", &timeinfo);

        // Se o estado da solenoide mudou
        if (solenoidState != lastSolenoidState)
        {
            // Enviar a informação para o servidor MQTT
            client.publish(date_topic, dateBuffer);
            client.publish(time_topic, timeBuffer);

            // Enviar o endereço MAC para o servidor MQTT
            String macAddress = WiFi.macAddress();
            client.publish(mac_topic, macAddress.c_str());

            // Atualizar o último tempo e estado da solenoide
            lastSolenoidTime = millis();
            lastSolenoidState = solenoidState;
        }

        // Se passou tempo suficiente desde o último acionamento, redefinir o estado
        if (millis() - lastSolenoidTime > 60000) // 60000 ms = 1 minuto
        {
            solenoidState = false;
        }
    }

    // Se a solenoide não estiver conectada, reconectar
    if (!client.connected())
    {
        reconnect();
    }

    // Lidar com as operações do MQTT
    client.loop();
}

void reconnect()
{
    while (!client.connected())
    {
        Serial.println("Tentando conexão MQTT");
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);

        if (client.connect(clientId.c_str(), mqtt_username, mqtt_password))
        {
            Serial.println("Conectado ao Broker MQTT!");
            client.subscribe(sensor4_topic);
        }
        else
        {
            Serial.print("Falha na conexão, rc=");
            Serial.print(client.state());
            Serial.println(" Tentando novamente em 5 segundos");
            delay(5000);
        }
    }
}

unsigned long lastStatusUpdate = 0;
bool firstReading = true;

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Messagem recebida do topico: ");
    Serial.println(topic);

    String message = "";
    for (int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }

    if (strcmp(topic, sensor4_topic) == 0)
    {
        int receivedValveState = message.toInt();
        if (receivedValveState == 0)
        {
            solenoidState = false;
            digitalWrite(Solenoid, LOW);
            Serial.println("Válvula Solenoide: Desligada!");
        }
        else
        {
            solenoidState = true;
            digitalWrite(Solenoid, HIGH);
            Serial.println("Válvula Solenoide: Ligada!");

            // Enviar o status da leitura para um novo tópico
            String statusTopic = "status_valvula";
            String statusMessage = (solenoidState ? "Ligada" : "Desligada");
            client.publish(statusTopic.c_str(), statusMessage.c_str());

            // Verificar se é a primeira leitura
            if (firstReading)
            {
                firstReading = false;
                lastStatusUpdate = millis(); // Registrar o tempo da primeira leitura
            }
            else if (millis() - lastStatusUpdate > 15000) // 15000 ms = 15 segundos
            {
                // Enviar os dados de data, hora e MAC address
                time_t now;
                struct tm timeinfo;
                if (getLocalTime(&timeinfo))
                {
                    char dateBuffer[20];
                    char timeBuffer[20];
                    strftime(dateBuffer, sizeof(dateBuffer), "%Y-%m-%d", &timeinfo);
                    strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", &timeinfo);

                    client.publish(date_topic, dateBuffer);
                    client.publish(time_topic, timeBuffer);

                    String macAddress = WiFi.macAddress();
                    client.publish(mac_topic, macAddress.c_str());

                    // Atualizar o tempo da última atualização
                    lastStatusUpdate = millis();
                }
            }
        }
    }
}

