#include "AdminService.h"
#include <iostream>
/*
 Constructor for the AdminService class
*/
AdminService::AdminService(Repository initialMoviesRepository) : moviesRepository{ initialMoviesRepository }
{
}

void AdminService::addMovie(string Title, string Genre, int YearOfRelease, int NrLikes, string Link)
{
	Movie movieToAdd{ Title, Genre, YearOfRelease, NrLikes, Link };
	return this->moviesRepository.addMovie(movieToAdd);
}

/*
	Function that removes a movie from the repository
*/
void AdminService::removeMovie(string Title, string Genre)
{
	//string Genre = "";
	int NrLikes = 0;
	int YearOfRelease = 0;
	string Link = "";
	Movie movieToRemove{ Title, Genre, YearOfRelease, NrLikes, Link };
	int indexOfMovieToRemove = this->moviesRepository.getMoviePosition(movieToRemove);
	return this->moviesRepository.removeMovie(indexOfMovieToRemove);
}

/*
	Function that updates a movie from the repository
*/
void AdminService::updateMovie(string Title, string Genre, string NewTitle, string NewGenre, int NewYearOfRelease, int NewNrLikes, string NewLink)
{
	//int yearOfRelease = 0;
	//int NrLikes = 0;
	//string Link = "";
	Movie movieToUpdate{ Title, Genre, 0, 0, "" };
	Movie updatedMovie{ NewTitle, NewGenre, NewYearOfRelease, NewNrLikes, NewLink };
	int indexOfMovieToUpdate = this->moviesRepository.getMoviePosition(movieToUpdate);
	return this->moviesRepository.updateMovie(indexOfMovieToUpdate, updatedMovie);
}

/*
	Function that increases the number of likes of a movie from the repository
*/
void AdminService::increaseLikes(string Title, string Genre)
{
	Movie movieToUpdate{ Title, Genre, 0, 0, "" };
	int indexOfMovieToUpdate = this->moviesRepository.getMoviePosition(movieToUpdate);
	Movie oldMovie = this->moviesRepository.getAllMovies()[indexOfMovieToUpdate];
	Movie updatedMovie{ Title, Genre, oldMovie.getYearOfRelease(), oldMovie.getNrLikes() + 1, oldMovie.getLink() };
	return this->moviesRepository.updateMovie(indexOfMovieToUpdate, updatedMovie);
}

/*
	Function that returns all the movies from the repository
*/
vector<Movie> AdminService::getAllMovies()
{
	return this->moviesRepository.getAllMovies();
}

/*
	Function that returns the movie with the most likes from the repository
*/
void AdminService::initialiseAllMovies()
{
	this->addMovie("Titanic", "Drama", 1997, 69, "https://www.imdb.com/title/tt0120338/");
	this->addMovie("The Shawshank Redemption", "Drama", 1994, 72, "https://www.imdb.com/title/tt0111161/");
	this->addMovie("The Godfather", "Crime", 1972, 70, "https://www.imdb.com/title/tt0068646/");
	this->addMovie("The Dark Knight", "Action", 2008, 68, "https://www.imdb.com/title/tt0468569/");
	this->addMovie("The Lord of the Rings: The Return of the King", "Adventure", 2003, 67, "https://www.imdb.com/title/tt0167260/");
	this->addMovie("Pulp Fiction", "Crime", 1994, 66, "https://www.imdb.com/title/tt0110912/");
	this->addMovie("Forrest Gump", "Drama", 1994, 65, "https://www.imdb.com/title/tt0109830/");
	this->addMovie("Inception", "Action", 2010, 64, "https://www.imdb.com/title/tt1375666/");
	this->addMovie("The Fellowship of the Ring", "Action", 2001, 63, "https://www.imdb.com/title/tt0120737/");
	this->addMovie("The Matrix", "Action", 1999, 62, "https://www.imdb.com/title/tt0133093/");
}


