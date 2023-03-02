#pragma once

#include <stdint.h>

// when USE_SIGFLOAT enabed the sigfloat_t must be defined
// typedef double sigfloat_t;
#define CAN_CODEGEN_USE_CANSTRUCT
// when USE_CANSTRUCT enabled __CoderDbcCanFrame_t__ must be defined
// #include "{header_with_can_struct}"
// typedef {can_struct} __CoderDbcCanFrame_t__;
typedef struct
{
	 uint32_t MsgId; //(CAN Frame message ID)
	 uint8_t DLC; //(CAN Frame payload length field)
	 uint8_t Data[8]; //(CAN Frame payload data)
	 uint8_t IDE; //(CAN Frame Extended (1) / Standard (0) ID type)

}__CoderDbcCanFrame_t__;
// if you need to allocate rx and tx messages structs put the allocation macro here
// #define __DEF_{your_driver_name}__

