#include <LiquidCrystal.h>

const int trigPin = 2;
const int echoPin = 3;
int ledPin = 12;
int buzzerPin = 13;
int yellowLedPin = 5;
int greenLedPin = 4;
int buttonPin = 6;

long duration;
int distance;

int An;
float C;

int humidityPin = A0;
int humidityValue;

LiquidCrystal lcd(7, 8, 9, 10, 11);

int displayMode = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(humidityPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  An = 0;
  C = 0;

  lcd.begin(16, 2);
  lcd.clear();

  Serial.begin(9600);
}

void loop()
{
  // Mesure de la température
  An = analogRead(A3);
  C = -40.0 + (An * 5.0 / 1023.0 - 0.1) * 100.0;
  Serial.println(C);

  // Affichage de la température sur l'écran LCD
  if (displayMode == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(C);
    lcd.print("C     ");
  }

  // Affichage de la distance sur l'écran LCD
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (displayMode == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Dist: ");
    lcd.print(distance);
    lcd.print("cm    ");
  }

  // Affichage de l'humidité sur l'écran LCD
  humidityValue = analogRead(humidityPin);

  if (displayMode == 2) {
    lcd.setCursor(0, 0);
    lcd.print("Hum: ");
    lcd.print(humidityValue);
    lcd.print("      ");
  }

  // Affichage de la distance sur la LED et le buzzer
  if (distance < 100) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(1000);
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }

  // Affichage de l'humidité sur les LEDs
  if (humidityValue < 500) {
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
  } else {
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
  }

  // Changement du mode d'affichage sur l'écran LCD en appuyant sur le bouton
  if (digitalRead(buttonPin) == LOW) {
    displayMode++;
    if (displayMode > 2) {
      displayMode = 0;
    }
    delay(500);
    lcd.clear();
  }
}