#include "assembler.h"

Assembler::Assembler(){};

uint16_t Assembler::generate_instruction_code(std::string assembly_line){
        // generate an instruction based off of one line of assembly
        uint16_t instruction_code = 0x00;

        uint16_t op = fetch_op(assembly_line);
        // 4 bit msb representing opcode
        instruction_code |= (op << 12);
        uint16_t instruction_12_to_0 = fetch_non_op(op, assembly_line);

        // bitwise or with rest of instruction
        op |= instruction_12_to_0;
        return op;
};

std::vector<std::string> line_split(std::string assembly_line){
    // helper function to split the line of assembly
    std::vector<std::string> asmb_components;
    std::istringstream iss(assembly_line);
    std::string word;
    while(iss >> word){
        asmb_components.push_back(word);
    }
    return asmb_components;
}

std::vector<std::string> assembly_split(std::string fpath){
// take a .txt file and split up each line to be returned as a vector containing all
    std::ifstream file(fpath);
    std::string line;
    std::vector<std::string> assembly_lines;

    while(std::getline(file, line)){
        assembly_lines.push_back(line);
    };

    return assembly_lines;
};

uint16_t Assembler::fetch_op(std::string assembly_line){
    // case sensitive assembly 

    // op will be the 0th element of the vector
    std::string op = line_split(assembly_line).at(0);
    if(op == "load"){
        
    }
    else if(op == "store"){
        return 0x0;
    }
    else if(op == "add"){
        return 0x1;
    }
    else if(op == "sub"){
        return 0x2;
    }
    else if(op == "and"){
        return 0x3;
    }
    else if(op == "or"){
        return 0x4;
    }
    else if(op == "xor"){
        return 0x5;
    }
    else if(op == "not"){
        return 0x6;
    }
    else if(op == "addi"){
        return 0x7;
    }
    else if(op == "subi"){
        return 0x8;
    }
    else if(op == "andi"){
        return 0x9;
    }
    else if(op == "ori"){
        return 0xA;
    }
    else if(op == "xori"){
        return 0xB;
    }
    else if(op == "jmp"){
        return 0xC;
    }
    else if(op == "jz"){
        return 0xD;
    }
    else if(op == "jnz"){
        return 0xE;
    }   
    else{
        // error case, may need to go back to this to fix since it is jnz
        return 0xF;
    }
};

uint16_t Assembler::fetch_non_op(uint16_t op, std::string assembly_line){
// return bits 12 to 0 of instruction depending on opcode
    std::vector<std::string> asmb_components = line_split(assembly_line);
    switch(op){
        uint16_t instr = 0x0;
        case(0x1):
            // load rd memloc
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_mem(asmb_components.at(2));
        case(0x2): 
            // store rs memloc
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_mem(asmb_components.at(2));
        case(0x3):
            // add rd ra rb    
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_rs(asmb_components.at(2), 'a');
            instr |= fetch_rs(asmb_components.at(3), 'b');
            return instr;
        case(0x4):
            // sub rd ra rb
            instr |= fetch_rs(asmb_components.at(1), 'a');
            instr |= fetch_rs(asmb_components.at(2), 'b');
            instr |= fetch_rs(asmb_components.at(3), 'c');
            return instr;
        case(0x5):
            // and rd ra rb
            instr |= fetch_rs(asmb_components.at(1), 'a');
            instr |= fetch_rs(asmb_components.at(2), 'b');
            instr |= fetch_rs(asmb_components.at(3), 'c');
            return instr;
        case(0x6):
            // or rd ra rb
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_rs(asmb_components.at(2), 'a');
            instr |= fetch_rs(asmb_components.at(3), 'b');
            return instr;
        case(0x7):
            // xor rd ra rb
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_rs(asmb_components.at(2), 'a');
            instr |= fetch_rs(asmb_components.at(3), 'b');
            return instr;
        case(0x8):
            // not rd ra
            instr |= fetch_rs(asmb_components.at(1), 'd');
            instr |= fetch_rs(asmb_components.at(2), 'a');
            return instr;
        case(0x9):
            // addi rd ra imm
            instr |= fetch_rs(asmb_components.at(1), 'a');
            instr |= fetch_rs(asmb_components.at(2), 'b');
            instr |= fetch_imm(asmb_components.at(3));
            return instr;
        case(0xA):
            // subi rd ra imm
            instr |= fetch_rs(asmb_components.at(1), 'a');
            instr |= fetch_rs(asmb_components.at(2), 'b');
            instr |= fetch_imm(asmb_components.at(3));
            return instr;
        case(0xB):
            // ori rd ra imm
            instr |= fetch_rs(asmb_components.at(1), 'a');
            instr |= fetch_rs(asmb_components.at(2), 'b');
            instr |= fetch_imm(asmb_components.at(3));
            return instr;
        case(0xC):
            // xori rd ra imm
            instr |= fetch_rs(asmb_components.at(1), 'a');
            instr |= fetch_rs(asmb_components.at(2), 'b');
            instr |= fetch_imm(asmb_components.at(3));
            return instr;
        case(0xD):
            // jmp

            return instr;
        case(0xE):
            // jz

            return instr;
        case(0xF):
            // jnz

            return instr;
        default:
            //error 
            return 0xFFFF;
    }

};

uint16_t Assembler::fetch_rs(std::string reg, char type){
    // splits the number from rs to get the bit representation
    std::string num_str;
    int bit_shift;

    if(type == 'd'){
        bit_shift = 8;
    }
    else if(type == 'a'){
        bit_shift = 4;
    }
    else if(type == 'b'){
        bit_shift = 0;
    }
    else{
        //error
        return 0xFFFF;
    }
    
    // grab number digits after rs
    for (char c : reg){
        if(std::isdigit(c)){
            num_str += c;
        }
    }

    if(!num_str.empty()){
        return static_cast<uint16_t>(std::stoi(num_str)) << bit_shift;
    }
    else{
        // error
        0xFFFF;
    }
};

uint16_t Assembler::fetch_imm(std::string imm){
    // return immediate value as an int, not a str
    return static_cast<uint16_t>(std::stoi(imm));
};

uint16_t Assembler::fetch_mem(std::string mem){
// decode the memory and return it as a uint
    std::string num_str;

    for(char c : mem){
        if(std::isdigit(c)){
            num_str += c;
        }

        if(!num_str.empty()){
        return static_cast<uint16_t>(std::stoi(num_str));
        }
    }
};