#pragma once
#include "Repository.h"
#include <string>
#include <vector>

using std::string;


class AdminService
{
private:
	Repository moviesRepository;
public:
	AdminService(Repository initialMovieRepository);
	void addMovie(string Title, string Genre, int YearOfRelease, int NrLikes, string Link);
	void removeMovie(string Title, string Genre);
	void updateMovie(string Title, string Genre, string NewTitle, string NewGenre, int NewYearOfRelease, int NewNrLikes, string NewLink);
	void increaseLikes(string Title, string Genre);

	vector<Movie> getAllMovies();
	void initialiseAllMovies();



};