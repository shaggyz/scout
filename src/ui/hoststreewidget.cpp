#include "hoststreewidget.h"

/**
 * @brief HostsTreeWidget::HostsTreeWidget
 * @param parent
 */
HostsTreeWidget::HostsTreeWidget(QWidget *parent) : QTreeView(parent)
{
    this->model = new QStandardItemModel();
    this->setMouseTracking(true);
    this->setModel(this->model);

    connect(this, SIGNAL(entered(QModelIndex)), this, SLOT(onMouseOverItem(QModelIndex)));
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(onItemClick(QModelIndex)));

}

/**
 * @brief HostsTreeWidget::addHost
 * @param host
 * @return
 */
QStandardItem *HostsTreeWidget::addHost(Host *host)
{
    QString applicationPath = QDir::currentPath() + "/..";

    QStandardItem *item = new QStandardItem(QIcon::fromTheme("computer"), host->ip);
    QVariant ipParam(host->ip);
    item->setData(ipParam);

    QStandardItem *viewDetailsItem = new QStandardItem(QIcon::fromTheme("x-office-document"), "Open host details");
    viewDetailsItem->setEditable(false);
    QFont viewDetailsFont;

    viewDetailsFont.setUnderline(true);
    viewDetailsItem->setFont(viewDetailsFont);
    item->appendRow(viewDetailsItem);

    if (host->mac.length() > 0) {
        QStandardItem *macItem = new QStandardItem(QIcon::fromTheme("network-workgroup"), "MAC: " + host->mac);
        macItem->setEditable(false);
        item->appendRow(macItem);
    }

    if (host->netbiosName.length() > 0) {
        QStandardItem *netbiosItem = new QStandardItem(QIcon::fromTheme("network-server"), "NETBIOS: " + host->netbiosName);
        netbiosItem->setEditable(false);
        item->appendRow(netbiosItem);
    }

    if (host->shares.length()) {
        QStandardItem *sharesItem = new QStandardItem(QIcon::fromTheme("folder"), "SMB shares: " + QString::number(host->shares.length()));
        sharesItem->setEditable(false);
        item->appendRow(sharesItem);
    }

    item->setEditable(false);

    return item;
}

/**
 * @brief HostsTreeWidget::leaveEvent
 * @param event
 */
void HostsTreeWidget::leaveEvent(QEvent *)
{
    QApplication::restoreOverrideCursor();
}

/**
 * @brief HostsTreeWidget::isOpenHostDetailsItem
 * @param index
 * @return
 */
bool HostsTreeWidget::isOpenHostDetailsItem(QModelIndex index)
{
    return index.parent().isValid() && 0 == index.row();
}

/**
 * @brief HostsTreeWidget::updateHosts
 * @param hosts
 */
void HostsTreeWidget::updateHosts(QList<Host *> hosts)
{
    this->clear();
    this->hosts = hosts;

    Host *host;
    foreach(host, this->hosts) {
        QStandardItem *hostItem = this->addHost(host);
        this->model->appendRow(hostItem);
    }
    this->updateTitle(QString::number(hosts.length()) + " hosts");
}

/**
 * @brief HostsTreeWidget::clear
 */
void HostsTreeWidget::clear()
{
    if (this->model->hasChildren()) {
        this->model->removeRows(0, this->model->rowCount());
    }

    this->hosts = QList<Host *>();
    this->reset();

    this->updateTitle("0 hosts");
}

/**
 * @brief HostsTreeWidget::updateTitle
 * @param title
 */
void HostsTreeWidget::updateTitle(QString title)
{
    QStringList labels;
    labels.append(title);
    this->model->setHorizontalHeaderLabels(labels);
}

/**
 * Returns the internal hosts collection
 * @brief HostsTreeWidget::getHosts
 */
QList<Host *> HostsTreeWidget::getHosts()
{
    return this->hosts;
}

/**
 * @brief HostsTreeWidget::onMouseOverItem
 * @param index
 */
void HostsTreeWidget::onMouseOverItem(QModelIndex index)
{
    // Only child items and
    if (this->isOpenHostDetailsItem(index)) {
        QApplication::setOverrideCursor(Qt::PointingHandCursor);
    } else {
        QApplication::restoreOverrideCursor();
    }
}

/**
 * @brief HostsTreeWidget::onItemClick
 * @param index
 */
void HostsTreeWidget::onItemClick(QModelIndex index)
{
    if (this->isOpenHostDetailsItem(index)) {
        Host *host = this->getHostFromItemIndex(index);
        emit this->openHostDetailsRequest(host);
    }
}

/**
 * @brief HostsTreeWidget::getHostByIP
 * @param ip
 * @return
 */
Host *HostsTreeWidget::getHostByIP(QString ip)
{
    Host *host;
    foreach(host, this->hosts) {
        if (ip == host->ip) {
            return host;
        }
    }

    return NULL;
}

/**
 * @brief HostsTreeWidget::getHostFromItemIndex
 * @param index
 * @return
 */
Host *HostsTreeWidget::getHostFromItemIndex(QModelIndex index)
{
    QStandardItem *parent = this->model->itemFromIndex(index.parent());
    QString ip = parent->data().toString();
    return this->getHostByIP(ip);
}

