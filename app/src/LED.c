#include "LED.h"

#define LED_PIN_N     GPIO_PIN_9
#define LED_PIN_NE    GPIO_PIN_10
#define LED_PIN_E     GPIO_PIN_11
#define LED_PIN_SE    GPIO_PIN_12
#define LED_PIN_S     GPIO_PIN_13
#define LED_PIN_SW    GPIO_PIN_14
#define LED_PIN_W     GPIO_PIN_15
#define LED_PIN_NW    GPIO_PIN_8

#define ALL_LED       (LED_N | LED_NE | LED_E | LED_SE | LED_S | LED_SW | LED_W | LED_NW)
#define ALL_LED_PIN   (LED_PIN_N | LED_PIN_NE | LED_PIN_E | LED_PIN_SE | LED_PIN_S | LED_PIN_SW | LED_PIN_W | LED_PIN_NW)

static const uint32_t LED_Table[LED_Number] =
{ 
  LED_PIN_N, 
  LED_PIN_NE, 
  LED_PIN_E, 
  LED_PIN_SE, 
  LED_PIN_S, 
  LED_PIN_SW, 
  LED_PIN_W, 
  LED_PIN_NW 
};

static uint32_t LED_InitBits = 0UL;


void LED_Init(uint32_t led_select_bits)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  for (uint8_t i = 0; i < LED_Number; i++)
  {
    if ((led_select_bits & (1UL << i)) != 0UL)
    {
      GPIO_InitStruct.Pin |= LED_Table[i];
      LED_InitBits |= (1 << i);
    }
  }

  __HAL_RCC_GPIOE_CLK_ENABLE();
  GPIO_InitStruct.Alternate = 0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

void LED_TurnOn(LED_ID_t led_id)
{
  if ((LED_InitBits & (1 << led_id)) != 0)
  {
    HAL_GPIO_WritePin(GPIOE, LED_Table[led_id], GPIO_PIN_SET);
  }
}

void LED_TurnOff(LED_ID_t led_id)
{
  if ((LED_InitBits & (1 << led_id)) != 0)
  {
    HAL_GPIO_WritePin(GPIOE, LED_Table[led_id], GPIO_PIN_RESET);
  }
}

void LED_Toggle(LED_ID_t led_id)
{
  if ((LED_InitBits & (1 << led_id)) != 0)
  {
    HAL_GPIO_TogglePin(GPIOE, LED_Table[led_id]);
  }
}

void LED_Blink_B(LED_ID_t led_id, uint32_t period_ms, uint32_t number_of_cycles)
{
  if (number_of_cycles == 0)
  {
    return;
  }

  number_of_cycles *= 2;

  while (number_of_cycles--)
  {
    LED_Toggle(led_id);
    HAL_Delay(period_ms / 2);
  }
}

void LED_InitAll(void)
{
  LED_Init(ALL_LED);
}

void LED_TurnOnAll(void)
{
  if (LED_InitBits == ALL_LED)
  {
    HAL_GPIO_WritePin(GPIOE, ALL_LED_PIN, GPIO_PIN_SET);
  }
}

void LED_TurnOffAll(void)
{
  if (LED_InitBits == ALL_LED)
  {
    HAL_GPIO_WritePin(GPIOE, ALL_LED_PIN, GPIO_PIN_RESET);
  }
}

void LED_ToggleAll(void)
{
  if (LED_InitBits == ALL_LED)
  {
    HAL_GPIO_TogglePin(GPIOE, ALL_LED_PIN);
  }
}

void LED_BlinkAll_B(uint32_t period_ms, uint32_t number_of_cycles)
{
  if (number_of_cycles == 0)
  {
    return;
  }

  number_of_cycles *= 2;

  while (number_of_cycles--)
  {
    LED_ToggleAll();
    HAL_Delay(period_ms / 2);
  }
}
