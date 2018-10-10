#include <QApplication>
#include <QStyleFactory>
#include <Forms/MainWindow.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Gen7TimeFinder");
    a.setOrganizationName("Admiral-Fish");

#ifdef Q_OS_WIN
    a.setStyle(QStyleFactory::create("windowsvista"));
#endif

    MainWindow w;
    w.show();

    return a.exec();
}
