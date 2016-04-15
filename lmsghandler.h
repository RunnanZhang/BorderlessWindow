/*
 * 消息管理类.在此定义信号，用于各类的通信.
*/
#ifndef LMSGHANDLER_H
#define LMSGHANDLER_H

#include <QObject>

class LMsgHandler : public QObject
{
    Q_OBJECT

public:
    static LMsgHandler* getInstance();
    static void destroy();

private:
    LMsgHandler(QObject *parent = 0);
    ~LMsgHandler();
    LMsgHandler(const LMsgHandler &other);
    LMsgHandler& operator=(const LMsgHandler &other);

    static LMsgHandler *m_Instance;

signals:
    void registerBorderlessWin(quint32 wId);
};

#endif // LMSGHANDLER_H
