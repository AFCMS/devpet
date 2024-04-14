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
            Text();
            Text(String _text);
            String getText();
            /**
             * @brief Set the node's text
             */
            void setText(String _text);
            unsigned char getFontSize();
            void setFontSize(unsigned char _size);
            unsigned char getCharsMax();
            void setCharsMax(unsigned char _charsMax);
            bool isCentered();
            void setCentered(bool _centered);
            void drawFrame(DisplaySystem *displaySystem) override;
        };
    }
}