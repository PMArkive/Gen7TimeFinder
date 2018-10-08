#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QVector>
#include <Core/IDSearcher.hpp>
#include <Core/IDFilter.hpp>
#include <Core/StationarySearcher.hpp>
#include <Core/Utility.hpp>
#include <Forms/ProfileManager.hpp>
#include <Views/StationaryView.hpp>
#include <Views/IDView.hpp>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonProfileManager_clicked();
    void on_comboBoxProfiles_currentIndexChanged(int index);
    void on_pushButtonStationarySearch_clicked();
    void addStationaryFrame(QVector<StationaryModel> frames);
    void updateStationaryProgress(int val);
    void on_pushButtonIDSearch_clicked();
    void addIDFrame(QVector<IDModel> frames);
    void updateIDProgess(int val);
    void updateProfiles();

private:
    Ui::MainWindow *ui;
    StationaryView *stationaryView;
    //EventView *eventView;
    //WildView *wildView;
    IDView *idView;
    QVector<Profile> profiles;

    void createProfileXML();
    void setupModel();

};

#endif // MAINWINDOW_HPP
