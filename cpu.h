#ifndef CPU_H
#define CPU_H

#include "stdint.h"
#include "ram.h"
#include "registers.h"
#include "alu.h"
#include "cu.h" 
#include <string>
#include <iostream>

class CentralProcessingUnit{
private:
    Registers r;
    RandomAccessMemory ram;
    ArithmeticLogicUnit alu;
    ControlUnit cu;

public: 
    CentralProcessingUnit();
    void run();
    bool str_to_instr(std::string *s, uint16_t *ui);
};

#endif