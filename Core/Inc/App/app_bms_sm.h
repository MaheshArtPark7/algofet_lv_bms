/*
 * app_bms_sm.h
 *
 *  Created on: Jan 01, 2023
 */

#ifndef INC_APP_TASK_1HZ_H_
#define INC_APP_TASK_1HZ_H_

typedef enum
{
    eBmsState_Unknown = 0,
    eBmsState_Fault,
    eBmsState_Idle,
    eBmsState_Drive,
    eBmsState_Charge,
    eBmsState_Sleep,
    eBmsMaxStates
} TeBmsState_t;

typedef enum
{
    eBmsStateRequest_None = 0,
    eBmsStateRequest_Drive,
    eBmsStateRequest_Charge,
    eBmsStateRequest_Sleep
} TeBmsStateRequest_t;

typedef struct
{
    void (*entry)();
    void (*main)();
    void (*exit)();
} TsBmsStateCallback_t;

typedef struct
{
    TeBmsState_t state;
    TsBmsStateCallback_t callback;
} TsBmsStateModule_t;

typedef struct
{
    bool inhibit_drive_entry;
    bool inhibit_drive;
    bool inhibit_charge_entry;
    bool inhibit_charge;
    TeBmsStateRequest_t request;
    TeBmsState_t prev_state;
    TeBmsState_t curr_state;
    TeBmsState_t next_state;
    TsBmsStateModule_t sm_module;

} TsStateMachine_t;

void app_bms_sm_init(void);

#endif /* INC_APP_TASK_1HZ_H_ */
