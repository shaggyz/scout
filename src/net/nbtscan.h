#ifndef NBTSCAN_H
#define NBTSCAN_H

#include <QObject>
#include <QString>
#include <QList>
#include <QProcess>
#include <QDebug>
#include <QStringList>

#include "net/host.h"

class NBTScan : public QObject
{
    Q_OBJECT
public:
    /**
     * Creates new instance of nbtscan wrapper
     * @brief NBTScan
     * @param parent
     */
    explicit NBTScan(QObject *parent = 0);

    /**
     * Repeats option
     * @brief repeats
     */
    int retransmits;

protected:

    /**
     * Internal process for discover
     * @brief process
     */
    QProcess *process;

    /**
     * Generate hosts results
     * @brief hosts
     */
    QList<Host *> getResult(QString rawOutput);

signals:
    /**
     * Emitted when discover starts
     * @brief started
     */
    void started();

    /**
     * Emitted when discover finishes
     * @brief discoverFinished
     * @param results
     */
    void discoverFinished(QList<Host *> results);

    /**
     * Emitted on process error
     * @brief discoverError
     * @param error
     */
    void discoverError(QString error);

    /**
     * Emitted when discover have something to notify
     * @brief onDiscoverOutput
     * @param output
     */
    void discoverOutput(QString output);

protected slots:

    /**
     * Called when internal process finishes
     * @brief onProcessFinished
     * @param processStatus
     */
    void onProcessFinished(int processStatus);

    /**
     * Called when internal process raises an error
     * @brief onProcessError
     * @param error
     */
    void onProcessError(QProcess::ProcessError error);

public slots:

    /**
     * Starts discover
     * @brief discover
     * @param target
     */
    void discover(QString target);

};

#endif // NBTSCAN_H
