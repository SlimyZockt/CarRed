#include <LiquidCrystal_I2C.h> //LiquidCrystal_I2C.h by Marco Schwarz
#define ADVERTISEMENT_COUNT 2

const unsigned long REFRESH_RATE = 500;
const String ADVERTISEMENTS[] = {};

LiquidCrystal_I2C
    lcd(0x27, 16,
        2); // set the LCD address to 0x27 for a 16 chars and 2 line display

int scrollingTextShift = 0;
int currentAdvertisement = 0;

unsigned long oldTime = 0;
unsigned long deltaTime = 0;
unsigned long currentTime = 0;

void setupDisplay() {
  lcd.init();      // Init lcd-Display
  lcd.backlight(); // Backlight ON
}

// Komplette Anzeige löschen
void displayValue(float value, int spalte, int zeile) {
  lcd.setCursor(zeile, spalte); // Cursor bei spalte:int, zeile:int
  lcd.print(value);
}

// Komplette Anzeige löschen
void clearDisplay() { lcd.clear(); }

// Test Anzeigen
void displayText(String text, int spalte, int zeile) {
  lcd.setCursor(zeile, spalte); // Cursor bei spalte:int, zeile:int
  lcd.print(text);
}

// Cursor blinken lassen
void link() { lcd.blink(); }

void displayAdvert() {
  displayText(ADVERTISEMENTS[currentAdvertisement], 1, -scrollingTextShift);
  if (scrollingTextShift == -16) {
    scrollingTextShift = 0;
  } else {
    scrollingTextShift = scrollingTextShift - 2;
  }
  if (scrollingTextShift == 0) {
    currentAdvertisement += 1;
    if (currentAdvertisement == ADVERTISEMENT_COUNT + 1) {
      currentAdvertisement = 0;
    }
  }
}

void startingAnimation() {
  displayText("Starting", 0, 0);
  displayText("Starting .", 0, 0);
  displayText("Starting ..", 0, 0);
  displayText("Starting ...", 0, 0);
  displayText("Starting    ", 0, 0);
  displayText("            ", 0, 0);
}

void displayDistance(int spalte, int zeile) {
  float dist = getDistance();
  if (dist == 500 || dist <= 0) {
    displayText("Kein Messwert", spalte, zeile);
    return;
  }
  displayText(String(dist), 0, 1);
}

void displayMode(int spalte, int zeile) {
  displayText("M: " + String(drivingMode), spalte, zeile);
}

void updateLCD() {
  currentTime = millis();
  deltaTime = currentTime - oldTime;
  if (deltaTime < REFRESH_RATE) {
    return;
  }
  clearDisplay();
  displayAdvert();
  displayDistance(0, 1);
  displayMode(0, -1) oldTime = currentTime;
}