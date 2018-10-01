#ifndef IDVIEW_HPP
#define IDVIEW_HPP

#include <QAbstractTableModel>
#include <QVector>
#include <Models/IDModel.hpp>

class IDView : public QAbstractTableModel
{

private:
    QVector<IDModel> model;

public:
    IDView(QObject *parent = nullptr);
    void addItems(QVector<IDModel> frames);
    void clear();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

};

#endif // IDVIEW_HPP
