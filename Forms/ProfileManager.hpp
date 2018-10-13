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

#ifndef PROFILEMANAGER_HPP
#define PROFILEMANAGER_HPP

#include <QMainWindow>
#include <QMessageBox>
#include <Core/Utility.hpp>
#include <Forms/ProfileEditor.hpp>
#include <Models/ProfileModel.hpp>

namespace Ui
{
    class ProfileManager;
}

class ProfileManager : public QMainWindow
{
    Q_OBJECT

signals:
    void updateProfiles();

public:
    explicit ProfileManager(QWidget *parent = nullptr);
    ~ProfileManager() override;

private slots:
    void on_pushButtonNew_clicked();
    void on_pushButtonEdit_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonDone_clicked();

private:
    Ui::ProfileManager *ui;
    ProfileModel *model;

};

#endif // PROFILEMANAGER_HPP
