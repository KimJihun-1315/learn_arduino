#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);   // 0x3F 또는 0x27

void setup()
{
  Serial.begin(9600);
  
  init();
  backlight();

  Serial.println("Start PM Sensor");

  setCursor(0, 0);
  print("%% PM SENSOR %%");
}
