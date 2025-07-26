#include "alu.h"

class ArithmeticLogicUnit{
    
    private:
        Registers *r;
        RandomAccessMemory *ram;

    public:
    ArithmeticLogicUnit(Registers *r, RandomAccessMemory *ram){
        // Constructor
        this->r = r;
        this->ram = ram;
    };

    void alu_load(uint16_t i){
        // Register Destination - 11:8
        // Memory Location - 7:0
        uint16_t regdest = (i >> 8) & 0xF;
        uint16_t memloc = i & 0xFF;

        uint16_t ram_data = ram->get_ramcell(memloc);
        r->update_general_purpose_register(regdest, ram_data);
    };

    void alu_store(uint16_t i){
        // Register Source - 11:8
        // Memory Location - 7:0
        uint16_t regsrc = (i >> 8) & 0xF;
        uint16_t memloc = i & 0xFF;

        uint16_t reg_data = r->get_data_general_purpose_register(regsrc);
        ram->update_ramcell(memloc, reg_data);    
    };

    void alu_add(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Register B - 3:0

        uint16_t regdest = (i >> 8) & 0xF; 
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t regb = i & 0xF;
    
        uint16_t rega_data = r->get_data_general_purpose_register(rega);
        uint16_t regb_data = r->get_data_general_purpose_register(regb);

        r->update_general_purpose_register(regdest, (rega_data + rega_data));
    };

    void alu_sub(uint16_t i){
        // Register Destination - 11:8
        // Register A - 7:4
        // Register B - 3:0

        uint16_t regdest = (i >> 8) & 0xF; 
        uint16_t rega = (i >> 4) & 0xF;
        uint16_t regb = i & 0xF;
    
        uint16_t rega_data = r->get_data_general_purpose_register(rega);
        uint16_t regb_data = r->get_data_general_purpose_register(regb);

        r->update_general_purpose_register(regdest, (rega_data + rega_data));
    };

    void alu_and(){};


    void alu_or(){};

    void alu_xor(){};

    void alu_not(){};

    // To be filled out later
    void alu_jmp(){
    };

    // To be filled out later
    void alu_jz(){
    };

    void alu_addi(){};

    void alu_subi(){};

    void alu_andi(){};

    void alu_ori(){};

    void alu_xori(){};







    

    




    



};
