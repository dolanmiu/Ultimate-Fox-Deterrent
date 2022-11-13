#include <Wire.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include "RTClib.h"
#include "LowPower.h"
#include <Dusk2Dawn.h>

RTC_DS1307 rtc;
int sunset; 

int pir1Pin = 7; // Input for HC-S501
int pir2Pin = 6; // Input for HC-S501
int pir3Pin = 5; // Input for HC-S501
int pir4Pin = 4; // Input for HC-S501
int scarePin = 13; // Output for scare

void setup() {
  Serial.begin(9600);
  Serial.println("Starting Ultimate Fox Deterrant");
  rtc.begin();

  syncTime();
  setSunset();

  pinMode(pir1Pin, INPUT);
  pinMode(pir2Pin, INPUT);
  pinMode(pir3Pin, INPUT);
  pinMode(pir4Pin, INPUT);
  pinMode(scarePin, OUTPUT);
  digitalWrite(scarePin, LOW);
  
  Alarm.alarmRepeat(0, 0, 0, setSunset);
  Serial.flush();
}

void loop() {
  Serial.flush();
  digitalClockDisplay();
  
  Alarm.delay(100); // wait one millisecond between clock display

  if (hour() >= sunset || hour() < 7) {
    bool foundFox = surveillance();
    if (foundFox) {
      LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    } else {
      LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
    }
    syncTime();
  } else {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    syncTime();
  }
}

bool surveillance() {
  int pir1 = digitalRead(pir1Pin);
  int pir2 = digitalRead(pir2Pin);
  int pir3 = digitalRead(pir3Pin);
  int pir4 = digitalRead(pir4Pin);

  Serial.println(String(pir1) + " " + String(pir2) + " " + String(pir3) + " " + String(pir4));
  Serial.print(pir1);
  Serial.print(pir2);
  Serial.print(pir3);
  Serial.print(pir4);
  Serial.println();
  
  if (pir1 + pir2 + pir3 + pir4 >= 2) {
    frightenFox();
    return true;
  }
  return false;
}

void frightenFox() {  
  Serial.println("Emitting LED and making noise");
  for (int i=0; i <= 5; i++){
    digitalWrite(scarePin, HIGH);
    delay(100);
    digitalWrite(scarePin, LOW);
    delay(100);
  }
}

void syncTime() {
  DateTime now = rtc.now();
  setTime(now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());
}

void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void setSunset() {
  sunset = findSunset(false);
  Serial.print("Setting sunset to: " + sunset);
}

void printDigits(int digits) {
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

int findSunset(bool dayLightSavings) {
  // Set Dusk2Dwan location
  Dusk2Dawn locationDusk2Dawn(51.3809, 0.5221, dayLightSavings ? 1 : 0);
  int sunsetMinutes = locationDusk2Dawn.sunset(year(), month(), day(), false);
  int sunsetHours = sunsetMinutes / 60;

  Serial.println("Sunset is at: " + String(sunsetMinutes) + " minutes from midnight");
  Serial.println("Sunset is at: " + String(sunsetHours) + " hours from midnight");
  return sunsetHours;
}

