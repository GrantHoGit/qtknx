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

#include "qknxnetipdeviceconfigurationrequest.h"

QT_BEGIN_NAMESPACE

QKnxNetIpDeviceConfigurationRequest::QKnxNetIpDeviceConfigurationRequest(const QKnxNetIpFrame &frame)
    : m_frame(frame)
{}

bool QKnxNetIpDeviceConfigurationRequest::isValid() const
{
    return m_frame.isValid() && m_frame.size() >= 12 && cemi().isValid()
        && m_frame.serviceType() == QKnxNetIp::ServiceType::DeviceConfigurationRequest;
}

quint8 QKnxNetIpDeviceConfigurationRequest::channelId() const
{
    return m_frame.channelId();
}

quint8 QKnxNetIpDeviceConfigurationRequest::sequenceNumber() const
{
    return m_frame.sequenceNumber();
}

QKnxLocalDeviceManagementFrame QKnxNetIpDeviceConfigurationRequest::cemi() const
{
    return QKnxLocalDeviceManagementFrame::fromBytes(m_frame.data(), 0, m_frame.dataSize());
}

QKnxNetIpDeviceConfigurationRequest::Builder QKnxNetIpDeviceConfigurationRequest::builder()
{
    return QKnxNetIpDeviceConfigurationRequest::Builder();
}


// -- QKnxNetIpDeviceConfigurationRequest::Builder

QKnxNetIpDeviceConfigurationRequest::Builder &
    QKnxNetIpDeviceConfigurationRequest::Builder::setChannelId(quint8 channelId)
{
    m_channelId = channelId;
    return *this;
}

QKnxNetIpDeviceConfigurationRequest::Builder &
    QKnxNetIpDeviceConfigurationRequest::Builder::setSequenceNumber(quint8 sequenceNumber)
{
    m_sequenceNumber = sequenceNumber;
    return *this;
}

QKnxNetIpDeviceConfigurationRequest::Builder &
    QKnxNetIpDeviceConfigurationRequest::Builder::setCemi(const QKnxLocalDeviceManagementFrame &cemi)
{
    m_cemi = cemi;
    return *this;
}

QKnxNetIpFrame QKnxNetIpDeviceConfigurationRequest::Builder::create() const
{
    return { QKnxNetIp::ServiceType::DeviceConfigurationRequest, { m_channelId, m_sequenceNumber },
        m_cemi.bytes() };
}

QT_END_NAMESPACE
