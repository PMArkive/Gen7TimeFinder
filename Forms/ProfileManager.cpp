#include "ProfileManager.hpp"
#include "ui_ProfileManager.h"

ProfileManager::ProfileManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProfileManager)
{
    ui->setupUi(this);
    model = new ProfileView();

    model->setModel(Profile::loadProfileList());
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ProfileManager::~ProfileManager()
{
    delete ui;
    delete model;
}

void ProfileManager::on_pushButtonNew_clicked()
{
    ProfileEditor *dialog = new ProfileEditor();
    if (dialog->exec() == QDialog::Accepted)
    {
        //Profile profile = dialog->getNewProfile();
        //profile.saveProfile();
        //model->addItem(profile);
        emit updateProfiles();
    }
    delete dialog;
}

void ProfileManager::on_pushButtonEdit_clicked()
{
    int r = ui->tableView->currentIndex().row();

    if (r < 0)
    {
        QMessageBox error;
        error.setText(tr("Please select a profile."));
        error.exec();
        return;
    }

    ProfileEditor *dialog = new ProfileEditor(model->getProfile(r));
    if (dialog->exec() == QDialog::Accepted)
    {
        Profile profile = dialog->getNewProfile();
        profile.updateProfile(dialog->getOriginal());
        int r = ui->tableView->currentIndex().row();
        model->updateProfile(profile, r);
        emit updateProfiles();
    }
    delete dialog;
}

void ProfileManager::on_pushButtonDelete_clicked()
{
    int r = ui->tableView->currentIndex().row();

    if (r < 0)
    {
        QMessageBox error;
        error.setText(tr("Please select a profile."));
        error.exec();
        return;
    }

    Profile profile = model->getProfile(r);
    profile.deleteProfile();

    model->removeProfile(r);

    emit updateProfiles();
}

void ProfileManager::on_pushButtonDone_clicked()
{
    this->close();
}
