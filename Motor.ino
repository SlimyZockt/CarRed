#define TURN_SPEED 130
#define DRIVE_SPEED 150

typedef enum DrivingModes { MANUEL, DRIVE_ON_CIRCLE, DRIVE_IN_CIRCLE };

DrivingModes drivingMode = MANUEL;

int directionPinLeft = 12;
int pwmPinLeft = 3;
int brakePinLeft = 9;

int directionPinRight = 13;
int pwmPinRight = 11;
int brakePinRight = 8;

// boolean to switch direction
bool directionState;

void setupMotor() {
  // define pins
  pinMode(directionPinLeft, OUTPUT);
  pinMode(pwmPinLeft, OUTPUT);
  pinMode(brakePinLeft, OUTPUT);

  pinMode(directionPinRight, OUTPUT);
  pinMode(pwmPinRight, OUTPUT);
  pinMode(brakePinRight, OUTPUT);
  stopMotor(100);
  drivingMode = MANUEL;
}

void reverseLeft(int vel) {
  digitalWrite(directionPinLeft, HIGH);
  digitalWrite(brakePinLeft, LOW);
  analogWrite(pwmPinLeft, vel);
}

void reverseRight(int vel) {
  digitalWrite(directionPinRight, HIGH);
  digitalWrite(brakePinRight, LOW);
  analogWrite(pwmPinRight, vel);
}

void forwardLeft(int vel) {
  digitalWrite(directionPinLeft, LOW);
  digitalWrite(brakePinLeft, LOW);
  analogWrite(pwmPinLeft, vel);
}

void forwardRight(int vel) {
  digitalWrite(directionPinRight, LOW);
  digitalWrite(brakePinRight, LOW);
  analogWrite(pwmPinRight, vel);
}

void rotateRight() {
  // Delay 500 für Viertel-Drehung
  forwardRight(TURN_SPEED);
  reverseLeft(TURN_SPEED);
}

void rotateLeft() {
  forwardLeft(TURN_SPEED);
  reverseRight(TURN_SPEED);
}

void stopMotor(int delayTime) {
  digitalWrite(brakePinRight, HIGH);
  digitalWrite(brakePinLeft, HIGH);
  pinMode(pwmPinLeft, OUTPUT);
  pinMode(pwmPinRight, OUTPUT);
  delay(delayTime);
}

void crashStopt() {
  if (getDistance() <= 30) {
    rotateLeft();
    delay(500);
    forwardRight(150);
    forwardLeft(130);
    delay(500);
    stopMotor(500);
    delay(500);
  }
}

void loopMotor() {
  switch (drivingMode) {
  case DrivingModes::MANUEL:
    break;
  case DrivingModes::DRIVE_IN_CIRCLE:
    crashStopt();
    driveInArea();
    break;
  default:
    break;
  }
}

void changeDrivingMode() {
  if (drivingMode == MANUEL) {
    drivingMode = DRIVE_ON_CIRCLE;
    return;
  }
  drivingMode = MANUEL;
}

void impulseDriveForward() {
  forwardLeft(DRIVE_SPEED);
  forwardRight(DRIVE_SPEED);
  delay(1000);
  stopMotor(500);
}

void impulseDriveBackward() {
  reverseRight(DRIVE_SPEED);
  reverseLeft(DRIVE_SPEED);
  delay(1000);
  stopMotor(500);
}

void impulseRotateRight() {
  rotateRight();
  delay(500);
  stopMotor(500);
}

void impulseRotateLeft() {
  rotateLeft();
  delay(500);
  stopMotor(500);
}

void diverAutomaticOnCircle() {
  if (!isDarkBS()) {
    stopMotor(500);
    rotateLeft();
    delay(250);
    return;
  }
  forwardLeft(DRIVE_SPEED);
  forwardRight(DRIVE_SPEED);
}

void driveInArea() {
  if (isDarkBS()) {
    impulseDriveBackward();
    impulseDriveBackward();
    rotateLeft();
    rotateLeft();
    return;
  }
  forwardLeft(DRIVE_SPEED);
  forwardRight(DRIVE_SPEED);
}
