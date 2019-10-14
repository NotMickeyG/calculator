#pragma once

#include "parse.h"

// calculator specific CommandNodes to build parse tree with
namespace calculator
{
    // Val is an assignment value for recognised single numbers
    class Val : public parse::CommandNode
    {
    public:
        Val(float value);
        ~Val();
        float execute() override;
    private:
        float val_;
    };


    // Add is an operator value for recognised addition
    class Add : public parse::CommandNode
    {
    public:
        Add(std::unique_ptr<parse::CommandNode> add1, std::unique_ptr<parse::CommandNode> add2);
        ~Add();
        float execute() override;
    private:
        std::unique_ptr<parse::CommandNode> add1_;
        std::unique_ptr<parse::CommandNode> add2_;
    };
}
