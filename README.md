# SSD1322 OLED library
Portable library for 256x64 OLED display with SSD1322 controller (with STM32F4 example project)

Library is divided into three layers:
  - Hardware driver - contains all hardware dependent functions wrappers.
  - API - commands, initialization seqence, functions to change screen grayscale levels, color inversion, contrasct, etc. Uses only functions from hardware driver to send data to OLED.
  - GFX - functions to draw on frame buffer. Drawing single pixels, graphic primitives, lines, bitmaps and fonts. Operates only on frame buffer. Only function that sends buffer to OLED calls API funtions.
# Provided example
Provided example is made for Nucleo F411RE development board with STM32F411RET6 MCU. Project was created in STM32CubeIDE. OLED is connected to following GPIOs:

| SSD1322 pin | STM32F411 GPIO | Nucleo pin |
| ------- | ------ | ----- |
| RESET   | PA0  | A0 |
| DC      | PA1  | A1 |
| CS      | PA4  | A2 |
| SPI SCK | PB0  | A3 |
| SPI MOSI| PA10 | D2 |

# How to modify it to work with different MCU than STM32F411?
Due to layered structure of library you have to provide only following functions in SSD1322_HW_driver.c file:
  - drive RESET pin low and high
  - drive CS (chip select) pin low and high
  - drive DC (data/command) pin low and high
  - send single byte via SPI interface
  - send array of bytes via SPI interface
  - delay milliseconds
  
Dont be afraid of that delay. It is only used in init sequence to drive RESET pin low for a few milliseconds. 

# Adafruit fonts
GFX library can draw text with fonts provided by [AdafruitGFX][AdafruitGFX] library. To write text with Adafruit font include font file and select font with function:
```c
void select_font(const GFXfont *new_gfx_font)
```
for example:
```c
select_font(&FreeMono12pt7b);
```
When font is already selected you can use it to write text on screen. It works only for null terminated strings!

# Bitmaps
General function to draw bitmap is:
```c
void draw_bitmap(uint8_t *frame_buffer, const uint8_t *bitmap, uint16_t x0, uint16_t y0, uint16_t x_size, uint16_t y_size);
```
It draws bitmap where one pixel corresponds to one byte - just an 8bit grayscale bitmaps.

There is also a function that can draw "compressed" bitmaps, where 2 pixels are coded into a single byte. This function remains untested, because i haven't found any suitable converter :(


[//]: #
   [AdafruitGFX]: <https://github.com/adafruit/Adafruit-GFX-Library> 