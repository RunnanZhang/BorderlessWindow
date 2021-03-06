/*
 * 原始事件过滤器类.用于接收最原始的windows消息.
*/
#ifndef LNATIVEEVENTFILTER_H
#define LNATIVEEVENTFILTER_H

#include <QObject>
#include <QList>
#include <QAbstractNativeEventFilter>

class LNativeEventFilter : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    LNativeEventFilter();
    ~LNativeEventFilter();
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);

private:
    QList<quint32> _WinList;
};

#endif // LNATIVEEVENTFILTER_H
