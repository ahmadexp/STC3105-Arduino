#include <STC3105.h>
#include <Wire.h>

// Defines ///////////////////////////////////////////////////////////

// The Arduino two-wire interface uses a 7-bit number for the address,
// and sets the last bit correctly based on reads and writes

#define STC_3105_ADDRESS 0b1110000


// Constructors //////////////////////////////////////////////////////

STC3105::STC3105(void)
{
  address = STC_3105_ADDRESS;
}

// Public Methods ////////////////////////////////////////////////////

// sets or detects slave address; returns bool indicating success
uint8_t STC3105::init(void)
{
  address = STC_3105_ADDRESS;
  return testWhoAmI();
}

// turns on the fuel guage
void STC3105::enableOperation(void)
{
  uint8_t tmp=readReg(STC_3105_MODE_address);	
  writeReg(STC_3105_MODE_address, tmp|STC_3105_GG_RUN);
}

// writes register
void STC3105::writeReg(uint8_t reg, uint8_t value)
{
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

// reads register
uint8_t STC3105::readReg(uint8_t reg)
{
  uint8_t value;

  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission(false); // restart
  Wire.requestFrom(address, (uint8_t)1);
  value = Wire.read();
  Wire.endTransmission();
  return value;
}

// reads Charge in uVh unit
float STC3105::readCharge(void)
{
  uint16_t charge=((uint16_t)readReg(STC_3105_Charge_H_address))<<8;
  charge+=(uint16_t)readReg(STC_3105_Charge_L_address);	
  return (float)charge*6.70;
}

// reads Counter
uint16_t STC3105::readCounter(void)
{
  uint16_t counter=((uint16_t)readReg(STC_3105_Counter_H_address))<<8;
  counter|=(uint16_t)readReg(STC_3105_Counter_L_address);	
  return counter;
}

// reads Current in uA unit
float STC3105::readCurrent(void)
{
  uint16_t current=((uint16_t)readReg(STC_3105_Current_H_address))<<8;
  current|=(uint16_t)readReg(STC_3105_Current_L_address);	
  return (float)current*11.77;
}

// reads voltage in mV unit
float STC3105::readVoltage(void)
{
  uint16_t voltage=((uint16_t)readReg(STC_3105_Voltage_H_address))<<8;
  voltage|=(uint16_t)readReg(STC_3105_Voltage_L_address);	
  return (float)voltage*2.44;
}

void STC3105::resetAccumulator(void)
{
  uint8_t tmp=readReg(STC_3105_CTRL_address);	
  writeReg(STC_3105_CTRL_address, tmp|STC_3105_GG_RST);
}

// Private Methods ///////////////////////////////////////////////////
uint8_t STC3105::testWhoAmI(void)
{
  return (readReg(STC_3105_REG_ID_address) == STC_3105_ID);
}