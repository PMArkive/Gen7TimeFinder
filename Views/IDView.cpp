#include "IDView.hpp"

IDView::IDView(QObject *parent) : QAbstractTableModel(parent)
{
}

void IDView::addItems(QVector<IDModel> frames)
{
    int i = rowCount();
    emit beginInsertRows(QModelIndex(), i, i + frames.size() - 1);
    model.append(frames);
    emit endInsertRows();
}

void IDView::clear()
{
    if (model.empty())
        return;
    emit beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    model.clear();
    model.squeeze();
    emit endRemoveRows();
}

int IDView::rowCount(const QModelIndex &parent) const
{
    (void) parent;
    return model.size();
}

int IDView::columnCount(const QModelIndex &parent) const
{
    (void) parent;
    return 6;
}

QVariant IDView::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        IDModel frame = model[index.row()];
        switch (index.column())
        {
            case 0:
                return frame.getDateTime();
            case 1:
                return frame.getFrame();
            case 2:
                return frame.getDisplayTID();
            case 3:
                return frame.getTID();
            case 4:
                return frame.getSID();
            case 5:
                return frame.getTSV();
        }
    }
    return QVariant();
}

QVariant IDView::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0:
                return tr("Date/Time");
            case 1:
                return tr("Frame");
            case 2:
                return tr("G7 TID");
            case 3:
                return tr("TID");
            case 4:
                return tr("SID");
            case 5:
                return tr("TSV");
        }
    }
    return QVariant();
}
