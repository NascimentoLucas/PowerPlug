#include "WiFiEsp.h"; //INCLUSÃO DA BIBLIOTECA
#include "SoftwareSerial.h";//INCLUSÃO DA BIBLIOTECA
#include "WiffiClass.h";



SoftwareSerial Serial1(6, 7); //PINOS QUE EMULAM A SERIAL, ONDE O PINO 6 É O RX E O PINO 7 É O TX  
WiFiEspServer server(80); //CONEXÃO REALIZADA NA PORTA 80
RingBuffer buf(8); //BUFFER PARA AUMENTAR A VELOCIDADE E REDUZIR A ALOCAÇÃO DE MEMÓRIA

int pinPower = 8;


  
WiffiObject wf(Serial1, server, pinPower);
DataSecurityObject data(1);

void setup(){
  pinMode(pinPower, OUTPUT); 
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, LOW); 
  digitalWrite(pinPower, HIGH); 
  Serial.begin(9600); //INICIALIZA A SERIAL
  Serial1.begin(9600); //INICIALIZA A SERIAL PARA O ESP8266
  WiFi.init(&Serial1); //INICIALIZA A COMUNICAÇÃO SERIAL COM O ESP8266
  WiFi.config(IPAddress(data.ip[0], data.ip[1], data.ip[2], data.ip[3])); //COLOQUE UMA FAIXA DE IP DISPONÍVEL DO SEU ROTEADOR
  
  //INÍCIO - VERIFICA SE O ESP8266 ESTÁ CONECTADO AO ARDUINO, CONECTA A REDE SEM FIO E INICIA O WEBSERVER
  if(WiFi.status() == WL_NO_SHIELD){
    while (true);
  }
  while(wf.status != WL_CONNECTED){
    wf.status = WiFi.begin(data.ssid, data.pass);
  }
  server.begin();
  digitalWrite(LED_BUILTIN, HIGH); 
}

void loop(){
  wf.update(server, buf, data);
}
