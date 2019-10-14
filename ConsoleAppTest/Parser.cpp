#include <iostream>

#include "h/parse.h"
#include "h/calculator_assigners.h"     // TODO remove this after removing the calculator specific dependencies below

namespace parse
{
    Parser::Parser() {}
    Parser::~Parser() {}
    std::unique_ptr<CommandNode> Parser::parse(std::string inputString)
    {
        std::unique_ptr<CommandNode> commandNode;
        // TODO remove these dependencies
        std::unique_ptr<NodeAssigner> addCheck(new calculator::AddAssigner);
        std::unique_ptr<NodeAssigner> valCheck(new calculator::ValAssigner);

        if (addCheck->check(inputString))
        {
            addCheck->assign(this, inputString, commandNode);
            return commandNode;
        }

        if (valCheck->check(inputString))
        {
            valCheck->assign(this, inputString, commandNode);
            return commandNode;
        }


        // TODO make this dependency more general and put it in parser
        // maybe an Unparsable : public CommandNode
        std::cout << "ERROR!!" << std::endl;
        commandNode = std::unique_ptr<CommandNode>(
            new calculator::Val(0));
        return commandNode;
    }
}