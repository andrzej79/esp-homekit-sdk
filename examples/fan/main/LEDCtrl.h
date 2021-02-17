#ifndef LEDCTRL_H
#define LEDCTRL_H

#include <driver/gpio.h>
#define IO_LED_PIN    GPIO_NUM_16

void ledCtrlInit(int freq);
void ledCtrlSetVal(float percent);

#endif // LEDCTRL_H
