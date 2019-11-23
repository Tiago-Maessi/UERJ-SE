#include "WiFiEsp.h" //INCLUSÃO DA BIBLIOTECA
#include "SoftwareSerial.h"//INCLUSÃO DA BIBLIOTECA

#include <IRremote.h>
IRsend irsend;

#define SAMPLES 3 //Número de amostras de temperaturas
#define sensortemp 1 //Pino analógico em que estará conectado o sensor LM35 (A1 no arduino UNO)

int enviou = 0;


//Padrao sinal RAW Ligar Ar
unsigned int S_pwr[383] = {1276, 440, 1248, 444, 400, 1264, 1272, 444, 1248, 444, 396, 1268, 424, 1264, 428, 1264, 424, 1268, 424, 1264, 428, 1264, 1272, 7180, 1272, 444, 1248, 444, 396, 1268, 1272, 444, 1244, 444, 400, 1268, 424, 1264, 424, 1264, 428, 1264, 424, 1268, 424, 1264, 1272, 7180, 1276, 444, 1244, 444, 400, 1264, 1272, 444, 1248, 444, 396, 1268, 424, 1264, 428, 1264, 424, 1268, 424, 1264, 424, 1268, 1272, 7180, 1272, 444, 1244, 424, 420, 1268, 1268, 448, 1244, 420, 424, 1264, 424, 1268, 424, 1264, 424, 1268, 424, 1268, 424, 1264, 1272, 7180, 1272, 424, 1268, 444, 376, 1288, 1252, 444, 1244, 444, 400, 1288, 400, 1292, 400, 1288, 404, 1288, 400, 1292, 400, 1288, 1252, 7200, 1280, 412, 1276, 416, 428, 1260, 1276, 416, 1276, 412, 428, 1264, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 432, 1256, 1280, 7176, 1276, 416, 1276, 412, 428, 1260, 1280, 412, 1276, 416, 428, 1260, 432, 1256, 432, 1260, 432, 1256, 432, 1260, 432, 1260, 1276, 7176, 1276, 416, 1276, 412, 428, 1260, 1280, 412, 1276, 416, 428, 1260, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 432, 1260, 1276, 7176, 1276, 416, 1276, 412, 428, 1260, 1280, 412, 1276, 416, 428, 1260, 428, 1264, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 1276, 7176, 1276, 416, 1276, 412, 428, 1264, 1276, 416, 1272, 416, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 1276, 7176, 1276, 416, 1276, 416, 424, 1264, 1272, 416, 1276, 416, 424, 1264, 428, 1264, 424, 1264, 428, 1264, 400, 1288, 404, 1288, 1248, 7204, 1248, 468, 1224, 440, 400, 1288, 1252, 440, 1248, 444, 400, 1288, 424, 1268, 424, 1264, 424, 1268, 424, 1264, 424, 1268, 1268, 7184, 1268, 448, 1244, 444, 400, 1264, 1272, 444, 1248, 420, 420, 1268, 424, 1268, 420, 1268, 424, 1268, 420, 1268, 424, 1268, 1268, 7184, 1268, 424, 1268, 444, 396, 1268, 1272, 444, 1244, 448, 396, 1268, 424, 1264, 424, 1268, 424, 1264, 428, 1264, 424, 1268, 1268, 7180, 1276, 444, 1244, 444, 400, 1264, 1272, 444, 1244, 448, 396, 1268, 424, 1264, 428, 1264, 424, 1264, 424, 1268, 424, 1264, 1272, 7180, 1272, 448, 1244, 444, 396, 1268, 1272, 444, 1244, 444, 400, 1268, 420, 1268, 424, 1264, 428, 1264, 424, 1268, 424, 1264, 1272};

//const PROGMEM unsigned int irSignal [] = {1276, 440, 1248, 444, 400, 1264, 1272, 444, 1248, 444, 396, 1268, 424, 1264, 428, 1264, 424, 1268, 424, 1264, 428, 1264, 1272, 7180, 1272, 444, 1248, 444, 396, 1268, 1272, 444, 1244, 444, 400, 1268, 424, 1264, 424, 1264, 428, 1264, 424, 1268, 424, 1264, 1272, 7180, 1276, 444, 1244, 444, 400, 1264, 1272, 444, 1248, 444, 396, 1268, 424, 1264, 428, 1264, 424, 1268, 424, 1264, 424, 1268, 1272, 7180, 1272, 444, 1244, 424, 420, 1268, 1268, 448, 1244, 420, 424, 1264, 424, 1268, 424, 1264, 424, 1268, 424, 1268, 424, 1264, 1272, 7180, 1272, 424, 1268, 444, 376, 1288, 1252, 444, 1244, 444, 400, 1288, 400, 1292, 400, 1288, 404, 1288, 400, 1292, 400, 1288, 1252, 7200, 1280, 412, 1276, 416, 428, 1260, 1276, 416, 1276, 412, 428, 1264, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 432, 1256, 1280, 7176, 1276, 416, 1276, 412, 428, 1260, 1280, 412, 1276, 416, 428, 1260, 432, 1256, 432, 1260, 432, 1256, 432, 1260, 432, 1260, 1276, 7176, 1276, 416, 1276, 412, 428, 1260, 1280, 412, 1276, 416, 428, 1260, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 432, 1260, 1276, 7176, 1276, 416, 1276, 412, 428, 1260, 1280, 412, 1276, 416, 428, 1260, 428, 1264, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 1276, 7176, 1276, 416, 1276, 412, 428, 1264, 1276, 416, 1272, 416, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 1276, 7176, 1276, 416, 1276, 416, 424, 1264, 1272, 416, 1276, 416, 424, 1264, 428, 1264, 424, 1264, 428, 1264, 400, 1288, 404, 1288, 1248, 7204, 1248, 468, 1224, 440, 400, 1288, 1252, 440, 1248, 444, 400, 1288, 424, 1268, 424, 1264, 424, 1268, 424, 1264, 424, 1268, 1268, 7184, 1268, 448, 1244, 444, 400, 1264, 1272, 444, 1248, 420, 420, 1268, 424, 1268, 420, 1268, 424, 1268, 420, 1268, 424, 1268, 1268, 7184, 1268, 424, 1268, 444, 396, 1268, 1272, 444, 1244, 448, 396, 1268, 424, 1264, 424, 1268, 424, 1264, 428, 1264, 424, 1268, 1268, 7180, 1276, 444, 1244, 444, 400, 1264, 1272, 444, 1244, 448, 396, 1268, 424, 1264, 428, 1264, 424, 1264, 424, 1268, 424, 1264, 1272, 7180, 1272, 448, 1244, 444, 396, 1268, 1272, 444, 1244, 444, 400, 1268, 420, 1268, 424, 1264, 428, 1264, 424, 1268, 424, 1264, 1272};
//int khz = 38;


//int tempvector[SAMPLES]; //Vetor que armazenará as temperaturas
//double tempSensor = 0.0; //Variável auxiliar
//int  valAnalog = 0; // Variável para aramazenar a leitura do sensor LM35



  void ligarAr(){
    Serial.println("Ligando...");
    irsend.sendRaw(S_pwr, 383, 38);
    Serial.println("Executando a 38 Hz");
    delay (20000);
}
 
SoftwareSerial Serial1(6, 7); //PINOS QUE EMULAM A SERIAL, ONDE O PINO 6 É O RX E O PINO 7 É O TX
 
char ssid[] = "MAESSI_2.4Ghz"; //VARIÁVEL QUE ARMAZENA O NOME DA REDE SEM FIO
char pass[] = "Fla25ago@";//VARIÁVEL QUE ARMAZENA A SENHA DA REDE SEM FIO
 
int status = WL_IDLE_STATUS; //STATUS TEMPORÁRIO ATRIBUÍDO QUANDO O WIFI É INICIALIZADO E PERMANECE ATIVO
//ATÉ QUE O NÚMERO DE TENTATIVAS EXPIRE (RESULTANDO EM WL_NO_SHIELD) OU QUE UMA CONEXÃO SEJA ESTABELECIDA
//(RESULTANDO EM WL_CONNECTED)
 
WiFiEspServer server(80); //CONEXÃO REALIZADA NA PORTA 80
 
RingBuffer buf(8); //BUFFER PARA AUMENTAR A VELOCIDADE E REDUZIR A ALOCAÇÃO DE MEMÓRIA
 
int statusLed = LOW; //VARIÁVEL QUE ARMAZENA O ESTADO ATUAL DO LED (LIGADO / DESLIGADO)
 
void setup(){
  pinMode(LED_BUILTIN, OUTPUT); //DEFINE O PINO COMO SAÍDA (LED_BUILTIN = PINO 13)
  digitalWrite(LED_BUILTIN, LOW); //PINO 13 INICIA DESLIGADO
  Serial.begin(9600); //INICIALIZA A SERIAL
  Serial1.begin(9600); //INICIALIZA A SERIAL PARA O ESP8266
  //for (int i= 0 ; i< 383; i++) {
     //   int v= pgm_read_word_near(irSignal + i);}


  
  WiFi.init(&Serial1); //INICIALIZA A COMUNICAÇÃO SERIAL COM O ESP8266
  WiFi.config(IPAddress(192,168,15,41)); //COLOQUE UMA FAIXA DE IP DISPONÍVEL DO SEU ROTEADOR
 
  //INÍCIO - VERIFICA SE O ESP8266 ESTÁ CONECTADO AO ARDUINO, CONECTA A REDE SEM FIO E INICIA O WEBSERVER
  if(WiFi.status() == WL_NO_SHIELD){
    while (true);
  }
  while(status != WL_CONNECTED){
    status = WiFi.begin(ssid, pass);
  }
  server.begin();
  //FIM - VERIFICA SE O ESP8266 ESTÁ CONECTADO AO ARDUINO, CONECTA A REDE SEM FIO E INICIA O WEBSERVER
}
 
void loop(){

  WiFiEspClient client = server.available(); //ATENDE AS SOLICITAÇÕES DO CLIENTE
  
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
           //unsigned int irSignal [] = {1276, 440, 1248, 444, 400, 1264, 1272, 444, 1248, 444, 396, 1268, 424, 1264, 428, 1264, 424, 1268, 424, 1264, 428, 1264, 1272, 7180, 1272, 444, 1248, 444, 396, 1268, 1272, 444, 1244, 444, 400, 1268, 424, 1264, 424, 1264, 428, 1264, 424, 1268, 424, 1264, 1272, 7180, 1276, 444, 1244, 444, 400, 1264, 1272, 444, 1248, 444, 396, 1268, 424, 1264, 428, 1264, 424, 1268, 424, 1264, 424, 1268, 1272, 7180, 1272, 444, 1244, 424, 420, 1268, 1268, 448, 1244, 420, 424, 1264, 424, 1268, 424, 1264, 424, 1268, 424, 1268, 424, 1264, 1272, 7180, 1272, 424, 1268, 444, 376, 1288, 1252, 444, 1244, 444, 400, 1288, 400, 1292, 400, 1288, 404, 1288, 400, 1292, 400, 1288, 1252, 7200, 1280, 412, 1276, 416, 428, 1260, 1276, 416, 1276, 412, 428, 1264, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 432, 1256, 1280, 7176, 1276, 416, 1276, 412, 428, 1260, 1280, 412, 1276, 416, 428, 1260, 432, 1256, 432, 1260, 432, 1256, 432, 1260, 432, 1260, 1276, 7176, 1276, 416, 1276, 412, 428, 1260, 1280, 412, 1276, 416, 428, 1260, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 432, 1260, 1276, 7176, 1276, 416, 1276, 412, 428, 1260, 1280, 412, 1276, 416, 428, 1260, 428, 1264, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 1276, 7176, 1276, 416, 1276, 412, 428, 1264, 1276, 416, 1272, 416, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 1276, 7176, 1276, 416, 1276, 416, 424, 1264, 1272, 416, 1276, 416, 424, 1264, 428, 1264, 424, 1264, 428, 1264, 400, 1288, 404, 1288, 1248, 7204, 1248, 468, 1224, 440, 400, 1288, 1252, 440, 1248, 444, 400, 1288, 424, 1268, 424, 1264, 424, 1268, 424, 1264, 424, 1268, 1268, 7184, 1268, 448, 1244, 444, 400, 1264, 1272, 444, 1248, 420, 420, 1268, 424, 1268, 420, 1268, 424, 1268, 420, 1268, 424, 1268, 1268, 7184, 1268, 424, 1268, 444, 396, 1268, 1272, 444, 1244, 448, 396, 1268, 424, 1264, 424, 1268, 424, 1264, 428, 1264, 424, 1268, 1268, 7180, 1276, 444, 1244, 444, 400, 1264, 1272, 444, 1244, 448, 396, 1268, 424, 1264, 428, 1264, 424, 1264, 424, 1268, 424, 1264, 1272, 7180, 1272, 448, 1244, 444, 396, 1268, 1272, 444, 1244, 444, 400, 1268, 420, 1268, 424, 1264, 428, 1264, 424, 1268, 424, 1264, 1272};
           //irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]),khz);
           digitalWrite(LED_BUILTIN, HIGH); //ACENDE O LED
           ligarAr();
           enviou = 1;
           //int khz = 38;
           //static unsigned int irSignal [] = {1276, 440, 1248, 444, 400, 1264, 1272, 444, 1248, 444, 396, 1268, 424, 1264, 428, 1264, 424, 1268, 424, 1264, 428, 1264, 1272, 7180, 1272, 444, 1248, 444, 396, 1268, 1272, 444, 1244, 444, 400, 1268, 424, 1264, 424, 1264, 428, 1264, 424, 1268, 424, 1264, 1272, 7180, 1276, 444, 1244, 444, 400, 1264, 1272, 444, 1248, 444, 396, 1268, 424, 1264, 428, 1264, 424, 1268, 424, 1264, 424, 1268, 1272, 7180, 1272, 444, 1244, 424, 420, 1268, 1268, 448, 1244, 420, 424, 1264, 424, 1268, 424, 1264, 424, 1268, 424, 1268, 424, 1264, 1272, 7180, 1272, 424, 1268, 444, 376, 1288, 1252, 444, 1244, 444, 400, 1288, 400, 1292, 400, 1288, 404, 1288, 400, 1292, 400, 1288, 1252, 7200, 1280, 412, 1276, 416, 428, 1260, 1276, 416, 1276, 412, 428, 1264, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 432, 1256, 1280, 7176, 1276, 416, 1276, 412, 428, 1260, 1280, 412, 1276, 416, 428, 1260, 432, 1256, 432, 1260, 432, 1256, 432, 1260, 432, 1260, 1276, 7176, 1276, 416, 1276, 412, 428, 1260, 1280, 412, 1276, 416, 428, 1260, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 432, 1260, 1276, 7176, 1276, 416, 1276, 412, 428, 1260, 1280, 412, 1276, 416, 428, 1260, 428, 1264, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 1276, 7176, 1276, 416, 1276, 412, 428, 1264, 1276, 416, 1272, 416, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 428, 1260, 432, 1260, 1276, 7176, 1276, 416, 1276, 416, 424, 1264, 1272, 416, 1276, 416, 424, 1264, 428, 1264, 424, 1264, 428, 1264, 400, 1288, 404, 1288, 1248, 7204, 1248, 468, 1224, 440, 400, 1288, 1252, 440, 1248, 444, 400, 1288, 424, 1268, 424, 1264, 424, 1268, 424, 1264, 424, 1268, 1268, 7184, 1268, 448, 1244, 444, 400, 1264, 1272, 444, 1248, 420, 420, 1268, 424, 1268, 420, 1268, 424, 1268, 420, 1268, 424, 1268, 1268, 7184, 1268, 424, 1268, 444, 396, 1268, 1272, 444, 1244, 448, 396, 1268, 424, 1264, 424, 1268, 424, 1264, 428, 1264, 424, 1268, 1268, 7180, 1276, 444, 1244, 444, 400, 1264, 1272, 444, 1244, 448, 396, 1268, 424, 1264, 428, 1264, 424, 1264, 424, 1268, 424, 1264, 1272, 7180, 1272, 448, 1244, 444, 396, 1268, 1272, 444, 1244, 444, 400, 1268, 420, 1268, 424, 1264, 428, 1264, 424, 1268, 424, 1264, 1272};
           //irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]),khz);
           //Serial.println(v);
          // delay (5000);
            statusLed = 1; //VARIÁVEL RECEBE VALOR 1(SIGNIFICA QUE O LED ESTÁ ACESO)

        
            
        }


        
        else{ //SENÃO, FAZ
          if (buf.endsWith("GET /L")) { //SE O PARÂMETRO DA REQUISIÇÃO VINDO POR GET FOR IGUAL A "L", FAZ
                  digitalWrite(LED_BUILTIN, LOW); //APAGA O LED
                  statusLed = 0; //VARIÁVEL RECEBE VALOR 0(SIGNIFICA QUE O LED ESTÁ APAGADO)
          }

        
       // irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]),khz);
        //Serial.println(v);  }


        
        }


        
        
         
      }
    }
    client.stop(); //FINALIZA A REQUISIÇÃO HTTP E DESCONECTA O CLIENTE
  }

  
}


 
//MÉTODO DE RESPOSTA A REQUISIÇÃO HTTP DO CLIENTE
void sendHttpResponse(WiFiEspClient client){
  client.println("HTTP/1.1 200 OK"); //ESCREVE PARA O CLIENTE A VERSÃO DO HTTP
  client.println("Content-Type: text/html"); //ESCREVE PARA O CLIENTE O TIPO DE CONTEÚDO(texto/html)
  client.println("");
  client.println("<!DOCTYPE HTML>"); //INFORMA AO NAVEGADOR A ESPECIFICAÇÃO DO HTML
  client.println("<html>"); //ABRE A TAG "html"
  client.println("<head>"); //ABRE A TAG "head"
  //client.println("<link rel='icon' type='image/png' href='https://www.uerj.br/wp-content/uploads/2017/09/logo_uerj_cor.jpg'/>"); //DEFINIÇÃO DO ICONE DA PÁGINA
  //client.println("<link rel='stylesheet' type='text/css' href='https://www.uerj.br/wp-content/uploads/2017/09/logo_uerj_cor.jpg' />"); //REFERENCIA AO ARQUIVO CSS (FOLHAS DE ESTILO)
  client.println("<title>Projeto Final Tiago</title>"); //ESCREVE O TEXTO NA PÁGINA
  client.println("</head>"); //FECHA A TAG "head"
  
  //AS LINHAS ABAIXO CRIAM A PÁGINA HTML
  client.println("<body>"); //ABRE A TAG "body"
  //client.println("<img alt='uerj' src='https://www.uerj.br/wp-content/uploads/2017/09/logo_uerj_cor.jpg' height='200' width='300' />"); //LOGO DA MASTERWALKER SHOP
  //client.println("<p style='line-height:2'><font>Projeto Final Tiago</font></p>"); //ESCREVE O TEXTO NA PÁGINA
  client.println("<font>ESTADO ATUAL DO LED</font>"); //ESCREVE O TEXTO NA PÁGINA
  //client.println("<font face='arial' size='4' color='blue' >Temperatura via Web   " ); //Exibe texto com formatação 




  //  for(int j = 0; j < SAMPLES ; j++ ){
     //   valAnalog = analogRead(sensortemp); // Leitura do pino analógico correspondente ao sensor e armazena em valAnalog
     //   tempvector[j] = (5.0 * valAnalog * 100.0)/1024.0; //Armazena as temperaturas amostradas em um vetor tamanho SAMPLES
     //   tempSensor = tempSensor + tempvector[j]; // Soma as amostras de temperatura e armazena em tempSensor   
   // }
//    tempSensor = tempSensor/SAMPLES; // Calcula a média das amostras de temperatura e a armazena em tempSensor
    
  
    //client.print(tempSensor); //Exibe a temperatura  
    client.print("&deg;"); // Referência do caratere(graus º) na codificação Latin-1 (ISO-8859-1)
    client.println("C </h1><br>"); // Exibe o "C" e finaliza a tag H1

  
  
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
