#include "Exception.h"

namespace Coal
{
    IMPLEMENT_NEW_EXCEPTION_CLASS(UnknownInstructionException, "Trying to process an unknown instruction.")
    IMPLEMENT_NEW_EXCEPTION_CLASS(InvalidNumberOfOperandInstruction, "Invalid number of operand.")
    IMPLEMENT_NEW_EXCEPTION_CLASS(InvalidOperandException, "Operand is invalid.")
    IMPLEMENT_NEW_EXCEPTION_CLASS(DivisionByZeroException, "Division by zero.")
    IMPLEMENT_NEW_EXCEPTION_CLASS(InstructionAlreadyRegistered, "Instruction has already been registered.")
}
