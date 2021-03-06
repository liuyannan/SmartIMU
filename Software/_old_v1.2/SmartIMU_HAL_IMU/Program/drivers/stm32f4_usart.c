/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_usart.h"
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_SendByte
**功能 : Send Byte
**輸入 : USARTx, *SendData
**輸出 : None
**使用 : UART_SendByte(USART1, 'A');
**====================================================================================================*/
/*====================================================================================================*/
void UART_SendByte( USART_TypeDef *USARTx, uint8_t *sendData )
{
  USARTx->DR = (*sendData & (uint16_t)0x01FF);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvByte
**功能 : Recv Byte
**輸入 : USARTx, *RecvByte
**輸出 : None
**使用 : UART_RecvByte(USART1, recvData);
**====================================================================================================*/
/*====================================================================================================*/
void UART_RecvByte( USART_TypeDef *USARTx, uint8_t *recvData )
{
  *recvData = (uint16_t)(USARTx->DR & (uint16_t)0x01FF);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvByteWTO
**功能 : Recv Byte with Timeout
**輸入 : USARTx, *RecvByte, TimeoutMs
**輸出 : State
**使用 : UART_RecvByteWTO(USART1, recvData, 200);
**====================================================================================================*/
/*====================================================================================================*/
int8_t UART_RecvByteWTO( USART_TypeDef *USARTx, uint8_t *recvData, uint32_t timeoutMs )
{
  while((USARTx->SR & UART_FLAG_RXNE) == RESET) {
    if(timeoutMs-- > 0)
      HAL_Delay(1);
    else
      return ERROR; // timeout
  }
  *recvData = (uint16_t)(USARTx->DR & (uint16_t)0x01FF);

  return SUCCESS;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_SendData
**功能 : Send Bytes
**輸入 : USARTx, *SendData, DataLen
**輸出 : None
**使用 : UART_SendByte(USART1, sendData, lens);
**====================================================================================================*/
/*====================================================================================================*/
void UART_SendData( USART_TypeDef *USARTx, uint8_t *sendData, uint16_t lens )
{
  do {
    UART_SendByte(USARTx, sendData++);
  } while(--lens);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvData
**功能 : Recv Bytes
**輸入 : USARTx, *RecvData, DataLen
**輸出 : None
**使用 : UART_RecvData(USART1, recvData, lens);
**====================================================================================================*/
/*====================================================================================================*/
void UART_RecvData( USART_TypeDef *USARTx, uint8_t *recvData, uint16_t lens )
{
  do {
    UART_RecvByte(USARTx, recvData++);
  } while(--lens);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UART_RecvDataWTO
**功能 : Recv Bytes with Timeout
**輸入 : USARTx, *RecvByte, DataLen, TimeoutMs
**輸出 : State
**使用 : UART_RecvDataWTO(USART1, recvData, lens, 200);
**====================================================================================================*/
/*====================================================================================================*/
int8_t UART_RecvDataWTO( USART_TypeDef *USARTx, uint8_t *recvData, uint16_t lens, uint32_t timeoutMs )
{
  int8_t State = ERROR;

  do {
    State = UART_RecvByteWTO(USARTx, recvData++, timeoutMs);
    if(State == ERROR)
      return ERROR;
  } while(--lens);

  return State;
}
/*====================================================================================================*/
/*====================================================================================================*/
