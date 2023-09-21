#ifndef API_H_
#define API_H_
#include <string>
#include <NewPing.h>

#include <Wire.h>
#include <MPU6050_light.h>

// MPU6050
MPU6050 mpu(Wire);





// Pin definitions
/*****************Motors**************/
// Right
#define ENA             19
#define IN1             18
#define IN2             5
// Left     
#define ENB             32
#define IN3             25
#define IN4             33
/*****************UltraSonic**************/
#define  S_RIGHT          0
#define  S_MIDDLE         1
#define  S_LEFT           2

#define MAX_DISTANCE    500
#define AVG_NUM         5

#define ECHO_R          15 
#define TRIGGER_R       4

#define ECHO_M          17
#define TRIGGER_M       16

#define ECHO_L          26
#define TRIGGER_L       27

#define SENSOR_LIMIT    8


NewPing sonar[3] = {NewPing(TRIGGER_R, ECHO_R, MAX_DISTANCE),
                    NewPing(TRIGGER_M, ECHO_M, MAX_DISTANCE),
                    NewPing(TRIGGER_L, ECHO_L, MAX_DISTANCE)};

// Wifi


#include "WiFi.h"

const char *ssid = "Bahrawy"; //ESP Access Point
const char *password = "Bahrawy12345"; //ESP Password


WiFiClient client;
IPAddress ip (192, 168, 19, 2);
IPAddress netmask (255, 255, 255, 0);
const int port = 5210;
WiFiServer server(port);


/*****************Encoders**************/
// #define  encoderResolution  7 

// #define encoderRight_A  25 
// #define encoderRight_B  26 
// #define encoderLeft_A   23
// #define encoderLeft_B   22

/*******************APIs****************/
int orientation(int orient, char turning);
void updateCoordinates(int orient, int *new_x, int *new_y);
bool wallFront();
bool wallRight();
bool wallLeft();
void moveForward();
void turnRight();
void turnLeft();
// Motors APIs
void Forward(void);
void Stop(void);
void Right(void);
void Left(void);
void EncoderRightHandler();
void EncoderLeftHandler();
uint32_t getDistance(NewPing sonar);

#endif