/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "display.hpp"

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
            int fontSize = 1;
            /**
             * @brief The maximum number of characters that can be displayed, used to display centered text
             */
            uint8_t charsMax = -1;
            /**
             * @brief Whether the text should be centered
             */
            bool centered = false;

            /**
             * @brief The position of the text, or the position of the centered area
             */
            int16_t x, y = 0;

            static const uint8_t DEFAULT_CHAR_LIMIT = -1;

        public:
            Text();
            Text(String _text);
            String getText();
            /**
             * @brief Set the node's text
             */
            void setText(String _text);
            int getFontSize();
            void setFontSize(int _size);
            uint8_t getCharsMax();
            void setCharsMax(uint8_t _charsMax);
            bool isCentered();
            void setCentered(bool _centered);
            void setPos(int16_t _x, int16_t _y);
            void drawFrame(DisplaySystem *displaySystem) override;
        };
    }
}