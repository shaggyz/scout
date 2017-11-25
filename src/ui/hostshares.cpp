#include "hostshares.h"
#include "ui_hostshares.h"

/**
 * Overloaded constructor
 * @brief HostShares::HostShares
 * @param host
 * @param parent
 */
HostShares::HostShares(Host *host, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HostShares)
{
    ui->setupUi(this);
    this->host = host;
    this->updateShareInformation();

    connect(ui->openSharesBtn, SIGNAL(clicked(bool)), this, SLOT(openSharesRequest()));
}

/**
 * @brief HostShares::HostShares
 * @param host
 * @param parent
 */
void HostShares::setHost(Host *host)
{
    this->host = host;
}

/**
 * @brief HostShares::~HostShares
 */
HostShares::~HostShares()
{
    delete ui;
}

/**
 * @brief HostShares::updateShareInformation
 */
void HostShares::updateShareInformation()
{
    Host::Share share;
    QString applicationPath = QDir::currentPath() + "/..";

    QStandardItemModel *model = new QStandardItemModel(this->host->shares.length(), 3, this);

    model->setHorizontalHeaderItem(0, new QStandardItem("Share Type"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Name"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Comments"));

    int row = 0;
    foreach(share, this->host->shares) {

        QIcon typeIcon;

        if (share.type == "Disk") {
            typeIcon = QIcon::fromTheme("drive-harddisk");
        } else if (share.type == "Server") {
            typeIcon = QIcon::fromTheme("computer");
        } else if (share.type == "Ipc") {
            typeIcon = QIcon::fromTheme("network");
        } else if (share.type == "Printer") {
            typeIcon = QIcon::fromTheme("printer");
        } else if (share.type == "Workgroup") {
            typeIcon = QIcon::fromTheme("network-workgroup");
        } else {
            typeIcon = QIcon::fromTheme("folder");
        } 
        
        QStandardItem *typeItem = new QStandardItem(typeIcon, share.type);
        typeItem->setEditable(false);
        model->setItem(row, 0, typeItem);

        QStandardItem *nameItem = new QStandardItem(share.name);
        nameItem->setEditable(false);
        model->setItem(row, 1, nameItem);

        QStandardItem *commentsItem = new QStandardItem(share.comment);
        commentsItem->setEditable(false);
        model->setItem(row, 2, commentsItem );

        row++;
    }

    ui->sharesTable->setModel(model);
    ui->sharesTable->horizontalHeader()->setStretchLastSection(true);
}

/**
 * @brief HostShares::openSharesRequest
 */
void HostShares::openSharesRequest()
{
    QProcess::startDetached("pantheon-files smb://" + this->host->ip + "/");
}
