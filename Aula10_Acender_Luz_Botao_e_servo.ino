#include <Servo.h>

Servo myservo;

const int pinoLed = 9;
const int pinoBotao = 5;
int pressionadoAnterior = 0;
int ligado = 0;
int pos;    // variable to store the servo position
int pos2;
int guardaState2;

void setup() {
  Serial.begin(9600);
  myservo.attach(6);
  while (!Serial) {}
  pinMode (pinoLed, OUTPUT);
  pinMode (pinoBotao, INPUT);
}

void loop() {
  int pressionado = digitalRead(pinoBotao);
  // caso o botao nao estava pressionado no instante anterior
  // && é o AND (E)
  Serial.println(pressionado);
  if (pressionado && (pressionadoAnterior == LOW)) {
    acionaPortao(ligado);
    delay(1000);
    ligado = 1 - ligado;
    digitalWrite(pinoLed, ligado);
    
    
  }
  //digitalWrite(pinoLed, ligado);
  //acionaPortao(ligado);
  pressionadoAnterior = pressionado;
}

void acionaPortao(int direcao) {
  // Abrir Portao : direcao = 1

  if (direcao == 0) {
    for (pos = 0; pos <= 100; pos += 1) { // goes from 0 degrees to 180 degrees
      myservo.write(pos);

      Serial.println("Portao Abrindo");
      Serial.flush();
    }
    guardaState2 = guardaState2 + 1;
    Serial.println("Portao Aberto");
  }
  // Fechar Portao
  else if (direcao == 1)  {
    for (pos2 = pos; pos2 >= 0; pos2--) { // goes from 180 degrees to 0 degrees
      myservo.write(pos2);  // waits 15ms for the servo to reach the position
      Serial.println("Portao Fechando");
      Serial.flush();
    }
    guardaState2 = guardaState2 - 1;
    Serial.println("Portao Fechado");
  }
}
