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

#include "ProfileCalibrater.hpp"
#include "ui_ProfileCalibrater.h"

ProfileCalibrater::ProfileCalibrater(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProfileCalibrater)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose, false);
    setAttribute(Qt::WA_DeleteOnClose);

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels(QStringList() << tr("Tick") << tr("Offset"));
    ui->tableView->setModel(model);

    qRegisterMetaType<QPair<u32, u32>>("QPair<u32, u32>");
}

ProfileCalibrater::~ProfileCalibrater()
{
    delete ui;
    delete model;
}

void ProfileCalibrater::on_pushButtonSearch_clicked()
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

    auto *search = new ProfileSearcher(dateTime, initialSeed, baseTick, baseOffset, tickRange, offsetRange);
    auto *timer = new QTimer();

    connect(search, &ProfileSearcher::finished, timer, &QTimer::deleteLater);
    connect(search, &ProfileSearcher::finished, timer, &QTimer::stop);
    connect(search, &ProfileSearcher::finished, this, [ = ] { ui->pushButtonSearch->setEnabled(true); ui->pushButtonCancel->setEnabled(false); });
    connect(search, &ProfileSearcher::finished, this, [ = ] { updateResults(search->getResults(), search->currentProgress()); });
    connect(timer, &QTimer::timeout, this, [ = ] { updateResults(search->getResults(), search->currentProgress()); });
    connect(ui->pushButtonCancel, &QPushButton::clicked, search, &ProfileSearcher::cancelSearch);

    ui->progressBar->setMaximum(search->maxProgress());

    search->start();
    timer->start(1000);
}

void ProfileCalibrater::updateResults(QVector<QPair<u32, u32>> results, int val)
{
    for (const auto &result : results)
    {
        auto list = { new QStandardItem(QString::number(result.first, 16)), new QStandardItem(QString::number(result.second)) };
        model->appendRow(list);
    }

    ui->progressBar->setValue(val);
}

void ProfileCalibrater::on_comboBox_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ui->lineEditBaseOffset->setText("54");
        ui->lineEditBaseTick->setText("3532EA4");
    }
    else if (index == 1)
    {
        ui->lineEditBaseOffset->setText("55");
        ui->lineEditBaseTick->setText("41D9CB9");
    }
}
