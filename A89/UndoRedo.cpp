#include "UndoRedo.h"
#include <iostream>

AddCommand::AddCommand(Repository* repository, Movie event) {
	this->repository = repository;
	this->movies.push_back(event);
}

void AddCommand::redo()
{
	Movie movie_to_add = this->movies[0];
	try {
		this->repository->addMovie(movie_to_add);
	}
	catch (FileException& e) {
		std::cout << e.what() << '\n';
	}

}

void AddCommand::undo()
{
	Movie movie_to_remove = this->movies[0];
	try {
		int index = this->repository->getMoviePosition(movie_to_remove);
		this->repository->removeMovie(index);
	}
	catch (FileException& e) {
		std::cout << e.what() << '\n';
	}
}

RemoveCommand::RemoveCommand(Repository* repository, Movie movie) {
	this->repository = repository;
	this->movies.push_back(movie);
}

void RemoveCommand::redo()
{
	Movie movie_to_remove = this->movies[0];
	try {
		int index = this->repository->getMoviePosition(movie_to_remove);
		this->repository->removeMovie(index);
	}
	catch (FileException& e) {
		std::cout << e.what() << '\n';
	}
}

void RemoveCommand::undo()
{
	Movie movie_to_add = this->movies[0];
	try {
		this->repository->addMovie(movie_to_add);
	}
	catch (FileException& e) {
		std::cout << e.what() << '\n';
	}
}

UpdateCommand::UpdateCommand(Repository* repository, Movie movie_old, Movie movie_new) {
	this->repository = repository;
	this->movies.push_back(movie_old);
	this->movies.push_back(movie_new);
}

void UpdateCommand::redo()
{
	Movie movie_to_update = this->movies[1];
	try {
		int index = this->repository->getMoviePosition(this->movies[0]);
		this->repository->updateMovie(index, movie_to_update);
	}
	catch (FileException& e) {
		std::cout << e.what() << '\n';
	}
}

void UpdateCommand::undo()
{
	Movie movie_to_update = this->movies[0];
	try {
		int index = this->repository->getMoviePosition(this->movies[1]);
		this->repository->updateMovie(index, movie_to_update);
	}
	catch (FileException& e) {
		std::cout << e.what() << '\n';
	}
}

void UndoRedo::addOperation(Command* command)
{
	this->undoStack.push(command);
}

void UndoRedo::executeUndo()
{
	if (this->undoStack.empty())
		throw FileException("No more undos!");
	Command* command = this->undoStack.top();
	command->undo();
	this->redoStack.push(command);
	this->undoStack.pop();
}

void UndoRedo::executeRedo()
{
	if (this->redoStack.empty())
		throw FileException("No more redos!");
	Command* command = this->redoStack.top();
	this->undoStack.push(command);
	command->redo();
	this->redoStack.pop();
}

Command::Command() {
	this->repository = nullptr;
}
