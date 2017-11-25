#ifndef SCOUTWIDGET_H
#define SCOUTWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QSplitter>
#include <QList>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include "hoststreewidget.h"
#include "discovertabswidget.h"
#include "scanners/smbscanner.h"

class ScoutWidget : public QWidget
{
    Q_OBJECT
public:

    /**
     * @brief ScoutWidget
     * @param parent
     */
    explicit ScoutWidget(QWidget *parent = 0);

    /**
     * Target textbox
     * @brief targetLineEdit
     */
    QLineEdit *targetLineEdit;

    /**
     * Tree widget
     * @brief treeWidget
     */
    HostsTreeWidget *treeWidget;

    /**
     * SMB Scanner reference
     * @brief smbScanner
     */
    SmbScanner *smbScanner;

protected:

    /**
     * Tabs reference
     * @brief tabs
     */
    DiscoverTabsWidget *tabs;

    /**
     * Creates the needed widgets
     * @brief configureWidgets
     */
    void configureWidgets();

    /**
     * Configures the hosts widget
     * @brief createHostsWidget
     * @return
     */
    QWidget *createHostsWidget();

    /**
     * Creates the tabs widget
     * @brief createTabsWidget
     * @return
     */
    QWidget *createTabsWidget();

    /**
     * Configures the main layout splitter
     * @brief adjustSplitter
     */
    void adjustSplitter(QSplitter *splitter);

    /**
     * Configures and instantiaties the SMB scanner
     * @brief createSMBScanner
     */
    void createSMBScanner();

signals:

public slots:

    /**
     * Sets all discovers to initial state
     * @brief clearWidgets
     */
    void resetWidgets();

    /**
     * Toggles a discover widget tab
     * @brief toggleDiscover
     * @param discoverTitle
     * @param toggle
     */
    void toggleDiscover(QString discoverTitle, bool toggle);
};

#endif // SCOUTWIDGET_H
