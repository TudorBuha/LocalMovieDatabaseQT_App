#pragma once
#include <qabstractitemmodel.h>
#include "Movie.h"
#include <QAbstractTableModel>
#include <vector>

class MovieListModel :
    public QAbstractTableModel
{
    Q_OBJECT

public:
	explicit MovieListModel(QObject* parent = nullptr);
	void setMovies(const std::vector<Movie>& events);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
	std::vector<Movie> movies;

};

