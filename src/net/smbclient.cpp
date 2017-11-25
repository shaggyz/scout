#include "smbclient.h"

/**
 * @brief SMBClient::SMBClient
 * @param parent
 */
SMBClient::SMBClient(QObject *parent) : QObject(parent)
{
    this->pool = QList<QProcess *>();
    this->hostsRemaining = 0;
}

/**
 * @brief SMBClient::prepareResult
 */
void SMBClient::prepareResult()
{
    // Iterate process and add result to internal results buffer
    QProcess *process;
    foreach(process, this->pool) {

        QString rawOutput = process->readAll();
        emit this->collectorOutput(rawOutput);
        QProcessEnvironment env = process->processEnvironment();
        QString ip = env.value("HOST");

        QList<Host::Share> shares = this->parseProcessOutput(ip , rawOutput);
        this->addSharesToHost(ip, shares);

        if (process->isOpen()) {
            process->close();
        }

    }

    emit this->collectorFinished(this->results);
}

/**
 * @brief SMBClient::parseOutput
 * @return
 */
QList<Host::Share> SMBClient::parseProcessOutput(QString ip, QString rawOutput)
{
    QList<Host::Share> shares;
    QStringList shareLines = rawOutput.split("\n");

    QString line;
    foreach(line, shareLines) {
        QStringList parts = line.split("|");
        if (parts.length() > 1) {
            Host::Share share;
            share.ip = ip;
            share.type = parts.at(0).trimmed();
            share.name = parts.at(1).trimmed();
            share.comment = parts.at(2).trimmed();
            shares.append(share);
        }
    }

    return shares;
}

/**
 * @brief SMBClient::addSharesToHost
 * @param ip
 * @param shares
 */
void SMBClient::addSharesToHost(QString ip, QList<Host::Share> shares)
{
    Host *host;
    foreach(host, this->results) {
        if (QString::compare(host->ip, ip)) {
            host->shares = shares;
            // Nothing more to do here
            return;
        }
    }
}

/**
 * @brief SMBClient::start
 * @param hosts
 */
void SMBClient::start(QList<Host *> hosts)
{
    if(hosts.length() == 0) {
        emit this->collectorError("No hosts to collect");
        return;
    }

    this->hostsRemaining = hosts.length();
    this->results = hosts;

    QString program = "/usr/bin/smbclient";

    Host *host;
    foreach(host, hosts) {
        QProcess *process = new QProcess(this);

        QProcessEnvironment env = QProcessEnvironment();
        env.insert("HOST", host->ip);
        process->setProcessEnvironment(env);

        connect(process, SIGNAL(finished(int)), this, SLOT(onProcessFinished(int)));
        connect(process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(onProcessError(QProcess::ProcessError)));

        QStringList args;
        args.append("-g");
        args.append("-N");
        args.append("-L" + host->ip);

        process->start(program, args);

        QString command = process->program() + " " + process->arguments().join(" ");
        emit this->collectorOutput("<b style=\"color: rgb(145, 255, 98);\">" + command + "</b>");

        this->pool.append(process);
    }
}

/**
 * @brief SMBClient::onSingleHostFinished
 * @param rawOutput
 */
void SMBClient::onProcessFinished(int status)
{
    this->hostsRemaining--;
    emit this->progressUpdate(this->results.length() - this->hostsRemaining);

    if (0 != status) {
        qDebug() << "Process finished with strange status: " + QString::number(status);
    }

    if (0 == this->hostsRemaining) {
        this->prepareResult();
    }
}

/**
 * @brief SMBClient::onProcessError
 */
void SMBClient::onProcessError(QProcess::ProcessError error)
{
    this->hostsRemaining--;
    emit this->progressUpdate(this->results.length() - this->hostsRemaining);

    qDebug() << "Collector process ERROR with code: " + QString::number(error);

    if (0 == this->hostsRemaining) {
        this->prepareResult();
    }
}
