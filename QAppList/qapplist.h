#ifndef QAPPLIST_H
#define QAPPLIST_H

#include <QtWidgets/QWidget>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QAbstractItemView>
#include <QWidgetItem>
#include <QString>
#include <QRegExp>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_qapplist.h"
#include "RetrieveHelper.h"

#include <vector>
#include <string>

using std::vector;

class QAppList : public QWidget
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
	Ui::QAppListClass ui;

	QSortFilterProxyModel* m_proxyModel;
	QStandardItemModel* m_appmodel;
	QStandardItemModel* m_procmodel;

	RetrieveHelper* m_helper;
};

#endif // QAPPLIST_H
