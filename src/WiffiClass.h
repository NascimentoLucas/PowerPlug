class WiffiObject{  
  //ATÉ QUE O NÚMERO DE TENTATIVAS EXPIRE (RESULTANDO EM WL_NO_SHIELD) OU QUE UMA CONEXÃO SEJA ESTABELECIDA
  //(RESULTANDO EM WL_CONNECTED)
  int statusLed = LOW; //VARIÁVEL QUE ARMAZENA O ESTADO ATUAL DO LED (LIGADO / DESLIGADO)
  
  WiFiEspClient client;

  void sendHttpResponse(WiFiEspClient client){
      client.println("HTTP/1.1 200 OK"); //ESCREVE PARA O CLIENTE A VERSÃO DO HTTP
      client.println("Content-Type: text/html"); //ESCREVE PARA O CLIENTE O TIPO DE CONTEÚDO(texto/html)
      client.println("");
      client.println("<!DOCTYPE HTML>"); //INFORMA AO NAVEGADOR A ESPECIFICAÇÃO DO HTML
      client.println("<html>"); //ABRE A TAG "html"
      client.println("<head>"); //ABRE A TAG "head" 
      client.println("<script type=\"text/javascript\" src=\"http://devlucasnascimento.com.br/Arduino/loadHtml.js \"></script>");               
      client.println("</head>"); // FEACHA A TAG "head"
      client.println("<body>"); 
      client.println("<iframe id=\"contentTest\">teste</iframe>");
      if (statusLed == HIGH){ //SE VARIÁVEL FOR IGUAL A HIGH (1), FAZ
        client.println("<p style='line-height:0'><font color='green'>LIGADO</font></p>"); //ESCREVE "LIGADO" NA PÁGINA
        client.println("<a href=\"/L\">APAGAR</a>"); //COMANDO PARA APAGAR O LED (PASSA O PARÂMETRO /L)
        
      }else{ //SENÃO, FAZ
       //SE VARIÁVEL FOR IGUAL A LOW (0), FAZ
        client.println("<p style='line-height:0'><font color='red'>DESLIGADO</font></p>"); //ESCREVE "DESLIGADO" NA PÁGINA
        client.println("<a href=\"/H\">ACENDER</a>"); //COMANDO PARA ACENDER O LED (PASSA O PARÂMETRO /H)
      }
      client.println("</body>"); 
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
            if(buf.endsWith("GET /H")){ //SE O PARÂMETRO DA REQUISIÇÃO VINDO POR GET FOR IGUAL A "H", FAZ 
                digitalWrite(LED_BUILTIN, HIGH); //ACENDE O LED
                statusLed = 1; //VARIÁVEL RECEBE VALOR 1(SIGNIFICA QUE O LED ESTÁ ACESO)               
                Serial.println("led on");
                break;
            }
            else if (buf.endsWith("GET /L")) { //SE O PARÂMETRO DA REQUISIÇÃO VINDO POR GET FOR IGUAL A "L", FAZ
                    digitalWrite(LED_BUILTIN, LOW); //APAGA O LED
                    statusLed = 0; //VARIÁVEL RECEBE VALOR 0(SIGNIFICA QUE O LED ESTÁ APAGADO)
                    Serial.println("led off");
                    break;
            } 
            else if(buf.endsWith("\r\n\r\n")) {
              
                sendHttpResponse(client);
              Serial.println("hello site");
              break;
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
