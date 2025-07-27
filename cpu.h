#ifndef CPU_H
#define CPU_H
#endif

#include "stdint.h"
#include "ram.h"
#include "registers.h"
#include "alu.h"
#include "cu.h"

class CentralProcessingUnit{
private:
    uint16_t instr_input; 
    Registers r;
    RandomAccessMemory ram;
    ArithmeticLogicUnit alu;
    ControlUnit cu;

public: 
    CentralProcessingUnit();
    void run();
};