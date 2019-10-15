#pragma once

#include <regex>

#include "calculator_nodes.h"

// pass a vector or similar collection of these into the parser
// the order pushed back to the vector becomes the order of operations with the last added being the most binding (don't forget Val)
namespace calculator
{
    // checks and assigns node for numerical value
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


    // checks and assigns node for addition
    class AddAssigner : public parse::NodeAssigner
    {
    public:
        AddAssigner();
        ~AddAssigner();
        bool check(std::string& inputString) override;
        void assign(
            parse::Parser* parser,
            std::string inputString,
            std::unique_ptr<parse::CommandNode>& commandNode) override;
    private:
        std::string check_;
        size_t result_;
    };


    // checks and assigns node for subtraction
    class SubAssigner : public parse::NodeAssigner
    {
    public:
        SubAssigner();
        ~SubAssigner();
        bool check(std::string& inputString) override;
        void assign(
            parse::Parser* parser,
            std::string inputString,
            std::unique_ptr<parse::CommandNode>& commandNode) override;
    private:
        std::string check_;
        size_t result_;
    };


    // checks and assigns node for multiplication
    class MulAssigner : public parse::NodeAssigner
    {
    public:
        MulAssigner();
        ~MulAssigner();
        bool check(std::string& inputString) override;
        void assign(
            parse::Parser* parser,
            std::string inputString,
            std::unique_ptr<parse::CommandNode>& commandNode) override;
    private:
        std::string check_;
        size_t result_;
    };


    // checks and assigns node for division
    class DivAssigner : public parse::NodeAssigner
    {
    public:
        DivAssigner();
        ~DivAssigner();
        bool check(std::string& inputString) override;
        void assign(
            parse::Parser* parser,
            std::string inputString,
            std::unique_ptr<parse::CommandNode>& commandNode) override;
    private:
        std::string check_;
        size_t result_;
    };
}