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

#ifndef SSD1322_GFX_H
#define SSD1322_GFX_H

/*============ defines ============*/

#define OLED_HEIGHT 64
#define OLED_WIDTH 256

/*============ Adafruit fonts structures ============*/

// Single character data (glyph)
typedef struct {
  uint16_t bitmapOffset; ///< Pointer into GFXfont->bitmap
  uint8_t width;         ///< Bitmap dimensions in pixels
  uint8_t height;        ///< Bitmap dimensions in pixels
  uint8_t xAdvance;      ///< Distance to advance cursor (x axis)
  int8_t xOffset;        ///< X dist from cursor pos to UL corner
  int8_t yOffset;        ///< Y dist from cursor pos to UL corner
} GFXglyph;

// Font data
typedef struct {
  uint8_t *bitmap;  ///< Glyph bitmaps, concatenated
  GFXglyph *glyph;  ///< Glyph array
  uint16_t first;   ///< ASCII extents (first char)
  uint16_t last;    ///< ASCII extents (last char)
  uint8_t yAdvance; ///< Newline distance (y axis)
} GFXfont;

/*============ functions ============*/

void set_buffer_size(uint16_t buffer_width, uint16_t buffer_height);
void fill_buffer(uint8_t *frame_buffer, uint8_t brightness);
void draw_pixel(uint8_t *frame_buffer, uint16_t x, uint16_t y, uint8_t brightness);
void draw_vline(uint8_t *frame_buffer, uint16_t x, uint16_t y0, uint16_t y1, uint8_t brightness);
void draw_hline(uint8_t *frame_buffer, uint16_t y, uint16_t x0, uint16_t x1, uint8_t brightness);
void draw_line(uint8_t *frame_buffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t brightness);
void draw_AA_line(uint8_t *frame_buffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t brightness);
void draw_rect(uint8_t *frame_buffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t x2, uint8_t brightness);
void draw_rect_filled(uint8_t *frame_buffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t x2, uint8_t brightness);
void draw_circle(uint8_t *frame_buffer, uint16_t x0, uint16_t y0, uint16_t r, uint8_t brightness);
void draw_bitmap(uint8_t *frame_buffer, const uint8_t *bitmap, uint16_t x0, uint16_t y0, uint16_t x_size, uint16_t y_size);
void draw_bitmap_compressed_4bit(uint8_t *frame_buffer, const uint8_t *bitmap, uint16_t x0, uint16_t y0, uint16_t x_size, uint16_t y_size);

void select_font(const GFXfont *new_gfx_font);
void draw_char(uint8_t *frame_buffer, uint8_t text, uint16_t x, uint16_t y, uint8_t brightness);
void draw_text(uint8_t *frame_buffer, const char* text, uint16_t x, uint16_t y, uint8_t brightness);

void send_buffer_to_OLED(uint8_t *frame_buffer, uint16_t start_x, uint16_t start_y);


#endif /* SSD1322_GFX_H */
