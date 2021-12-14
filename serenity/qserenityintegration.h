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

#ifndef QPLATFORMINTEGRATION_SERENITY_H
#define QPLATFORMINTEGRATION_SERENITY_H
#define AK_DONT_REPLACE_STD

#include <qpa/qplatformintegration.h>
#include <qpa/qplatformscreen.h>

#include "qserenityscreen.h"
#include "qserenitywindow.h"

#include <AK/StdLibExtraDetails.h>
#include <LibGUI/Application.h>

#include <private/qunixeventdispatcher_qpa_p.h>

#include <QTimer>

QT_BEGIN_NAMESPACE

class QSerenityEventDispatcher : public QUnixEventDispatcherQPA {
    Q_OBJECT
public:
    explicit QSerenityEventDispatcher(QObject *parent = nullptr);
    ~QSerenityEventDispatcher();

private slots:
    bool processSerenityEvents();

protected:
    bool processEvents(QEventLoop::ProcessEventsFlags flags) override;

private:
};

class QSerenityIntegration : public QPlatformIntegration
{
public:
    explicit QSerenityIntegration(const QStringList &parameters);
    ~QSerenityIntegration();

    bool hasCapability(QPlatformIntegration::Capability cap) const override;
    QPlatformFontDatabase *fontDatabase() const override;

    QPlatformWindow *createPlatformWindow(QWindow *window) const override;
    QPlatformBackingStore *createPlatformBackingStore(QWindow *window) const override;
    QAbstractEventDispatcher *createEventDispatcher() const override;

    static QSerenityIntegration *instance();

private:
    mutable QPlatformFontDatabase *m_fontDatabase;
    QSerenityScreen *m_primaryScreen;
    RefPtr<GUI::Application> app;
};

QT_END_NAMESPACE

#endif
