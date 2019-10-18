#pragma once

#include <regex>

#include "calculator_nodes.h"

// pass a vector or similar collection of these into the parser
// the order pushed back to the vector becomes the order of operations with the last added being the most binding (don't forget Val)
namespace calculator
{
    // checks and assigns node for numerical value
    // numbers with spaces in between will be converted to a single number (see CalculatorAssigners.cpp for details)
    class ValAssigner : public parse::NodeAssigner
    {
    public:
        ValAssigner();
        ~ValAssigner();
        bool check(std::string& inputString) override;
        void assign(
            parse::Parser* parser,
            std::string inputString,
            std::unique_ptr<parse::CommandNode>& commandNode) override;
    private:
        std::regex check_;
    };


    // generic checker & assigner for "x op y" operations eg "5 + 1"
    // currently works with +, -, * and /
    // see implementation in CalculatorAssigners.cpp if you want to add more similar operators
    template <class OP>
    class OpAssigner : public parse::NodeAssigner
    {
    public:
        OpAssigner(std::string check);
        ~OpAssigner();
        bool check(std::string& inputString) override;
        void assign(
            parse::Parser* parser,
            std::string inputString,
            std::unique_ptr<parse::CommandNode>& commandNode) override;
    private:
        std::string check_;
        size_t result_;
    };
}