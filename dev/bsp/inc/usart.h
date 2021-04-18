#ifndef USART_H_
#define USART_H_

#ifdef DEBUG

#define PUTCHAR_PROTOTYPE char putchar (char c)
#define GETCHAR_PROTOTYPE char getchar (void)

void UsartInit(void);

#endif

#endif