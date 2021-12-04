#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  lcd.init();
  lcd.backlight();
  dht.begin();
}

void loop()
{
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.println(h);
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  Serial.println("");

  lcd.setCursor(0,0);
  lcd.print(F("Humi: "));
  lcd.print(h);
  lcd.setCursor(0,1);
  lcd.print(F("Temp: "));
  lcd.print(t);
  lcd.print(F("'C "));
  
  }
