///////////////////////////////////////////////////////////////////////////////
// thanks to Konstantin Isakov for coding this up
//
///////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
void __exit(volatile int32_t exitStatus)
{
    int32_t duration;
    int32_t frequency;

    if (exitStatus != 0)
    {
        asm("nop"); // place for a breakpoint
        duration = 50;
        frequency = 250;
    }
    else
    {
        duration = 20;
        frequency = 5000;
    }

    while (1)
    {
        GPIO_WriteBit(GPIO_PORT_LD2, GPIO_PIN_LD2, Bit_SET);
        delay(duration);

        GPIO_WriteBit(GPIO_PORT_LD2, GPIO_PIN_LD2, Bit_RESET);
        delay(frequency - duration);
    }
}
