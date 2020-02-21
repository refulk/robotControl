#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN           2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define E_STEP_PIN         26
#define E_DIR_PIN          28
#define E_ENABLE_PIN       24

#define Q_STEP_PIN         36
#define Q_DIR_PIN          34
#define Q_ENABLE_PIN       30

#define SDPOWER            -1
#define SDSS               53
#define LED_PIN            13

#define FAN_PIN            9

#define PS_ON_PIN          12
#define KILL_PIN           -1

#define HEATER_0_PIN       10
#define HEATER_1_PIN       8
#define TEMP_0_PIN          13   // ANALOG NUMBERING
#define TEMP_1_PIN          14   // ANALOG NUMBERING

unsigned long microsPasso = 0;
unsigned long delayPasso = 250;
boolean passo = true;

void setupLocomover() {
    
  pinMode(FAN_PIN , OUTPUT);
  pinMode(HEATER_0_PIN , OUTPUT);
  pinMode(HEATER_1_PIN , OUTPUT);
  pinMode(LED_PIN  , OUTPUT);
  
  pinMode(X_STEP_PIN  , OUTPUT);
  pinMode(X_DIR_PIN    , OUTPUT);
  pinMode(X_ENABLE_PIN    , OUTPUT);
  
  pinMode(Y_STEP_PIN  , OUTPUT);
  pinMode(Y_DIR_PIN    , OUTPUT);
  pinMode(Y_ENABLE_PIN    , OUTPUT);
  
  pinMode(Z_STEP_PIN  , OUTPUT);
  pinMode(Z_DIR_PIN    , OUTPUT);
  pinMode(Z_ENABLE_PIN    , OUTPUT);
  
  pinMode(E_STEP_PIN  , OUTPUT);
  pinMode(E_DIR_PIN    , OUTPUT);
  pinMode(E_ENABLE_PIN    , OUTPUT);
  
  pinMode(Q_STEP_PIN  , OUTPUT);
  pinMode(Q_DIR_PIN    , OUTPUT);
  pinMode(Q_ENABLE_PIN    , OUTPUT);
  
  digitalWrite(X_ENABLE_PIN    , LOW);
  digitalWrite(Y_ENABLE_PIN    , LOW);
  digitalWrite(Z_ENABLE_PIN    , LOW);
  digitalWrite(E_ENABLE_PIN    , LOW);
  digitalWrite(Q_ENABLE_PIN    , LOW);
    
  digitalWrite(X_DIR_PIN    , LOW);
  digitalWrite(Y_DIR_PIN    , LOW);
  digitalWrite(Z_DIR_PIN    , LOW);
  digitalWrite(Q_DIR_PIN    , LOW);  
}

void locomover(boolean m1, boolean m2, boolean m3, boolean m4) //locomover funcao
{  
  if(delayMicros(&microsPasso, delayPasso))
  {
    if(passo)
    {
      passo = false;      
      digitalWrite(X_STEP_PIN, LOW);    // Passos  de acionamento nível abaixo
      digitalWrite(Y_STEP_PIN, LOW);
      digitalWrite(Z_STEP_PIN, LOW);
      digitalWrite(Q_STEP_PIN, LOW);
    }
    else
    {
      passo = true;
      if(m1)
        digitalWrite(X_STEP_PIN, HIGH);  // Passos  de acionamento nível alto
      if(m2)
        digitalWrite(Y_STEP_PIN, HIGH);
      if(m3)
        digitalWrite(Z_STEP_PIN, HIGH);
      if(m4)
        digitalWrite(Q_STEP_PIN, HIGH);
    }
  }
}

void giraHorario()
{
  digitalWrite(X_DIR_PIN, LOW); // frente esquerdo - anti horário
  digitalWrite(Y_DIR_PIN, LOW); // frente direito - anti horário
  digitalWrite(Z_DIR_PIN, LOW); // traseiro esquerdo - anti horário 
  digitalWrite(Q_DIR_PIN, LOW); // traseiro direito - anti horário
  locomover(true, true, true, true);
}

void giraAntiHorario()
{
  digitalWrite(X_DIR_PIN, HIGH); // frente esquerdo - horário
  digitalWrite(Y_DIR_PIN, HIGH);
  digitalWrite(Z_DIR_PIN, HIGH);
  digitalWrite(Q_DIR_PIN, HIGH);
  locomover(true, true, true, true);
}

void frente()
{    
  digitalWrite(X_DIR_PIN, LOW); // frente esquerdo - anti horário
  digitalWrite(Y_DIR_PIN, HIGH); // Motor dianteiro esquerdo - sentido horário
  digitalWrite(Z_DIR_PIN, LOW); // Motor traseiro direito - sentido horário 
  digitalWrite(Q_DIR_PIN, HIGH); // Motor traseiro esquerda - sentido horário
  locomover(true, true, true, true);
}

void tras()
{    
  digitalWrite(X_DIR_PIN, HIGH); // frente esquerdo - horário 
  digitalWrite(Y_DIR_PIN, LOW); 
  digitalWrite(Z_DIR_PIN, HIGH); 
  digitalWrite(Q_DIR_PIN, LOW); 
  locomover(true, true, true, true);
}

void esquerda()
{    
  digitalWrite(X_DIR_PIN, HIGH); // frente esquerdo - horário 
  digitalWrite(Y_DIR_PIN, HIGH); 
  digitalWrite(Z_DIR_PIN, LOW); 
  digitalWrite(Q_DIR_PIN, LOW); 
  locomover(true, true, true, true);
}

void direita()
{    
  digitalWrite(X_DIR_PIN, LOW); // frente esquerdo - anti horário 
  digitalWrite(Y_DIR_PIN, LOW); 
  digitalWrite(Z_DIR_PIN, HIGH); 
  digitalWrite(Q_DIR_PIN, HIGH); 
  locomover(true, true, true, true);
}

void dFD() //diagonalFrenteDireita
{    
  digitalWrite(X_DIR_PIN, LOW); // frente esquerdo - anti horário
  digitalWrite(Q_DIR_PIN, HIGH); // traseiro direito - horário 
  locomover(true, false, false, true);
}

void dTE() //diagonalTrasEsquerda
{    
  digitalWrite(X_DIR_PIN, HIGH); // frente esquerdo - anti horário
  digitalWrite(Q_DIR_PIN, LOW); // traseiro direito - horário 
  locomover(true, false, false, true);
}

void dFE() //diagonalFrenteEsquerda
{    
  digitalWrite(Y_DIR_PIN, HIGH); // Motor dianteiro esquerdo - sentido horário
  digitalWrite(Z_DIR_PIN, LOW); // Motor traseiro direito - sentido horário 
  locomover(false, true, true, false);
}

void dTD() //diagonalTrasDireita
{    
  digitalWrite(Y_DIR_PIN, LOW); // Motor dianteiro esquerdo - sentido horário
  digitalWrite(Z_DIR_PIN, HIGH); // Motor traseiro direito - sentido horário 
  locomover(false, true, true, false);
}
