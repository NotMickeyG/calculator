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
}
