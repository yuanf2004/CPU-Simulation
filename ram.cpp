#include "ram.h"

// RAM Object
class RAMCell{
private:
    uint16_t data;
public:
    uint16_t get_data(void){
        return data;
    }

    void update_data(uint16_t d){
        data = d;
    }

    void clear_data(void){
        data = 0;
    }
};

// Random Access Memory array object to hold all memory locations
class RandomAccessMemory{
private:
    RAMCell ramcell[BIT16_SIZE];

public:
    RandomAccessMemory(){
    // Constructor 
        for(int i = 0; i < )

    }







}

