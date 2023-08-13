/* Names: Mona Afshar, Shenelle Jayakody, Leo Farb
    Date: 04/18/2023
    Teacher: Mr. Wong
    Description: This code is for the sumobot to be able to detect when its going to fall off the board, moving forward, backward and finding the other robot.
    It will also be able to attack other robots to push them off the board.
*/

//distance sensors
const int frontDistTrig = 4;
const int frontDistEcho = 5;
const int backDistTrig = 2;
const int backDistEcho = 3;

//motor
const int leftMotorForward = 6;
const int leftMotorBackward = 9;
const int rightMotorForward = 10;
const int rightMotorBackward = 11;

//when computer port is on left side
const int frontLight = A0; //top right on board
const int backLight = A2; //top left on board
const int leftLight = A3; //bottom right on board
const int rightLight = A5; //bottom left on board

const int ledRight = 8; //BOTTOM RIGHT
const int ledLeft = 12; //TOP RIGHT
const int ledFront = 13; //TOP LEFT
const int ledBack = 7; //BOTTOM LEFT

long duration;
int distanceCm;

const int colour = 140;
void setup()
{
  pinMode(leftMotorForward , OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);

  pinMode(frontDistTrig, OUTPUT);
  pinMode(frontDistEcho, INPUT);
  pinMode(backDistTrig, OUTPUT);
  pinMode(backDistEcho, INPUT);

  pinMode(frontLight, INPUT);
  pinMode(leftLight, INPUT);
  pinMode(rightLight, INPUT);
  pinMode(backLight, INPUT);

  pinMode(ledRight, OUTPUT);
  pinMode(ledLeft, OUTPUT);
  pinMode(ledFront, OUTPUT);
  pinMode(ledBack, OUTPUT);

  Serial.begin(9600);
}
void loop()
{
  detectColour();
  if (sendForwardUltrasonic() < 10)
    attackForward();
  else if (sendForwardUltrasonic() < 50)
    moveForward();
  else
    locate();
}

void detectColour() {
  if (analogRead (frontLight) > (colour - 100)) {
    moveBackward();
    digitalWrite(ledFront, HIGH);
    digitalWrite(ledBack, LOW);
    digitalWrite(ledLeft, LOW);
    digitalWrite(ledRight, LOW);
  }
  else if (analogRead (backLight) > colour) {
    moveForward();
    digitalWrite(ledFront, LOW);
    digitalWrite(ledBack, HIGH);
    digitalWrite(ledLeft, LOW);
    digitalWrite(ledRight, LOW);
  }
  else if (analogRead (leftLight) > colour) {
    moveRight();
    digitalWrite(ledFront, LOW);
    digitalWrite(ledBack, LOW);
    digitalWrite(ledLeft, HIGH);
    digitalWrite(ledRight, LOW);
  }
  else if (analogRead (rightLight) > (colour-10)) {
    moveLeft();
    digitalWrite(ledFront, LOW);
    digitalWrite(ledBack, LOW);
    digitalWrite(ledLeft, LOW);
    digitalWrite(ledRight, HIGH);
  }

}

int sendForwardUltrasonic() {
  digitalWrite(frontDistTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(frontDistTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(frontDistTrig, LOW);
  duration = pulseIn(frontDistEcho, HIGH);
  distanceCm = duration * 0.034 / 2;
  return distanceCm;
}

int sendBackwardUltrasonic() {
  digitalWrite(backDistTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(backDistTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(backDistTrig, LOW);
  duration = pulseIn(backDistEcho, HIGH);
  distanceCm = duration * 0.034 / 2;
  return distanceCm;
}

void moveForward() {
  analogWrite(rightMotorForward, 100);
  analogWrite(leftMotorForward, 140);
  analogWrite(leftMotorBackward, 0);
  analogWrite(rightMotorBackward, 0);
}

void attackForward() {
  analogWrite(rightMotorForward, 255);
  analogWrite(leftMotorForward, 255);
  analogWrite(leftMotorBackward, 0);
  analogWrite(rightMotorBackward, 0);
}

void moveBackward() {
  analogWrite(leftMotorForward, 0);
  analogWrite(rightMotorForward, 0);
  analogWrite(leftMotorBackward, 255);//160
  analogWrite(rightMotorBackward, 255);//150
}

void moveRight() {
  analogWrite(leftMotorForward, 255);//was 100
  analogWrite(rightMotorForward, 0);
  analogWrite(leftMotorBackward, 0);
  analogWrite(rightMotorBackward, 255);//was 90
}

void locate() {
  analogWrite(leftMotorForward, 150);//was 100
  analogWrite(rightMotorForward, 0);
  analogWrite(leftMotorBackward, 0);
  analogWrite(rightMotorBackward, 100);//was 90
}

void moveLeft() {
  analogWrite(leftMotorForward, 0);
  analogWrite(rightMotorForward, 255);//was 77
  analogWrite(leftMotorBackward, 255);//was 100
  analogWrite(rightMotorBackward, 0);
}

void stopAll() {
  analogWrite(leftMotorForward, 0);
  analogWrite(rightMotorForward, 0);
  analogWrite(leftMotorBackward, 0);
  analogWrite(rightMotorBackward, 0);
}
