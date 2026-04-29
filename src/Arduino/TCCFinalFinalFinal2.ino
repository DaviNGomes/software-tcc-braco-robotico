//Pinos das pontes h
//Linha Transversal
const int LT_ENA = 44;   // PWM para velocidade
const int LT_IN1 = 10;
const int LT_IN2 = 45;
//base
const int B_ENA = 4;   // PWM para velocidade
const int B_IN1 = 40;
const int B_IN2 = 41;
//ombro
const int O_ENA = 5;   // PWM para velocidade
const int O_IN1 = 42;
const int O_IN2 = 25;
//Cotovelo
const int C_ENA = 6;   // PWM para velocidade
const int C_IN1 = 26;
const int C_IN2 = 27;
//Giro do punho
const int GP_ENA = 7;   // PWM para velocidade
const int GP_IN1 = 28;
const int GP_IN2 = 29;
//Movimento do punho
const int MP_ENA = 8;   // PWM para velocidade
const int MP_IN1 = 30;
const int MP_IN2 = 31;
//Garra
const int G_ENA = 9;   // PWM para velocidade
const int G_IN1 = 32;
const int G_IN2 = 33;

//Pinos dos encoders
//Linha tranversal
const byte LT_encoderPinA = 53;
const byte LT_encoderPinB = 52;
//Base
const byte B_encoderPinA = 18;
const byte B_encoderPinB = 34;
//Ombro
const byte O_encoderPinA = 19;
const byte O_encoderPinB = 35;
//Cotovelo
const byte C_encoderPinA = 20;
const byte C_encoderPinB = 36;
//Giro do punho
const byte GP_encoderPinA = 21;
const byte GP_encoderPinB = 37;
//Movimento do punho
const byte MP_encoderPinA = 2;
const byte MP_encoderPinB = 38;
//Garra
const byte G_encoderPinA = 3;
const byte G_encoderPinB = 39;

//Pinos das chaves fim de curso
//Linha tranversal
const int LT_limitSwitch = 51;
//base
const int B_limitSwitch = 46;
//ombro
const int O_limitSwitch = 47;
//cotovelo
const int C_limitSwitch = 48;
//giro do punho
const int GP_limitSwitch = 49;
//movimento do punho
const int MP_limitSwitch = 50;

//Variaveis para salvar a posição
//Linha Tranversal
volatile long LT_encoderPos = 0;
//base
volatile long B_encoderPos = 0;
//Ombro
volatile long O_encoderPos = 0;
//Cotovelo
volatile long C_encoderPos = 0;
//giro do punho
volatile long GP_encoderPos = 0;
int GP_lastEncoded = 0;
volatile long MP_encoderPos = 0;
//Garra
volatile long G_encoderPos = 0;

//Posições maximas e minimas
//Linha tranversal Descobrir o máximo
const long LT_POSICAO_MINIMA = 0;
const long LT_POSICAO_MAXIMA = 100000000;
//Base
const long B_POSICAO_MINIMA = -55000;
const long B_POSICAO_MAXIMA = -2000;
//OMBRO
const long O_POSICAO_MINIMA = 0;
const long O_POSICAO_MAXIMA = 18000;
//COTOVELO
const long C_POSICAO_MINIMA = -60;
const long C_POSICAO_MAXIMA = 19950;
//MOVIMENTO PUNHO
const long MP_POSICAO_MINIMA = -80;
const long MP_POSICAO_MAXIMA = 10600;
//GIRO PUNHO
const long GP_POSICAO_MINIMA = -410;
const long GP_POSICAO_MAXIMA = 23000;
//GARRA
const long G_POSICAO_MINIMA = 0;
const long G_POSICAO_MAXIMA = 26095;

int z = 0;

String comando = "";
unsigned long lastPrintTime = 0;

bool LT_fimCursoAcionado = false;
bool B_fimCursoAcionado = false;
bool O_fimCursoAcionado = false;
bool C_fimCursoAcionado = false;
bool GP_fimCursoAcionado = false;
bool MP_fimCursoAcionado = false;

int ok = 5;
volatile int okk=0;

void setup() {
  Serial.begin(9600);

  pinMode(LT_ENA, OUTPUT);
  pinMode(LT_IN1, OUTPUT);
  pinMode(LT_IN2, OUTPUT);

  pinMode(B_ENA, OUTPUT);
  pinMode(B_IN1, OUTPUT);
  pinMode(B_IN2, OUTPUT);

  pinMode(O_ENA, OUTPUT);
  pinMode(O_IN1, OUTPUT);
  pinMode(O_IN2, OUTPUT);

  pinMode(C_ENA, OUTPUT);
  pinMode(C_IN1, OUTPUT);
  pinMode(C_IN2, OUTPUT);

  pinMode(GP_ENA, OUTPUT);
  pinMode(GP_IN1, OUTPUT);
  pinMode(GP_IN2, OUTPUT);
  
  pinMode(MP_ENA, OUTPUT);
  pinMode(MP_IN1, OUTPUT);
  pinMode(MP_IN2, OUTPUT);

  pinMode(G_ENA, OUTPUT);
  pinMode(G_IN1, OUTPUT);
  pinMode(G_IN2, OUTPUT);

  pinMode(LT_encoderPinA, INPUT_PULLUP);
  pinMode(LT_encoderPinB, INPUT_PULLUP);
  
  pinMode(B_encoderPinA, INPUT_PULLUP);
  pinMode(B_encoderPinB, INPUT_PULLUP);

  pinMode(O_encoderPinA, INPUT_PULLUP);
  pinMode(O_encoderPinB, INPUT_PULLUP);

  pinMode(GP_encoderPinA, INPUT_PULLUP);
  pinMode(GP_encoderPinB, INPUT_PULLUP);

  pinMode(MP_encoderPinA, INPUT_PULLUP);
  pinMode(MP_encoderPinB, INPUT_PULLUP);

  pinMode(C_encoderPinA, INPUT_PULLUP);
  pinMode(C_encoderPinB, INPUT_PULLUP);

  pinMode(G_encoderPinA, INPUT_PULLUP);
  pinMode(G_encoderPinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(LT_encoderPinA), LT_updateEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(B_encoderPinA), B_updateEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(O_encoderPinA), O_updateEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(C_encoderPinA), C_updateEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(GP_encoderPinA), GP_updateEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(MP_encoderPinA), MP_updateEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(G_encoderPinA), G_updateEncoder, RISING);

  pinMode(LT_limitSwitch, INPUT_PULLUP);
  pinMode(B_limitSwitch, INPUT_PULLUP);
  pinMode(O_limitSwitch, INPUT_PULLUP);
  pinMode(C_limitSwitch, INPUT_PULLUP);
  pinMode(GP_limitSwitch, INPUT_PULLUP);
  pinMode(MP_limitSwitch, INPUT_PULLUP);
  //Zeramento Base
  while(z == 0){
    if(digitalRead(B_limitSwitch) == LOW and !B_fimCursoAcionado){
      setMotorB(80);     
    }
    else if(digitalRead(B_limitSwitch) == HIGH and !B_fimCursoAcionado){
      setMotorB(0);
      B_encoderPos = B_POSICAO_MINIMA;
      B_fimCursoAcionado = true;
      z=1;
    }
   }
   //Serial.println("1");
   //Zeramento movimento do punho
   while(z == 1){
          if(digitalRead(MP_limitSwitch) == LOW and !MP_fimCursoAcionado){
            setMotorMP(-80);
            setMotorGP(80);    
          }
          else if(digitalRead(MP_limitSwitch) == HIGH and !MP_fimCursoAcionado){
            setMotorMP(0);
            setMotorGP(0);
            MP_encoderPos = MP_POSICAO_MINIMA;
            MP_fimCursoAcionado = true;
            z=2;
          }
   }
   //Serial.println("2");
   //Zeramento giro do punho
   while(z == 2){
          if(digitalRead(GP_limitSwitch) == LOW and !GP_fimCursoAcionado){
            setMotorGP(-80);  
            setMotorMP(-100); 
          }
          else if(digitalRead(GP_limitSwitch) == HIGH and !GP_fimCursoAcionado){
            setMotorGP(0);
            setMotorMP(0);
            GP_encoderPos = GP_POSICAO_MINIMA;
            GP_fimCursoAcionado = true;
            z=3;
          }
   }
   //Serial.println("3");
   //Zeramento cotovelo
   //Arrumar esse em específico
   while(z == 3){
          if(digitalRead(C_limitSwitch) == LOW and !C_fimCursoAcionado){
            setMotorC(-80);
            setMotorMP(100);
            setMotorGP(-90);     
          }
          else if(digitalRead(C_limitSwitch) == HIGH and !C_fimCursoAcionado){
            setMotorC(0);
            setMotorMP(0);
            setMotorGP(0);
            C_encoderPos = C_POSICAO_MINIMA;
            C_fimCursoAcionado = true;
            z=4;
          }
   }
   //Serial.println("4");
   //Zeramento ombro
   while(z == 4){
    if(digitalRead(O_limitSwitch) == LOW and !O_fimCursoAcionado){
      setMotorO(-150);
      setMotorC(90);
      setMotorMP(-80);
      setMotorGP(80);       
    }
    else if(digitalRead(O_limitSwitch) == HIGH and !O_fimCursoAcionado){
      setMotorO(0);
      setMotorC(0);
      setMotorMP(0);
      setMotorGP(0);  
      O_encoderPos = O_POSICAO_MINIMA;
      O_fimCursoAcionado = true;
      z=5;
    }
   }
   //Serial.println("5");
}

void loop() {
  if (Serial.available()) {
    comando = Serial.readStringUntil('\n');
    comando.trim();
  }
  if (comando == "FIM") {
    z=0;
    while(z == 0){
      if(digitalRead(B_limitSwitch) == LOW){
        setMotorB(80);     
      }
      else if(digitalRead(B_limitSwitch) == HIGH){
        setMotorB(0);
        B_encoderPos = B_POSICAO_MINIMA;
        B_fimCursoAcionado = true;
        z=1;
      }
     }
     //Serial.println("1");
     //Zeramento movimento do punho
     while(z == 1){
            if(digitalRead(MP_limitSwitch) == LOW){
              setMotorMP(-80);
              setMotorGP(80);    
            }
            else if(digitalRead(MP_limitSwitch) == HIGH){
              setMotorMP(0);
              setMotorGP(0);
              MP_encoderPos = MP_POSICAO_MINIMA;
              MP_fimCursoAcionado = true;
              z=2;
            }
     }
     //Serial.println("2");
     //Zeramento giro do punho
     while(z == 2){
            if(digitalRead(GP_limitSwitch) == LOW){
              setMotorGP(-80);  
              setMotorMP(-100); 
            }
            else if(digitalRead(GP_limitSwitch) == HIGH){
              setMotorGP(0);
              setMotorMP(0);
              GP_encoderPos = GP_POSICAO_MINIMA;
              GP_fimCursoAcionado = true;
              z=3;
            }
     }
     //Serial.println("3");
     //Zeramento cotovelo
     //Arrumar esse em específico
     while(z == 3){
            if(digitalRead(C_limitSwitch) == LOW){
              setMotorC(-80);
              setMotorMP(100);
              setMotorGP(-90);     
            }
            else if(digitalRead(C_limitSwitch) == HIGH ){
              setMotorC(0);
              setMotorMP(0);
              setMotorGP(0);
              C_encoderPos = C_POSICAO_MINIMA;
              C_fimCursoAcionado = true;
              z=4;
            }
     }
     //Serial.println("4");
     //Zeramento ombro
     while(z == 4){
      if(digitalRead(O_limitSwitch) == LOW){
        setMotorO(-150);
        setMotorC(90);
        setMotorMP(-80);
        setMotorGP(80);       
      }
      else if(digitalRead(O_limitSwitch) == HIGH){
        setMotorO(0);
        setMotorC(0);
        setMotorMP(0);
        setMotorGP(0);  
        O_encoderPos = O_POSICAO_MINIMA;
        O_fimCursoAcionado = true;
        z=5;
      }
     }
   while(G_encoderPos > G_POSICAO_MINIMA)
   {
    setMotorG(80);
   }
   setMotorG(0);
   delay(150);     
   comando = "";
  }
  if (comando == "MODO_MANUAL") {
    ok = 0;
    //Serial.println("OK");
  }
  else if (comando == "MODO_AUTOMATICO") {
    ok = 1;
    //Serial.println("OK");
  }
  
  // Modo manual
  if (ok == 0)
  {
    // Movimento Linha tranversal
    if (comando == "DIREITA") {
      okk = 3;
        setMotorLT(-230);
    } 
    else if (comando == "ESQUERDA") {
      okk = 3;
      if (digitalRead(LT_limitSwitch) == LOW) {
        setMotorLT(230);
      } 
    } 
    else if (comando == "PARARL") {
      comando = "";
      setMotorLT(0);
    }
    // Movimento BASE
    if (comando == "AVANCARB") {
      okk = 4;
      if (B_encoderPos < B_POSICAO_MAXIMA) {
        setMotorB(-80);
      } else {
        setMotorB(0);
        //Serial.println(">> LIMITE MÁXIMO atingido.");
      }
    } 
    else if (comando == "RECUARB") {
      okk = 4;
      if (B_encoderPos > B_POSICAO_MINIMA) {
        setMotorB(80);
      } else {
        setMotorB(0);
        //Serial.println(">> LIMITE MÍNIMO atingido.");
      }
    } 
    else if (comando == "PARARB") {
      comando = "";
      setMotorB(0);
      enviarPosicao("B", B_encoderPos);
    }
    //Movimento ombro
    if (comando == "AVANCARO") {
      okk = 5;
      if (digitalRead(O_limitSwitch) == LOW) {
        setMotorO(-150);
        setMotorC(90);
        setMotorMP(-80);
        setMotorGP(80);  
      } else {
        setMotorO(0);
        setMotorC(0);
        setMotorMP(0);
        setMotorGP(0);
        //Serial.println(">> LIMITE MÁXIMO atingido.");
      }
    } 
    else if (comando == "RECUARO") {
      okk = 5;
      if (O_encoderPos < O_POSICAO_MAXIMA) {
        setMotorO(150);
        setMotorC(-90);
        setMotorMP(80);
        setMotorGP(-80);  
      } else {
        setMotorO(0);
        setMotorC(0);
        setMotorMP(0);
        setMotorGP(0);
        //Serial.println(">> LIMITE MÍNIMO atingido.");
      }
    } 
    else if (comando == "PARARO") {
      comando = "";
      setMotorO(0);
      setMotorC(0);
      setMotorMP(0);
      setMotorGP(0);
      enviarPosicao("O", O_encoderPos);
    }
    //Movimento cotovelo 
    //arrumar daqui pra baixo
    if (comando == "AVANCARC") {
      okk = 6;
      if (digitalRead(C_limitSwitch) == LOW) {
         setMotorC(-80);
         setMotorMP(100);
         setMotorGP(-90); 
      } else {
        C_encoderPos = C_POSICAO_MINIMA;
        setMotorC(0);
        setMotorMP(0);
        setMotorGP(0);
        //Serial.println(">> LIMITE MÁXIMO atingido.");
      }
    } 
    else if (comando == "RECUARC") {
      okk = 6;
      if (C_encoderPos < C_POSICAO_MAXIMA) {
        setMotorC(80);
        setMotorMP(-50);
        setMotorGP(50); 
      } else {
        setMotorC(0);
        setMotorMP(0);
        setMotorGP(0);
        //Serial.println(">> LIMITE MÍNIMO atingido.");
      }
    } 
    else if (comando == "PARARC") {
      comando = "";
      setMotorC(0);
      setMotorMP(0);
      setMotorGP(0);
      enviarPosicao("C", C_encoderPos);
    }
    //Movimento do punho
    if (comando == "AVANCARMP") {
      okk=1;
      if (digitalRead(MP_limitSwitch) == LOW) {
        setMotorMP(-80);
        setMotorGP(80);
      } else {
        setMotorMP(0);
        setMotorGP(0);
        MP_encoderPos = MP_POSICAO_MINIMA;
        //Serial.println(">> LIMITE MÁXIMO atingido.");
      }
    } 
    else if (comando == "RECUARMP") {
      okk=1;
      if (MP_encoderPos < MP_POSICAO_MAXIMA) {
        setMotorMP(80);
        setMotorGP(-80);
      } else {
        setMotorMP(0);
        setMotorGP(0);
        //Serial.println(">> LIMITE MÍNIMO atingido.");
      }
    } 
    else if (comando == "PARARMP") {
      comando = "";
      setMotorMP(0);
      setMotorGP(0);
      enviarPosicao("MP", MP_encoderPos);
    }
    //Giro do punho
    if (comando == "AVANCARGP") {
      okk=2;
      if (digitalRead(GP_limitSwitch) == LOW) {
        setMotorGP(-80);
        setMotorMP(-90);
      } else {
        GP_encoderPos = GP_POSICAO_MINIMA;
        setMotorGP(0);
        setMotorMP(0);
        //Serial.println(">> LIMITE MÁXIMO atingido.");
      }
    } 
    else if (comando == "RECUARGP") {
      okk=2;
      if (GP_encoderPos < GP_POSICAO_MAXIMA) {
        setMotorGP(80);
        setMotorMP(90);
      } else {
        setMotorGP(0);
        setMotorMP(0);
       // Serial.println(">> LIMITE MÍNIMO atingido.");
      }
    } 
    else if (comando == "PARARGP") {
      comando = "";
      setMotorGP(0);
      setMotorMP(0);
      enviarPosicao("GP", GP_encoderPos);
    }
    //Ainda arrumar a garra
    //Garra
    if (comando == "ABRIRG") {
      okk=10;
      if (G_encoderPos > G_POSICAO_MINIMA) {
        setMotorG(80);
      } else {
        setMotorG(0);
       // Serial.println(">> LIMITE MÁXIMO atingido.");
      }
    } 
    else if (comando == "FECHARG") {
      okk=10;
      if (G_encoderPos < G_POSICAO_MAXIMA) {
        setMotorG(-80);
      } else {
        setMotorG(0);
      //  Serial.println(">> LIMITE MÍNIMO atingido.");
      } 
    }
    else if (comando == "PARARG") {
      comando = "";
      setMotorG(0);
      enviarPosicao("G", G_encoderPos);
    }
    if (comando == "RESETAR"){
           z=0;
          while(z == 0){
            if(digitalRead(B_limitSwitch) == LOW){
              setMotorB(80);     
            }
            else if(digitalRead(B_limitSwitch) == HIGH){
              setMotorB(0);
              B_encoderPos = B_POSICAO_MINIMA;
              B_fimCursoAcionado = true;
              z=1;
            }
           }
           //Serial.println("1");
           //Zeramento movimento do punho
           while(z == 1){
                  if(digitalRead(MP_limitSwitch) == LOW){
                    setMotorMP(-80);
                    setMotorGP(80);    
                  }
                  else if(digitalRead(MP_limitSwitch) == HIGH){
                    setMotorMP(0);
                    setMotorGP(0);
                    MP_encoderPos = MP_POSICAO_MINIMA;
                    MP_fimCursoAcionado = true;
                    z=2;
                  }
           }
           //Serial.println("2");
           //Zeramento giro do punho
           while(z == 2){
                  if(digitalRead(GP_limitSwitch) == LOW){
                    setMotorGP(-80);  
                    setMotorMP(-100); 
                  }
                  else if(digitalRead(GP_limitSwitch) == HIGH){
                    setMotorGP(0);
                    setMotorMP(0);
                    GP_encoderPos = GP_POSICAO_MINIMA;
                    GP_fimCursoAcionado = true;
                    z=3;
                  }
           }
           //Serial.println("3");
           //Zeramento cotovelo
           //Arrumar esse em específico
           while(z == 3){
                  if(digitalRead(C_limitSwitch) == LOW){
                    setMotorC(-80);
                    setMotorMP(100);
                    setMotorGP(-90);     
                  }
                  else if(digitalRead(C_limitSwitch) == HIGH){
                    setMotorC(0);
                    setMotorMP(0);
                    setMotorGP(0);
                    C_encoderPos = C_POSICAO_MINIMA;
                    C_fimCursoAcionado = true;
                    z=4;
                  }
           }
           //Serial.println("4");
           //Zeramento ombro
           while(z == 4){
            if(digitalRead(O_limitSwitch) == LOW){
              setMotorO(-150);
              setMotorC(90);
              setMotorMP(-80);
              setMotorGP(80);       
            }
            else if(digitalRead(O_limitSwitch) == HIGH){
              setMotorO(0);
              setMotorC(0);
              setMotorMP(0);
              setMotorGP(0);  
              O_encoderPos = O_POSICAO_MINIMA;
              O_fimCursoAcionado = true;
              z=5;
            }
           }
         while(G_encoderPos > G_POSICAO_MINIMA)
         {
          setMotorG(80);
         }
         setMotorG(0);
         delay(150);     
         comando = "";
    }
  }
  else if(ok==1){
    //Base
    if (comando.startsWith("B")) {  // Verifica se o comando começa com 'B'
          okk=9;
          long pulsosB = comando.substring(1).toInt(); // Pega o número após o B
          // Movimento para frente
          if (pulsosB > B_encoderPos) {
            while (B_encoderPos < (pulsosB) && B_encoderPos < B_POSICAO_MAXIMA) {
              setMotorB(-80);
            }
          }
          // Movimento para trás
          else if (pulsosB < B_encoderPos) {
            while (B_encoderPos > (pulsosB) && digitalRead(B_limitSwitch) == LOW) {
              setMotorB(80);
            }
          }
          setMotorB(0); // Para o motor
          Serial.flush();             // garante que o buffer está limpo
          Serial.write('K');
          delay(150);     
          comando = "";
    }
    //Ombro
    if (comando.startsWith("O")) {  // Verifica se o comando começa com 'B'
          long pulsosO = comando.substring(1).toInt(); // Pega o número após o B
          okk=5;
          // Movimento para frente
          if (pulsosO > O_encoderPos) {
            while (O_encoderPos < pulsosO) {
              setMotorO(150);
              setMotorC(-90);
              setMotorMP(80);
              setMotorGP(-80); 
            }
          }
          // Movimento para trás
          else if (pulsosO < O_encoderPos) {
            while (O_encoderPos > (pulsosO) && digitalRead(O_limitSwitch) == LOW) {
              setMotorO(-150);
              setMotorC(90);
              setMotorMP(-80);
              setMotorGP(80); 
            }
          }
          setMotorO(0); // Para o motor
          setMotorC(0);
          setMotorMP(0);
          setMotorGP(0);
          Serial.flush();             // garante que o buffer está limpo
          Serial.println("OK");
          delay(150);     
          comando = "";
      }
    //Cotovelo
    //Novamente arrumar daqui pra baixo
    if (comando.startsWith("C")) {  // Verifica se o comando começa com 'B'
          okk=6;
          long pulsosC = comando.substring(1).toInt(); // Pega o número após o B
      
          // Movimento para frente
          if (pulsosC > C_encoderPos) {
            while (C_encoderPos < pulsosC && C_encoderPos < C_POSICAO_MAXIMA) {
              setMotorC(80);
              setMotorMP(-50);
              setMotorGP(50);
            }
          }
          // Movimento para trás
          else if (pulsosC < C_encoderPos) {
            while (C_encoderPos > pulsosC && digitalRead(C_limitSwitch) == LOW) {
               setMotorC(-80);
               setMotorMP(100);
               setMotorGP(-90); 
            }
          }
          setMotorMP(0);
          setMotorGP(0);
          setMotorC(0); // Para o motor
          Serial.flush();             // garante que o buffer está limpo
          Serial.write('K');
          delay(150);  
          comando = "";
      } 
    //Movimento Punho
    if (comando.startsWith("MP")) {  // Verifica se o comando começa com 'B'
          okk=1;
          long pulsosMP = comando.substring(2).toInt(); // Pega o número após o B
      
          // Movimento para frente
          if (pulsosMP > MP_encoderPos) {
            while (MP_encoderPos < pulsosMP && MP_encoderPos < MP_POSICAO_MAXIMA) {
              setMotorMP(80);
              setMotorGP(-80);
            }
          }
          // Movimento para trás
          else if (pulsosMP < MP_encoderPos) {
            while (MP_encoderPos > pulsosMP && digitalRead(MP_limitSwitch) == LOW) {
              setMotorMP(-80);
              setMotorGP(80);
            }
          }
          setMotorGP(0);
          setMotorMP(0); // Para o motor
          Serial.flush();             // garante que o buffer está limpo
          Serial.write('K');
          delay(150);    
          comando = "";
      } 
    //Giro punho
    if (comando.startsWith("GP")) {  // Verifica se o comando começa com 'B'
          okk=2;
          long pulsosGP = comando.substring(2).toInt(); // Pega o número após o B
      
          // Movimento para frente
          if (pulsosGP > GP_encoderPos) {
            while (GP_encoderPos < pulsosGP && GP_encoderPos < GP_POSICAO_MAXIMA) {
              setMotorGP(80);
              setMotorMP(90);
            }
          }
          // Movimento para trás
          else if (pulsosGP < GP_encoderPos) {
            while (GP_encoderPos > pulsosGP && digitalRead(GP_limitSwitch) == LOW) {
              setMotorGP(-80);
              setMotorMP(-90);
            }
          }
          setMotorMP(0);
          setMotorGP(0); // Para o motor
          Serial.flush();             // garante que o buffer está limpo
          Serial.write('K');
          delay(150);   
          comando = "";
      } 
    //Garra
    if (comando.startsWith("G")) {  // Verifica se o comando começa com 'B'
      okk=7;
      long pulsosG = comando.substring(1).toInt(); // Pega o número após o B
      if (pulsosG > G_encoderPos) {
            while (G_encoderPos < pulsosG && G_encoderPos < G_POSICAO_MAXIMA) {
              setMotorG(-80);
            }
          }
          // Movimento para trás
          else if (pulsosG < G_encoderPos) {
            while (G_encoderPos > pulsosG && G_encoderPos > G_POSICAO_MINIMA) {
              setMotorG(80);
          }
      }
      setMotorG(0);
      Serial.flush();             // garante que o buffer está limpo
      Serial.write('K');
      delay(150); 
      comando = "";
    } 
    //Zeramento
    if (comando.startsWith("Z")) {  // Verifica se o comando começa com 'B'
          z=0;
          while(z == 0){
            if(digitalRead(B_limitSwitch) == LOW){
              setMotorB(80);     
            }
            else if(digitalRead(B_limitSwitch) == HIGH){
              setMotorB(0);
              B_encoderPos = B_POSICAO_MINIMA;
              B_fimCursoAcionado = true;
              z=1;
            }
           }
           //Serial.println("1");
           //Zeramento movimento do punho
           while(z == 1){
                  if(digitalRead(MP_limitSwitch) == LOW){
                    setMotorMP(-80);
                    setMotorGP(80);    
                  }
                  else if(digitalRead(MP_limitSwitch) == HIGH){
                    setMotorMP(0);
                    setMotorGP(0);
                    MP_encoderPos = MP_POSICAO_MINIMA;
                    MP_fimCursoAcionado = true;
                    z=2;
                  }
           }
           //Serial.println("2");
           //Zeramento giro do punho
           while(z == 2){
                  if(digitalRead(GP_limitSwitch) == LOW){
                    setMotorGP(-80);  
                    setMotorMP(-100); 
                  }
                  else if(digitalRead(GP_limitSwitch) == HIGH){
                    setMotorGP(0);
                    setMotorMP(0);
                    GP_encoderPos = GP_POSICAO_MINIMA;
                    GP_fimCursoAcionado = true;
                    z=3;
                  }
           }
           //Serial.println("3");
           //Zeramento cotovelo
           //Arrumar esse em específico
           while(z == 3){
                  if(digitalRead(C_limitSwitch) == LOW){
                    setMotorC(-80);
                    setMotorMP(100);
                    setMotorGP(-90);     
                  }
                  else if(digitalRead(C_limitSwitch) == HIGH){
                    setMotorC(0);
                    setMotorMP(0);
                    setMotorGP(0);
                    C_encoderPos = C_POSICAO_MINIMA;
                    C_fimCursoAcionado = true;
                    z=4;
                  }
           }
           //Serial.println("4");
           //Zeramento ombro
           while(z == 4){
            if(digitalRead(O_limitSwitch) == LOW){
              setMotorO(-150);
              setMotorC(90);
              setMotorMP(-80);
              setMotorGP(80);       
            }
            else if(digitalRead(O_limitSwitch) == HIGH){
              setMotorO(0);
              setMotorC(0);
              setMotorMP(0);
              setMotorGP(0);  
              O_encoderPos = O_POSICAO_MINIMA;
              O_fimCursoAcionado = true;
              z=5;
            }
           }
         while(G_encoderPos > G_POSICAO_MINIMA)
         {
          setMotorG(80);
         }
         setMotorG(0);
 
       Serial.flush();             // garante que o buffer está limpo
       Serial.write('K');
       delay(150);     
       comando = "";
    }
  } 
  //Serial.print("Posicao: ");
  //Serial.println(B_encoderPos);
  delay(150);
}

void setMotorB(int pwm) {
  pwm = constrain(pwm, -255, 255);

  if (pwm > 0) {
    digitalWrite(B_IN1, HIGH);
    digitalWrite(B_IN2, LOW);
    analogWrite(B_ENA, pwm);
  } 
  else if (pwm < 0) {
    digitalWrite(B_IN1, LOW);
    digitalWrite(B_IN2, HIGH);
    analogWrite(B_ENA, -pwm);
  } 
  else {
    digitalWrite(B_IN1, LOW);
    digitalWrite(B_IN2, LOW);
    analogWrite(B_ENA, 0);
  }
}

void setMotorO(int pwm) {
  pwm = constrain(pwm, -255, 255);

  if (pwm > 0) {
    digitalWrite(O_IN1, HIGH);
    digitalWrite(O_IN2, LOW);
    analogWrite(O_ENA, pwm);
  } 
  else if (pwm < 0) {
    digitalWrite(O_IN1, LOW);
    digitalWrite(O_IN2, HIGH);
    analogWrite(O_ENA, -pwm);
  } 
  else {
    digitalWrite(O_IN1, LOW);
    digitalWrite(O_IN2, LOW);
    analogWrite(O_ENA, 0);
  }
}

void setMotorC(int pwm) {
  pwm = constrain(pwm, -255, 255);

  if (pwm > 0) {
    digitalWrite(C_IN1, HIGH);
    digitalWrite(C_IN2, LOW);
    analogWrite(C_ENA, pwm);
  } 
  else if (pwm < 0) {
    digitalWrite(C_IN1, LOW);
    digitalWrite(C_IN2, HIGH);
    analogWrite(C_ENA, -pwm);
  } 
  else {
    digitalWrite(C_IN1, LOW);
    digitalWrite(C_IN2, LOW);
    analogWrite(C_ENA, 0);
  }
}

void setMotorGP(int pwm) {
  pwm = constrain(pwm, -255, 255);

  if (pwm > 0) {
    digitalWrite(GP_IN1, HIGH);
    digitalWrite(GP_IN2, LOW);
    analogWrite(GP_ENA, pwm);
  } 
  else if (pwm < 0) {
    digitalWrite(GP_IN1, LOW);
    digitalWrite(GP_IN2, HIGH);
    analogWrite(GP_ENA, -pwm);
  } 
  else {
    digitalWrite(GP_IN1, LOW);
    digitalWrite(GP_IN2, LOW);
    analogWrite(GP_ENA, 0);
  }
}

void setMotorMP(int pwm) {
  pwm = constrain(pwm, -255, 255);

  if (pwm > 0) {
    digitalWrite(MP_IN1, HIGH);
    digitalWrite(MP_IN2, LOW);
    analogWrite(MP_ENA, pwm);
  } 
  else if (pwm < 0) {
    digitalWrite(MP_IN1, LOW);
    digitalWrite(MP_IN2, HIGH);
    analogWrite(MP_ENA, -pwm);
  } 
  else {
    digitalWrite(MP_IN1, LOW);
    digitalWrite(MP_IN2, LOW);
    analogWrite(MP_ENA, 0);
  }
}

void setMotorG(int pwm) {
  pwm = constrain(pwm, -255, 255);

  if (pwm > 0) {
    digitalWrite(G_IN1, HIGH);
    digitalWrite(G_IN2, LOW);
    analogWrite(G_ENA, pwm);
  } 
  else if (pwm < 0) {
    digitalWrite(G_IN1, LOW);
    digitalWrite(G_IN2, HIGH);
    analogWrite(G_ENA, -pwm);
  } 
  else {
    digitalWrite(G_IN1, LOW);
    digitalWrite(G_IN2, LOW);
    analogWrite(G_ENA, 0);
  }
}

void setMotorLT(int pwm) {
  pwm = constrain(pwm, -255, 255);

  if (pwm > 0) {
    digitalWrite(LT_IN1, HIGH);
    digitalWrite(LT_IN2, LOW);
    analogWrite(LT_ENA, pwm);
  } 
  else if (pwm < 0) {
    digitalWrite(LT_IN1, LOW);
    digitalWrite(LT_IN2, HIGH);
    analogWrite(LT_ENA, -pwm);
  } 
  else {
    digitalWrite(LT_IN1, LOW);
    digitalWrite(LT_IN2, LOW);
    analogWrite(LT_ENA, 0);
  }
}
// ---- FUNÇÃO ENCODER
void LT_updateEncoder() {
  if (digitalRead(B_encoderPinB) == HIGH) {
    LT_encoderPos--;
  } else {
    LT_encoderPos++;
  }
}


void B_updateEncoder() {
  if (digitalRead(B_encoderPinB) == HIGH) {
    B_encoderPos--;
  } else {
    B_encoderPos++;
  }
}

void O_updateEncoder() {
  if(okk == 5){
    if (digitalRead(O_encoderPinB) == HIGH) {
      O_encoderPos++;
    } else {
      O_encoderPos--;
    }
  }
}

void C_updateEncoder() {
  if(okk == 6){
    if (digitalRead(C_encoderPinB) == HIGH) {
      C_encoderPos++;
    } else {
      C_encoderPos--;
    }
  }
}

void GP_updateEncoder() {
  if(okk == 2){
    if (digitalRead(GP_encoderPinB) == HIGH) {
      GP_encoderPos++;
    } else {
      GP_encoderPos--;
    }
  }
}

void MP_updateEncoder() {
  if(okk == 1){
    if (digitalRead(MP_encoderPinB) == HIGH) {
      MP_encoderPos++;
    } else {
      MP_encoderPos--;
    }
  }
}

void G_updateEncoder() {
  if (digitalRead(G_encoderPinB) == HIGH) {
    G_encoderPos++;
  } else {
    G_encoderPos--;
  }
}
void enviarPosicao(String eixo, long valor) {
  Serial.print(eixo);
  Serial.println(valor);
}
