#include "borderlesswindow.h"
#include "ui_borderlesswindow.h"
#include "lmsghandler.h"
#include <windows.h>

BorderlessWindow::BorderlessWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BorderlessWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    quint32 wId = (quint32)this->winId();
    LMsgHandler *pMsgHandler = LMsgHandler::getInstance();
    emit pMsgHandler->registerBorderlessWin(wId);
}

BorderlessWindow::~BorderlessWindow()
{
    delete ui;
}

bool BorderlessWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	const MSG *msg = static_cast<MSG*>(message);


	if (msg->message == WM_CREATE)
	{
		int a = 0;
	}

	if (msg->message == WM_NCHITTEST)
	{
		int a = 0;
	}

	if (msg->message == WM_NCHITTEST) {
		int xPos = ((int)(short)LOWORD(msg->lParam)) - this->frameGeometry().x();
		int yPos = ((int)(short)HIWORD(msg->lParam)) - this->frameGeometry().y();

		//int xPos = ((int)(short)LOWORD(msg->lParam)) - this->geometry().x();
		//int yPos = ((int)(short)HIWORD(msg->lParam)) - this->geometry().y();

		QRect aa = this->frameGeometry();
		QRect bb = this->geometry();

		if (this->childAt(xPos, yPos) == 0) {
			*result = HTCAPTION; //相当于选中标题栏，用于移动操作.
		}
		else {
			return false;
		}

		int HIT_BORDER = 8;

		if (xPos >= 0 && xPos < HIT_BORDER) {
			*result = HTLEFT;
		}
		if (xPos >(this->width() - HIT_BORDER) && xPos < (this->width() - 0)) {
			*result = HTRIGHT;
		}
		if (yPos >= 0 && yPos < HIT_BORDER) {
			*result = HTTOP;
		}
		if (yPos >(this->height() - HIT_BORDER) && yPos < (this->height() - 0)) {
			*result = HTBOTTOM;
		}
		if (xPos > 0 && xPos < HIT_BORDER && yPos > 0 && yPos < HIT_BORDER) {
			*result = HTTOPLEFT;
		}
		if (xPos >(this->width() - HIT_BORDER) && xPos < (this->width() - 0) && yPos > 0 && yPos < HIT_BORDER) {
			*result = HTTOPRIGHT;
		}
		if (xPos > 0 && xPos < HIT_BORDER && yPos >(this->height() - HIT_BORDER) && yPos < (this->height() - 0)) {
			*result = HTBOTTOMLEFT;
		}
		if (xPos >(this->width() - HIT_BORDER) && xPos < (this->width() - 0) && yPos >(this->height() - HIT_BORDER) && yPos < (this->height() - 0)) {
			*result = HTBOTTOMRIGHT;
		}
		return true;
	}

	return false;
}
