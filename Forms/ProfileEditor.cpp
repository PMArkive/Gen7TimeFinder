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

    fresh = Profile(input, ui->lineEditProfileOffset->text().toUInt(), ui->lineEditProfileTID->text().toUShort(),
                    ui->lineEditProfileSID->text().toUShort(), static_cast<Game>(ui->comboBoxProfileVersion->currentData().toInt()), ui->checkBoxShinyCharm->isChecked());

    done(QDialog::Accepted);
}

void ProfileEditor::on_buttonBox_rejected()
{
    done(QDialog::Rejected);
}
