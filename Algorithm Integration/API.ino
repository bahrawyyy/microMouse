#include "API.h"




float angle = 0.0, rawAngle = 0.0,prevAngle = 0.0;


void resetMPUFIFO() {
  Wire.beginTransmission(0x68);  // Address of the MPU6050
  Wire.write(0x6A);              // I2C Master Control register address
  Wire.write(0x42);              // Reset FIFO
  Wire.endTransmission();
}

const int readingsBeforeClearing = 100;  // Change this as needed
int readingsCount = 0;                    // Counter to keep track of readings

float distancePerPulse = 0.1; 
volatile long encoderCountRight = 0,encoderCountLeft = 0; 
float distanceLeft = 0.0,distanceRight = 0.0;


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
  // analogWrite(ENA,200);
  // analogWrite(ENB,210);
}

void Left(void)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

bool wallFront() {
  if( getDistance(sonar[S_MIDDLE]) < (SENSOR_LIMIT-3))
    return 1;
  else
    return 0;
}

bool wallRight() {
  if( getDistance(sonar[S_RIGHT]) < SENSOR_LIMIT)
    return 1;
  else
    return 0;
}


bool wallLeft() {
  if( getDistance(sonar[S_LEFT]) < SENSOR_LIMIT)
    return 1;
  else
    return 0;
}

// Using encoders
void moveForward() {
  encoderCountLeft = 0;
  encoderCountRight = 0;
  distanceLeft = encoderCountLeft * distancePerPulse;
  distanceRight = encoderCountRight * distancePerPulse;
  while((distanceLeft < 9) || (distanceRight < 9)){  // distance is adjustable
    Forward();
    distanceLeft = encoderCountLeft * distancePerPulse;
    distanceRight = encoderCountRight * distancePerPulse;
  }
  Stop();
}
}


// Testing before encoders

// void moveForward()
// {
//   Forward();
//   delay(1250);
// }




const float correctionFactor = 2.3; // Adjust this value as needed
const int baseSpeed = 220; // Adjust the base motor speed as needed

void turnRight() {
  Wire.begin();
  mpu.begin();
  mpu.calcOffsets();  // Initial sensor calibration
  mpu.update();
  
  rawAngle = mpu.getAngleZ();
  angle = abs(rawAngle);



  float targetAngle = prevAngle + 85.0; // Calculate the target angle
  
  while (angle < targetAngle) {
    mpu.update();
    rawAngle = mpu.getAngleZ();
    angle = abs(rawAngle);

    Serial.print("Angle: ");
    Serial.println(angle);

    // Calculate the correction factor
    float correction = (targetAngle - angle) * correctionFactor;
    

    Right();
    analogWrite(ENA, max((int)(baseSpeed + correction),100));
    analogWrite(ENB, max((int)(baseSpeed - correction),100));

  }
  
  Stop();
  
  prevAngle = angle; // Update the previous angle
}


void turnLeft() {
  Wire.begin();
  mpu.begin();
  mpu.calcOffsets();  // Initial sensor calibration
  mpu.update();
  

  rawAngle = mpu.getAngleZ();
  angle = abs(rawAngle);
  
  float targetAngle = prevAngle + 85.0; // Calculate the target angle

  while (angle < targetAngle) {
    mpu.update();
    rawAngle = mpu.getAngleZ();
    angle = abs(rawAngle);

    Serial.print("Angle: ");
    Serial.println(angle);

    // Calculate the correction factor
    float correction = (targetAngle - angle) * correctionFactor;
    

    Left();
    analogWrite(ENA, max((int)(baseSpeed + correction),100));
    analogWrite(ENB, max((int)(baseSpeed - correction),100));

  }
  
  Stop();
  
  prevAngle = angle; // Update the previous angle

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
void EncoderLeftHandler() {
  // Read the state of channel A and B
  int stateA = digitalRead(encoderLeft_A);
  int stateB = digitalRead(encoderLeft_B);
  // Determine the direction of rotation
  if (stateA == stateB) {
    encoderCountLeft++; // Clockwise rotation
  } else {
    encoderCountLeft--; // Counterclockwise rotation
  }
}
void EncoderRightHandler() {
  // Read the state of channel A and B
  int stateA = digitalRead(encoderRight_A);
  int stateB = digitalRead(encoderRight_B);
  // Determine the direction of rotation
  if (stateA == stateB) {
    encoderCountRight++; // Clockwise rotation
  } else {
    encoderCountRight--; // Counterclockwise rotation
  }
}
uint32_t getDistance(NewPing sonar){
  uint32_t sum = 0;
  for(uint8_t i = 0 ;i<AVG_NUM;i++){
    sum += sonar.ping_cm();
    delay(30);                    
  }
  return (sum/AVG_NUM);
}