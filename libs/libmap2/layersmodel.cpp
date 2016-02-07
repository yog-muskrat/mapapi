#include "layersmodel.h"
#include "maplayer.h"

#include "gis.h"

#include <QIcon>
#include <QDebug>
#include <QPixmap>
#include <QApplication>
#include <QFont>

using namespace Map2;

LayersModel::LayersModel(QObject *parent) :
	QAbstractTableModel(parent)
{
}

LayersModel::~LayersModel()
{
	qDeleteAll(mLayers);
}

int LayersModel::addLayer(Map2::MapLayer *layer)
{
	if(!mLayers.contains(layer))
	{
		beginInsertRows( QModelIndex(), mLayers.count(), mLayers.count());

		mLayers << layer;
		connect(layer, SIGNAL(layerNameChanged(QString)), this, SLOT(onLayerUpdated()));
		connect(layer, SIGNAL(visibilityToggled(bool)), this, SLOT(onLayerUpdated()));
		connect(layer, SIGNAL(lockToggled(bool)), this, SLOT(onLayerUpdated()));
		connect(layer, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onLayerUpdated()));
		connect(layer, SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(onLayerUpdated()));

		endInsertRows();
	}

	return mLayers.indexOf(layer);
}

void LayersModel::removeLayer(Map2::MapLayer *layer)
{
	removeLayer( mLayers.indexOf(layer));
}

void LayersModel::removeLayer(int row)
{
	if (row < 0 || row >= rowCount())
	{
		return;
	}

	beginRemoveRows(QModelIndex(), row, row);
	MapLayer *l = mLayers.takeAt(row);
	l->deleteFiles();
	l->deleteLater();
	endRemoveRows();
}

Map2::MapLayer *LayersModel::layerAt(int row)
{
	if(row < 0 || row >= rowCount())
	{
		return 0;
	}

	return mLayers[row];
}

Map2::MapLayer *LayersModel::layerByHandle(HSITE handle)
{
	foreach(MapLayer *l, mLayers)
	{
		if(l->siteHandle() == handle)
		{
			return l;
		}
	}

	return 0;
}

int LayersModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return mLayers.count();
}

int LayersModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return COL_Count;
}

QVariant LayersModel::data(const QModelIndex &index, int role) const
{
	if(!checkIndex(index))
	{
		return QVariant();
	}

	if(role == Qt::DisplayRole)
	{
		return displayRole(index);
	}
	else if(role == Qt::DecorationRole)
	{
		return decorationRole(index);
	}
	else if(role == Qt::FontRole)
	{
		QFont f = qApp->font();
		f.setPointSize(10);
		return f;
	}

	return QVariant();
}
QVariant LayersModel::displayRole(const QModelIndex &index) const
{
	MapLayer *l = mLayers.at(index.row());
	if(index.column() == COL_Name)
	{
		return l->layerName();
	}

	return QVariant();
}

QVariant LayersModel::checkStateRole(const QModelIndex &index) const
{
	MapLayer *l = mLayers.at(index.row());
	if(index.column() == COL_Visible)
	{
		return l->isVisible() ? Qt::Checked : Qt::Unchecked;
	}
	else if(index.column() == COL_Locked)
	{
		return l->isLocked() ? Qt::Checked : Qt::Unchecked;
	}

	return QVariant();
}

QVariant LayersModel::decorationRole(const QModelIndex &index) const
{
	MapLayer *l = mLayers.at(index.row());
	if(index.column() == COL_Visible)
	{
		return l->isVisible() ? QIcon(":visible_on") : QIcon(":visible_off");
	}
	else if(index.column() == COL_Locked)
	{
		return l->isLocked() ? QIcon(":lock") : QIcon(":unlock");
	}

	return QVariant();
}


bool LayersModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(!checkIndex(index))
	{
		return false;
	}

	if(role == Qt::CheckStateRole)
	{
		return setCheckStateRole(index, value);
	}
	else if( role == Qt::EditRole)
	{
		return setEditRole(index, value);
	}

	return QAbstractTableModel::setData(index, value, role);
}

bool LayersModel::setCheckStateRole(QModelIndex index, QVariant value)
{
	MapLayer *layer = mLayers.at(index.row());

	Qt::CheckState cs = static_cast<Qt::CheckState>(value.toInt());

	if(index.column() == COL_Visible)
	{
		layer->setVisible( cs == Qt::Checked );
		return true;
	}
	else if(index.column() == COL_Locked)
	{
		layer->setLocked(cs == Qt::Checked);
		return true;
	}

	return QAbstractTableModel::setData(index, value, Qt::CheckStateRole);
}

bool LayersModel::setEditRole(QModelIndex index, QVariant value)
{
	MapLayer *layer = mLayers.at(index.row());

	if(index.column() == COL_Name)
	{
		layer->setLayerName( value.toString());
		return true;
	}

	return QAbstractTableModel::setData(index, value, Qt::EditRole);
}

QVariant LayersModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(orientation != Qt::Horizontal)
	{
		return QAbstractTableModel::headerData(section, orientation, role);
	}

	if(section < 0 || section >= columnCount())
	{
		return QVariant();
	}

	if(section == COL_Visible)
	{
		if(role == Qt::DecorationRole)
		{
			return QPixmap(":visible_on");
		}
	}
	else if(section == COL_Locked)
	{
		if(role == Qt::DecorationRole)
		{
			return QPixmap(":lock");
		}
	}
	else if(section == COL_Name)
	{
		if(role == Qt::DisplayRole || role == Qt::EditRole)
		{
			return "Название";
		}
	}

	return QVariant();
}

Qt::ItemFlags LayersModel::flags(const QModelIndex &index) const
{
	Qt::ItemFlags flags = QAbstractItemModel::flags(index);
	if(index.column() == COL_Name)
	{
		flags |= Qt::ItemIsEditable;
	}

	return flags;
}

void LayersModel::onLayerUpdated()
{
	MapLayer *layer = qobject_cast<MapLayer*>( sender() );
	if(!layer || !mLayers.contains( layer ))
	{
		return;
	}

	int row = mLayers.indexOf( layer );

	emit dataChanged(index(row, 0), index(row, columnCount()));
}

bool LayersModel::checkIndex(const QModelIndex &idx) const
{
	return idx.isValid() && idx.row() < rowCount() && idx.column() < columnCount();
}