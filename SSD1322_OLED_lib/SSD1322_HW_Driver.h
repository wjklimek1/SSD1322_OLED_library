/**
 ****************************************************************************************
 *
 * \file SSD1322_HW_Driver.h
 *
 * \brief Hardware dependent functions declarations for SSD1322 OLED display.
 *
 * This file contains functions that rely on hardware of used MCU. In this example functions
 * are filled with STM32F411RE hardware implementation. To use this library on any other MCU
 * you just have to provide its hardware implementations of functions from this file and higher
 * level functions should work without modification.
 *
 * Copyright (C) 2020 Wojciech Klimek
 * MIT license:
 * https://github.com/wjklimek1/SSD1322_OLED_library
 *
 ****************************************************************************************
 */
#ifndef SSD1322_HW_DRIVER_H
#define SSD1322_HW_DRIVER_H

#include <stdint.h>

void SSD1322_HW_drive_CS_low();
void SSD1322_HW_drive_CS_high();
void SSD1322_HW_drive_DC_low();
void SSD1322_HW_drive_DC_high();
void SSD1322_HW_drive_RESET_low();
void SSD1322_HW_drive_RESET_high();
void SSD1322_HW_SPI_send_byte(uint8_t byte_to_transmit);
void SSD1322_HW_SPI_send_array(uint8_t *array_to_transmit, uint32_t array_size);
void SSD1322_HW_msDelay(uint32_t milliseconds);

#endif /* SSD1322_HW_DRIVER_H */
