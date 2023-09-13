#include "API.h"


static volatile int lState;
static volatile int cuState;
float distanceLeft = 0.0,distanceRight = 0.0;
unsigned long debounceTime = 25; // Adjust as needed (milliseconds)
unsigned long lastDebounceMillis = 0;


volatile long encoderPositionLeft=0,encoderPositionRight=0;

void Forward(void)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
 
}
void Stop(void)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void Right(void)
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA,200);
  analogWrite(ENB,210);
}

void Left(void)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA,200);
  analogWrite(ENB,210);
}

bool wallFront() {
  return digitalRead(IR_Front);
}

bool wallRight() {
  return digitalRead(IR_Right);
}


bool wallLeft() {
  return digitalRead(IR_Left);
}



// Using encoders
void moveForward() {
  distanceLeft = encoderPositionLeft * distancePerCount;
  distanceRight = encoderPositionRight * distancePerCount;
  while((distanceLeft < 9) || (distanceRight < 9)){
    Forward();
  distanceLeft = encoderPositionLeft * distancePerCount;
  distanceRight = encoderPositionRight * distancePerCount;
  }
  Stop();
}



void turnRight() {
    Right();
    delay(100);
}



void turnLeft() {
    Left();
    delay(100);
}




int orientation(int orient, char turning)
{

  if (turning== 'L'){

    orient-=1;

    if (orient==-1)

      orient=3;

  }else if(turning== 'R'){

    orient+=1;

    if (orient==4)

      orient=0;

  }else if(turning== 'B'){

    if (orient==0)

      orient=2;

    else if(orient==1)

      orient=3;

    else if(orient==2)

      orient=0;

    else if (orient==3)

      orient=1;

  }

    return orient;

}



void updateCoordinates(int orient, int *new_x, int *new_y)

{

  if(orient == 0)
    *new_y += 1;
  else if(orient == 1)
    *new_x += 1;
  else if(orient == 2)
    *new_y -= 1;
  else if(orient == 3)
    *new_x -= 1;

}






void readEncoderLeft() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - lastDebounceMillis >= debounceTime) {
    cuState = digitalRead(encoderLeft);
  
    if (cuState == HIGH && lState == LOW) {
      encoderPositionLeft++;
    }
    
    lastDebounceMillis = currentMillis;
  }
  
  lState = cuState;
}



void readEncoderRight() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - lastDebounceMillis >= debounceTime) {
    cuState = digitalRead(encoderRight);
  
    if (cuState == HIGH && lState == LOW) {
      encoderPositionRight++;
    }
    
    lastDebounceMillis = currentMillis;
  }
  
  lState = cuState;
}