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
        start_('('),
        end_(')')
    {
        // TODO for the most part BracketChecker is handling the subTree stack stack so maybe it should be a member of BracketChecker?
        assigner_.subTrees_.push_back(std::vector<std::unique_ptr<parse::CommandNode>>());
    }

    BracketChecker::~BracketChecker() {}

    bool BracketChecker::check(std::string& inputString)
    {
        size_t index = 0;

        while (index < inputString.length())
        {
            startResults_.clear();
            endResults_.clear();
            int bracketCount = 0;

            for (index = 0; index < inputString.length(); index++)
            {
                if (inputString[index] == start_ &&
                    bracketCount++ == 0)
                {
                    startResults_.push_back(index);
                }

                if (inputString[index] == end_ &&
                    --bracketCount == 0)
                {
                    endResults_.push_back(index);
                }

                // if we go negative there was a missed opening bracket so put one in and restart loop
                if (bracketCount < 0)
                {
                    inputString.insert(inputString.begin(), '(');
                    break;
                }
            }
        }

        // similarly if we're missing the closing bracket for this layer's outer brackets, add it on
        // this can be done on each layer so it doesn't need to restart the loop
        if (startResults_.size() > endResults_.size())
        {
            endResults_.push_back(index);
            inputString.push_back(')');
        }

        // true if no subtrees yet given to subTree layer && if there are brackets
        return
            !startResults_.empty() &&
            assigner_.subTrees_.back().empty();
    }

    void BracketChecker::assign(
        parse::Parser* parser,
        std::string inputString,
        std::unique_ptr<parse::CommandNode>& commandNode)
    {
        // because the same BracketsChecker is used for all parses,
        // the results need to be held locally whilst parsing each inner bracket string
        std::vector<size_t> startResults = startResults_;
        std::vector<size_t> endResults = endResults_;

        std::string outer = inputString;

        // loop through backwards to work with string erase() and also means subtrees can be a 2d vector rather than a vector of queues
        while (!startResults.empty())
        {
            size_t startResult = startResults.back();
            size_t endResult = endResults.back();

            std::string inner = inputString.substr(startResult + 1, endResult - startResult - 1);

            //here we add a layer to subtree stack, parse, pop layer then add the parsed pointer to subtree stack layer
            assigner_.subTrees_.push_back(std::vector<std::unique_ptr<parse::CommandNode>>());
            std::unique_ptr<parse::CommandNode> subTree = parser->parse(inner);
            assigner_.subTrees_.pop_back();
            assigner_.subTrees_.back().push_back(std::move(subTree));

            outer.erase(startResult + 1, endResult - startResult - 1);

            startResults.pop_back();
            endResults.pop_back();
        }

        commandNode = parser->parse(outer);
    }




    BracketAssigner::BracketAssigner() : check_("^\\(\\)$") {}

    BracketAssigner::~BracketAssigner() {}

    bool BracketAssigner::check(std::string& inputString)
    {
        // Remove whitespace
        inputString.erase(std::remove(inputString.begin(), inputString.end(), ' '), inputString.end());

        // true if there is a subtree to assign && if the string matches "()"
        return
            !subTrees_.back().empty() &&
            std::regex_match(inputString, check_);
    }

    void BracketAssigner::assign(
        parse::Parser* parser,
        std::string inputString,
        std::unique_ptr<parse::CommandNode>& commandNode)
    {
        commandNode = std::unique_ptr<parse::CommandNode>(
            new Bracket(std::move(subTrees_.back().back())));

        subTrees_.back().pop_back();
    }
}
