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

#include "ProfileEditor.hpp"
#include "ui_ProfileEditor.h"

ProfileEditor::ProfileEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileEditor)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose, false);
    setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);

    ui->comboBoxProfileVersion->setItemData(0, Game::Sun);
    ui->comboBoxProfileVersion->setItemData(1, Game::Moon);
    ui->comboBoxProfileVersion->setItemData(2, Game::UltraSun);
    ui->comboBoxProfileVersion->setItemData(3, Game::UltraMoon);
}

ProfileEditor::ProfileEditor(Profile profile, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileEditor)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose, false);
    setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);

    ui->comboBoxProfileVersion->setItemData(0, Game::Sun);
    ui->comboBoxProfileVersion->setItemData(1, Game::Moon);
    ui->comboBoxProfileVersion->setItemData(2, Game::UltraSun);
    ui->comboBoxProfileVersion->setItemData(3, Game::UltraMoon);

    ui->lineEditProfileName->setText(profile.getName());
    ui->comboBoxProfileVersion->setCurrentIndex(ui->comboBoxProfileVersion->findData(profile.getVersion()));
    ui->lineEditProfileOffset->setText(QString::number(profile.getOffset()));
    ui->lineEditProfileTick->setText(QString::number(profile.getTick(), 16));
    ui->lineEditProfileTID->setText(QString::number(profile.getTID()));
    ui->lineEditProfileSID->setText(QString::number(profile.getSID()));
    ui->checkBoxShinyCharm->setChecked(profile.getShinyCharm());

    isEditing = true;
    original = profile;
}

ProfileEditor::~ProfileEditor()
{
    delete ui;
}

Profile ProfileEditor::getNewProfile()
{
    return fresh;
}

Profile ProfileEditor::getOriginal()
{
    return original;
}

void ProfileEditor::on_buttonBox_accepted()
{
    QString input = ui->lineEditProfileName->text().trimmed();
    if (input == "")
    {
        QMessageBox error;
        error.setText(tr("Enter a Profile Name."));
        error.exec();
        return;
    }

    fresh = Profile(input, ui->lineEditProfileOffset->text().toUInt(), ui->lineEditProfileTick->text().toUInt(nullptr, 16), ui->lineEditProfileTID->text().toUShort(),
                    ui->lineEditProfileSID->text().toUShort(), static_cast<Game>(ui->comboBoxProfileVersion->currentData().toInt()), ui->checkBoxShinyCharm->isChecked());

    done(QDialog::Accepted);
}

void ProfileEditor::on_buttonBox_rejected()
{
    done(QDialog::Rejected);
}
