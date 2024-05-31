/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <Arduino.h>

#pragma once

namespace images
{
    /**
     * @brief Heart icon `heart_full_1`, 9x9px, 18 bytes
     *
     * Hand-drawn by @AFCMS
     */
    const unsigned char static_heart_full_1[] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x7f, 0x00, 0x7f, 0x00, 0x3e, 0x00, 0x1c, 0x00, 0x08, 0x00,
        0x00, 0x00};

    /**
     * @brief Heart icon `heart_full_2`, 9x9px, 18 bytes
     *
     * Hand-drawn by @AFCMS
     */
    const unsigned char static_heart_full_2[] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x6f, 0x00, 0x7f, 0x00, 0x3e, 0x00, 0x1c, 0x00, 0x08, 0x00,
        0x00, 0x00};

    /**
     * @brief Heart icon `heart_half_1`, 9x9px, 18 bytes
     *
     * Hand-drawn by @AFCMS
     */
    const unsigned char static_heart_half_1[] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x79, 0x00, 0x71, 0x00, 0x3a, 0x00, 0x14, 0x00, 0x08, 0x00,
        0x00, 0x00};

    /**
     * @brief Heart icon `heart_half_2`, 9x9px, 18 bytes
     *
     * Hand-drawn by @AFCMS
     */
    const unsigned char static_heart_half_2[] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x69, 0x00, 0x71, 0x00, 0x3a, 0x00, 0x14, 0x00, 0x08, 0x00,
        0x00, 0x00};

    /**
     * @brief Heart icon `heart_empty_1`, 9x9px, 18 bytes
     *
     * Hand-drawn by @AFCMS
     */
    const unsigned char static_heart_empty_1[] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x49, 0x00, 0x41, 0x00, 0x22, 0x00, 0x14, 0x00, 0x08, 0x00,
        0x00, 0x00};

    /**
     * @brief Heart icon frames `heart_full`, 9x9px, 2x18 bytes
     */
    extern const unsigned char *heart_full[];

    /**
     * @brief Heart icon frames `heart_half`, 9x9px, 2x18 bytes
     */
    extern const unsigned char *heart_half[];

    /**
     * @brief Heart icon frames `heart_empty`, 9x9px, 2x18 bytes (duplicated images to match the array size of the other states)
     */
    extern const unsigned char *heart_empty[];

    /**
     * @brief Heart icon frames `heart`, 9x9px, 3x2x18 bytes
     */
    extern const unsigned char **heart[];

    /**
     * @brief Heart icon number of frames `heart`
     */
    const unsigned char heart_num_frames[] = {2, 2, 2};
};