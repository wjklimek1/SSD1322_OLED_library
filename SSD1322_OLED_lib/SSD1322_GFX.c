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

#include <stdlib.h>

//====================== draw pixel ========================//
/**
 *  @brief Draws one pixel on frame buffer
 *
 *  Draws pixel of specified brightness on given coordinates on frame buffer.
 *  Pixels drawn outside buffer outline are ignored to avoid "segfault".
 *
 *  @param[in] frame_buffer
 *             array of pixel values
 *  @param[in] x
 *             horizontal coordinate of pixel
 *  @param[in] y
 *             vertical coordinate of pixel
 *  @param[in] brightness
 *             brightness value of pixel (range 0-15 dec or 0x00-0x0F hex)
 */
void draw_pixel(uint8_t *frame_buffer, uint16_t x, uint16_t y, uint8_t brightness)
{
	if(x > (BUFFER_WIDTH-1) || y > (BUFFER_HEIGHT-1))
		return;

	if ((y * BUFFER_WIDTH + x) % 2 == 1)
	{
		frame_buffer[((y * BUFFER_WIDTH) + x) / 2] = (frame_buffer[((y * BUFFER_WIDTH) + x) / 2] & 0xF0) | brightness;
	}
	else
	{
		frame_buffer[((y * BUFFER_WIDTH) + x) / 2] = (frame_buffer[((y * BUFFER_WIDTH) + x) / 2] & 0x0F) | brightness << 4;
	}
}

//====================== draw vertical line ========================//
/**
 *  @brief Draws vertical line in frame buffer
 *
 *  Draws vertical line of specified brightness on given coordinates on frame buffer.
 *
 *  @param[in] frame_buffer
 *             array of pixel values
 *  @param[in] x
 *             horizontal coordinate of line
 *  @param[in] y0
 *             beginning of the line
 *  @param[in] y1
 *             end of the line
 * 	@param[in] brightness
 *             brightness value of pixels (range 0-15 dec or 0x00-0x0F hex)
 */
void draw_vline(uint8_t *frame_buffer, uint16_t x, uint16_t y0, uint16_t y1, uint8_t brightness)
{
	if(y0 < y1)
	{
		for (uint8_t i = y0; i <= y1; i++)
		{
			draw_pixel(frame_buffer, x, i, brightness);
		}
	}
	else
	{
		for (uint8_t i = y1; i <= y0; i++)
		{
			draw_pixel(frame_buffer, x, i, brightness);
		}
	}
}

//====================== draw horizontal line ========================//
/**
 *  @brief Draws horizontal line in frame buffer
 *
 *  Draws horizontal line of specified brightness on given coordinates on frame buffer.
 *
 *  @param[in] frame_buffer
 *             array of pixel values
 *  @param[in] y
 *             vertical coordinate of line
 *  @param[in] x0
 *             beginning of the line
 *  @param[in] x1
 *             end of the line
 * 	@param[in] brightness
 *             brightness value of pixels (range 0-15 dec or 0x00-0x0F hex)
 */
void draw_hline(uint8_t *frame_buffer, uint16_t y, uint16_t x0, uint16_t x1, uint8_t brightness)
{
	if(x0 < x1)
	{
		for (uint8_t i = x0; i <= x1; i++)
		{
			draw_pixel(frame_buffer, i, y, brightness);
		}
	}
	else
	{
		for (uint8_t i = x1; i <= x0; i++)
		{
			draw_pixel(frame_buffer, i, y, brightness);
		}
	}
}

//====================== draw sloping line ========================//
/**
 *  @brief Draws sloping line
 *
 *  Can be also used to draw vertical and horizontal lines.
 *
 *  @param[in] frame_buffer
 *             array of pixel values
 *  @param[in] x0
 *             x position of line beginning
 *  @param[in] y0
 *             y position of line beginning
 *  @param[in] x1
 *             x position of line ending
 *  @param[in] y1
 *             y position of line ending
 * 	@param[in] brightness
 *             brightness value of pixels (range 0-15 dec or 0x00-0x0F hex)
*/
void draw_line(uint8_t *frame_buffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t brightness)
{
	//handle horizontal and vertical lines with appropriate functions
	if (x0 == x1)
	{
		draw_vline(frame_buffer, x0, y0, y1, brightness);
	}
	if (y0 == y1)
	{
		draw_hline(frame_buffer, y0, x0, x1, brightness);
	}

	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep == 1)
	{
		uint16_t tmp = y0;
		y0 = x0;
		x0 = tmp;
		tmp = y1;
		y1 = x1;
		x1 = tmp;
	}

	if (x0 > x1)
	{
		uint16_t tmp = x0;
		x0 = x1;
		x1 = tmp;
		tmp = y0;
		y0 = y1;
		y1 = tmp;
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1)
	{
		ystep = 1;
	}
	else
	{
		ystep = -1;
	}

	for (; x0 <= x1; x0++)
	{
		if (steep)
		{
			draw_pixel(frame_buffer, y0, x0, brightness);
		}
		else
		{
			draw_pixel(frame_buffer, x0, y0, brightness);
		}
		err -= dy;
		if (err < 0)
		{
			y0 += ystep;
			err += dx;
		}
	}
}



//====================== draw empty rectangle ========================//
/**
 *  @brief Draws empty rectangle on frame buffer
 *
 *  @param[in] frame_buffer
 *             array of pixel values
 *  @param[in] x0
 *             x position of first corner
 *  @param[in] y0
 *             y position of first corner
 *  @param[in] x1
 *             x position of second corner
 *  @param[in] y1
 *             y position of second corner
 * 	@param[in] brightness
 *             brightness value of pixels (range 0-15 dec or 0x00-0x0F hex)
 */
void draw_rect(uint8_t *frame_buffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t brightness)
{
	draw_vline(frame_buffer, x0, y0, y1, brightness);
	draw_vline(frame_buffer, x1, y0, y1, brightness);
	draw_hline(frame_buffer, y0, x0, x1, brightness);
	draw_hline(frame_buffer, y1, x0, x1, brightness);
}

//====================== draw filled rectangle ========================//
/**
 *  @brief Draws filled rectangle on frame buffer
 *
 *  @param[in] frame_buffer
 *             array of pixel values
 *  @param[in] x0
 *             x position of first corner
 *  @param[in] y0
 *             y position of first corner
 *  @param[in] x1
 *             x position of second corner
 *  @param[in] y1
 *             y position of second corner
 * 	@param[in] brightness
 *             brightness value of pixels (range 0-15 dec or 0x00-0x0F hex)
 */
void draw_rect_filled(uint8_t *frame_buffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t brightness)
{
	for (uint8_t i = x0; i <= x1; i++)
	{
		for (uint8_t j = y0; j <= y1; j++)
		{
			draw_pixel(frame_buffer, i, j, brightness);
		}
	}
}

//====================== draw empty circle ========================//
/**
 *  @brief Draws empty circle on frame buffer
 *
 *  @param[in] frame_buffer
 *             array of pixel values
 *  @param[in] x0
 *             x position of circle's center
 *  @param[in] y0
 *             y position of circle's center
 *  @param[in] r
 *             radius of the circle (pixels)
 * 	@param[in] brightness
 *             brightness value of pixels (range 0-15 dec or 0x00-0x0F hex)
 */
void draw_circle(uint8_t *frame_buffer, uint16_t x0, uint16_t y0, uint16_t r, uint8_t brightness)
{
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  draw_pixel(frame_buffer, x0, y0 + r, brightness);
  draw_pixel(frame_buffer, x0, y0 - r, brightness);
  draw_pixel(frame_buffer, x0 + r, y0, brightness);
  draw_pixel(frame_buffer, x0 - r, y0, brightness);

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

    draw_pixel(frame_buffer, x0 + x, y0 + y, brightness);
    draw_pixel(frame_buffer, x0 - x, y0 + y, brightness);
    draw_pixel(frame_buffer, x0 + x, y0 - y, brightness);
    draw_pixel(frame_buffer, x0 - x, y0 - y, brightness);
    draw_pixel(frame_buffer, x0 + y, y0 + x, brightness);
    draw_pixel(frame_buffer, x0 - y, y0 + x, brightness);
    draw_pixel(frame_buffer, x0 + y, y0 - x, brightness);
    draw_pixel(frame_buffer, x0 - y, y0 - x, brightness);
  }
}

//====================== draw bitmap ========================//
/**
 *  @brief Draws 8-bit uncompressed bitmap to frame buffer.
 *
 *  Only 4 first bits of grayscale byte are written to frame buffer. For example, if pixel value in bitmap
 *  is 0x14 (0b00010100), this byte is cut in half (0b0001 0100) and only first half is used.
 *
 *  You can use any image to bitmap converter as long as it gives you an 8-bit grayscale color depth array.
 *
 *  @param[in] frame_buffer
 *             array of pixel values
 *  @param[in] bitmap
 *  		   array with pixels to write to frame buffer
 *  @param[in] x0
 *             x position of top left bitmap corner
 *  @param[in] y0
 *             y position of top left bitmap corner
 *  @param[in] x_size
 *             width of bitmap in pixels
 *  @param[in] y_size
 *             height of bitmap in pixels

 */
void draw_bitmap(uint8_t *frame_buffer, const uint8_t *bitmap, uint16_t x0, uint16_t y0, uint16_t x_size, uint16_t y_size)
{
	uint16_t bitmap_pos = 0;

	for (uint8_t i = y0; i < y0 + y_size; i++)
	{
		for (uint8_t j = x0; j < x0 + x_size; j++)
		{
			draw_pixel(frame_buffer, j, i, bitmap[bitmap_pos]);
			bitmap_pos++;
		}
	}
}

//====================== send frame buffer to OLED ========================//
/**
 *  @brief Sends frame buffer to OLED display.
 *
 *  Transmits frame buffer to OLED display.
 *
 *  If your frame buffer size is equal to OLED size, leave start_x and start_y at 0.
 *  If you use bigger frame buffer, you can use this parameters to choose region of your frame buffer
 *  that will be displayed on OLED. This is particularly useful for scrolling.
 *
 *  @param[in] frame_buffer
 *             array of pixel values
 *  @param[in] start_x
 *             x position of frame buffer part that will be displayed on OLED. Useful for horizontal scrolling.
 *  @param[in] start_y
 *             y position of frame buffer part that will be displayed on OLED Useful for vertical scrolling.

 */
void send_buffer_to_OLED(uint8_t *frame_buffer, uint16_t start_x, uint16_t start_y)
{
	SSD1322_API_set_window(0, 63, 0, 127);
	SSD1322_API_send_buffer(frame_buffer + (start_y * OLED_WIDTH / 2) + start_x, 8192);
}
