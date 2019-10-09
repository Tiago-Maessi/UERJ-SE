
#define LED_SAIDA 10 // LED PISCA
#define BOT_ACL 7 // BOTAO ACELERA LED
#define BOT_DCL 8 // BOTAO DESACELERA LED
byte valor = 0;  // CONVERTE VALOR PARA BYTE
int tempo_inicio=0;
int tempo_final;
int intervalo=1000;
int tempo; 
int bot_acl=0;
int bot_dcl=0; 
boolean liga_desl=true;

void setup (){
  pinMode(LED_SAIDA, OUTPUT); 
  pinMode(BOT_ACL, INPUT);
  pinMode(BOT_DCL, INPUT);
}

void frequencia(){
  if(valor==1){
    intervalo+=250;
  }
  else if((valor==2)&&(intervalo>200)){
    intervalo-=250;
  }
  else if(((valor==3)&&((millis()-tempo)<500))){
    digitalWrite(LED_SAIDA,LOW);
  }
}

void pisca(){
  tempo=millis();
  if(liga_desl==true){
    if((tempo-tempo_inicio)>=intervalo){
      digitalWrite(LED_SAIDA, HIGH); tempo_inicio=tempo; liga_desl=false;
    }
  }
    else{
      if((tempo-tempo_inicio)>=intervalo){
        tempo_inicio=tempo; digitalWrite(LED_SAIDA, LOW); liga_desl=true;
      }
    }
}



void loop(){
  pisca();
  if((digitalRead(BOT_DCL)==0) && (digitalRead(BOT_ACL)==0)){
    valor=3;
    frequencia();
    valor=0;
    while(1);
  }
  if(bot_acl){
    if(digitalRead(BOT_ACL)){
      bot_acl=0;
    }
  }
  else if(digitalRead(BOT_ACL)==LOW){
    bot_acl=1;
    valor=1;
    frequencia();
  }

   if(bot_dcl){
    if(digitalRead(BOT_DCL)){
      bot_dcl=0;
    }
  }
  else if(digitalRead(BOT_DCL)==LOW){
    bot_dcl=1;
    valor=2;
    frequencia();
  }
    
}  










  /* digitalWrite(LED_PIN_SAIDA,HIGH);
  delay(1000);
  digitalWrite(LED_PIN_SAIDA,LOW);
  delay(1000);


  
  int but = digitalRead (BOT_ACL);
  digitalWrite(LED_PIN_SAIDA, but);
}


/*#define PIN_LED_IN 13
#define PIN_LED_OUT 11
#define PIN_BUT_AC 2
#define PIN_BUT_DC 4

int but_ac = 0;// diz o estado e quando foi precionado
int but_dc = 0;// diz o estado e quando foi precionado

int Delay = 250;
int inicio_pis = 0;
int intervalo = 1000;
int fim_pis = 0;
int led = HIGH;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED_IN, OUTPUT);
  pinMode(PIN_LED_OUT, OUTPUT);
  pinMode(PIN_BUT_AC, INPUT);
  pinMode(PIN_BUT_DC, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  fim_pis = millis();
  if(  (fim_pis - inicio_pis > intervalo) ) { 
    led = !led;
    inicio_pis = millis();
    digitalWrite(PIN_LED_OUT, led); //led da protoboard
  }

  if ( (but_ac) && (but_dc) && (millis() - but_ac <500) && (millis() - but_dc <500) ) { // testa se os butoes foram apertados
    digitalWrite(PIN_LED_OUT, LOW);                                                     // depois quando foram 
    while(1);
  }
  else {
    if( but_ac ) {// primeir ve se o botao ja foi precionado antes
      if(digitalRead(PIN_BUT_AC)) {// depois ve se ele continua precionado
        but_ac = 0;// se nao estiver, muda o estado para nao precionada
        digitalWrite(PIN_LED_IN, LOW); //led da placa, ignore nao influencia
      }
    }
    else if(!digitalRead(PIN_BUT_AC)) {//caso o botao nao tenha sido apertado antes, mas foi agora
      but_ac = millis();// muda o estado para precionado e quando foi
      intervalo = intervalo - Delay;// altera o intervalo
      digitalWrite(PIN_LED_IN, HIGH); //led da placa, ignore nao influencia
    }
    
    if( but_dc ) {// primeir ve se o botao ja foi precionado antes
      if(digitalRead(PIN_BUT_DC)) {// depois ve se ele continua precionado
        but_dc = 0;// se nao estiver, muda o estado para nao precionada
        digitalWrite(PIN_LED_IN, LOW); //led da placa, ignore nao influencia
      }
    }
    else if(!digitalRead(PIN_BUT_DC)) {//caso o botao nao tenha sido apertado antes, mas foi agora
      but_dc = millis();// muda o estado para precionado e quando foi
      intervalo = intervalo + Delay;// altera o intervalo
      digitalWrite(PIN_LED_IN, HIGH); //led da placa, ignore nao influencia
    }
  }
    
}
*/
