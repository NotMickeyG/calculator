#pragma once

#include <regex>
#include <queue>

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
        char start_;
        char end_;
        std::vector<size_t> startResults_;
        std::vector<size_t> endResults_;
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

        //std::vector<std::queue<std::unique_ptr<parse::CommandNode>>> subTrees_;
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

    

    // bigger issue than originally thought, backets rely on being done in order currently because of the passing forward of the tree node
    // can I pass forward to a stack? but then how do I check?
    // can I pass forward to a dictionary or hash table? yes and that would allow for look ups

    // actually the dependencies are worked out linearly left to right and they might be calculated left to right as well
    // nah but stacked dependencies wouldn't do well there eg

    // (1 + 2) * ((3 + 4) / (5 + 6))
    // leads to
    // () * ((3 + 4) / (5 + 6))
    // store parsed (1 + 2) in stack - linear so far
    // () * ()
    // parse ((3 + 4) / (5 + 6)) but (1 + 2) is still in stack!!! Bad


    // bad because if something like this is input
    //(1 + 2) * ((3 + 4) / ())
    // we end up assigning (1 + 2) to () when we should be passing () forward as new brackets

    // This issue is probably why input generally goes through a parser one char at a time using a formal language
    // that way, every node can be accounted for without relying on formatting the string which has a risks like the above one

    // I don't want to restructure though because that requires a whole program rewrite so I'll either
    // ban certain characters like {} and then use as a wrapper, eg "{1} * {2}"
    // use characters that can't be input via terminal, eg "\n1\0 * \n2\0"

    // would there be any other way to do this w/o writing to string?
    // I could use a layered stack
    // do each time I parse inner I push a new stack layer on top
    // would this work?

    // (1 + 2) * ((3 + 4) / (5 + 6))
    // leads to
    // () * ((3 + 4) / (5 + 6))
    // store parsed (1 + 2) in first layer of stack - linear so far
    // () * ()
    // parse ((3 + 4) / (5 + 6)) also in first layer of stack, but another layer is pushed during the parsing itself
    
    // in other words before and after parse(inner), push and pop a new stack
    // that does require adjacent brackets being handled at the same time though

    // ug this feels way too complex but I can't see any way of nicely doing it whilst still handling strings like I am now
    // how the hell does the javascript interpreter do this kind of shit lol
    // 

    // incrementalise?
    // bracket result queue
    // print strings for each inner result & outer result

    // then parse inners
    // then parse outers
}