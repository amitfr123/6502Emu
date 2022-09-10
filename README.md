# 6502Emu
This project was created as a part of an emulator for the NES console.
This project contains a cpu class that can be used to emulate the 6502 cpu.

## What does the repo contain?
This repository contains file copied as is from the NES emulator repository.

* Cpu files - This files contain all of the "logic" for the cpu.
* NumToHexStringConvertor - This is a utility class created to convert hex numbers to string.
* NestestLogTester - This class was created to "debug" the cpu. It compares the cpu current state to the expected state from a valid emulator running the nestest rom.

## How to use
As a user you might/will need to make some changes to the files in this project. Here is a list of changes you might need to preform:

* Change include paths to match your project.
* For testing the cpu against the nestest log you will need to define the next variables:
    1. NESTEST_DEBUG
    2. NESTEST_ROM_LOG_PATH - The path to the nestest.log file

If you wish to just import the cpu class into your project you will just need to take the Cpu.hpp Cpu.cpp and the NumToHexStringConvertor.hpp and change the include paths.

### How does the cpu class work?
The cpu is given 2 functions in the constructor. This functions represent the connection between the cpu and the mmu/bus (the source and destination for the cpu read and write operations).

    using WriteFunction = std::function<void (const uint16_t address, const uint8_t data)>;
    using ReadFunction = std::function<uint8_t (const uint16_t address)>;

    Cpu(WriteFunction mmu_write, ReadFunction mmu_read);

If you wish to dissemble your rom you may do that by calling the Disassemble function.

* Notice that the Disassemble function is naive. It reads the entire address space once and try to disassemble all of it. The function does not differentiate memory types (is you use it for an emulator it will read RAM ROM and IO memory). 
And the function does not preform logical actions.

Every time you call the CpuExecuteInstruction function a full asm instruction is preformed.

## Future features to be added:
While i don't promise that there would be future updates to this repository i do plan to update it if i change the cpu class while working on the NES emulator.

The main features i want to add are:
* Making this repository compile to a library.
* Support "illegal" opcodes - There are many opcodes that are not official in the cpu instruction set so if i have the time i want to add support for them.

## A note about the commit history
In this repository i originally wrote some code that is related to the NES emulator and not the cpu.
After Thinking about what i should do i decided to delete that code and create a new repository to contain all of the NES emulator code.