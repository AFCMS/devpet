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
        class Text : public Node2D
        {
        private:
            /**
             * @brief The text to be displayed
             */
            String text;
            /**
             * @brief The size of the text to be displayed
             */
            unsigned char fontSize = 1;
            /**
             * @brief The maximum number of characters that can be displayed, used to display centered text
             */
            unsigned char charsMax = -1;
            /**
             * @brief Whether the text should be centered
             */
            bool centered = false;

            static const unsigned char DEFAULT_CHAR_LIMIT = -1;

        public:
            /**
             * @brief Create a Text node with an empty base string
             */
            Text();

            /**
             * @brief Create a Text node with a given base string
             */
            Text(String _text);

            /**
             * @brief Get the node's text
             */
            String getText();

            /**
             * @brief Set the node's text
             */
            void setText(String _text);

            /**
             * @brief Get the size of the text to be displayed.
             *
             * 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc.
             *
             * See the `Adafruit_GFX` library for more information.
             */
            unsigned char getFontSize();

            /**
             * @brief Set the size of the text to be displayed.
             *
             * 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc.
             *
             * See the `Adafruit_GFX` library for more information.
             */
            void setFontSize(unsigned char _size);

            /**
             * @brief Get the maximum number of characters that can be displayed.
             */
            unsigned char getCharsMax();

            /**
             * @brief Set the maximum number of characters that can be displayed.
             *
             * If the text is centered the text will be displayed in the center of the space reserved by the max chars value.
             */
            void setCharsMax(unsigned char _charsMax);

            /**
             * @brief Check if the text should be centered
             */
            bool isCentered();

            /**
             * @brief Set whether the text should be centered.
             *
             * If the text is centered, the text will be displayed in the center of the space reserved by the max chars value.
             */
            void setCentered(bool _centered);

            void drawFrame(DisplaySystem *displaySystem) override;
        };
    }
}