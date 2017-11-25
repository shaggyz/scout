#ifndef SMBCLIENT_H
#define SMBCLIENT_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QList>
#include <QProcess>
#include <QProcessEnvironment>
#include <QStringList>

#include "net/host.h"

class SMBClient : public QObject
{
    Q_OBJECT
public:

    /**
     * Constructor overload
     * @brief SMBClient
     * @param parent
     */
    explicit SMBClient(QObject *parent = 0);

    /**
     * Internal process pool
     * @brief pool
     */
    QList<QProcess *> pool;

private:
    /**
     * Hosts (process) remaining counter
     * @brief hostsRemaining
     */
    int hostsRemaining;

    /**
     * Results buffer.
     * @brief results
     */
    QList<Host *> results;

protected:

    /**
     * Prepare result and trigger collectorFinished() signal
     * @brief prepareResult
     */
    void prepareResult();

    /**
     * Creates a share struct from smbclient raw output
     * @brief parseOutput
     * @return
     */
    QList<Host::Share> parseProcessOutput(QString ip, QString rawOutput);

    /**
     * Adds a share list to internal results buffer
     * @brief addSharesToHost
     * @param ip
     * @param shares
     */
    void addSharesToHost(QString ip, QList<Host::Share> shares);

signals:
    /**
     * Emitted when colector raises an error
     * @brief collectorError
     * @param error
     */
    void collectorError(QString error);

    /**
     * Emitted when all process finishes
     * @brief collectorFinished
     * @param results
     */
    void collectorFinished(QList<Host *> results);

    /**
     * Emitted when collector have some to notify
     * @brief collectorOutput
     * @param output
     */
    void collectorOutput(QString output);

    /**
     * Emitted when process (number of hosts scanned) changes
     * @brief progressUpdate
     * @param progress
     */
    void progressUpdate(int progress);

protected slots:

    /**
     * Called when a single proces (for a single host) finishes.
     * @brief onSingleHostFinished
     * @param status
     */
    void onProcessFinished(int status);

    /**
     * Called when a host process reaches error state
     * @brief onProcessError
     * @param error
     */
    void onProcessError(QProcess::ProcessError error);

public slots:

    /**
     * Starts the collector
     * @brief start
     * @param hosts
     */
    void start(QList<Host *> hosts);

};

#endif // SMBCLIENT_H
