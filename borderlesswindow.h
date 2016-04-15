/*
 * Borderless Window Using Resized，Areo Snap, Shadow, Minimize Animation, and Shake
*/
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

protected:
	bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private slots:
    void on_pAddBtn_clicked();
	void on_pShadowBtn_clicked();

private:
    Ui::BorderlessWindow *ui;
	bool _isShadow;
};

#endif // BORDERLESSWINDOW_H
