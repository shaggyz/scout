#ifndef HOSTSHARES_H
#define HOSTSHARES_H

#include <QWidget>
#include <QDebug>
#include <QIcon>
#include <QDir>
#include <QProcess>
#include <QStandardItem>
#include <QStandardItemModel>

#include "net/host.h"

namespace Ui {
class HostShares;
}

class HostShares : public QWidget
{
    Q_OBJECT

public:

    /**
     * Ovarloaded constructor for host propagation
     * @brief HostShares
     * @param host
     * @param parent
     */
    HostShares(Host* host, QWidget *parent = 0);

    /**
     * Sets the host
     * @brief setHost
     * @param host
     */
    void setHost(Host *host);

    ~HostShares();

public slots:

    /**
     * Sets the shares info into widget
     * @brief updateShareInformation
     */
    void updateShareInformation();

protected:

    /**
     * Host reference
     * @brief host
     */
    Host* host;

protected slots:

    /**
     *
     * @brief openSharesRequest
     */
    void openSharesRequest();

private:
    Ui::HostShares *ui;
};

#endif // HOSTSHARES_H
