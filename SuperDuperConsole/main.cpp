#include "ConsoleFramebuffer.h"
#include "CoalComputer.h"

#include <iostream>

int main(int argc, char** argv)
{
    ConsoleFramebuffer cfb;
    
    Coal::Computer computer;

    /*
    Coal::InstructionList instructionList = {
        "MOV 42 r7"
      , "MOV 12 r0"
      , "ADD r0 r7 r14"
      , "ADD r0 5  r14"
      , "ADD 7  r0 r14"
      , "SUB r7 r0 r13"
      , "MUL r7 2  r12"
      , "MUL r7 r0 r12"
      , "DIV r7 r0 r11"
      , "DIV r7 0  r11 "
      , "JE r0 r1 0"
    };
    */

    Coal::InstructionList instructionList = {
        "MOV 123 r0"
      , "DISPN 0 0 r0"
      , "ADD r5 48 r6"
      , "DISP 0 0 r6"
      , "DIV r0 100 r5"
      , "DISP 0 0 65"
      , "MOV 42 r1"
      , "JE r0 r1 4"
      , "MOV 32 r5"
      , "MOV 30 r4"
    };

    Coal::showCPU(cfb, computer.cpu);
    Coal::showScreen(cfb, computer.screen);
    cfb.show();

    while (!instructionList.empty())
    {
        ::getchar();
        try
        {
            computer.cpu.processOneInstruction(instructionList);
        }
        catch (std::runtime_error& e)
        {
            std::cerr << e.what();
            return 0;
        }

        Coal::showCPU(cfb, computer.cpu);
        Coal::showScreen(cfb, computer.screen);
        cfb.show();
    }
}
