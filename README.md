# IOT Projeto IOT - UDESC 2023

# README - Dispositivo para Monitoramento em Ambientes Agrícolas
# Descrição do Projeto
O projeto "Dispositivo para Monitoramento de Temperatura, Umidade e Fumaça em Ambientes Agrícolas" visa fornecer uma solução de baixo custo para monitoramento ambiental em ambientes agrícolas. O dispositivo microcontrolador principal, denominado "A1", é responsável por medir a presença de fumaça, gases e poeira usando sensores de qualidade do ar. Esses dados são enviados para um servidor de mensageria por meio de Wi-Fi (802.11) e o protocolo MQTT para comunicação.

Além das informações de qualidade do ar, o dispositivo "A1" também envia dados de temperatura e umidade, juntamente com a identificação do microcontrolador utilizado para controle e transmissão das informações. Por outro lado, o microcontrolador "B1" é encarregado de ler as informações publicadas no Broker MQTT e acionar uma válvula solenoide para dispersão de água no ambiente. 

# Comunicação e Desenvolvimento Aberto
O projeto utiliza hardwares de baixo custo e adota soluções de comunicação e desenvolvimento de código aberto. A comunicação entre os dispositivos é realizada por meio do protocolo MQTT, proporcionando uma arquitetura flexível e escalável.

# Dashboard e Visualização de Dados
Os dados publicados no Broker MQTT são acessados por painéis de monitoramento conhecidos como Dashboards. O projeto prevê pelo menos duas visualizações de Dashboard:

# MQTT-Explorer (Computadores e Notebooks): 
Este Dashboard é voltado para sistemas operacionais Windows, Linux e Mac. O MQTT-Explorer oferece uma interface gráfica para acompanhar o envio de dados, mas não permite o acionamento de dispositivos.

# MQTT Client (Smartphones e Tablets - Android): 
Projetado para uso em dispositivos móveis, o MQTT Client proporciona uma interface gráfica que não só permite visualizar e acompanhar o envio de dados, mas também oferece a opção de configurar alertas na tela e acionar dispositivos por meio da interface gráfica.

# Estrutura do Repositório
O repositório está estruturado da seguinte forma:

/sketch_MQTT_temp_umi_gas.ino: Contém o código-fonte para o microcontrolador "A1", responsável pelo monitoramento e envio de dados.

/sketch_nov14aMQTTSolenoide.ino: Contém o código-fonte para o microcontrolador "B1", responsável por ler dados do Broker MQTT e acionar a válvula solenoide.


# Configuração e Uso
Para configurar e usar o projeto, siga as instruções nos subdiretórios relevantes. Certifique-se de ajustar as configurações do servidor MQTT, credenciais e outras variáveis conforme necessário.

# Pré-Requisitos
Antes de iniciar a implementação do projeto, certifique-se de ter os seguintes pré-requisitos instalados:
Arduino IDE - Utilizado para programar os microcontroladores "A1" e "B1".
MQTT-Explorer - Ferramenta de visualização para computadores e notebooks.
MQTT Client - Aplicativo para visualização em smartphones e tablets Android.
HiveMQTT - Conta no servidor HiveMQTT

# Bibliotecas Utilizadas:

# Esp32 Microcontrolador A1
WiFi.h: A biblioteca WiFi.h é utilizada para configurar e gerenciar a conectividade Wi-Fi do ESP32. Ela fornece funcionalidades para conectar o ESP32 a redes Wi-Fi e monitorar o status da conexão.
PubSubClient.h:A biblioteca PubSubClient.h implementa um cliente MQTT para comunicação com um Broker MQTT. Ela permite que o ESP32 publique mensagens e se inscreva em tópicos para receber mensagens MQTT.
DHT.h: A biblioteca DHT.h é utilizada para interagir com sensores de temperatura e umidade da série DHT. Esses sensores são comuns em projetos que envolvem o monitoramento dessas grandezas.
WiFiClientSecure.h: A biblioteca WiFiClientSecure.h permite estabelecer conexões seguras (HTTPS) com servidores. Ela é útil quando é necessário garantir a segurança na comunicação, como em conexões MQTT seguras.
WebServer.h: A biblioteca WebServer.h oferece suporte à criação de um servidor web no ESP32. Isso possibilita a configuração remota do dispositivo por meio de uma interface web.
NTPClient.h: A biblioteca NTPClient.h permite que o ESP32 sincronize seu relógio interno com servidores de Tempo (NTP). Isso é fundamental para ter informações de data e hora precisas.
WiFiManager.h: A biblioteca WiFiManager.h facilita a gestão da configuração Wi-Fi do ESP32. Ela é especialmente útil quando o dispositivo precisa ser configurado remotamente, pois simplifica o processo de conexão à rede Wi-Fi.

# Esp8266 Microcontrolador B1
ESP8266WiFi: Biblioteca para a configuração e gestão da conectividade Wi-Fi do ESP8266.
WiFiClientSecure: Utilizada para estabelecer conexões seguras com servidores através do protocolo HTTPS.
PubSubClient: Implementa um cliente MQTT para comunicação com um Broker MQTT.
DNSServer: Biblioteca para configurar um servidor DNS no ESP8266.
ESP8266WebServer: Oferece suporte à criação de um servidor web no ESP8266, utilizado para a configuração remota.
WiFiManager: Facilita a gestão da configuração Wi-Fi, permitindo a configuração remota do dispositivo.
TimeLib: Utilizada para manipulação de data e hora.
BearSSL: Implementa funcionalidades de segurança, especialmente útil para conexões seguras com servidores MQTT.

Arduino IDE (Integrated Development Environment): Ferramenta de desenvolvimento para programação dos microcontroladores.
Essas bibliotecas são essenciais para o funcionamento do projeto, fornecendo funcionalidades básicas como comunicação Wi-Fi, MQTT, segurança em conexões e manipulação de data e hora. Certifique-se de ter as versões adequadas instaladas na Arduino IDE para evitar conflitos de compatibilidade.

# Configuração do Ambiente de Desenvolvimento
Abra a Arduino IDE.
Carregue o código-fonte do microcontrolador "A1" localizado em /A1_Microcontroller.
Ajuste as configurações, como o servidor MQTT, credenciais e detalhes da rede Wi-Fi no código.
Compile e faça o upload do código para o microcontrolador "A1".
Repita o mesmo processo para o microcontrolador "B1", carregando o código-fonte de /B1_Microcontroller.

# Configuração dos Dashboards MQTT
MQTT-Explorer (Computadores e Notebooks):
Configurações conforme site da aplicação: https://mqtt-explorer.com/

MQTT Client (Smartphones e Tablets - Android):
Configurações conforme site da aplicação: https://play.google.com/store/apps/details?id=com.doikov.mqttclient&hl=en_US

HiveMQTT (Broker MQTT Serviço de Mensageria):
Acesse o site e crie conta gratuitamente: https://www.hivemq.com/

Instale o aplicativo MQTT Client em seu dispositivo Android.
Configure uma conexão para o servidor MQTT.
Visualize dados e configure alertas conforme necessário.


# Contribuição
Contribuições são bem-vindas! Para grandes alterações, por favor, abra uma issue primeiro para discutir o que você gostaria de mudar.


# Licença
Este projeto é distribuído sob a licença [GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007]. Consulte o arquivo LICENSE para obter mais detalhes.


# Desenvolvido por [Ivo Marcos Riegel] - [2023]



