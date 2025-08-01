#ifndef RAM_H
#define RAM_H

#include <stdint.h>

const int BIT16_SIZE = 1 << 16;

class RAMCell {
private:
    uint16_t data;
public:
    uint16_t get_data(void);
    void update_data(uint16_t d);
    void reset_data(void);
};

class RandomAccessMemory{
private:
    RAMCell ramcell[BIT16_SIZE];

    void init_ram(void){
        for(int i = 0; i < BIT16_SIZE; i++){
            ramcell[i].reset_data();
        }
    }

public:
    RandomAccessMemory();
    uint16_t get_ramcell(uint16_t cellnum);
    void update_ramcell(uint16_t cellnum, uint16_t data);
    void reset_ramcell(uint16_t cellnum);
};

#endif
