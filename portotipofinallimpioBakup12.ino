#include <TimerOne.h>
#include <avr/wdt.h>
char winm[3];
#include <AccelStepper.h>
#define dirPin1 5
#define stepPin1 2
#define dirPin2 6
#define stepPin2 3
#define dirPin3 7
#define stepPin3 4
#define motorInterfaceType 1
int sube;
int baja;
int extra1;
int extra2;
int acelerarion;
bool m1;
bool m2;
boolean coridas;
AccelStepper stepper1 = AccelStepper(motorInterfaceType, stepPin1, dirPin1);
AccelStepper stepper2 = AccelStepper(motorInterfaceType, stepPin2, dirPin2);
AccelStepper stepper3 = AccelStepper(motorInterfaceType, stepPin3, dirPin3);
const int stepsPerRevolution2 = 1850;
int player1;
int digitos;
int sensorval;
const int buttonPin = 10;
int buttonState = 0;
const int sensorPin = 9;
int player0;
int player2;
int valsensorEmu;
int sensordetec=88;
boolean valsensor;
boolean completo1=false;
boolean completo2=false;
int cronometro=31;
boolean inicio=true;
boolean btn=false;
boolean msg=false;
boolean termino;
long randomNumber;
long randomNumber2;
bool tickb;
int tick=10;



void loop() {


  //Serial.println(buttonState);
  //Serial.println(buttonState);
  sensorval=digitalRead(sensorPin);
   if(btn==true){
     motores();

     if(termino==false){
      Timer1.attachInterrupt(juego3);
      }else{
        wdt_enable(WDTO_1S);
        wdt_reset(); 
        Serial.println("preciona boton para nuevo juego");

        }
    }
   
  //Serial.println(buttonState);
   //btn=true;
   buttonState = digitalRead(buttonPin);
     if(buttonState==0){
     btn=true;
    }
    if(msg==false){
      msg=true;
      msgstart();
       //Serial.println("estoy dentro del loop del msg");
      }

}
              
void timerpantalla(){

           Serial.println("  ▀▄   ▄▀ ");       
           Serial.println(" ▄█▀███▀█▄");       
           Serial.println("█▀███████▀█");      
           Serial.println("█ █▀▀▀▀▀█ █ ");     
           Serial.println("   ▀▀ ▀▀");
           delay(5000); 

  }

void msgstart(){

//Serial.println(msg);
Serial.println("          █▀▀█ █  █  █ ");
Serial.println("          █▄▄█ █  █▄▄█ ");
Serial.println("          █    ▀▀▀▄▄▄█ ");

//bolita();
       
  }
void jugador1(){   
                  
                  digitos=digitos+1;
                  cronometro=cronometro-1;// le va restando al tiempo-----------------------------------------+
                   if(cronometro<=0){//cuadno termina el tiempo termino el tiempo y cuadra el final           |
                    digitos=0;
                  completo1=true;  //  enciente esto para cuando entre a funcion juego3 no repita el juego1   |                
                  completo2=true;      // enciente esto para cuando entre a juego3 active la funcion juego2 //|
                  player1=player0;//mete la puntuacion acumulada al jugador 1   //                         // |
                  player0=0;//retesea el puntero principal para cuando entre a jugador 2 este en 0 puntos //  |
                  cronometro=30;// el tiempo pero no me acuerdo como es qeu funciona
                  int var = 0;
                   while (var < 10) {
                   

                      timerpantalla();
                      
                      var++; 
                      
                    }
                                                                                      
                   }                                                                               
              
               Serial.println(player0);
                 
                 
                  
                  digitospantalla();  
                                                     
              
               
               if (sensordetec == 2) { //aqui esta la variable no volatil que hablaba //if (sensordetec == 2 && inicio == true)  //(sensordetec == 2)
               player0 = player0 + 10;
               
               sensordetec = 888; //la reseteo  porque 888 pues no importa valor que sea siempre y cuando no sea 2 que ese fue que establesi como


         
          if(player0==100){ //si acumula los 100 puntos cuadra final
            player1=player0;
            player0=0;
            completo1=true;
            digitos=0;
            

            }
          }

          
  }



  void jugador2(){
                   digitos=digitos+1;
                  cronometro=cronometro-1;
                   if(cronometro<=0){ //se acaba tiempo y cuadra puntuacion finales 
                  //completo1=true;
                  player2=player0;
                  player0=0;
                  completo2=false; // activa esto para que cuando entre a juego3 no repita el jugador2
                   }
               
                //Serial.println("cronometro");
               // Serial.println(cronometro);
               //Serial.println("jugador2");
               Serial.println(player0);

                 // Serial.println(digitos);
                  digitospantalla();
               
               if (sensordetec == 2) { //aqui esta la variable no volatil que hablaba //if (sensordetec == 2 && inicio == true)  //(sensordetec == 2)
               player0 = player0 + 10;
               
               sensordetec = 888; //la reseteo  porque 888 pues no importa valor que sea siempre y cuando no sea 2 que ese fue que establesi como

          if(player0==100){
            player1=player0;
            player0=0;
            completo2=true;
            digitos=0;
            }
          }
  }

  void juego3(){
         
         if(completo1==false){
        jugador1();
        }


       
        if(completo2==true ){
          jugador2();
          }
               
              
          
            if(btn==true){
            if((completo1==true && completo2==false)){
            btn=false;
           if(player1==player2){
            //Serial.println("empate");
            empate();
            termino=true;
          
            }
         
          if(player1>player2){
            winMSG();
            d1();
            termino=true;
            }

            if(player2>player1){
            winMSG();
            d2();
            termino=true;
            }
         
          }
              }

        //}else{
          // Serial.println("Presiona S para start");
          // Serial.println(buttonState);
         
         // }

    }        


void motores(){
Timer1.attachInterrupt(juego3);
  if(m1==false){
     ramdom();
     m1f();
    }
    if(m1==true){
       m2f();
      }
  }

  void lectura(){
  Serial.println(stepper1.currentPosition());
  }
void m1f(){
  stepper1.setSpeed(acelerarion);
  stepper1.moveTo(baja);
  stepper1.runSpeedToPosition(); 
  stepper2.setSpeed(acelerarion);
  stepper2.moveTo(baja);
  stepper2.runSpeedToPosition();  
  stepper3.setSpeed(acelerarion);
  stepper3.moveTo(baja);
  stepper3.runSpeedToPosition();  
    sensorval=digitalRead(sensorPin);
    debugsensor();
  if(stepper1.currentPosition()==baja){
    m1=true;
    coridas=false;
    }
  }
  void m2f(){
  stepper1.setSpeed(acelerarion);
  stepper1.moveTo(sube);
  stepper1.runSpeedToPosition(); 
  stepper2.setSpeed(acelerarion);
  stepper2.moveTo(sube);
  stepper2.runSpeedToPosition(); 
  stepper3.setSpeed(acelerarion);
  stepper3.moveTo(sube);
  stepper3.runSpeedToPosition(); 
    sensorval=digitalRead(sensorPin);
    debugsensor();
    if(stepper1.currentPosition()==sube){
    m1=false;
    coridas=false;
    }  
    }
   
void debugsensor(){
 buttonState = digitalRead(buttonPin);
 valsensor = digitalRead(sensorPin); //guarda valor de sensor a tiempo real en valsensor el sensor algo raro pq leee alreves false para detecto true //para detecta nada
if(valsensor==false){ //el sensor detecta el objeto su deteccion es false para que detecto
  sensordetec=2;
  }
}


void ramdom(){
 if(coridas==false){
     extra1=random(1,50);
     baja= random(100, 1000);
     sube= random(0, extra1);
     
     acelerarion = random(300, 600);
     coridas=true;
      }
  }

void setup() {
  wdt_disable();
   // Declare pins as Outputs
   stepper1.setMaxSpeed(1000);
   stepper2.setMaxSpeed(1000);
   stepper3.setMaxSpeed(1000);
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  pinMode(buttonPin, INPUT);

  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(sensorPin, INPUT);  //definir pin como entrada
  Timer1.initialize(1000000);//el timer que hace correr el juego a 1 segundo

  //wdt_enable(WDTO_1S);
}

void sensor(){
  valsensor = digitalRead(sensorPin);
  if(valsensor=0){
       sensordetec=true;
    }
  }

void d1(){
Serial.println("▄█ ");
Serial.println(" █ ");
Serial.println("▄█▄");
}
void d2(){
Serial.println("█▀█");
Serial.println(" ▄▀");
Serial.println("█▄▄");
}
void d3(){
Serial.println("█▀▀█");
Serial.println("  ▀▄");
Serial.println("█▄▄█");
}
void d4(){
Serial.println(" █▀█ ");
Serial.println("█▄▄█▄");
Serial.println("   █ ");
}
void d5(){
Serial.println("█▀▀");
Serial.println("▀▀▄");
Serial.println("▄▄▀");
}
void d6(){
Serial.println("▄▀▀▄");
Serial.println("█▄▄ ");
Serial.println("▀▄▄▀");
}
void d7(){
Serial.println("▀▀▀█");
Serial.println("  █ ");
Serial.println(" ▐▌ ");
}

void d8(){
Serial.println("▄▀▀▄");
Serial.println("▄▀▀▄");
Serial.println("▀▄▄▀");
}
void d9(){
Serial.println("▄▀▀▄");
Serial.println("▀▄▄█ ");
Serial.println(" ▄▄▀");
}
void d10(){
Serial.println("▄█ █▀▀█");
Serial.println(" █ █   █");
Serial.println("▄█▄█▄▄█");
}

void d11(){
Serial.println("▄█ ▄█ ");
Serial.println(" █  █ ");
Serial.println("▄█▄▄█▄");
}
void d12(){
Serial.println("▄█ █▀█");
Serial.println(" █  ▄▀");
Serial.println("▄█▄█▄▄");
}
void d13(){
Serial.println("▄█ █▀▀█");
Serial.println(" █   ▀▄");
Serial.println("▄█▄█▄▄█");
}
void d14(){
Serial.println("▄█  █▀█ ");
Serial.println(" █ █▄▄█▄");
Serial.println("▄█▄   █ ");
}
void d15(){
Serial.println("▄█ █▀▀");
Serial.println(" █ ▀▀▄");
Serial.println("▄█▄▄▄▀");
}
void d16(){
Serial.println("▄█ ▄▀▀▄");
Serial.println(" █ █▄▄ ");
Serial.println("▄█▄▀▄▄▀");
}
void d17(){
Serial.println("▄█ ▀▀▀█");
Serial.println(" █   █ ");
Serial.println("▄█▄ ▐▌ ");
}

void d18(){
Serial.println("▄█ ▄▀▀▄");
Serial.println(" █ ▄▀▀▄");
Serial.println("▄█▄▀▄▄▀");
}
void d19(){
Serial.println("▄█ ▄▀▀▄");
Serial.println(" █ ▀▄▄█ ");
Serial.println("▄█▄ ▄▄▀");
}
void d20(){
Serial.println("█▀█ █▀▀█");
Serial.println(" ▄▀ █  █");
Serial.println("█▄▄ █▄▄█");
}


void d21(){
Serial.println("█▀█ ▄█ ");
Serial.println(" ▄▀  █ ");
Serial.println("█▄▄▄ █▄");
}
void d22(){
Serial.println("█▀█ █▀█");
Serial.println(" ▄▀  ▄▀");
Serial.println("█▄▄ █▄▄");
}
void d23(){
Serial.println("█▀█ █▀▀█");
Serial.println(" ▄▀   ▀▄");
Serial.println("█▄▄ █▄▄█");
}
void d24(){
Serial.println("█▀█  █▀█ ");
Serial.println(" ▄▀ █▄▄█▄");
Serial.println("█▄▄    █ ");
}
void d25(){
Serial.println("█▀█ █▀▀");
Serial.println(" ▄▀ ▀▀▄");
Serial.println("█▄▄ ▄▄▀");
}
void d26(){
Serial.println("█▀█ ▄▀▀▄");
Serial.println(" ▄▀ █▄▄ ");
Serial.println("█▄▄ ▀▄▄▀");
}
void d27(){
Serial.println("█▀█ ▀▀▀█");
Serial.println(" ▄▀   █ ");
Serial.println("█▄▄  ▐▌ ");
}

void d28(){
Serial.println("█▀█ ▄▀▀▄");
Serial.println(" ▄▀ ▄▀▀▄");
Serial.println("█▄▄ ▀▄▄▀");
}
void d29(){
Serial.println("█▀█ ▄▀▀▄");
Serial.println(" ▄▀ ▀▄▄█ ");
Serial.println("█▄▄  ▄▄▀");
}
void d30(){
Serial.println("█▀▀█ █▀▀█");
Serial.println("  ▀▄ █  █");
Serial.println("█▄▄█ █▄▄█");
}

void digitospantalla(){
  
                      if(digitos==1){
                      d1();
                      }
                      if(digitos==2){
                      d2();
                      }
                      if(digitos==3){
                      d3();
                      }
                      if(digitos==4){
                      d4();
                      }
                      if(digitos==5){
                      d5();
                      }
                      if(digitos==6){
                      d6();
                      }
                      if(digitos==7){
                      d7();
                      }
                      if(digitos==8){
                      d8();
                      }
                      if(digitos==9){
                      d9();
                      }
                      if(digitos==10){
                      d10();
                      }
                      if(digitos==11){
                      d11();
                      }                      
                      if(digitos==12){
                      d12();
                      }                   
                      if(digitos==13){
                      d13();
                      }                  
                         if(digitos==14){
                      d14();
                      }

                      if(digitos==15){
                      d15();
                      }

                      if(digitos==16){
                      d16();
                      }

                      if(digitos==17){
                      d17();
                      }

                      if(digitos==18){
                      d18();
                      }

                      if(digitos==19){
                      d19();
                      }

                       if(digitos==20){
                      d20();
                      }

                      if(digitos==21){
                      d21();
                      }
                       if(digitos==22){
                      d22();
                      }                                          
                      if(digitos==23){
                      d23();
                      }

                      if(digitos==24){
                      d24();
                      }

                      if(digitos==25){
                      d25();
                      }

                      if(digitos==26){
                      d26();
                      }

                      if(digitos==27){
                      d27();
                      }

                      if(digitos==28){
                      d28();
                      }


                       if(digitos==29){
                      d29();
                      }                     
                                            
                         if(digitos==30){
                      d30();
                      }
  
  }

  void empate(){
 Serial.println("EMPATE");
  
    }

      void winMSG(){
Serial.println("█   █ ▀█▀  █▄  █"); 
Serial.println("█ █ █  █   █ █ █");
Serial.println("█▄▀▄█ ▄█▄  █  ▀█");


        }
    
