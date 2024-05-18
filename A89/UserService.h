#pragma once
#include "Repository.h"
#include "FileWatchlist.h"
#include <string>
#include <vector>

using std::string;

class UserService
{
private:
	Repository moviesRepository;
	FileWatchlist* watchList;
public:
	UserService(Repository initialMoviesRepository, FileWatchlist* initialWatchlist = nullptr);
	bool addMovieToWatchList(Movie movieToAdd);
	bool removeMovieFromWatchList(string Title, string Genre);
	vector<Movie> getMoviesOfGivenGenre(vector<Movie> allMovies, string Genre);
	FileWatchlist* getWatchList();
	void setWatchlist(std::string watchlistType);
	void saveWatchlist();
	void openWatchlist();
};