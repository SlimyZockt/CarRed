#include <SoftwareSerial.h>

// RX port = 10 | TX port = 11
SoftwareSerial bluetooth(7, 6);
String inByte = "";

typedef enum Input { X, Y, O, B, START, SELECT, UP, DOWN, RIGHT, LEFT, NONE };

Input input = Input::NONE;

void automaticCircleInputHandler(Input input) {
  // TODO
}

void automaticForwardMotorInputHandler(Input input) {
  // TODO
}

void manuelInputHandler(Input input) {
  switch (input) {
  case Input::UP:
    impulseDriveForward();
    break;
  case Input::DOWN:
    impulseDriveBackward();
    break;
  case Input::LEFT:
    impulseRotateLeft();
    break;
  case Input::RIGHT:
    impulseRotateRight();
    break;
  default:
    break;
  }
}

void switchDrivingMode() {
  if (drivingMode == DrivingModes::DRIVE_IN_CIRCLE) {
    drivingMode = DrivingModes::MANUEL;
    Serial.println(drivingMode);
    return;
  }
  drivingMode = drivingMode + 1;
  Serial.println(drivingMode);
}

void setupBT() {
  // Start the hardware serial port
  bluetooth.begin(9600);
  Serial.println("bluetooth available");
}

void loopBT() {
  // while there is data coming in, read it
  // and send to the hardware serial port:
  if (bluetooth.available()) {
    inByte = bluetooth.readString();
    inByte.trim();
    Serial.println(inByte);
    if (inByte == "x") {
      input = Input::X;
    } else if (inByte == "o") {
      input = Input::O;
    } else if (inByte == "y") {
      input = Input::Y;
    } else if (inByte == "b") {
      input = Input::B;
    } else if (inByte == "start") {
      switchDrivingMode();
      input = Input::START;
    } else if (inByte == "select") {
      input = Input::SELECT;
    } else if (inByte == "up") {
      input = Input::UP;
    } else if (inByte == "down") {
      input = Input::DOWN;
    } else if (inByte == "left") {
      input = Input::LEFT;
    } else if (inByte == "right") {
      input = Input::RIGHT;
    }

    switch (drivingMode) {
    case DrivingModes::MANUEL:
      manuelInputHandler(input);
      Serial.println("Manuel mode");
      break;
    case DrivingModes::DRIVE_ON_CIRCLE:
      automaticCircleInputHandler(input);
      Serial.println("AUTOMATIC C mode");
      break;
    case DrivingModes::DRIVE_IN_CIRCLE:
      automaticForwardMotorInputHandler(input);
      Serial.println("AUTOMATIC FORWARD mode");
      break;
    default:
      break;
    }
    input = Input::NONE;
  }

  Serial.println("bluetooth finished");
}
