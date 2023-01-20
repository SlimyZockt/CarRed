#include<Servo.h>
#define TARGET_TPS = 60

Servo leftMotor;
Servo rightMotor;

unsigned long oldTime = 0;
unsigned long deltaTime;


void setupEngineControl(PINS leftMotorPin, PINS rightMotorPin, int targetTPS)
{
    leftMotor.attach(9);
    rightMotor.attach(10);
    deltaTime = millis();
}

void move(float angle, int speed)
{
    angle = constrain(x, a, b)
    float x = cos(angle) float y = sin(angle)                                                             leftMotor.write(leftSpeed);
    rightMotor.write(rightSpeed);
}



void updateEngineDelta()
{
    unsigned long time = millis()
    deltaTime = time - last_time;
    oldTime = time;
}

void test_drive()
{
    move(90, 90); // move forward
    delay(1000);
    move(120, 60); // turn left
    delay(1000);
    move(60, 120); // turn right
    delay(1000);
    move(0, 0); // stop
    delay(1000);
}