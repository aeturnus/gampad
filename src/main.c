#include <stdio.h>
#include <string.h>

#include <drivers/tm4c/Wrappers.h>
#include <drivers/tm4c/Timer0.h>

#include <drivers/system/hw.h>
#include <drivers/system/time.h>
#include <drivers/system/switch.h>
#include <drivers/system/display.h>

#include <drivers/devices/input.h>

static void InitializeHardware(void)
{
  Hardware_Init();
  Time_Init();
  Display_Init();
  Switch_Init();
  Input_Init();
}

static int flag = 0;
int main(void)
{
  InitializeHardware();
  Display_DrawString(0, 0, "Hello world!", 0xFFFF, 0x0000, 1);
  
  unsigned int cell_h = Display_GetCellHeight();
  unsigned int cell_w = Display_GetCellWidth();
  char buffer[32];
  Input_State input;
  /*
  for(;;) {
    Input_Read(&input);
    int row = 1;
    
    sprintf(buffer, "Stick X: %5d", Input_Stick(&input, STK_X));
    Display_DrawString(0, cell_h * (row++), buffer, 0xFFFF, 0x0000, 1);
    
    sprintf(buffer, "Stick Y: %5d", Input_Stick(&input, STK_Y));
    Display_DrawString(0, cell_h * (row++), buffer, 0xFFFF, 0x0000, 1);
    
    sprintf(buffer, "Button A: %d", Input_Button(&input, BTN_A));
    Display_DrawString(0, cell_h * (row++), buffer, 0xFFFF, 0x0000, 1);
    
    sprintf(buffer, "Button B: %d", Input_Button(&input, BTN_B));
    Display_DrawString(0, cell_h * (row++), buffer, 0xFFFF, 0x0000, 1);
    
    sprintf(buffer, "Button X: %d", Input_Button(&input, BTN_X));
    Display_DrawString(0, cell_h * (row++), buffer, 0xFFFF, 0x0000, 1);
    
    sprintf(buffer, "Button Y: %d", Input_Button(&input, BTN_Y));
    Display_DrawString(0, cell_h * (row++), buffer, 0xFFFF, 0x0000, 1);
    
    sprintf(buffer, "Button L: %d", Input_Button(&input, BTN_L));
    Display_DrawString(0, cell_h * (row++), buffer, 0xFFFF, 0x0000, 1);
    
    sprintf(buffer, "Button R: %d", Input_Button(&input, BTN_R));
    Display_DrawString(0, cell_h * (row++), buffer, 0xFFFF, 0x0000, 1);
  }
  */
  return 0;
}