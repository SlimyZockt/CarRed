int QRE1113_Pin = A1; // verbunden mit analog 5

// Helligkeit: wenn schwarz, dann TRUE
boolean isDarkBS() {
  int QRE_Value = analogRead(QRE1113_Pin);
  if (QRE_Value > 500) {
    return true;
  }
  return false;
}
