#include "geoip.h"

/**
 * @brief GeoIP::GeoIP
 * @param parent
 */
GeoIP::GeoIP(QObject *parent) : QObject(parent)
{

}

/**
 * @brief GeoIP::parseResponse
 * @param rawOutput
 * @return
 */
Host::GeoIP GeoIP::parseResponse(QString rawOutput)
{
    Host::GeoIP geodata = this->IPnotFoundResponse();

    QStringList lines = rawOutput.split("\n");
    QString line;

    foreach(line, lines) {
        if (line.length() < 1) {
            continue;
        }

        QStringList keyVal = line.split(":");
        QString key = keyVal.at(0);
        QString value = keyVal.at(1);

        // Country
        if (key == "GeoIP Country Edition") {
            geodata.country = value;
        }

        // City and location
        if (key == "GeoIP City Edition, Rev 1") {

            QStringList cityParts = value.split(",");
            if (cityParts.length() > 2) {
                QString state = cityParts.at(2).trimmed();
                QString city = cityParts.at(3).trimmed();
                QString zip = cityParts.at(4).trimmed();
                QString latitudeStr = cityParts.at(5).trimmed();
                QString longitudeStr = cityParts.at(6).trimmed();

                geodata.city = state + ", " + city + ", " + zip;

                QGeoCoordinate coordinates;
                coordinates.setLatitude(latitudeStr.toDouble());
                coordinates.setLongitude(longitudeStr.toDouble());

                geodata.coordinates = coordinates;
            }

        }

        // ISP
        if (key == "GeoIP ASNum Edition") {
            geodata.provider = value;
        }

    }
    return geodata;
}

/**
 * @brief GeoIP::IPnotFoundResponse
 * @return
 */
Host::GeoIP GeoIP::IPnotFoundResponse()
{
    Host::GeoIP geodata;

    geodata.city = "IP not found";
    geodata.coordinates = QGeoCoordinate();
    geodata.country = "IP not found";
    geodata.provider = "IP not found";

    return geodata;
}

/**
 * @brief GeoIP::lookup
 * @param ip
 */
void GeoIP::lookup(QString ip)
{
    emit this->lookupStarted();

    this->process = new QProcess(this);
    QStringList args;
    args.append(ip);

    this->process->setProgram("/usr/bin/geoiplookup");
    this->process->setArguments(args);

    connect(this->process, SIGNAL(finished(int)), this, SLOT(onProcessFinished(int)));
    connect(this->process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(onProcessError(QProcess::ProcessError)));

    this->process->start(QProcess::ReadOnly);
}

/**
 * @brief GeoIP::lookup
 * @param host
 */
void GeoIP::lookup(Host *host)
{
    this->lookup(host->ip);
}

/**
 * @brief GeoIP::processError
 * @param error
 */
void GeoIP::onProcessError(QProcess::ProcessError error)
{
    qDebug() << "Error process code: " + QString::number(error);
}

/**
 * @brief GeoIP::processFinishes
 * @param status
 */
void GeoIP::onProcessFinished(int status)
{
    qDebug() << "Process finishes with code: " + QString::number(status);
    Host::GeoIP geoData = this->parseResponse(this->process->readAll());
    emit this->lookupFinished(geoData);
}

