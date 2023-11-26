#include <LiquidCrystal.h>
#include <Wire.h>
#include <DHT.h>

// const int buzzer = 10; //buzzer to arduino pin 9

int Contrast = 100;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int resval = 0;   // holds the value
int respin = A2;  // sensor pin used

#define DHTPIN 1
#define DHTTYPE DHT11  // DHT 11
DHT dht(DHTPIN, DHTTYPE);

int sensor_pin = A0;  //Sensor Pin
int relay_pin = 13;   //Relay Pin
int ph_sensor_pin = A1;

void setup() {
  int Contrast = 100;
  analogWrite(9, Contrast);
  lcd.begin(16, 2);
  dht.begin();
  pinMode(sensor_pin, INPUT);
  pinMode(relay_pin, OUTPUT);
  // pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
}

void loop() {
  int Contrast = 100;
  LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
  analogWrite(9, Contrast);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Efficient urban farming");
  lcd.setCursor(0, 1);
  lcd.print("System with IoT.");
  delay(5000);
  lcd.clear();

  // Water Level
  lcd.setCursor(0, 0);
  resval = analogRead(respin);  //Read data from analog pin and store it to resval variable
  if (resval <= 330) {
    // Serial.print("Tank Emptry");
    lcd.print("Tank Empty");
  } else if (resval > 330 && resval <= 500) {
    // Serial.print("Water Level Low");
    lcd.print("Water Level Low");
  } 
  else if (resval > 500) {
    // Serial.print("Enough Water");
    lcd.print("Enough Water");
  }
  else if (resval > 600) {
    // Serial.print("No Need to fill the tank");
    lcd.print("No Need to Fill");
    lcd.setCursor(0, 1);
    lcd.print("the Tank");
  }
  delay(2000);
  lcd.clear();

  // HUMIDITY TEMPERATURE
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  float f = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    // Serial.println("Failed to read from DHT sensor!");
    return;
  }

  lcd.setCursor(13, 0);
  lcd.print("H");
  lcd.print(h);
  lcd.print("%");

  lcd.setCursor(13, 1);
  lcd.print("T");
  lcd.print(t);
  lcd.print("C");

  // pH value
  float ph_sensor_data = analogRead(ph_sensor_pin);
  ph_sensor_data = (ph_sensor_data / 100.0);
  if (ph_sensor_data > 8) {
    ph_sensor_data = ph_sensor_data - float(6.00);
  }
  else if (ph_sensor_data < 6) {
    ph_sensor_data = ph_sensor_data + float(6.00);
  }


  // MOISTURE & MOTOR
  int sensor_data = analogRead(sensor_pin);
  if (sensor_data > 950) {
    digitalWrite(relay_pin, LOW);
    lcd.setCursor(0, 0);
    lcd.print("M1TD");
    lcd.setCursor(0, 1);
    lcd.print("pH");
    lcd.print(ph_sensor_data);
  } else if (sensor_data >= 400 && sensor_data <= 950) {
    digitalWrite(relay_pin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("M5HM");
    lcd.setCursor(0, 1);
    lcd.print("pH");
    lcd.print(ph_sensor_data);
  } else if (sensor_data < 400) {
    digitalWrite(relay_pin, LOW);
    lcd.setCursor(0, 0);
    lcd.print("M4HW");
    lcd.setCursor(0, 1);
    lcd.print("pH");
    lcd.print(ph_sensor_data);
  }
  delay(5000);
  lcd.clear();
  // Serial.print("Temperature & Humidity Sensor Data:");
  // Serial.print("T:");
  // Serial.println(t);
  // Serial.print("H:");
  // Serial.println(h);
  // Serial.print("Moisture Data");
  // Serial.println(sensor_data);
}
