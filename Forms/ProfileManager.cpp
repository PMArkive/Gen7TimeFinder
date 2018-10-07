#include "ProfileManager.hpp"
#include "ui_ProfileManager.h"

ProfileManager::ProfileManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProfileManager)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose, false);
    setAttribute(Qt::WA_DeleteOnClose);

    model = new ProfileView();
    model->setModel(Utility::loadProfileList());
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
        Profile profile = dialog->getNewProfile();
        Utility::saveProfile(profile);
        model->addItem(profile);
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
        Utility::updateProfile(dialog->getOriginal(), profile);
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

    Utility::deleteProfile(model->getProfile(r));
    model->removeProfile(r);
    emit updateProfiles();
}

void ProfileManager::on_pushButtonDone_clicked()
{
    this->close();
}
