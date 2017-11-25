#include "discovertabswidget.h"

// Tabs titles
const QString DiscoverTabsWidget::HOST_DETAILS_TITLE = " - Details";

/**
 * @brief DiscoverTabsWidget::DiscoverTabsWidget
 * @param parent
 */
DiscoverTabsWidget::DiscoverTabsWidget(QWidget *parent) : QTabWidget(parent)
{
    this->setTabsClosable(true);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(onCloseTabRequest(int)));
}

/**
 * @brief DiscoverTabsWidget::onCloseTabRequest
 * @param index
 */
void DiscoverTabsWidget::onCloseTabRequest(int index)
{
    QString tabTitle = this->tabText(index);

    // Update internal tabs counters
    if (this->registeredDiscovers.contains(tabTitle)) {
        this->removeDiscoverTab(tabTitle);
    } else {
        this->removeHostTab(tabTitle);
    }
}

/**
 * @brief DiscoverTabsWidget::addHostTab
 * @param host
 */
void DiscoverTabsWidget::addHostTab(Host *host)
{
    // Already open?
    if (this->hostDetailsTabs.contains(host->ip)) {
        return;
    }

    this->hostDetailsTabs.append(host->ip);

    HostDetails *hostDetails = new HostDetails(this);
    hostDetails->setHost(host);
    hostDetails->updateHostDetailsTab();

    QString applicationPath = QDir::currentPath() + "/..";
    QIcon computerIcon(applicationPath + "/resources/icons/computer.png");

    int index = this->addTab(hostDetails, computerIcon, host->ip + HOST_DETAILS_TITLE);

    this->setCurrentIndex(index);
}

/**
 * @brief DiscoverTabsWidget::removeDiscoverTab
 * @param discoverTitle
 */
void DiscoverTabsWidget::removeDiscoverTab(QString discoverTitle)
{
    if (this->discoverTabs.contains(discoverTitle)) {
        this->discoverTabs.removeAt(this->discoverTabs.indexOf(discoverTitle));
        int index = this->getTabIndexByTitle(discoverTitle);
        this->removeTab(index);
    }
}

/**
 * @brief DiscoverTabsWidget::removeHostTab
 * @param hostTitle
 * @param index
 */
void DiscoverTabsWidget::removeHostTab(QString hostTitle)
{
    // Host details
    QStringList titleParts = hostTitle.split(" - ");
    QString hostIP = titleParts.first().replace("&", "");

    if (this->hostDetailsTabs.contains(hostIP)) {
        this->hostDetailsTabs.removeAt(this->hostDetailsTabs.indexOf(hostIP));
        int index = this->getTabIndexByTitle(hostTitle);
        this->removeTab(index);
    }
}

/**
 * @brief DiscoverTabsWidget::registerDiscover
 * @param discover
 */
void DiscoverTabsWidget::registerDiscover(BaseDiscover *discover)
{
    this->registeredDiscovers.append(discover->getDiscoverTitle());
}

/**
 * @brief DiscoverTabsWidget::addDiscoverTab
 * @param discover
 */
void DiscoverTabsWidget::addDiscoverTab(BaseDiscover *discover)
{
    this->addTab(discover, discover->getDiscoverTitle());
    this->discoverTabs.append(discover->getDiscoverTitle());
}

/**
 * @brief DiscoverTabsWidget::getTabIndexByTitle
 * @param tabTitle
 * @return
 */
int DiscoverTabsWidget::getTabIndexByTitle(QString tabTitle)
{
    for(int x=0; x<this->count(); x++) {
        if (tabTitle == this->tabText(x)) {
            return x;
        }
    }

    return 999999;
}

