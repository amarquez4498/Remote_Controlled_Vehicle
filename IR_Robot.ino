#include <IRremote.h>
int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define PWM_A_Pin 3
#define Dir_A_Pin 12
#define Brake_Pin 9

#define PWM_B_Pin 11
#define Dir_B_Pin 13
#define Brake_Pin_B 8

const bool forwardA = HIGH;
const bool backwardA = LOW;
const bool forwardB = HIGH;
const bool backwardB = LOW;



void go_fordward()
{
  digitalWrite(Brake_Pin, LOW); //Eengage the Brake for Channel A
  digitalWrite(Brake_Pin_B, LOW); //Eengage the Brake for Channel B
  digitalWrite(Dir_A_Pin, backwardA); //Establishes forward direction of Channel A
  analogWrite(PWM_A_Pin, 255);
  digitalWrite(Dir_B_Pin, forwardB); //Establishes forward direction of Channel B
  analogWrite(PWM_B_Pin, 255);

  
  irrecv.resume();
  loop();
}

void speedUp()
{
  digitalWrite(Brake_Pin_B, LOW); //Establishes forward direction of Channel A
  digitalWrite(Brake_Pin, LOW); //Establishes forward direction of Channel A
  digitalWrite(Dir_A_Pin, backwardA); //Establishes forward direction of Channel A
  analogWrite(PWM_A_Pin, 255);
  digitalWrite(Dir_B_Pin, forwardB); //Establishes forward direction of Channel B
  analogWrite(PWM_B_Pin, 255);
  irrecv.resume();
  loop();

}

void go_back()
{
  digitalWrite(Brake_Pin_B, LOW); //Establishes forward direction of Channel A
  digitalWrite(Brake_Pin, LOW); //Establishes forward direction of Channel A
  digitalWrite(Dir_A_Pin, forwardA); //Establishes forward direction of Channel A
  analogWrite(PWM_A_Pin, 255);
  digitalWrite(Dir_B_Pin, backwardB); //Establishes forward direction of Channel B
  analogWrite(PWM_B_Pin, 255);

  irrecv.resume();
  loop();
}

void turnLeft()
{
  digitalWrite(Dir_A_Pin, backwardA); //Establishes forward direction of Channel A
  analogWrite(PWM_A_Pin, 255);
  digitalWrite(Dir_B_Pin, forwardB); //Establishes forward direction of Channel B
  analogWrite(PWM_B_Pin, 0);
  delay(250);

  digitalWrite(Dir_A_Pin, backwardA); //Establishes forward direction of Channel A
  analogWrite(PWM_A_Pin, 255);
  digitalWrite(Dir_B_Pin, forwardB); //Establishes forward direction of Channel B
  analogWrite(PWM_B_Pin, 255);

  delay (1000);

  irrecv.resume();
  loop();
}

void turnRight()
{
  digitalWrite(Dir_A_Pin, backwardA); //Establishes forward direction of Channel A
  analogWrite(PWM_A_Pin, 0);
  digitalWrite(Dir_B_Pin, forwardB); //Establishes forward direction of Channel B
  analogWrite(PWM_B_Pin, 255);

  delay(250);

  digitalWrite(Dir_A_Pin, backwardA); //Establishes forward direction of Channel A
  analogWrite(PWM_A_Pin, 255);
  digitalWrite(Dir_B_Pin, forwardB); //Establishes forward direction of Channel B
  analogWrite(PWM_B_Pin, 255);

  delay (1000);

  irrecv.resume();
  loop();
}

void stop_now()
{
  digitalWrite(Brake_Pin, HIGH); //Eengage the Brake for Channel A
  digitalWrite(Brake_Pin_B, HIGH); //Eengage the Brake for Channel B
  irrecv.resume();
  loop();
}

void wall_avoidance()
{
  digitalWrite(Dir_A_Pin, backwardA); //Establishes forward direction of Channel A
  analogWrite(PWM_A_Pin, 0);
  digitalWrite(Dir_B_Pin, forwardB); //Establishes forward direction of Channel B
  analogWrite(PWM_B_Pin, 255);

  delay(500);
  irrecv.resume();
  go_fordward();
}



void setup()
{
  pinMode(Dir_A_Pin, OUTPUT); //Initiates Motor Channel A pin
  pinMode(Brake_Pin, OUTPUT); //Initiates Brake Channel A pin
  pinMode(Dir_B_Pin, OUTPUT); //Initiates Motor Channel A pin
  pinMode(Brake_Pin_B, OUTPUT); //Initiates Brake Channel A pin
  pinMode(Brake_Pin, OUTPUT); //Initiates Brake Channel A pin
  irrecv.enableIRIn(); // Start the receiver
  Serial.begin(9600);   //initializing serial port, Bluetooth used as serial port, setting baud ratio at 9600
}

void loop()
{

  if (irrecv.decode(&results)) //judging if serial port receives data
  {
    if (irrecv.decode(&results)) //if the ir receiver module receiver data
  { 
    if(results.value == 0xFF30CF) // key 1
    {
      go_fordward();
      irrecv.resume();
    }
    else if(results.value == 0xFF6897) // key 0
    {
      stop_now();
      irrecv.resume();
    }
    else if(results.value == 0xFFC23D) // >>   //Used if and if else conditions inside the above if condition 
    { 
      turnLeft();
      irrecv.resume();                                  
    }
    else if(results.value == 0xFF02FD) // <<
    {
      turnRight();
      irrecv.resume();
    }
    else if(results.value == 0xFF906F) // +
    {
      speedUp();
      irrecv.resume();
    }
    else if(results.value == 0xFFA857) // - 
    {
      go_back();
      irrecv.resume();
    }
    else if(results.value == 0xFF18E7) // - 
    {
      wall_avoidance();
      irrecv.resume();
    }
    
    irrecv.resume(); // Receive the next value 
  }
  }
}
