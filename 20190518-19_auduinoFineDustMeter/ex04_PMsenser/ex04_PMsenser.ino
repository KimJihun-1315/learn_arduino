//PMsenser를 이용한 미세먼지측정
#include <PMsensor.h>

PMsensor PM;

void setup()
{
  Serial.begin(9600);

  PM.init(3, A0);

  Serial.println("Start PM Sensor");
}

void loop()
{
  float pm = 0;
  int err = PMsensorErrSuccess;
  
  if ((err = PM.read(&pm, true, 1)) != PMsensorErrSuccess)
  {
    Serial.print("Error = ");
    Serial.println(err);
    delay(3000);
    return;
  }
  
  Serial.print("PM : ");
  Serial.print(pm);
  Serial.println(" ug/m^3");
  
  delay(3000);
} 
