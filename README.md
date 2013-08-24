VGA output on a TI Stellaris ARM Cortex M3 mcu running at 50mhz (lms3s5749)
=========

- PB0-7 ->  RGB signal (toggled using DMA)
- PG0 (PWM0) -> Vsync
- PH0 (PWM2) -> Hsync

PWM4 used to start DMA transfer early to fit in horizontal backporch