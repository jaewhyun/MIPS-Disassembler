//
//  mipsdisassembler.h
//  mipsdisassembler
//
//  Created by Jae Won Hyun on 9/29/16.
//  Copyright © 2016 Jae Won Hyun. All rights reserved.
//

#ifndef mipsdisassembler_h
#define mipsdisassembler_h

#include <iomanip>
#include <iostream>
#include <array>
using namespace std;

class Disassembler
{
public:
    static const size_t instructionset = 11; // declare arrray size
    
    Disassembler(); // initial constructor
    void setopcode(int instruction); // find opcode
    void rtypedis(int instruction); // r type
    void itypedis(int instruction); // i type
    void branchtypedis(int instruction); // branch
    void setfunction(int instruction); // find function
    void sets1register(int instruction); // set first register
    int gets1register(); // return first register
    void sets2register(int instruction); // set second register
    int gets2register(); // get second register
    void setdregister(int instruction); // set destination register
    int getdregister(); // get destination register
    void setoffset(int instruction); // set offset
    short getoffset(); // get offset 
    void incrementaddress(); // incrementaddress
    
private:
    int opcode; 
    int address;
    int label;
    int function;
    int sRegister1;
    int sRegister2;
    int dRegister;
    int addresscount;
    short offset;
    array<int, instructionset> instructions; // delcare aray
};

#endif /* mipsdisassembler_h */
