#define LED_SAIDA 10 // LED PISCA
#define BOT_ACL 7 // BOTAO ACELERA LED
#define BOT_DCL 8 // BOTAO DESACELERA LED
byte valor = 0;  // CONVERTE VALOR PARA BYTE
int tempo_inicio=0; // VARIAVEL CONTROLE TEMPO INICIAL
int tempo_final; // VARIAVEL CONTROLE TEMPO FINAL
int intervalo=1000; // VARIAVEL INTERVALO PISCA LED
int Delay = 100; // VARIAVEL DELAY DE TEMPO / VELOC PISCA
int tempo; // VARIAVEL TEMPO
int bot_acl=0; // VARIAVEL ESTADO ACELERACAO
int bot_dcl=0; // VARIAVEL ESTADO DESACELERACAO
boolean liga_desl=true; // 
int led = LOW;

void setup (){  // FUNCAO SETUP DECLARANDO IN/OUT
  pinMode(LED_SAIDA, OUTPUT); 
  pinMode(BOT_ACL, INPUT);
  pinMode(BOT_DCL, INPUT);
}

void velocidade(){ // FUNCAO CONTROLE VELOCIDADE LED
  if(valor==1){
    intervalo+=Delay;
  }
  else if((valor==2)&&(intervalo>200)){
    intervalo-=Delay;
  }
  else if(((valor==3)&&((millis()-tempo)<500))){
    digitalWrite(LED_SAIDA,led);
  }
}
void loop(){   // FUNCAO LOOP DE ACORDO COM O ESTADO SELECIONADO 
  tempo = millis();
  if ((tempo-tempo_inicio)>=intervalo){
    led = !led;
    tempo_inicio = millis();
    tempo_inicio=tempo; digitalWrite(LED_SAIDA, led);
  }
  
  if((digitalRead(BOT_DCL)==0) && (digitalRead(BOT_ACL)==0)){
    valor=3;
    velocidade();
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
    velocidade();
  }
   if(bot_dcl){
    if(digitalRead(BOT_DCL)){
      bot_dcl=0;
    }
  }
  else if(digitalRead(BOT_DCL)==LOW){
    bot_dcl=1;
    valor=2;
    velocidade();
  }
}  
