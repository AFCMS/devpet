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

            static const unsigned char NO_AFTER_ANIM = 255;
            /**
             * @brief The width and height of the bitmaps in the frames.
             */
            unsigned char w, h;
            unsigned char selectedAnim = 0;
            unsigned char selectedAnimAfter = NO_AFTER_ANIM;
            unsigned char selectedFrame = 0;

            /**
             * @brief Represent the number of `drawFrame` calls a frame will be displayed, default 1.
             */
            unsigned char speed = 1;
            unsigned char repeatFrame = 0;

            bool stopLoop = false;
            bool stopLoopAfter = false;

        public:
            SpriteAnimated(unsigned char _x, unsigned char _y, const unsigned char ***_frames, const unsigned char *_numFrames, unsigned char _w, unsigned char _h);

            /**
             * @brief Set the animation to play right now.
             */
            void setAnim(unsigned char anim);

            /**
             * @brief Set the animation to play after the current one finishes.
             *
             * If doStopAfter have been called for the current animation it won't do anything.
             */
            void setAnimAfter(unsigned char _afterAnim);

            /**
             * @brief Set the speed of the animations.
             *
             * Represent the number of `drawFrame` calls a frame will be displayed, default 1.
             */
            void setSpeed(unsigned char _speed);

            /**
             * @brief Stop the current animation at the last frame instead of looping.
             *
             * Must be called after setAnim.
             */
            void doStopLoop();

            /**
             * @brief Will stop the next animation at the last frame instead of looping.
             *
             * Must be called after setAnimAfter.
             */
            void doStopLoopAfter();

            void drawFrame(DisplaySystem *displaySystem) override;
        };
    };
};