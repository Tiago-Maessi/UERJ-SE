Aluno: Tiago Maessi Santos Junior 
Disciplina: Software Embarcado
Professor: Francisco Sant’Anna

Projeto proposto: Ar-condicionado Controlado por Arduino Via Bluetooth, Via Infravermelho e com Medição de Temperatura

Material que será utilizado:

- Arduino Uno;
- Sensor LM-35;
- Sensor IRM-3638 (Leitor Infravermelho);
- LED IR (Emissor Infravermelho);
- Resistor de 150 Ω;
- Fios
- Módulo Bluetooth / Módulo ESP01 (Wi-Fi) (em avaliação);

A ideia deste projeto é efetuar um controle de temperatura e acionamento do ar-condicionado remotamente. A comunicação e controle do Arduino, será feita via rede sem fio utilizando tecnologias como Bluetooth ou Wi-Fi (ainda em avaliação) através de um celular. O acionamento remoto permite gerar maior flexibilidade e conforto ao usuário que poderá efetuar tal acionamento quando estiver em deslocamento para sua residência, por exemplo.  Em sequência segue descrição dos componentes a serem utilizados, suas funcionalidades e aplicabilidades dentro do projeto:

O Sensor de Temperatura LM35 é um sensor de precisão, que apresenta uma saída de tensão linear relativa à temperatura em que ele se encontrar no momento em que for alimentado por uma tensão de 4-20Vdc e GND, tendo em sua saída um sinal de 10mV para cada Grau Celsius de temperatura, sendo assim, apresenta uma boa vantagem com relação aos demais sensores de temperatura calibrados em “KELVIN”, não necessitando nenhuma subtração de variáveis para que se obtenha uma escala de temperatura em Graus Celsius.
O Sensor IRM-3638 é um sensor receptor Infravermelho, que será utilizado para leitura de maneira a clonar o sinal do botão de liga / desliga de um controle de ar-condicionado. 

O LED IR é um emissor infravermelho que será utilizado o acionamento do ar-condicionado controlado pelo Arduino.

A comunicação com o Arduino será feita através do Módulo Bluetooth ou módulo Wifi ESP-8266. Este tópico está em estudo e avaliação. Caso o controle seja feito por Bluetooth, pode-se utilizar softwares disponíveis na Play Store para Android de controle e acionamento para Arduino. Se a opção for o módulo Wi-Fi ESP-8266, pode-se criar uma página Web para controle do acionamento do Arduino.
