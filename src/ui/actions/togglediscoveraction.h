#ifndef TOGGLEDISCOVERACTION_H
#define TOGGLEDISCOVERACTION_H

#include <QObject>
#include <QAction>
#include <QString>

class ToggleDiscoverAction : public QAction
{
    Q_OBJECT
public:
    explicit ToggleDiscoverAction(QObject *parent = 0);
    void setDiscoverTitle(QString title);
    QString getDiscoverTitle();
protected:
    QString discoverTitle;
protected slots:
    void onToggleRequest(bool toggle);
signals:
    void discoverToggled(QString discoverTitle, bool toggle);
public slots:
};

#endif // TOGGLEDISCOVERACTION_H
