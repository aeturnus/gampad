/**
 * @file    Input.h
 * @author  Brandon Nguyen
 * @brief   Driver gampad input
 */

#include <stdint.h>

#include <drivers/tm4c/ADC.h>
#include <drivers/system/switch.h>
#include <drivers/devices/Input.h>

Switch_State switches[NUM_SWITCHES];

static int16_t tare_x = 0;
static int16_t tare_y = 0;

static
void tare(void)
{
  ADC_Data adc;
  int32_t sum_x = 0;
  int32_t sum_y = 0;
  int i;
  for (i = 0; i < 16; ++i) {
    ADC_Read(&adc);
    sum_x += adc.values[0];
    sum_y += adc.values[1];
  }

  int16_t avg_x = sum_x / i;
  int16_t avg_y = sum_y / i;

  tare_x = 0 - avg_x;
  tare_y = 0 - avg_y;
}

void Input_Init(void)
{
  Switch_Init();
  ADC_Init();
  //tare(); // doesn't like the tare function for some reason
  tare_x = -2000;
  tare_y = -1980;
}

void Input_Read(Input_State * readings)
{
  ADC_Data adc;
  ADC_BeginRead(&adc);
  
  int16_t stk_x = 0;
  int16_t stk_y = 0;
  #define HIS_SIZE 4
  static int16_t x_his[HIS_SIZE];
  static int x_his_pos = 0;
  static int32_t x_his_sum = 0;
  static int16_t y_his[HIS_SIZE];
  static int y_his_pos = 0;
  static int32_t y_his_sum = 0;

  // do switch stuff while ADC is being handled 
  Switch_GetStates(switches);
  uint8_t btn = 0;
  btn |= (switches[0] & 0x1) << BTN_L;
  btn |= (switches[1] & 0x1) << BTN_R;
  btn |= (switches[3] & 0x1) << BTN_A;
  btn |= (switches[5] & 0x1) << BTN_B;
  btn |= (switches[4] & 0x1) << BTN_X;
  btn |= (switches[2] & 0x1) << BTN_Y;
  readings->btn = btn;

  while(ADC_FinishRead(&adc) == -1);
  
  stk_x = adc.values[0] + tare_x;
  stk_y = adc.values[1] + tare_y;
  
  // process the averaging filter
  x_his_sum -= x_his[x_his_pos];
  x_his_sum += stk_x;
  x_his[x_his_pos] = stk_x;
  x_his_pos = (x_his_pos + 1) % HIS_SIZE;
  
  y_his_sum -= y_his[y_his_pos];
  y_his_sum += stk_y;
  y_his[y_his_pos] = stk_y;
  y_his_pos = (y_his_pos + 1) % HIS_SIZE;

  readings->stk[STK_X] = x_his_sum / HIS_SIZE;
  readings->stk[STK_Y] = y_his_sum / HIS_SIZE;
}