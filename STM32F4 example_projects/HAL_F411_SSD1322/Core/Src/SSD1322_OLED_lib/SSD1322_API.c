/**
 ****************************************************************************************
 *
 * \file SSD1322_API.c
 *
 * \brief API for SSD1322 display. Includes commands, options and initialization sequence.
 *
 *
 * Copyright (C) 2020 Wojciech Klimek
 * MIT license:
 * https://github.com/wjklimek1/SSD1322_OLED_library
 *
 ****************************************************************************************
 */

#include "../SSD1322_OLED_lib/SSD1322_HW_Driver.h"
#include "../SSD1322_OLED_lib/SSD1322_API.h"


//====================== command ========================//
/**
 *  @brief Sends command byte to SSD1322
 */
void SSD1322_API_command(uint8_t command)
{
	SSD1322_HW_drive_CS_low();
	SSD1322_HW_drive_DC_low();
	SSD1322_HW_SPI_send_byte(command);
	SSD1322_HW_drive_CS_high();
}

//====================== data ========================//
/**
 *  @brief Sends data byte to SSD1322
 */
void SSD1322_API_data(uint8_t data)
{
	SSD1322_HW_drive_CS_low();
	SSD1322_HW_drive_DC_high();
	SSD1322_HW_SPI_send_byte(data);
	SSD1322_HW_drive_CS_high();
}

//====================== initialization sequence ========================//
/**
 *  @brief Initializes SSD1322 OLED display.
 */
void SSD1322_API_init()
{
	SSD1322_HW_drive_RESET_low();  //Reset pin low
	SSD1322_HW_msDelay(1);                  //1ms delay
	SSD1322_HW_drive_RESET_high(); //Reset pin high
	SSD1322_HW_msDelay(50);                 //50ms delay
	SSD1322_API_command(0xFD);     //set Command unlock
	SSD1322_API_data(0x12);
	SSD1322_API_command(0xAE);     //set display off
	SSD1322_API_command(0xB3);     //set display clock divide ratio
	SSD1322_API_data(0x91);
	SSD1322_API_command(0xCA);     //set multiplex ratio
	SSD1322_API_data(0x3F);
	SSD1322_API_command(0xA2);   //set display offset to 0
	SSD1322_API_data(0x00);
	SSD1322_API_command(0xA1);   //start display start line to 0
	SSD1322_API_data(0x00);
	SSD1322_API_command(0xA0);   //set remap and dual COM Line Mode
	SSD1322_API_data(0x14);
	SSD1322_API_data(0x11);
	SSD1322_API_command(0xB5);   //disable IO input
	SSD1322_API_data(0x00);
	SSD1322_API_command(0xAB);   //function select
	SSD1322_API_data(0x01);
	SSD1322_API_command(0xB4);   //enable VSL extern
	SSD1322_API_data(0xA0);
	SSD1322_API_data(0xFD);
	SSD1322_API_command(0xC1);   //set contrast current
	SSD1322_API_data(0xFF);
	SSD1322_API_command(0xC7);   //set master contrast current
	SSD1322_API_data(0x0F);
	SSD1322_API_command(0xB9);   //default grayscale
	SSD1322_API_command(0xB1);   //set phase length
	SSD1322_API_data(0xE2);
	SSD1322_API_command(0xD1);   //enhance driving scheme capability
	SSD1322_API_data(0x82);
	SSD1322_API_data(0x20);
	SSD1322_API_command(0xBB);   //first pre charge voltage
	SSD1322_API_data(0x1F);
	SSD1322_API_command(0xB6);   //second pre charge voltage
	SSD1322_API_data(0x08);
	SSD1322_API_command(0xBE);   //VCOMH
	SSD1322_API_data(0x07);
	SSD1322_API_command(0xA6);   //set normal display mode
	SSD1322_API_command(0xA9);   //no partial mode
	SSD1322_HW_msDelay(10);               //stabilize VDD
	SSD1322_API_command(0xAF);   //display on
	SSD1322_HW_msDelay(50);               //stabilize VDD
}

//====================== normal/inversion ========================//
/**
 *  @brief Sets display mode to normal/inverted/off/on
 *
 *  When mode is set to ON or OFF, display ignores GRAM data and is always on or off.
 */

void SSD1322_API_set_display_mode(enum SSD1322_mode_e mode)
{
	switch (mode)
	{
	case SSD1322_MODE_NORMAL:
		SSD1322_API_command(SET_DISP_MODE_NORMAL);
		break;
	case SSD1322_MODE_INVERTED:
		SSD1322_API_command(SET_DISP_MODE_INVERTED);
		break;
	case SSD1322_MODE_ON:
		SSD1322_API_command(SET_DISP_MODE_ON);
		break;
	case SSD1322_MODE_OFF:
		SSD1322_API_command(SET_DISP_MODE_OFF);
		break;
	}
}

//====================== go to sleep ========================//
/**
 *  @brief Go to sleep mode.
 */
void SSD1322_API_sleep_on()
{
	SSD1322_API_command(SLEEP_MODE_ON);
}

//====================== wake up from sleep ========================//
/**
 *  @brief Wake up from sleep mode.
 */
void SSD1322_API_sleep_off()
{
	SSD1322_API_command(SLEEP_MODE_OFF);
}

//====================== contrast ========================//
/**
 *  @brief Sets contrast between brightest and darkest pixels.
 */
void SSD1322_API_set_contrast(uint8_t contrast)
{
	SSD1322_API_command(SET_CONTRAST_CURRENT);
	SSD1322_API_data(contrast);
}

//====================== brightness ========================//
/**
 *  @brief Should set brightness, but actual effect is similar to setting contrast.
 */
void SSD1322_API_set_brightness(uint8_t brightness)
{
	SSD1322_API_command(MASTER_CONTRAST_CURRENT);
	SSD1322_API_data(0x0F & brightness);            //first 4 bits have to be 0
}

//====================== custom grayscale ========================//
/**
 *  @brief Upload custom grayscale table to SSD1322.
 *
 *  Uploads exact values for 4-bit grayscale levels. Grayscale levels can have values from 0 to 180
 *  and have to meet following condition:
 *
 *  G0 < G1 < G2 < ... < G14 < G15
 *
 *  Where Gx is value of grayscale level
 *
 *  @param[in] grayscale_tab array of 16 brightness values
 *
 *  @return 0 when levels are out of range, 1 if function has ended correctly
 */
uint8_t SSD1322_API_custom_grayscale(uint8_t *grayscale_tab)
{
	SSD1322_API_command(SET_GRAYSCALE_TABLE);
	for(int i = 0; i < 16; i++)
	{
		if(grayscale_tab[i] > 180)
			return 0;
		SSD1322_API_data(grayscale_tab[i]);
	}
	SSD1322_API_command(ENABLE_GRAYSCALE_TABLE);
	return 1;
}

//====================== default grayscale ========================//
/**
 *  @brief Reset grayscale levels to default (linear)
 */
void SSD1322_API_default_grayscale()
{
	SSD1322_API_command(SET_DEFAULT_GRAYSCALE_TAB);
}

//====================== window to draw into ========================//
/**
 *  @brief Sets range of pixels to write to.
 *
 *  @param[in] start_column
 *  @param[in] end_column
 *  @param[in] start_row
 *  @param[in] end_row
 */
void SSD1322_API_set_window(uint8_t start_column, uint8_t end_column, uint8_t start_row, uint8_t end_row)
{
	SSD1322_API_command(SET_COLUMN_ADDR);  //set columns range
	SSD1322_API_data(28+start_column);
	SSD1322_API_data(28+end_column);
	SSD1322_API_command(SET_ROW_ADDR);  //set rows range
	SSD1322_API_data(start_row);
	SSD1322_API_data(end_row);
}

//====================== send pixel data to display ========================//
/**
 *  @brief Sends pixels buffer to SSD1322 GRAM memory.
 *
 *  This function should be always preceded by SSD1322_API_set_window() to specify range of rows and columns.
 *
 *  @param[in] buffer array of pixel values
 *  @param[in] buffer_size amount of bytes in the array
 */
void SSD1322_API_send_buffer(uint8_t* buffer, uint32_t buffer_size)
{
	SSD1322_API_command(ENABLE_RAM_WRITE);  //enable write of pixels
	SSD1322_HW_drive_CS_low();
	SSD1322_HW_drive_DC_high();
	SSD1322_HW_SPI_send_array(buffer, buffer_size);
	SSD1322_HW_drive_CS_high();
}
