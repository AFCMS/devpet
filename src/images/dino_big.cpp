/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "dino_big.hpp"

namespace images
{
    const unsigned char *dino_big_music[] = {static_dino_big_music_1, static_dino_big_music_2};

    const unsigned char *dino_big_coffee[] = {
        static_dino_big_coffee_1,
        static_dino_big_coffee_2,
        static_dino_big_coffee_3,
        static_dino_big_coffee_4,
        static_dino_big_coffee_5,
        static_dino_big_coffee_6,
        static_dino_big_coffee_7};

    const unsigned char **dino_big[] = {dino_big_music, dino_big_coffee};
}