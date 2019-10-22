#include <Wire.h> //INCLUSÃO DA BIBLIOTECA
#include "RTClib.h" //INCLUSÃO DA BIBLIOTECA
 
RTC_DS3231 rtc; //OBJETO DO TIPO RTC_DS3231

const int pinoSensor = 7; //PINO DIGITAL UTILIZADO PELO SENSOR
const int pinoRele = 9; //PINO DIGITAL UTILIZADO PELO MÓDULO RELÉ
int status = 0; //VARIÁVEL QUE CONTROLA O STATUS DO MÓDULO RELÉ (LIGADO / DESLIGADO)
const int pinoBuzzer = 8; //PINO DIGITAL UTILIZADO PELO BUZZER

//float volumeBuzzer = 0; //VARIÁVEL QUE ARMAZENA O VALOR DA LUMINOSIDADE QUE SERÁ APLICADA AO LED
 
//DECLARAÇÃO DOS DIAS DA SEMANA
char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado"};
 
void setup(){
  Serial.begin(9600); //INICIALIZA A SERIAL
  pinMode(pinoSensor, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoRele, OUTPUT); //DEFINE O PINO COMO SAÍDA
  digitalWrite(pinoRele, HIGH); //MÓDULO RELÉ INICIA DESLIGADO
  pinMode(pinoBuzzer, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoBuzzer, LOW);
  
// Configuração do TIMER1
  TCCR1A = 0;                //confira timer para operação normal
  TCCR1B = 0;                //limpa registrador
  TCNT1  = 0;                //zera temporizado
 
  OCR1A = 0xB71B;            // carrega registrador de comparação: 16MHz/1024/1Hz = 15625 = 0X3D09
  TCCR1B |= (1 << WGM12)|(1<<CS10)|(1 << CS12);   // modo CTC, prescaler de 1024: CS12 = 1 e CS10 = 1  
  TIMSK1 |= (1 << OCIE1A);  // habilita interrupção por igualdade de comparação


  
  if(! rtc.begin()) { // SE O RTC NÃO FOR INICIALIZADO, FAZ
    Serial.println("DS3231 não encontrado"); //IMPRIME O TEXTO NO MONITOR SERIAL
    while(1); //SEMPRE ENTRE NO LOOP
  }
  if(rtc.lostPower()){ //SE RTC FOI LIGADO PELA PRIMEIRA VEZ / FICOU SEM ENERGIA / ESGOTOU A BATERIA, FAZ
    Serial.println("DS3231 OK!"); //IMPRIME O TEXTO NO MONITOR SERIAL
    //REMOVA O COMENTÁRIO DE UMA DAS LINHAS ABAIXO PARA INSERIR AS INFORMAÇÕES ATUALIZADAS EM SEU RTC
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //CAPTURA A DATA E HORA EM QUE O SKETCH É COMPILADO
    rtc.adjust(DateTime(2019, 8, 28, 23, 02, 45)); //(ANO), (MÊS), (DIA), (HORA), (MINUTOS), (SEGUNDOS)
  }
 // delay(100); //INTERVALO DE 100 MILISSEGUNDOS


  
}

  

 
void loop () {
    
    if(digitalRead(pinoSensor) == LOW){ //SE A LEITURA DO PINO FOR IGUAL A LOW, FAZ
      Serial.println("Batida detectada"); //IMPRIME O TEXTO NA SERIAL
    if (status == 0){ //SE VARIÁVEL FOR IGUAL A 0, FAZ
      digitalWrite(pinoRele, LOW); //LIGA O RELÉ
      status = 1; //VARIÁVEL RECEBE O VALOR 1
      Serial.println("RELE LIGADO"); //IMPRIME O TEXTO NO MONITOR SERIAL
      //tone(pinoBuzzer, 100);
      //Serial.println("ALARME ATIVADO"); //IMPRIME O TEXTO NO MONITOR SERIAL

      
    
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

    
   // else {//SENÃO, FAZ
    
   // ISR(TIMER1_COMPA_vect)          // interrupção por igualdade de comparação no TIMER1

    //TCNT1 = 0xC2F7;                                 // Renicia TIMER
   // digitalWrite(pinoRele, digitalRead(pinoRele) ^ 1);   //inverte estado do BUZZER
   // Serial.println(pinoRele);

    
/*
    
      // digitalWrite(pinoRele, HIGH); DESLIGA O RELÉ
      // status = 0; // VARIÁVEL RECEBE O VALOR 0
      // Serial.println("RELÉ DESLIGADO"); // IMPRIME O TEXTO NO MONITOR SERIAL
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
  */  
    //}
    }}

    
      ISR(TIMER1_COMPA_vect)          // interrupção por igualdade de comparação no TIMER1
{
  //TCNT1 = 0xC2F7;                                 // Renicia TIMER
  digitalWrite(pinoRele, digitalRead(pinoRele) ^ 1);   //inverte estado do BUZZER
  Serial.println(pinoRele);
}
