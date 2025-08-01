#include "cu.h"

// Thinking of initializing the registers and the RAM and then passing their
// actual reference to this class to manipulate it

    ControlUnit::ControlUnit(
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

    void ControlUnit::decode_instruction(uint16_t i){
        uint16_t opcode = i >> 12;

        switch(opcode){
            case 0x0:
                decode_load(i);
                break;
            case 0x1:
                decode_store(i);
                break;
            case 0x2:
                decode_add(i);
                break;
            case 0x3:
                decode_sub(i);
                break;
            case 0x4:
                decode_and(i);
                break;
            case 0x5:
                decode_or(i);
                break;
            case 0x6:
                decode_xor(i);
                break;
            case 0x7:
                decode_not(i);
                break;
            case 0x8:
                decode_addi(i);
                break;
            case 0x9:   
                decode_subi(i);
                break;
            case 0xA:
                decode_andi(i);
                break;
            case 0xB:
                decode_ori(i);
                break;
            case 0xC:
                decode_xori(i);
                break;
            case 0xD:
                decode_jmp(i);
                break;
            case 0xE:
                decode_jz(i);
                break;
            case 0xF:
                decode_jnz(i);
                break;
        }
    }

    void ControlUnit::decode_load(uint16_t i){
        // Register Destination - 11:8
        // Memory Location - 7:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t memloc = i & 0xFF;

        alu->alu_load(regdest, memloc);
    }

    void ControlUnit::decode_store(uint16_t i){
        // Register Source - 11:8
        // Memory Location - 7:0
        uint16_t regsrc = (i >> 8) & 0xF;
        uint16_t memloc = i & 0xFF;

        alu->alu_store(regsrc, memloc);
    }

    void ControlUnit::decode_add(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Register B - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t regb = i & 0xF;

        alu->alu_add(regdest, rega, regb);
    }

    void ControlUnit::decode_sub(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Register B - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t regb = i & 0xF;

        alu->alu_sub(regdest, rega, regb);
    }

    void ControlUnit::decode_and(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Register B - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t regb = i & 0xF;

        alu->alu_and(regdest, rega, regb);
    }

    void ControlUnit::decode_or(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Register B - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t regb = i & 0xF;

        alu->alu_or(regdest, rega, regb);
    }

    void ControlUnit::decode_xor(uint16_t i){        
        // Register Destination - 11:8
        // Register A - 7:4
        // Register B - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t regb = i & 0xF;

        alu->alu_xor(regdest, rega, regb);
    }

    void ControlUnit::decode_not(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Don't Care - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;

        alu->alu_not(regdest, rega);
    }

    void ControlUnit::decode_addi(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Immediate - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t imm = i & 0xF;
        alu->alu_addi(regdest, rega, imm);
    }

    void ControlUnit::decode_subi(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Immediate - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t imm = i & 0xF;

        alu->alu_subi(regdest, rega, imm);
    }

    void ControlUnit::decode_andi(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Immediate - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t imm = i & 0xF;

        alu->alu_andi(regdest, rega, imm);
    }

    void ControlUnit::decode_xori(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Immediate - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t imm = i & 0xF;

        alu->alu_xori(regdest, rega, imm);
    }

    void ControlUnit::decode_ori(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Immediate - 3:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t imm = i & 0xF;

        alu->alu_ori(regdest, rega, imm);
    }

    //TODO: Write later
    void ControlUnit::decode_jmp(uint16_t i){
    }

    //TODO: Write later
    void ControlUnit::decode_jz(uint16_t i){
    }

    //TODO: Write later
    void ControlUnit::decode_jnz(uint16_t i){
    }