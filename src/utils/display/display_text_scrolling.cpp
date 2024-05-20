/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "display_text_scrolling.hpp"

namespace utils
{
    namespace display
    {
        String TextScrolling::whitespaces(unsigned char n)
        {
            String repeatedString = "";

            for (char i = 0; i < n; i++)
            {
                repeatedString += ' ';
            };

            return repeatedString;
        };

        void TextScrolling::regenerateInternals()
        {
            extendedText = whitespaces(charsMax) + text + whitespaces(charsMax);
            extendedTextLength = extendedText.length();
        };

        String TextScrolling::getTextToDisplay()
        {
            return extendedText.substring(indexCounter, min((unsigned char)(indexCounter + charsMax), extendedTextLength));
        };

        TextScrolling::TextScrolling(unsigned char _x, unsigned char _y, String _text, unsigned char _fontSize, unsigned char _charsMax, unsigned char _speed)
        {
            x = _x;
            y = _y;
            text = _text;
            fontSize = _fontSize;
            charsMax = _charsMax;
            speed = _speed;
            regenerateInternals();
        };

        String TextScrolling::getText()
        {
            return text;
        };

        void TextScrolling::setText(String _text)
        {
            text = _text;
            regenerateInternals();
        };

        unsigned char TextScrolling::getFontSize()
        {
            return fontSize;
        };

        void TextScrolling::setFontSize(unsigned char _size)
        {
            fontSize = _size;
        };

        unsigned char TextScrolling::getCharsMax()
        {
            return charsMax;
        };

        void TextScrolling::setCharsMax(unsigned char _charsMax)
        {
            charsMax = _charsMax;
            regenerateInternals();
        };

        void TextScrolling::setSpeed(unsigned char _speed)
        {
            speed = _speed;
        };

        void TextScrolling::drawFrame(DisplaySystem *displaySystem)
        {
            repeatFrame++;
            if (repeatFrame >= speed)
            {
                if (indexCounter > extendedTextLength - charsMax)
                {
                    indexCounter = 0;
                }
                else
                {
                    indexCounter++;
                };

                repeatFrame = 0;
            };

            auto dp = displaySystem->getDP();
            dp->setTextSize(getFontSize());
            dp->setCursor(x, y);
            dp->print(getTextToDisplay());
        };
    }
}
