#ifndef __TREEMODEL_HPP__
#define __TREEMODEL_HPP__

#include <QtCore/QObject>
#include <QtCore/qabstractitemmodel.h>


class TreeModel : public QAbstractItemModel
{
    class Item
    {
    public:
        Item();

        inline unsigned id(void) const {return _id;}

        void clear(void);
        bool insertRow(int row);

        QVariant data(int role) const;
        void setData(const QVariant & value,  int role);

        inline Item * parent(void) const {return _parent;}
        inline void setParent(Item * parent) {_parent = parent;}

        int childrenCount(void) const;
        const Item * child(int index) const;
        Item * child(int index);
        int childRow(const Item * child) const;

    private:
        unsigned            _id;
        Item *              _parent;
        QMap<int,  QVariant> _data;
        QList<Item>         _children;

        static unsigned next_id;
    };

public:
    TreeModel(QObject * parent = 0);
    TreeModel(unsigned columns,  QObject * parent = 0);

    /* Read-Only model members */
    virtual QModelIndex index(int row , int column,  const QModelIndex & parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex & index) const;
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex & index,  int role) const;
    virtual QVariant headerData(int section,  Qt::Orientation orientation,  int role = Qt::DisplayRole) const;

    /* Editable Model members */
    bool insertRow(int row,  const QModelIndex & parent = QModelIndex());
    virtual bool setData(const QModelIndex & index,  const QVariant & value,  int role = Qt::EditRole);

    void clear(void);

private:
    Item * get_item(const QModelIndex & index);
    const Item * get_item(const QModelIndex & index) const;

private:
    unsigned _columnCount;
    QList<QString> _horizontalHeader;
    Item _root;
};

#endif //__TREEMODEL_HPP__
