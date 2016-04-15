#include "lnativeeventfilter.h"
#include "lmsghandler.h"
#include <windows.h>

LNativeEventFilter::LNativeEventFilter()
{
    LMsgHandler *pMsgHandler = LMsgHandler::getInstance();
    connect(pMsgHandler, &LMsgHandler::registerBorderlessWin, this, [=](quint32 wId){
        _WinList.append(wId);
    });
}

LNativeEventFilter::~LNativeEventFilter()
{

}

bool LNativeEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)

    MSG *msg = static_cast<MSG *>(message);
	
	if (msg->message == WM_CREATE) {
		// 实现放入各自的构造函数中.
	}

	// this kills the window frame and title bar we added with WS_THICKFRAME or WS_CAPTION.
	if (msg->message == WM_NCCALCSIZE && _WinList.contains(quint32(msg->hwnd)))
	{
		*result = 0;
		return true;
	}

    return false;
}

