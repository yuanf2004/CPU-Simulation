#ifndef CU_H
#define CU_H

#include "registers.h"
#include "ram.h"
#include "alu.h"

class ControlUnit{
private:
    Registers *r;
    RandomAccessMemory *ram;
    ArithmeticLogicUnit *alu;
public:
    ControlUnit(Registers *r, RandomAccessMemory *ram, ArithmeticLogicUnit *alu);
    void decode_instruction(uint16_t i);
    void decode_load(uint16_t i);
    void decode_store(uint16_t i);
    void decode_add(uint16_t i);
    void decode_sub(uint16_t i);
    void decode_and(uint16_t i);
    void decode_or(uint16_t i);
    void decode_xor(uint16_t i);
    void decode_not(uint16_t i);
    void decode_addi(uint16_t i);
    void decode_subi(uint16_t i);
    void decode_andi(uint16_t i);
    void decode_ori(uint16_t i);
    void decode_xori(uint16_t i);
    void decode_jmp(uint16_t i);
    void decode_jz(uint16_t i);
    void decode_jnz(uint16_t i);
};

#endif