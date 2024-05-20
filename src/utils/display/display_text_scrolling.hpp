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
        class TextScrolling : public Node2D
        {
        private:
            /**
             * @brief The text to be displayed
             */
            String text;

            /**
             * @brief The extended text to be displayed
             *
             * @internal
             */
            String extendedText;

            /**
             * @brief The length of the extended text
             *
             * @internal
             */
            unsigned char extendedTextLength;

            /**
             * @brief The size of the text to be displayed
             */
            unsigned char fontSize = 1;

            /**
             * @brief The maximum number of characters that will be displayed at a time
             */
            unsigned char charsMax = 21;

            /**
             * @brief The index of the first character to be displayed, incremented when needed
             */
            unsigned char indexCounter = 0;

            /**
             * @brief Represent the number of `drawFrame` calls a frame will be displayed, default 1.
             */
            unsigned char speed = 1;
            unsigned char repeatFrame = 0;

            /**
             * @brief Generate a string of whitespaces
             */
            String whitespaces(unsigned char n);

            /**
             * @brief Regenerate the internal variables from text and charsMax
             */
            void regenerateInternals();

            /**
             * @brief Get a string of lenght of charsMax with the scroll
             */
            String getTextToDisplay();

        public:
            /**
             * @brief Create a TextScrolling node with a given base string and parameters
             *
             * @param _fontSize The size of the text to be displayed (1 is default 6x8, 2 is 12x16, 3 is 18x24, etc.)
             * @param _charsMax The maximum number of characters that can be displayed
             * @param _speed The speed of the animations (number of frames between each moves)
             */
            TextScrolling(unsigned char _x, unsigned char _y, String _text, unsigned char _fontSize, unsigned char _charsMax, unsigned char _speed);

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
             */
            void setCharsMax(unsigned char _charsMax);

            /**
             * @brief Set the speed of the animations.
             *
             * Represent the number of `drawFrame` calls a frame will be displayed, default 1.
             */
            void setSpeed(unsigned char _speed);

            void drawFrame(DisplaySystem *displaySystem) override;
        };
    }
}