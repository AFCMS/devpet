/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "display_progress_bar.hpp"

namespace utils
{
    namespace display
    {
        ProgressBar::ProgressBar(unsigned char _w, unsigned char _h)
        {
            w = _w;
            h = _h;
            percent = 0;
        };

        ProgressBar::ProgressBar(unsigned char _w, unsigned char _h, unsigned char _percent)
        {
            w = _w;
            h = _h;
            percent = _percent;
        };

        unsigned char ProgressBar::getPercent()
        {
            return percent;
        };

        void ProgressBar::setPercent(unsigned char _percent)
        {
            percent = _percent;
        };

        void ProgressBar::drawFrame(DisplaySystem *displaySystem)
        {
            auto dp = displaySystem->getDP();
            dp->fillRect(x, y, w * percent / 100, h, SSD1306_WHITE);
        };
    }
}