/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include "qserenityintegration.h"
#include "qserenitybackingstore.h"

#include <QtGui/private/qpixmap_raster_p.h>
#include <QtGui/private/qguiapplication_p.h>
#include <qpa/qplatformwindow.h>
#include <qpa/qwindowsysteminterface.h>

#include <QtGui/private/qfreetypefontdatabase_p.h>
#include <QtGui/private/qgenericunixeventdispatcher_p.h>

#  include <QtGui/private/qgenericunixfontdatabase_p.h>
#  include <qpa/qplatformfontdatabase.h>

#include <iostream>

#include <stdlib.h>

#include <LibCore/EventLoop.h>

QT_BEGIN_NAMESPACE

class QCoreTextFontEngine;

QSerenityIntegration::QSerenityIntegration(const QStringList &parameters)
    : m_fontDatabase(0)
{
    qputenv("QT_ENABLE_REGEXP_JIT", "0");
    qputenv("QT_QPA_FONTDIR", "/res/fonts");

    if (pledge("stdio recvfd sendfd rpath wpath cpath unix getkeymap fattr prot_exec", nullptr) < 0) {
        perror("pledge");
    }
    else {
        perror("pledge");
    }
    app = GUI::Application::construct(0, nullptr);

    m_primaryScreen = new QSerenityScreen();

    QWindowSystemInterface::handleScreenAdded(m_primaryScreen);
}

QSerenityIntegration::~QSerenityIntegration()
{
    QWindowSystemInterface::handleScreenRemoved(m_primaryScreen);
    delete m_fontDatabase;
}

bool QSerenityIntegration::hasCapability(QPlatformIntegration::Capability cap) const
{
    switch (cap) {
    case ThreadedPixmaps: return true;
    case MultipleWindows: return true;
    case NonFullScreenWindows: return true;
    case RhiBasedRendering: return false;
    case PaintEvents: return true;
    case WindowManagement: return true;
    default: return QPlatformIntegration::hasCapability(cap);
    }
}

// Dummy font database that does not scan the fonts directory to be
// used for command line tools like qmlplugindump that do not create windows
// unless DebugBackingStore is activated.
class DummyFontDatabase : public QPlatformFontDatabase
{
public:
    virtual void populateFontDatabase() override {}
};

QPlatformFontDatabase *QSerenityIntegration::fontDatabase() const
{
    m_fontDatabase = new QFreeTypeFontDatabase;
    //m_fontDatabase->addApplicationFont("", "/res/fonts/SerenitySans-Regular.ttf");
    return m_fontDatabase;
}

QPlatformWindow *QSerenityIntegration::createPlatformWindow(QWindow *window) const
{
    QPlatformWindow *w = new QSerenityWindow(window);
    w->requestActivateWindow();
    return w;
}

QPlatformBackingStore *QSerenityIntegration::createPlatformBackingStore(QWindow *window) const
{
    std::cerr << "Creating a new backing store" << std::endl;
    return new QSerenityBackingStore(window);
}

QAbstractEventDispatcher *QSerenityIntegration::createEventDispatcher() const
{
    return new QSerenityEventDispatcher();
}

QSerenityIntegration *QSerenityIntegration::instance()
{
    return static_cast<QSerenityIntegration *>(QGuiApplicationPrivate::platformIntegration());
}

QT_END_NAMESPACE

QSerenityEventDispatcher::QSerenityEventDispatcher(QObject *parent)
    : QUnixEventDispatcherQPA(parent)
{
}

QSerenityEventDispatcher::~QSerenityEventDispatcher() {

}

bool QSerenityEventDispatcher::processEvents(QEventLoop::ProcessEventsFlags flags) {
    processSerenityEvents();
    // while this whole class is hacking, this is another layer of hacks: clear the WaitForMoreEvents flag to process everything immediatelly
    // makes everything run way smoother at the cost of eating all the CPU
    return QUnixEventDispatcherQPA::processEvents(flags & (~QEventLoop::WaitForMoreEvents));
}

bool QSerenityEventDispatcher::processSerenityEvents() {
    auto& loop = Core::EventLoop::current();
    if (loop.was_exit_requested())
        exit(0);
    loop.pump(Core::EventLoop::WaitMode::PollForEvents);

    return true;
}
