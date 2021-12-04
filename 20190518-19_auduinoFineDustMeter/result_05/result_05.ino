#include <PMsensor.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

PMsensor PM;
DHT dht(7, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);   // 0x3F 또는 0x27

byte temp_sig[] = {
  B00100,
  B01010,
  B01010,
  B01110,
  B01110,
  B11111,
  B11111,
  B01110
};

byte humi[] = {
  B00100,
  B00100,
  B01010,
  B01010,
  B10001,
  B11111,
  B11111,
  B01110
};

byte dust[] = {
  B01010,
  B10101,
  B00000,
  B01010,
  B10101,
  B00000,
  B01010,
  B10101
};

byte comf[] = {
  B00000,
  B01010,
  B11111,
  B01111,
  B01110,
  B00100,
  B00000
};

byte C[] = {
  B10000,
  B00110,
  B01001,
  B01000,
  B01000,
  B01001,
  B00110,
  B00000
};

void setup()
{
  Serial.begin(9600);

  PM.init(3, A0);
  dht.begin();
  lcd.init();
  lcd.backlight();

  // 특수기호 만들기
  lcd.createChar(0, temp_sig);
  lcd.createChar(1, humi);
  lcd.createChar(2, dust);
  lcd.createChar(3, comf);
  lcd.createChar(4, C);
  
  Serial.println("Start PM Sensor");
}

void loop()
{
  float pm = 0;
  int err = PMsensorErrSuccess;

  float humi = dht.readHumidity();
  float temp = dht.readTemperature();

  float discomfort = ( 0.81 * temp ) + ( 0.01 * humi * (0.99 * temp - 14.3) ) + 46.3;

  if ((err = PM.read(&pm, true, 0.1)) != PMsensorErrSuccess)
  {
    Serial.print("Error = ");
    Serial.println(err);
    delay(100);
    return;
  }

  if (isnan(humi) || isnan(temp))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("PM : ");
  Serial.print(pm);
  Serial.println(" ug/m^3");

  Serial.print("Temperature : ");
  Serial.print(temp);
  Serial.println(" C");

  Serial.print("Humidity : ");
  Serial.print(humi);
  Serial.println(" %");

  Serial.print("Discomfort Index : ");
  Serial.println(discomfort);

  Serial.println();

  lcd.clear();

  // 온도
  lcd.setCursor(0, 0);
  lcd.write(0);
  lcd.print(":");
  lcd.print(temp, 1);
  lcd.write(4);

  // 습도
  lcd.setCursor(8, 0);
  lcd.write(1);
  lcd.print(":");
  lcd.print(humi, 1);
  lcd.print("%");

  // 먼지
  lcd.setCursor(0, 1);
  //lcd.print("PM:");
  lcd.write(2);
  lcd.print(":");
  lcd.print(pm, 1);

  // 불쾌지수
  lcd.setCursor(8, 1);
  //lcd.print("DI:");
  lcd.write(3);
  lcd.print(":");
  lcd.print((int)discomfort);

  delay(1000);
}
