#include "Instruction.h"
#include "CoalComputer.h"

namespace Coal
{
    class Mov : public IInstruction
    {
    public:
        Mov(const TokenList& tokenList) : IInstruction(tokenList, 3), src(tokenList[1]), dest(tokenList[2])
        {
        }

        void apply(CPU& cpu) override
        {
            dest.affect(cpu, src.evaluate(cpu));
        }

        OperandAccessor src;
        OperandAccessor dest;
    };

    class Add : public IInstructionWith2InputOperandsAnd1OutputOperand
    {
    public:
        Add(const TokenList& tokenList) : IInstructionWith2InputOperandsAnd1OutputOperand(tokenList)
        {
        }

        void apply(CPU& cpu) override
        {
            dest.affect(cpu, src1.evaluate(cpu) + src2.evaluate(cpu));
        }
    };

    class Sub : public IInstructionWith2InputOperandsAnd1OutputOperand
    {
    public:
        Sub(const TokenList& tokenList) : IInstructionWith2InputOperandsAnd1OutputOperand(tokenList)
        {
        }

        void apply(CPU& cpu) override
        {
            dest.affect(cpu, src1.evaluate(cpu) - src2.evaluate(cpu));
        }
    };

    class Mul : public IInstructionWith2InputOperandsAnd1OutputOperand
    {
    public:
        Mul(const TokenList& tokenList) : IInstructionWith2InputOperandsAnd1OutputOperand(tokenList)
        {
        }

        void apply(CPU& cpu) override
        {
            dest.affect(cpu, src1.evaluate(cpu) * src2.evaluate(cpu));
        }
    };

    class Div : public IInstructionWith2InputOperandsAnd1OutputOperand
    {
    public:
        Div(const TokenList& tokenList) : IInstructionWith2InputOperandsAnd1OutputOperand(tokenList)
        {
        }

        void apply(CPU& cpu) override
        {
            if (src2.evaluate(cpu) == 0)
                throw DivisionByZeroException();

            dest.affect(cpu, src1.evaluate(cpu) / src2.evaluate(cpu));
        }
    };

    class Je : public IInstructionWith3InputOperands
    {
    public:
        Je(const TokenList& tokenList) : IInstructionWith3InputOperands(tokenList)
        {
        }

        void apply(CPU& cpu) override
        {
            if (src1.evaluate(cpu) == src2.evaluate(cpu))
            {
                OperandAccessor ip("r15");
                ip.affect(cpu, src3.evaluate(cpu) - 1);
            }
        }
    };

    class Jne : public IInstructionWith3InputOperands
    {
    public:
        Jne(const TokenList& tokenList) : IInstructionWith3InputOperands(tokenList)
        {
        }

        void apply(CPU& cpu) override
        {
            if (src1.evaluate(cpu) != src2.evaluate(cpu))
            {
                OperandAccessor ip("r15");
                ip.affect(cpu, src3.evaluate(cpu) - 1);
            }
        }
    };

    class Disp : public IInstructionWith3InputOperands
    {
    public:
        Disp(const TokenList& tokenList) : IInstructionWith3InputOperands(tokenList)
        {
        }

        void apply(CPU& cpu) override
        {
            cpu.getComputer().screen.setChar(src1.evaluate(cpu), src2.evaluate(cpu), src3.evaluate(cpu));
        }
    };

    class Dispn : public IInstructionWith3InputOperands
    {
    public:
        Dispn(const TokenList& tokenList) : IInstructionWith3InputOperands(tokenList)
        {
        }

        void apply(CPU& cpu) override
        {
            unsigned char valueToDisplay = src3.evaluate(cpu);
            unsigned char cent = valueToDisplay / 100;
            unsigned char dizaine = (valueToDisplay - cent * 100) / 10;
            unsigned char unity = valueToDisplay % 10;

            cpu.getComputer().screen.setChar(src1.evaluate(cpu), src2.evaluate(cpu) + 0, '0' + cent);
            cpu.getComputer().screen.setChar(src1.evaluate(cpu), src2.evaluate(cpu) + 1, '0' + dizaine);
            cpu.getComputer().screen.setChar(src1.evaluate(cpu), src2.evaluate(cpu) + 2, '0' + unity);
        }
    };

    InstructionFactoryOldSchoolFashioned& getInstructionFactory()
    {
        static InstructionFactoryOldSchoolFashioned theFactory;
        return theFactory;
    }

    InstructionFactoryOldSchoolFashioned::InstructionFactoryOldSchoolFashioned()
    {
#define REGISTER_INSTRUCTION(mnemonic, InstructionClass) \
        class InstructionClass##InstructionCreationRecipe : public IInstructionCreationRecipe\
        {\
            IInstruction* createInstruction(const TokenList& tokenList) override { return new InstructionClass(tokenList); }\
        };\
        registerType(mnemonic, new InstructionClass##InstructionCreationRecipe);

        REGISTER_INSTRUCTION("MOV", Mov);

        REGISTER_INSTRUCTION("ADD", Add);
        REGISTER_INSTRUCTION("SUB", Sub);
        REGISTER_INSTRUCTION("MUL", Mul);
        REGISTER_INSTRUCTION("DIV", Div);
    }

    InstructionFactoryActualFashioned& getInstructionFactoryNewStyle()
    {
        static InstructionFactoryActualFashioned theFactory;
        return theFactory;
    }

    InstructionFactoryActualFashioned::InstructionFactoryActualFashioned()
    {
        registerType("MOV", [](const TokenList& tokenList) { return new Mov(tokenList); });
        registerType("ADD", [](const TokenList& tokenList) { return new Add(tokenList); });
        registerType("SUB", [](const TokenList& tokenList) { return new Sub(tokenList); });
        registerType("MUL", [](const TokenList& tokenList) { return new Mul(tokenList); });
        registerType("DIV", [](const TokenList& tokenList) { return new Div(tokenList); });
        registerType("JE", [](const TokenList& tokenList) { return new Je(tokenList); });
        registerType("JNE", [](const TokenList& tokenList) { return new Jne(tokenList); });
        registerType("DISP", [](const TokenList& tokenList) { return new Disp(tokenList); });
        registerType("DISPN", [](const TokenList& tokenList) { return new Dispn(tokenList); });
    }


}
