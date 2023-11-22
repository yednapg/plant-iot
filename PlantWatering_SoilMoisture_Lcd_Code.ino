#include <LiquidCrystal.h>
#include <Wire.h>
#include <DHT.h>

int Contrast = 100;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define DHTPIN 1
#define DHTTYPE DHT11  // DHT 11
DHT dht(DHTPIN, DHTTYPE);

int sensor_pin = A0;  //Sensor Pin
int relay_pin = 13;   //Relay Pin

void setup() {
  int Contrast = 100;
  analogWrite(9, Contrast);
  lcd.begin(16, 2);
  dht.begin();
  pinMode(sensor_pin, INPUT);
  pinMode(relay_pin, OUTPUT);
}

void loop() {
  int Contrast = 100;
  LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
  analogWrite(9, Contrast);
  lcd.begin(16, 2);

  // HUMIDITY TEMPERATURE
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  float f = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    return;
  }

  lcd.setCursor(13, 0);
  lcd.print("H");
  lcd.print(h);
  // lcd.print("%");

  lcd.setCursor(13, 1);
  lcd.print("T");
  lcd.print(t);
  // lcd.print("C");

  // MOISTURE & MOTOR
  int sensor_data = analogRead(sensor_pin);
  if (sensor_data > 950) {
    digitalWrite(relay_pin, LOW);
    lcd.setCursor(0, 0);
    lcd.print("M1TD");
    lcd.setCursor(0, 1);
    lcd.print("N50 P7 P180");
  } else if (sensor_data >= 400 && sensor_data <= 950) {
    digitalWrite(relay_pin, LOW);
    lcd.setCursor(0, 0);
    lcd.print("M5HM");
    lcd.setCursor(0, 1);
    lcd.print("N50 P7 P180");
  } else if (sensor_data < 400) {
    digitalWrite(relay_pin, LOW);
    lcd.setCursor(0, 0);
    lcd.print("M4HW");
    lcd.setCursor(0, 1);
    lcd.print("N50 P7 P180");
  }
  delay(20000);
}
