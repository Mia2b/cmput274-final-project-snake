#ifndef snake_h
#define snake_h

class Snake
{
    private:
        uint8_t newX, newY;
        uint8_t direction;
        uint8_t length;
        void move();
        void drawBody();
    public:
        Snake(uint8_t x, uint8_t y);
        void update();
};
#endif


