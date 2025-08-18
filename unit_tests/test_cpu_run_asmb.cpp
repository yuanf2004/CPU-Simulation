#include "../cpu.h"
#include <string>
#include <vector>
#include <gtest/gtest.h>

TEST(CPUTest, AssemblyOption){
    CentralProcessingUnit cpu;
    uint16_t rs5 = cpu.test_run_assembly_file("test_beqbne.txt");
    EXPECT_EQ(rs5, 10);
};