#ifndef STATIONARYVIEW_HPP
#define STATIONARYVIEW_HPP

#include <QAbstractTableModel>
#include <QVector>
#include <Core/Utility.hpp>
#include <Models/StationaryModel.hpp>

class StationaryView : public QAbstractTableModel
{

private:
    QVector<StationaryModel> model;

public:
    StationaryView(QObject *parent = nullptr);
    void addItems(QVector<StationaryModel> frames);
    void clear();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

};

#endif // STATIONARYVIEW_HPP
