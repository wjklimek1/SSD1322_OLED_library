/**
 ****************************************************************************************
 *
 * \file SSD1322_API.h
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

#ifndef SSD1322_API_H
#define SSD1322_API_H

#include "..\SSD1322_OLED_lib\SSD1322_HW_Driver.h"

/*============ Commands defines ============*/

#define ENABLE_GRAYSCALE_TABLE     0x00
#define SET_COLUMN_ADDR            0x15
#define ENABLE_RAM_WRITE           0x05
#define SET_ROW_ADDR               0x75
#define SET_REMAP_AND_DUAL_COM     0xA0
#define SET_DISP_START_LINE        0xA1
#define SET_DISP_OFFSET            0xA2

#define SET_DISP_MODE_OFF          0xA4
#define SET_DISP_MODE_ON           0xA5
#define SET_DISP_MODE_NORMAL       0xA6
#define SET_DISP_MODE_INVERTED     0xA7

#define ENABLE_PARTIAL_MODE        0xA8
#define DISABLE_PARTIAL_MODE       0xA9

#define SLEEP_MODE_ON              0xAE
#define SLEEP_MODE_OFF             0xAF

#define SET_PHASE_LENGTH           0xB1
#define SET_FRONT_CLOCK_DIV        0xB3
#define DISP_ENCHANCEMENT          0xB4
#define SET_2ND_PRECHARGE_PERIOD   0xB6
#define SET_GRAYSCALE_TABLE        0xB8
#define SET_DEFAULT_GRAYSCALE_TAB  0x9B
#define SET_PRECHARGE_VOLTAGE      0xBB
#define SET_V_COMH                 0xBE
#define SET_CONTRAST_CURRENT       0xC1
#define MASTER_CONTRAST_CURRENT    0xC7
#define SET_MUX_RATIO              0xCA
#define SET_COMMANDS_LOCK          0xFD

/*============ SSD1322 enums ============*/

enum SSD1322_mode_e
{
	SSD1322_MODE_ON, SSD1322_MODE_OFF, SSD1322_MODE_NORMAL, SSD1322_MODE_INVERTED
};

void SSD1322_API_command(uint8_t command);
void SSD1322_API_data(uint8_t data);
void SSD1322_API_set_display_mode(enum SSD1322_mode_e mode);

#endif /* SSD1322_API_H */
