#include <Servo.h>

/*
Posicoes Motor 1
Teorico  Real
0   5
10  15
20  23
30  31
40  39
50  48
60  56
70  66
80  75
90  85
100 94
110 104
120 115
130 123
*/
/*
Posicoes Motor 2
Teorico  Real
0   151
10  141
20  134
30  126
40  118
50  110
60  102
70  94
80  86
90  77
100 69
110 60
120 51
130 43

*/

Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;
// twelve servo objects can be created on most boards

//int pos = 0;    // variable to store the servo position
//int servoUm[] = {5, 15, 23, 31, 39, 48, 56, 66, 75, 85, 94, 104, 115, 123}; //direito braco
int servoUm[] = {5, 15, 20, 31, 39, 48, 56, 66, 75, 85, 94, 104, 115, 120}; //direito braco
int servoDois[] = {151, 141, 134, 126, 118, 110, 102, 94, 86, 77, 69, 60, 51, 43}; //esquerdo braco
int servoTres[] = {9, 14, 20, 29, 36, 45, 54, 63, 71, 81, 90, 99, 108, 116, 125, 133, 141, 149, 163};
//int servoTres[] = {8, 10, 16, 24, 32, 40, 48, 57, 65, 72, 83, 92, 101, 111, 120, 128, 137, 145, 154};
int servoQuatro[] = {167, 164, 156, 147, 139, 130, 121, 112, 104, 93, 84, 76, 67, 58, 49, 41, 33, 26, 16};
int servoPos1, servoPos2, servoPos3, servoPos4;

unsigned long millisBraco = 0;
unsigned int delayBraco = 5;

unsigned long millisMao = 0;
unsigned int delayMao = 20;

void setupServos() {
//  setupLocomover();
  myservo1.attach(11); // Servo1 (mais proximo dos 5V)
  myservo2.attach(6); // Servo2
  myservo3.attach(5); // Servo3
  myservo4.attach(4); // Servo4 ( mais proximo da escrita servo)
  servoPos1 = servoUm[13];
  servoPos2 = servoDois[13];
  servoPos3 = servoTres[10];
  servoPos4 = servoQuatro[10];
  myservo1.write(servoPos1);
  myservo2.write(servoPos2);
  myservo3.write(servoPos3);
  myservo4.write(servoPos4);
  //moveBraco(13);
  //moveMao(10);  
}

//posicao vai de 0 ate 13
void moveBraco(int pos)
{
  if(
  (servoPos1 != servoUm[pos] || servoPos2 != servoDois[pos])
  && delayMillis(&millisBraco, delayBraco)
  )
  {
    if(servoPos1 > servoUm[pos])
    {
      servoPos1--;
    }
    else if(servoPos1 < servoUm[pos])
    {
      servoPos1++;
    }
    
    if(servoPos2 > servoDois[pos])
    {
      servoPos2--;
    }
    else if(servoPos2 < servoDois[pos])
    {
      servoPos2++;
    }
    
    myservo2.write(servoPos2);
    myservo1.write(servoPos1);
  }
}

//posicao vai de 0 ate 18
void moveMao(int pos)
{
  pos = 18 - pos;
  //myservo3.write(servoTres[pos]);
  //myservo4.write(servoQuatro[pos]); 
  if(
  (servoPos3 != servoTres[pos] || servoPos4 != servoQuatro[pos])
  && delayMillis(&millisMao, delayMao)
  )
  {
    if(servoPos3 > servoTres[pos])
    {
      servoPos3--;
    }
    else if(servoPos3 < servoTres[pos])
    {
      servoPos3++;
    } 
    
    if(servoPos4 > servoQuatro[pos])
    {
      servoPos4--;
    }
    else if(servoPos4 < servoQuatro[pos])
    {
      servoPos4++;
    }  
    myservo3.write(servoPos3);
    myservo4.write(servoPos4);     
  }  
}
