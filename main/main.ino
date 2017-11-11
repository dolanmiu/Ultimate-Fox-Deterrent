#include <Wire.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include "RTClib.h"
#include "LowPower.h"
#include <Dusk2Dawn.h>

RTC_DS1307 rtc;
int sunset; 

int pir1Pin = 7; // Input for HC-S501
int pir2Pin = 8; // Input for HC-S501
int pir3Pin = 9; // Input for HC-S501
int pir4Pin = 10; // Input for HC-S501

void setup() {
  Serial.begin(9600);
  Serial.println("Starting Ultimate Fox Deterrant");
  rtc.begin();

  syncTime();
  setSunset();

  pinMode(pir1Pin, INPUT);
  
  Alarm.alarmRepeat(0, 0, 0, setSunset);
  Serial.flush();
}

void loop() {
  Serial.flush();
  digitalClockDisplay();
  Alarm.delay(1000); // wait one second between clock display

  if (hour() > sunset || hour() < 7) {
    surveillance();
    // LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
  } else {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
  syncTime();
}

void surveillance() {
  Serial.println("Surveillancing");
  int pirValue = digitalRead(pir1Pin);
  Serial.println(pirValue);
}

void frightenFox() {  
  Serial.println("Emitting LED and making noise");
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
