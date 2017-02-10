#pragma once

#include <QObject>
#include <QQmlExtensionPlugin>
#include "DOtherSideTypesCpp.h"
#include "DOtherSide/DosQQmlExtensionPluginImpl.h"

namespace DOS {
    class DosQQmlExtensionPlugin : public QQmlExtensionPlugin, public DosQQml {
        
    }
}