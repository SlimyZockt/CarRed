int directionPinRight = 12;
int brakePinRight = 9;
int pwmPinRight = 3;

int directionPinLeft = 13;
int pwmPinLeft = 11;
int brakePinLeft = 8;

// boolean to switch direction
bool directionState;

void setupEngine()
{
    // define pins
    pinMode(directionPinRight, OUTPUT);
    pinMode(pwmPinRight, OUTPUT);
    pinMode(brakePinRight, OUTPUT);
    pinMode(directionPinLeft, OUTPUT);
    pinMode(pwmPinLeft, OUTPUT);
    pinMode(brakePinLeft, OUTPUT);
}

void drive(float ange, int speed) {
    digitalWrite(directionPinRight, HIGH);
    digitalWrite(directionPinLeft, HIGH);

    digitalWrite(brakePinRight, LOW);
    digitalWrite(brakePinLeft, LOW);
    analogWrite(pwmPinRight, speed);
    analogWrite(pwmPinLeft, speed);
}

void dive_time(int time) {
    drive(0, 130);
    delay(time);
    // activate breaks
    digitalWrite(brakePinLeft, HIGH);
    digitalWrite(brakePinRight, HIGH);

    // set work duty for the motor to 0 (off)
    analogWrite(pwmPinLeft, 0);
    analogWrite(pwmPinRight, 0);

    delay(time);
}