#ifndef GEOIP_H
#define GEOIP_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QString>
#include <QPair>
#include <QStringList>

#include "net/host.h"

class GeoIP : public QObject
{
    Q_OBJECT
public:
    explicit GeoIP(QObject *parent = 0);
protected:

    /**
     * Internal process
     * @brief process
     */
    QProcess *process;

    /**
     * Parses command response
     * @brief parseResponse
     * @param rawOutput
     * @return
     */
    Host::GeoIP parseResponse(QString rawOutput);

    /**
     * Creates a IP not found response
     * @brief IPnotFoundResponse
     * @return
     */
    Host::GeoIP IPnotFoundResponse();

signals:

    /**
     * Emitted when lookup finishes
     * @brief lookupFinished
     */
    void lookupFinished(Host::GeoIP);

    /**
     * Emitted when lookup raises error
     * @brief lookupError
     * @param error
     */
    void lookupError(QString error);

    /**
     * Emitted when lookup have something to identify
     * @brief lookupOutput
     * @param output
     */
    void lookupOutput(QString output);

    /**
     * Emitted when lookup starts
     * @brief lookupStarted
     */
    void lookupStarted();

public slots:
    /**
     * Start geoip lookup
     * @brief lookup
     * @param ip
     */
    void lookup(QString ip);

    /**
     * Lookup from host
     * @brief lookup
     * @param host
     */
    void lookup(Host *host);

protected slots:

    /**
     * Called on internal process error
     * @brief processError
     * @param error
     */
    void onProcessError(QProcess::ProcessError error);

    /**
     * Called when process finishes
     * @brief processFinishes
     * @param status
     */
    void onProcessFinished(int status);

};

#endif // GEOIP_H
