#ifndef __INPUT_H__
#define __INPUT_H__
/**
 * @file    Input.h
 * @author  Brandon Nguyen
 * @brief   Driver gampad input
 */

#include <stdint.h>

typedef enum Input_Sticks_enum
{
  STK_X = 0,
  STK_Y,
  STK_NUM
} Input_Sticks;

typedef enum Input_Buttons
{
  BTN_A = 0,
  BTN_B,
  BTN_X,
  BTN_Y,
  BTN_L,
  BTN_R,
  BTN_NUM
} Input_Buttons;

/**
 * @struct    Input_State
 * @brief     Holds input data
 */
typedef struct Input_State_str
{
  int16_t stk[2];
  int8_t  btn;
} Input_State;


/**
 * @fn          Input_Init
 * @brief       Initializes the Input driver
 */
void Input_Init(void);

/**
 * @fn          Input_Read
 * @brief       Gets input readings
 * @param[out]  readings  Place to write the input readings to
 */
void Input_Read(Input_State * readings);

static inline
int16_t Input_Stick(Input_State * input, Input_Sticks stick)
{
  return input->stk[stick];
}

static inline
uint8_t Input_Button(Input_State * input, Input_Buttons button)
{
  return (input->btn >> button) & 0x1;
}

#endif//__INPUT_H__