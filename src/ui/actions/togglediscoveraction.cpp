#include "togglediscoveraction.h"

ToggleDiscoverAction::ToggleDiscoverAction(QObject *parent) : QAction(parent)
{
    connect(this, SIGNAL(toggled(bool)), this, SLOT(onToggleRequest(bool)));
}

void ToggleDiscoverAction::setDiscoverTitle(QString title)
{
    this->discoverTitle = title;
}

QString ToggleDiscoverAction::getDiscoverTitle()
{
    return this->discoverTitle;
}

void ToggleDiscoverAction::onToggleRequest(bool toggle)
{
    emit discoverToggled(this->discoverTitle, toggle);
}
