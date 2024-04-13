/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "display_sprite_animated.hpp"

namespace utils
{
    namespace display
    {
        SpriteAnimated::SpriteAnimated(int16_t _x, int16_t _y, const unsigned char ***_frames, const unsigned char *_numFrames, int16_t _w, int16_t _h)
        {
            x = _x;
            y = _y;
            frames = _frames;
            numFrames = _numFrames;
            w = _w;
            h = _h;
        };

        void SpriteAnimated::setAnim(unsigned char anim)
        {
            selectedAnim = anim;
            selectedFrame = 0;
        };

        void SpriteAnimated::setSpeed(unsigned char _speed)
        {
            speed = _speed;
        };

        void SpriteAnimated::drawFrame(DisplaySystem *displaySystem)
        {
            auto bitmap = frames[selectedAnim][selectedFrame];

            repeatFrame++;
            if (repeatFrame >= speed)
            {
                if (selectedFrame == numFrames[selectedAnim] - 1)
                {
                    selectedFrame = 0;
                }
                else
                {
                    selectedFrame++;
                }
                repeatFrame = 0;
            }

            displaySystem->drawBitmap(x, y, bitmap, w, h);
        };
    };
};