
char moveControl[5] = "9999";
char comando[3] = "99";
int bracoControl = 13;
int maoControl = 10;

char tempValor[3] = "99";
int valorComando = 0;
char aux[20] = "";

bool responder = false;

//delay parar movimento caso nao exista novo comando
unsigned long millisStop = 0;
unsigned int delayStop = 200;

/////////////////////////////////////////////////////
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

void answerROSmsg(char msg[10])
{
  str_msg.data= msg;
  answer.publish( &str_msg );
  listener.spinOnce();
  responder = false;
}

void messageROS( const std_msgs::String& toggle_msg)
{
  responder = true;
  millisStop = millis();
  //digitalWrite(13, HIGH-digitalRead(13));   // blink the led
//  digitalWrite(13, HIGH);   // blink the led
  
//  if(toggle_msg.data[0] == '9')
//  {

    //str_msg.data = hello;
    //answer.publish( &str_msg );
    //listener.spinOnce();
    
//    digitalWrite(13, LOW);   // blink the led
//    delay(5000);
//  }
  strcpy(moveControl, toggle_msg.data);
}

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
  //amaciarMotor();
  //Serial.begin(9600); 
  //Serial.println("--- Start Serial Monitor SEND_RCVE ---");
}

void loop() {
  if(detectarObstaculo() == 0)
  {
    //maoControl = 13;
  }
  else
  {
    //maoControl = 10;   
  }
  listener.spinOnce();

  moveBraco(bracoControl);
  moveMao(maoControl); 
  
  strncpy(comando,moveControl,2); //copia os 2 primeiros caracteres de 'moveControl' para 'comando'
  strncpy(tempValor,moveControl+2,2); //copia os 2 ultimos caracteres de 'moveControl' para 'tempValor'
  valorComando = atoi(tempValor); //converte de vetor de caracteres para inteiro
  set_delayPasso(valorComando); //atualiza delay (velocidade)
  
  switch (atoi(comando)) {
    case 0:
      strcpy(aux, "giraHorario");
      giraHorario();
      break;
    case 1:
      strcpy(aux, "giraAntiHorario");
      giraAntiHorario();
      break;
    case 2:
      strcpy(aux, "frente");
      frente();
      break;
    case 3:
      strcpy(aux, "tras");
      tras();
      break;
    case 4:
      strcpy(aux, "esquerda");
      esquerda();
      break;
    case 5:
      strcpy(aux, "direita");
      direita();
      break;
    case 6:
      strcpy(aux, "dFD");
      dFD();
      break;
    case 7:
      strcpy(aux, "dTE");
      dTE();
      break;
    case 8:
      strcpy(aux, "dFE");
      dFE();
      break;
    case 9:
      strcpy(aux, "frente");
      dTD();
      break;
    case 21:
      //bracoCima 
      strcpy(aux, "bracoCima");     
      bracoControl = valorComando;
      break;
    case 22:
      //bracoBaixo 
      strcpy(aux, "bracoBaixo");   
      bracoControl = valorComando;
      break;
    case 31:
      //maoCima 
      strcpy(aux, "maoCima");     
      maoControl = valorComando;
      break;
    case 32:
      //maoBaixo 
      strcpy(aux, "maoBaixo");   
      maoControl = valorComando;
      break;
    case 41:
      //eletroima ON
      ligarEletroima();
      break;
    case 42:
      //eletroima OFF
      desligarEletroima();
      break;
    default:
      strcpy(aux, "default");
      break;
  }  

  //Responde utilizando o no 'answer' o texto escrito em aux
  // no futuro o no answer deve retornar apenas quando for detectados obstaculos
  // pelo sensor de proximidade.
  // se necessario, na mensagem enviar se o obstaculo esta a frente, tras, direita, esquerda
  if(responder)
    answerROSmsg(aux);
    
  if(delayMillisKeep(&millisStop, delayStop)) //Se não receber comando, fica parado
  {
    strcpy(moveControl, "9999");
  }
}
