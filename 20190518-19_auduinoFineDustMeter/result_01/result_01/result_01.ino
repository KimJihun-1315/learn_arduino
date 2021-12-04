#include <PMsensor.h>
#include <DHT.h>

PMsensor PM;
DHT dht(7, DHT11);

void setup()
{
  Serial.begin(9600);

  PM.init(3, A0);
  dht.begin();
  
  Serial.println("Start PM Sensor");
}

void loop()
{
  float pm = 0;
  int err = PMsensorErrSuccess;

  float humi = dht.readHumidity();                                                   // 습도 측정
  float temp = dht.readTemperature();                                            // 온도 측정
  float discomfort = ( 0.81*temp ) + ( 0.01* humi * (0.99*temp-14.3) ) + 46.3;       // 습도 계산및 측정
  
  if ((err = PM.read(&pm, true, 0.1)) != PMsensorErrSuccess)     //미세먼지 민감도 조절
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
  
  delay(3000);
}
