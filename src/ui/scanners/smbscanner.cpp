#include "smbscanner.h"
#include "ui_smbscanner.h"

/**
 * @brief SmbScanner::SmbScanner
 * @param parent
 */
SmbScanner::SmbScanner(QWidget *parent) :
    BaseDiscover(parent),
    ui(new Ui::SmbScanner)
{
    this->discoverTitle = "&SMB discover";
    ui->setupUi(this);
    this->configureWidgets();
}

/**
 * @brief SmbScanner::~SmbScanner
 */
SmbScanner::~SmbScanner()
{
    delete ui;
}

/**
 * @brief SmbScanner::setTargetEdit
 * @param targetLineEdit
 */
void SmbScanner::setTargetEdit(QLineEdit *targetLineEdit)
{
    this->targetLineEdit = targetLineEdit;
}

/**
 * @brief SmbScanner::setTreeWidger
 * @param treeWidget
 */
void SmbScanner::setTreeWidget(HostsTreeWidget *treeWidget)
{
   this->treeWidget = treeWidget;
}

/**
 * @brief SmbScanner::startDiscover
 */
void SmbScanner::startDiscover()
{
    ui->discoverFrame->setEnabled(false);
    NBTScan *nbtscan = new NBTScan(this);
    nbtscan->retransmits = ui->repeatsSpin->value();

    connect(nbtscan, SIGNAL(discoverFinished(QList<Host *>)), this, SLOT(onDiscoverFinished(QList<Host *>)));
    connect(nbtscan, SIGNAL(discoverOutput(QString)), ui->discoverOutputTextEdit, SLOT(append(QString)));

    nbtscan->discover(this->targetLineEdit->text().trimmed());
}

/**
 * @brief SmbScanner::startCollector
 */
void SmbScanner::startCollector()
{
    int hostsCount = this->treeWidget->getHosts().length();

    if (hostsCount == 0) {
        qDebug() << "Collector aborted since no SMB hosts detected";
        this->ui->discoverFrame->setEnabled(true);
        this->ui->collectorFrame->setEnabled(true);
        return;
    }

    ui->collectorFrame->setEnabled(false);

    SMBClient *smbclient = new SMBClient(this);
    connect(smbclient, SIGNAL(collectorFinished(QList<Host*>)), this, SLOT(onCollectorFinished(QList<Host*>)));
    connect(smbclient, SIGNAL(collectorOutput(QString)), ui->collectorOutputTextEdit, SLOT(append(QString)));
    connect(smbclient, SIGNAL(progressUpdate(int)), ui->collectorProgressBar, SLOT(setValue(int)));

    ui->collectorProgressBar->setMaximum(hostsCount);
    ui->collectorProgressBar->setValue(0);

    smbclient->start(this->treeWidget->getHosts());
}

/**
 * @brief SmbScanner::onDiscoverFinished
 * @param results
 */
void SmbScanner::onDiscoverFinished(QList<Host *> results)
{
    if (!ui->collectSharesCheckbox->isChecked()) {
        ui->discoverFrame->setEnabled(true);
    }

    if (results.length() > 0) {
        ui->collectorFrame->setEnabled(true);
    }

    emit this->finished(results);

    if (ui->collectSharesCheckbox->isChecked()) {
        this->startCollector();
    }
}

/**
 * @brief SmbScanner::onCollectorFinished
 * @param results
 */
void SmbScanner::onCollectorFinished(QList<Host *> results)
{
    ui->collectorFrame->setEnabled(true);

    if (ui->collectSharesCheckbox->isChecked()) {
        ui->discoverFrame->setEnabled(true);
    }

    emit this->finished(results);
}

/**
 * @brief SmbScanner::resetWidgets
 */
void SmbScanner::resetWidgets()
{
    ui->discoverOutputTextEdit->clear();
    ui->collectorOutputTextEdit->clear();
    ui->collectorFrame->setEnabled(false);
    ui->repeatsSpin->setValue(0);
    ui->collectSharesCheckbox->setChecked(false);
    ui->discoverButton->setEnabled(true);
    ui->collectorProgressBar->setValue(0);
}

/**
 * @brief SmbScanner::configureWidgets
 */
void SmbScanner::configureWidgets()
{
    connect(ui->discoverButton, SIGNAL(clicked(bool)), this, SLOT(startDiscover()));
    connect(ui->collectSharesButton, SIGNAL(clicked(bool)), this, SLOT(startCollector()));
}
