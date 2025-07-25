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

    void reset_data(void){
        data = 0;
    }
};

// Random Access Memory array object to hold all memory locations
class RandomAccessMemory{
private:
    RAMCell ramcell[BIT16_SIZE];

    void init_ram(void){
        for(int i = 0; i < BIT16_SIZE; i++){
            ramcell[i].reset_data();
        }
    }

public:
    RandomAccessMemory(){
    // Constructor 
        init_ram();
    }

    uint16_t get_ramcell(uint16_t cellnum){
        return ramcell[cellnum].get_data();
    };

    void update_ramcell(uint16_t cellnum, uint16_t data){
        ramcell[cellnum].update_data(data);
    }

    void reset_ramcell(uint16_t cellnum){
        ramcell[cellnum].update_data(0);
    }

    

};

