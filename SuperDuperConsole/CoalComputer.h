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

    class Screen
    {
    public:
        Screen();
        const char& getChar(int row, int col) const;
        void setChar(int row, int col, char value);
        const int getHeight() const;
        const int getWidth() const;

    private:
        std::vector<char> m_data;
        int m_height;
        int m_width;
    };

    class Computer;

    class CPU
    {
    public:
        CPU(Computer& computer);
        Register& getRegister(int idx);
        const Register& getRegister(int idx) const;
        void processOneInstruction(const InstructionList&);
        Register& getInstructionPointerRegister();
        const Register& getInstructionPointerRegister() const;

        Computer& getComputer();
        const Computer& getComputer() const;

    private:
        Register m_registers[16];
        Computer& m_computer;
    };
    
    void showCPU(ConsoleFramebuffer& cfb, const CPU& cpu);
    void showScreen(ConsoleFramebuffer& cfb, const Screen& screen);

    class Computer
    {
    public:
        Computer();

        CPU cpu;
        Screen screen;
        InstructionList instructions;
    };
}
