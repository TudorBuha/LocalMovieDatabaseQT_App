#pragma once
#include "Movie.h"
#include "Repository.h"
#include "Exception.h"
#include <stack>

class Command
{
protected:
	std::vector<Movie> movies;
	Repository* repository;
public:
	Command();
	virtual void redo() = 0;
	virtual void undo() = 0;
};

class AddCommand : public Command {
public:
	AddCommand(Repository* repository, Movie movie);
	void redo() override;
	void undo() override;
};

class RemoveCommand : public Command {
public:
	RemoveCommand(Repository* repository, Movie movie);
	void redo() override;
	void undo() override;
};

class UpdateCommand : public Command {
public:
	UpdateCommand(Repository* repository, Movie movie_old, Movie movie_new);
	void redo() override;
	void undo() override;
};

class UndoRedo {
private:
	std::stack<Command*> undoStack;
	std::stack<Command*> redoStack;
public:
	UndoRedo() = default;
	void addOperation(Command* command);
	void executeUndo();
	void executeRedo();

};