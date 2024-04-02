#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <vector>
#include <map>

namespace utils
{
    namespace display
    {
        const int SCREEN_WIDTH = 128;
        const int SCREEN_HEIGHT = 64;

        /**
         * @brief The height of the yellow upper band of the screen
         */
        const int SCREEN_UB_HEIGHT = 16;

        /**
         * @brief The height of the blue lower band of the screen
         */
        const int SCREEN_LB_HEIGHT = SCREEN_HEIGHT - SCREEN_UB_HEIGHT;

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

        class DisplaySystem;

        /**
         * @brief A 2D node that can be drawn on the DisplaySystem
         */
        class Node2D
        {
        private:
            int zIndex;

        public:
            virtual void drawFrame(DisplaySystem *displaySystem) = 0;
        };

        class SpriteAnimated : public Node2D
        {
            void drawFrame(DisplaySystem *displaySystem) override;
        };

        class SpriteStatic : public Node2D
        {
        private:
            int16_t x, y;
            const uint8_t *bitmap;
            int16_t w, h;

        public:
            SpriteStatic(int16_t _x, int16_t _y, const uint8_t *_bitmap, int16_t _w, int16_t _h);
            void drawFrame(DisplaySystem *displaySystem) override;
        };

        class Text : public Node2D
        {
        private:
            String text;
            int size = 1;

        public:
            Text(String _text);
            String getText();
            void setText(String _text);
            int getSize();
            void setSize(int _size);
            void drawFrame(DisplaySystem *displaySystem) override;
        };

        class DisplaySystem
        {
        private:
            int fps;
            /**
             * @brief The display to draw on
             */
            Adafruit_SSD1306 *dp;
            unsigned long lastMillis;
            /**
             * All nodes to render on the screen
             *
             * `std::map` is a sorted container, so the nodes will be drawn in the order of their key
             */
            std::map<int, Node2D *> nodes;
            // std::vector<Node2D *> nodesSortedByZIndex();

        public:
            DisplaySystem(Adafruit_SSD1306 *_dp, int _fps);
            int getFps();
            void addNode2D(Node2D *node, int zIndex);
            void removeNode2D(int zIndex);
            Node2D *getNode2D(int zIndex);
            std::map<int, Node2D *> getNodes2D();
            void setNodes2D(std::map<int, Node2D *> _nodes);
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
