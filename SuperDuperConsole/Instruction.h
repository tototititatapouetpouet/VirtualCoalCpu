#pragma once

#include "Exception.h"
#include "OperandAccessor.h"

#include <vector>
#include <string>
#include <map>
#include <functional>

namespace Coal
{
    using Token = std::string;
    using TokenList = std::vector<Token>;

    class CPU;

    class IInstruction
    {
    public:
        virtual ~IInstruction()
        {

        }

        IInstruction(const TokenList& tokenList, int nbOperand)
        {
            if (tokenList.size() != nbOperand)
                throw InvalidNumberOfOperandInstruction();
        }

        virtual void apply(CPU& cpu) = 0;
    };

    class IInstructionCreationRecipe
    {
    public:
        virtual IInstruction* createInstruction(const TokenList& tokenList) = 0;
        virtual ~IInstructionCreationRecipe() = default;
    };

    class InstructionFactoryOldSchoolFashioned
    {
    public:
        InstructionFactoryOldSchoolFashioned();

        IInstruction* create(const InstructionType& type, const TokenList& tokenList)
        {
            auto it = m_recipes.find(type);
            if (it == m_recipes.end())
                throw UnknownInstructionException();

            IInstructionCreationRecipe* recipe = it->second;
            return recipe->createInstruction(tokenList);
        }

        void registerType(const InstructionType& type, IInstructionCreationRecipe* recipe)
        {
            auto it = m_recipes.find(type);
            if (it != m_recipes.end())
                throw InstructionAlreadyRegistered();

            m_recipes[type] = recipe;
        }

    private:
        std::map<InstructionType, IInstructionCreationRecipe*> m_recipes;
    };

    InstructionFactoryOldSchoolFashioned& getInstructionFactory();

    class InstructionFactoryActualFashioned
    {
    public:
        InstructionFactoryActualFashioned();

        using InstructionCreationRecipe = std::function<IInstruction* (const TokenList& tokenList)>;

        IInstruction* create(const InstructionType& type, const TokenList& tokenList)
        {
            auto it = m_recipes.find(type);
            if (it == m_recipes.end())
                throw UnknownInstructionException();

            InstructionCreationRecipe recipe = it->second;
            return recipe(tokenList);
        }

        void registerType(const InstructionType& type, InstructionCreationRecipe recipe)
        {
            auto it = m_recipes.find(type);
            if (it != m_recipes.end())
                throw InstructionAlreadyRegistered();

            m_recipes[type] = recipe;
        }

    private:
        std::map<InstructionType, InstructionCreationRecipe> m_recipes;
    };

    InstructionFactoryActualFashioned& getInstructionFactoryNewStyle();

    class IInstructionWith2InputOperandsAnd1OutputOperand : public IInstruction
    {
    public:
        IInstructionWith2InputOperandsAnd1OutputOperand(const TokenList& tokenList) : IInstruction(tokenList, 4), src1(tokenList[1]), src2(tokenList[2]), dest(tokenList[3])
        {
        }

        OperandAccessor src1;
        OperandAccessor src2;
        OperandAccessor dest;
    };

    class IInstructionWith3InputOperands : public IInstruction
    {
    public:
        IInstructionWith3InputOperands(const TokenList& tokenList) : IInstruction(tokenList, 4), src1(tokenList[1]), src2(tokenList[2]), src3(tokenList[3])
        {
        }

        OperandAccessor src1;
        OperandAccessor src2;
        OperandAccessor src3;
    };


    
}
