#include "qapplist.h"

QAppList::QAppList(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_helper = new RetrieveHelper;

	initProcList();
	initAppList();
	
	connect(ui.RefreshBtn, SIGNAL(clicked()), this, SLOT(onRefreshBtnClicked()));
	connect(ui.exportBtn, SIGNAL(clicked()), this, SLOT(onExportBtnClicked()));
	connect(ui.filterexp, SIGNAL(textChanged(const QString&)), this, SLOT(onFilterChanged(const QString&)));
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
	ui.procssTableView->verticalHeader()->hide();
	ui.procssTableView->horizontalHeader()->setStretchLastSection(true);
	ui.procssTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.procssTableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.procssTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.procssTableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	ui.procssTableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	ui.procssTableView->horizontalHeader()->setStretchLastSection(true);

	m_procmodel = new QStandardItemModel(0, 6, this);
	m_proxyModel = new QSortFilterProxyModel(this);
	m_proxyModel->setSourceModel(m_procmodel);
	ui.procssTableView->setModel(m_proxyModel);
	createProcHeader();
	loadProcessList();
}

void QAppList::createProcHeader()
{
	m_procmodel->setHeaderData(0, Qt::Horizontal, QStringLiteral("Process Name"));
	m_procmodel->setHeaderData(1, Qt::Horizontal, QStringLiteral("PID"));
	m_procmodel->setHeaderData(2, Qt::Horizontal, QStringLiteral("Thread Count"));
	m_procmodel->setHeaderData(3, Qt::Horizontal, QStringLiteral("PPID"));
	m_procmodel->setHeaderData(4, Qt::Horizontal, QStringLiteral("Priority Base"));
	m_procmodel->setHeaderData(5, Qt::Horizontal, QStringLiteral("Priority Class"));

}

void QAppList::loadProcessList()
{
	m_procmodel->removeRows(0, m_procmodel->rowCount());
	const vector<ProcEntry> pec = m_helper->getProclist();
	for (vector<ProcEntry>::const_iterator ci = pec.cbegin(); ci != pec.cend(); ++ci)
	{
		m_procmodel->insertRow(0);
		m_procmodel->setData(m_procmodel->index(INSERT_ROW, 0), QString::fromStdWString((*ci).procName));
		m_procmodel->setData(m_procmodel->index(INSERT_ROW, 1), (*ci).procId);
		m_procmodel->setData(m_procmodel->index(INSERT_ROW, 2), (*ci).ctThread);
		m_procmodel->setData(m_procmodel->index(INSERT_ROW, 3), (*ci).procPid);
		m_procmodel->setData(m_procmodel->index(INSERT_ROW, 4), (*ci).priorBase);
		m_procmodel->setData(m_procmodel->index(INSERT_ROW, 5), (*ci).priorClass);
	}
}

void QAppList::initAppList()
{
	ui.appTableView->verticalHeader()->hide();
	ui.appTableView->horizontalHeader()->setStretchLastSection(true);
	ui.appTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.appTableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.appTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.appTableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	ui.appTableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	ui.appTableView->horizontalHeader()->setStretchLastSection(true);

	m_appmodel = new QStandardItemModel(0, 5, this);
	ui.appTableView->setModel(m_appmodel);
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