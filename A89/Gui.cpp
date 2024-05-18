#include "Gui.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHeaderView>
#include <QDialog>
#include <QInputDialog>
#include <warning.h>
#include <qmessagebox.h>
#include <iostream>
#include <QGroupBox>
#include <qlabel.h>

Gui::Gui(AdminService initialAdminService, UserService initialUserService, int initialArgumentCount, char** initialArgumentVector)
	: adminService{ initialAdminService }, userService{ initialUserService }, argumentCount{ initialArgumentCount }, argumentVector{ initialArgumentVector }
{}

int Gui::StartScreen()
{
	QApplication application(argumentCount, argumentVector);

	QWidget window{};

	window.setStyleSheet("background-color: #186A3B; color: white;");
	window.setWindowTitle("Movie Database");

	QVBoxLayout* mainLayout = new QVBoxLayout{};
	QHBoxLayout* buttonLayout = new QHBoxLayout{};
	QLabel* titleLabel = new QLabel("Movie Database Application");
	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setStyleSheet("font-size: 30px; font-weight: bold; margin-bottom: 20px;");

	QPushButton* adminButton = new QPushButton("Administrator Mode");
	QPushButton* userButton = new QPushButton("User Mode");

	adminButton->setStyleSheet("background-color:  darkgreen; color: white;");
	userButton->setStyleSheet("background-color:  darkgreen; color: white;");

	connect(adminButton, &QPushButton::clicked, this, &Gui::PrintAdminMenu);
	connect(userButton, &QPushButton::clicked, this, &Gui::PrintUserMenu);

	buttonLayout->addWidget(adminButton);
	buttonLayout->addWidget(userButton);

	mainLayout->addWidget(titleLabel);
	mainLayout->addLayout(buttonLayout);

	window.setLayout(mainLayout);
	window.resize(500, 250);
	window.show();
	return application.exec();
}

int Gui::PrintAdminMenu()
{
	QDialog* popup = new QDialog();
	QWidget window{ popup };
	window.setStyleSheet("background-color: #186A3B; color: white; font-size: 20px;");
	QVBoxLayout layout{};
	QListWidget list;
	QLabel title("Admin mode");
	title.setAlignment(Qt::AlignCenter);
	QListWidgetItem* element1 = new QListWidgetItem("1. Add a new movie", &list);
	QListWidgetItem* element2 = new QListWidgetItem("2. Delete a movie", &list);
	QListWidgetItem* element3 = new QListWidgetItem("3. Update a movie", &list);
	QListWidgetItem* element4 = new QListWidgetItem("4. Display all movies", &list);
	layout.addWidget(&title);
	layout.addWidget(&list);
	window.setLayout(&layout);
	window.show();
	window.resize(500, 450);
	connect(&list, &QListWidget::itemClicked, this, &Gui::handleAdminMode);
	return popup->exec();
}


int Gui::PrintUserMenu()
{
	QStringList options;
	options << "HTML" << "CSV";
	bool ok;
	QString selectedOption = QInputDialog::getItem(nullptr, "Save Watchlist", "Choose file format:", options, 0, false, &ok);
	if (!ok)
	{
		return 0;
	}
	this->userService.setWatchlist(selectedOption.toStdString());
	if (this->userService.getWatchList() == nullptr)
	{
		QMessageBox::critical(nullptr, "Error", "Watchlist is nullptr!");
		return 0;
	}
	QDialog* popup = new QDialog();
	QWidget window{ popup };
	window.setStyleSheet("background-color: #186A3B; color: white; font-size: 20px;");
	QVBoxLayout layout{};
	QListWidget list;
	QLabel title("User mode");
	title.setAlignment(Qt::AlignCenter);
	QListWidgetItem* element1 = new QListWidgetItem("1. Search movie by genre", &list);
	QListWidgetItem* element2 = new QListWidgetItem("2. Remove movie from watchlist", &list);
	QListWidgetItem* element3 = new QListWidgetItem("3. Display watchlist", &list);
	QListWidgetItem* element4 = new QListWidgetItem("4. Save watchlist", &list);
	QListWidgetItem* element5 = new QListWidgetItem("5. Open watchlist", &list);
	layout.addWidget(&title);
	layout.addWidget(&list);
	window.setLayout(&layout);
	window.show();
	window.resize(500, 450);
	connect(&list, &QListWidget::itemClicked, this, &Gui::handleUserMode);
	return popup->exec();
}

int Gui::addMovie()
{
	QDialog popup;
	popup.setStyleSheet("background-color: #186A3B; color: white;");
	QFormLayout* formLayout = new QFormLayout{};

	QLabel label("Add a new movie");
	label.setAlignment(Qt::AlignCenter);

	QLineEdit* titleInput = new QLineEdit();
	titleInput->setObjectName("title");
	QLabel titleLabel("Title ");
	titleLabel.setBuddy(titleInput);

	QLineEdit* genreInput = new QLineEdit();
	genreInput->setObjectName("genre");
	QLabel genreLabel("Genre ");
	genreLabel.setBuddy(genreInput);

	QLineEdit* yearOfReleaseInput = new QLineEdit();
	yearOfReleaseInput->setObjectName("yearOfRelease");
	QLabel yearOfReleaseLabel("Year of release ");
	yearOfReleaseLabel.setBuddy(yearOfReleaseInput);

	QLineEdit* likesInput = new QLineEdit();
	likesInput->setObjectName("likes");
	QLabel nrLikesLabel("Likes ");
	nrLikesLabel.setBuddy(likesInput);

	QLineEdit* linkInput = new QLineEdit();
	linkInput->setObjectName("link");
	QLabel linkLabel("Link ");
	linkLabel.setBuddy(linkInput);

	formLayout->addRow(&label);
	formLayout->addRow(&titleLabel, titleInput);
	formLayout->addRow(&genreLabel, genreInput);
	formLayout->addRow(&yearOfReleaseLabel, yearOfReleaseInput);
	formLayout->addRow(&nrLikesLabel, likesInput);
	formLayout->addRow(&linkLabel, linkInput);

	QPushButton* addButton = new QPushButton("Add");
	formLayout->addRow(addButton);

	connect(addButton, &QPushButton::clicked, this, &Gui::on_addAdminButton_clicked);

	popup.setLayout(formLayout);
	return popup.exec();

}

int Gui::removeMovieFromAdmin()
{
	QDialog* popup = new QDialog();
	QWidget window{ popup };
	window.setStyleSheet("background-color: #186A3B; color: white;");
	QFormLayout* formLayout = new QFormLayout{};
	QLabel label("Remove a movie");
	label.setAlignment(Qt::AlignCenter);
	QLabel titleLabel("Title ");
	QLabel genreLabel("Genre ");

	QLineEdit* titleInput = new QLineEdit();
	titleInput->setObjectName("title");
	titleLabel.setBuddy(titleInput);
	QLineEdit* presenterInput = new QLineEdit();
	presenterInput->setObjectName("genre");
	genreLabel.setBuddy(presenterInput);
	formLayout->addRow(&label);
	formLayout->addRow(&titleLabel, titleInput);
	formLayout->addRow(&genreLabel, presenterInput);

	QPushButton removeBtn("Remove");
	formLayout->addRow(&removeBtn);
	connect(&removeBtn, &QPushButton::clicked, this, &Gui::on_removeAdminButton_clicked);
	window.setLayout(formLayout);
	window.show();
	return popup->exec();
}

int Gui::updateMovie()
{
	QDialog* popup = new QDialog();
	QWidget window{ popup };
	window.setStyleSheet("background-color: #186A3B; color: white;");
	QFormLayout* formLayout = new QFormLayout{};
	QLabel label("Update a movie");
	label.setAlignment(Qt::AlignCenter);

	QLabel oldTitleLabel("Old Title ");
	QLabel oldGenreLabel("Old Genre ");
	QLabel newTitleLabel("New Title ");
	QLabel newGenreLabel("New Genre ");
	QLabel newYearOfReleaseLabel("New Year of release ");
	QLabel newLikesLabel("New likes ");
	QLabel newLinkLabel("New link ");

	QLineEdit* oldTitleInput = new QLineEdit();
	oldTitleInput->setObjectName("oldTitle");
	oldTitleLabel.setBuddy(oldTitleInput);
	QLineEdit* oldGenreInput = new QLineEdit();
	oldGenreInput->setObjectName("oldGenre");
	oldGenreLabel.setBuddy(oldGenreInput);

	QLineEdit* newTitleInput = new QLineEdit();
	newTitleInput->setObjectName("newTitle");
	newTitleLabel.setBuddy(newTitleInput);
	QLineEdit* newGenreInput = new QLineEdit();
	newGenreInput->setObjectName("newGenre");
	newGenreLabel.setBuddy(newGenreInput);
	QLineEdit* newYearOfReleaseInput = new QLineEdit();
	newYearOfReleaseInput->setObjectName("newYearOfRelease");
	newYearOfReleaseLabel.setBuddy(newYearOfReleaseInput);
	QLineEdit* newLikesInput = new QLineEdit();
	newLikesInput->setObjectName("newLikes");
	newLikesLabel.setBuddy(newLikesInput);
	QLineEdit* newLinkInput = new QLineEdit();
	newLinkInput->setObjectName("newLink");
	newLinkLabel.setBuddy(newLinkInput);

	formLayout->addRow(&label);
	formLayout->addRow(&oldTitleLabel, oldTitleInput);
	formLayout->addRow(&oldGenreLabel, oldGenreInput);
	formLayout->addRow(&newTitleLabel, newTitleInput);
	formLayout->addRow(&newGenreLabel, newGenreInput);
	formLayout->addRow(&newYearOfReleaseLabel, newYearOfReleaseInput);
	formLayout->addRow(&newLikesLabel, newLikesInput);
	formLayout->addRow(&newLinkLabel, newLinkInput);

	QPushButton updateBtn("Update");
	formLayout->addRow(&updateBtn);
	connect(&updateBtn, &QPushButton::clicked, this, &Gui::on_updateAdminButton_clicked);
	window.setLayout(formLayout);
	window.show();
	return popup->exec();
}

int Gui::displayAllMovies()
{
	QDialog* popup = new QDialog();
	QTableWidget* table = new QTableWidget(popup);
	table->setRowCount(adminService.getAllMovies().size());
	table->setColumnCount(5);

	table->setStyleSheet("background-color: #186A3B; color: white; font-size: 15px;");
	QStringList headerLabels;
	headerLabels << "Title" << "Genre" << "YearOfRelease" << "Likes" << "Link";
	table->setHorizontalHeaderLabels(headerLabels);

	int rowIndex = 0;
	for (const auto& currentMovie : adminService.getAllMovies())
	{
		QTableWidgetItem* titleItem = new QTableWidgetItem(currentMovie.getTitle().c_str());
		QTableWidgetItem* genreItem = new QTableWidgetItem(currentMovie.getGenre().c_str());
		QTableWidgetItem* yearOfReleaseItem = new QTableWidgetItem(QString::number(currentMovie.getYearOfRelease()));
		QTableWidgetItem* likesItem = new QTableWidgetItem(QString::number(currentMovie.getNrLikes()));
		QTableWidgetItem* linkItem = new QTableWidgetItem(currentMovie.getLink().c_str());

		table->setItem(rowIndex, 0, titleItem);
		table->setItem(rowIndex, 1, genreItem);
		table->setItem(rowIndex, 2, yearOfReleaseItem);
		table->setItem(rowIndex, 3, likesItem);
		table->setItem(rowIndex, 4, linkItem);

		rowIndex++;
	}
	QHeaderView* header = table->horizontalHeader();
	header->setStyleSheet("color: #186A3B;");
	QHeaderView* verticalHeader = table->verticalHeader();
	verticalHeader->setStyleSheet("color: #186A3B;");
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);

	table->resizeRowsToContents();
	table->resizeColumnsToContents();
	table->resize(750, 500);
	table->show();
	return popup->exec();
}

int Gui::searchMovieByGenre()
{
	QDialog dialog;
	QVBoxLayout layout(&dialog);
	dialog.setStyleSheet("background-color: #186A3B; color: white;");
	QLabel searchLabel("Search a genre:");
	QLineEdit genreLineEdit;
	QPushButton searchButton("Search");
	QGroupBox movieGroupBox("Details");
	QVBoxLayout movieLayout(&movieGroupBox);
	QLabel movieLabel;
	QPushButton addButton("Add to Watchlist");
	QPushButton nextButton("Next");
	searchButton.setStyleSheet("background-color:  darkgreen; color: white;");
	addButton.setStyleSheet("background-color:  darkgreen; color: white;");
	nextButton.setStyleSheet("background-color:  darkgreen; color: white;");
	QHBoxLayout searchLayout;
	searchLayout.addWidget(&searchLabel);
	searchLayout.addWidget(&genreLineEdit);
	searchLayout.addWidget(&searchButton);

	layout.addLayout(&searchLayout);
	layout.addWidget(&movieGroupBox);
	layout.addWidget(&addButton);
	layout.addWidget(&nextButton);

	std::vector<Movie> searchedMovies;
	int currentIndex = 0;

	QObject::connect(&searchButton, &QPushButton::clicked, [&]() {
		QString searchedGenre = genreLineEdit.text();

		int currentIndex = 0;
		searchedMovies = this->userService.getMoviesOfGivenGenre(
			this->adminService.getAllMovies(), searchedGenre.toStdString());

		if (searchedMovies.empty()) {
			QMessageBox::warning(&dialog, "Invalid search", "Please enter a valid genre!");
			return;
		}

		this->detailsOfMovie(searchedMovies[currentIndex], movieLabel);
		});

	QObject::connect(&addButton, &QPushButton::clicked, [&]() {
		if (currentIndex < searchedMovies.size()) {
			this->userService.addMovieToWatchList(searchedMovies[currentIndex]);
			currentIndex++;
			if (currentIndex < searchedMovies.size()) {
				this->detailsOfMovie(searchedMovies[currentIndex], movieLabel);
			}
			else {
				currentIndex = 0;
			}
		}
		});

	QObject::connect(&nextButton, &QPushButton::clicked, [&]() {
		currentIndex++;

		if (currentIndex < searchedMovies.size()) {
			this->detailsOfMovie(searchedMovies[currentIndex], movieLabel);
		}
		else {
			currentIndex = 0;
		}
		});
	movieLayout.addWidget(&movieLabel);
	dialog.resize(600, 400);
	return dialog.exec();
}

void Gui::detailsOfMovie(const Movie& movie, QLabel& movieLabel)
{
	QString title = QString::fromStdString(movie.getTitle());
	QString genre = QString::fromStdString(movie.getGenre());
	QString yearOfRelease = QString::number(movie.getYearOfRelease());
	QString likes = QString::number(movie.getNrLikes());
	QString link = QString::fromStdString(movie.getLink());
	/////////////////////////////////////////////////////////////////////////////////
	QString message = QString("<b>Title:</b> %1<br>"
		"<b>Genre:</b> %2<br>"
		"<b>YearOfRelease:</b> %3<br>"
		"<b>Likes:</b> %4<br>"
		"<b>Link:</b> %5<br>")
		.arg(title)
		.arg(genre)
		.arg(yearOfRelease)
		.arg(likes)
		.arg(link);

	movieLabel.setText(message);
	movieLabel.setAlignment(Qt::AlignTop);
	movieLabel.setWordWrap(true);
	movieLabel.setOpenExternalLinks(true);
	movieLabel.setTextInteractionFlags(Qt::TextBrowserInteraction);
	movieLabel.setStyleSheet(" color: white; font-size: 20pt;");
}

int Gui::removeMovieFromWatchlist()
{
	QDialog* popup = new QDialog();
	QWidget window{ popup };
	window.setStyleSheet("background-color: #186A3B; color: white;");
	QFormLayout* formLayout = new QFormLayout{};
	QLabel label("Remove a movie");
	label.setAlignment(Qt::AlignCenter);
	QLabel titleLabel("Title ");
	QLabel genreLabel("Genre ");

	QLineEdit* titleInput = new QLineEdit();
	titleInput->setObjectName("title");
	titleLabel.setBuddy(titleInput);
	QLineEdit* genreInput = new QLineEdit();
	genreInput->setObjectName("genre");
	genreLabel.setBuddy(genreInput);
	formLayout->addRow(&label);
	formLayout->addRow(&titleLabel, titleInput);
	formLayout->addRow(&genreLabel, genreInput);

	QPushButton removeBtn("Remove");
	formLayout->addRow(&removeBtn);
	connect(&removeBtn, &QPushButton::clicked, this, [&]() {
		std::string title = sender()->parent()->findChild<QLineEdit*>("title")->text().toStdString();
		std::string genre = sender()->parent()->findChild<QLineEdit*>("genre")->text().toStdString();
		try
		{
			userService.removeMovieFromWatchList(title, genre);
			std::cout << "Successful remove\n";

		}
		catch (const std::exception& e)
		{
			displayError(e.what());
			QWidget* parentW = qobject_cast<QWidget*>(sender()->parent());
			parentW->close();
		}
		QWidget* parentW = qobject_cast<QWidget*>(sender()->parent()->parent());
		parentW->close();
		});
	window.setLayout(formLayout);
	window.show();
	return popup->exec();
}

int Gui::displayWatchlist()
{
	QDialog* popup = new QDialog();
	QTableWidget* table = new QTableWidget(popup);
	table->setRowCount(userService.getWatchList()->getAllMovies().size());
	table->setColumnCount(5);

	table->setStyleSheet("background-color: #186A3B; color: white; font-size: 15px;");
	QStringList headerLabels;
	headerLabels << "Title" << "Genre" << "YearOfRelease" << "Likes" << "Link";
	table->setHorizontalHeaderLabels(headerLabels);

	int rowIndex = 0;
	for (const auto& currentMovie : userService.getWatchList()->getAllMovies())
	{
		QTableWidgetItem* titleItem = new QTableWidgetItem(currentMovie.getTitle().c_str());
		QTableWidgetItem* genre = new QTableWidgetItem(currentMovie.getGenre().c_str());
		QTableWidgetItem* yearOfRelease = new QTableWidgetItem(QString::number(currentMovie.getYearOfRelease()));
		QTableWidgetItem* Likes = new QTableWidgetItem(QString::number(currentMovie.getNrLikes()));
		QTableWidgetItem* linkItem = new QTableWidgetItem(currentMovie.getLink().c_str());

		table->setItem(rowIndex, 0, titleItem);
		table->setItem(rowIndex, 1, genre);
		table->setItem(rowIndex, 2, yearOfRelease);
		table->setItem(rowIndex, 3, Likes);
		table->setItem(rowIndex, 4, linkItem);

		rowIndex++;
	}
	QHeaderView* header = table->horizontalHeader();
	header->setStyleSheet("color: #186A3B;");
	QHeaderView* verticalHeader = table->verticalHeader();
	verticalHeader->setStyleSheet("color: #186A3B;");
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);


	table->resizeRowsToContents();
	table->resizeColumnsToContents();
	table->resize(750, 500);
	table->show();
	return popup->exec();
}

int Gui::saveWatchlistToFile()
{
	this->userService.saveWatchlist();
	QMessageBox validationMessage;
	validationMessage.setStyleSheet("background-color: #186A3B; color: white;");
	validationMessage.setText("Watchlist saved successfully!");
	return validationMessage.exec();
}

int Gui::openWatchlist()
{
	this->userService.openWatchlist();
	return 0;
}

void Gui::displayError(const char* message)
{
	if (strcmp(message, "invalid stoi argument") == 0)
		message = "Invalid input";
	QDialog* popup = new QDialog();
	QLabel label(message, popup);
	popup->setStyleSheet("background-color: #186A3B; color: white;");
	label.setAlignment(Qt::AlignCenter);
	label.setFont(QFont("Courier", 15, 10));
	label.resize(300, 200);
	label.show();
	popup->exec();
}

void Gui::on_addAdminButton_clicked()
{
	QLineEdit* titleInput = qobject_cast<QLineEdit*>(sender()->parent()->findChild<QLineEdit*>("title"));
	QLineEdit* genreInput = qobject_cast<QLineEdit*>(sender()->parent()->findChild<QLineEdit*>("genre"));
	QLineEdit* yearOfReleaseInput = qobject_cast<QLineEdit*>(sender()->parent()->findChild<QLineEdit*>("yearOfRelease"));
	QLineEdit* likesInput = qobject_cast<QLineEdit*>(sender()->parent()->findChild<QLineEdit*>("likes"));
	QLineEdit* linkInput = qobject_cast<QLineEdit*>(sender()->parent()->findChild<QLineEdit*>("link"));

	if (!titleInput || !genreInput || !yearOfReleaseInput || !likesInput || !linkInput)
	{
		displayError("Error retrieving input fields");
		return;
	}

	std::string title = titleInput->text().toStdString();
	std::string genre = genreInput->text().toStdString();
	std::string yearOfReleaseStr = yearOfReleaseInput->text().toStdString();
	std::string likesStr = likesInput->text().toStdString();
	std::string link = linkInput->text().toStdString();

	// Validate yearOfRelease and likes
	int yearOfRelease;
	int likes;

	try {
		yearOfRelease = std::stoi(yearOfReleaseStr);
	}
	catch (const std::exception& e) {
		displayError("Invalid input for Year of Release. Please enter a valid integer.");
		return;
	}

	try {
		likes = std::stoi(likesStr);
	}
	catch (const std::exception& e) {
		displayError("Invalid input for Likes. Please enter a valid integer.");
		return;
	}

	try
	{
		adminService.addMovie(title, genre, yearOfRelease, likes, link);
		std::cout << "Successful add\n";
	}
	catch (const std::exception& e)
	{
		displayError(e.what());
		return;
	}

	QDialog* parentDialog = qobject_cast<QDialog*>(sender()->parent()->parent());
	if (parentDialog)
		parentDialog->close();
}

void Gui::on_removeAdminButton_clicked()
{
	std::string title = sender()->parent()->findChild<QLineEdit*>("title")->text().toStdString();
	std::string genre = sender()->parent()->findChild<QLineEdit*>("genre")->text().toStdString();
	try
	{
		adminService.removeMovie(title, genre);
		std::cout << "Successful remove\n";

	}
	catch (const std::exception& e)
	{
		displayError(e.what());
		QWidget* parentW = qobject_cast<QWidget*>(sender()->parent());
		parentW->close();
	}
	QWidget* parentW = qobject_cast<QWidget*>(sender()->parent()->parent());
	parentW->close();
}

void Gui::on_updateAdminButton_clicked()
{
	std::string oldTitle = sender()->parent()->findChild<QLineEdit*>("oldTitle")->text().toStdString();
	std::string oldGenre = sender()->parent()->findChild<QLineEdit*>("oldGenre")->text().toStdString();
	std::string newTitle = sender()->parent()->findChild<QLineEdit*>("newTitle")->text().toStdString();
	std::string newGenre = sender()->parent()->findChild<QLineEdit*>("newGenre")->text().toStdString();
	std::string newYearOfRelease = sender()->parent()->findChild<QLineEdit*>("newYearOfRelease")->text().toStdString();
	std::string newLikes = sender()->parent()->findChild<QLineEdit*>("newLikes")->text().toStdString();
	std::string newLink = sender()->parent()->findChild<QLineEdit*>("newLink")->text().toStdString();
	try {
		adminService.updateMovie(oldTitle, oldGenre, newTitle, newGenre, std::stoi(newYearOfRelease), std::stoi(newLikes), newLink);
		std::cout << "Successful update\n";
	}
	catch (std::exception& e)
	{
		displayError(e.what());
		QWidget* parentW = qobject_cast<QWidget*>(sender()->parent());
		parentW->close();
	}
	QWidget* parentWidget = qobject_cast<QWidget*>(sender()->parent()->parent());
	parentWidget->close();
}

void Gui::handleUserMode()
{
	QListWidget* item = qobject_cast<QListWidget*>(QObject::sender()); // Get the clicked item
	QString text = item->currentItem()->text();
	try {
		if (text.startsWith("1"))
			this->searchMovieByGenre();
		if (text.startsWith("2"))
			this->removeMovieFromWatchlist();
		if (text.startsWith("3"))
			this->displayWatchlist();
		if (text.startsWith("4"))
			this->saveWatchlistToFile();
		if (text.startsWith("5"))
			this->openWatchlist();
	}
	catch (std::exception& e) {

	}
}

void Gui::handleAdminMode()
{
	QListWidget* item = qobject_cast<QListWidget*>(QObject::sender()); // Get the clicked item
	QString text = item->currentItem()->text();
	try {
		if (text.startsWith("1"))
			this->addMovie();
		if (text.startsWith("2"))
			this->removeMovieFromAdmin();
		if (text.startsWith("3"))
			this->updateMovie();
		if (text.startsWith("4"))
			this->displayAllMovies();
	}
	catch (std::exception& e) {

	}

}