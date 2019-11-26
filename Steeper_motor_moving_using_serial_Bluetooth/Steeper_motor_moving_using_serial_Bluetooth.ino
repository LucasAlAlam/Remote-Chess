#include "BluetoothSerial.h"

#define vi 50
#define vf 5
#define motor1_pin_1  13
#define motor1_pin_2  12
#define motor1_pin_3  14
#define motor1_pin_4  27
#define motor2_pin_1  32
#define motor2_pin_2  33
#define motor2_pin_3  25
#define motor2_pin_4  26
#define volta 88
#define fim_de_curso_1  35
#define fim_de_curso_2  34

BluetoothSerial SerialBT;
int numero_passos_motor2, passo1, passo2;
int destino[2] = {49, 97}, origem[2] = {49, 97};
const bool passos[8][4] = {{HIGH, LOW, LOW, LOW},
  {HIGH, LOW, HIGH, LOW},
  {LOW, LOW, HIGH, LOW},
  {LOW, HIGH, HIGH, LOW},
  {LOW, HIGH, LOW, LOW},
  {LOW, HIGH, LOW, HIGH},
  {LOW, LOW, LOW, HIGH},
  {HIGH, LOW, LOW, HIGH}
};                            //0             1             2             3
const int motor[2][4] = {{motor1_pin_1, motor1_pin_2, motor1_pin_3, motor1_pin_4},
  {motor2_pin_1, motor2_pin_2, motor2_pin_3, motor2_pin_4}
};
bool le_fim_de_curso_1 , le_fim_de_curso_2 ;


void setup()
{

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      pinMode(motor[i][j], OUTPUT);
    }
  }
  pinMode(fim_de_curso_1, INPUT);
  pinMode(fim_de_curso_2, INPUT);
  pinMode(2, OUTPUT);
  desativa_motor(0);
  Serial.begin(115200);
  SerialBT.begin("Xadrez Remoto"); //Bluetooth device name
  //xTaskCreatePinnedToCore(loop2, "loop2", 8192, NULL, 1, NULL, 0);
  delay(1);
}



void desativa_motor(int i)
{
  for (int j = 0; j < 4; j++) {
    digitalWrite(motor[i][j], LOW);
  }
}
void movimenta_motor1(int numero_passos)
{
  int linha = 0;
  int passos_realizados = 0;
  float acelerador;
  if (numero_passos > 0) {
    for (acelerador = 0; acelerador < (vi - vf); acelerador = (-0.0119 * acelerador * acelerador) + (2.156 * acelerador) + 1.7241) {
      for (int pino = 0; pino < 4; pino++) {
        digitalWrite(motor[0][pino], passos[linha][pino]);
      }
      delay(vi - acelerador);
      linha++;
      passos_realizados++;
      if (linha > 7)
        linha = 0;

      if (passos_realizados == numero_passos) {
        numero_passos = 0;
        acelerador = vi;
      }
      le_fim_de_curso_1 = digitalRead(fim_de_curso_1);
      if (le_fim_de_curso_1 == HIGH)  {
        numero_passos = 0;
        acelerador = vi;
      }
    }
    numero_passos = numero_passos - passos_realizados;
    for (linha;  passos_realizados <= numero_passos ; linha++) {
      for (int pino = 0; pino < 4; pino++) {
        digitalWrite(motor[0][pino], passos[linha][pino]);
      }
      delay(vf);
      passos_realizados++;
      if (linha > 7)
        linha = 0;
      le_fim_de_curso_1 = digitalRead(fim_de_curso_1);
      if (le_fim_de_curso_1 == HIGH)  {
        numero_passos = 0;
      }
    }
    desativa_motor(0);
  }
  if (numero_passos < 0) {
    linha = 7;
    numero_passos *= -1;
    for (acelerador = 0; acelerador < (vi - vf); acelerador = (-0.0119 * acelerador * acelerador) + (2.156 * acelerador) + 1.7241) {
      for (int pino = 0; pino < 4; pino++) {
        digitalWrite(motor[0][pino], passos[linha][pino]);
      }
      delay(vi - acelerador);
      linha--;
      passos_realizados++;
      if (linha < 0)
        linha = 7;
      if (passos_realizados == numero_passos) {
        numero_passos = 0;
        acelerador = vi;
      }
      le_fim_de_curso_1 = digitalRead(fim_de_curso_1);
      if (le_fim_de_curso_1 == HIGH)  {
        numero_passos = 0;
        acelerador = vi;
      }
    }
    numero_passos = numero_passos - passos_realizados;
    for (linha;  passos_realizados <= numero_passos ; linha--) {
      for (int pino = 0; pino < 4; pino++) {
        digitalWrite(motor[0][pino], passos[linha][pino]);
      }
      delay(vf);
      passos_realizados++;
      if (linha < 0)
        linha = 7;
      le_fim_de_curso_1 = digitalRead(fim_de_curso_1);
      if (le_fim_de_curso_1 == HIGH)  {
        numero_passos = 0;
      }
    }
    desativa_motor(0);
  }
}
void movimenta_motor1_numero_casas(int numero_casas)
{
  movimenta_motor1(volta * numero_casas);
}
void movimenta_motor2(int numero_passos)
{
  int linha = 0;
  int passos_realizados = 0;
  float acelerador;
  if (numero_passos > 0) {
    for (acelerador = 0; acelerador < (vi - vf); acelerador = (-0.0119 * acelerador * acelerador) + (2.156 * acelerador) + 1.7241) {
      for (int pino = 0; pino < 4; pino++) {
        digitalWrite(motor[1][pino], passos[linha][pino]);
      }
      delay(vi - acelerador);
      linha++;
      passos_realizados++;
      if (linha > 7)
        linha = 0;
      if (passos_realizados == numero_passos) {
        numero_passos = 0;
        acelerador = vi;
      }
      le_fim_de_curso_2 = digitalRead(fim_de_curso_2);
      if (le_fim_de_curso_2 == HIGH)  {
        numero_passos = 0;
        acelerador = vi;
      }
    }
    numero_passos = numero_passos - passos_realizados;
    for (linha;  passos_realizados <= numero_passos ; linha++) {
      for (int pino = 0; pino < 4; pino++) {
        digitalWrite(motor[1][pino], passos[linha][pino]);
      }
      delay(vf);
      passos_realizados++;
      if (linha > 7)
        linha = 0;
      le_fim_de_curso_2 = digitalRead(fim_de_curso_2);
      if (le_fim_de_curso_2 == HIGH)  {
        numero_passos = 0;
      }
    }
    desativa_motor(1);
  }
  if (numero_passos < 0) {
    linha = 7;
    numero_passos *= -1;
    for (acelerador = 0; acelerador < (vi - vf); acelerador = (-0.0119 * acelerador * acelerador) + (2.156 * acelerador) + 1.7241) {
      for (int pino = 0; pino < 4; pino++) {
        digitalWrite(motor[1][pino], passos[linha][pino]);
      }
      delay(vi - acelerador);
      linha--;
      passos_realizados++;
      if (linha < 0)
        linha = 7;
      if (passos_realizados == numero_passos) {
        numero_passos = 0;
        acelerador = vi;
      }
      le_fim_de_curso_2 = digitalRead(fim_de_curso_2);
      if (le_fim_de_curso_2 == HIGH)  {
        numero_passos = 0;
        acelerador = vi;
      }
    }
    numero_passos = numero_passos - passos_realizados;
    for (linha;  passos_realizados <= numero_passos ; linha--) {
      for (int pino = 0; pino < 4; pino++) {
        digitalWrite(motor[1][pino], passos[linha][pino]);
      }
      delay(vf);
      passos_realizados++;
      if (linha < 0)
        linha = 7;
      le_fim_de_curso_2 = digitalRead(fim_de_curso_2);
      if (le_fim_de_curso_2 == HIGH)  {
        numero_passos = 0;
      }
    }
    desativa_motor(1);
  }
}
void movimenta_motor2_numero_casas(int numero_casas)
{
  movimenta_motor2(volta * numero_casas);
}
void loop()
{
  int casaX=0, casaY=0,  pos_vet=0, dado=0;
  while (SerialBT.available()) {
     destino[pos_vet] = SerialBT.read();
     pos_vet++;
     dado=1;
  }
    if (dado==1){
    casaX=destino[0]-origem[0];
    movimenta_motor1_numero_casas(casaX);
    casaY=destino[1]-origem[1];
    movimenta_motor2_numero_casas(casaY);
    origem[0]=destino[0];
    origem[1]=destino[1];
    dado = 0;
    }
  delay(200);
  
}
/*void loop2(void*z)
  {
  movimenta_motor2_numero_casas(5);
  movimenta_motor2_numero_casas(-5);
  }
*/
