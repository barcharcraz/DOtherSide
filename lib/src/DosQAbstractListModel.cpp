#include "DOtherSide/DosQAbstractListModel.h"
#include "DOtherSide/DosQObjectImpl.h"

namespace {
DOS::DosQObjectImpl::ParentMetaCall createParentMetaCall(QAbstractListModel *parent)
{
    return [parent](QMetaObject::Call callType, int index, void **args)->int {
        return parent->QAbstractListModel::qt_metacall(callType, index, args);
    };
}
}

namespace DOS {

DosQAbstractListModel::DosQAbstractListModel(void *modelObject,
                                             DosIQMetaObjectPtr metaObject,
                                             OnSlotExecuted onSlotExecuted,
                                             RowCountCallback rowCountCallback,
                                             ColumnCountCallback columnCountCallback,
                                             DataCallback dataCallback,
                                             SetDataCallback setDataCallback,
                                             RoleNamesCallback roleNamesCallback,
                                             FlagsCallback flagsCallback,
                                             HeaderDataCallback headerDataCallback)
    : m_impl(new DosQObjectImpl(this, ::createParentMetaCall(this), std::move(metaObject), std::move(onSlotExecuted)))
    , m_modelObject(std::move(modelObject))
    , m_rowCountCallback(std::move(rowCountCallback))
    , m_columnCountCallback(std::move(columnCountCallback))
    , m_dataCallback(std::move(dataCallback))
    , m_setDataCallback(std::move(setDataCallback))
    , m_roleNamesCallback(std::move(roleNamesCallback))
    , m_flagsCallback(std::move(flagsCallback))
    , m_headerDataCallback(std::move(headerDataCallback))
{}

bool DosQAbstractListModel::emitSignal(QObject *emitter, const QString &name, const std::vector<QVariant> &argumentsValues)
{
    Q_ASSERT(m_impl);
    return m_impl->emitSignal(emitter, name, argumentsValues);
}

const QMetaObject *DosQAbstractListModel::metaObject() const
{
    Q_ASSERT(m_impl);
    return m_impl->metaObject();
}

int DosQAbstractListModel::qt_metacall(QMetaObject::Call call, int index, void **args)
{
    Q_ASSERT(m_impl);
    return m_impl->qt_metacall(call, index, args);
}

int DosQAbstractListModel::rowCount(const QModelIndex &parent) const
{
    int result;
    m_rowCountCallback(m_modelObject, &parent, &result);
    return result;
}

int DosQAbstractListModel::columnCount(const QModelIndex &parent) const
{
    int result;
    m_columnCountCallback(m_modelObject, &parent, &result);
    return result;
}

QVariant DosQAbstractListModel::data(const QModelIndex &index, int role) const
{
    QVariant result;
    m_dataCallback(m_modelObject, &index, role, &result);
    return result;
}

bool DosQAbstractListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool result = false;
    m_setDataCallback(m_modelObject, &index, &value, role, &result);
    return result;
}

Qt::ItemFlags DosQAbstractListModel::flags(const QModelIndex &index) const
{
    int result;
    m_flagsCallback(m_modelObject, &index, &result);
    return Qt::ItemFlags(result);
}

QVariant DosQAbstractListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant result;
    m_headerDataCallback(m_modelObject, section, orientation, role, &result);
    return result;
}

void *DosQAbstractListModel::modelObject()
{
    return m_modelObject;
}

QHash<int, QByteArray> DosQAbstractListModel::roleNames() const
{
    QHash<int, QByteArray> result;
    m_roleNamesCallback(m_modelObject, &result);
    return result;
}

void DOS::DosQAbstractListModel::publicBeginInsertRows(const QModelIndex &index, int first, int last)
{
    beginInsertRows(index, first, last);
}

void DOS::DosQAbstractListModel::publicEndInsertRows()
{
    endInsertRows();
}

void DOS::DosQAbstractListModel::publicBeginRemoveRows(const QModelIndex &index, int first, int last)
{
    beginRemoveRows(index, first, last);
}

void DOS::DosQAbstractListModel::publicEndRemoveRows()
{
    endRemoveRows();
}

void DOS::DosQAbstractListModel::publicBeginResetModel()
{
    beginResetModel();
}

void DOS::DosQAbstractListModel::publicEndResetModel()
{
    endResetModel();
}

void DOS::DosQAbstractListModel::publicDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    emit dataChanged(topLeft, bottomRight, roles);
}

} // namespace DOS
