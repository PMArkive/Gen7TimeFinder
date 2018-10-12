/*
 * This file is part of Gen7TimeFinder
 * Copyright (C) 2018 by Admiral_Fish
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "ProfileSearcher.hpp"
#include "ui_ProfileSearcher.h"

ProfileSearcher::ProfileSearcher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProfileSearcher)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose, false);
    setAttribute(Qt::WA_DeleteOnClose);

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels(QStringList() << tr("Tick") << tr("Offset"));
    ui->tableView->setModel(model);

    qRegisterMetaType<QPair<u32, u32>>("QPair<u32, u32>");
}

ProfileSearcher::~ProfileSearcher()
{
    delete ui;
    delete model;
}

void ProfileSearcher::on_pushButtonSearch_clicked()
{
    model->removeRows(0, model->rowCount());
    ui->pushButtonSearch->setEnabled(false);
    ui->pushButtonCancel->setEnabled(true);

    QDateTime dateTime = ui->dateTimeEdit->dateTime();
    dateTime.setTimeSpec(Qt::UTC);
    u32 initialSeed = ui->lineEditInitialSeed->text().toUInt(nullptr, 16);
    u32 baseTick = ui->lineEditBaseTick->text().toUInt(nullptr, 16);
    u32 baseOffset = ui->lineEditBaseOffset->text().toUInt();
    u32 tickRange = ui->lineEditTickRange->text().toUInt();
    u32 offsetRange = ui->lineEditOffsetRange->text().toUInt();

    ProfileSearch *search = new ProfileSearch(dateTime, initialSeed, baseTick, baseOffset, tickRange, offsetRange);
    connect(search, &ProfileSearch::resultReady, this, &ProfileSearcher::addResult);
    connect(search, &ProfileSearch::updateProgress, this, &ProfileSearcher::updateProgressBar);
    connect(search, &ProfileSearch::finished, search, &QObject::deleteLater);
    connect(search, &ProfileSearch::finished, this, [ = ] { ui->pushButtonSearch->setEnabled(true); ui->pushButtonCancel->setEnabled(false); });
    connect(ui->pushButtonCancel, &QPushButton::clicked, search, &ProfileSearch::cancelSearch);

    ui->progressBar->setMaximum(search->maxProgress());
    search->start();
}

void ProfileSearcher::addResult(QPair<u32, u32> result)
{
    QList<QStandardItem *> item;
    item << new QStandardItem(QString::number(result.first, 16)) << new QStandardItem(QString::number(result.second));
    model->appendRow(item);
}

void ProfileSearcher::updateProgressBar(int num)
{
    ui->progressBar->setValue(num);
}

ProfileSearch::ProfileSearch(QDateTime start, u32 initialSeed, u32 baseTick, u32 baseOffset, u32 tickRange, u32 offsetRange)
{
    startDate = start;
    this->initialSeed = initialSeed;
    this->baseTick = baseTick;
    this->baseOffset = baseOffset;
    this->tickRange = tickRange;
    this->offsetRange = offsetRange;
    progress = 0;
    cancel = false;
}

void ProfileSearch::run()
{
    for (u32 tick = 0; tick <= tickRange; tick++)
    {
        for (u32 offset = 0; offset <= offsetRange; offset++)
        {
            if (cancel)
                return;

            // Plus offset
            u64 epochPlus = Utility::getCitraTime(startDate, baseOffset + offset);
            u32 valuesPlus[4] = { baseTick + tick, 0, static_cast<u32>(epochPlus & 0xffffffff), static_cast<u32>(epochPlus >> 32) };
            u32 seedPlus = Utility::calcInitialSeed(valuesPlus);
            if (seedPlus == initialSeed)
            {
                emit resultReady(QPair<u32, u32>(baseTick + tick, baseOffset + offset));
            }

            // Minus offset
            u64 epochMinus = Utility::getCitraTime(startDate, baseOffset - offset);
            u32 valuesMinus[4] = { baseTick - tick, 0, static_cast<u32>(epochMinus & 0xffffffff), static_cast<u32>(epochMinus >> 32) };
            u32 seedMinus = Utility::calcInitialSeed(valuesMinus);
            if (seedMinus == initialSeed)
            {
                emit resultReady(QPair<u32, u32>(baseTick - tick, baseOffset - offset));
            }
        }
        emit updateProgress(++progress);
    }
}

int ProfileSearch::maxProgress()
{
    return static_cast<int>(tickRange + 1);
}

void ProfileSearch::cancelSearch()
{
    cancel = true;
}

void ProfileSearcher::on_comboBox_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ui->lineEditBaseTick->setText("2b942c5");
    }
    else if (index == 1)
    {
        ui->lineEditBaseTick->setText("383e329");
    }
}
