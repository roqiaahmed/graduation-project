#include "DHT.h"
#include <EEPROM.h>
#include "GravityTDS.h"

// LCD
//#include <LiquidCrystal.h>
//LiquidCrystal lcd(8, 7, 6, 5, 4, 3);//lcd(RS,En,D4,D5,D6,D7)
  
#define DHTTYPE    DHT22
#define HT_SENSOR  2
#define TDS_SENSOR A1

DHT dht(HT_SENSOR, DHTTYPE);
GravityTDS gravityTds;
float temperature = 0;
int humidity = 0;

void setup() {
  Serial.begin(9600);
  
  // LCD
//  lcd.begin(16, 2);
//  lcd.clear();

  dht.begin();
  
//  gravityTds.setPin(TDS_SENSOR);
//  gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
//  gravityTds.begin();  //initialization

  // LCD
//  lcd.setCursor(0, 0);
//  lcd.print("TEMP=   ");
//  lcd.setCursor(0, 10);
//  lcd.print("HU=  ");
//  lcd.setCursor(1, 0);
//  lcd.print("TDS=   ");
}

void loop() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  
  ht_readings(temperature, humidity);
//  tds_readings(temperature);
}

void ht_readings(float temperature, int humidity) {

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  //LCD
//  lcd.setCursor(0, 5);
//  lcd.print(temperature);
//  lcd.print("C");
//  lcd.setCursor(0, 12);
//  lcd.print(humidity);
//  lcd.print("%");

  Serial.print("TEMP= ");
  Serial.print(temperature);
  Serial.println("C");
  Serial.print("HU= ");
  Serial.print(humidity);
  Serial.print("%");
  Serial.println();
  delay(2000);
}

void tds_readings(float temperature) {
  float tds = 0;
  gravityTds.setTemperature(temperature);
  gravityTds.update();
  tds = gravityTds.getTdsValue();

  // LCD
//  lcd.setCursor(1, 4);
//  lcd.print(tds);
//  lcd.print("ppm");
  
//  Serial.print(tds,0);
  Serial.print("TDS= ");
  Serial.print(tds);
  Serial.println("ppm");
  delay(500);
}
