#include <iostream>
#include <vector>

#include "h/parse.h"

namespace parse
{
    ParseFail::ParseFail(Parser& parser)
    {
        parser.state_ = error;
    }
    ParseFail::~ParseFail() {}
    float ParseFail::execute()
    {
        return 0;
    }


    Parser::Parser(std::vector<std::unique_ptr<NodeAssigner>> assigners) :
        assigners_(std::move(assigners)),
        state_(run)
    {}
    Parser::~Parser() {}
    std::unique_ptr<CommandNode> Parser::parse(std::string inputString)
    {
        std::unique_ptr<CommandNode> commandNode;

        for (std::unique_ptr<NodeAssigner>& assigner : assigners_)
        {
            if (assigner->check(inputString))
            {
                assigner->assign(this, inputString, commandNode);
                return commandNode;
            }
        }

        

        // if no assigner can be matched, the input has failed to match the parser
        commandNode = std::unique_ptr<CommandNode>(new ParseFail(*this));
        return commandNode;
    }
}