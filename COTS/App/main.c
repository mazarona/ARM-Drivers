#include "../Mcal/Port/Inc/Port.h"
#include "../Mcal/Gpio/Inc/Gpio.h"
#include "../Mcal/Nvic/Inc/Nvic.h"
#include "../Mcal/Sys_Tick/Inc/SysTick.h"
void sysTickISR(void);
int onTimeInSeconds = 0;
int offTimeInSeconds = 0;
int numberOfPresses = 0;
int getInput = 1;

int main() {
  Nvic_Init();
  Port_Init();
  SysTick_SetISRCallBack(sysTickISR);

  while (1) {
		if(getInput){
			/* Check Switch 1 */
			if(!Gpio_ReadChannel(GPIO_Channel_F0)){
				while(!Gpio_ReadChannel(GPIO_Channel_F0));
				if(numberOfPresses < 2) numberOfPresses += 1;
				else{
					getInput = 0;
					SysTick_SetDuration(onTimeInSeconds, offTimeInSeconds);
					SysTick_Init();	
				}
			}
			
			/* Check Switch 1 */
			if(!Gpio_ReadChannel(GPIO_Channel_F4)){
				while(!Gpio_ReadChannel(GPIO_Channel_F4));
				if(numberOfPresses == 1) onTimeInSeconds += 1;
				else if(numberOfPresses == 2) offTimeInSeconds += 1;
			}
			
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
