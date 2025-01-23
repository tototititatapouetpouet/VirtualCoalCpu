#pragma once

#include <stdexcept>

namespace Coal
{
#define DECLARE_NEW_EXCEPTION_CLASS(classname) \
class classname : public std::runtime_error\
{\
public:\
    classname();\
};

#define IMPLEMENT_NEW_EXCEPTION_CLASS(classname, message) \
classname::classname()\
    : std::runtime_error(message)\
{\
}

    DECLARE_NEW_EXCEPTION_CLASS(UnknownInstructionException);
    DECLARE_NEW_EXCEPTION_CLASS(InstructionAlreadyRegistered);
    DECLARE_NEW_EXCEPTION_CLASS(InvalidNumberOfOperandInstruction);
    DECLARE_NEW_EXCEPTION_CLASS(InvalidOperandException);
    DECLARE_NEW_EXCEPTION_CLASS(DivisionByZeroException);
}
