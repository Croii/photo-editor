#include "CommandManager.h"

void CommandManager::executeCommand(std::unique_ptr<ICommand> command)
{
	command->execute();
	m_undoStack.push_back(std::move(command));
	m_redoStack.clear();
}

void CommandManager::undo()
{
	if (m_undoStack.empty())
		return;
	auto command = std::move(m_undoStack.back());
	m_undoStack.pop_back();

	command->undo();
	m_redoStack.push_back(std::move(command));
	command = nullptr;
}

#include <iostream>
void CommandManager::redo()
{
	if (m_redoStack.empty())
		return;

	auto command = std::move(m_redoStack.back());
	m_redoStack.pop_back();
	command->execute();
	m_undoStack.push_back(std::move(command));
	command = nullptr;
	std::cout << "executed redo";
}
