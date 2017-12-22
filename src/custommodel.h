#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H

#include <QStandardItemModel>
#include <QVariant>

class CustomModel : public QStandardItemModel
{
	Q_OBJECT

public:
	explicit CustomModel(QObject *parent = NULL):QStandardItemModel(parent){}
	CustomModel(int row, int col, QObject* parent = NULL): QStandardItemModel(row, col, parent){}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	~CustomModel();

private:
	CustomModel& operator=(const CustomModel& obj);
	CustomModel(const CustomModel& obj);
};

#endif // CUSTOMMODEL_H
