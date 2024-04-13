/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "display_text.hpp"

namespace utils
{
    namespace display
    {
        Text::Text()
        {
            text = "";
        };

        Text::Text(String _text)
        {
            text = _text;
        };

        String Text::getText()
        {
            return text;
        };

        void Text::setText(String _text)
        {
            text = _text;
        };

        int Text::getFontSize()
        {
            return fontSize;
        };

        void Text::setFontSize(int _size)
        {
            fontSize = _size;
        };

        uint8_t Text::getCharsMax()
        {
            return charsMax;
        };

        void Text::setCharsMax(uint8_t _charsMax)
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
                int16_t x1, y1;
                uint16_t w, h;
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
