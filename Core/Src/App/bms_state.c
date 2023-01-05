

static TsStateMachine_t state_machine;

static const TsBmsStateModule_t bms_sm[eTotalStates] =
    {
        {.state = eBmsState_Fault,
         .callback = {NULL, state_fault_main, NULL}},
        {.state = eBmsState_Idle,
         .callback = {NULL, state_idle_main, NULL}},
        {.state = eBmsState_Drive,
         .callback = {state_drive_entry, state_drive_main, NULL}},
        {.state = eBmsState_Charge,
         .callback = {state_charge_entry, state_charge_main, NULL}},
        {.state = eBmsState_Sleep,
         .callback = {state_sleep_entry, state_sleep_main, state_sleep_exit}}};

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

/* BMS StateMachine State Transition Handler */
int16_t bms_state_transition_handler(TeBmsState state)
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
