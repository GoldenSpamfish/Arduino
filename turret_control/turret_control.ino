// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0;  // analog pin connected to X output
const int Y_pin = 1;  // analog pin connected to Y output
#define A 11
#define B 10
#define C 9
#define D 8
 
#define NUMBER_OF_STEPS_PER_REV 512
double serv=10; //servo home
int dir;
double servspeed;

#include <Servo.h>
#include <Stepper.h>

Servo servX;

void setup()
{
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);

  servX.attach(13); //connect pin 9 with the control line(the middle line of Servo)

  servspeed = 0.5;
  Serial.println("Ready");
}

void write(int a,int b,int c,int d){
digitalWrite(A,a);
digitalWrite(B,b);
digitalWrite(C,c);
digitalWrite(D,d);
}

// very simple stepper motor control
void Rstep(){
write(1,0,0,0);
delay(5);
write(1,1,0,0);
delay(5);
write(0,1,0,0);
delay(5);
write(0,1,1,0);
delay(5);
write(0,0,1,0);
delay(5);
write(0,0,1,1);
delay(5);
write(0,0,0,1);
delay(5);
write(1,0,0,1);
delay(5);
}

void Lstep(){
write(1,0,0,1);
delay(5);
write(0,0,0,1);
delay(5);
write(0,0,1,1);
delay(5);
write(0,0,1,0);
delay(5);
write(0,1,1,0);
delay(5);
write(0,1,0,0);
delay(5);
write(1,1,0,0);
delay(5);
write(1,0,0,0);
delay(5);
}

void loop()
{
  if (analogRead(Y_pin) > 540)
    {
    Lstep();
    }
    
  else if (analogRead(Y_pin) < 460)
    {
      Rstep();
    }

  if ((analogRead(X_pin) > 540) && serv < 110)
  {
    serv += servspeed;
  }

  else if ((analogRead(X_pin) < 460) && serv > 0.5)
  {
    serv = serv - servspeed;
  }

  servX.write(serv);

  //text output
  Serial.print("JoyX:");             Serial.print(analogRead(X_pin));
  Serial.print("         Serv:");    Serial.print(serv);
  Serial.print("         JoyY:");    Serial.print(analogRead(Y_pin));
  Serial.print("         StepDir:"); Serial.println(dir);

  delay(2);
}
