#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdint.h>
#include <string>
#include <vector>
#include <sstream>

class Assembler{
private:
public:
    // Need an assembler that reads a file line by line

    //ex:

    // add rd rsx rsy

    uint16_t generate_instruction_code(std::string assembly_line){};

    std::vector<std::string> line_split(std::string assembly_line){};

    uint16_t fetch_op(std::string assembly_line){};

    uint16_t fetch_non_op(uint16_t op, std::string assembly_line){};
    // this function is supposed to get the opcode and then
    // decode the rest of the line based on the given opcode

    // these will first depend on the opcode fetched

    uint16_t fetch_rs(std::string reg, char type){};

    uint16_t fetch_imm(std::string imm){};

    uint16_t fetch_mem(std::string imm){};
};

#endif