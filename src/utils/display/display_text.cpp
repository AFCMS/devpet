/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "display_text.hpp"

namespace utils
{
    namespace display
    {
        Text::Text(unsigned char _x, unsigned char _y, String _text)
        {
            x = _x;
            y = _y;
            text = _text;
        };

        Text::Text(unsigned char _x, unsigned char _y, String _text, unsigned char _fontSize, unsigned char _charsMax, bool _centered)
        {
            x = _x;
            y = _y;
            text = _text;
            fontSize = _fontSize;
            charsMax = _charsMax;
            centered = _centered;
        };

        String Text::getText()
        {
            return text;
        };

        void Text::setText(String _text)
        {
            text = _text;
        };

        unsigned char Text::getFontSize()
        {
            return fontSize;
        };

        void Text::setFontSize(unsigned char _size)
        {
            fontSize = _size;
        };

        unsigned char Text::getCharsMax()
        {
            return charsMax;
        };

        void Text::setCharsMax(unsigned char _charsMax)
        {
            charsMax = _charsMax;
        };

        bool Text::isCentered()
        {
            return centered;
        };

        void Text::setCentered(bool _centered)
        {
            centered = _centered;
        };

        void Text::drawFrame(DisplaySystem *displaySystem)
        {
            auto dp = displaySystem->getDP();
            dp->setTextSize(getFontSize());
            if (isCentered())
            {
                short x1, y1;
                unsigned short w, h;
                auto cmax = getCharsMax();
                dp->getTextBounds(getText(), x, y, &x1, &y1, &w, &h);
                dp->setCursor((x - w / 2) + ((cmax == DEFAULT_CHAR_LIMIT) ? (SCREEN_WIDTH / 2) : ((6 * getFontSize() * getCharsMax()) / 2)), y);
            }
            else
            {
                dp->setCursor(x, y);
            };
            dp->print(getText());
        };
    }
}
