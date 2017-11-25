#include "hostdetails.h"
#include "ui_hostdetails.h"

HostDetails::HostDetails(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HostDetails)
{
    ui->setupUi(this);
}

/**
 * @brief HostDetails::~HostDetails
 */
HostDetails::~HostDetails()
{
    delete ui;
}

/**
 * @brief HostDetails::setHost
 * @param host
 */
void HostDetails::setHost(Host *host)
{
    this->host = host;
}

/**
 * Called after set host, initializes the widget
 * @brief HostDetails::configureHostDetailsTab
 */
void HostDetails::updateHostDetailsTab()
{
    ui->ipTxt->setText(this->host->ip);
    this->updateHostGeolocationData();

    if (this->host->shares.length() > 0) {
        this->addSharesTab();
    }
}

/**
 * @brief HostDetails::updateHostGeolocationData
 */
void HostDetails::updateHostGeolocationData()
{
    GeoIP *geoIP = new GeoIP(this);
    connect(geoIP, SIGNAL(lookupFinished(Host::GeoIP)), this, SLOT(onGeoIpDataUpdated(Host::GeoIP)));
    geoIP->lookup(this->host);
}

/**
 * @brief HostDetails::updateGoolgeMaps
 * @param coordinates
 */
void HostDetails::updateGoolgeMaps(QGeoCoordinate coordinates)
{
    QString applicationPath = QDir::currentPath() + "/..";
    QFile file(applicationPath + "/resources/html/googlemaps.html");

    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot read the google maps html file!";
        return;
    }

    QString html(file.readAll());
    html.replace("<lat>", QString::number(coordinates.latitude(), 'f'));
    html.replace("<lon>", QString::number(coordinates.longitude(), 'f'));
    html.replace("<zoom>", QString::number(12));
    html.replace("<ip>", this->host->ip);

    file.close();

    ui->googleMapsWebView->setHtml(html);
    ui->googleMapsWebView->reload();
}

/**
 * @brief HostDetails::addSharesTab
 */
void HostDetails::addSharesTab()
{
    HostShares *hostSharesWidget = new HostShares(this->host, this);

    this->ui->hostTabs->addTab(hostSharesWidget, "SMB Shares");


}

/**
 * @brief HostDetails::onGeoIpDataUpdated
 */
void HostDetails::onGeoIpDataUpdated(Host::GeoIP geoIPData)
{
    this->host->geoIPInformation = geoIPData;
    ui->cityTxt->setText(geoIPData.city);
    ui->countryTxt->setText(geoIPData.country);
    ui->ISPtxt->setText(geoIPData.provider);

    if (geoIPData.coordinates.isValid()) {
        ui->latitudeTxt->setText(QString::number(geoIPData.coordinates.latitude(), 'f'));
        ui->longitudeTxt->setText(QString::number(geoIPData.coordinates.longitude(), 'f'));

        this->updateGoolgeMaps(geoIPData.coordinates);
    }
}
