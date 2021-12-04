#include <PMsensor.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

PMsensor PM;
DHT dht(7, DHT11);
LiquidCrystal_I2C lcd(0x3F, 16, 2);   // 0x3F 또는 0x27


void setup()
{
  Serial.begin(9600);

  PM.init(3, A0);
  dht.begin();
  lcd.init();
  lcd.backlight();

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
    delay(3000);
    return;
  }

  if (isnan(humi) || isnan(temp))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

//시리얼 모니터 송출
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

//lcd 화면송출
  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.print("T:");
  lcd.print(temp);
  lcd.print("C");

  lcd.print(" H:");
  lcd.print((int)humi);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("PM:");
  lcd.print(pm);
  lcd.print(" ");

  lcd.print("DI:");
  lcd.print((int)discomfort);

  delay(3000);
}
