#ifndef QAPPLIST_H
#define QAPPLIST_H

#include <QtWidgets/QWidget>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QAbstractItemView>
#include <QWidgetItem>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QIcon>
#include <QRegExp>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileIconProvider>
#include <QPixmap>

#include "shadoweffectwidget.h"
#include "RetrieveHelper.h"
#include "custommodel.h"
#include "applicationview.h"
#include "processview.h"
#include "nofocusframedelegate.h"
#include "titlebar.h"

#include <vector>
#include <string>

using std::vector;

class QAppList : public ShadowEffectWidget
{
	Q_OBJECT

public:
	QAppList(QWidget *parent = 0);
	~QAppList();
	enum {INSERT_ROW};
private slots:
	void onExportBtnClicked();
	void onRefreshBtnClicked();
	void onFilterChanged(const QString& regexp);

private:
	QAppList& operator=(const QAppList& obj);
	QAppList(const QAppList& obj);

	void initProcList();
	void createProcHeader();
	void loadProcessList();
	void initAppList();
	void createAppListHeader();
	void loadApplist();
	void dumpProclist(const QString& path);
private:
	QLineEdit* m_filterexp;
	QPushButton* m_exportBtn;
	QPushButton* m_refreshBtn;
	QHBoxLayout* m_toplayout;
	QVBoxLayout* m_mainLayout;
	TitleBar* m_titleWidget;

	QSortFilterProxyModel* m_proxyModel;
	CustomModel* m_appmodel;
	CustomModel* m_procmodel;
	ApplicationView* m_appTableView;
	ProcessView* m_procssTableView;

	RetrieveHelper* m_helper;
};

#endif // QAPPLIST_H
