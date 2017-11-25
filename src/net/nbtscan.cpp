#include "nbtscan.h"

NBTScan::NBTScan(QObject *parent) : QObject(parent)
{
    this->retransmits = 0;
}

/**
 * Generates the result collection from raw output
 * @brief NBTScan::getResult
 * @param rawOutput
 * @return
 */
QList<Host *> NBTScan::getResult(QString rawOutput)
{
    QStringList entries = rawOutput.trimmed().split("\n");
    QList<Host *> results;

    if (rawOutput.length()) {

        emit this->discoverOutput(rawOutput);

        foreach(const QString &entry, entries) {
            QStringList parts = entry.split("%");

            if (5 != parts.length()) {
                qDebug() << "Unknown format for entry: '" + entry + "'";
                continue;
            }

            Host *host = new Host();
            host->ip = parts.at(0).trimmed();
            host->netbiosName = parts.at(1).trimmed();
            host->netbiosType = parts.at(2).trimmed();
            host->mac = parts.at(4).trimmed();

            results.append(host);
        }
    } else {
        emit this->discoverOutput("<i style=\"color: grey\">No results from this command</i>");
    }

    return results;
}

/**
 * @brief NBTScan::discover
 * @param target
 */
void NBTScan::discover(QString target)
{
    emit this->started();

    this->process = new QProcess();

    QList<QString> args;
    args.append("-s%");
    args.append("-q");

    if (this->retransmits > 0) {
        args.append("-m" + QString::number(this->retransmits));
    }

    args.append(target);

    this->process->setProgram("/usr/bin/nbtscan");
    this->process->setArguments(args);

    connect(this->process, SIGNAL(finished(int)), this, SLOT(onProcessFinished(int)));
    connect(this->process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(onProcessError(QProcess::ProcessError)));

    QString command = this->process->program() + " " + this->process->arguments().join(" ");
    emit this->discoverOutput("<b style=\"color: rgb(145, 255, 98);\">" + command + "</b>");

    this->process->start();
}

/**
 * @brief NBTScan::onProcessFinished
 * @param processStatus
 */
void NBTScan::onProcessFinished(int processStatus)
{
    QString output = this->process->readAll();

    if (this->process->isOpen()) {
        this->process->close();
    }

    QList<Host *> hosts = this->getResult(output);

    emit this->discoverFinished(hosts);
}

/**
 * @brief NBTScan::onProcessError
 * @param error
 */
void NBTScan::onProcessError(QProcess::ProcessError error)
{
    QString errorMessage = "Process ERROR: ";

    switch (error) {
        case 0:
            errorMessage.append("Program failed to start. Maybe missing executable?");
        break;
        case 1:
            errorMessage.append("Program crashed.");
        break;
        case 2:
            errorMessage.append("Timeout reached.");
        break;
        case 3:
        case 4:
            errorMessage.append("I/O Error.");
        break;
        case 5:
        default:
            errorMessage.append("Unknown error.");
        break;
    }

    if (this->process->isOpen()) {
        this->process->close();
    }

    emit discoverOutput("<p style=\"color: red\">" + errorMessage + "</p>");
    emit discoverError(errorMessage);
}

