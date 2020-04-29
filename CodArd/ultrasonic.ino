#include <Ultrasonic.h>

//const int echoPin = 21; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)#tras
//const int trigPin = 20; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
//const int echoPin = 29; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)#direita
//const int trigPin = 27; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
//const int echoPin = 32; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)#esquerda
//const int trigPin = 47; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
const int echoPin = 17; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)#frente
const int trigPin = 16; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)


Ultrasonic ultrasonic(trigPin,echoPin); //INICIALIZANDO OS PINOS DO ARDUINO

unsigned long duration;
int distance; //VARIÁVEL DO TIPO INTEIRO
String result2; //VARIÁVEL DO TIPO STRING

int distancia; //VARIÁVEL DO TIPO INTEIRO
String result; //VARIÁVEL DO TIPO STRING

unsigned long mUltra = 0;
unsigned int dUltra = 500;

int index = 0;
int v1[] = {1,1,1,1,1};
int v2[] = {1,1,1,1,1};
int v3[] = {1,1,1,1,1};
int v4[] = {1,1,1,1,1};
int s1 = 5;
int s2 = 5;
int s3 = 5;
int s4 = 5;

void setupUltrasonic() 
{
  pinMode(echoPin, INPUT); //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(trigPin, OUTPUT); //DEFINE O PINO COMO SAIDA (ENVIA)
}

//MÉTODO RESPONSÁVEL POR CALCULAR A DISTÂNCIA
//void hcsr04_OLD()
//{
//    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
//    delayMicroseconds(2); //INTERVALO DE 2 MICROSSEGUNDOS
//    digitalWrite(trigPin, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
//    delayMicroseconds(10); //INTERVALO DE 10 MICROSSEGUNDOS
//    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
//    //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
//    //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
//    //NA VARIAVEL "distancia"
//    distancia = (ultrasonic.Ranging(CM)); //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
//    result = String(distancia); //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
//    
////    delay(500); //INTERVALO DE 500 MILISSEGUNDOS
//}

//MÉTODO RESPONSÁVEL POR CALCULAR A DISTÂNCIA
void hcsr04()
{
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
    delayMicroseconds(2); //INTERVALO DE 2 MICROSSEGUNDOS
    digitalWrite(trigPin, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
    delayMicroseconds(10); //INTERVALO DE 10 MICROSSEGUNDOS
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
    
    duration = pulseIn(echoPin, HIGH);
    distance = duration*0.034/2;
    result2 = String(distance); //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
    
}

boolean freeWay()
{
  hcsr04();
  if(distance > 20)
    return true; //caminho livre, pode prosseguir
  else
    return false; //obstaculo detectado
}

//só deve verificar na direcao do movimento
int detectarObstaculo()
{
  if(freeWay()) 
  { //livre = 1
    if(v1[index] == 0)
    {
      s1++;
      v1[index] = 1;      
    }
  }
  else
  { //obstaculo detectado = 0
    if(v1[index] == 1)
    {
      s1--;   
      v1[index] = 0;       
    }  
  }
  index++;
  if(index == 5)
    index = 0;
  if(s1 <= 2)
    return 1; //sensor 1 com obstaculo
  else
    return 0; //livre
}

void loopUltrasonic()
{
  
  if(delayMillis(&mUltra, dUltra))
  {
    hcsr04();
    Serial.println(result2);
  }
  
}
 
