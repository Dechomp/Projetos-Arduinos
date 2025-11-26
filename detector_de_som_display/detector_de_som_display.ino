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
LiquidCrystal_I2C lcd(endereco, colunas, linhas)

//Variável apara detectar o som
bool som;


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
