/*
 *  Author  :   Ahmad Yaqoot
 *  Type    :   Standard Types Library
 *  Date    :   29/July/2020
 *  Version :   V1.0
 */

#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef     unsigned char           u8  ;
typedef     unsigned short int      u16 ;
typedef     unsigned long int       u32 ;


typedef     signed char             s8  ;
typedef     signed short int        s16 ;
typedef     signed long int         s32 ;


typedef     float                    f32;
typedef     double                   f64;
typedef     long double             f128;

typedef enum ErrorStatus 
{OK,NOK,INDEX_OUT_OF_RANGE} enuErrorStatus;

#ifndef NULL
#define NULL (void*)0
#endif

#endif
