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
        class SpriteStatic : public Node2D
        {
        private:
            const uint8_t *bitmap;

        public:
            unsigned char w, h;

            SpriteStatic(unsigned char _x, unsigned char _y, const uint8_t *bitmap, unsigned char _w, unsigned char _h);
            void drawFrame(DisplaySystem *displaySystem) override;
        };
    };
};