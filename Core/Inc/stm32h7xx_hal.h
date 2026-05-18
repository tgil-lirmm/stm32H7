/**
  ******************************************************************************
  * @file    stm32h7xx_hal.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the HAL
  *          module driver.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32H7xx_HAL_H
#define __STM32H7xx_HAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* C'est ici que l'on inclut le fichier de configuration généré par CubeMX */
#include "stm32h7hal_conf.h"

/* Exported types ------------------------------------------------------------*/
/** 
  * @brief  HAL Status structures definition  
  */  
typedef enum 
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

/** 
  * @brief  HAL Lock structures definition  
  */
typedef enum 
{
  HAL_UNLOCKED = 0x00U,
  HAL_LOCKED   = 0x01U  
} HAL_LockTypeDef;

/* Exported macro ------------------------------------------------------------*/

/** @brief  Freeze/Unfreeze Peripherals in Debug mode 
  */
#define __HAL_DBGMCU_FREEZE_TIM2()           (DBGMCU->APB1LFZR |= (DBGMCU_APB1LFZR_DBG_TIM2))
#define __HAL_DBGMCU_UNFREEZE_TIM2()         (DBGMCU->APB1LFZR &= ~(DBGMCU_APB1LFZR_DBG_TIM2))

/** @brief  Main Flash memory mapped at 0x08000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_FLASH()     (SYSCFG->MEMRMP &= ~(SYSCFG_MEMRMP_MEM_MODE))

/* Macros de verrouillage utilisées par les pilotes HAL */
#define __HAL_LOCK(__HANDLE__)                                           \
                                do{                                        \
                                    if((__HANDLE__)->Lock == HAL_LOCKED)   \
                                    {                                      \
                                       return HAL_BUSY;                    \
                                    }                                      \
                                    else                                   \
                                    {                                      \
                                       (__HANDLE__)->Lock = HAL_LOCKED;    \
                                    }                                      \
                                  }while(0U)

#define __HAL_UNLOCK(__HANDLE__)                                         \
                                  do{                                      \
                                       (__HANDLE__)->Lock = HAL_UNLOCKED;  \
                                    }while(0U)

/* Exported functions --------------------------------------------------------*/

/* Fonctions d'initialisation globales */
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);

/* Fonctions de contrôle du temps (SysTick) */
void HAL_InitTick (uint32_t TickPriority);
void HAL_IncTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);

/* Fonctions de révision et configuration globale */
uint32_t HAL_GetHalVersion(void);
uint32_t HAL_GetREVID(void);
uint32_t HAL_GetDEVID(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32H7xx_HAL_H */