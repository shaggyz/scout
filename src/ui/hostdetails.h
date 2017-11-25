#ifndef HOSTDETAILS_H
#define HOSTDETAILS_H

#include <QWidget>
#include <QDir>
#include <QFile>
#include <QGeoCoordinate>
#include <QtWebKitWidgets/QWebView>

#include "net/host.h"
#include "net/geoip.h"
#include "ui/hostshares.h"

namespace Ui {
class HostDetails;
}

class HostDetails : public QWidget
{
    Q_OBJECT

public:
    explicit HostDetails(QWidget *parent = 0);
    ~HostDetails();
    /**
     * Sets internal host info
     * @brief setHost
     * @param host
     */
    void setHost(Host *host);

    /**
     * Sets the hosts details tab
     * @brief configureHostDetailsTab
     */
    void updateHostDetailsTab();

protected:

    /**
     * Updates the geolocation data for this host
     * @brief updateHostGeolocationData
     */
    void updateHostGeolocationData();

    /**
     * Updates the google maps webview
     * @brief updateGoolgeMaps
     * @param coordinates
     */
    void updateGoolgeMaps(QGeoCoordinate coordinates);

    /**
     * Creates the host SMB shares tab
     * @brief addSharesTab
     */
    void addSharesTab();

protected slots:

    /**
     * Sets the updated geoip data on GUI
     * @brief onGeoIpDataUpdated
     */
    void onGeoIpDataUpdated(Host::GeoIP geoIPData);

private:
    Ui::HostDetails *ui;
    Host *host;
};

#endif // HOSTDETAILS_H
