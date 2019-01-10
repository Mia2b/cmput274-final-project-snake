/////////////////////////////////////////////////////////////////////////////
// Name: Mia2b, HalloweenRalph                                             //
// ID: 0000000, 0000001                                                    //
// CMPUT 274, Fall 2018                                                    //
//                                                                         //
// Final Project                                                           //
/////////////////////////////////////////////////////////////////////////////
#ifndef crumb_h
#define crumb_h

class Crumb
{
    /* This class is to emulate an 1 dimensional array of crumbs 
       (quarter bytes) to allow for memory effecient moves storage */
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