#include <Wire.h> //INCLUSÃO DA BIBLIOTECA
#include "RTClib.h" //INCLUSÃO DA BIBLIOTECA
 
RTC_DS3231 rtc; //OBJETO DO TIPO RTC_DS3231

const int pinoSensor = 7; //PINO DIGITAL UTILIZADO PELO SENSOR
const int pinoRele = 8; //PINO DIGITAL UTILIZADO PELO MÓDULO RELÉ
const int pinoPOT = A0; //PINO ANALÓGICO UTILIZADO PELO POTENCIÔMETRO
const int pinoBuzzer = 9; //PINO DIGITAL UTILIZADO PELO BUZZER
int leituraA0 = 0; //VARIÁVEL QUE ARMAZENA O VALOR LIDO NO PINO ANALÓGICO
int status = 0; //VARIÁVEL QUE CONTROLA O STATUS DO MÓDULO RELÉ (LIGADO / DESLIGADO)

float volumeBuzzer = 0; //VARIÁVEL QUE ARMAZENA O VALOR DA LUMINOSIDADE QUE SERÁ APLICADA AO LED

//DECLARAÇÃO DOS DIAS DA SEMANA
char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado"};
 
void setup(){
  Serial.begin(9600); //INICIALIZA A SERIAL
  pinMode(pinoSensor, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoRele, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoPOT, INPUT); //DEFINE O PINO COMO ENTRADA
  digitalWrite(pinoRele, HIGH); //MÓDULO RELÉ INICIA DESLIGADO
  pinMode(pinoBuzzer, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoBuzzer, LOW);
  
  
  
  if(! rtc.begin()) { // SE O RTC NÃO FOR INICIALIZADO, FAZ
    Serial.println("DS3231 não encontrado"); //IMPRIME O TEXTO NO MONITOR SERIAL
    while(1); //SEMPRE ENTRE NO LOOP
  }
  if(rtc.lostPower()){ //SE RTC FOI LIGADO PELA PRIMEIRA VEZ / FICOU SEM ENERGIA / ESGOTOU A BATERIA, FAZ
    Serial.println("DS3231 OK!"); //IMPRIME O TEXTO NO MONITOR SERIAL
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //CAPTURA A DATA E HORA EM QUE O SKETCH É COMPILADO
    rtc.adjust(DateTime(2019, 8, 28, 23, 02, 45)); //(ANO), (MÊS), (DIA), (HORA), (MINUTOS), (SEGUNDOS)
  }
  //delay(100); //INTERVALO DE 100 MILISSEGUNDOS
}
void loop () {

      leituraA0 = analogRead(pinoPOT);//LÊ O VALOR NO PINO ANALÓGICO (VALOR LIDO EM BITS QUE VAI DE 0 A 1023)
      volumeBuzzer = map(leituraA0, 0, 1023 , 0, 255); //EXECUTA A FUNÇÃO "map" DE ACORDO COM OS PARÂMETROS PASSADOS
    // volumeBuzzer = map(leituraA0, 1023, 0, 0, 255); //EXECUTA A FUNÇÃO "map" DE ACORDO COM OS PARÂMETROS PASSADOS
      analogWrite(pinoBuzzer, volumeBuzzer); //APLICA AO BUZZER O VALOR DE CONTROLE (PWM) GERADO PELA FUNÇÃO "map"
    // Serial.println(luminosidadeLED); //IMPRIME O TEXTO NO MONITOR SERIAL
     //  Serial.println(leituraA0); //IMPRIME O TEXTO NO MONITOR SERIAL
     
    if(digitalRead(pinoSensor) == LOW){ //SE A LEITURA DO PINO FOR IGUAL A LOW, FAZ
      Serial.println("Batida detectada"); //IMPRIME O TEXTO NA SERIAL
    if (status == 0){ //SE VARIÁVEL FOR IGUAL A 0, FAZ
      digitalWrite(pinoRele, LOW); //LIGA O RELÉ
      status = 1; //VARIÁVEL RECEBE O VALOR 1
      Serial.println("RELE LIGADO"); //IMPRIME O TEXTO NO MONITOR SERIAL
      tone(pinoBuzzer, 100);
      Serial.println("ALARME ATIVADO"); //IMPRIME O TEXTO NO MONITOR SERIAL
      
    
        
    DateTime now = rtc.now(); //CHAMADA DE FUNÇÃO
    Serial.print("Data: "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(now.day(), DEC); //IMPRIME NO MONITOR SERIAL O DIA
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.month(), DEC); //IMPRIME NO MONITOR SERIAL O MÊS
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.year(), DEC); //IMPRIME NO MONITOR SERIAL O ANO
    Serial.print(" / Dia: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]); //IMPRIME NO MONITOR SERIAL O DIA
    Serial.print(" / Horas: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(now.hour(), DEC); //IMPRIME NO MONITOR SERIAL A HORA
    Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.minute(), DEC); //IMPRIME NO MONITOR SERIAL OS MINUTOS
    Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.second(), DEC); //IMPRIME NO MONITOR SERIAL OS SEGUNDOS
    Serial.println(); //QUEBRA DE LINHA NA SERIAL
    delay(1000); //INTERVALO DE 1 SEGUNDO
    }

       
    else{ //SENÃO, FAZ
     // digitalWrite(pinoRele, HIGH); //DESLIGA O RELÉ
     // status = 0; //VARIÁVEL RECEBE O VALOR 0
     // Serial.println("RELE DESLIGADO"); //IMPRIME O TEXTO NO MONITOR SERIAL
    
    DateTime now = rtc.now(); //CHAMADA DE FUNÇÃO
    Serial.print("Data: "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(now.day(), DEC); //IMPRIME NO MONITOR SERIAL O DIA
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.month(), DEC); //IMPRIME NO MONITOR SERIAL O MÊS
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.year(), DEC); //IMPRIME NO MONITOR SERIAL O ANO
    Serial.print(" / Dia: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]); //IMPRIME NO MONITOR SERIAL O DIA
    Serial.print(" / Horas: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(now.hour(), DEC); //IMPRIME NO MONITOR SERIAL A HORA
    Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.minute(), DEC); //IMPRIME NO MONITOR SERIAL OS MINUTOS
    Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.second(), DEC); //IMPRIME NO MONITOR SERIAL OS SEGUNDOS
    Serial.println(); //QUEBRA DE LINHA NA SERIAL
    delay(1000); //INTERVALO DE 1 SEGUNDO

    
     
    }    }}
