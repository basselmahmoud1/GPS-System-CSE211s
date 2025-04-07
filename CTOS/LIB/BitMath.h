/*
 * BitMath.h
 *
 * Created: 25/08/2024 06:47:02
 *  Author: Khaled Ismail
 */ 


#ifndef BITMATH_H_
#define BITMATH_H_


#define SET_BIT(reg,pin) reg |=(1<<pin)
#define CLR_BIT(reg,pin) reg &=(~(1<<pin))
#define GET_BIT(reg,pin) (reg>>pin)&1
#define TGL_BIT(REG,BIT) REG^=(1<<BIT)
#define MaskReg(reg,mask) reg&=mask 
#define PostMaskSet(reg,bits,shift) reg |=(bits<<shift)


#endif /* BITMATH_H_ */