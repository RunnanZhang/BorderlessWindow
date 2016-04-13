#ifndef LTITLEBAR_H
#define LTITLEBAR_H

#include <QWidget>

namespace Ui {
class LTitleBar;
}

class LTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit LTitleBar(QWidget *parent = 0);
    ~LTitleBar();

signals:
    void minRequested();
    void maxRequested();
    void closeRequested();

private:
    Ui::LTitleBar *ui;
};

#endif // LTITLEBAR_H
