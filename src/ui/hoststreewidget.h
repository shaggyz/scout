#ifndef HOSTSTREEWIDGET_H
#define HOSTSTREEWIDGET_H

#include <QTreeView>
#include <QList>
#include <QDebug>
#include <QIcon>
#include <QDir>
#include <QFont>
#include <QStringList>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QModelIndex>
#include <QApplication>
#include <QEvent>

#include "net/host.h"

class HostsTreeWidget : public QTreeView
{
    Q_OBJECT
public:
    /**
     * @brief HostsTreeWidget
     * @param parent
     */
    explicit HostsTreeWidget(QWidget *parent = 0);

protected:

    /**
     * Creates a standard item from host container
     * @brief addHost
     * @param host
     * @return
     */
    QStandardItem *addHost(Host *host);

    /**
     * Internal model
     * @brief model
     */
    QStandardItemModel *model;

    /**
     * Internal hosts collection
     * @brief hosts
     */
    QList<Host *> hosts;

    /**
     * Overload to reset cursor transformations.
     * Called when mouse leaves the widget area.
     * @brief leaveEvent
     * @param event
     */
    void leaveEvent(QEvent *event);

    /**
     * Check if given index belongs to an open details button item
     * @brief isOpenHostDetailsItem
     * @param index
     * @return
     */
    bool isOpenHostDetailsItem(QModelIndex index);

signals:

    /**
     * Emitted when user request to open host details
     * @brief openHostDetailsRequest
     * @param host
     */
    void openHostDetailsRequest(Host *host);

public slots:

    /**
     * Clear the tree widget and set new hosts to list
     * @brief updateHosts
     * @param hosts
     */
    void updateHosts(QList<Host *> hosts);

    /**
     * Clear the tree
     * @brief clear
     */
    void clear();

    /**
     * Updates the tree widget
     * @brief updateTitle
     * @param title
     */
    void updateTitle(QString title);

    /**
     * Returns the internal hosts collection
     * @brief getHosts
     */
    QList<Host *> getHosts();

protected slots:

    /**
     * Chenges the cursor to hand, when mouse is over an action item
     * @brief onMouseOverItem
     * @param index
     */
    void onMouseOverItem(QModelIndex index);

    /**
     * Called on item click
     * @brief requestOpenHost
     * @param index
     */
    void onItemClick(QModelIndex index);

    /**
     * Returns a hosts from its IP
     * @brief getHostByIP
     * @param ip
     * @return
     */
    Host *getHostByIP(QString ip);

    /**
     * Retuns a host from its model index (inside internal collection)
     * @brief getHostFromItemIndex
     * @param index
     * @return
     */
    Host *getHostFromItemIndex(QModelIndex index);
};

#endif // HOSTSTREEWIDGET_H
