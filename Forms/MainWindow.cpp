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
    delete stationaryView;
    //delete eventView;
    //delete wildView;
    delete idView;
}

void MainWindow::on_pushButtonProfileManager_clicked()
{
    ProfileManager *manager = new ProfileManager();
    connect(manager, &ProfileManager::updateProfiles, this, &MainWindow::updateProfiles);
    manager->show();
    manager->raise();
}

void MainWindow::on_comboBoxProfiles_currentIndexChanged(int index)
{
    if (index != -1)
    {
        auto profile = profiles[index];
        ui->labelProfileOffsetValue->setText(QString::number(profile.getOffset()));
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
    else if (frameStart > frameEnd)
    {
        QMessageBox error;
        error.setText(tr("Set end frame to be after start frame"));
        error.exec();
        return;
    }

    stationaryView->clear();
    ui->pushButtonStationarySearch->setEnabled(false);
    ui->pushButtonStationaryCancel->setEnabled(true);

    QVector<int> min = { ui->spinBoxStationaryMinHP->value(), ui->spinBoxStationaryMinAtk->value(), ui->spinBoxStationaryMinDef->value(),
                         ui->spinBoxStationaryMinSpA->value(), ui->spinBoxStationaryMinSpD->value(), ui->spinBoxStationaryMinSpe->value()
                       };
    QVector<int> max = { ui->spinBoxStationaryMaxHP->value(), ui->spinBoxStationaryMaxAtk->value(), ui->spinBoxStationaryMaxDef->value(),
                         ui->spinBoxStationaryMaxSpA->value(), ui->spinBoxStationaryMaxSpD->value(), ui->spinBoxStationaryMaxSpe->value()
                       };

    StationaryFilter filter(min, max, ui->comboBoxStationaryNature->currentIndex() - 1, ui->comboBoxStationaryHiddenPower->currentIndex() - 1,
                            ui->comboBoxStationaryAbility->currentIndex() - 1, ui->checkBoxStationaryShiny->isChecked());

    StationarySearcher *search = new StationarySearcher(start, end, frameStart, frameEnd, ui->checkBoxStationary3IVs->isChecked(),
            ui->checkBoxStationaryAbilityLock->isChecked() ? ui->comboBoxStationaryAbilityLock->currentIndex() : -1, ui->comboBoxStationarySynchNature->currentIndex() - 1,
            ui->comboBoxStationaryGenderRatio->currentData().toInt(), ui->checkBoxStationaryAlwaysSynch->isChecked(), ui->checkBoxStationaryShinyLock->isChecked(),
            profiles[ui->comboBoxProfiles->currentIndex()], filter);
    connect(search, &StationarySearcher::resultReady, this, &MainWindow::addStationaryFrame);
    connect(search, &StationarySearcher::updateProgress, this, &MainWindow::updateStationaryProgress);
    connect(search, &StationarySearcher::finished, search, &QObject::deleteLater);
    connect(search, &StationarySearcher::finished, this, [ = ] { ui->pushButtonStationarySearch->setEnabled(true); ui->pushButtonStationaryCancel->setEnabled(false); });
    connect(ui->pushButtonStationaryCancel, &QPushButton::clicked, search, &StationarySearcher::cancelSearch);

    ui->progressBarStationary->setMaximum(search->maxProgress());

    search->start();
}

void MainWindow::addStationaryFrame(QVector<StationaryModel> frames)
{
    stationaryView->addItems(frames);
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
    else if (frameStart > frameEnd)
    {
        QMessageBox error;
        error.setText(tr("Set end frame to be after start frame"));
        error.exec();
        return;
    }

    idView->clear();
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

    IDSearcher *search = new IDSearcher(start, end, frameStart, frameEnd, profiles[ui->comboBoxProfiles->currentIndex()], filter);
    connect(search, &IDSearcher::resultReady, this, &MainWindow::addIDFrame);
    connect(search, &IDSearcher::updateProgress, this, &MainWindow::updateIDProgess);
    connect(search, &IDSearcher::finished, search, &QObject::deleteLater);
    connect(search, &IDSearcher::finished, this, [ = ] { ui->pushButtonIDSearch->setEnabled(true); ui->pushButtonIDCancel->setEnabled(false); });
    connect(ui->pushButtonIDCancel, &QPushButton::clicked, search, &IDSearcher::cancelSearch);

    ui->progressBarID->setMaximum(search->maxProgress());

    search->start();
}

void MainWindow::addIDFrame(QVector<IDModel> frames)
{
    idView->addItems(frames);
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

    for (auto profile : profiles)
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
    stationaryView = new StationaryView();
    //eventView = new EventView();
    //wildView = new WildView();
    idView = new IDView();

    ui->tableViewStationary->setModel(stationaryView);
    ui->tableViewStationary->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableViewStationary->verticalHeader()->setVisible(false);

    //ui->tableViewEvent->setModel(eventView);
    ui->tableViewEvent->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableViewEvent->verticalHeader()->setVisible(false);

    //ui->tableViewWild->setModel(wildView);
    ui->tableViewWild->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableViewWild->verticalHeader()->setVisible(false);

    ui->tableViewID->setModel(idView);
    ui->tableViewID->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableViewID->verticalHeader()->setVisible(false);

    ui->comboBoxStationaryNature->addItems(Utility::getNatures());
    ui->comboBoxStationaryHiddenPower->addItems(Utility::getHiddenPowers());
    ui->comboBoxStationarySynchNature->addItems(Utility::getNatures());
    ui->comboBoxStationaryGenderRatio->addItems(Utility::getGenderRatios());

    ui->comboBoxStationaryGenderRatio->setItemData(0, 0);
    ui->comboBoxStationaryGenderRatio->setItemData(0, 126);
    ui->comboBoxStationaryGenderRatio->setItemData(0, 30);
    ui->comboBoxStationaryGenderRatio->setItemData(0, 62);
    ui->comboBoxStationaryGenderRatio->setItemData(0, 190);
    ui->comboBoxStationaryGenderRatio->setItemData(0, 224);
    ui->comboBoxStationaryGenderRatio->setItemData(0, 1);
    ui->comboBoxStationaryGenderRatio->setItemData(0, 2);

    qRegisterMetaType<QVector<IDModel>>("QVector<IDModel>");
    qRegisterMetaType<QVector<StationaryModel>>("QVector<StationaryModel>");
}
