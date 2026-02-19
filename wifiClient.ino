/*
 * wifiClient.ino
 * Exemplo de cliente WiFi para ESP8266 / ESP32
 * Conecta à rede WiFi e faz uma requisição HTTP GET simples.
 */

// ── Escolha a placa correta ──────────────────────────────────────────────────
// Para ESP8266:
#include <ESP8266WiFi.h>

// Para ESP32, comente a linha acima e descomente a abaixo:
// #include <WiFi.h>
// ────────────────────────────────────────────────────────────────────────────

// ── Configurações de rede ────────────────────────────────────────────────────
const char* ssid     = "REDEWORK";        // Nome da sua rede WiFi
const char* password = "Acessonet05";    // Senha da rede WiFi
// ────────────────────────────────────────────────────────────────────────────

// ── Servidor alvo ────────────────────────────────────────────────────────────
const char* host = "exemplo.com";        // Domínio ou IP do servidor
const uint16_t port = 80;               // Porta (80 = HTTP, 443 = HTTPS)
const char* path = "/";                 // Caminho da requisição
// ────────────────────────────────────────────────────────────────────────────

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.print("Conectando ao WiFi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Aguarda conexão
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println();
  Serial.print("Conectando ao servidor: ");
  Serial.println(host);

  if (!client.connect(host, port)) {
    Serial.println("Falha na conexão com o servidor!");
    delay(5000);
    return;
  }

  Serial.println("Conexão estabelecida. Enviando requisição HTTP GET...");

  // Monta e envia a requisição HTTP
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  // Aguarda resposta do servidor (timeout de 5 segundos)
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println("Timeout! Encerrando conexão.");
      client.stop();
      delay(5000);
      return;
    }
  }

  // Lê e imprime a resposta
  Serial.println("Resposta do servidor:");
  while (client.available()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }

  Serial.println();
  Serial.println("Conexão encerrada.");
  client.stop();

  // Aguarda 10 segundos antes de nova requisição
  delay(10000);
}
