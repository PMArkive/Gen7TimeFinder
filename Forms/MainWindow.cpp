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

#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file(QApplication::applicationDirPath() + "/profiles.xml");
    if (!file.exists())
        createProfileXML();

    setupModel();
    updateProfiles();
}

MainWindow::~MainWindow()
{
    QSettings settings;
    settings.setValue("profile", ui->comboBoxProfiles->currentIndex());

    delete ui;
    delete stationaryModel;
    //delete eventModel;
    //delete wildModel;
    delete idModel;
}

void MainWindow::on_pushButtonProfileManager_clicked()
{
    auto *manager = new ProfileManager();
    connect(manager, &ProfileManager::updateProfiles, this, &MainWindow::updateProfiles);
    manager->show();
    manager->raise();
}

void MainWindow::on_comboBoxProfiles_currentIndexChanged(int index)
{
    if (index != -1)
    {
        auto profile = profiles.at(index);
        ui->labelProfileOffsetValue->setText(QString::number(profile.getOffset()));
        ui->labelProfileTickValue->setText(QString::number(profile.getTick(), 16));
        ui->labelProfileTIDValue->setText(QString::number(profile.getTID()));
        ui->labelProfileSIDValue->setText(QString::number(profile.getSID()));
        ui->labelProfileGameValue->setText(profile.getVersionString());
        ui->labelProfileShinyCharmValue->setText(profile.getShinyCharm() ? "Yes" : "No");
    }
}

void MainWindow::on_pushButtonStationarySearch_clicked()
{
    QDateTime start = ui->dateTimeEditStationaryStartDate->dateTime();
    QDateTime end = ui->dateTimeEditStationaryEndDate->dateTime();
    u32 frameStart = ui->lineEditStationaryStartFrame->text().toUInt();
    u32 frameEnd = ui->lineEditStationaryEndFrame->text().toUInt();

    if (start > end)
    {
        QMessageBox error;
        error.setText(tr("Set end date to be after start date."));
        error.exec();
        return;
    }
    if (frameStart > frameEnd)
    {
        QMessageBox error;
        error.setText(tr("Set end frame to be after start frame"));
        error.exec();
        return;
    }

    stationaryModel->clear();
    ui->pushButtonStationarySearch->setEnabled(false);
    ui->pushButtonStationaryCancel->setEnabled(true);

    QVector<int> min = { ui->spinBoxStationaryMinHP->value(), ui->spinBoxStationaryMinAtk->value(), ui->spinBoxStationaryMinDef->value(),
                         ui->spinBoxStationaryMinSpA->value(), ui->spinBoxStationaryMinSpD->value(), ui->spinBoxStationaryMinSpe->value()
                       };
    QVector<int> max = { ui->spinBoxStationaryMaxHP->value(), ui->spinBoxStationaryMaxAtk->value(), ui->spinBoxStationaryMaxDef->value(),
                         ui->spinBoxStationaryMaxSpA->value(), ui->spinBoxStationaryMaxSpD->value(), ui->spinBoxStationaryMaxSpe->value()
                       };

    StationaryFilter filter(min, max, ui->comboBoxStationaryNature->currentIndex() - 1, ui->comboBoxStationaryHiddenPower->currentIndex() - 1,
                            ui->comboBoxStationaryAbility->currentIndex() - 1, ui->checkBoxStationaryShiny->isChecked(), ui->comboBoxStationaryGender->currentIndex());

    auto *search = new StationarySearcher(start, end, frameStart, frameEnd, ui->checkBoxStationary3IVs->isChecked(),
                                          ui->checkBoxStationaryAbilityLock->isChecked() ? ui->comboBoxStationaryAbilityLock->currentIndex() : -1, ui->comboBoxStationarySynchNature->currentIndex() - 1,
                                          ui->comboBoxStationaryGenderRatio->currentData().toInt(), ui->checkBoxStationaryAlwaysSynch->isChecked(), ui->checkBoxStationaryShinyLock->isChecked(),
                                          profiles[ui->comboBoxProfiles->currentIndex()], filter);
    auto *timer = new QTimer();

    connect(search, &StationarySearcher::finished, search, &QObject::deleteLater);
    connect(search, &StationarySearcher::finished, timer, &QTimer::deleteLater);
    connect(search, &StationarySearcher::finished, timer, &QTimer::stop);
    connect(search, &StationarySearcher::finished, this, [ = ] { updateStationaryProgress(search->currentProgress()); });
    connect(search, &StationarySearcher::finished, this, [ = ] { ui->pushButtonStationarySearch->setEnabled(true); ui->pushButtonStationaryCancel->setEnabled(false); });
    connect(timer, &QTimer::timeout, this, [ = ] { addStationaryFrames(search->getResults()); });
    connect(timer, &QTimer::timeout, this, [ = ] { updateStationaryProgress(search->currentProgress()); });
    connect(ui->pushButtonStationaryCancel, &QPushButton::clicked, search, &StationarySearcher::cancelSearch);

    ui->progressBarStationary->setMaximum(search->maxProgress());

    search->start();
    timer->start(1000);
}

void MainWindow::addStationaryFrames(const QVector<StationaryResult> &frames)
{
    if (!frames.isEmpty())
        stationaryModel->addItems(frames);
}

void MainWindow::updateStationaryProgress(int val)
{
    ui->progressBarStationary->setValue(val);
}

void MainWindow::on_pushButtonIDSearch_clicked()
{
    QDateTime start = ui->dateTimeEditIDStartDate->dateTime();
    QDateTime end = ui->dateTimeEditIDEndDate->dateTime();
    u32 frameStart = ui->lineEditIDStartFrame->text().toUInt();
    u32 frameEnd = ui->lineEditIDEndFrame->text().toUInt();

    if (start > end)
    {
        QMessageBox error;
        error.setText(tr("Set end date to be after start date."));
        error.exec();
        return;
    }
    if (frameStart > frameEnd)
    {
        QMessageBox error;
        error.setText(tr("Set end frame to be after start frame"));
        error.exec();
        return;
    }

    idModel->clear();
    ui->pushButtonIDSearch->setEnabled(false);
    ui->pushButtonIDCancel->setEnabled(true);

    int filterType;
    if (ui->radioButtonIDTID->isChecked())
        filterType = 0;
    else if (ui->radioButtonIDSID->isChecked())
        filterType = 1;
    else if (ui->radioButtonIDTIDSID->isChecked())
        filterType = 2;
    else
        filterType = 3;

    IDFilter filter(ui->textEditIDFilter->toPlainText(), ui->textEditTSVFilter->toPlainText(), filterType);

    auto *search = new IDSearcher(start, end, frameStart, frameEnd, profiles[ui->comboBoxProfiles->currentIndex()], filter);
    auto *timer = new QTimer();

    connect(search, &IDSearcher::finished, search, &QObject::deleteLater);
    connect(search, &IDSearcher::finished, timer, &QTimer::deleteLater);
    connect(search, &IDSearcher::finished, timer, &QTimer::stop);
    connect(search, &IDSearcher::finished, this, [ = ] { updateIDProgess(search->currentProgress()); });
    connect(search, &IDSearcher::finished, this, [ = ] { ui->pushButtonIDSearch->setEnabled(true); ui->pushButtonIDCancel->setEnabled(false); });
    connect(timer, &QTimer::timeout, this, [ = ] { addIDFrames(search->getResults()); });
    connect(timer, &QTimer::timeout, this, [ = ] { updateIDProgess(search->currentProgress()); });
    connect(ui->pushButtonIDCancel, &QPushButton::clicked, search, &IDSearcher::cancelSearch);

    ui->progressBarID->setMaximum(search->maxProgress());

    search->start();
    timer->start(1000);
}

void MainWindow::addIDFrames(const QVector<IDResult> &frames)
{
    if (!frames.isEmpty())
        idModel->addItems(frames);
}

void MainWindow::updateIDProgess(int val)
{
    ui->progressBarID->setValue(val);
}

void MainWindow::updateProfiles()
{
    profiles = Utility::loadProfileList();
    profiles.insert(profiles.begin(), Profile());

    ui->comboBoxProfiles->clear();

    for (const auto &profile : profiles)
        ui->comboBoxProfiles->addItem(profile.getName());

    QSettings setting;
    int val = setting.value("profile").toInt();
    if (val < ui->comboBoxProfiles->count())
        ui->comboBoxProfiles->setCurrentIndex(val);
}

void MainWindow::createProfileXML()
{
    QFile file(QApplication::applicationDirPath() + "/profiles.xml");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QDomDocument doc;
        QDomElement profiles = doc.createElement(QString("Profiles"));
        doc.appendChild(profiles);
        QTextStream stream(&file);
        stream << doc.toString();
        file.close();
    }
}

void MainWindow::setupModel()
{
    stationaryModel = new StationaryModel();
    //eventModel = new EventModel();
    //wildModel = new WildModel();
    idModel = new IDModel();

    ui->tableViewStationary->setModel(stationaryModel);
    ui->tableViewStationary->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableViewStationary->verticalHeader()->setVisible(false);

    //ui->tableViewEvent->setModel(eventModel);
    ui->tableViewEvent->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableViewEvent->verticalHeader()->setVisible(false);

    //ui->tableViewWild->setModel(wildModel);
    ui->tableViewWild->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableViewWild->verticalHeader()->setVisible(false);

    ui->tableViewID->setModel(idModel);
    ui->tableViewID->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableViewID->verticalHeader()->setVisible(false);

    ui->comboBoxStationaryNature->addItems(Utility::getNatures());
    ui->comboBoxStationaryHiddenPower->addItems(Utility::getHiddenPowers());
    ui->comboBoxStationarySynchNature->addItems(Utility::getNatures());
    ui->comboBoxStationaryGenderRatio->addItems(Utility::getGenderRatios());

    ui->comboBoxStationaryGenderRatio->setItemData(0, 0);
    ui->comboBoxStationaryGenderRatio->setItemData(1, 126);
    ui->comboBoxStationaryGenderRatio->setItemData(2, 30);
    ui->comboBoxStationaryGenderRatio->setItemData(3, 62);
    ui->comboBoxStationaryGenderRatio->setItemData(4, 190);
    ui->comboBoxStationaryGenderRatio->setItemData(5, 224);
    ui->comboBoxStationaryGenderRatio->setItemData(6, 1);
    ui->comboBoxStationaryGenderRatio->setItemData(7, 2);

    qRegisterMetaType<QVector<IDResult>>("QVector<IDResult>");
    qRegisterMetaType<QVector<StationaryResult>>("QVector<StationaryResult>");
}

void MainWindow::on_actionCalibrate_Profile_triggered()
{
    auto *searcher = new ProfileSearcher();
    searcher->show();
    searcher->raise();
}
