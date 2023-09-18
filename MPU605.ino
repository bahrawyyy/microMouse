
#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

#define IN1 25
#define IN2 33
// Left
#define IN3 18
#define IN4 5

#define ENA 32
#define ENB 19


float angle = 0.0, rawAngle = 0.0;

bool isTurning = true;          // Flag to control turning state


void Stop(void) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void Right(void) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.begin();
  mpu.calcOffsets();  // Initial sensor calibration
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  analogWrite(ENA, 155);
  analogWrite(ENB, 165);
  pinMode(2, OUTPUT);

}

void resetMPUFIFO() {
  Wire.beginTransmission(0x68);  // Address of the MPU6050
  Wire.write(0x6A);              // I2C Master Control register address
  Wire.write(0x42);              // Reset FIFO
  Wire.endTransmission();
}

const int readingsBeforeClearing = 100;  // Change this as needed
int readingsCount = 0;                    // Counter to keep track of readings

void loop() {
  mpu.update();
  rawAngle = mpu.getAngleZ();


  angle = abs(rawAngle);

  

  // Debug information
  Serial.print("Angle: ");
  Serial.println(angle);


  if(angle<90)
  {
    Right();
  }else{
    Stop();
  }

  readingsCount++;  // Increment the readings count

  // Check if it's time to reset the FIFO
  if (readingsCount >= readingsBeforeClearing) {
    resetMPUFIFO();     // Reset the FIFO
    readingsCount = 0;  // Reset the readings count
  }

  // Control loop timing, adjust as needed
  delay(10);
}

