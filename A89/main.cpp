#include "A89.h"
#include "Gui.h"
#include "Movie.h"
#include "Repository.h"
#include "AdminService.h"
#include "UserService.h"
#include "CsvWatchlist.h"
#include "HtmlWatchlist.h"
#include "Exception.h"
#include <iostream>
#include <crtdbg.h>
#include <vector>

#include <QtWidgets/QApplication>

using namespace std;

int main(int argc, char* argv[])
{
	{
		try {
			Repository repo{ "movies.txt" };
			FileWatchlist* filePointer = nullptr;

			UserService userService{ repo, filePointer };
			AdminService adminService{ repo };
			Gui console{ adminService, userService };

			cout << endl << endl;

			console.StartScreen();
		}
		catch (FileException&)
		{
			cout << "Repository file could not be opened! The application will terminate." << endl;
			return 1;
		}
	}
}

