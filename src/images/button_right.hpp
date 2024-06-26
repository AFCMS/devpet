/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <Arduino.h>

#pragma once

namespace images
{
    /**
     * @brief Button right, 13x13px, 26 bytes
     *
     * Hand-drawn by @AFCMS
     */
    const unsigned char static_button_right[] PROGMEM = {
        0x00, 0x00, 0x3f, 0xe0, 0x40, 0x10, 0x4c, 0x10, 0x4f, 0x10, 0x4f, 0x90, 0x4f, 0xd0, 0x4f, 0x90,
        0x4f, 0x10, 0x4c, 0x10, 0x40, 0x10, 0x3f, 0xe0, 0x00, 0x00};
};