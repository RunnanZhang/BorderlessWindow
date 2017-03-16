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
	
	// this kills the window frame and title bar we added with WS_THICKFRAME or WS_CAPTION.
	if (msg->message == WM_NCCALCSIZE && _WinList.contains(quint32(msg->hwnd)))
	{

        // Correct window rectangle recomputation
        // https://github.com/telegramdesktop/tdesktop/blob/dev/Telegram/SourceFiles/platform/win/windows_event_filter.cpp

        WINDOWPLACEMENT wp;
        wp.length = sizeof(WINDOWPLACEMENT);
        if (GetWindowPlacement(msg->hwnd, &wp) && wp.showCmd == SW_SHOWMAXIMIZED) {
            LPNCCALCSIZE_PARAMS params = (LPNCCALCSIZE_PARAMS)msg->lParam;
            LPRECT r = (msg->wParam == TRUE) ? &params->rgrc[0] : (LPRECT)msg->lParam;
            HMONITOR hMonitor = MonitorFromPoint({ (r->left + r->right) / 2, (r->top + r->bottom) / 2 }, MONITOR_DEFAULTTONEAREST);

            if (hMonitor) {
                MONITORINFO mi;
                mi.cbSize = sizeof(mi);
                if (GetMonitorInfo(hMonitor, &mi)) {
                    *r = mi.rcWork;
                }
            }
        }
        if (result) *result = 0;
        return true;
	}

    return false;
}

