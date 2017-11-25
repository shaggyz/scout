#ifndef DISCOVERTABSWIDGET_H
#define DISCOVERTABSWIDGET_H

#include <QTabWidget>
#include <QDebug>
#include <QIcon>
#include <QDir>
#include <QStringList>

#include "net/host.h"
#include "ui/hostdetails.h"
#include "ui/scanners/smbscanner.h"
#include "ui/scanners/basediscover.h"

class DiscoverTabsWidget : public QTabWidget
{
    Q_OBJECT
public:

    /**
     * Constructor
     * @brief DiscoverTabsWidget
     * @param parent
     */
    explicit DiscoverTabsWidget(QWidget *parent = 0);

    /**
     * Host details title
     * @brief HOST_DETAILS_TITLE
     */
    static const QString HOST_DETAILS_TITLE;

    /**
     * SmbScanner widget reference singleton
     * @brief SMBScanner
     */
    SmbScanner* SMBScanner;

private:

    /**
     * Host detail opened tabs list
     * @brief hostDetailsTabs
     */
    QStringList hostDetailsTabs;

    /**
     * Collection of current opened discover tabs names
     * @brief discoverTabs
     */
    QStringList discoverTabs;

    /**
     * Collection of activated and registered discover names
     * @brief registeredDiscovers
     */
    QStringList registeredDiscovers;

protected slots:

    /**
     * Called
     * @brief onCloseTabRequest
     * @param index
     */
    void onCloseTabRequest(int index);

public slots:
    /**
     * Adds a new host tab
     * @brief addHostTab
     * @param host
     */
    void addHostTab(Host *host);

    /**
     * Removes a discover by its tab title and index.
     * Please use constants to avoid typo-like errors.
     *
     * @brief removeDiscoverTab
     * @param discoverTitle
     * @param index
     */
    void removeDiscoverTab(QString discoverTitle);

    /**
     * Removes a host tab from internal collection from the tab title
     *
     * @brief removeHostTab
     * @param hostTitle
     * @param index
     */
    void removeHostTab(QString hostTitle);

    /**
     * Registers a discover as valid
     * @brief registerDiscover
     * @param discover
     */
    void registerDiscover(BaseDiscover* discover);

    /**
     * Adds a new tab with given discover
     * @brief addDiscoverTab
     * @param discover
     */
    void addDiscoverTab(BaseDiscover* discover);

    /**
     * Returns the tab index from its title, if exists
     * @brief getTabIndexByTitle
     * @param tabTitle
     * @return
     */
    int getTabIndexByTitle(QString tabTitle);

};

#endif // DISCOVERTABSWIDGET_H
