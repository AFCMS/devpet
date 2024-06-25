/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "display_sprite_animated.hpp"

namespace utils
{
    namespace display
    {
        SpriteAnimated::SpriteAnimated(unsigned char _x, unsigned char _y, const unsigned char ***_frames, const unsigned char *_numFrames, unsigned char _w, unsigned char _h)
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
            stopAfter = false;
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
                    if (!stopAfter)
                    {
                        selectedFrame = 0;
                    }
                }
                else
                {
                    selectedFrame++;
                }
                repeatFrame = 0;
            }

            auto dp = displaySystem->getDP();
            dp->drawBitmap(x, y, bitmap, w, h, SSD1306_WHITE);
        };

        void SpriteAnimated::doStopAfter()
        {
            stopAfter = true;
        }
    };
};