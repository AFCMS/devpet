/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "display_sprite_static.hpp"

namespace utils
{
    namespace display
    {
        SpriteStatic::SpriteStatic(unsigned char _x, unsigned char _y, const uint8_t *_bitmap, unsigned char _w, unsigned char _h)
        {
            x = _x;
            y = _y;
            bitmap = _bitmap;
            w = _w;
            h = _h;
        };

        void SpriteStatic::drawFrame(DisplaySystem *displaySystem)
        {
            auto dp = displaySystem->getDP();
            dp->drawBitmap(x, y, bitmap, w, h, SSD1306_WHITE);
        };
    };
};