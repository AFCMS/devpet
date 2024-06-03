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
         * @brief A 2D rectangle which only fills a determined amount of it's width
         */
        class ProgressBar : public Node2D
        {
        private:
            unsigned char w, h, maxVal;
            unsigned char val = 0;

        public:
            /**
             * @brief Create a progress bar with a default value of 0
             *
             * @param _maxVal The maximum value of the progress bar
             */
            ProgressBar(unsigned char _w, unsigned char _h, unsigned char _maxVal);

            /**
             * @brief Set the progress bar value
             */
            void setVal(unsigned char _newVal);

            void drawFrame(DisplaySystem *displaySystem) override;
        };
    }
}
