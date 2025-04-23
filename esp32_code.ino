/***************************
 *   PARKNGO SYSTEM - FINAL
 * ESP32 + LCD + BLYNK Notifications + Working LEDs
 ***************************/

#define BLYNK_TEMPLATE_ID "TMPL3NJ5kOSLN"
#define BLYNK_TEMPLATE_NAME "major project"
#define BLYNK_AUTH_TOKEN "Z1plgs5ICwCslJEm4OaHe4xwCChSQdi6"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Wi-Fi credentials
char ssid[] = "OnePlus 12R";
char pass[] = "n5pwvrad";

// I/O Pins for Sensors and LEDs
#define SENSOR1 32
#define SENSOR2 33
#define SENSOR3 25
#define SENSOR4 26

#define LED1 2
#define LED2 4
#define LED3 5
#define LED4 18

// LCD Display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Previous sensor states
bool lastS1 = true, lastS2 = true, lastS3 = true, lastS4 = true;

// LED blink timing
unsigned long previousMillis = 0;
const long blinkInterval = 500;
bool ledBlinkState = false;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  pinMode(SENSOR1, INPUT_PULLUP);
  pinMode(SENSOR2, INPUT_PULLUP);
  pinMode(SENSOR3, INPUT_PULLUP);
  pinMode(SENSOR4, INPUT_PULLUP);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  lcd.clear();
  lcd.print("Connected Blynk");
  delay(1000);
}

void loop() {
  Blynk.run();

  // Handle blinking
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= blinkInterval) {
    previousMillis = currentMillis;
    ledBlinkState = !ledBlinkState;
  }

  checkParkingSpots();
}

void checkParkingSpots() {
  bool s1 = digitalRead(SENSOR1);
  bool s2 = digitalRead(SENSOR2);
  bool s3 = digitalRead(SENSOR3);
  bool s4 = digitalRead(SENSOR4);

  // LEDs: Blink when vacant (HIGH = vacant)
  digitalWrite(LED1, s1 ? ledBlinkState : LOW);
  digitalWrite(LED2, s2 ? ledBlinkState : LOW);
  digitalWrite(LED3, s3 ? ledBlinkState : LOW);
  digitalWrite(LED4, s4 ? ledBlinkState : LOW);

  // Blynk: Write 1 when FULL (LOW), 0 when vacant (HIGH)
  Blynk.virtualWrite(V0, s1 ? 0 : 1);
  Blynk.virtualWrite(V1, s2 ? 0 : 1);
  Blynk.virtualWrite(V2, s3 ? 0 : 1);
  Blynk.virtualWrite(V3, s4 ? 0 : 1);

  // Total available
  int available = s1 + s2 + s3 + s4;
  Blynk.virtualWrite(V4, available);

  // Notifications only when a spot becomes vacant
  if (s1 && !lastS1) Blynk.logEvent("spot1_vacant", "Spot 1 is now vacant");
  if (s2 && !lastS2) Blynk.logEvent("spot2_vacant", "Spot 2 is now vacant");
  if (s3 && !lastS3) Blynk.logEvent("spot3_vacant", "Spot 3 is now vacant");
  if (s4 && !lastS4) Blynk.logEvent("spot4_vacant", "Spot 4 is now vacant");

  // Save last states
  lastS1 = s1;
  lastS2 = s2;
  lastS3 = s3;
  lastS4 = s4;

  // LCD update
  lcd.setCursor(0, 0);
  lcd.printf("S1:%s S2:%s", s1 ? "Emp" : "Full", s2 ? "Emp" : "Full");
  lcd.setCursor(0, 1);
  lcd.printf("S3:%s S4:%s", s3 ? "Emp" : "Full", s4 ? "Emp" : "Full");
}