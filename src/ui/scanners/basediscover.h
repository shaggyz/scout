#ifndef BASEDISCOVER_H
#define BASEDISCOVER_H

#include <QWidget>
#include <QDebug>

class BaseDiscover : public QWidget
{
    Q_OBJECT
public:

    explicit BaseDiscover(QWidget *parent = 0);

    /**
     * Returns the discover title
     * @brief getDiscoverTitle
     * @return
     */
    QString getDiscoverTitle();

protected:

    QString discoverTitle;

signals:

public slots:
};

#endif // BASEDISCOVER_H
