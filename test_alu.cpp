#include "alu.h"
#include "registers.h"
#include "ram.h"
#include <gtest/gtest.h>

TEST(ALUTest, LoadStoreOperations){
    Registers r;
    RandomAccessMemory ram;
    ArithmeticLogicUnit alu(&r, &ram);

    alu.alu_addi(0, 0, 7);
    alu.alu_store(0, 888);
    EXPECT_EQ(ram.get_ramcell(888), 7);
    alu.alu_load(9, 888); 
    EXPECT_EQ(r.get_data_general_purpose_register(9), 7);

    r.clear_all_general_purpose_registers();
    ram.clear_ramcells();
};

TEST(ALUTest, RegisterOperations){
    Registers r;
    RandomAccessMemory ram;
    ArithmeticLogicUnit alu(&r, &ram);

    // populate first
    alu.alu_addi(0, 0, 10);
    alu.alu_addi(1, 1, 3);

    alu.alu_add(2, 0, 1);
    EXPECT_EQ(r.get_data_general_purpose_register(2), 13);
    alu.alu_sub(2, 0, 1); 
    EXPECT_EQ(r.get_data_general_purpose_register(2), 7);
    alu.alu_and(2, 0, 1);
    EXPECT_EQ(r.get_data_general_purpose_register(2), 2);
    alu.alu_or(2, 0, 1);
    EXPECT_EQ(r.get_data_general_purpose_register(2), 11);
    alu.alu_xor(2, 0, 1);
    EXPECT_EQ(r.get_data_general_purpose_register(2), 9);
    alu.alu_not(2, 2);
    // because 16 bits the number is so large
    EXPECT_EQ(r.get_data_general_purpose_register(2), 65526);

    r.clear_all_general_purpose_registers();
    ram.clear_ramcells();
};

TEST(ALUTest, ImmediateOperations){
    Registers r;
    RandomAccessMemory ram;
    ArithmeticLogicUnit alu(&r, &ram);

    //operations onto the different registers immediate
    alu.alu_addi(1, 0, 5);
    EXPECT_EQ(r.get_data_general_purpose_register(1), 5);
    alu.alu_subi(1, 1, 3);
    EXPECT_EQ(r.get_data_general_purpose_register(1), 2);
    alu.alu_andi(2, 1, 2);
    EXPECT_EQ(r.get_data_general_purpose_register(2), 2);
    alu.alu_ori(2, 2, 3);
    EXPECT_EQ(r.get_data_general_purpose_register(2), 3);
    alu.alu_xori(3, 2, 0);
    EXPECT_EQ(r.get_data_general_purpose_register(3), 3);

    r.clear_all_general_purpose_registers();
    ram.clear_ramcells();
};

//TODO: add unit test for jz, jzn.. etc?


