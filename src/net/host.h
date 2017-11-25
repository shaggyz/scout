#ifndef HOST_H
#define HOST_H

#include <QObject>
#include <QHash>
#include <QList>
#include <QGeoCoordinate>

class Host : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Host
     * @param parent
     */
    explicit Host(QObject *parent = 0);

    /**
     * @brief Host
     * @param other
     */
    Host(const Host &other);

    /**
     * @brief operator =
     * @param other
     * @return
     */
    Host &operator = (const Host &other);

    /**
     * Host IPV4 address
     * @brief ip
     */
    QString ip;

    /**
     * NetBIOS name
     * @brief netbiosName
     */
    QString netbiosName;

    /**
     * NetBIOS type
     * @brief netbiosType
     */
    QString netbiosType;

    /**
     * MAC Address
     * @brief mac
     */
    QString mac;

    /**
     * SMB Share definition
     * @brief The Share struct
     */
    struct Share {
        QString ip;
        QString type;
        QString name;
        QString comment;
    };

    /**
     * Geoip information
     * @brief The GeoIP struct
     */
    struct GeoIP {
        QString country;
        QString city;
        QGeoCoordinate coordinates;
        QString provider;
    };

    /**
     * Shares collection
     * @brief shares
     */
    QList<Share> shares;

    /**
     * GeoIP info
     * @brief geoIPInformation
     */
    GeoIP geoIPInformation;

protected:


signals:

public slots:
};

#endif // HOST_H
