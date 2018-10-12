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

#ifndef PROFILEEDITOR_HPP
#define PROFILEEDITOR_HPP

#include <QDialog>
#include <QMessageBox>
#include <Models/Profile.hpp>

namespace Ui
{
    class ProfileEditor;
}

class ProfileEditor : public QDialog
{
    Q_OBJECT

signals:
    void newProfile(Profile);
    void editProfile(Profile, Profile);

public:
    explicit ProfileEditor(QWidget *parent = nullptr);
    explicit ProfileEditor(Profile profile, QWidget *parent = nullptr);
    ~ProfileEditor();
    Profile getNewProfile();
    Profile getOriginal();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ProfileEditor *ui;
    bool isEditing = false;
    Profile original;
    Profile fresh;

};

#endif // PROFILEEDITOR_HPP
