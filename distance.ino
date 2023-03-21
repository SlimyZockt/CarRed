int triggerPin = 4;
int echoPin = 5;

void distanceSetup() {
  // Trigger-Pin ist ein Ausgang
  pinMode(triggerPin, OUTPUT);
  // Echo-Pin ist ein Eingang
  pinMode(echoPin, INPUT);
}

// Gibt Variable die die Entfernung eines Objektes vor dem Schallsensor angibt
// zurück
float getDistance() {
  digitalWrite(triggerPin, LOW);
  delay(5);
  digitalWrite(triggerPin, HIGH);
  delay(10);
  digitalWrite(triggerPin, LOW);
  float time = pulseIn(echoPin, HIGH);
  float dist = (time / 2) * 0.03432;
  return min(dist, 500);
}
