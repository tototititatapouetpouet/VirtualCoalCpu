#include "Instruction.h"

namespace Coal
{

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
    }


}
