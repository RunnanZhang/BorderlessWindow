#include "ltitlebar.h"
#include "ui_ltitlebar.h"

#include <QPainter>

LTitleBar::LTitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LTitleBar),
    _isMaximized(false)
{
    ui->setupUi(this);

    _MinPix.load(":/images/title_min.png");
	ui->pMinBtn->setIcon(_MinPix);

    _MaxPix.load(":/images/title_max.png");
    _RestorePix.load(":/images/title_restore.png");
	ui->pMaxReBtn->setIcon(_MaxPix);

    _ClosePix.load(":/images/title_close.png");
	ui->pCloseBtn->setIcon(_ClosePix);

    connect(ui->pMinBtn, &QToolButton::clicked, this, &LTitleBar::minRequested);
    connect(ui->pMaxReBtn, &QToolButton::clicked, this, [=](){
        _isMaximized ? emit restoreRequested() : emit maxRequested();
		_isMaximized = !_isMaximized;
    });
    connect(ui->pCloseBtn, &QToolButton::clicked, this, &LTitleBar::closeRequested);
}

LTitleBar::~LTitleBar()
{
    delete ui;
}

void LTitleBar::setMaxStatus(bool bStatus)
{
    _isMaximized = bStatus;

    if(_isMaximized)  {
        ui->pMaxReBtn->setIcon(_MaxPix);
    } else {
        ui->pMaxReBtn->setIcon(_RestorePix);
    }
}

void LTitleBar::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	painter.fillRect(rect(), QBrush(QColor(Qt::white)));
	QWidget::paintEvent(event);
}
