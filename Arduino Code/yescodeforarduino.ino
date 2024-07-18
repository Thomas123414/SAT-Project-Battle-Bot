#include <SoftwareSerial.h>
SoftwareSerial BT(1,0);
char val;

int motor1pin1 = 2;
int motor1pin2 = 3;
int motor2pin1 = 4;
int motor2pin2 = 5;
void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  BT.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if( BT.available() ){
    val = BT.read();
    BT.print("Reading new data: ");
    BT.println(val);
  }
  if (val < 2)
  {
    digitalWrite(motor1pin1,   LOW);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1,   LOW);
    digitalWrite(motor2pin2, LOW);
  }
  else if (val > 2)
  {
    digitalWrite(motor1pin1,   HIGH);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1,   HIGH);
    digitalWrite(motor2pin2, LOW);
  }
 /* else 
  {
    digitalWrite(motor1pin1,   LOW);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1,   LOW);
    digitalWrite(motor2pin2, LOW);
  }*/
  delay(100);
  /*digitalWrite(motor1pin1,   HIGH);
  digitalWrite(motor1pin2, LOW);
  delay(3000);

  digitalWrite(motor2pin1,   LOW);
  digitalWrite(motor2pin2, HIGH);
  delay(3000);

  digitalWrite(motor1pin1,   HIGH);
  digitalWrite(motor1pin2, LOW);
  delay(3000);

  digitalWrite(motor2pin1,   LOW);
  digitalWrite(motor2pin2, HIGH);
  delay(3000);*/
}
