

#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(reg , bit)     reg |= (1<<bit)
#define Clear_BIT(reg , bit)   reg &= ~(1<<bit)
#define Toggle_BIT(reg , bit)  reg ^= (1<<bit)
#define GET_BIT(reg , bit)    ((reg >> bit) & 1)




#endif