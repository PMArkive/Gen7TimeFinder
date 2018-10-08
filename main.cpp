#include <QApplication>
#include <Forms/MainWindow.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Gen7TimeFinder");
    a.setOrganizationName("Admiral-Fish");

    MainWindow w;
    w.show();

    return a.exec();
}
