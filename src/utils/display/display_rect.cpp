/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "display_rect.hpp"

namespace utils
{
    namespace display
    {
        Rect::Rect(unsigned char _x, unsigned char _y, unsigned char _w, unsigned char _h)
        {
            x = _x;
            y = _y;
            w = _w;
            h = _h;
        };

        void Rect::drawFrame(DisplaySystem *displaySystem)
        {
            auto dp = displaySystem->getDP();
            dp->drawRect(x, y, w, h, SSD1306_WHITE);
        };
    };
};