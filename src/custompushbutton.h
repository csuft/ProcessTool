#ifndef CUSTOMPUSHBUTTON_H
#define CUSTOMPUSHBUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>

class CustomPushButton : public QPushButton
{
	Q_OBJECT

public:
	explicit CustomPushButton(QWidget *parent);
	~CustomPushButton(){}
	enum BtnStatus{NORMAL, PRESSED, HOVER};
	void setButtonBgrd(const QString& filename);
protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);

private:
	CustomPushButton(const CustomPushButton& obj);
	CustomPushButton& operator=(const CustomPushButton& obj);

private:
	BtnStatus m_status;  // record the status to take different painting action
	bool isPressed;   // whether the button is pressed.
	QString m_bgpic;
};

#endif // CUSTOMPUSHBUTTON_H
