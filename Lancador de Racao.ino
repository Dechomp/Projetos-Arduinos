#include <Servo.h>

Servo lancador;

const int botao = 9;
const int pinoServo = 6;

const int posicaoInicial = 20;
const int posicaoLancamento = 120;

void setup() {

  pinMode(botao, INPUT_PULLUP);

  lancador.attach(pinoServo);

  // Posição inicial
  lancador.write(posicaoInicial);

  delay(500);
}

void loop() {

  // Botão pressionado
  if (digitalRead(botao) == LOW) {

    // Movimento para lançar a ração
    lancador.write(posicaoLancamento);

    delay(300);

    // Retorna para a posição inicial
    lancador.write(posicaoInicial);

    delay(700);
  }
}
