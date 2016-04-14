#include "lnativeeventfilter.h"
#include "lmsghandler.h"
#include <windows.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

LNativeEventFilter::LNativeEventFilter()
{
    _isBorderless = false;

    LMsgHandler *pMsgHandler = LMsgHandler::getInstance();
    connect(pMsgHandler, &LMsgHandler::registerBorderlessWin, this, [=](quint32 wId){
        _WinList.append(wId);
        _isBorderless = true;
    });
}

LNativeEventFilter::~LNativeEventFilter()
{

}

bool LNativeEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)

    MSG *msg = static_cast<MSG *>(message);

	// we cannot just use WS_POPUP style
	// WS_THICKFRAME: without this the window cannot be resized and so aero snap, de-maximizing and minimizing won't work
	// WS_SYSMENU: enables the context menu with the move, close, maximize, minize... commands (shift + right-click on the task bar item)
	// HOWEVER, this also enables the menu with the maximize buttons in the title bar, which will exist inside your client area and are clickable.
	// WS_CAPTION: enables aero minimize animation/transition
	// WS_MAXIMIZEBOX, WS_MINIMIZEBOX: enable minimize/maximize
	if (msg->message == WM_CREATE /*&& _isBorderless*/)
	{
		SetWindowLongPtr(msg->hwnd, GWL_STYLE, WS_POPUP | WS_THICKFRAME
			| WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);

		static const MARGINS shadow_state[2] = { { 0, 0, 0, 0 }, { 1, 1, 1, 1 } };
		DwmExtendFrameIntoClientArea(msg->hwnd, &shadow_state[1]);
	}

	// this kills the window frame and title bar we added with WS_THICKFRAME or WS_CAPTION.
	if (msg->message == WM_NCCALCSIZE /*&& _WinList.contains(quint32(msg->hwnd))*/)
	{
		*result = 0;
		return true;
	}

    return false;
}

