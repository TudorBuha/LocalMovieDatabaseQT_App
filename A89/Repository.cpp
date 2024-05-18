#include "Repository.h"
#include <algorithm>
#include <fstream>
#include "Utils.h"
#include "Exception.h"

Repository::Repository(std::string filename, std::vector<Movie> initialMovies) :
	allMovies{ initialMovies },
	filename{ filename }
{
	this->readFromFile();
}

vector<Movie> Repository::getAllMovies()
{
	return this->allMovies;
}



void Repository::addMovie(Movie movieToAdd)
{
	auto iterator = std::find(this->allMovies.begin(), this->allMovies.end(), movieToAdd);
	if (iterator != this->allMovies.end())
		throw std::exception("Movie already exists!");
	this->allMovies.push_back(movieToAdd);
	this->writeToFile();
}

void Repository::removeMovie(int indexOfMovieToRemove)
{
	if (indexOfMovieToRemove < 0 || indexOfMovieToRemove >= this->allMovies.size())
		throw std::exception("Movie doesn't exists!");
	this->allMovies.erase(this->allMovies.begin() + indexOfMovieToRemove);
	this->writeToFile();
}

void Repository::updateMovie(int indexOfMovieToUpdate, Movie updatedMovie)
{
	if (indexOfMovieToUpdate < 0 || indexOfMovieToUpdate > this->allMovies.size())
		throw std::exception("Movie doesn't exists!");
	this->allMovies[indexOfMovieToUpdate] = updatedMovie;
	this->writeToFile();
}


int Repository::getMoviePosition(Movie movieToGetPosition)
{
	auto iterator = std::find(this->allMovies.begin(), this->allMovies.end(), movieToGetPosition);
	if (iterator == this->allMovies.end())
		return -1;
	return std::distance(this->allMovies.begin(), iterator);
}

void Repository::readFromFile()
{
	std::ifstream inputFile(this->filename);
	if (!inputFile.is_open())
		throw FileException("The file could not be opened!");
	Movie movieToRead;
	while (inputFile >> movieToRead)
		this->allMovies.push_back(movieToRead);
	inputFile.close();
}

void Repository::writeToFile()
{
	std::ofstream outputFile(this->filename);
	if (!outputFile.is_open())
		throw FileException("The file could not be opened!");
	for (auto movie : this->allMovies)
		outputFile << movie;
	outputFile.close();
}