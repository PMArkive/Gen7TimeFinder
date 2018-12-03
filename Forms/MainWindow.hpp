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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>
#include <QVector>
#include <Core/IDFilter.hpp>
#include <Core/IDSearcher.hpp>
#include <Core/StationarySearcher.hpp>
#include <Core/Utility.hpp>
#include <Forms/ProfileCalibrater.hpp>
#include <Forms/ProfileManager.hpp>
#include <Models/StationaryModel.hpp>
#include <Models/IDModel.hpp>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_pushButtonProfileManager_clicked();
    void on_comboBoxProfiles_currentIndexChanged(int index);
    void on_pushButtonStationarySearch_clicked();
    void updateStationary(const QVector<StationaryResult> &frames, int val);
    void on_pushButtonIDSearch_clicked();
    void updateID(const QVector<IDResult> &frames, int val);
    void updateProfiles();
    void on_actionCalibrate_Profile_triggered();

private:
    Ui::MainWindow *ui;
    StationaryModel *stationaryModel;
    //EventModel *eventModel;
    //WildModel *wildModel;
    IDModel *idModel;
    QVector<Profile> profiles;

    void checkProfileJson();
    void setupModel();

};

#endif // MAINWINDOW_HPP
