#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/*
 SYSCLK = 168Mhz, we need to make:

 HSE_VALUE or HSI_VALUE = 8Mhz
 PLL_M = 8
 PLL_N = 336
 PLL_P =  2

 SYSCLK = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N / PLL_P

----- system_stm32f4xx.c -----

-> PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N
#define PLL_M      8
#define PLL_N      336

-> SYSCLK = PLL_VCO / PLL_P
#define PLL_P      2

-> USB OTG FS, SDIO and RNG Clock =  PLL_VCO / PLLQ
#define PLL_Q      7

----- stm32f4xx.h -----

#if !defined  (HSE_VALUE)
  #define HSE_VALUE    ((uint32_t)8000000) -> Value of the External oscillator in Hz (We Have Changed)
#endif  -> HSE_VALUE

----------------------
*/

int main(void)
{
  while (1)
  {

  }
}

//
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
  return -1;
}
