#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    idView = new IDView();

    ui->tableViewID->setModel(idView);
    ui->tableViewID->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    qRegisterMetaType<QVector<IDModel>>("QVector<IDModel>");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete idView;
}

#include <QDebug>

void MainWindow::on_pushButtonIDSearch_clicked()
{
    QDateTime start = ui->dateTimeEditIDStart->dateTime();
    QDateTime end = ui->dateTimeEditIDEnd->dateTime();
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

    IDSearcher *search = new IDSearcher(start, end, frameStart, frameEnd, 0x383e329, filter, tsv, filterType);
    connect(search, &IDSearcher::resultReady, this, &MainWindow::addIDFrame);
    connect(search, &IDSearcher::updateProgress, this, &MainWindow::updateIDProgess);
    connect(search, &IDSearcher::finished, search, &QObject::deleteLater);
    connect(search, &IDSearcher::finished, this, &MainWindow::toggleIDEnable);
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

void MainWindow::toggleIDEnable()
{
    ui->pushButtonIDSearch->setEnabled(true);
    ui->pushButtonIDCancel->setEnabled(false);
}
