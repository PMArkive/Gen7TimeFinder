#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMessageBox>
#include <Header/IDSearcher.hpp>
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
    void on_pushButtonIDSearch_clicked();
    void addIDFrame(QVector<IDModel> frames);
    void updateIDProgess(int val);
    void toggleIDEnable();

private:
    Ui::MainWindow *ui;
    IDView *idView;

};

#endif // MAINWINDOW_HPP
