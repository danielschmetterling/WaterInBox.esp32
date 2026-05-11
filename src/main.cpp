#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>

const char* ssid = "murilinho";
const char* password = "senhajoia";

WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Inicializa o LittleFS (onde seus arquivos HTML/CSS estão gravados)
  if (!LittleFS.begin(true)) {
    Serial.println("Erro ao montar o LittleFS");
    return;
  }

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado!");
  Serial.print("IP para acessar a página: ");
  Serial.println(WiFi.localIP());

  // Rotas do Servidor Web
  server.serveStatic("/", LittleFS, "/index.html");
  server.serveStatic("/style.css", LittleFS, "/style.css");
  server.serveStatic("/script.js", LittleFS, "/script.js");

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  // Mantém o servidor escutando as requisições do navegador
  server.handleClient();
  
  // Aqui você colocará depois as lógicas de leitura do sensor e MQTT
}