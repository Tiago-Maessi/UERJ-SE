#define PIN_LED_IN 13
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
