#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stationaryView = new StationaryView();
    //eventView = new EventView();
    //wildView = new WildView();
    idView = new IDView();

    ui->tableViewStationary->setModel(stationaryView);
    ui->tableViewStationary->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewStationary->verticalHeader()->setVisible(false);

    //ui->tableViewEvent->setModel(eventView);
    ui->tableViewEvent->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewEvent->verticalHeader()->setVisible(false);

    //ui->tableViewWild->setModel(wildView);
    ui->tableViewWild->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewWild->verticalHeader()->setVisible(false);

    ui->tableViewID->setModel(idView);
    ui->tableViewID->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewID->verticalHeader()->setVisible(false);

    qRegisterMetaType<QVector<IDModel>>("QVector<IDModel>");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete stationaryView;
    //delete eventView;
    //delete wildView;
    delete idView;
}

void MainWindow::on_pushButtonStationarySearch_clicked()
{
    // TODO
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

    QVector<QPair<u32, u32>> filter;
    if (!ui->textEditIDFilter->toPlainText().isEmpty())
    {
        for (QString in : ui->textEditIDFilter->toPlainText().split("\n"))
        {
            QPair<u32, u32> pair;
            if (filterType == 2)
            {
                QStringList split = in.split("/");
                pair.first = split[0].toUInt();
                pair.second = split[1].toUInt();
            }
            else
            {
                pair.first = in.toUInt();
                pair.second = 0;
            }
            filter.append(pair);
        }
    }

    QVector<u32> tsv;
    if (!ui->textEditTSVFilter->toPlainText().isEmpty())
    {
        for (QString in : ui->textEditTSVFilter->toPlainText().split("\n"))
        {
            tsv.append(in.toUInt());
        }
    }

    IDSearcher *search = new IDSearcher(start, end, frameStart, frameEnd, 0x383e329, IDFilter(filter, tsv, filterType));
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
