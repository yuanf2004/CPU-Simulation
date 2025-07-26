#include "registers.h"
#include "ram.h"
#include "alu.h"

class ControlUnit{
private:
    Registers *r;
    RandomAccessMemory *ram;
public:
    ControlUnit(Registers *r, RandomAccessMemory *ram);
    void handle_instruction(uint16_t i);
    void handle_load(uint16_t i);
    void handle_store(uint16_t i);
    void handle_add(uint16_t i);
    void handle_subtract(uint16_t i);
    void handle_and(uint16_t i);
    void handle_or(uint16_t i);
    void handle_xor(uint16_t i);
    void handle_not(uint16_t i);
    void handle_jmp(uint16_t i);
    void handle_jz(uint16_t i);
    void handle_addi(uint16_t i);
    void handle_subi(uint16_t i);
    void handle_andi(uint16_t i);
    void handle_ori(uint16_t i);
};