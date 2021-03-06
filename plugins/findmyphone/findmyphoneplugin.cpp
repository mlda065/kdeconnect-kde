/**
 * Copyright 2014 Apoorv Parle <apparle@gmail.com>
 * Copyright 2015 David Edmundson <davidedmundson@kde.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "findmyphoneplugin.h"

#include <core/device.h>
#include <QDBusConnection>
#include <QDebug>

#include <KPluginFactory>

K_PLUGIN_FACTORY_WITH_JSON( KdeConnectPluginFactory, "kdeconnect_findmyphone.json", registerPlugin< FindMyPhonePlugin >(); )

FindMyPhonePlugin::FindMyPhonePlugin(QObject* parent, const QVariantList& args) : KdeConnectPlugin(parent, args)
{
}

FindMyPhonePlugin::~FindMyPhonePlugin()
{
}

bool FindMyPhonePlugin::receivePackage(const NetworkPackage& np)
{
    Q_UNUSED(np);
    return false;
}

void FindMyPhonePlugin::ring()
{
    NetworkPackage np(PACKAGE_TYPE_FINDMYPHONE);
    sendPackage(np);
}

void FindMyPhonePlugin::connected()
{
    QDBusConnection::sessionBus().registerObject(dbusPath(), this, QDBusConnection::ExportAllContents);
}

QString FindMyPhonePlugin::dbusPath() const
{
    return "/modules/kdeconnect/devices/" + device()->id() + "/findmyphone";
}

#include "findmyphoneplugin.moc"

