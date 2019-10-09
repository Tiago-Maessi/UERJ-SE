#define LED_SAIDA 10 // LED PISCA
#define BOT_ACL 7 // BOTAO ACELERA LED
#define BOT_DCL 8 // BOTAO DESACELERA LED
byte valor = 0;  // CONVERTE VALOR PARA BYTE
int tempo_inicio=0; // VARIAVEL CONTROLE TEMPO INICIAL
int tempo_final; // VARIAVEL CONTROLE TEMPO FINAL
int intervalo=1000; // VARIAVEL INTERVALO PISCA LED
int Delay = 250;
int tempo; // VARIAVEL TEMPO
int bot_acl=0; // VARIAVEL ESTADO ACELERACAO
int bot_dcl=0; // VARIAVEL ESTADO DESACELERACAO
boolean liga_desl=true; // 
int led = HIGH;

void setup (){
  pinMode(LED_SAIDA, OUTPUT); 
  pinMode(BOT_ACL, INPUT);
  pinMode(BOT_DCL, INPUT);
}

void repeticao(){
  if(valor==1){
    intervalo+=Delay;
  }
  else if((valor==2)&&(intervalo>200)){
    intervalo-=Delay;
  }
  else if(((valor==3)&&((millis()-tempo)<500))){
    digitalWrite(LED_SAIDA,LOW);
  }
}

/*void pisca(){
/*  tempo=millis();
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
*/

void pisca () {
  tempo = millis();
  if ((tempo-tempo_inicio)>=intervalo){
    led = !led;
    tempo_inicio = millis ();
    tempo_inicio=tempo; digitalWrite(LED_SAIDA, led);
  }}

void loop(){
  pisca();
  if((digitalRead(BOT_DCL)==0) && (digitalRead(BOT_ACL)==0)){
    valor=3;
    repeticao();
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
    repeticao();
  }

   if(bot_dcl){
    if(digitalRead(BOT_DCL)){
      bot_dcl=0;
    }
  }
  else if(digitalRead(BOT_DCL)==LOW){
    bot_dcl=1;
    valor=2;
    repeticao();
  }
    
}  
