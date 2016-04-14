#include "ltitlebar.h"
#include "ui_ltitlebar.h"

#include <QPixmap>

LTitleBar::LTitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LTitleBar)
{
    ui->setupUi(this);

    QPixmap  pix;
    pix.load(":/images/title_min.png");
    ui->pMinBtn->setIcon(pix);

    pix.load(":/images/title_restore.png");
    ui->pMaxBtn->setIcon(pix);

    pix.load(":/images/title_close.png");
    ui->pCloseBtn->setIcon(pix);

    connect(ui->pMinBtn, &QToolButton::clicked, this, &LTitleBar::minRequested);
    connect(ui->pMaxBtn, &QToolButton::clicked, this, &LTitleBar::maxRequested);
    connect(ui->pCloseBtn, &QToolButton::clicked, this, &LTitleBar::closeRequested);
}

LTitleBar::~LTitleBar()
{
    delete ui;
}
