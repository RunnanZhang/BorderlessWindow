#include "lmsghandler.h"

LMsgHandler* LMsgHandler::m_Instance = Q_NULLPTR;

LMsgHandler::LMsgHandler(QObject *parent) : QObject(parent)
{

}

LMsgHandler::~LMsgHandler()
{

}

LMsgHandler* LMsgHandler::getInstance()
{
    if (Q_NULLPTR == m_Instance) {
        m_Instance = new LMsgHandler;
    }

    return m_Instance;
}

void LMsgHandler::destroy()
{
    if(m_Instance != Q_NULLPTR) {
        delete m_Instance;
        m_Instance = Q_NULLPTR;
    }
}
