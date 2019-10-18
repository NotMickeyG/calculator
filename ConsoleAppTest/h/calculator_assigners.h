#pragma once

#include <regex>

#include "calculator_nodes.h"

// pass a vector or similar collection of these into the parser
// the order pushed back to the vector becomes the order of operations with the last added being the most binding (don't forget Val)
namespace calculator
{
    class ValAssigner;
    class BracketChecker;
    class BracketAssigner;


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


    class BracketChecker : public parse::NodeAssigner
    {
    public:
        BracketChecker(BracketAssigner& assigner);
        ~BracketChecker();
        bool check(std::string& inputString) override;
        void assign(
            parse::Parser* parser,
            std::string inputString,
            std::unique_ptr<parse::CommandNode>& commandNode) override;
    private:
        BracketAssigner& assigner_;
        std::string start_;
        std::string end_;
        size_t startResult_;
        size_t endResult_;
    };


    class BracketAssigner : public parse::NodeAssigner
    {
    public:
        BracketAssigner();
        ~BracketAssigner();
        bool check(std::string& inputString) override;
        void assign(
            parse::Parser* parser,
            std::string inputString,
            std::unique_ptr<parse::CommandNode>& commandNode) override;

        std::unique_ptr<parse::CommandNode> subTree_;
    private:
        std::regex check_;
    };

    // the idea is "//dunno (//whatever ) //more stuff" is caught by bracket checker
    // string is split into "//dunno () //more stuff" and "//whatever"
    // parse "//whatever" to get unique pointer
    // pass pointer to bracket assigner
    // parse "//dunno () //more stuff"
    // "()" caught like a Val but by bracket assigner which currently contains the unique pointer
    // bracket assigner returns that unique pointer in a Bracket CommandNode
    // bracket checker returns the parsed "//dunno () //more stuff"

    // this is a great start but doesn't account for adjacent brackets currently, ie "() + ()"
    // will probably need to
}