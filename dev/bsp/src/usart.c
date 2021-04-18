#include "stm8l15x.h"
#include "usart.h"

#ifdef DEBUG

void UsartInit(void)
{
    /* USART1 configuration -----------------------------------------*/
    /* USART1 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Receive and transmit enabled
        - USART Clock disabled
    */
    /* Enable USART clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);

    /* Configure USART Tx as alternate function push-pull  (software pull up)*/
    GPIO_ExternalPullUpConfig(GPIOC, GPIO_Pin_3, ENABLE);

    /* Configure USART Rx as alternate function push-pull  (software pull up)*/
    GPIO_ExternalPullUpConfig(GPIOC, GPIO_Pin_2, ENABLE);

    /* USART configuration */
    USART_Init(USART1, (uint32_t)115200, USART_WordLength_8b, USART_StopBits_1,
                   USART_Parity_No, (USART_Mode_TypeDef)(USART_Mode_Tx | USART_Mode_Rx));
    USART_ClearFlag(USART1, USART_FLAG_TC);
}

/**
  * @brief Retargets the C library printf function to the USART.
  * @param[in] c Character to send
  * @retval char Character sent
  * @par Required preconditions:
  * - None
  */
PUTCHAR_PROTOTYPE
{
    USART_ClearFlag(USART1,USART_FLAG_TC);
    /* Write a character to the USART */
    USART_SendData8(USART1, c);
    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);

    return (c);
}
/**
  * @brief Retargets the C library scanf function to the USART.
  * @param[in] None
  * @retval char Character to Read
  * @par Required preconditions:
  * - None
  */
GETCHAR_PROTOTYPE
{
    int c = 0;
    /* Loop until the Read data register flag is SET */
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    c = USART_ReceiveData8(USART1);
    return (c);
}
#endif