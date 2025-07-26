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

    void handle_instruction(uint16_t i){
        uint16_t opcode = i >> 12;

        switch(opcode){
            case 0x0:
            case 0x1:
            case 0x2:
            case 0x3:
            case 0x4:
            case 0x5:
            case 0x6:
            case 0x7:
            case 0x8:
            case 0x9:
            case 0xA:
            case 0xB:
            case 0xC:
            case 0xD:
            case 0xE:
            case 0xF:
        }
    }

    void handle_load(uint16_t i){
        // Opcode - 15:12
        // Register Destination - 11:8
        // Memory Location - 7:0

        uint8_t rd = (i >> 8) & 0xF;
        uint8_t ram_mem_loc = i & 0xFF;

    }

    void handle_store(uint16_t i){
        // Opcode - 15:12
        // Register Destination - 11:8
        // Memory Location - 7:0

        uint8_t rd = (i >> 8) & 0xF;
        uint8_t memloc = i & 0xFF;

    }

    void handle_add(uint16_t i){
        // Opcode - 15:12
        // Register Destination - 11:8
        // Register A - 7:4
        // Register B - 3:0
        
        uint8_t rd = (i >> 8) & 0xF;
        uint8_t ra = (i >> 4) & 0xF; 
        uint8_t rb = i & 0xF;
        
    }

    void handle_subtract(uint16_t i){
        // Opcode - 15:12
        // Register Destination - 11:8
        // Register A - 7:4
        // Register B - 3:0

        uint8_t rd = (i >> 8) & 0xF;
        uint8_t ra = (i >> 4) & 0xF; 
        uint8_t rb = i & 0xF;
    
    }

    void handle_and(uint16_t i){
        // Opcode - 15:12
        // Register Destination - 11:8
        // Register A - 7:4
        // Register B - 3:0

        uint8_t rd = (i >> 8) & 0xF;
        uint8_t ra = (i >> 4) & 0xF; 
        uint8_t rb = i & 0xF;
    
    }

    void handle_or(uint16_t i){
        // Opcode - 15:12
        // Register Destination - 11:8
        // Register A - 7:4
        // Register B - 3:0

        uint8_t rd = (i >> 8) & 0xF;
        uint8_t ra = (i >> 4) & 0xF; 
        uint8_t rb = i & 0xF;
    
    }

    void handle_xor(uint16_t i){
        // Opcode - 15:12
        // Register Destination - 11:8
        // Register A - 7:4
        // Register B - 3:0

        uint8_t rd = (i >> 8) & 0xF;
        uint8_t ra = (i >> 4) & 0xF; 
        uint8_t rb = i & 0xF;
    
    }

    void handle_not(uint16_t i){
        // Opcode - 15:12
        // Register Destination - 11:8
        // Register A - 7:4
        // Don't Care - 3:0

        uint8_t rd = (i >> 8) & 0xF;
        uint8_t ra = (i >> 4) & 0xF; 
    }

    void handle_jmp(uint16_t i){
        // TODO
    }

    void handle_jz(uint16_t i){
        // TODO
    }

    void handle_addi(uint16_t i){
        // Opcode - 15:12
        // Register Destination - 11:8
        // Register A - 7:4
        // Immediate Value - 3:0

        uint8_t rd = (i >> 8) & 0xF;
        uint8_t ra = (i >> 4) & 0xF; 
        uint8_t imm = i & 0xF;
    
    }

    void handle_subi(uint16_t i){
        // Opcode - 15:12
        // Register Destination - 11:8
        // Register A - 7:4
        // Immediate Value - 3:0

        uint8_t rd = (i >> 8) & 0xF;
        uint8_t ra = (i >> 4) & 0xF; 
        uint8_t imm = i & 0xF;
    
    }

    void handle_andi(uint16_t i){
        // Opcode - 15:12
        // Register Destination - 11:8
        // Register A - 7:4
        // Immediate Value - 3:0

        uint8_t rd = (i >> 8) & 0xF;
        uint8_t ra = (i >> 4) & 0xF; 
        uint8_t imm = i & 0xF;
    }

    void handle_ori(uint16_t i){
        // Opcode - 15:12
        // Register Destination - 11:8
        // Register A - 7:4
        // Immediate Value - 3:0

        uint8_t rd = (i >> 8) & 0xF;
        uint8_t ra = (i >> 4) & 0xF; 
        uint8_t imm = i & 0xF;
    
    }
};