/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <initializer_list>

#include "display.hpp"
#include "display_sprite_animated.hpp"

#pragma once

namespace utils
{
    namespace display
    {
        enum SpriteBarSpState
        {
            SpriteBarSpStateEmpty = 0,
            SpriteBarSpStateHalf = 1,
            SpriteBarSpStateFull = 2,
        };

        class SpriteBar
        {
        private:
            const unsigned char spNum;
            const unsigned char maxVal;
            display::SpriteAnimated **sprites;

        public:
            SpriteBar(unsigned char _spNum, display::SpriteAnimated *_sprites[], unsigned char _maxVal);

            /**
             * @brief Set the progress bar percent
             */
            void setVal(unsigned char val);
        };
    }
}
