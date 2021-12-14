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


#include "qserenitybackingstore.h"
#include "qserenityintegration.h"
#include "qscreen.h"
#include <QtCore/qdebug.h>
#include <qpa/qplatformscreen.h>
#include <QGuiApplication>

#include <iostream>
#include <cstdlib>

QSerenityBackingStore::QSerenityBackingStore(QWindow *window)
    : QPlatformBackingStore(window)

{
}

QSerenityBackingStore::~QSerenityBackingStore()
{
}

QPaintDevice *QSerenityBackingStore::paintDevice()
{
    return &mImage;
}

void QSerenityBackingStore::flush(QWindow *window, const QRegion &region, const QPoint &offset)
{
    Q_UNUSED(window);
    Q_UNUSED(region);
    Q_UNUSED(offset);

    QPlatformWindow *platformWindow = this->window()->handle();
    QSerenityWindow *qSerenityWindow = dynamic_cast<QSerenityWindow*>(platformWindow);

    auto proxyWidget = qSerenityWindow->proxyWidget();

    for (auto &r : region) {
        for (int i = offset.x() + r.left(); i < mImage.width() && i < offset.x() + r.right(); i++) {
            for (int j = offset.y() + r.top(); j < mImage.height() && j < offset.y() + r.bottom(); j++) {
                auto currentColor = mImage.pixel(i, j);
                proxyWidget->m_buffer->set_pixel(i, j, Gfx::Color(currentColor >> 16 & 0xFF, currentColor >> 8 & 0xFF, currentColor & 0xFF));
            }
        }
        proxyWidget->update(Gfx::IntRect(r.x() + offset.x(), r.y() + offset.y(), r.width(), r.height()));
    }
}

void QSerenityBackingStore::resize(const QSize &size, const QRegion &)
{
    QPlatformWindow *platformWindow = window()->handle();
    QSerenityWindow *qSerenityWindow = dynamic_cast<QSerenityWindow*>(platformWindow);

    auto proxyWidget = qSerenityWindow->proxyWidget();

    QImage::Format format = QGuiApplication::primaryScreen()->handle()->format();
    if (mImage.size() != size) {
        mImage = QImage(size, format);
        proxyWidget->m_buffer = Gfx::Bitmap::try_create(Gfx::BitmapFormat::BGRx8888, Gfx::IntSize(window()->width(), window()->height())).value();
        proxyWidget->m_buffer->set_volatile();
        proxyWidget->resize(Gfx::IntSize(size.width(), size.height()));
        proxyWidget->update();
    }
}
QT_END_NAMESPACE
