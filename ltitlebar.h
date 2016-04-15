/*
 * 自定义标题栏类.
 * 最简单的标题栏，许多东西不可以设置，可以完善接口，放出许多设置功能.
*/

#ifndef LTITLEBAR_H
#define LTITLEBAR_H

#include <QWidget>
#include <QPixmap>

namespace Ui {
class LTitleBar;
}

class LTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit LTitleBar(QWidget *parent = 0);
    ~LTitleBar();

    ///< \note 设置当前状态.
    void setMaxStatus(bool bStatus);

protected:
	void paintEvent(QPaintEvent * event);

signals:
    void minRequested();
    void maxRequested();
    void restoreRequested();
    void closeRequested();

private:
    Ui::LTitleBar *ui;

    bool _isMaximized;

    QPixmap _MinPix;
    QPixmap _MaxPix;
    QPixmap _ClosePix;
    QPixmap _RestorePix;
};

#endif // LTITLEBAR_H
