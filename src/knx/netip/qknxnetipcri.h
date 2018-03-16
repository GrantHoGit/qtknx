/******************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtKnx module.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#ifndef QKNXNETIPCRI_H
#define QKNXNETIPCRI_H

#include <QtKnx/qknxglobal.h>
#include <QtKnx/qknxnetipstruct.h>

QT_BEGIN_NAMESPACE

class Q_KNX_EXPORT QKnxNetIpCriView final
{
public:
    QKnxNetIpCriView() = delete;
    ~QKnxNetIpCriView() = default;

    QKnxNetIpCriView(const QKnxNetIpCri &&) = delete;
    explicit QKnxNetIpCriView(const QKnxNetIpCri &cri);

    bool isValid() const;

    QKnxNetIp::ConnectionType connectionType() const;
    QKnxNetIp::TunnelingLayer tunnelingLayer() const;
    QKnxByteArray additionalData() const;

    class Q_KNX_EXPORT Builder final
    {
    public:
        Builder &setConnectionType(QKnxNetIp::ConnectionType type);
        Builder &setTunnelingLayer(QKnxNetIp::TunnelingLayer layer);
        Builder &setAdditionalData(const QKnxByteArray &additionalData);

        QKnxNetIpCri create() const;

    private:
        QKnxNetIp::ConnectionType m_cType = QKnxNetIp::ConnectionType::Tunnel;
        QKnxByteArray m_additionalData;
    };
    static QKnxNetIpCriView::Builder builder();

private:
    const QKnxNetIpCri &m_cri;
};

QT_END_NAMESPACE

#endif
