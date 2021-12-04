//온습도센서를 이용하여 온도에 따른 네오픽셀의 색깔 조절과 습도에 따른 네오픽셀의 갯수조절
#include <SimpleDHT.h>
#include <Adafruit_NeoPixel.h>

SimpleDHT11 dht11(7);
Adafruit_NeoPixel pixels(5, 12, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  pixels.begin();
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
  
  //온도에 따른 LED색깔조절
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

  
  delay(1500);
}
