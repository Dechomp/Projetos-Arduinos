const int btn_A = 2;
const int btn_B = 3;
const int rele_A = 4;
const int rele_B = 5;
const int pinoBuzzer = 6;
const int btnReset = 7;

bool jogoAtivo = true;

void setup() {
  // ATIVA O RESISTOR INTERNO (Mágica que dispensa o resistor físico)
  pinMode(btn_A, INPUT_PULLUP); 
  pinMode(btn_B, INPUT_PULLUP);
  pinMode(btnReset, INPUT_PULLUP);

  pinMode(rele_A, OUTPUT);
  pinMode(rele_B, OUTPUT);
  pinMode(pinoBuzzer, OUTPUT);

  digitalWrite(rele_A, HIGH); 
  digitalWrite(rele_B, HIGH);
  digitalWrite(pinoBuzzer, LOW);
}

void loop() {
  if (jogoAtivo) {
    // Agora verificamos se o sinal é LOW (botão apertado)
    if (digitalRead(btn_A) == LOW) {
      vitoria(rele_A);
    }
    else if (digitalRead(btn_B) == LOW) {
      vitoria(rele_B);
    }

    
  }

  if(digitalRead(btnReset) == LOW){
    digitalWrite(rele_A,HIGH);
    digitalWrite(rele_B,HIGH);
    jogoAtivo = true;
  }
}

void vitoria(int pinoVencedor) {
  jogoAtivo = false;
  digitalWrite(pinoVencedor, LOW); // Liga a lâmpada
  
  // Som de vitória
  digitalWrite(pinoBuzzer, HIGH);
  delay(1000);
  digitalWrite(pinoBuzzer, LOW);
  /*delay(5000);

  digitalWrite(pinoVencedor,HIGH);*/
}