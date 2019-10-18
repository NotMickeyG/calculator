#include <iostream>

#include "h/calculator_assigners.h"


namespace calculator
{
    // ValAssigner initialised with a fixed regex that matches number strings
    ValAssigner::ValAssigner() : check_("^[-|+]?[0-9]+(\\.[0-9]+)?$") {}

    ValAssigner::~ValAssigner() {}

    // all whitespace is removed before checking against the regex
    // note: ALL whitespace is removed, ie "3 43 1" passes the check and gets converted to 3431
    bool ValAssigner::check(std::string& inputString)
    {
        // remove whitespace
        inputString.erase(std::remove(inputString.begin(), inputString.end(), ' '), inputString.end());
        return std::regex_match(inputString, check_);
    }

    void ValAssigner::assign(
        parse::Parser* parser,
        std::string inputString,
        std::unique_ptr<parse::CommandNode>& commandNode)
    {
        commandNode = std::unique_ptr<parse::CommandNode>(
            new Val(std::stof(inputString)));
    }




    // custom check passed in for each type of CommandNode to parse
    // check should generally be in the format " op " unless you know what you're doing
    template <class OP>
    OpAssigner<OP>::OpAssigner(std::string check) : check_(check) {}

    template <class OP>
    OpAssigner<OP>::~OpAssigner() {}

    template <class OP>
    bool OpAssigner<OP>::check(std::string& inputString)
    {
        result_ = inputString.find(check_);
        return result_ != std::string::npos;
    }

    template <class OP>
    void OpAssigner<OP>::assign(
        parse::Parser* parser,
        std::string inputString,
        std::unique_ptr<parse::CommandNode>& commandNode)
    {
        // inputString is split on either side of the check
        std::string split1 = inputString.substr(0, result_);
        std::string split2 = inputString.substr(result_ + check_.length());

        // the two splits are parsed then added to the templated CommandNode
        commandNode = std::unique_ptr<parse::CommandNode>(
            new OP(parser->parse(split1), parser->parse(split2)));
    }


    // if you have a new CommandNode to assign with OpAssigner, it must be declared here
    // the CommandNode must construct with two unique_ptrs to CommandNodes, other than that you can probably mess around
    // main thing to take into account is that the two pointers come from the split strings on each side of the check
    template class OpAssigner<Add>;
    template class OpAssigner<Sub>;
    template class OpAssigner<Mul>;
    template class OpAssigner<Div>;
    template class OpAssigner<Mod>;
    template class OpAssigner<Pow>;




    BracketChecker::BracketChecker(BracketAssigner& assigner) :
        assigner_(assigner),
        start_("("),
        end_(")")
    {}

    BracketChecker::~BracketChecker() {}

    bool BracketChecker::check(std::string& inputString)
    {
        startResult_ = inputString.find(start_);
        endResult_ = inputString.find_last_of(end_);

        // true if no subtree yet given to BracketAssigner && if there is an opening and closing bracket
        return
            !assigner_.subTree_ &&
            startResult_ != std::string::npos &&
            endResult_ != std::string::npos;
    }

    void BracketChecker::assign(
        parse::Parser* parser,
        std::string inputString,
        std::unique_ptr<parse::CommandNode>& commandNode)
    {
        std::string inner = inputString.substr(startResult_ + 1, endResult_ - startResult_ - 1);
        std::string outer = inputString;
        outer.erase(startResult_ + 1, endResult_ - startResult_ - 1);

        std::cout << "\ninner: " << inner << std::endl;
        std::cout << "outer: " << outer << std::endl;

        assigner_.subTree_ = parser->parse(inner);
        commandNode = parser->parse(outer);

        //commandNode = std::unique_ptr<parse::CommandNode>(
        //    new Val(0));
    }




    BracketAssigner::BracketAssigner() : check_("^\\(\\)$") {}

    BracketAssigner::~BracketAssigner() {}

    bool BracketAssigner::check(std::string& inputString)
    {
        // Remove whitespace
        inputString.erase(std::remove(inputString.begin(), inputString.end(), ' '), inputString.end());

        // true if there is a subtree to assign && if the string matches "()"
        return
            subTree_ &&
            std::regex_match(inputString, check_);
    }

    void BracketAssigner::assign(
        parse::Parser* parser,
        std::string inputString,
        std::unique_ptr<parse::CommandNode>& commandNode)
    {
        commandNode = std::unique_ptr<parse::CommandNode>(
            new Bracket(std::move(subTree_)));
    }
}
