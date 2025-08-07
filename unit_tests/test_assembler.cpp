#include "../assembler.h"
#include <string>
#include <vector>
#include <gtest/gtest.h>

TEST(AssemblerTest, GenerateInstructionCode){
// test the assembler's ability to generate instruction codes
    Assembler asmb;

    // example 1 - addi
    // this should result in: 0x8108
    std::string example = "addi rs1 rs0 8";
    uint16_t example1code = asmb.generate_instruction_code(example);
    EXPECT_EQ(example1code, 0x8108);

    // example 2 - sub 
    // this should result in: 0x3897
    example = "sub rs8 rs9 rs7";
    uint16_t example2code = asmb.generate_instruction_code(example);
    EXPECT_EQ(example2code, 0x3897);

    // example 3 - store
    // this should result in: 0b 0001 0010 1101 1110 or 0x12DE
    example = "store rs2 memloc222";
    uint16_t example3code = asmb.generate_instruction_code(example);
    EXPECT_EQ(example3code, 0x12DE);

    // example 4 - and
    // this should result in: 0x4567
    example = "and rs5 rs6 rs7";
    uint16_t example4code = asmb.generate_instruction_code(example);
    EXPECT_EQ(example4code, 0x4567);
};

TEST(AssemblerTest, AssemblySplit){
// test to see if the assembler can split text files by line
    Assembler asmb;
    std::string fpath = "assembly_files/test_assembly.txt";
    std::vector<std::string> expected_vector = {"add rs2 rs8 rs9",
        "subi rs1 rs7 99",
        "load rs8 memloc200",
        "xor rs4 rs1 rs2"};
    EXPECT_EQ(asmb.assembly_split(fpath), expected_vector);
};