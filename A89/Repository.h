#pragma once
#include "Movie.h"
#include <vector>

using std::vector;

class Repository
{
private:
	vector<Movie> allMovies;
	std::string filename;
public:
	Repository(std::string filename, std::vector<Movie> initialMovies = {});
	vector<Movie> getAllMovies();
	void addMovie(Movie movieToAdd);
	void removeMovie(int indexOfMovieToRemove);
	void updateMovie(int indexOfMovieToUpdate, Movie updatedMovie);
	int getMoviePosition(Movie movieToGetPosition);
private:
	void readFromFile();
	void writeToFile();
};