

#include <SFE_BMP180.h>
#include <Wire.h>
// You will need to create an SFE_BMP180 object, here called "pressure":
SFE_BMP180 pressure;
void setup()
{
  Serial.begin(9600);
  Serial.println("REBOOT");
  // Initialize the sensor (it is important to get calibration values stored on the device).
  (pressure.begin());   
}
void loop()
{
  char status;
  double T,P,p0,a;
  status = pressure.startTemperature();
  {
    // Wait for the measurement to complete:
    delay(status);
    status = pressure.getTemperature(T);
    {
      // Print out the measurement:
      Serial.print("temperature: ");
      Serial.print(T,2);
      Serial.print(" deg C, ");
      status = pressure.startPressure(3);
      {
        // Wait for the measurement to complete:
        delay(status);
        status = pressure.getPressure(P,T);
        {
          Serial.print(P,2);
          Serial.println(" mb, ");
        delay(1000);
        }
      }
      }
  }
  }
