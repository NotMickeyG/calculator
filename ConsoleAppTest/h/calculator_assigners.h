#pragma once

#include <regex>

#include "calculator_nodes.h"

// calculator specific CommandAssigners for the CommandNodes in command_nodes.h
namespace calculator
{
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