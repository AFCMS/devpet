/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "display_progress_bar.hpp"

namespace utils
{
    namespace display
    {
        ProgressBar::ProgressBar(unsigned char _x, unsigned char _y, unsigned char _w, unsigned char _h, unsigned char _maxVal)
        {
            x = _x;
            y = _y;
            w = _w;
            h = _h;
            maxVal = _maxVal;
        }

        void ProgressBar::setVal(unsigned char _newVal)
        {
            val = _newVal;
        }

        void ProgressBar::drawFrame(DisplaySystem *displaySystem)
        {
            auto dp = displaySystem->getDP();
            dp->drawRect(x, y, w, h, SSD1306_WHITE);
            dp->fillRect(x + 1, y + 1, val * w / maxVal, h - 1, SSD1306_WHITE);
        };
    }
}