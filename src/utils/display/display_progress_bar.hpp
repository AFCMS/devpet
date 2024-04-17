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
         * @brief A 2D rectangle which only fills a determined percent of it's width
         */
        class ProgressBar : public Node2D
        {
        private:
            unsigned char w, h, percent;

        public:
            /**
             * @brief Create a progress bar with a default percent of 0
             */
            ProgressBar(unsigned char _w, unsigned char _h);

            /**
             * @brief Create a progress bar with a given initial percent
             */
            ProgressBar(unsigned char _w, unsigned char _h, unsigned char _percent);

            /**
             * @brief Get the current percent
             */
            unsigned char getPercent();

            /**
             * @brief Set the progress bar percent
             */
            void setPercent(unsigned char _percent);

            void drawFrame(DisplaySystem *displaySystem) override;
        };
    }
}
