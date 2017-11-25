#include "scoutwidget.h"

ScoutWidget::ScoutWidget(QWidget *parent) : QWidget(parent)
{
    this->configureWidgets();
}

/**
 * @brief ScoutWidget::configureWidgets
 */
void ScoutWidget::configureWidgets()
{
    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QSplitter *splitter = new QSplitter();

    splitter->addWidget(this->createHostsWidget());

    splitter->addWidget(this->createTabsWidget());

    // Open host details
    connect(this->treeWidget, SIGNAL(openHostDetailsRequest(Host*)), this->tabs, SLOT(addHostTab(Host*)));

    mainLayout->addWidget(splitter);
    this->adjustSplitter(splitter);

    this->setLayout(mainLayout);
}

/**
 * @brief ScoutWidget::createHostsWidget
 * @return
 */
QWidget *ScoutWidget::createHostsWidget()
{
    QWidget *hosts = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout();

    layout->setContentsMargins(4, 4, 4, 4);

    // Host text edit
    this->targetLineEdit = new QLineEdit(this);
    this->targetLineEdit->setPlaceholderText("192.168.1.0/24");
    this->targetLineEdit->setText("192.168.1.0/24");
    //this->targetLineEdit->setInputMask("dd0.dd0.dd0.dd0/dd");

    layout->addWidget(this->targetLineEdit);

    // Hosts tree
    this->treeWidget = new HostsTreeWidget(this);

    layout->addWidget(this->treeWidget);

    // Tree buttons
    QWidget *treeActions = new QWidget(this);
    QHBoxLayout *treeActionsLayout = new QHBoxLayout();
    treeActionsLayout->setContentsMargins(0, 0, 0, 0);
    QPushButton *expandButton = new QPushButton("Expand all");
    QPushButton *collapseButton = new QPushButton("Collapase all");

    connect(expandButton, SIGNAL(clicked(bool)), this->treeWidget, SLOT(expandAll()));
    connect(collapseButton, SIGNAL(clicked(bool)), this->treeWidget, SLOT(collapseAll()));

    treeActionsLayout->addWidget(expandButton);
    treeActionsLayout->addWidget(collapseButton);
    treeActions->setLayout(treeActionsLayout);

    layout->addWidget(treeActions);

    hosts->setLayout(layout);

    return hosts;
}

/**
 * @brief ScoutWidget::createTabsWidget
 * @return
 */
QWidget *ScoutWidget::createTabsWidget()
{
    QWidget *discovers = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(4, 4, 4, 4);

    this->tabs = new DiscoverTabsWidget();

    // Discovers
    this->createSMBScanner();

    // Discover register on tabs
    this->tabs->registerDiscover(this->smbScanner);

    // Default opened discovers
    this->tabs->addDiscoverTab(this->smbScanner);

    layout->addWidget(this->tabs);
    discovers->setLayout(layout);

    return discovers;
}

/**
 * @brief ScoutWidget::adjustSplitter
 */
void ScoutWidget::adjustSplitter(QSplitter *splitter)
{
    int leftPanelSize = 30 * splitter->size().width() / 100;
    int rightPanelSIze = splitter->size().width() - leftPanelSize;

    QList<int> sizes;
    sizes.append(leftPanelSize);
    sizes.append(rightPanelSIze);

    splitter->setSizes(sizes);
}

void ScoutWidget::createSMBScanner()
{
    // SMB Scanner
    this->smbScanner = new SmbScanner(this);
    this->smbScanner->setTargetEdit(this->targetLineEdit);
    this->smbScanner->setTreeWidget(this->treeWidget);

    connect(this->smbScanner, SIGNAL(finished(QList<Host*>)), this->treeWidget, SLOT(updateHosts(QList<Host*>)));
}

/**
 * @brief ScoutWidget::clearWidgets
 */
void ScoutWidget::resetWidgets()
{
    this->smbScanner->resetWidgets();
}

/**
 * @brief ScoutWidget::toggleDiscover
 * @param discoverTitle
 * @param toggle
 */
void ScoutWidget::toggleDiscover(QString discoverTitle, bool toggle)
{
    if (!toggle) {
        this->tabs->removeDiscoverTab(discoverTitle);
    } else {
        // Add discovers by name
        if (this->smbScanner->getDiscoverTitle() == discoverTitle) {
            this->tabs->addDiscoverTab(this->smbScanner);
        }
    }
}

