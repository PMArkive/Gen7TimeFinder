#include "ProfileView.hpp"

ProfileView::ProfileView(QObject *parent) : QAbstractTableModel(parent)
{
}

void ProfileView::setModel(QVector<Profile> profiles)
{
    if (profiles.empty())
        return;
    int i = rowCount();
    emit beginInsertRows(QModelIndex(), i, i + profiles.size() - 1);
    model.append(profiles);
    emit endInsertRows();
}

void ProfileView::addItem(Profile profile)
{
    int i = rowCount();
    emit beginInsertRows(QModelIndex(), i, i);
    model.push_back(profile);
    emit endInsertRows();
}

void ProfileView::updateProfile(Profile profile, int row)
{
    model[row] = profile;
    emit dataChanged(index(row, 0), index(row, columnCount()));
}

int ProfileView::rowCount(const QModelIndex &parent) const
{
    (void) parent;
    return model.size();
}

int ProfileView::columnCount(const QModelIndex &parent) const
{
    (void) parent;
    return 6;
}

QVariant ProfileView::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        Profile profile = model[index.row()];
        switch (index.column())
        {
            case 0:
                return profile.getName();
            case 1:
                return profile.getVersionString();
            case 2:
                return profile.getTID();
            case 3:
                return profile.getSID();
            case 4:
                return profile.getShinyCharm() ? "Yes" : "No";
            case 5:
                return profile.getOffset();
        }
    }
    return QVariant();
}

QVariant ProfileView::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0:
                return tr("Profile Name");
            case 1:
                return tr("Version");
            case 2:
                return tr("TID");
            case 3:
                return tr("SID");
            case 4:
                return tr("Shiny Charm");
            case 5:
                return tr("Offset");
        }
    }
    return QVariant();
}

Profile ProfileView::getProfile(int index)
{
    return model[index];
}

void ProfileView::removeProfile(int index)
{
    emit beginRemoveRows(QModelIndex(), index, index);
    model.erase(model.begin() + index);
    model.squeeze();
    emit endRemoveRows();
}
