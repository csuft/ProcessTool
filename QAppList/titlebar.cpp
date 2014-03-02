#include "titlebar.h"

TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
{
	m_layout = new QHBoxLayout(this);
	m_closeBtn = new CustomPushButton(this);
	m_minBtn = new CustomPushButton(this);
	m_winTitle = new QLabel(QStringLiteral("System Helper"), this);
	m_winTitle->setStyleSheet("color: white; font-size: 14px");
	
	m_closeBtn->setButtonBgrd(QStringLiteral(":/Buttons/close"));
	m_minBtn->setButtonBgrd(QStringLiteral(":/Buttons/min"));
	m_layout->addWidget(m_winTitle, 0, Qt::AlignCenter);
	m_layout->addStretch();
	m_layout->addWidget(m_minBtn, 0, Qt::AlignTop);
	m_layout->addWidget(m_closeBtn, 0, Qt::AlignTop);

	m_layout->setSpacing(0);
	m_layout->setContentsMargins(15, 0, 5, 0);
	setLayout(m_layout);

	connect(m_closeBtn, SIGNAL(clicked()), this, SIGNAL(customCloseWindow()));
	connect(m_minBtn, SIGNAL(clicked()), this, SIGNAL(customShowMinWindow()));
}

void TitleBar::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::white);
	painter.drawPixmap(QRect(0, 0, width(), height()), QPixmap(":/background"));
}