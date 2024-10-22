#include "program.h"


// Delay x1.5us
void delay_x1o5us(uint8_t delay) {
    for(uint8_t i=0; i<delay; i++) NOP();
}

// Delay x24.25us
void delay_x24o25us(uint16_t delay) {
    for(uint16_t i=0; i<delay; i++) delay_x1o5us(15);
}

// Delay x1ms
void delay_ms(uint32_t delay) {
    for(uint32_t i=0; i<delay; i++) delay_x24o25us(41);
}


void programInitialize(void) {
    // Pins for LED matrix
    TRISA = 0;
    ANSELA = 0;
    LATA = 0;
}

void programLoop(void) {
    uint8_t i = 0;
    
    for(i=0; i<50; i++) {
        ledMatrix_SetDisplay(0b100100100);
    }
    
    for(i=0; i<50; i++) {
        ledMatrix_SetDisplay(0b010010010);
    }
    
    for(i=0; i<50; i++) {
        ledMatrix_SetDisplay(0b001001001);
    }
    
    for(i=0; i<50; i++) {
        ledMatrix_SetDisplay(0b010010010);
    }
}


void ledMatrix_AllOff(void) { // Turn off all LEDs
    led_VccColumn1 = 0;
    led_VccColumn2 = 0;
    led_VccColumn3 = 0;
    led_GndRow1 = 0;
    led_GndRow2 = 0;
    led_GndRow3 = 0;
}

void ledMatrix_SetDisplay(uint16_t ledWord) { // Set LED matrix using 9bit binary word
    uint8_t delay = 200;
    
    // First row
    
    ledMatrix_AllOff();
    
    led_VccColumn1 = (bool)(ledWord & 0b100000000);
    led_VccColumn2 = (bool)(ledWord & 0b010000000);
    led_VccColumn3 = (bool)(ledWord & 0b001000000);
    led_GndRow1 = 0;
    led_GndRow2 = 1;
    led_GndRow3 = 1;
    
    delay_x24o25us(delay);
    
    // Second row
    
    ledMatrix_AllOff();
    
    led_VccColumn1 = (bool)(ledWord & 0b000100000);
    led_VccColumn2 = (bool)(ledWord & 0b000010000);
    led_VccColumn3 = (bool)(ledWord & 0b000001000);
    led_GndRow1 = 1;
    led_GndRow2 = 0;
    led_GndRow3 = 1;
    
    delay_x24o25us(delay);
    
    // Third row
    
    ledMatrix_AllOff();
    
    led_VccColumn1 = (bool)(ledWord & 0b000000100);
    led_VccColumn2 = (bool)(ledWord & 0b000000010);
    led_VccColumn3 = (bool)(ledWord & 0b000000001);
    led_GndRow1 = 1;
    led_GndRow2 = 1;
    led_GndRow3 = 0;
    
    delay_x24o25us(delay);
}
