#pragma once
#include "ICommand.h"
#include <memory>
#include <vector>

class CommandManger
{
public:
	void executeCommand(std::unique_ptr<ICommand> command);
	void undo();
	void redo();

private:
	std::vector<std::unique_ptr<ICommand>> m_undoStack;
	std::vector<std::unique_ptr<ICommand>> m_redoStack;

};

