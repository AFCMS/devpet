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
            int16_t w, h;

        public:
            SpriteStatic(int16_t _x, int16_t _y, const uint8_t *bitmap, int16_t _w, int16_t _h); // Update the parameter type accordingly
            void drawFrame(DisplaySystem *displaySystem) override;
        };
    };
};