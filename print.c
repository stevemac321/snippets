///////////////////////////////////////////////////////////////////////////////
// thanks to Konstantin Isakov for coding this up per IAR documentation
//
///////////////////////////////////////////////////////////////////////////////
void PrintByte(char c)
{
  USART_SendData(COMM, c);
  while (USART_GetFlagStatus(COMM, USART_FLAG_TXE) == RESET)
          ; /* do nothing until RESET state*/
}
#ifdef _REDIRECT_SYSTEM_WRITE
size_t __write(int handle, const unsigned char* data, size_t byteCount)
{
    size_t nChars = 0;

    // handle == -1 means "flush all streams". Not implemented here.
    if (handle == -1 || byteCount == 0)
        return 0;

    // 1 - stdout; 2 - stderr. 
    if (handle != 1 && handle != 2)
        return -1;

    while (byteCount-- > 0) {
        char ch = (char)(*data);
        PrintByte(ch);
        if (ch == '\n') {
            PrintByte('\r');
        }
       ++data;
       ++nChars;
    }
    return nChars;

} // __write
#endif

