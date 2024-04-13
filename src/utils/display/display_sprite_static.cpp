/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "display_sprite_static.hpp"

namespace utils
{
    namespace display
    {
        SpriteStatic::SpriteStatic(int16_t _x, int16_t _y, const uint8_t *_bitmap, int16_t _w, int16_t _h)
        {
            x = _x;
            y = _y;
            bitmap = _bitmap;
            w = _w;
            h = _h;
        };

        void SpriteStatic::drawFrame(DisplaySystem *displaySystem)
        {
            displaySystem->drawBitmap(x, y, bitmap, w, h);
        };
    };
};