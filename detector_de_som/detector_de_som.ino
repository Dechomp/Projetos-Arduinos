//Variável para armazenar se tem som ou não
bool som;

//Porta de saida do led
int led = 10;

//Setando portas de entrada e saida
void setup() {
  // put your setup code here, to run once:

  //Inicia a porta do Moitor Serial que irei usar
  Serial.begin(9600);

  //Confirgurando portas de entrada e saida

  //Entrada de dados
  //Porta 4 (Detector)
  pinMode(4, INPUT);

  //Portas de Saida 
  //Porta 10 (LED Vermelho)
  pinMode(led, OUTPUT);


}

//Código que fica rodando para sempre
void loop() {
  // put your main code here, to run repeatedly:

  //Recebe a presença de som
  som = digitalRead(4);

  //Caso tenha som, o arduino retorna um valor False
  //Então Se não tiver silencio
  if (!som){
    //Manda uma mensagem no LOG
    Serial.println("Som detectado");

    //Acende o LED
    digitalWrite(led, HIGH);

    //Espera dois segundos (2 * 1000) antes de apagar
    delay(2000);
  }

  //Desliga o LED
  digitalWrite(led, LOW);
}
