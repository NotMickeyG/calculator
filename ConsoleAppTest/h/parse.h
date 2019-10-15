#pragma once

#include <memory>
#include <string>
#include <vector>

namespace parse
{
    class CommandNode;
    class Parser;
    class NodeAssigner;
    class ParseFail;


    // ParserState values need to be exposed to code using the parser so it get's defined here
    enum ParserState { run, error, exit };


    // a parse tree is made up of nodes
    // CommandNodes specifically have a built in execution function that can be called through the tree once parsed
    class CommandNode
    {
    public:
        CommandNode() {}
        ~CommandNode() {}
        virtual float execute() = 0;
    };


    // parser is a container for NodeAssigners
    // parse() uses the NodeAssigners to return a tree of CommandNodes
    class Parser
    {
    public:
        Parser(std::vector<std::unique_ptr<NodeAssigner>> assigners);
        ~Parser();
        std::unique_ptr<CommandNode> parse(std::string inputString);
        ParserState state_;
    private:
        // vector needs to know the size of the objects it holds
        // because NodeAssigners are so varied by design, the vector can only take references for NodeAssigners
        std::vector<std::unique_ptr<NodeAssigner>> assigners_;
    };


    // NodeAssigners are used to check and assign nodes
    // this allows for varied syntax checks on the input and varied types of assignment on the output
    class NodeAssigner
    {
    public:
        NodeAssigner() {}
        ~NodeAssigner() {}
        virtual bool check(std::string& inputString) = 0;
        virtual void assign(
            Parser* parser,
            std::string inputString,
            std::unique_ptr<CommandNode>& commandNode) = 0;
    };


    class ParseFail : public CommandNode
    {
    public:
        ParseFail();
        ~ParseFail();
        float execute();
    };
}
