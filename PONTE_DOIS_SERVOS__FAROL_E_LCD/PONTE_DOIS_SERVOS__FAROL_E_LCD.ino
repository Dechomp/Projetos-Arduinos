/*Incluir a biblioteca Servo.h*/
# include <Servo.h>
#include <LiquidCrystal_I2C.h>

/*Definir nomes para as portas digitais para envio de comandos.*/

//Motores
#define pino_Servo1 9
#define pino_Servo2 11

//POTENCIOMETRO
#define pino_Potenciometro A0

//LEDs
#define farolDireitoVermelho 2
#define farolDireitoVerde 4 
#define farolDireitoAmarelo 3

#define farolEsquerdoVermelho 5
#define farolEsquerdoVerde 7
#define farolEsquerdoAmarelo 6


//LCD
#define endereco 0x27
#define linhas 2
#define colunas 16

//Biblioteca LCD
LiquidCrystal_I2C lcd(endereco, colunas, linhas);

/* Instanciar duas variáveis com as propriedades
da biblioteca para movimentar os servos motores.*/

Servo motor_ponte_direita, motor_ponte_esquerda;

void setup()
{
  //Porta dos motores (9 e 11)
  motor_ponte_direita.attach(pino_Servo1);
  motor_ponte_esquerda.attach(pino_Servo2);


  //Inicia o Serial
  Serial.begin(9600);
  Serial.println("Ponte Iniciada");
  

  //Porta dos leds (2 a 7)
  pinMode(farolDireitoVermelho, OUTPUT);
  pinMode(farolDireitoVerde, OUTPUT);
  pinMode(farolDireitoAmarelo, OUTPUT);

  pinMode(farolEsquerdoVermelho, OUTPUT);
  pinMode(farolEsquerdoVerde, OUTPUT);
  pinMode(farolEsquerdoAmarelo, OUTPUT);

  

  //LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();

  //Limpa dnv
  delay(2000);
  lcd.clear();

}

void loop()
{

  //Limpa o LCD
  lcd.clear();

  //Volta para primeira linha
  lcd.setCursor(0, 0);

  /* Criar a variável "lido" para ler e armazenar 
     o valor do potenciômetro.*/
   
  int lido = analogRead (pino_Potenciometro);
  
  /*Criar a variável "angulo" para converter
    e armazenar a tensão emitida pelo potenciômetro
    em ângulo para os servos motores.*/
    
  byte angulo = map (lido, 0, 1023, 0, 179);



  //Configuração dos farois
  //******* Só funciona se colocar até o final para ambos os lados
  if (angulo < 40){
    //Ponte fechada, pode passar, liga o verde
    semaforo(farolEsquerdoVerde, farolEsquerdoVermelho, farolEsquerdoAmarelo);
    semaforo(farolDireitoVerde, farolDireitoVermelho, farolDireitoAmarelo);

    //Mensagem Serial
    Serial.println("Farol Verde! Passagem Liberada");

    //Mensagem da primeira linha
    lcd.print("Farol Verde!");

    //Linha de baixo
    lcd.setCursor(0, 1);  

    //Mensagem da segunda linha
    lcd.print("Passagem Liberada!");

    

  }
  else if (angulo <= 90){
    //Começando a subir a ponte, liga o amarelo
    semaforo(farolEsquerdoAmarelo, farolEsquerdoVerde, farolEsquerdoVermelho);
    semaforo(farolDireitoAmarelo, farolDireitoVerde, farolDireitoVermelho);

    //Mensagem Serial
    Serial.println("Farol Amarelo! Fique em Alerta");

    //Mensagem da primeira linha
    lcd.print("Farol Amarelo!");

    //Linha de baixo
    lcd.setCursor(0, 1);  

    //Mensagem da segunda linha
    lcd.print("Fique em Alerta!");
  }
  else{
    //Já subiu a ponte, liga o vermelho
    semaforo(farolEsquerdoVermelho, farolEsquerdoAmarelo, farolEsquerdoVerde);
    semaforo(farolDireitoVermelho, farolDireitoAmarelo, farolDireitoVerde);

    //Mensagem Serial
    Serial.println("Farol Vermelho! Passagem Bloqueada");

    //Mensagem da primeira linha
    lcd.print("Farol Vermelho!");

    //Linha de baixo
    lcd.setCursor(0, 1);  

    //Mensagem da segunda linha
    lcd.print("Passagem Bloqueada!");
  }

  //Não deixa abaixar menos que 90 graus ou mais que 150
  if (angulo < 90) {
    angulo = 90;
  }
  else if (angulo > 150){
    angulo = 150;
  }



  /*Escrever o valor obtido pela variável "angulo"
  dentro das variáveis que controlam os servos motores.*/
  
  motor_ponte_direita.write(angulo);
  motor_ponte_esquerda.write(angulo);

  /*Checagem da precisão de escrita do ângulo 
    pelo monitor serial do próprio Arduino.*/
  
  Serial.print("A0:");
  Serial.print(lido);
  Serial.print(" angulo:");
  Serial.println(angulo);
  delay(1000);
  

}


void semaforo(int semaforoLigar, int semaforoDesligar1, int semaforoDesligar2){
  //Acende o LED que deve ser ligado
  digitalWrite(semaforoLigar, HIGH);

  //Desliga os outros
  digitalWrite(semaforoDesligar1, LOW);
  digitalWrite(semaforoDesligar2, LOW);


}
