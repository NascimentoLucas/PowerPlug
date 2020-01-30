class WiffiObject{  
  //ATÉ QUE O NÚMERO DE TENTATIVAS EXPIRE (RESULTANDO EM WL_NO_SHIELD) OU QUE UMA CONEXÃO SEJA ESTABELECIDA
  //(RESULTANDO EM WL_CONNECTED)
  
  int statusLed = LOW; //VARIÁVEL QUE ARMAZENA O ESTADO ATUAL DO LED (LIGADO / DESLIGADO)
  
  WiFiEspClient client;
  inline void sendLine(WiFiEspClient client, char head[],int value){
    //client.print(";");
    //client.print(head);
    client.println(value);
    client.print(";");
  }

  void sendHttpResponse(WiFiEspClient client){
      client.println("HTTP/1.1 200 OK"); //ESCREVE PARA O CLIENTE A VERSÃO DO HTTP
      client.println("Content-Type: text/html"); //ESCREVE PARA O CLIENTE O TIPO DE CONTEÚDO(texto/html)
      client.println("");
      client.println("<!DOCTYPE HTML>"); //INFORMA AO NAVEGADOR A ESPECIFICAÇÃO DO HTML
      client.println("<html>"); //ABRE A TAG "html"
      client.println("<head>"); //ABRE A TAG "head"
      client.println("<link rel='icon' type='image/png' href='https://blogmasterwalkershop.com.br/arquivos/artigos/sub_wifi/icon_mws.png'/>"); //DEFINIÇÃO DO ICONE DA PÁGINA
      client.println("<link rel='stylesheet' type='text/css' href='https://blogmasterwalkershop.com.br/arquivos/artigos/sub_wifi/webpagecss.css' />"); //REFERENCIA AO ARQUIVO CSS (FOLHAS DE ESTILO)
      client.println("<title>MasterWalker Shop - Modulo WiFi ESP8266 para Arduino</title>"); //ESCREVE O TEXTO NA PÁGINA
      client.println("</head>"); //FECHA A TAG "head"
      
      //AS LINHAS ABAIXO CRIAM A PÁGINA HTML
      client.println("<body>"); //ABRE A TAG "body"
      client.println("<img alt='masterwalkershop' src='https://blogmasterwalkershop.com.br/arquivos/artigos/sub_wifi/logo_mws.png' height='156' width='700' />"); //LOGO DA MASTERWALKER SHOP
      client.println("<p style='line-height:2'><font>Modulo WiFi ESP8266 para Arduino</font></p>"); //ESCREVE O TEXTO NA PÁGINA
      client.println("<font>ESTADO ATUAL DO LED</font>"); //ESCREVE O TEXTO NA PÁGINA
      
      if (statusLed == HIGH){ //SE VARIÁVEL FOR IGUAL A HIGH (1), FAZ
        client.println("<p style='line-height:0'><font color='green'>LIGADO</font></p>"); //ESCREVE "LIGADO" NA PÁGINA
        client.println("<a href=\"/L\">APAGAR</a>"); //COMANDO PARA APAGAR O LED (PASSA O PARÂMETRO /L)
      }else{ //SENÃO, FAZ
        if (statusLed == LOW){ //SE VARIÁVEL FOR IGUAL A LOW (0), FAZ
        client.println("<p style='line-height:0'><font color='red'>DESLIGADO</font></p>"); //ESCREVE "DESLIGADO" NA PÁGINA
        client.println("<a href=\"/H\">ACENDER</a>"); //COMANDO PARA ACENDER O LED (PASSA O PARÂMETRO /H)
        }
      }
      client.println("<hr />"); //TAG HTML QUE CRIA UMA LINHA NA PÁGINA
      client.println("<hr />"); //TAG HTML QUE CRIA UMA LINHA NA PÁGINA
      client.println("</body>"); //FECHA A TAG "body"
      client.println("</html>"); //FECHA A TAG "html"
      
      delay(1); //INTERVALO DE 1 MILISSEGUNDO
    }
    
  public:  
    int status = WL_IDLE_STATUS; //STATUS TEMPORÁRIO ATRIBUÍDO QUANDO O WIFI É INICIALIZADO E PERMANECE ATIVO
    WiffiObject(SoftwareSerial Serial1, WiFiEspServer server){
      
      //FIM - VERIFICA SE O ESP8266 ESTÁ CONECTADO AO ARDUINO, CONECTA A REDE SEM FIO E INICIA O WEBSERVER
    }
    
    void update(WiFiEspServer server, RingBuffer buf){    
      if (client) { //SE CLIENTE TENTAR SE CONECTAR, FAZ
        buf.init(); //INICIALIZA O BUFFER
        while (client.connected()){ //ENQUANTO O CLIENTE ESTIVER CONECTADO, FAZ
          if(client.available()){ //SE EXISTIR REQUISIÇÃO DO CLIENTE, FAZ
            char c = client.read(); //LÊ A REQUISIÇÃO DO CLIENTE
            buf.push(c); //BUFFER ARMAZENA A REQUISIÇÃO
    
            //IDENTIFICA O FIM DA REQUISIÇÃO HTTP E ENVIA UMA RESPOSTA
            if(buf.endsWith("\r\n\r\n")) {
              sendHttpResponse(client);
              break;
            }
            if(buf.endsWith("GET /H")){ //SE O PARÂMETRO DA REQUISIÇÃO VINDO POR GET FOR IGUAL A "H", FAZ 
                digitalWrite(LED_BUILTIN, HIGH); //ACENDE O LED
                statusLed = 1; //VARIÁVEL RECEBE VALOR 1(SIGNIFICA QUE O LED ESTÁ ACESO)
            }
            else{ //SENÃO, FAZ
              if (buf.endsWith("GET /L")) { //SE O PARÂMETRO DA REQUISIÇÃO VINDO POR GET FOR IGUAL A "L", FAZ
                      digitalWrite(LED_BUILTIN, LOW); //APAGA O LED
                      statusLed = 0; //VARIÁVEL RECEBE VALOR 0(SIGNIFICA QUE O LED ESTÁ APAGADO)
              }
            }
          }
        }

        client.stop(); //FINALIZA A REQUISIÇÃO HTTP E DESCONECTA O CLIENTE
      }
      else{              
        client = server.available(); //ATENDE AS SOLICITAÇÕES DO CLIENTE
      }
    }
    
    //MÉTODO DE RESPOSTA A REQUISIÇÃO HTTP DO CLIENTE
    
};
