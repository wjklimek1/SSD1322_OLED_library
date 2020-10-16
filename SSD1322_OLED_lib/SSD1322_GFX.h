/**
 ****************************************************************************************
 *
 * \file SSD1322_GFX.h
 *
 * \brief Simple GFX library to draw some basic shapes on OLED display.
 *
 *
 * Copyright (C) 2020 Wojciech Klimek
 * MIT license:
 * https://github.com/wjklimek1/SSD1322_OLED_library
 *
 ****************************************************************************************
 */

#ifndef SD1322_GFX_H
#define SSD1322_GFX_H

/*============ defines ============*/

#define BUFFER_HEIGHT 64
#define BUFFER_WIDTH 256

#define OLED_HEIGHT 64
#define OLED_WIDTH 256

/*============ functions ============*/

void draw_pixel(uint8_t *frame_buffer, uint16_t x, uint16_t y, uint8_t brightness);
void draw_vline(uint8_t *frame_buffer, uint16_t x, uint16_t y0, uint16_t y1, uint8_t brightness);
void draw_hline(uint8_t *frame_buffer, uint16_t y, uint16_t x0, uint16_t x1, uint8_t brightness);
void draw_rect(uint8_t *frame_buffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t x2, uint8_t brightness);
void draw_rect_filled(uint8_t *frame_buffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t x2, uint8_t brightness);
void draw_circle(uint8_t *frame_buffer, uint16_t x0, uint16_t y0, uint16_t r, uint8_t brightness);
void draw_bitmap(uint8_t *frame_buffer, const uint8_t *bitmap, uint16_t x0, uint16_t y0, uint16_t x_size, uint16_t y_size);

void send_buffer_to_OLED(uint8_t *frame_buffer, uint16_t start_x, uint16_t start_y);


#endif /* SSD1322_GFX_H */
