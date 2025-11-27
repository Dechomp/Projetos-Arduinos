//IDE do Arduino
#include  <Wire.h>

//Bibloteca do I2C
#include <LiquidCrystal_I2C.h>

//Definição de valores
//Endereço do I2C
#define endereco 0x27

//Quantidade de linhas
#define linhas 2

//Quantidade de colunas
#define colunas 16

//Cria uma variável do Liquid Crystal para configurar o LCD
LiquidCrystal_I2C lcd(endereco, colunas, linhas);

//Variável apara detectar o som
bool som;


void setup() {
  // put your setup code here, to run once:

  //Inicio o led
  lcd.init();

  //Ligo o fundo do led
  lcd.backlight();

  //Limpo qualquer texto salvo
  lcd.clear();

  //Abro a porta Serial
  Serial.begin(9600);
  
  //Porta de entrada de dados (detector de som)
  pinMode(7,INPUT);

  //Religo
  lcd.backlight();

  //Pausa de 2 segundos
  delay(2000);

  //Limpo o texto novamente
  lcd.clear();

}

//Còdigo em looping
void loop() {
  // put your main code here, to run repeatedly:

  //Recebo se há silencio ou não na porta 7
  som = digitalRead(7);

  //Se não houver silêncio
  if (!som){
    //MOstra a mensagem no LCD
    lcd.print("Som Auto.");

    //Direciono aonde quero q apareça
    lcd.setCursor(0,1);

    //Mostra=o a segunda mensagem
    lcd.print("Cuidado!");

    //Espero 2 segundos
    delay(2000);
  }

  //Limpo o LCD
  lcd.clear();
}
