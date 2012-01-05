#ifndef CMI8788Driver_CMI8788Registers_h
#define CMI8788Driver_CMI8788Registers_h

typedef struct CMI8788Registers {
    const static UInt16
    // GPI
    GPI_DATA = 0xa4,
    // GPIO
    GPIO_DATA = 0xA6,
    GPIO_CONTROL = 0xA8,
    GPIO_INTERRUPT_MASK = 0xAA;
} CMI8788Registers;

#endif
