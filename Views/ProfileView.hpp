#ifndef PROFILEVIEW_HPP
#define PROFILEVIEW_HPP

#include <QAbstractTableModel>
#include <QVector>
#include <Models/Profile.hpp>

class ProfileView : public QAbstractTableModel
{

private:
    QVector<Profile> model;

public:
    ProfileView(QObject *parent = nullptr);
    void setModel(QVector<Profile> profiles);
    void addItem(Profile profile);
    void updateProfile(Profile profile, int row);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Profile getProfile(int index);
    void removeProfile(int index);

};

#endif // PROFILEVIEW_HPP
