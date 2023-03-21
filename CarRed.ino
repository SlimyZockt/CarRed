
void setup() {
  Serial.begin(9600);
  setupMotor();
  setupBT();
  setupDisplay();
  distanceSetup();
  // startingAnimation();
}

void loop() {
  Serial.println("bluetooth start");
  loopBT();
  Serial.println("bluetooth end");
  Serial.println("Motor start");
  loopMotor();
  Serial.println("motor end");
  Serial.println("LCD Draw");
  updateLCD();
  Serial.println("LCD end");
  // displayAdvert();
  // showMode();
  }
