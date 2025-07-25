#include "alu.h"

class ArithmeticLogicUnit{
    
    private:

    public:
    ArithmeticLogicUnit(){
        // Constructor
    };

    void alu_load(
        GeneralPurposeRegister &rd,
        RandomAccessMemory &ram,
        uint8_t mem_location
    ){
    // Load from memory into register
    // Instruction Formatting:
    // 4 bits opcode, 4 bits destination register, 8 bits memory location
        rd.update_data(ram.get_ramcell(mem_location));
    };

    void alu_store(
        GeneralPurposeRegister &a,
        RandomAccessMemory &ram,
        uint8_t mem_location
    ){
    // Store data from register into memory
    // Instruction Formatting:
    // 4 bits opcode, 4 bits destination register, 8 bits memory location
        ram.update_ramcell(mem_location, a.get_data());
    };

    void alu_add(
        GeneralPurposeRegister &a, 
        GeneralPurposeRegister &b, 
        GeneralPurposeRegister &rd
    ){
    // Opcode 0000
        rd.update_data(a.get_data() + b.get_data());
    };

    void alu_sub(
        GeneralPurposeRegister &a, 
        GeneralPurposeRegister &b, 
        GeneralPurposeRegister &rd
    ){
    // Opcode 0001
        rd.update_data(a.get_data() - b.get_data());
    };

    void alu_and(
        GeneralPurposeRegister &a, 
        GeneralPurposeRegister &b, 
        GeneralPurposeRegister &rd
    ){
    // Opcode 0010
        rd.update_data(a.get_data() & b.get_data());
    };

    void alu_or(
        GeneralPurposeRegister &a, 
        GeneralPurposeRegister &b, 
        GeneralPurposeRegister &rd
    ){
    // Opcode 0011
        rd.update_data(a.get_data() | b.get_data());
    };

    void alu_xor(
        GeneralPurposeRegister &a, 
        GeneralPurposeRegister &b, 
        GeneralPurposeRegister &rd
    ){
    // Opcode 0100
        rd.update_data(a.get_data() ^ b.get_data());
    };

    void alu_not(
        GeneralPurposeRegister &a, 
        GeneralPurposeRegister &rd
    ){
    // Opcode 0101
        rd.update_data(~(a.get_data()));
    };

    // To be filled out later
    void alu_jmp(){
    // Opcode 0110
    };

    // To be filled out later
    void alu_jz(){
    // Opcode 0111
    };

    void alu_addi(
        GeneralPurposeRegister &a,
        uint8_t immb,
        GeneralPurposeRegister &rd
    ){
    // Opcode 1000
        rd.update_data(a.get_data() + immb);
    }

    void alu_subi(
        GeneralPurposeRegister &a,
        uint8_t immb,
        GeneralPurposeRegister &rd
    ){
    // Opcode 1001
        rd.update_data(a.get_data() - immb);
    }

    void alu_andi(
        GeneralPurposeRegister &a,
        uint8_t immb,
        GeneralPurposeRegister &rd
    ){
    // Opcode 1010
        rd.update_data(a.get_data() & immb);
    }

    void alu_ori(
        GeneralPurposeRegister &a,
        uint8_t immb,
        GeneralPurposeRegister &rd
    ){
        rd.update_data(a.get_data() | immb);
    }







    

    




    



};
