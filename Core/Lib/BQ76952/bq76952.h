/*
 * bq76952.h
 *
 *  Created on: 24-Aug-2022
 */

#ifndef __BQ76952_H_
#define __BQ76952_H_

#include "app_defines.h"

typedef struct
{
    uint8_t len;
    union
    {
        struct
        {
            uint16_t power_cfg_reg;
            uint16_t x;
            uint16_t reg_val;
        };
        uint8_t buffer[4];
    };
}TsBmsPower_cfg;
extern int16_t bq76952_init(void);

#endif /* __BQ76952_H_ */
