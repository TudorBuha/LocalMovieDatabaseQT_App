#include "HtmlWatchlist.h"
#include <exception>
#include <Windows.h>

void HtmlWatchlist::writeMovieToHTML(std::ostream& outputFile, const Movie& tutorialToWrite)
{
	outputFile
		<< "		<tr>\n"
		<< "			<td>" << tutorialToWrite.getTitle() << "</td>" << std::endl
		<< "			<td>" << tutorialToWrite.getGenre() << "</td>" << std::endl
		<< "			<td>" << tutorialToWrite.getYearOfRelease() << "</td>" << std::endl
		<< "			<td>" << tutorialToWrite.getNrLikes() << "</td>" << std::endl
		<< "			<td>" << "<a href=\"" << tutorialToWrite.getLink() << "\">" << "Link" << "</a>" << "</td>" << std::endl
		<< "		</tr>" << std::endl;
}

void HtmlWatchlist::writeToFile()
{
	std::ofstream outputFile{ filename };
	if (!outputFile.is_open())
		throw std::runtime_error{ "File is not opened!" };
	outputFile << "<!DOCTYPE html>\n"
		<< "<html>\n"
		<< "	<head>\n"
		<< "		<title> Watchlist </title>\n"
		<< "	</head>\n"
		<< "<body>\n"
		<< "	<table border = ""1"">\n"
		<< "		<tr>\n"
		<< "			<td>" << "Title" << "</td>" << std::endl
		<< "			<td>" << "Genre" << "</td>" << std::endl
		<< "			<td>" << "YearOfRelease" << "</td>" << std::endl
		<< "			<td>" << "Likes" << "</td>" << std::endl
		<< "			<td>" << "Link" << "</td>" << std::endl
		<< "		</tr>" << std::endl;
	for (const auto& currentMovie : allMovies)
		this->writeMovieToHTML(outputFile, currentMovie);
	outputFile << "</table>\n"
		<< "</body>\n"
		<< "</html>\n";
	outputFile.close();
}

void HtmlWatchlist::displayWatchlist()
{
	char buffer[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, buffer);
	std::string path(buffer);
	path += "\\" + filename;
	std::string command = "start \"\" \"" + path + "\"";
	system(command.c_str());
}