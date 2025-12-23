// C++ code
//

#define ledVermelho 2
#define ledAmarelo 3
#define ledVerde 4
void setup()
{
 	pinMode(ledVermelho, OUTPUT);
 	pinMode(ledAmarelo, OUTPUT);
    pinMode(ledVerde, OUTPUT);
  
    Serial.begin(9600);
    Serial.println("Sistema iniciado...");
    Serial.println();
}

void loop()
{
  //Farol Verde fica por 10 segundos
  ligarFarol(ledVerde, ledAmarelo, ledVermelho);
  Serial.println("Farol Verde, pode prosseguir!");
  Serial.println();
  delay(10000);
  
  //Farol Amarelo fica por 2 segundos
  ligarFarol(ledAmarelo, ledVermelho, ledVerde);
  Serial.println("Farol AMarelo, diminua a velocidade!");
  Serial.println();
  delay(2000);
  
  //Farol Vermelho fica por 5 segundos
  ligarFarol(ledVermelho, ledVerde, ledAmarelo);
  Serial.println("Farol Vermelho, fique parado imediatamente!");
  Serial.println();
  delay(5000);
}

//Função paraligar o farol principal e desligar outros
void ligarFarol(int ledLiga, int ledApaga1, int ledApaga2){
	digitalWrite(ledLiga, HIGH);
    digitalWrite(ledApaga1, LOW);
    digitalWrite(ledApaga2, LOW);

}