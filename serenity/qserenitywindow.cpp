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

#include "qserenitywindow.h"

#include <iostream>

#include <private/qguiapplication_p.h>

#include <Kernel/API/KeyCode.h>

static QMap<KeyCode, int> keyMap {
    { KeyCode::Key_Invalid, 0 },
    { KeyCode::Key_Escape, Qt::Key_Escape },
    { KeyCode::Key_Tab, Qt::Key_Tab },
    { KeyCode::Key_Backspace, Qt::Key_Backspace },
    { KeyCode::Key_Return, Qt::Key_Return },
    { KeyCode::Key_Insert, Qt::Key_Insert },
    { KeyCode::Key_Delete, Qt::Key_Delete },
    { KeyCode::Key_PrintScreen, Qt::Key_Print },
    { KeyCode::Key_SysRq, Qt::Key_SysReq },
    { KeyCode::Key_Home, Qt::Key_Home },
    { KeyCode::Key_End, Qt::Key_End },
    { KeyCode::Key_Left, Qt::Key_Left },
    { KeyCode::Key_Up, Qt::Key_Up },
    { KeyCode::Key_Right, Qt::Key_Right },
    { KeyCode::Key_Down, Qt::Key_Down },
    { KeyCode::Key_PageUp, Qt::Key_PageUp },
    { KeyCode::Key_PageDown, Qt::Key_PageDown },
    { KeyCode::Key_LeftShift, Qt::Key_Shift },
    { KeyCode::Key_RightShift, Qt::Key_Shift },
    { KeyCode::Key_Control, Qt::Key_Control },
    { KeyCode::Key_Alt, Qt::Key_Alt },
    { KeyCode::Key_CapsLock, Qt::Key_CapsLock },
    { KeyCode::Key_NumLock, Qt::Key_NumLock },
    { KeyCode::Key_ScrollLock, Qt::Key_ScrollLock },
    { KeyCode::Key_F1, Qt::Key_F1 },
    { KeyCode::Key_F2, Qt::Key_F2 },
    { KeyCode::Key_F3, Qt::Key_F3 },
    { KeyCode::Key_F4, Qt::Key_F4 },
    { KeyCode::Key_F5, Qt::Key_F5 },
    { KeyCode::Key_F6, Qt::Key_F6 },
    { KeyCode::Key_F7, Qt::Key_F7 },
    { KeyCode::Key_F8, Qt::Key_F8 },
    { KeyCode::Key_F9, Qt::Key_F9 },
    { KeyCode::Key_F10, Qt::Key_F10 },
    { KeyCode::Key_F11, Qt::Key_F11 },
    { KeyCode::Key_F12, Qt::Key_F12 },
    { KeyCode::Key_Space, Qt::Key_Space },
    { KeyCode::Key_ExclamationPoint, Qt::Key_Exclam },
    { KeyCode::Key_DoubleQuote, Qt::Key_QuoteDbl },
    { KeyCode::Key_Hashtag, Qt::Key_NumberSign },
    { KeyCode::Key_Dollar, Qt::Key_Dollar },
    { KeyCode::Key_Percent, Qt::Key_Percent },
    { KeyCode::Key_Ampersand, Qt::Key_Ampersand },
    { KeyCode::Key_Apostrophe, Qt::Key_Apostrophe },
    { KeyCode::Key_LeftParen, Qt::Key_ParenLeft },
    { KeyCode::Key_RightParen, Qt::Key_ParenRight },
    { KeyCode::Key_Asterisk, Qt::Key_Asterisk },
    { KeyCode::Key_Plus, Qt::Key_Plus },
    { KeyCode::Key_Comma, Qt::Key_Comma },
    { KeyCode::Key_Minus, Qt::Key_Minus },
    { KeyCode::Key_Period, Qt::Key_Period },
    { KeyCode::Key_Slash, Qt::Key_Slash },
    { KeyCode::Key_0, Qt::Key_0 },
    { KeyCode::Key_1, Qt::Key_1 },
    { KeyCode::Key_2, Qt::Key_2 },
    { KeyCode::Key_3, Qt::Key_3 },
    { KeyCode::Key_4, Qt::Key_4 },
    { KeyCode::Key_5, Qt::Key_5 },
    { KeyCode::Key_6, Qt::Key_6 },
    { KeyCode::Key_7, Qt::Key_7 },
    { KeyCode::Key_8, Qt::Key_8 },
    { KeyCode::Key_9, Qt::Key_9 },
    { KeyCode::Key_Colon, Qt::Key_Colon },
    { KeyCode::Key_Semicolon, Qt::Key_Semicolon },
    { KeyCode::Key_LessThan, Qt::Key_Less },
    { KeyCode::Key_Equal, Qt::Key_Equal },
    { KeyCode::Key_GreaterThan, Qt::Key_Greater },
    { KeyCode::Key_QuestionMark, Qt::Key_Question },
    { KeyCode::Key_AtSign, Qt::Key_At },
    { KeyCode::Key_A, Qt::Key_A },
    { KeyCode::Key_B, Qt::Key_B },
    { KeyCode::Key_C, Qt::Key_C },
    { KeyCode::Key_D, Qt::Key_D },
    { KeyCode::Key_E, Qt::Key_E },
    { KeyCode::Key_F, Qt::Key_F },
    { KeyCode::Key_G, Qt::Key_G },
    { KeyCode::Key_H, Qt::Key_H },
    { KeyCode::Key_I, Qt::Key_I },
    { KeyCode::Key_J, Qt::Key_J },
    { KeyCode::Key_K, Qt::Key_K },
    { KeyCode::Key_L, Qt::Key_L },
    { KeyCode::Key_M, Qt::Key_M },
    { KeyCode::Key_N, Qt::Key_N },
    { KeyCode::Key_O, Qt::Key_O },
    { KeyCode::Key_P, Qt::Key_P },
    { KeyCode::Key_Q, Qt::Key_Q },
    { KeyCode::Key_R, Qt::Key_R },
    { KeyCode::Key_S, Qt::Key_S },
    { KeyCode::Key_T, Qt::Key_T },
    { KeyCode::Key_U, Qt::Key_U },
    { KeyCode::Key_V, Qt::Key_V },
    { KeyCode::Key_W, Qt::Key_W },
    { KeyCode::Key_X, Qt::Key_X },
    { KeyCode::Key_Y, Qt::Key_Y },
    { KeyCode::Key_Z, Qt::Key_Z },
    { KeyCode::Key_LeftBracket, Qt::Key_BracketLeft },
    { KeyCode::Key_RightBracket, Qt::Key_BracketRight },
    { KeyCode::Key_Backslash, Qt::Key_Backslash },
    { KeyCode::Key_Circumflex, Qt::Key_AsciiCircum },
    { KeyCode::Key_Underscore, Qt::Key_Underscore },
    { KeyCode::Key_LeftBrace, Qt::Key_BraceLeft },
    { KeyCode::Key_RightBrace, Qt::Key_BraceRight },
    { KeyCode::Key_Pipe, Qt::Key_Bar }, // maybe wrong
    { KeyCode::Key_Tilde, Qt::Key_AsciiTilde },
    { KeyCode::Key_Backtick, Qt::Key_Agrave }, // maybe wrong
    { KeyCode::Key_Super, Qt::Key_Meta },
    { KeyCode::Key_Menu, Qt::Key_Menu }
};

QSerenityWindow::QSerenityWindow(QWindow *window)
    : QPlatformWindow(window)
    , m_window(GUI::Window::construct())
    , m_proxyWidget(SerenityProxyWidget::construct(this))
{
    std::cerr << "Creating a new window" << std::endl;

    if (window->width() > 0 && window->height() > 0)
        m_window->resize(window->width(), window->height());
    m_window->set_double_buffering_enabled(false);

    m_window->set_main_widget(m_proxyWidget);
    m_window->set_title(QSerenityString::fromQString(window->title()));
    m_window->show();

    std::cerr << "Native window set up\n";
}

void QSerenityWindow::setWindowTitle(const QString &text)
{
    m_window->set_title(QSerenityString::fromQString(text));
}

QRect QSerenityWindow::geometry() const {
    return QRect(m_window->rect().x(), m_window->rect().y(), m_window->rect().width(), m_window->rect().height());
}

SerenityProxyWidget::SerenityProxyWidget(QSerenityWindow *window)
    : m_qtWindow(window)
{
    std::cerr << __FUNCTION__ << std::endl;
    m_buffer = Gfx::Bitmap::try_create(Gfx::BitmapFormat::BGRx8888, Gfx::IntSize(window->window()->width(), window->window()->height())).value();
    update();
}

void SerenityProxyWidget::paint_event(GUI::PaintEvent &event) {
    // std::cerr << __FUNCTION__ << std::endl;

    GUI::Painter painter(*this);
    painter.add_clip_rect(event.rect());
    painter.blit(event.rect().location(), *m_buffer, event.rect());
}

void SerenityProxyWidget::resize_event(GUI::ResizeEvent &event) {
    std::cerr << __FUNCTION__ << std::endl;

    //m_qtWindow->window()->resize(event.size().width(), event.size().height());
    //m_qtBackingStore->resize(QSize(event.size().width(), event.size().height()), QRegion());

    auto qtEvent = new QResizeEvent(QSize(event.size().width(), event.size().height()), m_qtWindow->window()->size());
    qApp->postEvent(m_qtWindow->window(), qtEvent);
}

void SerenityProxyWidget::show_event(GUI::ShowEvent &) {
    std::cerr << __FUNCTION__ << std::endl;
}

void SerenityProxyWidget::hide_event(GUI::HideEvent &) {
    std::cerr << __FUNCTION__ << std::endl;

}

void SerenityProxyWidget::mousedown_event(GUI::MouseEvent &event) {
    std::cerr << __FUNCTION__ << std::endl;

    QWindow *qtWindow = m_qtWindow->window();
    QPlatformWindow *platformWindow = qtWindow->handle();
    auto qtEvent = new QMouseEvent(QEvent::MouseButtonPress, QPointF(event.x(), event.y()), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    qApp->postEvent(qtWindow, qtEvent);
}

void SerenityProxyWidget::mousemove_event(GUI::MouseEvent &event) {
    //std::cerr << __FUNCTION__ << std::endl;

    QWindow *qtWindow = m_qtWindow->window();
    QPlatformWindow *platformWindow = qtWindow->handle();
    auto qtEvent = new QMouseEvent(QEvent::MouseMove, QPointF(event.x(), event.y()), Qt::NoButton, Qt::NoButton, Qt::NoModifier);
    qApp->postEvent(qtWindow, qtEvent);
}

void SerenityProxyWidget::mouseup_event(GUI::MouseEvent &event) {
    std::cerr << __FUNCTION__ << std::endl;

    QWindow *qtWindow = m_qtWindow->window();
    QPlatformWindow *platformWindow = qtWindow->handle();
    auto qtEvent = new QMouseEvent(QEvent::MouseButtonRelease, QPointF(event.x(), event.y()), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    qApp->postEvent(qtWindow, qtEvent);
}

void SerenityProxyWidget::keydown_event(GUI::KeyEvent &event) {
    std::cerr << __FUNCTION__ << std::endl;

    Qt::KeyboardModifiers modifiers = Qt::NoModifier;
    if (event.ctrl())
        modifiers |= Qt::ControlModifier;
    if (event.alt())
        modifiers |= Qt::AltModifier;
    if (event.shift())
        modifiers |= Qt::ShiftModifier;
    if (event.super())
        modifiers |= Qt::MetaModifier;

    QWindow *qtWindow = m_qtWindow->window();
    QPlatformWindow *platformWindow = qtWindow->handle();
    int k = keyMap.value(event.key(), 0);
    if (k < 0x01000000) {
        QWindowSystemInterface::handleKeyEvent<QWindowSystemInterface::SynchronousDelivery>(qtWindow, QEvent::KeyPress, k, modifiers, QChar(event.code_point()));
    }
    else {
        QWindowSystemInterface::handleKeyEvent<QWindowSystemInterface::SynchronousDelivery>(qtWindow, QEvent::KeyPress, k, modifiers);
    }
}

void SerenityProxyWidget::keyup_event(GUI::KeyEvent &event) {
    std::cerr << __FUNCTION__ << std::endl;

    Qt::KeyboardModifiers modifiers = Qt::NoModifier;
    if (event.ctrl())
        modifiers |= Qt::ControlModifier;
    if (event.alt())
        modifiers |= Qt::AltModifier;
    if (event.shift())
        modifiers |= Qt::ShiftModifier;
    if (event.super())
        modifiers |= Qt::MetaModifier;

    QWindow *qtWindow = m_qtWindow->window();
    QPlatformWindow *platformWindow = qtWindow->handle();
    int k = keyMap.value(event.key(), 0);
    QWindowSystemInterface::handleKeyEvent<QWindowSystemInterface::SynchronousDelivery>(qtWindow, QEvent::KeyRelease, k, modifiers);
}

void SerenityProxyWidget::enter_event(Core::Event &event) {
    std::cerr << __FUNCTION__ << std::endl;
    QWindow *qtWindow = m_qtWindow->window();
    QWindowSystemInterface::handleEnterEvent<QWindowSystemInterface::SynchronousDelivery>(qtWindow);
}

void SerenityProxyWidget::leave_event(Core::Event &event) {
    std::cerr << __FUNCTION__ << std::endl;
    QWindow *qtWindow = m_qtWindow->window();
    QWindowSystemInterface::handleLeaveEvent<QWindowSystemInterface::SynchronousDelivery>(qtWindow);
}


