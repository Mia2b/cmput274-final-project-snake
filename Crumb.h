#ifndef crumb_h
#define crumb_h

class Crumb
{
    public:
        Crumb();
        void insert(uint8_t direction);
        uint8_t getMove(uint16_t index);
        void setLength(uint16_t len);
    private:
        uint16_t length;
        uint16_t storageSize;
        bool lengthChanged;
        uint64_t moves[84]; // Will be able to store n * 32 moves

};

#endif