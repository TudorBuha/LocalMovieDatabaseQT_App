#pragma once
#include "FileWatchlist.h"
#include <iostream>
#include <fstream>

class HtmlWatchlist : public FileWatchlist
{
private:
    void writeMovieToHTML(std::ostream& outputFile, const Movie& movieToWrite);
public:
    HtmlWatchlist(const std::string& filename) : FileWatchlist{ filename } {};
    void writeToFile() override;
    void displayWatchlist() override;
};
