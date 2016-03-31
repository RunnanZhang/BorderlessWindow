#include "borderlesswindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BorderlessWindow w;
    w.show();

    return a.exec();
}
