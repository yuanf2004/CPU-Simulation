#include "cu.h"

// Thinking of initializing the registers and the RAM and then passing their
// actual reference to this class to manipulate it

class ControlUnit{
private:
    Registers *r;
    RandomAccessMemory *ram;
    ArithmeticLogicUnit *alu;

public:
    ControlUnit(
        // These are all made in the cpu .cpp file
        Registers *r, 
        RandomAccessMemory *ram, 
        ArithmeticLogicUnit *alu
    ){
    // Pass the addresses of the init registers and RAM to be modified
        this->r = r;
        this->ram = ram;
        this->alu = alu;
    };

    void decode_instruction(uint16_t i){
        uint16_t opcode = i >> 12;

        switch(opcode){
            case 0x0:
                decode_load(i);
            case 0x1:
                decode_store(i);
            case 0x2:
                decode_add(i);
            case 0x3:
                decode_sub(i);
            case 0x4:
                decode_and(i);
            case 0x5:
                decode_or(i);
            case 0x6:
                decode_xor(i);
            case 0x7:
                decode_not(i);
            case 0x8:
                decode_addi(i);
            case 0x9:   
                decode_subi(i);
            case 0xA:
                decode_andi(i);
            case 0xB:
                decode_ori(i);
            case 0xC:
                decode_xori(i);
            case 0xD:
                decode_jmp(i);
            case 0xE:
                decode_jz(i);
            case 0xF:
                decode_jnz(i);
        }
    }

    void decode_load(uint16_t i){
        // Register Destination - 11:8
        // Memory Location - 7:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t memloc = i & 0xFF;

        alu->alu_load(regdest, memloc);
    }

    void decode_store(uint16_t i){
        // Register Source - 11:8
        // Memory Location - 7:0
        uint16_t regsrc = (i >> 8) & 0xF;
        uint16_t memloc = i & 0xFF;

        alu->alu_store(regsrc, memloc);
    }

    void decode_add(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Register B - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t regb = i & 0xF;

        alu->alu_add(regdest, rega, regb);
    }

    void decode_sub(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Register B - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t regb = i & 0xF;

        alu->alu_sub(regdest, rega, regb);
    }

    void decode_and(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Register B - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t regb = i & 0xF;

        alu->alu_and(regdest, rega, regb);
    }

    void decode_or(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Register B - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t regb = i & 0xF;

        alu->alu_or(regdest, rega, regb);
    }

    void decode_xor(uint16_t i){        
        // Register Destination - 11:8
        // Register A - 7:4
        // Register B - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t regb = i & 0xF;

        alu->alu_xor(regdest, rega, regb);
    }

    void decode_not(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Don't Care - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;

        alu->alu_not(regdest, rega);
    }

    void decode_addi(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Immediate - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t imm = i & 0xF;

        alu->alu_addi(regdest, rega, imm);
    }

    void decode_subi(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Immediate - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t imm = i & 0xF;

        alu->alu_subi(regdest, rega, imm);
    }

    void decode_andi(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Immediate - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t imm = i & 0xF;

        alu->alu_andi(regdest, rega, imm);
    }

    void decode_xori(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Immediate - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t imm = i & 0xF;

        alu->alu_xori(regdest, rega, imm);
    }

    void decode_ori(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Immediate - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t imm = i & 0xF;

        alu->alu_ori(regdest, rega, imm);
    }

    //TODO: Write later
    void decode_jmp(uint16_t i){
        
    }

    //TODO: Write later
    void decode_jz(uint16_t i){
    
    }

    //TODO: Write later
    void decode_jnz(uint16_t i){

    }
};