#include "ram.h"

// RAMCell Class

    uint16_t RAMCell::get_data(void){
        return data;
    }

    void RAMCell::update_data(uint16_t d){
        data = d;
    }

    void RAMCell::reset_data(void){
        data = 0;
    }

// RandomAccessMemory Class

    RandomAccessMemory::RandomAccessMemory(){
    // Constructor 
        init_ram();
    }

    uint16_t RandomAccessMemory::get_ramcell(uint16_t cellnum){
        return ramcell[cellnum].get_data();
    };

    void RandomAccessMemory::update_ramcell(uint16_t cellnum, uint16_t data){
        ramcell[cellnum].update_data(data);
    }

    void RandomAccessMemory::reset_ramcell(uint16_t cellnum){
        ramcell[cellnum].update_data(0);
    }



