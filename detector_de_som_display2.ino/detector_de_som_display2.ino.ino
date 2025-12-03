
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define endereco 0x27
#define linhas 2
#define colunas 16

LiquidCrystal_I2C lcd(endereco, colunas, linhas);

bool som;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();

  Serial.begin(9600);
  Serial.println("Sistema iniciado...");
  Serial.println("Monitorando som na porta 7...");
  Serial.println();

  pinMode(7, INPUT);

  delay(2000);
  lcd.clear();
}

void loop() {

  som = digitalRead(7);

  lcd.clear();              
  lcd.setCursor(0, 0);      

  if (!som) {
    // LCD
    lcd.print("Som Auto.");
    lcd.setCursor(0, 1);
    lcd.print("Cuidado!");
    
    // SERIAL
    Serial.println("Som detectado! (Valor: 0)");
    Serial.println("Exibindo: Som Auto / Cuidado!");
  } 
  else {
    // LCD
    lcd.print("Sem som.");
    lcd.setCursor(0, 1);
    lcd.print("Silencio!");

    // SERIAL
    Serial.println("Sem som detectado. (Valor: 1)");
    Serial.println("Exibindo: Sem som / Silencio!");
  }

  Serial.println("-----------------------------");

  delay(2000);
}
