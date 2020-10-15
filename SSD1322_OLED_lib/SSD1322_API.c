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

#include "..\SSD1322_OLED_lib\SSD1322_HW_Driver.h"
#include "..\SSD1322_OLED_lib\SSD1322_API.h"

void SSD1322_API_command(uint8_t command)
{
	SSD1322_HW_drive_CS_low();
	SSD1322_HW_drive_DC_low();
	SSD1322_HW_SPI_send_byte(command);
	SSD1322_HW_drive_CS_high();
}

void SSD1322_API_data(uint8_t data)
{
	SSD1322_HW_drive_CS_low();
	SSD1322_HW_drive_DC_high();
	SSD1322_HW_SPI_send_byte(data);
	SSD1322_HW_drive_CS_high();
}

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
