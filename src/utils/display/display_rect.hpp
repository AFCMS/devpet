/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "display.hpp"

#pragma once

namespace utils
{
    namespace display
    {
        class Rect : public Node2D
        {
        private:
            unsigned char w, h;

        public:
            Rect(unsigned char _x, unsigned char _y, unsigned char _w, unsigned char _h);
            void drawFrame(DisplaySystem *displaySystem) override;
        };
    };
};