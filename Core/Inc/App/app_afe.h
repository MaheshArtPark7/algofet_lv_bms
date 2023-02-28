/*
 * app_afe.h
 *
 *  Created on: 24-Aug-2022
 */

#ifndef INC_APP_APP_AFE_H_
#define INC_APP_APP_AFE_H_

#include "app_defines.h"

typedef struct
{

}TS_FETcotrol_s;

typedef struct
{
    uint16_t vCellModecmd ; //0x03C3 for 6S | 0x0303 for 4S
    uint16_t FETs_CONTROL ;
    uint16_t enabledProtectionsA ;
    uint16_t enabledProtectionsB ;
    uint16_t prechargeStartVoltage;
    uint16_t prechargeStopVoltage;
    uint16_t TS3config;

}TS_AFEramreg_s;

typedef struct
{
    uint16_t Device_Number;       //Stores Device Number
    float Stack_Voltage;          //Stores Stack Voltage
    float Pack_Voltage;           //Stores Pack Voltage
    float Load_Voltage;           //Stores Load Voltage
    uint16_t Pack_Current;           //Stores Pack Current
    float CellVoltages[10];    //Stores Cell Voltages (1-10)
    float Temperatures[2];     //Stores Temperatures TS1 and TS3

}TS_AFEinfo_s;


typedef struct
{
    uint16_t device_number;
    uint16_t stack_vol;
    uint16_t pack_vol;
    uint16_t load_vol;  //Stores load Voltage
    float pack_curr;        //Stores Pack Current
    uint16_t cellvoltages[10];    //Stores Cell Voltages (1-10)
    uint16_t temps[2];     //Stores Temperatures TS1 and TS3

}TS_AFEdata_s;

extern int16_t afe_data_read(void);
extern int16_t app_afe_init(void);
extern int16_t app_afe_tick(void);

#endif /* INC_APP_APP_AFE_H_ */
