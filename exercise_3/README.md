# Exercise 3

## Env
- IDE: Platformio 
- Debugger: Platformio
- Framework: stm32cube (HAL)

## Registers
### LED
GPIO G: 0x40021800 - 0x4002 1BFF
0x40023800 + 0x14 (Output Data Register) + 13th bit

`led_direct_read_val = ((*(uint32_t *)0x40021814) >> 13) & 0x1;`

### BUTTON
GPIO A: 0x40000000
0x4002 0000  + 0x10 (Input Data Register) + 0th bit

`btn_direct_read_val = ((*(uint32_t *)0x40020010) >> 0) & 0x1;`


