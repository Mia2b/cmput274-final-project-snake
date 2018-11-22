#ifndef Controller_h
#define Controller_h

class Controller
{
    private:
        uint8_t  pinX;
        uint8_t  pinY;
        uint8_t  pinB;
        uint8_t  lastMoves;
        uint16_t middleX;
        uint16_t middleY;
        uint16_t deadZone = 128;
    public:
        Controller(uint8_t pinX, uint8_t pinY, uint8_t pinB);
        uint8_t getDirection();
};

#endif