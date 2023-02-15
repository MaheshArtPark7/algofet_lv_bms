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
    uint16_t Load_Voltage;
    uint16_t Pack_Current;
    uint8_t FET_Status;
    uint16_t Cell1Voltage;
    uint16_t Cell2Voltage;
    uint16_t Cell3Voltage;
    uint16_t Cell4Voltage;
    uint16_t Cell5Voltage;
    uint16_t Cell6Voltage;
    uint16_t Cell7Voltage;
    uint16_t Cell8Voltage;
    uint16_t Cell9Voltage;
    uint16_t Cell10Voltage;
    uint16_t Cell11Voltage;
    uint16_t Cell12Voltage;
    uint16_t Cell13Voltage;
    uint16_t Cell14Voltage;
    uint16_t Cell15Voltage;
    uint16_t Cell16Voltage;
    //Add TS1,TS2, TS3

}TS_AFEdata_s;

extern int16_t app_afe_init(void);
extern int16_t app_afe_tick(void);

#endif /* INC_APP_APP_AFE_H_ */
