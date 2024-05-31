/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "display_sprite_bar.hpp"

namespace utils
{
    namespace display
    {
        SpriteBar::SpriteBar(unsigned char _spNum, display::SpriteAnimated *_sprites[], unsigned char _maxVal) : spNum(_spNum), maxVal(_maxVal)
        {
            sprites = _sprites;
        }

        void SpriteBar::setVal(unsigned char val)
        {
            long bCount = map(val, 0, maxVal, 0, spNum * 2);
            for (unsigned char i = 0; i < spNum; i++)
            {
                if (bCount >= 2)
                {
                    // If bCount is greater than or equal to 2, display a full heart
                    sprites[i]->setAnim(0); // Assuming 0 is the index for the full heart animation
                    bCount -= 2;
                }
                else if (bCount == 1)
                {
                    // If bCount is 1, display a half heart
                    sprites[i]->setAnim(1); // Assuming 1 is the index for the half heart animation
                    bCount -= 1;
                }
                else
                {
                    // If bCount is 0, display an empty heart
                    sprites[i]->setAnim(2); // Assuming 2 is the index for the empty heart animation
                }
            }
        }
    }
}