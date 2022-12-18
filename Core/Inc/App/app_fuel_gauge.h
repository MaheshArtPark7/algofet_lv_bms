/*
 * app_fuel_gauge.h
 *
 *  Created on: 24-Aug-2022
 */

#ifndef INC_APP_APP_FUEL_GAUGE_H_
#define INC_APP_APP_FUEL_GAUGE_H_

#include "app_defines.h"

#define BQ_WR_ADDR 0xAA // I2C address for reading: 7bit address (0x55) + [0] write bit (0xAA)
#define BQ_RD_ADDR 0xAB // I2C address for writing: 7bit address (0x55) + [1] read bit  (0xAB)
#define BQ_RD_BUFFER_LEN 20u
#define BQ_NUM_BURST_RD_BLOCKS 4u

/* Gauge Data Block Config Structure */
typedef struct
{
    uint8_t Addr; // Start Address of the DataBlock to read
    uint8_t Len;  // Length of the DataBlock in bytes to read
} TsDataBlockConfig_t;

typedef struct
{
    /* standard data cmd */
    /* Data_Block_0 - start_address = 0x02 and data_len = 18 (bytes) */
    uint16_t Control;            // 0x00  array[0]
    uint8_t StateOfCharge;       // 0x02  array[2]      m = 1
    uint8_t MaxError;            // 0x03  array[3]      m = 3
    uint16_t RemainingCapacity;  // 0x04  array[4]      m = 3
    uint16_t FullChargeCapacity; // 0x06  array[6]      m = 3+
    uint16_t vStack;             // 0x08  array[8]      m = 1 [milli volts]
    uint16_t AvgCurrent;         // 0x0A  array[10]     m = 2
    uint16_t Temperature;        // 0x0C  array[12]     m = 2 [(temp/10) - 273.15] *C
    uint16_t Flags;              // 0x0E  array[14]
    uint16_t Current;            // 0x10  array[16]     m = 1
    uint16_t FlagsB;             // 0x12  array[18]
    /* End of Standard Data Commands */
} TsGaugeData_t;

typedef struct
{
    int SoC;
    float RemCap;
    float FullChgCap;
    float vStack;
    float AvgCurrent;
    float BatTemp;
    float InstCurrent;
} TsAppGaugeData_t;

typedef enum
{
    eAlgoFet_BLOCK0 = 0,
    eAlgoFet_BLOCK1,
    eAlgoFet_TotalNumBlocks
}TeAlgoFet_FuelGauge_DataBlocks;

extern int16_t app_gauge_init(void);
extern int16_t app_gauge_tick(void);

#endif /* INC_APP_APP_FUEL_GAUGE_H_ */
