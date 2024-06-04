#include "MovieListModel.h"

MovieListModel::MovieListModel(QObject* parent) : QAbstractTableModel{ parent }
{
}

void MovieListModel::setMovies(const std::vector<Movie>& movies)
{
	beginResetModel();
	this->movies = movies;
	endResetModel();
}

int MovieListModel::rowCount(const QModelIndex& parent) const
{
	return this->movies.size();
}

int MovieListModel::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant MovieListModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	Movie movie = this->movies[row];
	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(movie.getTitle());
		case 1:
			return QString::fromStdString(movie.getGenre());
		case 2:
			return QString::number(movie.getYearOfRelease());
		case 3:
			return QString::number(movie.getNrLikes());
		case 4:
			return QString::fromStdString(movie.getLink());
		default:
			break;
		}
	}
	return QVariant{};
}

QVariant MovieListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return "Title";
			case 1:
				return "Genre";
			case 2:
				return "ReleaseYear";
			case 3:
				return "Likes";
			case 4:
				return "Link";
			default:
				break;
			}
		}
	}
	return QVariant{};
}