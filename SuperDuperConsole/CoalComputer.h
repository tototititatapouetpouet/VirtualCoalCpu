#pragma once

#include "Instruction.h"

#include <vector>
#include <string>

class ConsoleFramebuffer;

namespace Coal
{
    class Register
    {
        friend class CPU;
        friend class Debuger;
        friend class OperandAccessor;

    public:
        const unsigned char& getValue() const { return m_value; }

    protected:
        void setValue(unsigned char newValue) { m_value = newValue; }

    private:
        unsigned char m_value = 0;
    };

    using InstructionLine = std::string;
    using InstructionList = std::vector<InstructionLine>;

    class CPU
    {
    public:
        Register& getRegister(int idx);
        const Register& getRegister(int idx) const;
        void processOneInstruction(const InstructionList&);
        Register& getInstructionPointerRegister();
        const Register& getInstructionPointerRegister() const;

    private:
        Register m_registers[16];
    };
    
    void showCPU(ConsoleFramebuffer& cfb, const CPU& cpu);

    class Computer
    {
    public:
        CPU& getCPU();
        const CPU& getCPU() const;
    
    private:
        CPU m_cpu;
        InstructionList m_instructions;
    };
}
