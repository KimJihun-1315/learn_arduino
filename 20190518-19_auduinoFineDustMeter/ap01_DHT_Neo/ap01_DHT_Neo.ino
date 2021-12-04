//온습도센서를 이용하여 습도에 따른 네오픽셀 밝기 조절하기
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
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temp, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temp); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
  
  //네오픽셀 LED켜기
  if(temp > 30)
  {
    pixels.setPixelColor(0, 255, 0, 0);
    pixels.show();
  }
  else if(temp > 20)
  {
    pixels.setPixelColor(0, 0, 255, 0);
    pixels.show();
  }
  else if(temp < 15)
  {
    pixels.setPixelColor(0, 0, 0, 255);
    pixels.show();
  }
  
  // DHT11 sampling rate is 1HZ.
  delay(1500);
} 
