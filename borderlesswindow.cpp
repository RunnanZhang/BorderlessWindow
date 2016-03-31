#include "borderlesswindow.h"
#include "ui_borderlesswindow.h"

BorderlessWindow::BorderlessWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BorderlessWindow)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::CustomizeWindowHint);
}

BorderlessWindow::~BorderlessWindow()
{
    delete ui;
}
