#include <Servo.h>

Servo alimentador;

// Pinos
const int trigPin = 6;
const int echoPin = 7;
const int servoPin = 9;

// Configurações
const int distanciaAtivacao = 20;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  alimentador.attach(servoPin);

  // Começa com a comporta fechada
  alimentador.write(0);
}

void loop() {
  // Envia o pulso do ultrassônico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Recebe o retorno
  long duracao = pulseIn(echoPin, HIGH);

  // Calcula a distância em centímetros
  int distancia = duracao * 0.034 / 2;

  // Verifica se algo está próximo
  if (distancia > 0 && distancia <= distanciaAtivacao) {

    // Abre a comporta
    alimentador.write(90);

    delay(1000);

    // Fecha a comporta
    alimentador.write(0);

    // Evita acionamentos repetidos
    delay(2000);
  }

  delay(100);
}
