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
        /**
         * @brief
         */
        class SpriteAnimated : public Node2D
        {
        private:
            /**
             * @brief The frames of the animation.
             *
             * Animation frames are stored in a 3D array. The first dimension is the animation, the second dimension is the frame, and the third dimension is the bitmap.
             *
             * You can use an enum to name the animations.
             */
            const unsigned char ***frames;
            /**
             * @brief The number of frames in each animation.
             */
            const unsigned char *numFrames;
            /**
             * @brief The width and height of the bitmaps in the frames.
             */
            unsigned char w, h;
            unsigned char selectedAnim = 0;
            unsigned char selectedFrame = 0;
            /**
             * @brief Represent the number of `drawFrame` calls a frame will be displayed, default 1.
             */
            unsigned char speed = 1;
            unsigned char repeatFrame = 0;

            bool stopAfter = false;

        public:
            SpriteAnimated(unsigned char _x, unsigned char _y, const unsigned char ***_frames, const unsigned char *_numFrames, unsigned char _w, unsigned char _h);
            /**
             * @brief Set the animation to play, use an enum to name the animations.
             */
            void setAnim(unsigned char anim);
            /**
             * @brief Set the speed of the animations.
             *
             * Represent the number of `drawFrame` calls a frame will be displayed, default 1.
             */
            void setSpeed(unsigned char _speed);
            void drawFrame(DisplaySystem *displaySystem) override;
            /**
             * @brief Stop the animation at the last frame instead of looping.
             */
            void doStopAfter();
        };
    };
};