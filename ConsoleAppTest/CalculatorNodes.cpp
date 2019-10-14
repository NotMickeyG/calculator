#include "h/calculator_nodes.h"

namespace calculator
{
    Val::Val(float value) : val_(value) {}
    Val::~Val() {}
    float Val::execute()
    {
        return val_;
    }


    Add::Add(std::unique_ptr<CommandNode> add1, std::unique_ptr<CommandNode> add2) :
        add1_(std::move(add1)),
        add2_(std::move(add2))
    {}
    Add::~Add() {}
    float Add::execute()
    {
        return add1_->execute() + add2_->execute();
    }
}