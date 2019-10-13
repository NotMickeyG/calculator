#pragma once
#include <iostream>

class InputCommand
{
public:
	InputCommand();
	virtual ~InputCommand();
	//virtual bool identify(std::string identifier) = 0;
	virtual void execute() = 0;
};







// so inputhandler has [command, command, command, etc]
// inputhandler.processLine() {getline;
// if command.identify(line) {command.process}
//}
// nah cause then we have all commands for every line check hmm

// really we want a seperate commandCheck class which returns it's command with correct params


// want to use command pattern for all InputCommands
// problem: How to map Input to InputCommands? Just do it on loop in InputHandler? Could work
// so literally command class w/ commands
// and InputHandler delegates

// problem: unknown number of arguments for operations (ie 3+2 has 2 arguments, 5 has one argument, help has no arguments)
// 3 gets passed as 3 w/ one argument
// 2 then added as next argument
// help just get's passed 0 or summat

// so how do we do +2?
// pass to execute an initial value and a calculation value

// problem: How to save past calculations?