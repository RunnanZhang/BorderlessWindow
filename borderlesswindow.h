#ifndef BORDERLESSWINDOW_H
#define BORDERLESSWINDOW_H

#include <QWidget>

namespace Ui {
class BorderlessWindow;
}

class BorderlessWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BorderlessWindow(QWidget *parent = 0);
    ~BorderlessWindow();

private:
    Ui::BorderlessWindow *ui;
};

#endif // BORDERLESSWINDOW_H
