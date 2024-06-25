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
            stopLoop = false;
        };

        void SpriteAnimated::setAnimAfter(unsigned char _afterAnim)
        {
            selectedAnimAfter = _afterAnim;
            stopLoopAfter = false;
        }

        void SpriteAnimated::setSpeed(unsigned char _speed)
        {
            speed = _speed;
        };

        void SpriteAnimated::doStopLoop()
        {
            stopLoop = true;
        }

        void SpriteAnimated::doStopLoopAfter()
        {
            stopLoopAfter = true;
        }

        void SpriteAnimated::drawFrame(DisplaySystem *displaySystem)
        {
            auto bitmap = frames[selectedAnim][selectedFrame];

            repeatFrame++;
            if (repeatFrame >= speed)
            {
                if (selectedFrame == numFrames[selectedAnim] - 1)
                {
                    if (selectedAnimAfter != NO_AFTER_ANIM)
                    {
                        setAnim(selectedAnimAfter);
                        selectedAnimAfter = NO_AFTER_ANIM;
                        stopLoop = stopLoopAfter;
                        stopLoopAfter = false;
                        bitmap = frames[selectedAnim][selectedFrame];
                    }
                    else if (!stopLoop)
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
    };
};