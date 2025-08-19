# YF16-CPU Simulation 
**YF16-CPU Simulation** is my personal approach to the reconstruction of a 16-bit RISC architecture central processing unit with C++.

I created this project to grasp a stronger understanding of computer architecture and the brain of the computer. 

The CPU simulation in this program can take in user Assembly instructions in two forms:

* Continuous Loop: Users can continuously type in new lines of Assembly to program the CPU.
* Assembly: Users can upload a written Assembly .txt file, drop it into the "assembly_files" folder, and run the program.

Both program forms allow the analysis of registers and memory by allowing the user to view the data held inside.

--- 
## **How to Use?**
Clone the repository into user desired project workspace and then compile the code. 
For me personally, the compile command is: 

**clang++ -std=c++17 -g main.cpp cpu/simulation.cpp cpu/registers.cpp cpu/ram.cpp cpu/cu.cpp cpu/cpu.cpp cpu/assembler.cpp cpu/alu.cpp -o main**

Once this succeeds, run ./main in the terminal and the program will start.

Before running the program, it is recommended to adjust the settings by typing "2" into the main menu (Change Simulation Settings).
In the settings, the user can change the program type (continuous loop/assembly) and also change the Assembly .txt file to be read by the program (more on this in section below).

To run the program, type "1" in the main menu and the selected program form will run.

For the **continuous loop program**, each line input will take one of four **arguments**:
* [1] The Assembly instruction, to be covered in the section below.
* [2] "rsX" command, replace X with a number see the value in register X. The range is 0 to 31 (32 registers)
* [3] "memlocX" command, replace X with a number to see the value in memory location X. The range is 0 to 65535
* [4] "exit" command goes back to the main menu
  
For the **Assembly program**, it will take all of the same arguments above ⬆️ except for the Assembly instruction. 

---

# **Assembly Instructions**

The instruction set is 16 bits, but the opcode (operation code) always remains the four most significant bits from 15:12. 
This means that there are 16 different operations that can be used:

**NOTES**: 
* Any capital letter should be replaced with numbers
* _DON'T CARE_ means that the bits in the field do not matter for the program
* _IMMEDIATE_ means the immediate user provided number
* jmp, beq, and bne are **ASSEMBLY PROGRAM ONLY**
* _LINE_ means line number to jump to
<br>

* 0x0 - **load** (loads from memory into register)
  * Format: load (4 bits) rsX (4 bits) memlocX (12 bits)
* 0x1 - **store** (stores from register into memory)
  * Format: store (4 bits) rsX (4 bits) memlocX (12 bits) 
* 0x2 - **add** (with value of two registers)
  * Format: add (4 bits) rsX (4 bits) rsA (4 bits) rsB (4 bits)
* 0x3 - **sub**, aka subtract (register)
  * Format: sub (4 bits) rsX (4 bits) rsA (4 bits) rsB (4 bits)
* 0x4 - **and**, aka bitwise and (register)
  * Format: and (4 bits) rsX (4 bits) rsA (4 bits) rsB (4 bits)
* 0x5 - **or**, aka bitwise or (register)
  * Format: or (4 bits) rsX (4 bits) rsA (4 bits) rsB (4 bits)
* 0x6 - **xor**, aka bitwise exclusive or (register only)
  * Format: xor (4 bits) rsX (4 bits) rsA (4 bits) rsB (4 bits) 
* 0x7 - **not**, aka bitwise not
  * Format: not (4 bits) rsX (4 bits) rsA (4 bits) DON'T CARE (4 bits)
* 0x8 - **addi** (with an immediate provided number)
  * Format: addi (4 bits) rsX (4 bits) rsA (4 bits) IMMEDIATE (4 bits)
* 0x9 - **subi** (immediate)
  * Format: subi (4 bits) rsX (4 bits) rsA (4 bits) IMMEDIATE (4 bits)
* 0xA - **andi** (immediate)
  * Format: andi (4 bits) rsX (4 bits) rsA (4 bits) IMMEDIATE (4 bits)
* 0xB - **ori** (immediate)
  * Format: ori (4 bits) rsX (4 bits) rsA (4 bits) IMMEDIATE (4 bits)
* 0xC - **xori** (immediate)
  * Format: xori (4 bits) rsX (4 bits) rsA (4 bits) IMMEDIATE (4 bits)
* 0xD - **jmp**, aka jump to line
  * Format: jmp (4 bits) LINE (12 bits)
* 0xE - **beq**, aka branch if equal
  * Format: beq (4 bits) rsA (4 bits) rsB (4 bits) LINE (4 bits)
* 0xF - **bne**, aka branch if not equal
  * Format: bne (4 bits) rsA (4 bits) rsB (4 bits) LINE (4 bits)

## **Example Usages**

**addi rs3 rs0 18** - adds value of register 0 and 18 and places result in register 3

**sub rs2 rs3 rs9** - subtracts value of register 9 from register 3 and places result in register 2

**jmp 23** - jump to line 23 of assembly

**beq rs0 rs2 4** - if register 0 and register 2 value are equal, jump to line 4

**bneq rs0 rs0 2** - if register 0 and register 0 are not equal, jump to line 2

---

# **Adding/Deleting Readable Assembly Files**

All Assembly files that are read by the program are in the "assembly_files" folder that comes with the repository.
These files are .txt files, and each line can hold one instruction line of Assembly.
The user is free to delete test .txt files or add their own .txt files for the CPU to run; newly added Assembly .txt files will appear in the settings on rerun of the program.

---

Thank you for checking out this project!

**Author**: Yuan Feng

**Email** yuanf.nyc@gmail.com
