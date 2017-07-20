//
//  mipsdisassembler.cpp
//  mipsdisassembler
//
//  Created by Jae Won Hyun on 9/29/16.
//  Copyright © 2016 Jae Won Hyun. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
#include "mipsdisassembler.h"

Disassembler::Disassembler() 
{
    // input instructions into array
    instructions[0] = 0x022DA822;
    instructions[1] = 0x8EF30018;
    instructions[2] = 0x12A70004;
    instructions[3] = 0x02689820;
    instructions[4] = 0xAD930018;
    instructions[5] = 0x02697824;
    instructions[6] = 0xAD8FFFF4;
    instructions[7] = 0x018C6020;
    instructions[8] = 0x02A4A825;
    instructions[9] = 0x158FFFF6;
    instructions[10] = 0x8E59FFF0;

    // initialize address
    address = 0x7A060;
    
    // increment address and figure out opcode for every instruction
    for(size_t i = 0; i < 11; i++)
    {
        cout << hex << address << " ";
        incrementaddress();
        setopcode(instructions[i]);
    }
    
}

// set opcode
void Disassembler::setopcode(int instruction)
{
    opcode = (instruction & 0xFC000000) >> 26;
    
    // if opcode = 0, go to rtype disassembler
    if(opcode == 0)
    {
        rtypedis(instruction);
    }
    // if not, go to itype disassembler
    else
    {
        itypedis(instruction);
    }
}

// set function
void Disassembler::setfunction(int instruction)
{
    function = (instruction & 0x0000003F);
    
    // print out different functions
    if(function == 32)
    {
        cout << "add ";
    }
    else if(function == 34)
    {
        cout << "sub ";
    }
    else if(function == 36)
    {
        cout << "and ";
    }
    else if(function == 37)
    {
        cout << "or ";
    }
    
}

// set first register
void Disassembler::sets1register(int instruction)
{
    sRegister1 = (instruction & 0x03E00000) >> 21;
}

// get first register
int Disassembler::gets1register()
{
    return sRegister1;
}

// set second register
void Disassembler::sets2register(int instruction)
{
    sRegister2 = (instruction & 0x001F0000) >> 16;
}

// get second register
int Disassembler::gets2register()
{
    return sRegister2;
}

// set destination register
void Disassembler::setdregister(int instruction)
{
    dRegister = (instruction & 0x0000F800) >> 11;
}

// get desitination register
int Disassembler::getdregister()
{
    return dRegister;
}

// set offset
void Disassembler::setoffset(int instruction)
{
    offset = (instruction & 0x0000FFFF);
    
    if(opcode == 4 || opcode == 5)
    {
        offset = offset << 2;
    }
}

// get offset
short Disassembler::getoffset()
{
    return offset;
}

// disassemble rtype instruction
void Disassembler::rtypedis(int instruction)
{
    setfunction(instruction);
    
    setdregister(instruction);
    cout << dec << "$" << getdregister() << ", ";
    
    sets1register(instruction);
    cout<< dec << "$" << gets1register() << ", ";
    
    sets2register(instruction);
    cout<< dec <<"$" << gets2register() << " \n";
}

// disassemble itype instruction
void Disassembler::itypedis(int instruction)
{
    if(opcode == 4 || opcode == 5)
    {
        branchtypedis(instruction);
    }
    else
    {
        if(opcode == 35)
        {
            cout << "lw ";
            
        }
        else if(opcode == 43)
        {
            cout << "sw ";
        }

        sets2register(instruction);
        cout<< dec << "$" << gets2register() << ", ";
        
        setoffset(instruction);
        cout<< dec << getoffset() << " ";
        
        sets1register(instruction);
        cout<< dec << "($" << gets1register() << ") \n";
    }
}

// disassemble branch
void Disassembler::branchtypedis(int instruction)
{
    if(opcode == 4)
    {
        cout << "beq ";
    }
    else if(opcode == 5)
    {
        cout << "bne ";
    }
    
    sets2register(instruction);
    cout<< dec << "$" << gets2register() << ", ";
    
    sets1register(instruction);
    cout<< dec <<"$" << gets1register() << ", ";

    setoffset(instruction);
    label = offset + address;
    cout<< "address " << hex << label << " \n";
}

// increment address
void Disassembler::incrementaddress()
{
    address = address + 4;
    
}
