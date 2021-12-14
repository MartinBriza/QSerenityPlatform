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

#ifndef QPLATFORMWINDOW_SERENITY_H
#define QPLATFORMWINDOW_SERENITY_H

#define AK_DONT_REPLACE_STD

#include <qpa/qplatformwindow.h>

#include <LibCore/EventLoop.h>
#include <LibGUI/Application.h>
#include <LibGUI/Painter.h>
#include <LibGUI/Widget.h>
#include <LibGUI/Window.h>
#include <LibGfx/Bitmap.h>

#include "qserenitystring.h"

namespace GUI
{
    class Window;
}

class QSerenityWindow;

class SerenityProxyWidget : public GUI::Widget
{
    C_OBJECT(SerenityProxyWidget)
public:
    explicit SerenityProxyWidget(QSerenityWindow*);
    RefPtr<Gfx::Bitmap> m_buffer;

protected:
    void paint_event(GUI::PaintEvent&) override;
    void resize_event(GUI::ResizeEvent&) override;
    void show_event(GUI::ShowEvent&) override;
    void hide_event(GUI::HideEvent&) override;

    void mousedown_event(GUI::MouseEvent&) override;
    void mousemove_event(GUI::MouseEvent&) override;
    void mouseup_event(GUI::MouseEvent&) override;

    void keydown_event(GUI::KeyEvent& event) override;
    void keyup_event(GUI::KeyEvent& event) override;

    void enter_event(Core::Event&) override;
    void leave_event(Core::Event&) override;

private:
    QSerenityWindow* m_qtWindow = nullptr;
};

class QSerenityWindow : public QPlatformWindow
{
public:
    QSerenityWindow(QWindow* window);

    virtual void setWindowTitle(const QString& text) override;
    virtual QRect geometry() const override;

    SerenityProxyWidget* proxyWidget() { return m_proxyWidget; }

private:
    GUI::Window* w;
    NonnullRefPtr<GUI::Window> m_window;
    NonnullRefPtr<SerenityProxyWidget> m_proxyWidget;
};

#endif  // QPLATFORMWINDOW_SERENITY_H
