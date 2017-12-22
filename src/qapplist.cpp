#include "qapplist.h"

QAppList::QAppList(QWidget *parent)
	: ShadowEffectWidget(parent)
{
	m_mainLayout = new QVBoxLayout(this);
	m_toplayout = new QHBoxLayout(this);
	m_filterexp = new QLineEdit(this);
	m_filterexp->setPlaceholderText(QStringLiteral("Filter expression"));
	m_filterexp->setContentsMargins(5, 0, 3, 1);
	m_refreshBtn = new QPushButton(QStringLiteral("Refresh"), this);
	m_exportBtn = new QPushButton(QStringLiteral("Export..."), this);
	m_refreshBtn->setObjectName("refreshBtn");
	m_exportBtn->setObjectName("exportBtn");
	m_refreshBtn->setFixedSize(75, 25);
	m_exportBtn->setFixedSize(75, 25);
	m_filterexp->setFixedHeight(25);

	m_toplayout->addWidget(m_filterexp);
	m_toplayout->addWidget(m_refreshBtn);
	m_toplayout->addWidget(m_exportBtn);
	m_toplayout->setContentsMargins(5, 0, 5, 0);

	m_titleWidget = new TitleBar(this);
	m_procssTableView = new ProcessView(this);
	m_appTableView = new ApplicationView(this);

	m_mainLayout->addWidget(m_titleWidget, 0, Qt::AlignTop);
	m_mainLayout->addLayout(m_toplayout);
	m_mainLayout->addWidget(m_procssTableView);
	m_mainLayout->addWidget(m_appTableView);

	setLayout(m_mainLayout);
	setFixedSize(700, 500);
	m_helper = new RetrieveHelper;
	
	initProcList();
	initAppList();
	
	connect(m_titleWidget, SIGNAL(customShowMinWindow()), this, SLOT(showMinimized()));
	connect(m_titleWidget, SIGNAL(customCloseWindow()), this, SLOT(close()));
	connect(m_refreshBtn, SIGNAL(clicked()), this, SLOT(onRefreshBtnClicked()));
	connect(m_exportBtn, SIGNAL(clicked()), this, SLOT(onExportBtnClicked()));
	connect(m_filterexp, SIGNAL(textChanged(const QString&)), this, SLOT(onFilterChanged(const QString&)));
}

QAppList::~QAppList()
{
	delete m_helper;
}

void QAppList::onExportBtnClicked()
{
	QString path = QFileDialog::getSaveFileName(this, QStringLiteral("Select storage path"));
	dumpProclist(path);
}

void QAppList::onRefreshBtnClicked()
{
	loadProcessList();
}

void QAppList::onFilterChanged(const QString& exp)
{
	QRegExp regexp(exp, Qt::CaseInsensitive, QRegExp::FixedString);
	m_proxyModel->setFilterRegExp(regexp);
}

void QAppList::initProcList()
{
	//////////////////////////////////////////////////////////////////////////
	// This code section should be placed at the first. Otherwise the setColumnWidth()
	// will not work.
	m_procmodel = new CustomModel(0, 7, this);
	m_proxyModel = new QSortFilterProxyModel(this);
	m_proxyModel->setSourceModel(m_procmodel);
	m_procssTableView->setModel(m_proxyModel);
	//////////////////////////////////////////////////////////////////////////
	m_procssTableView->verticalHeader()->hide();
	m_procssTableView->horizontalHeader()->setDefaultSectionSize(90);
	m_procssTableView->setColumnWidth(0, 100);
	m_procssTableView->setColumnWidth(1, 45);
	m_procssTableView->setColumnWidth(2, 80);
	m_procssTableView->setColumnWidth(3, 45);
	m_procssTableView->setColumnWidth(4, 70);
	QFont f = m_procssTableView->font();
	f.setBold(true);
	m_procssTableView->horizontalHeader()->setFont(f);
	m_procssTableView->horizontalHeader()->setSectionsClickable(false);
	m_procssTableView->horizontalHeader()->setStretchLastSection(true);
	m_procssTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_procssTableView->setSelectionMode(QAbstractItemView::SingleSelection);
	m_procssTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_procssTableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_procssTableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_procssTableView->setShowGrid(false);  // disable the table grid.
	m_procssTableView->verticalHeader()->setDefaultSectionSize(25);  // set row height.
	m_procssTableView->horizontalHeader()->setHighlightSections(false);
	m_procssTableView->setFrameShape(QFrame::NoFrame);
	m_procssTableView->setItemDelegate(new NoFocusFrameDelegate());

	createProcHeader();
	loadProcessList();
}

void QAppList::createProcHeader()
{
	m_procmodel->setHeaderData(0, Qt::Horizontal, QStringLiteral("Process Name"));
	m_procmodel->setHeaderData(1, Qt::Horizontal, QStringLiteral("PID"));
	m_procmodel->setHeaderData(2, Qt::Horizontal, QStringLiteral("Thread Count"));
	m_procmodel->setHeaderData(3, Qt::Horizontal, QStringLiteral("PPID"));
	m_procmodel->setHeaderData(4, Qt::Horizontal, QStringLiteral("Prior Base"));
	m_procmodel->setHeaderData(5, Qt::Horizontal, QStringLiteral("Prior Class"));
	m_procmodel->setHeaderData(6, Qt::Horizontal, QStringLiteral("Path"));
}

void QAppList::loadProcessList()
{
	m_procmodel->removeRows(INSERT_ROW, m_procmodel->rowCount());
	const vector<ProcEntry> pec = m_helper->getProclist();
	QFileIconProvider fip;
	for (vector<ProcEntry>::const_iterator ci = pec.cbegin(); ci != pec.cend(); ++ci)
	{
		m_procmodel->insertRow(INSERT_ROW);
		m_procmodel->setData(m_procmodel->index(INSERT_ROW, 0), QString::fromStdWString((*ci).procName));
		m_procmodel->setData(m_procmodel->index(INSERT_ROW, 1), (*ci).procId);
		m_procmodel->setData(m_procmodel->index(INSERT_ROW, 2), (*ci).ctThread);
		m_procmodel->setData(m_procmodel->index(INSERT_ROW, 3), (*ci).procPid);
		m_procmodel->setData(m_procmodel->index(INSERT_ROW, 4), (*ci).priorBase);
		m_procmodel->setData(m_procmodel->index(INSERT_ROW, 5), (*ci).priorClass);
		m_procmodel->setData(m_procmodel->index(INSERT_ROW, 6), QString::fromStdWString((*ci).exePath));
		QFileInfo file(QString::fromStdWString((*ci).exePath));
		m_procmodel->item(INSERT_ROW, 0)->setIcon(fip.icon(file));
	}
}

void QAppList::initAppList()
{
	// This statement should be first, otherwise setColumnWidth() will not work
	m_appmodel = new CustomModel(0, 5, this);  
	m_appTableView->setModel(m_appmodel);
	m_appTableView->horizontalHeader()->setDefaultSectionSize(150);
	m_appTableView->setColumnWidth(0, 200);
	m_appTableView->setColumnWidth(1, 75);
	m_appTableView->setColumnWidth(2, 75);
	m_appTableView->verticalHeader()->hide();
	QFont f = m_appTableView->font();
	f.setBold(true);
	m_appTableView->horizontalHeader()->setFont(f);
	m_appTableView->horizontalHeader()->setStretchLastSection(true);
	m_appTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_appTableView->setSelectionMode(QAbstractItemView::SingleSelection);
	m_appTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_appTableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_appTableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_appTableView->setShowGrid(false);
	m_appTableView->horizontalHeader()->setHighlightSections(false);
	m_appTableView->verticalHeader()->setDefaultSectionSize(25);
	m_appTableView->setFrameShape(QFrame::NoFrame);
	m_appTableView->setItemDelegate(new NoFocusFrameDelegate());


	createAppListHeader();
	loadApplist();
}

void QAppList::createAppListHeader()
{
	m_appmodel->setHeaderData(0, Qt::Horizontal, QStringLiteral("App Name"));
	m_appmodel->setHeaderData(1, Qt::Horizontal, QStringLiteral("Version"));
	m_appmodel->setHeaderData(2, Qt::Horizontal, QStringLiteral("Install Date"));
	m_appmodel->setHeaderData(3, Qt::Horizontal, QStringLiteral("Location"));
	m_appmodel->setHeaderData(4, Qt::Horizontal, QStringLiteral("Publisher"));
}

void QAppList::loadApplist()
{
	m_appmodel->removeRows(0, m_appmodel->rowCount());
	const vector<AppEntry> pec = m_helper->getApplist();
	for (vector<AppEntry>::const_iterator ci = pec.cbegin(); ci != pec.cend(); ++ci)
	{
		m_appmodel->insertRow(0);
		m_appmodel->setData(m_appmodel->index(INSERT_ROW, 0), QString::fromStdWString((*ci).appName));
		m_appmodel->setData(m_appmodel->index(INSERT_ROW, 1), QString::fromStdWString((*ci).appVer));
		m_appmodel->setData(m_appmodel->index(INSERT_ROW, 2), QString::fromStdWString((*ci).installDate));
		m_appmodel->setData(m_appmodel->index(INSERT_ROW, 3), QString::fromStdWString((*ci).location));
		m_appmodel->setData(m_appmodel->index(INSERT_ROW, 4), QString::fromStdWString((*ci).publisher));
	}
}

void QAppList::dumpProclist(const QString& path)
{


}