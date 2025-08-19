#include "../cpu.h"
#include <string>
#include <vector>
#include <gtest/gtest.h>

TEST(CPUTestAssemblyOption, beqtest){
    CentralProcessingUnit cpu;
    uint16_t rs5 = cpu.test_run_assembly_file("test_beqbne.txt", "beq");
    EXPECT_EQ(rs5, 10);
};

TEST(CPUTestAssemblyOption, jmptest){
    CentralProcessingUnit cpu;
    uint16_t rs0 = cpu.test_run_assembly_file("test_jmp.txt", "jmp");
    EXPECT_EQ(rs0, 3);
};
