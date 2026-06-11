#include <Servo.h>

// VELOCIDADE

// Velocidade utilizada para andar para frente
int velocidade = 10;

// Velocidade utilizada durante as curvas
int velocidadeVirando = 15;


// DESVIO DE OBSTÁCULO

// Tempo utilizado para realizar o desvio
int anguloDesvio = 500;

// Tempo utilizado para procurar um caminho livre
int anguloBusca = 500;


// MOTORES

Servo motor11;
Servo motor10;
Servo motor9;
Servo motor8;


// SENSORES DE LINHA

// Porta do sensor esquerdo
int sensorFrenteEsq = 2;

// Porta do sensor direito
int sensorFrenteDir = 3;

// Variável para armazenar a leitura do sensor esquerdo
int frenteEsq;

// Variável para armazenar a leitura do sensor direito
int frenteDir;


// ULTRASSÔNICO

// Porta de envio do sinal ultrassônico
int trigPin = 5;

// Porta de recebimento do sinal ultrassônico
int echoPin = 4;

// Variável para armazenar o tempo do eco
long duracao;

// Variável para armazenar a distância calculada
int distancia;

// Variável para armazenar a distância à esquerda
int distanciaEsquerda;

// Variável para armazenar a distância à direita
int distanciaDireita;


void setup() {

  // Conectar motores às portas do shield
  motor11.attach(11);
  motor10.attach(10);
  motor9.attach(9);
  motor8.attach(8);

  // Configurar sensores de linha
  pinMode(sensorFrenteEsq, INPUT);
  pinMode(sensorFrenteDir, INPUT);

  // Configurar ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Todos os servos na posição parada
  parar();

  Serial.begin(9600);
}


void loop() {

  // Ler sensores de linha
  lerSensoresLinha();

  // Ler distância do ultrassônico
  lerUltrassonico();

  // Mostrar distância no monitor serial
  Serial.print("Distancia: ");
  Serial.println(distancia);

  // Verificar se existe obstáculo
  verificarObstaculo();

  // Controlar o movimento do carrinho
  seguirLinha();
}


// LEITURA DOS SENSORES

// Função para ler os sensores de linha
void lerSensoresLinha() {

  frenteEsq = digitalRead(sensorFrenteEsq);
  frenteDir = digitalRead(sensorFrenteDir);

  Serial.print("Esquerdo: ");
  Serial.println(frenteEsq);

  Serial.print("Direito: ");
  Serial.println(frenteDir);

  Serial.println();

}


// ULTRASSÔNICO

// Função para ler a distância do ultrassônico
void lerUltrassonico() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin, HIGH, 30000);

  //Caso de 0 de ditancia por pulso inválido
  if (duracao != 0) {

    distancia = duracao * 0.034 / 2;

  }

}


// VERIFICAÇÃO DE OBSTÁCULO

// Função para verificar se existe obstáculo
void verificarObstaculo() {

  // Caso a distância seja menor ou igual a 15 cm
  if (distancia <= 15) {

    desviarObstaculo();

  }

}


// ESCOLHA DO MELHOR LADO

// Função para descobrir qual lado possui mais espaço livre
int escolherMelhorLado() {

  // Virar para a esquerda para realizar a leitura
  virarEsquerda();
  delay(anguloBusca);

  // Ler distância à esquerda
  lerUltrassonico();

  // Armazenar distância encontrada
  distanciaEsquerda = distancia;

  // Voltar para a posição central
  virarDireita();
  delay(anguloBusca);

  // Virar para a direita para realizar a leitura
  virarDireita();
  delay(anguloBusca);

  // Ler distância à direita
  lerUltrassonico();

  // Armazenar distância encontrada
  distanciaDireita = distancia;

  // Voltar para a posição central
  virarEsquerda();
  delay(anguloBusca);

  // Mostrar distância no monitor serial
  Serial.print("Distancia Esquerda: ");
  Serial.println(distanciaEsquerda);

  // Mostrar distância no monitor serial
  Serial.print("Distancia Direita: ");
  Serial.println(distanciaDireita);

  // Caso a esquerda tenha mais espaço
  if (distanciaEsquerda > distanciaDireita) {

    return -1;

  }

  // Caso a direita tenha mais espaço
  return 1;

}


// DESVIO DE OBSTÁCULO

// Função para realizar o desvio
void desviarObstaculo() {

  // Descobrir qual lado possui mais espaço
  int lado = escolherMelhorLado();

  // Caso a esquerda seja o melhor caminho
  if (lado == -1) {

    virarEsquerda();
    delay(anguloDesvio);

  }

  // Caso a direita seja o melhor caminho
  else {

    virarDireita();
    delay(anguloDesvio);

  }

}


// SEGUE LINHA

// Função para controlar o segue linha
void seguirLinha() {

  // Caso os dois sensores estejam sobre a linha
  if (frenteEsq == 0 && frenteDir == 0) {

    irFrente();

  }

  // Caso o sensor esquerdo saia da linha
  else if (frenteEsq == 1 && frenteDir == 0) {

    virarEsquerda();
    delay(500);

  }

  // Caso o sensor direito saia da linha
  else if (frenteEsq == 0 && frenteDir == 1) {

    virarDireita();
    delay(500);

  }

  // Caso os dois sensores saiam da linha
  else if (frenteEsq == 1 && frenteDir == 1) {

    irFrente();

  }

}


// MOVIMENTOS

// Função para mover o carrinho para frente
void irFrente() {

  // Motores esquerdos para frente
  motor11.write(90 + velocidade);
  motor10.write(90 + velocidade);

  // Motores direitos para frente
  motor9.write(90 - velocidade);
  motor8.write(90 - velocidade);

}


// Função para mover o carrinho para trás
void irTras() {

  // Motores esquerdos para trás
  motor11.write(90 - velocidade);
  motor10.write(90 - velocidade);

  // Motores direitos para trás
  motor9.write(90 + velocidade);
  motor8.write(90 + velocidade);

}


// Função para virar o carrinho para a esquerda
void virarEsquerda() {

  // Motores esquerdos para trás
  motor11.write(90 - velocidadeVirando);
  motor10.write(90 - velocidadeVirando);

  // Motores direitos para trás
  motor9.write(90 - velocidadeVirando);
  motor8.write(90 - velocidadeVirando);

}


// Função para virar o carrinho para a direita
void virarDireita() {

  // Motores esquerdos para frente
  motor11.write(90 + velocidadeVirando);
  motor10.write(90 + velocidadeVirando);

  // Motores direitos para frente
  motor9.write(90 + velocidadeVirando);
  motor8.write(90 + velocidadeVirando);

}


// Função para parar o carrinho
void parar() {

  // Todos os motores parados
  motor11.write(90);
  motor10.write(90);

  motor9.write(90);
  motor8.write(90);

}