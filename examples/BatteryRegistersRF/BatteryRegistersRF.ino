#include <Wire.h>
#include <STC3105.h>
#include <ZigduinoRadio.h>

STC3105 stc;

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  RF.begin(11);
  
  RF.setParam(RP_TXPWR(3));
  RF.setParam(RP_DATARATE(MOD_OQPSK_1000));

  if (!stc.init())
  {
    Serial.println("Failed to detect the battery fuel guage!");
    while (1);
  }

  stc.enableOperation();
}

void loop()
{
  char writeBuffer[12];
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
  
  RF.beginTransmission();
  RF.write("Charge: ");
  itoa((int16_t)charge, writeBuffer, 10);
  RF.write(writeBuffer);
  RF.write(" uVh\tCounter: ");
  utoa(counter, writeBuffer, 10);
  RF.write(writeBuffer);
  RF.write(" \tCurrent: ");
  itoa((int16_t)current, writeBuffer, 10);
  RF.write(writeBuffer);
  RF.write(" mA\tVoltage: ");
  itoa((int16_t)voltage, writeBuffer, 10);
  RF.write(writeBuffer);
  RF.write(" mV\tSOC: ");
  utoa(soc, writeBuffer, 10);
  RF.write(writeBuffer);
    
  RF.endTransmission();

  delay(100);
}
