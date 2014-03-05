#include "modulestableview.h"

ModulesTableView::ModulesTableView(unsigned long pid, QWidget *parent)
	: ShadowEffectWidget(parent), m_pid(pid)
{
	resize(500, 350);
	m_mainLayout = new QVBoxLayout(this);
	m_topLayout = new QHBoxLayout(this);
	m_closeBtn = new CustomPushButton(this);
	m_closeBtn->setButtonBgrd(QStringLiteral(":/Buttons/close"));
	m_title = new QLabel(QStringLiteral("Process Modules"));
	m_title->setFixedHeight(QPixmap(":/Buttons/close").height());
	m_title->setContentsMargins(5, 5, 0, 5);
	m_title->setObjectName(QStringLiteral("Title"));
	m_topLayout->addWidget(m_title, 0, Qt::AlignCenter);
	m_topLayout->addStretch();
	m_topLayout->addWidget(m_closeBtn, 0, Qt::AlignTop);
	m_topLayout->setContentsMargins(15, 0, 5, 0);

	m_view = new QTableView(this);
	m_model = new CustomModel(0, 6, this);
	m_view->setModel(m_model);
	initialViewBehavior();
	createHeaders();
	
	m_OkBtn = new QPushButton(QStringLiteral("OK"), this);
	m_OkBtn->setFixedSize(75, 25);
	m_OkBtn->setObjectName(QStringLiteral("OkBtn"));
	m_modCounts = new QLabel(this);
	m_modCounts->setFixedHeight(25);
	m_modCounts->setObjectName(QStringLiteral("CountLabel"));
	m_bottomLayout = new QHBoxLayout(this);
	m_bottomLayout->addWidget(m_modCounts, 0, Qt::AlignCenter);
	m_bottomLayout->addStretch();
	m_bottomLayout->addWidget(m_OkBtn, 0, Qt::AlignRight);
	m_bottomLayout->setContentsMargins(10, 0, 10, 5);

	m_mainLayout->addLayout(m_topLayout);
	m_mainLayout->addWidget(m_view);
	m_mainLayout->addLayout(m_bottomLayout);
	m_mainLayout->setSpacing(0);
	m_mainLayout->setContentsMargins(5, 5, 5, 5);

	fillTableView();

	setLayout(m_mainLayout);

	connect(m_closeBtn, SIGNAL(clicked()), this, SLOT(hide()));
	connect(m_OkBtn, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
}

ModulesTableView::~ModulesTableView()
{

}

void ModulesTableView::createHeaders()
{
	m_model->setHeaderData(0, Qt::Horizontal, QStringLiteral("Name"));
	m_model->setHeaderData(1, Qt::Horizontal, QStringLiteral("Path"));
	m_model->setHeaderData(2, Qt::Horizontal, QStringLiteral("PID"));
	m_model->setHeaderData(3, Qt::Horizontal, QStringLiteral("Glb Ref"));
	m_model->setHeaderData(4, Qt::Horizontal, QStringLiteral("Pro Ref"));
	m_model->setHeaderData(5, Qt::Horizontal, QStringLiteral("Base Size"));
}

void ModulesTableView::initialViewBehavior()
{
	m_view->verticalHeader()->hide();
	m_view->horizontalHeader()->setDefaultSectionSize(100);
	m_view->setColumnWidth(1, 150);
	m_view->setColumnWidth(2, 50);
	m_view->setColumnWidth(3, 50);
	m_view->setColumnWidth(4, 50);
	m_view->setColumnWidth(5, 50);
	m_view->horizontalHeader()->setSectionsClickable(false);
	m_view->horizontalHeader()->setStretchLastSection(true);
	m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_view->setSelectionMode(QAbstractItemView::SingleSelection);
	m_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_view->setShowGrid(false);
	m_view->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_view->verticalHeader()->setDefaultSectionSize(25);
	m_view->horizontalHeader()->setHighlightSections(false);
	m_view->setFrameShape(QFrame::NoFrame);
	m_view->setItemDelegate(new NoFocusFrameDelegate());
}

void ModulesTableView::fillTableView()
{
	vector<ModuleEntry> vme = RetrieveHelper::getFullModules(m_pid);
	for (vector<ModuleEntry>::const_iterator ci = vme.cbegin(); ci != vme.cend(); ++ci)
	{
		m_model->insertRow(0);
		m_model->setData(m_model->index(0, 0), QString::fromStdWString((*ci).modName));
		m_model->setData(m_model->index(0, 1), QString::fromStdWString((*ci).exePath));
		m_model->setData(m_model->index(0, 2), QString::number((*ci).modPid, 10));
		m_model->setData(m_model->index(0, 3), QString::number((*ci).glblcntUsage, 10));
		m_model->setData(m_model->index(0, 4), QString::number((*ci).proccntUsage, 10));
		m_model->setData(m_model->index(0, 5), QString::number((*ci).modBaseSize, 10));
	}
	m_modCounts->setText(QString("Modules count: %1").arg(m_model->rowCount()));
}

void ModulesTableView::onBtnClicked()
{
	this->accept();
}

void ModulesTableView::paintEvent(QPaintEvent* event)
{
	ShadowEffectWidget::paintEvent(event);
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::white);
	painter.drawPixmap(5, 5, width()-10, height()-10, QPixmap(QStringLiteral(":/background")));
	painter.drawRect(5, 30, width()-10, height()-35);
	
}