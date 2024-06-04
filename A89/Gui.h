#pragma once
#include <qobject.h>
#include <qmainwindow.h>
#include <qlabel.h>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QListWidget>
#include "AdminService.h"
#include "UserService.h"

class Gui :
	public QObject
{
	Q_OBJECT
private:
	AdminService adminService;
	UserService userService;
	int argumentCount;
	char** argumentVector;

public:
	Gui(AdminService initialAdminService, UserService initialUserService, int argumentCount = 0, char** argumentVector = nullptr);
	int StartScreen();

	int PrintAdminMenu();
	int PrintUserMenu();

	int addMovie();
	int removeMovieFromAdmin();
	int updateMovie();
	int displayAllMovies();

	int searchMovieByGenre();
	int removeMovieFromWatchlist();
	int displayWatchlist();
	void detailsOfMovie(const Movie& movie, QLabel& movieLabel);
	int saveWatchlistToFile();
	int openWatchlist();

	void displayError(const char* message);

private slots:

	void on_addAdminButton_clicked();
	void on_removeAdminButton_clicked();
	void on_updateAdminButton_clicked();

	void handleUserMode();
	void handleAdminMode();

	void UndoButtonClicked();
	void RedoButtonClicked();
};