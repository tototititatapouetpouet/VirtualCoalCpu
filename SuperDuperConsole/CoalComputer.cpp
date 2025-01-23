#include "CoalComputer.h"

#include "ConsoleFramebuffer.h"
#include "Exception.h"

#include <sstream>

namespace
{
    using Token = Coal::Token;
    using TokenList = Coal::TokenList;
    TokenList splitStringBySpace(const std::string& str)
    {
        std::string workingStr = str;
        TokenList tokenList;

        while (true)
        {
            auto index = workingStr.find_first_of(' ');
            if (index == std::string::npos)
                break;

            std::string tmp(&workingStr[0], index);
            tokenList.push_back(tmp);
            workingStr = std::string(&workingStr[index + 1], workingStr.size() - (index + 1));
        }
        tokenList.push_back(workingStr);

        return tokenList;
    }

    TokenList removeEmptyTokens(const TokenList& tokens)
    {
        TokenList result;
        for (size_t i = 0; i < tokens.size(); ++i)
        {
            if (tokens[i] != "")
                result.push_back(tokens[i]);
        }
        return result;
    }

    TokenList splitIntoTokens(const std::string& str)
    {
        return removeEmptyTokens(splitStringBySpace(str));
    }
}

namespace Coal
{
    void showCPU(ConsoleFramebuffer& cfb, const CPU& cpu)
    {
        for (int row = 0; row < 10; ++row)
            for (int col = 0; col < 10; ++col)
                cfb.setCharacter(row, col, ' ', Green, Green);

        for (int row = 0; row < 8; ++row)
        {
            std::stringstream ss;
            ss << static_cast<unsigned int>(cpu.getRegister(row).getValue());
            cfb.printString(row + 1, 1, ss.str(), Green, White);
        }

        for (int row = 0; row < 8; ++row)
        {
            std::stringstream ss;
            ss << static_cast<unsigned int>(cpu.getRegister(row + 8).getValue());
            cfb.printString(row + 1, 6, ss.str(), Green, White);
        }
    }

    const Register& CPU::getRegister(int idx)const { return m_registers[idx]; }
    Register& CPU::getRegister(int idx) { return m_registers[idx]; }

    Register& CPU::getInstructionPointerRegister() { return m_registers[15]; }
    const Register& CPU::getInstructionPointerRegister() const { return m_registers[15]; }

    void CPU::processOneInstruction(const InstructionList& instructionList)
    {
        const InstructionLine& instructionLine = instructionList[getInstructionPointerRegister().getValue()];
        TokenList tokenList = splitIntoTokens(instructionLine);
        const InstructionType& instructionType = tokenList[0];

        IInstruction* instruction = getInstructionFactoryNewStyle().create(instructionType, tokenList);
        instruction->apply(*this);
        
        getInstructionPointerRegister().setValue(getInstructionPointerRegister().getValue() + 1);
    }
}
