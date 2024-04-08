/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "display.hpp"

namespace utils
{
    namespace display
    {
        int nbCharsInLine(int fontSize)
        {
            return SCREEN_WIDTH / (6 * fontSize);
        };

        void printCenter(Adafruit_SSD1306 *dp, const String buf, int x, int y, uint8_t size = 1)
        {

            int16_t x1, y1;
            uint16_t w, h;
            dp->setTextSize(size);
            dp->getTextBounds(buf, x, y, &x1, &y1, &w, &h); // calc width of new string
            dp->setCursor((x - w / 2) + (128 / 2), y);
            dp->print(buf);
        }

        void printUpBar(Adafruit_SSD1306 *dp, const String buf)
        {
            dp->setTextSize(1);
            dp->setCursor(0, 0);
            dp->print(buf);
        };

        void Node2D::setPos(uint8_t _x, uint8_t _y)
        {
            x = _x;
            y = _y;
        };

        void SpriteStatic::drawFrame(DisplaySystem *displaySystem)
        {
            displaySystem->drawBitmap(x, y, bitmap, w, h);
        };

        DisplaySystem::DisplaySystem(Adafruit_SSD1306 *_dp, int _fps)
        {
            dp = _dp;
            fps = _fps;
            lastMillis = 0;
        };

        int DisplaySystem::getFps()
        {
            return fps;
        };

        Adafruit_SSD1306 *DisplaySystem::getDP()
        {
            return dp;
        };

        void DisplaySystem::addNode2D(Node2D *node, int zIndex)
        {
            nodes[zIndex] = node;
        };

        void DisplaySystem::removeNode2D(int zIndex)
        {
            nodes.erase(zIndex);
        };

        Node2D *DisplaySystem::getNode2D(int zIndex)
        {
            return nodes[zIndex];
        };

        std::map<int, Node2D *> DisplaySystem::getNodes2D()
        {
            return nodes;
        };

        void DisplaySystem::setNodes2D(std::map<int, Node2D *> _nodes)
        {
            nodes = _nodes;
        };

        void DisplaySystem::clearDisplay()
        {
            dp->clearDisplay();
        };

        void DisplaySystem::clearArea(int x, int y, int w, int h)
        {
            dp->fillRect(x, y, w, h, SSD1306_BLACK);
        };

        void DisplaySystem::clearUpBar()
        {
            dp->fillRect(0, 0, SCREEN_WIDTH, SCREEN_UB_HEIGHT, SSD1306_BLACK);
        };

        void DisplaySystem::printUpBar(const String buf)
        {
            dp->setTextSize(1);
            dp->setCursor(0, 0);
            dp->print(buf);
        };

        void DisplaySystem::drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h)
        {
            dp->drawBitmap(x, y, bitmap, w, h, SSD1306_WHITE);
        };

        void DisplaySystem::drawNode2D(Node2D *node)
        {
            node->drawFrame(this);
        };

        void DisplaySystem::begin()
        {
            dp->begin(SSD1306_SWITCHCAPVCC, 0x3C);
            dp->clearDisplay();
            dp->setTextSize(1);
            dp->setTextColor(SSD1306_WHITE);
            dp->setCursor(0, 0);
            dp->display();
        };

        void DisplaySystem::display()
        {
            dp->display();
        };

        void DisplaySystem::step()
        {
            if (millis() - lastMillis > 1000 / fps)
            {
                lastMillis = millis();
                clearDisplay();

                for (std::map<int, Node2D *>::iterator it = nodes.begin(); it != nodes.end(); ++it)
                {
                    it->second->drawFrame(this);
                }

                display();
            }
        };
    }
}
