#ifndef API_H_
#define API_H_

#define IR_Left 22
#define IR_Front 27
#define IR_Right 34



#define distancePerCount 1.660275

// 1.0205   -->   6.5
// ?        -->   18.8

// Right
#define IN1 33
#define IN2 25
// Left
#define IN3 5
#define IN4 18

#define ENA  32
#define ENB  19

// Pin definitions
#define encoderLeft  23
#define encoderRight  26 



#include <string>

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
void readEncoderRight();
void readEncoderLeft();


#endif