#include <stdint.h>
#include <tm4c123gh6pm.h>
#include <drivers/tm4c/SysTick.h>
#include <drivers/system/switch.h>

#define SWITCH_MASK 0x0F

void Switch_Init(void) {
  SYSCTL_RCGCGPIO_R |= 0x28;            // activate Port D and F
  while((SYSCTL_PRGPIO_R&0x28) == 0){};
  GPIO_PORTD_DIR_R   &= ~SWITCH_MASK;    // PD0-3 is an input
  GPIO_PORTD_AFSEL_R &= ~SWITCH_MASK;      // regular port function
  GPIO_PORTD_AMSEL_R &= ~SWITCH_MASK;      // disable analog on PC0-3
  GPIO_PORTD_PCTL_R  &= ~(0x0000FFFF); // PCTL GPIO on PD0-3
  GPIO_PORTD_DEN_R   |= SWITCH_MASK;         // PD5-7 enabled as a digital port

  GPIO_PORTF_LOCK_R  = 0x4C4F434B;       //Unlock PF7
  GPIO_PORTF_CR_R    = 0xFF;               
  GPIO_PORTF_AMSEL_R = (GPIO_PORTF_AMSEL_R&~0x1F);
  GPIO_PORTF_AFSEL_R = (GPIO_PORTF_AFSEL_R&~0x1F);
  GPIO_PORTF_DIR_R   = (GPIO_PORTF_DIR_R&~0x11)|(0x0E);
  GPIO_PORTF_PCTL_R  = GPIO_PORTF_PCTL_R&(~0x000FFFFF);
  GPIO_PORTF_DEN_R  |= 0x1F;
  GPIO_PORTF_PUR_R  |= 0x11; //Enable pullup resistors
}

uint8_t Switch_Input(void) {
  uint8_t val = 0;
  val |= ((GPIO_PORTF_DATA_R >> 0) & 0x1) << 0;
  val |= ((GPIO_PORTF_DATA_R >> 4) & 0x1) << 1;
  val |= (GPIO_PORTD_DATA_R & SWITCH_MASK) << 2;
  return val;
}

#define DELAY 160

uint8_t Switch_GetDebounce() {
  uint8_t in, old;
  uint32_t time;
  time = 1000;
  old = Switch_Input();
  while(time) {
    //SysTick_Wait(DELAY);
    in = Switch_Input();
    if(in == old) {
      time--;
    } else {
      time = 1000;
      old = in;
    }
  }
  return old;
}

void Switch_GetStatesDebounced(Switch_State *states) {
  uint8_t switchStates = Switch_GetDebounce();
  
  for(uint8_t i = 0; i < NUM_SWITCHES; i++) {
    states[i] = switchStates & (0x01 << i) ? Switch_Off : Switch_On;
  }
}

void Switch_GetStates(Switch_State * states) {
  uint8_t switchStates = Switch_Input();
  
  for(uint8_t i = 0; i < NUM_SWITCHES; i++) {
    states[i] = (switchStates & (0x01 << i)) ? Switch_Off : Switch_On;
  }
}
