// -------------------- IMPORTAÇÃO DAS BIBLIOTECAS --------------------
#include <Wire.h>
#include <Adafruit_TCS34725.h>

// -------------------- DEFINIÇÃO DE PINOS --------------------
int motorEsq = 9;   // ajustar conforme shield
int motorDir = 10;  // ajustar conforme shield

int chuvaPin = A0;  // HL-83 analógico

// Bluetooh (RX/TX do Arduino)
int BT_TX = 1; 
int BT_RX = 0;

// -------------------- SENSOR DE COR --------------------
Adafruit_TCS34725 tcs = Adafruit_TCS34725(
    TCS34725_INTEGRATIONTIME_50MS,
    TCS34725_GAIN_4X
);

// -------------------- VARIÁVEIS GLOBAIS --------------------
bool chovendo = false;
String corSemaforo = "nenhuma";

// -------------------- SETUP --------------------
void setup() {
  Serial.begin(9600);

  // Motores
  pinMode(motorEsq, OUTPUT);
  pinMode(motorDir, OUTPUT);

  // Sensor de chuva
  pinMode(chuvaPin, INPUT);

  // Inicia sensor de cor
  if (!tcs.begin()) {
    Serial.println("Erro ao iniciar TCS34725");
    while(1);
  }

  Serial.println("Sistema iniciado!");
}

// -------------------- LOOP PRINCIPAL --------------------
void loop() {

  lerChuva();
  lerCor();
  controlarMotores();
  enviarStatusBT();

  delay(100);
}

// -------------------- FUNÇÃO: CHUVA --------------------
void lerChuva() {
  int leitura = analogRead(chuvaPin);

  if (leitura < 600) chovendo = true;
  else chovendo = false;
}

// -------------------- FUNÇÃO: COR --------------------
void lerCor() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  // comparações simples
  if (g > r && g > b) corSemaforo = "verde";
  else if (r > g && r > b) corSemaforo = "vermelho";
  else if (r > g && g > b) corSemaforo = "amarelo";
  else corSemaforo = "indefinido";
}

// -------------------- FUNÇÃO: CONTROLE DOS MOTORES --------------------
void controlarMotores() {

  if (corSemaforo == "vermelho") { 
    analogWrite(motorEsq, 0);
    analogWrite(motorDir, 0);
  }

  else if (corSemaforo == "amarelo") {
    analogWrite(motorEsq, 120);
    analogWrite(motorDir, 120);
  }

  else if (corSemaforo == "verde") {
    if (chovendo) {
      analogWrite(motorEsq, 90);
      analogWrite(motorDir, 90);
    } else {
      analogWrite(motorEsq, 200);
      analogWrite(motorDir, 200);
    }
  }
}

// -------------------- FUNÇÃO: BLUETOOTH --------------------
void enviarStatusBT() {
  Serial.print("Cor: ");
  Serial.print(corSemaforo);
  Serial.print(" | Chuva: ");
  Serial.print(chovendo ? "Sim" : "Não");
  Serial.print(" | Motores: ");

  if (corSemaforo == "vermelho") Serial.println("Parado");
  else if (corSemaforo == "amarelo") Serial.println("Freando");
  else {
    if (chovendo) Serial.println("Devagar");
    else Serial.println("Normal");
  }
}