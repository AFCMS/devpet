/*
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
*/

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <vector>
#include <map>

#pragma once

#define OLED_RESET 0x3C

namespace utils
{
    namespace display
    {
        class DisplaySystem;

        /**
         * @brief The width of the screen
         */
        static const unsigned char SCREEN_WIDTH = 128;

        /**
         * @brief The height of the screen
         */
        static const unsigned char SCREEN_HEIGHT = 64;

        /**
         * @brief The height of the yellow upper band of the screen
         */
        static const unsigned char SCREEN_UB_HEIGHT = 16;

        /**
         * @brief The height of the blue lower band of the screen
         */
        static const unsigned char SCREEN_LB_HEIGHT = SCREEN_HEIGHT - SCREEN_UB_HEIGHT;

        /**
         * @brief The number of characters that can be displayed on a line
         */
        static const unsigned char SCREEN_NB_CHARS = SCREEN_WIDTH / 6;

        /**
         * @brief The number of characters that can be displayed on a line
         */
        int nbCharsInLine(int fontSize);

        /**
         * @brief Print a string centered horizontally on the screen
         * @param dp The display to print to
         * @param buf The string to print
         * @param x The x coordinate of the string (in pixels)
         * @param y The y coordinate of the string (in pixels)
         * @param size The size of the text to print (1 is 6x8, 2 is 12x16, 3 is 18x24)
         */
        void printCenter(Adafruit_SSD1306 *dp, const String buf, int x, int y, uint8_t size = 1);

        /**
         * @brief Print a string in the upper band of the screen with size 1 (6x8)
         * @param dp The display to print to
         * @param buf The string to print
         */
        void printUpBar(Adafruit_SSD1306 *dp, const String buf);

        /**
         * @brief A 2D node that can be drawn on the DisplaySystem
         */
        class Node2D
        {
        protected:
            /**
             * @brief The position of the node on the screen
             */
            uint8_t x, y;

        public:
            /**
             * @brief Set the position of the node on the screen
             */
            void setPos(uint8_t _x, uint8_t _y);

            /**
             * @brief Draw a frame
             */
            virtual void drawFrame(DisplaySystem *displaySystem) = 0;
        };

        class DisplaySystem
        {
        private:
            /**
             * @brief The rate at which the display is refreshed
             */
            unsigned char fps;
            /**
             * @brief The display to draw on
             */
            Adafruit_SSD1306 dp;
            unsigned long lastMillis;
            /**
             * All nodes to render on the screen
             *
             * `std::map` is a sorted container, so the nodes will be drawn in the order of their key
             */
            std::map<unsigned char, Node2D *> nodes;

        public:
            DisplaySystem(unsigned char _fps);
            unsigned char getFps();
            /**
             * @brief Get a pointer to the display
             */
            Adafruit_SSD1306 *getDP();
            void addNode2D(Node2D *node, unsigned char zIndex);
            void removeNode2D(unsigned char zIndex);
            Node2D *getNode2D(unsigned char zIndex);
            std::map<unsigned char, Node2D *> getNodes2D();
            void setNodes2D(std::map<unsigned char, Node2D *> _nodes);
            void clearDisplay();
            void clearArea(int x, int y, int w, int h);
            void clearUpBar();
            void printUpBar(const String buf);
            void drawNode2D(Node2D *node);
            void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h);
            void begin();
            void display();
            void step();
        };
    }
}
