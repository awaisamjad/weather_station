#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include "uRTCLib.h"

#define DHTPIN 7
#define DHTTYPE DHT11 // Change this to DHT22 if you are using a DHT22 sensor
const int pResistor = A0;
const int ledPin_photocell = 13;
DHT dht(DHTPIN, DHTTYPE);
uRTCLib rtc(0x68);
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int photocell_value = 0;
void setup()
{
  Serial.begin(9600);
  dht.begin();
  URTCLIB_WIRE.begin();
  pinMode(ledPin_photocell, OUTPUT);
  pinMode(pResistor, INPUT);
}

void photocell()
{
  photocell_value = analogRead(pResistor);
  if (photocell_value > 500)
  {
    digitalWrite(ledPin_photocell, HIGH); // Turn led off
  }
  else
  {
    digitalWrite(ledPin_photocell, LOW); // Turn led on
  }

}
void clock()
{
  rtc.refresh();
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Print the date and time in D-M-Y format.
  Serial.print(rtc.day());
  Serial.print("-");
  Serial.print(rtc.month());
  Serial.print("-");
  Serial.print(rtc.year());

  // Print the day of the week.
  Serial.print(" (");
  Serial.print(daysOfTheWeek[rtc.dayOfWeek()]);
  Serial.print(") ");

  // Print the time.
  Serial.print(rtc.hour());
  Serial.print(":");
  if (rtc.minute() < 10)
  {
    Serial.print("0");
  }
  Serial.print(rtc.minute());
  Serial.print(":");
  if (rtc.second() < 10)
  {
    Serial.print("0");
  }
  Serial.println(rtc.second());
  // Spacing
  Serial.println();
  // Print temperature and humidity.
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.println();
  Serial.println();
}
void loop()
{
  clock();
  photocell();
  delay(2000); // Wait for 2 seconds between readings
}
