#pragma once
#include "AdminService.h"
#include "UserService.h"

class UI
{
private:
	AdminService adminService;
	UserService userService;
public:
	UI(AdminService initialAdminService, UserService initialUserService);

	//admin stuff
	void addMovieUi();
	void removeMovieUI();
	void updateMovieUI2();
	void updateMovieUI();
	void displayAllMoviesUI();
	void printAdminMenuUI();
	void adminModeUI();

	//user stuff
	void searchMovieByGenreUI();
	void removeMovieFromWatchlistUI();
	void displayWatchlistUI();
	void printUserMenuUI();
	void userModeUI();
	// 
	void saveWatchlistToFileUI();
	void openWatchlistUI();

	void startAppUI();

};