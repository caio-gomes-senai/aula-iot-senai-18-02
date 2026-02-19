/\*

&nbsp;\* wifiClient.ino

&nbsp;\* Exemplo de cliente WiFi para ESP8266 / ESP32

&nbsp;\* Conecta à rede WiFi e faz uma requisição HTTP GET simples.

&nbsp;\*/



// ── Escolha a placa correta ──────────────────────────────────────────────────

// Para ESP8266:

\#include <ESP8266WiFi.h>



// Para ESP32, comente a linha acima e descomente a abaixo:

// #include <WiFi.h>

// ────────────────────────────────────────────────────────────────────────────



// ── Configurações de rede ────────────────────────────────────────────────────

const char\* ssid     = "SEU\_SSID";       // Nome da sua rede WiFi

const char\* password = "SUA\_SENHA";      // Senha da rede WiFi

// ────────────────────────────────────────────────────────────────────────────



// ── Servidor alvo ────────────────────────────────────────────────────────────

const char\* host = "exemplo.com";        // Domínio ou IP do servidor

const uint16\_t port = 80;               // Porta (80 = HTTP, 443 = HTTPS)

const char\* path = "/";                 // Caminho da requisição

// ────────────────────────────────────────────────────────────────────────────



WiFiClient client;



void setup() {

&nbsp; Serial.begin(115200);

&nbsp; delay(100);



&nbsp; Serial.println();

&nbsp; Serial.print("Conectando ao WiFi: ");

&nbsp; Serial.println(ssid);



&nbsp; WiFi.mode(WIFI\_STA);

&nbsp; WiFi.begin(ssid, password);



&nbsp; // Aguarda conexão

&nbsp; while (WiFi.status() != WL\_CONNECTED) {

&nbsp;   delay(500);

&nbsp;   Serial.print(".");

&nbsp; }



&nbsp; Serial.println();

&nbsp; Serial.println("WiFi conectado!");

&nbsp; Serial.print("Endereço IP: ");

&nbsp; Serial.println(WiFi.localIP());

}



void loop() {

&nbsp; Serial.println();

&nbsp; Serial.print("Conectando ao servidor: ");

&nbsp; Serial.println(host);



&nbsp; if (!client.connect(host, port)) {

&nbsp;   Serial.println("Falha na conexão com o servidor!");

&nbsp;   delay(5000);

&nbsp;   return;

&nbsp; }



&nbsp; Serial.println("Conexão estabelecida. Enviando requisição HTTP GET...");



&nbsp; // Monta e envia a requisição HTTP

&nbsp; client.print(String("GET ") + path + " HTTP/1.1\\r\\n" +

&nbsp;              "Host: " + host + "\\r\\n" +

&nbsp;              "Connection: close\\r\\n\\r\\n");



&nbsp; // Aguarda resposta do servidor (timeout de 5 segundos)

&nbsp; unsigned long timeout = millis();

&nbsp; while (client.available() == 0) {

&nbsp;   if (millis() - timeout > 5000) {

&nbsp;     Serial.println("Timeout! Encerrando conexão.");

&nbsp;     client.stop();

&nbsp;     delay(5000);

&nbsp;     return;

&nbsp;   }

&nbsp; }



&nbsp; // Lê e imprime a resposta

&nbsp; Serial.println("Resposta do servidor:");

&nbsp; while (client.available()) {

&nbsp;   String line = client.readStringUntil('\\n');

&nbsp;   Serial.println(line);

&nbsp; }



&nbsp; Serial.println();

&nbsp; Serial.println("Conexão encerrada.");

&nbsp; client.stop();



&nbsp; // Aguarda 10 segundos antes de nova requisição

&nbsp; delay(10000);

}



