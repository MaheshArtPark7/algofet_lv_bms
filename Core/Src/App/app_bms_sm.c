/*
 * app_bms_sm.c
 *
 *  Created on: 01-Jan-2023
 */

#include "app_bms_sm.h"

static TsStateMachine_t state_machine;

static const TsBmsStateModule_t bms_sm[eBmsMaxStates] =
    {
        {.state = eBmsState_Unknown,
         .callback = {NULL, sm_state_unknown_main, NULL}},
        {.state = eBmsState_Fault,
         .callback = {sm_state_fault_entry, sm_state_fault_main, sm_state_fault_exit}},
        {.state = eBmsState_Idle,
         .callback = {sm_state_idle_entry, sm_state_idle_main, sm_state_idle_exit}},
        {.state = eBmsState_Drive,
         .callback = {sm_state_drive_entry, sm_state_drive_main, sm_state_drive_exit}},
        {.state = eBmsState_Charge,
         .callback = {sm_state_charge_entry, sm_state_charge_main, sm_state_charge_exit}},
        {.state = eBmsState_Sleep,
         .callback = {sm_state_sleep_entry, sm_state_sleep_main, sm_state_sleep_exit}}};

static void sm_state_unknown_main(TsStateMachine_t *const sm);

static void sm_state_fault_entry(TsStateMachine_t *const sm);
static void sm_state_fault_main(TsStateMachine_t *const sm);
static void sm_state_fault_exit(TsStateMachine_t *const sm);

static void sm_state_idle_entry(TsStateMachine_t *const sm);
static void sm_state_idle_main(TsStateMachine_t *const sm);
static void sm_state_idle_exit(TsStateMachine_t *const sm);

static void sm_state_drive_entry(TsStateMachine_t *const sm);
static void sm_state_drive_main(TsStateMachine_t *const sm);
static void sm_state_drive_exit(TsStateMachine_t *const sm);

static void sm_state_charge_entry(TsStateMachine_t *const sm);
static void sm_state_charge_main(TsStateMachine_t *const sm);
static void sm_state_charge_exit(TsStateMachine_t *const sm);

static void sm_state_sleep_entry(TsStateMachine_t *const sm);
static void sm_state_sleep_main(TsStateMachine_t *const sm);
static void sm_state_sleep_exit(TsStateMachine_t *const sm);

void app_bms_sm_init(void)
{
    app_bms_state_transition_handler(eBmsState_Idle);
}

/* BMS StateMachine State Transition Handler */
int16_t app_bms_state_transition_handler(TeBmsState state)
{
    int16_t exit_code = SYS_ERR;

    // 1.Exit current state
    if (NULL != bms_sm[state_machine.curr_state].callback.exit)
    {
        bms_sm[state_machine.curr_state].callback.exit();
    }

    // 2. Update State Transition
    state_machine.prev_state = state_machine.curr_state;
    state_machine.curr_state = state;

    // 3. Enter New State
    if (NULL != bms_sm[state_machine.curr_state].callback.entry)
    {
        bms_sm[state_machine.curr_state].callback.entry();
        exit_code = SYS_OK;
    }
    else
    {
        exit_code = SYS_FAIL;
    }

    return exit_code;
}


// ------------------ DRIVE STATE ------------------------------
/* Drive Entry */
static void sm_state_drive_entry(TsStateMachine_t *const sm)
{
    //TODO Close FET's
}

/* Drive Main */
static void sm_state_drive_main(TsStateMachine_t *const sm)
{
    if((sm->inhibit_charge_entry == true) && (sm->inhibit_drive_entry == true))
    {
        app_bms_state_transition_handler(eBmsState_Fault);
    }
    else
    {
        // Update BMS state to Drive
        // Wait for drive exit
        switch(sm->request)
        {
        case eBmsStateRequest_Charge:
            if(sm->inhibit_charge_entry == false)
            {
                app_bms_state_transition_handler(eBmsState_Charge);
            }
            break;
        case eBmsState_Idle:
            app_bms_state_transition_handler(eBmsState_Idle);
            break;
        case eBmsStateRequest_Sleep:
            app_bms_state_transition_handler(eBmsState_Sleep);
            break;
        default: // Continue in Drive State
            break;
        }
    }
}

/* Drive Exit */
static void sm_state_drive_exit(TsStateMachine_t *const sm)
{
    // If requested Charge Connect to "charge_main"
    // Else Open Fet's and Connect to next State
}

// ------------------ CHARGE STATE ------------------------------
/* Charge Enter */
static void sm_state_charge_entry(TsStateMachine_t *const sm)
{
}

/* Charge Main*/
static void sm_state_charge_main(TsStateMachine_t *const sm)
{
    if((sm->inhibit_charge_entry == true) && (sm->inhibit_drive_entry == true))
    {
        app_bms_state_transition_handler(eBmsState_Fault);
    }
    else
    {
        switch(sm->request)
        {
        case eBmsStateRequest_Drive:
            if((sm->inhibit_drive == false) && (sm->inhibit_drive_entry == false))
            {
                app_bms_state_transition_handler(eBmsState_Drive);
            }
            break;
        case eBmsState_Idle:
            app_bms_state_transition_handler(eBmsState_Idle);
            break;
        case eBmsStateRequest_Sleep:
            app_bms_state_transition_handler(eBmsState_Sleep);
            break;
        default: // Continue in Charge State
            break;
        }
    }
}

/* Charge Exit */
static void sm_state_charge_exit(TsStateMachine_t *const sm)
{
    // Stop Balancing
}

// ------------------ FAULT STATE ------------------------------
/* Fault entry */
static void sm_state_fault_entry(TsStateMachine_t *const sm)
{
    //TODO Open FET's
}

/* Fault Main */
static void sm_state_fault_main(TsStateMachine_t *const sm)
{
    if((sm->inhibit_charge_entry == false) && (sm->inhibit_drive_entry == false))
    {
        app_bms_state_transition_handler(eBmsState_Idle);
    }
    else
    {
        // Continue in fault state
    }
}

/* Fault exit */
static void sm_state_fault_exit(TsStateMachine_t *const sm)
{
}

// ------------------ IDLE STATE ------------------------------
/* Idle entry */
static void sm_state_idle_entry(TsStateMachine_t *const sm)
{
    //TODO: Command FET's to Open

    // Jump to Idle Main
    sm_state_idle_main();
}

/* Idle main */
static void sm_state_idle_main(TsStateMachine_t *const sm)
{
    if((sm->inhibit_charge_entry == true) && (sm->inhibit_drive_entry == true))
    {
        app_bms_state_transition_handler(eBmsState_Fault);
    }
    else
    {
        switch(sm->request)
        {
        case eBmsStateRequest_Drive:
            if(sm->inhibit_drive_entry == false)
            {
                app_bms_state_transition_handler(eBmsState_Drive);
            }
            break;
        case eBmsStateRequest_Charge:
            if(sm->inhibit_charge_entry == false)
            {
                app_bms_state_transition_handler(eBmsState_Charge);
            }
            break;
        case eBmsStateRequest_Sleep:
            // TODO Check for sleep conditions
            app_bms_state_transition_handler(eBmsState_Sleep);
            break;
        default: // Continue in Idle State
        break;
        }
    }

}

/* Idle exit */
static void sm_state_idle_exit(TsStateMachine_t *const sm)
{
}

// ------------------ SLEEP STATE ------------------------------
/* Sleep entry */
static void sm_state_sleep_entry(TsStateMachine_t *const sm)
{
}

