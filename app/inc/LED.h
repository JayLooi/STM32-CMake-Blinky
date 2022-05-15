#ifndef LED_H_
#define LED_H_

#include "stm32f3xx_hal.h"

#define LED_N         (1UL << LED_ID_N)
#define LED_NE        (1UL << LED_ID_NE)
#define LED_E         (1UL << LED_ID_E)
#define LED_SE        (1UL << LED_ID_SE)
#define LED_S         (1UL << LED_ID_S)
#define LED_SW        (1UL << LED_ID_SW)
#define LED_W         (1UL << LED_ID_W)
#define LED_NW        (1UL << LED_ID_NW)

typedef enum
{
  LED_ID_N, 
  LED_ID_NE,
  LED_ID_E,
  LED_ID_SE,
  LED_ID_S,
  LED_ID_SW,
  LED_ID_W,
  LED_ID_NW,
  LED_Number
} LED_ID_t;

void LED_Init(uint32_t led_select_bits);
void LED_TurnOn(LED_ID_t led_id);
void LED_TurnOff(LED_ID_t led_id);
void LED_Toggle(LED_ID_t led_id);
void LED_Blink_B(LED_ID_t led_id, uint32_t period_ms, uint32_t number_of_cycles);
void LED_InitAll(void);
void LED_TurnOnAll(void);
void LED_TurnOffAll(void);
void LED_ToggleAll(void);
void LED_BlinkAll_B(uint32_t period_ms, uint32_t number_of_cycles);

#endif  /* LED_H_ */
