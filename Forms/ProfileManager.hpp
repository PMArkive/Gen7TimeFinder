#ifndef PROFILEMANAGER_HPP
#define PROFILEMANAGER_HPP

#include <QMainWindow>
#include <QMessageBox>
#include <Forms/ProfileEditor.hpp>
#include <Views/ProfileView.hpp>

namespace Ui
{
    class ProfileManager;
}

class ProfileManager : public QMainWindow
{
    Q_OBJECT

signals:
    void updateProfiles();

public:
    explicit ProfileManager(QWidget *parent = nullptr);
    ~ProfileManager();

private slots:
    void on_pushButtonNew_clicked();
    void on_pushButtonEdit_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonDone_clicked();

private:
    Ui::ProfileManager *ui;
    ProfileView *model;

};

#endif // PROFILEMANAGER_HPP
