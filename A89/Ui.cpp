#include "UI.h"
#include <iostream>
#include <string>
#include <cstdlib>

using std::string;
using std::cout;
using std::cin;
using std::getline;

#define USER_SEARCH 1
#define USER_REMOVE 2
#define USER_CONSOLE_WATCHLIST 3
#define USER_SAVE_WATCHLIST 4
#define USER_OPEN_WATCHLIST 5

#define ADMIN_ADD 1
#define ADMIN_REMOVE 2
#define ADMIN_UPDATE 3
#define ADMIN_DISPLAY_TUTORIALS 4

#define EXIT 0

UI::UI(AdminService initialAdminService, UserService initialUserService) : adminService{ initialAdminService }, userService{ initialUserService }
{
}

void UI::addMovieUi()
{
	string Title = "", Genre = "", Link = "";
	int YearOfRelease = 0, NrLikes = 0;

	cout << "Movie title: '\n'";
	cin.ignore();
	getline(cin, Title);

	cout << "Movie genre: '\n'";
	getline(cin, Genre);

	cout << "Year of release: '\n'";
	cin >> YearOfRelease;

	cout << "Number of likes:'\n' ";
	cin >> NrLikes;

	cout << "Link:'\n' ";
	cin.ignore();
	getline(cin, Link);

	try {
		this->adminService.addMovie(Title, Genre, YearOfRelease, NrLikes, Link);
		std::cout << "Movie added successfully!" << '\n';
	}
	catch (const std::exception& message)
	{
		std::cout << message.what() << '\n';
	}
}

void UI::removeMovieUI()
{
	string Title = "";
	string Genre = "";

	cout << "Movie title to be removed: ";
	cin.ignore();
	getline(cin, Title);

	cout << "Genre: ";

	getline(cin, Genre);

	try {
		this->adminService.removeMovie(Title, Genre);
		std::cout << "Movie removed successfully!" << '\n';
	}
	catch (const std::exception& message)
	{
		std::cout << message.what() << '\n';
	}
}



void UI::updateMovieUI()
{
	string Title, Genre;

	std::cout << "Enter the title of the movie you want to update: ";
	cin.ignore();
	getline(cin, Title);

	std::cout << "Enter the genre of the movie you want to update: ";
	//cin.ignore();
	getline(cin, Genre);


	std::cout << "Enter the new title of the movie: ";
	string newTitle;
	//cin.ignore();
	getline(cin, newTitle);

	std::cout << "Enter the new genre of the movie: ";
	string newGenre;
	//cin.ignore();
	getline(cin, newGenre);

	std::cout << "Enter the new year of release of the movie: ";
	int newYearOfRelease;
	cin >> newYearOfRelease;

	std::cout << "Enter the new number of likes of the movie: ";
	int newNrLikes;
	cin >> newNrLikes;

	std::cout << "Enter the new link of the movie: ";
	string newLink;
	cin.ignore();
	getline(cin, newLink);

	try {
		this->adminService.updateMovie(Title, Genre, newTitle, newGenre, newYearOfRelease, newNrLikes, newLink);
		std::cout << "Movie updated successfully!" << '\n';
	}
	catch (const std::exception& message)
	{
		std::cout << message.what() << '\n';
	}
}


void UI::displayAllMoviesUI()
{
	vector<Movie> allMovies = this->adminService.getAllMovies();
	for (const auto& currentMovie : allMovies)
	{
		std::cout << "#" << &currentMovie - allMovies.data() + 1 << ".";
		std::cout << currentMovie.getTitle() << " - " << currentMovie.getGenre() << " - " << currentMovie.getYearOfRelease() << ", Number of likes: " << currentMovie.getNrLikes() << ", Link: " << currentMovie.getLink() << '\n';
	}
}

void UI::printAdminMenuUI()
{
	cout << "Admin menu: " << '\n';
	cout << "1. Add movie." << '\n';
	cout << "2. Remove movie." << '\n';
	cout << "3. Update movie." << '\n';
	cout << "4. Display all movies." << '\n';
	cout << "0. Exit admin mode." << '\n';
}

void UI::adminModeUI()
{
	int option;
	printAdminMenuUI();
	while (true)
	{
		cout << "Enter option: ";
		cin >> option;

		if (cin.fail() || option < 0 || option > 4)
		{
			cout << "Invalid option!" << '\n';
			cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear the buffer from invalid input 
			continue;
		}

		switch (option)
		{
		case ADMIN_ADD:
			addMovieUi();
			break;
		case ADMIN_REMOVE:
			removeMovieUI();
			break;
		case ADMIN_UPDATE:
			updateMovieUI();
			break;
		case ADMIN_DISPLAY_TUTORIALS:
			displayAllMoviesUI();
			break;
		case EXIT:
			cout << std::endl;
			return;
		default:
			cout << "Invalid option! Please try again!" << '\n';
			break;
		}
	}
}

void UI::searchMovieByGenreUI()
{
	string genre = "";
	string userOption = "";

	cout << "Search a genre: ";
	cin.ignore();
	getline(cin, genre);

	vector<Movie> searchedMovies = this->userService.getMoviesOfGivenGenre(this->adminService.getAllMovies(), genre);
	int currentMovieIndex = 0;

	while (true)
	{
		if (searchedMovies.size() == 0)
		{
			cout << "\nInvalid search! Please enter a valid genre!\n";
			break;
		}
		if (currentMovieIndex == searchedMovies.size())
			currentMovieIndex = 0;

		Movie currentMovie = searchedMovies[currentMovieIndex];
		cout << "\n#" << currentMovieIndex + 1 << std::endl;
		cout << currentMovie.toString() << '\n';
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		string command = "start " + currentMovie.getLink();
		system(command.c_str());

		cout << "Do you want to add this movie to your watchlist? (yes/next): ";
		cout << "Write 'x' to exit search!\n\n";

		while (true)
		{
			cout << "> ";
			cin >> userOption;
			if (userOption.compare("yes") == 0)
			{
				this->userService.addMovieToWatchList(currentMovie);
				currentMovieIndex++;
				cout << "Movie added to watchlist!" << '\n';
				break;
			}
			else if (userOption.compare("next") == 0)
			{
				currentMovieIndex++;
				break;
			}
			else if (userOption.compare("x") == 0)
			{
				cout << "You exited the search!\n";
				return;
			}
			else
				cout << "\nTake your time to decide!\nHint:\nyes - add to watchlist\nnext - see next tutorial in the search\nx - exit the search\n\n";
		}
		cout << std::endl;
	}
}

void UI::removeMovieFromWatchlistUI()
{
	string Title = "", Genre = "";
	string userOption;

	std::cout << "Enter the title of the movie you want to remove from the watchlist: ";
	cin.ignore();
	getline(cin, Title);

	std::cout << "Enter the genre of the movie you want to remove from the watchlist: ";
	//cin.ignore();
	getline(cin, Genre);

	bool checkRemoved = this->userService.removeMovieFromWatchList(Title, Genre);
	if (checkRemoved == false)
		cout << "Movie does not exist in the watchlist!" << '\n';
	else
	{
		cout << "Would you like to leave a like at this tutorial before removing it? (yes/no)\n";
		while (true)
		{
			cout << "> ";
			cin >> userOption;
			if (userOption.compare("yes") == 0)
			{
				this->adminService.increaseLikes(Title, Genre);
				cout << "Like added! Thank you for feedback!" << '\n';
				break;
			}
			else if (userOption.compare("no") == 0)
			{
				cout << "Like not added! Thank you for feedback!" << '\n';
				break;
			}
			else
				cout << "Invalid option! Please try again!\n Hint:(yes/no)" << '\n';
			cout << "Movie removed from watchlist successfully!" << '\n';
		}
	}


}

void UI::displayWatchlistUI()
{
	std::vector<Movie> allMovies = this->userService.getWatchList()->getAllMovies();
	for (const auto& currentMovie : allMovies)
	{
		std::cout << "#" << &currentMovie - allMovies.data() + 1 << ".";
		std::cout << currentMovie.getTitle() << " - " << currentMovie.getGenre() << " - " << currentMovie.getYearOfRelease() << ", Number of likes: " << currentMovie.getNrLikes() << ", Link: " << currentMovie.getLink() << '\n';

	}
}

void UI::printUserMenuUI()
{
	cout << "User menu: " << '\n';
	cout << "1. Search movie by genre." << '\n';
	cout << "2. Remove movie from watchlist." << '\n';
	cout << "3. Display watchlist." << '\n';
	cout << "4. Save watchlist to file." << '\n';
	cout << "5. Open watchlist." << '\n';
	cout << "0. Exit user mode." << '\n';
}

void UI::saveWatchlistToFileUI()
{
	std::string filename;
	std::cout << "Input the file name (absolute path): ";
	std::cin.ignore();
	std::getline(std::cin, filename);
	this->userService.saveWatchlist();

	if (this->userService.getWatchList() == nullptr)
	{
		std::cout << "Watchlist cannot be displayed!" << '\n';
		return;
	}
}

void UI::openWatchlistUI()
{
	this->userService.openWatchlist();
}


void UI::userModeUI()
{
	int optionChosen = -1;
	printUserMenuUI();
	while (true)
	{
		cout << "Enter option: ";
		cin >> optionChosen;

		if (cin.fail() || optionChosen < 0 || optionChosen > 5)
		{
			cout << "Invalid option!" << '\n';
			cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear the buffer from invalid input 
			continue;
		}
		switch (optionChosen)
		{
		case USER_SEARCH:
			this->searchMovieByGenreUI();
			break;
		case USER_REMOVE:
			this->removeMovieFromWatchlistUI();
			break;
		case USER_CONSOLE_WATCHLIST:
			this->displayWatchlistUI();
			break;
		case USER_SAVE_WATCHLIST:
			this->saveWatchlistToFileUI();
			break;
		case USER_OPEN_WATCHLIST:
			this->openWatchlistUI();
			break;
		case EXIT:
			cout << std::endl;
			return;
		default:
			cout << "Invalid option! Please try again!" << '\n';
			break;
		}
	}
}


void UI::startAppUI()
{
	cout << "Welcome to Local Movie Database!" << '\n';
	cout << "Please enter your mode (admin/user) or type 'exit' to close the app \n \n";

	string accesMode = "";

	while (true)
	{
		cout << "Enter mode: ";
		cin >> accesMode;
		if (accesMode.compare("admin") == 0)
			adminModeUI();
		else if (accesMode.compare("user") == 0)
			userModeUI();
		else if (accesMode.compare("exit") == 0)
		{
			cout << "App closed successfully!" << '\n';
			return;
		}
		else
			cout << "Invalid acces mode!\nHint: admin/user/exit\n\n";

	}
}

