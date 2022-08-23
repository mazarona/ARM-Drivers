#include "../Mcal/Port/Inc/Port.h"
#include "../Mcal/Gpio/Inc/Gpio.h"
int main() {
  Port_Init();
  Gpio_WriteChannel(GPIO_Channel_A0, GPIO_LEVEL_HIGH);
  Gpio_WriteChannel(GPIO_Channel_A1, GPIO_LEVEL_HIGH);
  while (1) {
  }
}
