#include "Watchlist.h"

std::vector<Movie> Watchlist::getAllMovies()
{
	return this->allMovies;
}

bool Watchlist::addMovie(Movie movieToAdd)
{
	auto iterator = std::find(this->allMovies.begin(), this->allMovies.end(), movieToAdd);
	if (iterator != this->allMovies.end())
		return false;
	this->allMovies.push_back(movieToAdd);
	return true;
}

bool Watchlist::removeMovie(Movie movieToRemove)
{
	auto iterator = std::find(this->allMovies.begin(), this->allMovies.end(), movieToRemove);
	if (iterator == this->allMovies.end())
		return false;
	this->allMovies.erase(iterator);
	return true;
}