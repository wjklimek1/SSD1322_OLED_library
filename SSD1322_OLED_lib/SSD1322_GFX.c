/**
 ****************************************************************************************
 *
 * \file SSD1322_GFX.c
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

#include "..\SSD1322_OLED_lib\SSD1322_API.h"
#include "..\SSD1322_OLED_lib\SSD1322_GFX.h"

void draw_pixel(uint8_t *tx_buffer, uint16_t x, uint16_t y, uint8_t brightness)
{
	if(x > BUFFER_WIDTH && y > BUFFER_HEIGHT)
		return;

	if ((y * BUFFER_WIDTH + x) % 2 == 1)
	{
		tx_buffer[((y * BUFFER_WIDTH) + x) / 2] = (tx_buffer[((y * BUFFER_WIDTH) + x) / 2] & 0xF0) | brightness;
	}
	else
	{
		tx_buffer[((y * BUFFER_WIDTH) + x) / 2] = (tx_buffer[((y * BUFFER_WIDTH) + x) / 2] & 0x0F) | brightness << 4;
	}
}

void draw_vline(uint8_t *tx_buffer, uint16_t x, uint16_t y0, uint16_t y1, uint8_t brightness)
{
	for(uint8_t i = y0; i <= y1; i++)
	{
		draw_pixel(tx_buffer, x, i, brightness);
	}
}

void draw_hline(uint8_t *tx_buffer, uint16_t y, uint16_t x0, uint16_t x1, uint8_t brightness)
{
	for(uint8_t i = x0; i <= x1; i++)
	{
		draw_pixel(tx_buffer, i, y, brightness);
	}
}

void draw_rect(uint8_t *tx_buffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t brightness)
{
	draw_vline(tx_buffer, x0, y0, y1, brightness);
	draw_vline(tx_buffer, x1, y0, y1, brightness);
	draw_hline(tx_buffer, y0, x0, x1, brightness);
	draw_hline(tx_buffer, y1, x0, x1, brightness);
}

void draw_rect_filled(uint8_t *tx_buffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t brightness)
{
	for (uint8_t i = x0; i <= x1; i++)
	{
		for (uint8_t j = y0; j <= y1; j++)
		{
			draw_pixel(tx_buffer, i, j, brightness);
		}
	}
}

void draw_circle(uint8_t *tx_buffer, uint16_t x0, uint16_t y0, uint16_t r, uint8_t brightness)
{
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  draw_pixel(tx_buffer, x0, y0 + r, brightness);
  draw_pixel(tx_buffer, x0, y0 - r, brightness);
  draw_pixel(tx_buffer, x0 + r, y0, brightness);
  draw_pixel(tx_buffer, x0 - r, y0, brightness);

  while (x < y)
  {
    if (f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    draw_pixel(tx_buffer, x0 + x, y0 + y, brightness);
    draw_pixel(tx_buffer, x0 - x, y0 + y, brightness);
    draw_pixel(tx_buffer, x0 + x, y0 - y, brightness);
    draw_pixel(tx_buffer, x0 - x, y0 - y, brightness);
    draw_pixel(tx_buffer, x0 + y, y0 + x, brightness);
    draw_pixel(tx_buffer, x0 - y, y0 + x, brightness);
    draw_pixel(tx_buffer, x0 + y, y0 - x, brightness);
    draw_pixel(tx_buffer, x0 - y, y0 - x, brightness);
  }
}


void draw_bitmap(uint8_t *tx_buffer, const uint8_t *bitmap, uint16_t x0, uint16_t y0, uint16_t x_size, uint16_t y_size)
{
	uint16_t bitmap_pos = 0;

	for (uint8_t i = y0; i < y0 + y_size; i++)
	{
		for (uint8_t j = x0; j < x0 + x_size; j++)
		{
			draw_pixel(tx_buffer, j, i, bitmap[bitmap_pos]);
			bitmap_pos++;
		}
	}
}
