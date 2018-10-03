#include "StationaryView.hpp"

StationaryView::StationaryView(QObject *parent) : QAbstractTableModel(parent)
{
}

void StationaryView::addItems(QVector<StationaryModel> frames)
{
    int i = rowCount();
    emit beginInsertRows(QModelIndex(), i, i + frames.size() - 1);
    model.append(frames);
    emit endInsertRows();
}

void StationaryView::clear()
{
    if (model.empty())
        return;
    emit beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    model.clear();
    model.squeeze();
    emit endRemoveRows();
}

int StationaryView::rowCount(const QModelIndex &parent) const
{
    (void) parent;
    return model.size();
}

int StationaryView::columnCount(const QModelIndex &parent) const
{
    (void) parent;
    return 15;
}

QVariant StationaryView::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        StationaryModel frame = model[index.row()];
        switch (index.column())
        {
            case 0:
                return frame.getDateTime();
            case 1:
                return QString::number(frame.getSeed(), 16).toUpper();
            case 2:
                return frame.getFrame();
            case 3:
                return frame.getIV(0);
            case 4:
                return frame.getIV(1);
            case 5:
                return frame.getIV(2);
            case 6:
                return frame.getIV(3);
            case 7:
                return frame.getIV(4);
            case 8:
                return frame.getIV(5);
            case 9:
                return Utility::getNature(frame.getNature());
            case 10:
                return frame.getSynch();
            case 11:
                return Utility::getHiddenPower(frame.getHiddenPower());
            case 12:
                return frame.getPSV();
            case 13:
                return "TODO";
            case 14:
                return "TODO";
        }
    }
    return QVariant();
}

QVariant StationaryView::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0:
                return tr("Date/Time");
            case 1:
                return tr("Initial Seed");
            case 2:
                return tr("Frame");
            case 3:
                return tr("HP");
            case 4:
                return tr("Atk");
            case 5:
                return tr("Def");
            case 6:
                return tr("SpA");
            case 7:
                return tr("SpD");
            case 8:
                return tr("Spe");
            case 9:
                return tr("Nature");
            case 10:
                return tr("Sync");
            case 11:
                return tr("HP Type");
            case 12:
                return tr("PSV");
            case 13:
                return tr("Gender");
            case 14:
                return tr("Ability");
        }
    }
    return QVariant();
}
