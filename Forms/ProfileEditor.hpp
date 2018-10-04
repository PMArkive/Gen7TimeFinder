#ifndef PROFILEEDITOR_HPP
#define PROFILEEDITOR_HPP

#include <QDialog>
#include <QMessageBox>
#include <Models/Profile.hpp>

namespace Ui
{
    class ProfileEditor;
}

class ProfileEditor : public QDialog
{
    Q_OBJECT

signals:
    void newProfile(Profile);
    void editProfile(Profile, Profile);

public:
    explicit ProfileEditor(QWidget *parent = nullptr);
    explicit ProfileEditor(Profile profile, QWidget *parent = nullptr);
    ~ProfileEditor();
    Profile getNewProfile();
    Profile getOriginal();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ProfileEditor *ui;
    bool isEditing = false;
    Profile original;
    Profile fresh;

};

#endif // PROFILEEDITOR_HPP
