
#define maxBraco 13
#define maxMao 18

unsigned long millisBracoTest = 0;
unsigned int delayBracoTest = 2000;

char moveControl[17] = "-default";
int bracoControl = 13;
int maoControl = 10;

unsigned long time;

unsigned long millisStop = 0;
unsigned int delayStop = 2000;
////////////////////////////////////////////////////
#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle listener;
std_msgs::String str_msg;
ros::Publisher answer("answer", &str_msg);
char hello[13] = "hello world!";

void messageROS( const std_msgs::String& toggle_msg);
ros::Subscriber<std_msgs::String> sub("talker" , &messageROS);

void setupROS()
{
  pinMode(13, OUTPUT);  
  listener.initNode();
  listener.subscribe(sub);

  listener.initNode();
  listener.advertise(answer);  
}

void messageROS( const std_msgs::String& toggle_msg)
{
  millisStop = millis();
  //digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  digitalWrite(13, HIGH);   // blink the led
  
  if(toggle_msg.data[0] == '9')
  {
    str_msg.data = hello;
    answer.publish( &str_msg );
    listener.spinOnce();
    digitalWrite(13, LOW);   // blink the led
    delay(5000);
  }
  moveControl[0] = toggle_msg.data[0];
}
////////////////////////////////////////////////////

//unsigned long time1 = millis();
//unsigned long time2 = time1 + 800;

//unsigned long microsRead1 = 0;
//unsigned long delayRead1 = 1000000;

//boolean bracoAumentar = false;
//boolean MaoAumentar = false;

/*
0giraHorario
1giraAntiHorario
2frente
3tras
4esquerda
5direita
6dFD //diagonalFrenteDireita
7dTE //diagonalTrasEsquerda
8dFE //diagonalFrenteEsquerda
9dTD //diagonalTrasDireita
 */
void setup() {
  setupUteis();
  setupLocomover();
  setupServos();
  setupEletroima();
  setupUltrasonic();
  setupPressao();
  setupROS();
}

void loop() {
  listener.spinOnce();

  
//  loopUltrasonic();
//  loopPressao();
  
//  testBracoMao();
//  testLocomover();   
//  if(delayMillis(&millisBracoTest, delayBracoTest))
//  {
//    if(freeWay())
//      strcpy(moveControl, "2frente");
//    else
//      strcpy(moveControl, "-default"); 
//  }
  moveBraco(bracoControl);
  moveMao(maoControl); 
  switch (moveControl[0]) {
    case '0':
      giraHorario();
      break;
    case '1':
      giraAntiHorario();
      break;
    case '2':
      frente();
      break;
    case '3':
      tras();
      break;
    case '4':
      esquerda();
      break;
    case '5':
      direita();
      break;
    case '6':
      dFD();
      break;
    case '7':
      dTE();
      break;
    case '8':
      dFE();
      break;
    case '9':
      dTD();
      break;
    default:
      break;
  }
  
  if(delayMillisKeep(&millisStop, delayStop)) //Se não receber comando, fica parado
  {
    moveControl[0] = '-';
  }
}






/*
//utilizado para teste apenas
// movimenta o braco e a mao em todas as POSICOES possiveis
void testBracoMao()
{
  if(delayMillis(&millisBracoTest, delayBracoTest))
  {
    if(bracoAumentar)
    {
      if(bracoControl < maxBraco)
        bracoControl++;
      if(bracoControl >= maxBraco) //nunca deve ser maior
        bracoAumentar = false;
    }
    else
    {
      if(bracoControl > 0)
        bracoControl--;
      if(bracoControl <= 0) //nunca deve ser menor
        bracoAumentar = true;      
    }
    
    if(MaoAumentar)
    {
      if(maoControl < maxMao)
        maoControl++;
      if(maoControl >= maxMao) //nunca deve ser maior
        MaoAumentar = false;      
    }
    else
    {
      if(maoControl > 0)
        maoControl--;
      if(maoControl <= 0) //nunca deve ser menor
        MaoAumentar = true;  
    }      
  }
}

//utilizado para teste apenas
// locomove o carrinho em todas as DIRECOES possiveis
void testLocomover()
{
  if(millis() < 1000 * 2)
  {      
      strcpy(moveControl, "0giraHorario");
  }
  else if(millis() < 2000 * 2)
  {
      strcpy(moveControl, "1giraAntiHorario");
  }
  else if(millis() < 3000 * 2)
  {
      strcpy(moveControl, "2frente");
  }
  else if(millis() < 4000 * 2)
  {
      strcpy(moveControl, "3tras");
  }
  else if(millis() < 5000 * 2)
  {
      strcpy(moveControl, "4esquerda");
  }
  else if(millis() < 6000 * 2)
  {
      strcpy(moveControl, "5direita");
  }
  else if(millis() < 7000 * 2)
  {
      strcpy(moveControl, "6dFD");
  }
  else if(millis() < 8000 * 2)
  {
      strcpy(moveControl, "7dTE");
  }
  else if(millis() < 9000 * 2)
  {
      strcpy(moveControl, "8dFE");
  }
  else if(millis() < 10000 * 2)
  {
      strcpy(moveControl, "9dTD");
  }
  else
  {
      strcpy(moveControl, "-default");
  }
  
}
*/