# Exercise 3

## Env
- IDE: Platformio 
- Debugger: Platformio
- Framework: stm32cube (HAL)

## Registers
### LED
GPIO G: 0x4002 1800 - 0x4002 1BFF
0x40023800 + 0x14 (Output Data Register) + 13th bit

### BUTTON
GPIO A: 0x4000 0000
0x4000 0000  + 0x10 (Input Data Register) + 0th bit


