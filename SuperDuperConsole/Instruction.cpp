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
}
