#include "borderlesswindow.h"
#include "ui_borderlesswindow.h"
#include "lmsghandler.h"
#include <windows.h>
#include <QDialog>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

BorderlessWindow::BorderlessWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BorderlessWindow)
{
    ui->setupUi(this);

	/* 虽然在之后的WM_CREATE里面已经设置了各种Style，这里其实已经无意义，但是此处必须设置，
	 * 相当于一个标志，告诉Qt我们是无边框的，否则frameGeometry的返回以及绘制区域都会出现错误.*/
    this->setWindowFlags(Qt::FramelessWindowHint);

    //LMsgHandler *pMsgHandler = LMsgHandler::getInstance();
    //emit pMsgHandler->registerBorderlessWin(0);

    //quint32 wId = (quint32)this->winId();

    //emit pMsgHandler->registerBorderlessWin(wId);

    connect(ui->pTitleBar, &LTitleBar::minRequested, this, &QWidget::showMinimized);
    connect(ui->pTitleBar, &LTitleBar::maxRequested, this, &QWidget::showMaximized);
    connect(ui->pTitleBar, &LTitleBar::closeRequested, this, &QWidget::close);
}

BorderlessWindow::~BorderlessWindow()
{
    delete ui;
}

void BorderlessWindow::on_pAddBtn_clicked()
{
	/*QWidget *w = new QWidget;
	w->show();*/
	BOOL composition_enabled = false;
	bool success = DwmIsCompositionEnabled(&composition_enabled) == S_OK;
	bool bbb =  composition_enabled && success;

	static const MARGINS shadow_state[2] = { { 0, 0, 0, 0 }, { 10, 10, 10, 10 } };
	static const MARGINS shadow_state2 = { 1, 1, 1, 1 };
	DwmExtendFrameIntoClientArea((HWND)this->winId(), &shadow_state2);
	// redraw frame
	//SetWindowPos((HWND)this->winId(), nullptr, 1, 1, 1, 1, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
}

bool BorderlessWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	const MSG *msg = static_cast<MSG*>(message);

	// WM_CREATE、WM_NCCALCSIZE这两消息在这里获取不到，只能在外面的过滤器才可以获取到.Fuck it.
	if (msg->message == WM_CREATE) {
		int a = 0;
	}
	if (msg->message == WM_NCCALCSIZE) {
		int a = 0;
	}

	if (msg->message == WM_NCHITTEST) {
		const int HIT_BORDER = 8;
		int xPos = ((int)(short)LOWORD(msg->lParam)) - this->frameGeometry().x();
		int yPos = ((int)(short)HIWORD(msg->lParam)) - this->frameGeometry().y();
		
		/* 1、下面的判断顺序不可改变。比如HTTOPLEFT包括Top，我们要保证优先级高的先执行.
		 * 2、每次必须return，不可最后return，因为除了这些情况，我们一定要返回false，让Qt自己处理，否则会影响其他控件的事件接收.*/
		if (xPos > 0 && xPos < HIT_BORDER && yPos > 0 && yPos < HIT_BORDER) {
			*result = HTTOPLEFT;
			return true;
		}
		if (xPos >(this->width() - HIT_BORDER) && xPos < (this->width() - 0) && yPos > 0 && yPos < HIT_BORDER) {
			*result = HTTOPRIGHT;
			return true;
		}
		if (xPos > 0 && xPos < HIT_BORDER && yPos >(this->height() - HIT_BORDER) && yPos < (this->height() - 0)) {
			*result = HTBOTTOMLEFT;
			return true;
		}
		if (xPos >(this->width() - HIT_BORDER) && xPos < (this->width() - 0) && yPos >(this->height() - HIT_BORDER) && yPos < (this->height() - 0)) {
			*result = HTBOTTOMRIGHT;
			return true;
		}
		if (xPos >= 0 && xPos < HIT_BORDER) {
			*result = HTLEFT;
			return true;
		}
		if (xPos >(this->width() - HIT_BORDER) && xPos < (this->width() - 0)) {
			*result = HTRIGHT;
			return true;
		}
		if (yPos >= 0 && yPos < HIT_BORDER) {
			*result = HTTOP;
			return true;
		}
		if (yPos >(this->height() - HIT_BORDER) && yPos < (this->height() - 0)) {
			*result = HTBOTTOM;
			return true;
		}

		// 相当于选中标题栏，用于移动操作.为了判断点击在哪个子窗体上，所以放在这里，没有在LNativeEventFilter中处理.
		if (this->childAt(xPos, yPos) == ui->pTitleBar) {
			*result = HTCAPTION;
			return true;
		}
	}
	return false;
}
