#include "Movie.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <vector>
/*
	Constructor for the Movie class
*/
Movie::Movie(string Title, string Genre, int YearOfRelease, int NrLikes, string Link)
{
	this->Title = Title;
	this->Genre = Genre;
	this->YearOfRelease = YearOfRelease;
	this->NrLikes = NrLikes;
	this->Link = Link;
}

/*
	Function that returns the title of the movie
*/
string Movie::getTitle() const
{
	return this->Title;
}

/*
	Function that returns the genre of the movie

*/
string Movie::getGenre() const
{
	return this->Genre;
}

/*
	Function that returns the link of the movie
*/
string Movie::getLink() const
{
	return this->Link;
}

/*
	Function that returns the number of likes of the movie
*/
int Movie::getNrLikes() const
{
	return this->NrLikes;
}

/*
	Function that returns the year of release of the movie
*/
int Movie::getYearOfRelease() const
{
	return this->YearOfRelease;
}

/*
	Function that increases the number of likes of the movie
*/
void Movie::setTitle(string NewTitle)
{
	this->Title = NewTitle;
}

/*
	Function that sets the genre of the movie
*/
void Movie::setGenre(string NewGenre)
{
	this->Genre = NewGenre;
}

/*
	Function that sets the link of the movie
*/
void Movie::setLink(string NewLink)
{
	this->Link = NewLink;
}

/*
	Function that sets the number of likes of the movie

*/
void Movie::setNrLikes(int NewNrLikes)
{
	this->NrLikes = NewNrLikes;
}

/*
	Function that sets the year of release of the movie
*/
void Movie::setYearOfRelease(int NewYearOfRelease)
{
	this->YearOfRelease = NewYearOfRelease;
}

//A movie is not unique if it have it's Title and Genre the same as other movie
bool Movie::operator==(const Movie& MovieToCompare)
{
	return (this->Title == MovieToCompare.Title && this->Genre == MovieToCompare.Genre);
}

/*
	Overloading the assignment operator
*/
void Movie::operator=(const Movie& MovieToCopy)
{
	this->Title = MovieToCopy.Title;
	this->Genre = MovieToCopy.Genre;
	this->YearOfRelease = MovieToCopy.YearOfRelease;
	this->NrLikes = MovieToCopy.NrLikes;
	this->Link = MovieToCopy.Link;
}

/*
	Turns the movie object into a string representation
*/
string Movie::toString()
{
	return this->Title + " - " + this->Genre + " - " + std::to_string(this->YearOfRelease) + " - " + std::to_string(this->NrLikes) + " likes - " + this->Link;
}

/*
	Overloading the >> operator
*/

std::istream& operator>>(std::istream& inputFile, Movie& movieToRead)
{
	std::string lineRead;
	std::getline(inputFile, lineRead);
	std::vector<std::string> tokens = tokenize(lineRead, ',');
	if (tokens.size() != 5)
		return inputFile;
	movieToRead.Title = tokens[0];
	movieToRead.Genre = tokens[1];
	movieToRead.YearOfRelease = std::stoi(tokens[2]);
	movieToRead.NrLikes = std::stoi(tokens[3]);
	movieToRead.Link = tokens[4];
	return inputFile;
}

/*
	Overloading the << operator
*/
std::ostream& operator<<(std::ostream& outputFile, const Movie& movieToWrite)
{
	outputFile << movieToWrite.Title << "," << movieToWrite.Genre << "," << movieToWrite.YearOfRelease << "," << movieToWrite.NrLikes << "," << movieToWrite.Link << "\n";
	return outputFile;
}