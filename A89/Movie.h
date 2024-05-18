#pragma once
#include <string>

using std::string;

class Movie
{
private:
	string Title;
	string Genre;
	int YearOfRelease;
	int NrLikes;
	string Link;

public:
	string getTitle() const;
	void setTitle(string Title);
	string getGenre() const;
	void setGenre(string Genre);
	string getLink() const;
	void setLink(string Link);
	int getYearOfRelease() const;
	void setYearOfRelease(int YearOfRelease);
	int getNrLikes() const;
	void setNrLikes(int NrLikes);

	//my constructor 
	Movie(string Title, string Genre, int YearOfRelease, int NrLikes, string Link);

	//default constructor NOT USED
	Movie() : Title(""), Genre(""), YearOfRelease(0), NrLikes(0), Link("") {}

	bool operator == (const Movie& MovieToCompare); // for comparing two movie objects
	void operator = (const Movie& MovieToCopy); // for making a copy of the movie object


	friend std::istream& operator >> (std::istream& inputFile, Movie& movieToRead); // for reading a movie object from the console
	friend std::ostream& operator << (std::ostream& outputFile, const Movie& movieToWrite); // for writing a movie object to the console

	string toString();
};