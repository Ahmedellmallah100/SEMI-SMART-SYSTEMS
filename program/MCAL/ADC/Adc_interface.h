#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include "../../Library/std_Bytes.h"
#include "../../Library/bit_math.h"


void AdcVoid_init(void);
u16 ADC_u16ReadASynchronus(u8 u8ChannelNumber);

#endif