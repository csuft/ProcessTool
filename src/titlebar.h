#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>
#include <QHBoxLayout>

#include "custompushbutton.h"

class TitleBar : public QWidget
{
	Q_OBJECT

public:
	explicit TitleBar(QWidget *parent);
	~TitleBar(){}
protected:
	void paintEvent(QPaintEvent *event);

signals:
	void customShowMinWindow();
	void customCloseWindow();

private:
	TitleBar& operator=(const TitleBar& obj);
	TitleBar(const TitleBar& obj);

private:
	CustomPushButton* m_minBtn;
	CustomPushButton* m_closeBtn;
	QLabel* m_winTitle;
	QHBoxLayout* m_layout;
};

#endif // TITLEBAR_H
