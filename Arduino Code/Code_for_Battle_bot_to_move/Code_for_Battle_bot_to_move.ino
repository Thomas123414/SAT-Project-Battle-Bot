#include <Servo.h>

/**
 * Motor shield (L298N) 
 */
const int ENA = 5; // Port 5: Enable A
const int ENB = 6; // Port 6: Enable B
// IN1: 5v; IN2: GND -> Motor A Direction 1
// IN1: GND; IN2: 5v -> Motor A Direction 2
const int IN1 = 2; 
const int IN2 = 3;
// IN3: 5v; IN4: GND -> Motor B Direction 1
// IN3: GND; IN4: 5V -> Motor B Direction 2
const int IN3 = 4;
const int IN4 = 7;
// PWM
const int PWM255 = 255;
const int PWM128 = 128;
// Constants
const int D = 1;
const int timeDelay = 30;
/**
 * Global Variables
 */
char incomingByte;
bool stopFlag = false;

void setup() {
  // put your setup code here, to run once:
// Motor
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  // Serial
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available() > 0)
  {
    //Bluetooth Command
    incomingByte = Serial.read();
    Serial.println(incomingByte);
    switch(incomingByte)
    {
    case 'f':
      if(!stopFlag) {
        Forward();
      }
      break;
    case 'b':
      Backward();
      break;
    case 'l':
      if(!stopFlag) {
        Left(PWM255);
      }
      else
      {
        Left(PWM128);
      }
      break;
    case 'r':
     if(!stopFlag) {
        Right(PWM255);
      }
      else
      {
        Right(PWM128);
      }
      break;
    default:
      StopMove();
      break;  
    } //Switch
  }
}

/** 
 * Forward
 */
void Forward()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  for (int x = 0; x < 256; x++)   // Motor will accelerate from 0 to maximum speed
  {
    analogWrite(ENA, x);
    analogWrite(ENB, x);
    delay(20);
  } 
}

/** 
 * Backward
 */
void Backward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  for (int x = 0; x < 256; x++)   // Motor will accelerate from 0 to maximum speed
  {
    analogWrite(ENA, x);
    analogWrite(ENB, x);
    delay(20);
  } 
}

/** 
 * Left
 */
void Left(int pwm)
{
  analogWrite(ENA, pwm);
  analogWrite(ENB, pwm);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

/**
 * Right
 */
void Right(int pwm)
{
  analogWrite(ENA, pwm);
  analogWrite(ENB, pwm);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

/** 
 * Break
 */
void Brake()
{
  for (int y = 255; y >= 0; --y)  // Motor will decelerate from maximum speed to 0
  {
    analogWrite(ENA, y);
    analogWrite(ENB, y);
    delay(20);
  } 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  delay(timeDelay);
}

void StopMove()
{
  analogWrite(ENA, PWM255);
  analogWrite(ENB, PWM255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

