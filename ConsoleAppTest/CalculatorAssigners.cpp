#include <iostream>

#include "h/calculator_assigners.h"


namespace calculator
{
    ValAssigner::ValAssigner() : check_("^[-|+]?[0-9]+(\\.[0-9]+)?$") {}
    ValAssigner::~ValAssigner() {}
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


    AddAssigner::AddAssigner() : check_(" + ") {}
    AddAssigner::~AddAssigner() {}
    bool AddAssigner::check(std::string& inputString)
    {
        result_ = inputString.find(check_);
        return result_ != std::string::npos;
    }
    void AddAssigner::assign(
        parse::Parser* parser,
        std::string inputString,
        std::unique_ptr<parse::CommandNode>& commandNode)
    {
        std::string split1 = inputString.substr(0, result_);
        std::string split2 = inputString.substr(result_ + check_.length());

        commandNode = std::unique_ptr<parse::CommandNode>(
            new Add(parser->parse(split1), parser->parse(split2)));
    }
}
