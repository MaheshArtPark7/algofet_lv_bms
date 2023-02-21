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
    uint16_t Load_Voltage;        //Stores load Voltage
    uint16_t Pack_Current;        //Stores Pack Current
    uint8_t FET_Status;           //Stores FET Status
    uint16_t CellVoltages;        //Stores Cell Voltages (1-10)
    uint16_t Temperatures;        //Stores Temperatures TS1 and TS3

}TS_AFEdata_s;

extern int16_t app_afe_init(void);
extern int16_t app_afe_tick(void);

#endif /* INC_APP_APP_AFE_H_ */
