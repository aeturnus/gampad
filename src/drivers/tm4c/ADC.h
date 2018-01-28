#ifndef __ADC_H__
#define __ADC_H__
/**
 * @file    ADC.h
 * @author  Brandon Nguyen
 * @brief   Driver for the TM4C ADC
 */

#include <stdint.h>

#define ADC_SIZE 2 
typedef struct ADC_Data_str
{
  int flag;
  uint16_t values[ADC_SIZE];
} ADC_Data;

/**
 * @fn        ADC_Init
 * @brief     Initializes the ADC
 */
void ADC_Init(void);


/**
 * @fn      ADC_Read
 * @brief   Synchronously perform ADC read
 *
 * Blocking implementation. Clears the flag and
 * when complete, flag in data will be set.
 */
void ADC_Read(ADC_Data * data);

/**
 * @fn      ADC_BeginRead
 * @brief   Kicks off a full ADC read
 *
 * Concurrent implementation. Clears the flag and
 * when complete, flag in data will be set.
 */
void ADC_BeginRead(ADC_Data * data);

/**
 * @fn 		ADC_FinishRead
 * @brief 	Finishes up read
 * @return  -1 if not done, 0 if success
 */

int ADC_FinishRead(ADC_Data * data);


#endif//__ADC_H__
