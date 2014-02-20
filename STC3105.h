#ifndef STC3105_h
#define STC3105_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

//Control Registers
#define STC_3105_MODE_address           0x00
#define STC_3105_CTRL_address           0x01
#define STC_3105_Charge_L_address       0x02
#define STC_3105_Charge_H_address       0x03
#define STC_3105_Counter_L_address      0x04
#define STC_3105_Counter_H_address      0x05
#define STC_3105_Current_L_address      0x06
#define STC_3105_Current_H_address      0x07
#define STC_3105_Voltage_L_address      0x08
#define STC_3105_Voltage_H_address      0x09
#define STC_3105_SOC_Base_L_address     0x0A
#define STC_3105_SOC_Base_H_address     0x0B
#define STC_3105_Alarm_SOC_L_address    0x0C
#define STC_3105_Alarm_SOC_H_address    0x0D
#define STC_3105_Alarm_Volt_address     0x0E
#define STC_3105_Current_Thres_address  0x0F
#define STC_3105_Relax_count_address    0x10

//Device ID Registers
#define STC_3105_REG_ID_address         0x18
#define STC_3105_ID                     0x12

//REG_Mode flags
#define STC_3105_PWR_SAVE               0x04
#define STC_3105_ALM_ENA                0x08
#define STC_3105_GG_RUN                 0x10

//REG_Ctrl flags
#define STC_3105_PWR_IO0DATA            0x01
#define STC_3105_GG_RST                 0x02
#define STC_3105_GG_EOC                 0x04
#define STC_3105_VM_EOC                 0x08
#define STC_3105_PORDET                 0x10
#define STC_3105_ALM_SOC                0x20
#define STC_3105_ALM_VOLT               0x40

//Unit values
#define VOLTAGE_UNIT                    2.44
#define CURRENT_UNIT                    0.01177/0.01
#define CHARGE_UNIT                     6.70


class STC3105
{
  public:
    STC3105(void);
    uint8_t init(void);
    void enableOperation(void);

    void writeReg(uint8_t, uint8_t);
    uint8_t readReg(uint8_t);

    float    readCharge(void);
    uint16_t readCounter(void);
    uint16_t readSOC(void);
    float    readCurrent(void);
    float    readVoltage(void);
    void     resetAccumulator(void);
  private:
    uint8_t  address;
    uint8_t  testWhoAmI(void);
};

#endif