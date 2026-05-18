#include "stm32h7xx_hal.h"
#include <stdio.h>

// Déclaration des handles pour la configuration
UART_HandleTypeDef huart3;

// Prototypes des fonctions
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
void Error_Handler(void);

/**
  * @brief  Redirection du printf vers le port UART3
  */
int _write(int file, char *ptr, int len) {
    // Envoi des caractères via le port série avec un timeout de sécurité
    HAL_StatusTypeDef status = HAL_UART_Transmit(&huart3, (uint8_t*)ptr, len, HAL_MAX_DELAY);
    return (status == HAL_OK) ? len : -1;
}

int main(void) {
    // 1. Réinitialisation de la mémoire Flash, de la札 cache et du SysTick
    HAL_Init();

    // 2. Configuration de l'horloge système (Le H7A3 peut monter jusqu'à 280 MHz)
    SystemClock_Config();

    // 3. Initialisation des périphériques configurés
    MX_GPIO_Init();
    MX_USART3_UART_Init();

    // 4. Désactivation du tampon pour printf (affichage instantané sans attendre le \n)
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("\r\n==========================================\r\n");
    printf("   Demarrage du STM32H7A3 dans Codespaces  \r\n");
    printf("==========================================\r\n");

    uint32_t compteur = 0;

    // Boucle principale
    while (1) {
        // Inverse l'état de la LED sur le port B, Pin 0
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);

        // Envoi du message avec le compteur actuel
        printf("[Codespace] LED Toggle ! Iteration : %lu\r\n", compteur++);

        // Pause de 500 millisecondes
        HAL_Delay(500);
    }
}

/**
  * @brief Configuration de la LED (GPIOB Pin 0)
  */
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Activer l'horloge du port GPIO B
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // Configuration du Pin 0 (LED) en mode sortie classique
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
  * @brief Configuration de l'UART3 (VCP - Virtual COM Port)
  */
static void MX_USART3_UART_Init(void) {
    __HAL_RCC_USART3_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE(); // L'UART3 utilise généralement le Port D sur Nucleo
    
    /** Configuration des Pins UART3
      * PD8     ------> USART3_TX
      * PD9     ------> USART3_RX
      */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    // Configuration des paramètres de l'UART
    huart3.Instance = USART3;
    huart3.Init.BaudRate = 115200;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart3.ClockPrescaler = UART_PRESCALER_DIV1;
    
    if (HAL_UART_Init(&huart3) != HAL_OK) {
        Error_Handler();
    }
}

/**
  * @brief Configuration basique de l'horloge (à adapter selon votre quartz)
  */
void SystemClock_Config(void) {
    // Note : Dans un vrai projet, cette section est générée automatiquement 
    // par CubeMX pour configurer le PLL à 280MHz. 
    // Si vous utilisez CubeMX, laissez sa fonction SystemClock_Config() par défaut.
}

void Error_Handler(void) {
    __disable_irq();
    while (1) {}
}