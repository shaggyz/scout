#include "basediscover.h"

BaseDiscover::BaseDiscover(QWidget *parent) : QWidget(parent)
{

}

QString BaseDiscover::getDiscoverTitle()
{
    return this->discoverTitle;
}
