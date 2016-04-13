#include "borderlesswindow.h"
#include "lnativeeventfilter.h"
#include "lmsghandler.h"

#include <QApplication>
#include <QAbstractEventDispatcher>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LNativeEventFilter *filter = new LNativeEventFilter;
    QAbstractEventDispatcher::instance()->installNativeEventFilter(filter);

    BorderlessWindow w;
    w.show();

    int result = a.exec();

    LMsgHandler::destroy();
    delete filter;

    return result;
}
