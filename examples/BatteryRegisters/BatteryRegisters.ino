#include <Wire.h>
#include <STC3105.h>

STC3105 stc;

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  if (!stc.init())
  {
    Serial.println("Failed to detect the battery fuel guage!");
    while (1);
  }

  stc.enableOperation();
}

void loop()
{
  float charge = stc.readCharge();
  uint16_t counter = stc.readCounter();
  float current = stc.readCurrent();
  float voltage = stc.readVoltage();
  uint16_t soc = stc.readSOC();
  
  Serial.print("Charge: ");
  Serial.print(charge);
  Serial.print(" uVh\tCounter: ");
  Serial.print(counter);
  Serial.print(" \tCurrent: ");
  Serial.print(current);
  Serial.print(" mA\tVoltage: ");
  Serial.print(voltage);
  Serial.print(" mV\tSOC: ");
  Serial.println(soc);

  delay(100);
}
