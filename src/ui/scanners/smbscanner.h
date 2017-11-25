#ifndef SMBSCANNER_H
#define SMBSCANNER_H

#include <QWidget>
#include <QLineEdit>
#include <QList>
#include <QDebug>

#include "ui/scanners/basediscover.h"
#include "net/nbtscan.h"
#include "net/smbclient.h"
#include "net/host.h"
#include "ui/hoststreewidget.h"

namespace Ui {
class SmbScanner;
}

class SmbScanner : public BaseDiscover
{
    Q_OBJECT

public:
    explicit SmbScanner(QWidget *parent = 0);

    ~SmbScanner();

signals:

    /**
     * Emitted when results are ready
     * @brief finished
     * @param results
     */
    void finished(QList<Host *> results);

public slots:
    /**
     * Sets the target widget lne edit
     * @brief setTargetEdit
     * @param targetLineEdit
     */
    void setTargetEdit(QLineEdit *targetLineEdit);

    /**
     * Sets the tree widget reference
     * @brief setTreeWidger
     * @param treeWidget
     */
    void setTreeWidget(HostsTreeWidget *treeWidget);

    /**
     * Start the host discover
     * @brief startDiscover
     */
    void startDiscover();

    /**
     * Start the shares collector
     * @brief startCollector
     */
    void startCollector();

    /**
     * Called when discover finishes
     * @brief onDiscoverFinished
     * @param results
     */
    void onDiscoverFinished(QList<Host *> results);

    /**
     * Callend when collector finishes
     * @brief onCollectorFinished
     * @param results
     */
    void onCollectorFinished(QList<Host *> results);

    /**
     * Resets all scanner widgets to the initial state
     * @brief resetWidgets
     */
    void resetWidgets();

private:
    Ui::SmbScanner *ui;

    /**
     * Target line edit
     * @brief targetLineEdit
     */
    QLineEdit *targetLineEdit;

    /**
     * treeWidget reference
     * @brief treeWidget
     */
    HostsTreeWidget *treeWidget;

    /**
     * Configures UI
     * @brief configureWidgets
     */
    void configureWidgets();
};

#endif // SMBSCANNER_H
