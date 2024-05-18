#include "UserService.h"
#include <iterator>
#include <algorithm>
#include "CsvWatchlist.h"
#include "HtmlWatchlist.h"
/*
  Constructor for the UserService class
*/
UserService::UserService(Repository initialMoviesRepository, FileWatchlist* initialWatchlist) : moviesRepository{ initialMoviesRepository }, watchList{ initialWatchlist }
{
}

/*
  Function that returns all the movies from the repository

  Returns:
	- a DynamicArray<Movie> object that contains all the movies from the repository
*/
bool UserService::addMovieToWatchList(Movie movieToAdd)
{

	return this->watchList->addMovie(movieToAdd);
}

/*
  Function that removes a movie from the watch list

  Parameters:
	- Title: a string representing the title of the movie to be removed
	- Genre: a string representing the genre of the movie to be removed

  Returns:
	- true, if the movie was removed successfully
	- false, otherwise
*/
bool UserService::removeMovieFromWatchList(string Title, string Genre)
{

	if (this->watchList == nullptr)
		return false;
	Movie movieToRemove(Title, Genre, 0, 0, "");
	return this->watchList->removeMovie(movieToRemove);
}

/*
  Function that returns all the movies from the watch list

  Returns:
	- a DynamicArray<Movie> object that contains all the movies from the watch list
*/
vector<Movie> UserService::getMoviesOfGivenGenre(vector<Movie> allMovies, string Genre)
{
	if (Genre.compare("") == 0)
		return allMovies;
	vector<Movie> neededMovies;
	std::copy_if(allMovies.begin(), allMovies.end(), std::back_inserter(neededMovies), [Genre](const Movie& movie) { return movie.getGenre() == Genre; }); // copy if the genre is the same
	return neededMovies;
}

/*
  Function that returns all the movies from the watch list

  Returns:
	- a DynamicArray<Movie> object that contains all the movies from the watch list
*/
FileWatchlist* UserService::getWatchList()
{
	return this->watchList;
}

void UserService::setWatchlist(std::string watchlistType)
{
	if (watchlistType == "CSV")
		this->watchList = new CsvWatchlist{ "watchlist.csv" };
	else if (watchlistType == "HTML")
		this->watchList = new HtmlWatchlist{ "watchlist.html" };
}


void UserService::saveWatchlist()
{
	this->watchList->writeToFile();
}

void UserService::openWatchlist()
{
	this->watchList->displayWatchlist();
}