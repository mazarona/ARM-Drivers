#include "../Mcal/Port/Inc/Port.h"
#include "../Mcal/Gpio/Inc/Gpio.h"
#include "../Mcal/Nvic/Inc/Nvic.h"
#include "../Mcal/Sys_Tick/Inc/SysTick.h"
void sysTickISR(void);
int onTimeInSeconds = 1;
int offTimeInSeconds = 1;
int setOnOrOffFlag = 0;
int main() {
  Nvic_Init();
  Port_Init();
  SysTick_SetISRCallBack(sysTickISR);
  SysTick_SetDuration(onTimeInSeconds, offTimeInSeconds);
  SysTick_Init();
  while (1) {
		if(!Gpio_ReadChannel(GPIO_Channel_F0)){
			while(!Gpio_ReadChannel(GPIO_Channel_F0));
			setOnOrOffFlag = !setOnOrOffFlag;
		}
		if(!Gpio_ReadChannel(GPIO_Channel_F4)){
			while(!Gpio_ReadChannel(GPIO_Channel_F4));
			if(setOnOrOffFlag) onTimeInSeconds += 1;
			else offTimeInSeconds += 1;
			SysTick_SetDuration(onTimeInSeconds, offTimeInSeconds);
		}
  }
}

void sysTickISR(void) {
  static uint32 isrCount = 0;
  static uint32 currentLedState = 0;
  isrCount++;
  if (isrCount > numberOfOverFlows) {
    if (currentLedState == 1) {
      currentLedState = 0;
      Gpio_WriteChannel(GPIO_Channel_F1, GPIO_LEVEL_LOW);
      numberOfOverFlows = offNumberOfOverFlows;
    } else {
      currentLedState = 1;
      Gpio_WriteChannel(GPIO_Channel_F1, GPIO_LEVEL_HIGH);
      numberOfOverFlows = onNumberOfOverFlows;
    }
    isrCount = 0;
  }
}
