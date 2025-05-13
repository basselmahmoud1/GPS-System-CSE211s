/****************************************************************/
/******* Author    : Habiba Khalil              *****************/
/******* Date      : 12/4/2025                  *****************/
/******* File Name : BIT_MATH.h                 *****************/
/****************************************************************/

#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SetBit(reg, bit)      reg |= (1 << bit)
#define ClrBit(reg, bit)      reg &= (~(1 << bit))
#define ToggleBit(reg, bit)   reg ^= (1 << bit)
#define GetBit(reg, bit)      ((reg >> bit) & 1)
#define IsHigh(reg, bit)      ((reg) & (1 << (bit)))
#define IsLow(reg, bit)       (!((reg) & (1 << (bit))))

#endif