#include "lnativeeventfilter.h"
#include "lmsghandler.h"
#include <windows.h>

LNativeEventFilter::LNativeEventFilter() //: QObject(0)
{
    LMsgHandler *pMsgHandler = LMsgHandler::getInstance();
    //connect(pMsgHandler, &LMsgHandler::registerBorderlessWin, this, [=](quint32 wId){_WinList.append(wId);});
}

LNativeEventFilter::~LNativeEventFilter()
{

}

bool LNativeEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    MSG *msg = static_cast<MSG *>(message);

    /*if(_WinList.contains(quint32(msg->hwnd)))
    {*/
        if (msg->message == WM_CREATE)
        {
			HWND aaaaa = msg->hwnd;
            SetWindowLongPtr(msg->hwnd, GWL_STYLE,
                             WS_POPUP | WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);

        }

        if (msg->message == WM_NCCALCSIZE)
        {
            *result = 0;
            return true;
        }
    //}

		RECT winrect;
		GetWindowRect(msg->hwnd, &winrect);
		RECT rcClient;
		GetClientRect(msg->hwnd, &rcClient);

		const LONG border_width = 8;
		if (msg->message == WM_NCHITTEST) 
		{
			HWND aaaaa = msg->hwnd;
			int x = ((int)(short)LOWORD(msg->lParam));
			int y = ((int)(short)HIWORD(msg->lParam));


			int HIT_BORDER = 8;

			// left border
			if (x >= winrect.left && x < winrect.left + border_width) {
				*result = HTLEFT;
			}
			// right border
			if (x < winrect.right && x >= winrect.right - border_width) {
				*result = HTRIGHT;
			}
			// bottom border
			if (y < winrect.bottom && y >= winrect.bottom - border_width) {
				*result = HTBOTTOM;
			}
			// top border
			if (y >= winrect.top && y < winrect.top + border_width) {
				*result = HTTOP;
			}

			// bottom left corner
			if (x >= winrect.left && x < winrect.left + border_width &&
				y < winrect.bottom && y >= winrect.bottom - border_width) {
				*result =  HTBOTTOMLEFT;
			}
			// bottom right corner
			if (x < winrect.right && x >= winrect.right - border_width &&
				y < winrect.bottom && y >= winrect.bottom - border_width) {
				*result = HTBOTTOMRIGHT;
			}
			// top left corner
			if (x >= winrect.left && x < winrect.left + border_width &&
				y >= winrect.top && y < winrect.top + border_width) {
				*result = HTTOPLEFT;
			}
			// top right corner
			if (x < winrect.right && x >= winrect.right - border_width &&
				y >= winrect.top && y < winrect.top + border_width) {
				*result = HTTOPRIGHT;
			}


			//*result = HTCAPTION;

			return true;
		}

    return false;
}

