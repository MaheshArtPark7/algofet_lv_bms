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

    uint16_t FETs_CONTROL ;
    uint16_t REG0config;
    uint16_t DFETOFFpinConfig;
    uint16_t TS3config;
    uint16_t DCHGPinconfig;
    uint16_t DDSGPinconfig;
    uint16_t vCellModecmd ;
    uint16_t enabledProtectionsA ;
    uint16_t enabledProtectionsB ;
    uint16_t enabledProtectionsC ;
    uint16_t CHGFETprotectionsA;
    uint16_t CHGFETprotectionsB;
    uint16_t CHGFETprotectionsC;
    uint16_t DSGFETprotectionsA;
    uint16_t DSGFETprotectionsB;
    uint16_t DSGFETprotectionsC;
    uint16_t DefaultalarmMask;
    uint16_t FEToptions;
    uint16_t prechargeStartVoltage;
    uint16_t prechargeStopVoltage;
    uint16_t Predischargetimeout;
    uint16_t PredischargestopDelta;
    uint16_t Balancingconfiguration;
    uint16_t CUVthreshold;
    uint16_t COVthreshold;
    uint16_t OCCthreshold;
    uint16_t OCD1threshold;
    uint16_t SCDthreshold;
    uint16_t SCDdelay;
    uint16_t SCDLlatchLimit;

}TS_AFEramreg_s;

typedef struct
{
    uint16_t device_number;
    uint16_t stack_vol;
    uint16_t pack_vol;
    uint16_t load_vol;         //Stores load Voltage
    uint16_t pack_curr;        //Stores Pack Current
    uint16_t cellvoltages[10];    //Stores Cell Voltages (1-10)
    uint16_t temps[2];     //Stores Temperatures TS1 and TS3

}TS_AFEdata_s;

extern int16_t app_afe_data_read(void);
extern int16_t app_afe_can_message_update(void);
extern int16_t app_afe_init(void);
extern int16_t app_afe_tick(void);

#endif /* INC_APP_APP_AFE_H_ */
