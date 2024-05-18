#pragma once
#include <vector>
#include "Movie.h"

class Watchlist
{
protected:
	std::vector<Movie> allMovies;
public:
	Watchlist(std::vector<Movie> initialMovies = {}) {};
	std::vector<Movie> getAllMovies();
	bool addMovie(Movie movieToAdd);
	bool removeMovie(Movie movieToRemove);
	virtual ~Watchlist() {};
};