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


    // Bracket is a placeholder value that parses it's contents as a subtree
    // it then returns the value calculated by that subtree
    class Bracket : public parse::CommandNode
    {
    public:
        Bracket(std::unique_ptr<parse::CommandNode> subTree);
        ~Bracket();
        float execute() override;
    private:
        std::unique_ptr<parse::CommandNode> subTree_;
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


    // Sub is an operator value for recognised subtraction
    class Sub : public parse::CommandNode
    {
    public:
        Sub(std::unique_ptr<parse::CommandNode> sub1, std::unique_ptr<parse::CommandNode> sub2);
        ~Sub();
        float execute() override;
    private:
        std::unique_ptr<parse::CommandNode> sub1_;
        std::unique_ptr<parse::CommandNode> sub2_;
    };


    // Mul is an operator value for recognised multiplication
    class Mul : public parse::CommandNode
    {
    public:
        Mul(std::unique_ptr<parse::CommandNode> mul1, std::unique_ptr<parse::CommandNode> mul2);
        ~Mul();
        float execute() override;
    private:
        std::unique_ptr<parse::CommandNode> mul1_;
        std::unique_ptr<parse::CommandNode> mul2_;
    };


    // Div is an operator value for recognised division
    class Div : public parse::CommandNode
    {
    public:
        Div(std::unique_ptr<parse::CommandNode> div1, std::unique_ptr<parse::CommandNode> div2);
        ~Div();
        float execute() override;
    private:
        std::unique_ptr<parse::CommandNode> div1_;
        std::unique_ptr<parse::CommandNode> div2_;
    };


    // Mod is an operator value for recognised modulo
    class Mod : public parse::CommandNode
    {
    public:
        Mod(std::unique_ptr<parse::CommandNode> split1, std::unique_ptr<parse::CommandNode> split2);
        ~Mod();
        float execute() override;
    private:
        std::unique_ptr<parse::CommandNode> split1_;
        std::unique_ptr<parse::CommandNode> split2_;
    };


    // Pow is an operator value for recognised power
    class Pow : public parse::CommandNode
    {
    public:
        Pow(std::unique_ptr<parse::CommandNode> split1, std::unique_ptr<parse::CommandNode> split2);
        ~Pow();
        float execute() override;
    private:
        std::unique_ptr<parse::CommandNode> split1_;
        std::unique_ptr<parse::CommandNode> split2_;
    };
}
