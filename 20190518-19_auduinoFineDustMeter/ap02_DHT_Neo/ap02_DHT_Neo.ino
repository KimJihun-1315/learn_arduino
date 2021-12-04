//온습도센서를 이용하여 온도에 따른 색깔 조절하기
#include <SimpleDHT.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

SimpleDHT11 dht11(7);
Adafruit_NeoPixel pixels(5, 12, NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(115200);
  pixels.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  byte temp = 0;
  byte hum = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temp, &hum, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temp); Serial.print(" *C, "); 
  Serial.print((int)hum); Serial.println(" H");
  int r=0;
  int g=0;
  int b=0;
  
  //네오픽셀 LED켜기
 if (temp > 30)
  {
    r = 255;
    g = 0;
    b = 0;
  }
  else if (temp > 20)
  {
    r = 0;
    g = 255;
    b = 0;
  }
  else if (temp < 15)
  {
    r = 0;
    g = 0;
    b = 255;
  }

  for(int i=0 ; i<5 ; i++)
  {
    pixels.setPixelColor(i, r,g,b);
  }
  pixels.show();

  //LCD에 온습도 표시하기
  lcd.setCursor(5,0);
  lcd.print("TEMP:");
  lcd.print(temp);
  lcd.print(" c");

  lcd.setCursor(5,1);
  lcd.print("HUMI:");
  lcd.print(hum);
  lcd.print(" %");

  delay(1500);
}
