#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QString>
#include <QFileInfo>
#include <QDebug>
#include <QDir>
#include <QKeySequence>
#include <QApplication>
#include <QWidget>
#include <QToolBar>
#include <QList>

#include "scoutwidget.h"
#include "ui/scanners/smbscanner.h"
#include "ui/actions/togglediscoveraction.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    /**
     * File menu handler
     * @brief fileMenu
     */
    QMenu *fileMenu;

    /**
     * Help menu
     * @brief helpMenu
     */
    QMenu *helpMenu;

    /**
     * Action: New project
     * @brief newProjectAction
     */
    QAction *newProjectAction;

    /**
     * Action: Exit program
     * @brief exitAction
     */
    QAction *exitAction;

    /**
     * Action: show settings dialog
     * @brief showSettingsAction
     */
    QAction *showSettingsAction;

    /**
     * Action: show about dialog
     * @brief showAboutAction
     */
    QAction *showAboutAction;

    /**
     * Action: show Qt's about dialog
     * @brief showAcoutQtAction
     */
    QAction *showAboutQtAction;

    /**
     * Shows/Hide the SMB discover
     * @brief toggleSMBDiscoverAction
     */
    ToggleDiscoverAction *toggleSMBDiscoverAction;

    /**
     * Root directory path
     * @brief applicationRootDirectory
     */
    QString applicationRootDirectory;

    /**
     * Main widget pointer
     * @brief mainWidget
     */
    ScoutWidget *mainWidget;

public:
    /**
     * Main window constructor
     * @brief MainWindow
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * Create all menus for main window menu-bar
     * @brief createMenus
     */
    void createMenus();

    /**
     * Create application global actions
     * @brief createActions
     */
    void createActions();

    /**
     * Configure window toolbars
     * @brief createToolbars
     */
    void createToolbars();

    /**
     * Setup depenences needed for main window in order to bootstrap
     * @brief initializeWindow
     */
    void initializeWindow();

    /**
     * Connect global signals
     * @brief connectSignals
     */
    void connectSignals();

    ~MainWindow();

public slots:

    /**
     * Terminates the program
     * @brief quitApplication
     */
    void quitApplication();

    /**
     * Starts new project
     * @brief newProject
     */
    void newProject();

    /**
     * @brief showSettings
     */
    void showSettingsDialog();

    /**
     * @brief showAboutDialog
     */
    void showAboutDialog();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
