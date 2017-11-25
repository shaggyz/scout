#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initializeWindow();
}

/**
 * @brief MainWindow::createMenus
 */
void MainWindow::createMenus()
{
    this->fileMenu = this->menuBar()->addMenu("&File");
    this->fileMenu->addAction(this->newProjectAction);
    this->fileMenu->addSeparator();
    this->fileMenu->addAction(this->exitAction);

    this->menuBar()->addSeparator();

    QMenu *discoverMenu = this->menuBar()->addMenu("Disco&vers");
    discoverMenu->addAction(this->toggleSMBDiscoverAction);

    this->menuBar()->addSeparator();

    this->helpMenu = this->menuBar()->addMenu("&Help");
    this->helpMenu->addAction(this->showAboutAction);
    this->helpMenu->addAction(this->showAboutQtAction);
}

/**
 * @brief MainWindow::createActions
 */
void MainWindow::createActions()
{
    // new project
    this->newProjectAction = new QAction(QIcon::fromTheme("document-new"), "&New scan", this);
    this->newProjectAction->setShortcut(QKeySequence::New);
    this->newProjectAction->setStatusTip("New project");

    // Exit
    this->exitAction = new QAction(QIcon::fromTheme("application-exit"), "E&xit", this);
    this->exitAction->setShortcut((QKeySequence::Quit));
    this->exitAction->setToolTip("Quit the application");

    // Settings
    this->showSettingsAction = new QAction(QIcon::fromTheme("preferences-system"), "Set&tings", this);
    this->showSettingsAction->setShortcut(QKeySequence("Ctrl+T"));
    this->showSettingsAction->setToolTip("Show the settings dialog");

    // About
    this->showAboutAction = new QAction("&About", this);
    this->showAboutAction->setStatusTip("Show the application's About box");

    // About Qt
    this->showAboutQtAction = new QAction("About Qt", this);
    this->showAboutQtAction->setStatusTip("Show the Qt library's About box");

    // Toggle SMB discover
    this->toggleSMBDiscoverAction = new ToggleDiscoverAction(this);
    this->toggleSMBDiscoverAction->setDiscoverTitle(this->mainWidget->smbScanner->getDiscoverTitle());
    this->toggleSMBDiscoverAction->setText("Toggle SMB discover");
    this->toggleSMBDiscoverAction->setStatusTip("Show/hide the SMB discover tab");
    this->toggleSMBDiscoverAction->setCheckable(true);
    this->toggleSMBDiscoverAction->setChecked(true);
}

/**
 * @brief MainWindow::createToolbars
 */
void MainWindow::createToolbars()
{
    QList<QToolBar *> toolbars = this->findChildren<QToolBar *>();
    QToolBar *fileToolbar = toolbars.first();
    fileToolbar->addAction(this->newProjectAction);
    fileToolbar->addSeparator();
    fileToolbar->addAction(this->showSettingsAction);
    fileToolbar->addAction(this->exitAction);
}

/**
 * @brief MainWindow::initializeWindow
 */
void MainWindow::initializeWindow()
{
    // Sets root application path
    QString applicationPath = QDir::currentPath() + "/..";
    this->applicationRootDirectory = applicationPath;

    // Window configuration
    this->setWindowTitle(QApplication::applicationName());
    QIcon applicationIcon(this->applicationRootDirectory + "/resources/icons/lis.png");
    this->setWindowIcon(applicationIcon);
    this->resize(1024, 768);

    // Status bar
    this->statusBar()->showMessage("Ready");

    // Main widget
    this->mainWidget = new ScoutWidget(this);
    this->setCentralWidget(this->mainWidget);

    // self.settingsDialog = SettingsDialog()

    // Create application actions
    this->createActions();

    // Tool bar
    this->createToolbars();

    // Menu bar configuration
    this->createMenus();

    // Connect signals
    this->connectSignals();
}

/**
 * @brief MainWindow::connectSignals
 */
void MainWindow::connectSignals()
{
    // Exit
    connect(this->exitAction, SIGNAL(triggered(bool)), this, SLOT(quitApplication()));
    // New project
    connect(this->newProjectAction, SIGNAL(triggered(bool)), this, SLOT(newProject()));
    // Settings
    connect(this->showSettingsAction, SIGNAL(triggered(bool)), this, SLOT(showSettingsDialog()));
    // About
    connect(this->showAboutAction, SIGNAL(triggered(bool)), this, SLOT(showAboutDialog()));
    // About Qt
    connect(this->showAboutQtAction, SIGNAL(triggered(bool)), QApplication::instance(), SLOT(aboutQt()));
    // Toggle SMB discover
    connect(this->toggleSMBDiscoverAction, SIGNAL(discoverToggled(QString,bool)), this->mainWidget, SLOT(toggleDiscover(QString,bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::quitApplication
 */
void MainWindow::quitApplication()
{
    QApplication::quit();
}

/**
 * @brief MainWindow::newProject
 */
void MainWindow::newProject()
{
    this->mainWidget->targetLineEdit->clear();
    this->mainWidget->treeWidget->clear();
    this->mainWidget->resetWidgets();

    qDebug() << "New project action triggered";
}

/**
 * @brief MainWindow::showSettings
 */
void MainWindow::showSettingsDialog()
{
    qDebug() << "Show settings dialog action triggered";
}

/**
 * @brief MainWindow::showAboutDialog
 */
void MainWindow::showAboutDialog()
{
    QString aboutText = "<p>A simple <b>Scanner</b> used as frontend for many "
            "network scanning tools like: <i>nmap, nbtscan, smbclient, "
            "etc.</i>.</p>"
            "<p>Author: Nicol&aacute;s Daniel Palumbo [n" "@xi" "nax.net]<br>"
            "License: MIT</p>";

    QMessageBox::about(this, "Scout, multi-tool network scanner", aboutText);
}
