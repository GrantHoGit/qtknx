/******************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtKnx module.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
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
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#include <QtKnx/qknxcharstring.h>
#include <QtKnx/qknxtpdufactory.h>
#include <QtKnx/qknxtunnelframe.h>
#include <QtTest/qtest.h>

class tst_QKnxTpduFactory : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testTpdu();
    void testGroupValueRead();
    void testGroupValueWrite();
    // TODO: GroupValueResponse

    void testGroupPropValueRead();
    void testGroupPropValueWrite();
    // TODO: GroupPropValueResponse
    // TODO: GroupPropValueInfoReport

    void testIndividualAddressRead();
    void testIndividualAddressWrite();
    // TODO: IndividualAddressResponse
    void testIndividualAddressSerialNumberRead();
    void testIndividualAddressSerialNumberWrite();
    // TODO: IndividualAddressSerialNumberResponse
    void testDomainAddressRead();
    void testDomainAddressWrite();
    // TODO: DomainAddressResponse
    // TODO: DomainAddressSelectiveRead
    void testDomainAddressSerialNumberRead();
    void testDomainAddressSerialNumberWrite();
    // TODO: DomainAddressSerialNumberResponse
    // TODO: DeviceDescriptorInfoReport

    void testSystemNetworkParameterRead();
    void testSystemNetworkParameterWrite();
    // TODO: SystemNetworkParameterResponse
    void testNetworkParameterRead();
    void testNetworkParameterWrite();
    void testNetworkParameterResponse();
    void testPropertyValueRead();
    void testPropertyValueWrite();
    // TODO: PropertyValueResponse
    void testPropertyDescriptionRead();
    // TODO: PropertyDescriptionResponse
    void testFunctionPropertyCommand();
    void testFunctionPropertyStateRead();
    // TODO: FunctionPropertyStateResponse
    void testLinkRead();
    void testLinkWrite();
    // TODO: LinkResponse
    void testDeviceDescriptorRead();
    void testDeviceDescriptorResponse();
    // TODO Restart
    void testAdcRead();
    // TODO: AdcResponse
    void testMemoryRead();
    // TODO: MemoryResponse
    void testMemoryWrite();
    // TODO: MemoryBitWrite
    void testUserMemoryRead();
    // TODO: UserMemoryResponse
    void testUserMemoryWrite();
    // TODO: UserMemoryBitWrite
    void testUserManufacturerInfoRead();
    // TODO: UserManufacturerInfoResponse
    // TODO: AuthorizeRequest
    // TODO: AuthorizeResponse
    // TODO: KeyWrite
    // TODO: KeyResponse
};

void tst_QKnxTpduFactory::testTpdu()
{
    QKnxTpdu tpdu1(QKnxTpdu::TransportControlField::DataGroup,
        QKnxTpdu::ApplicationControlField::GroupValueWrite);
    tpdu1.setData(QByteArray::fromHex("01"));

    QKnxTunnelFrame frame;
    frame.setTpdu(tpdu1);
    QCOMPARE(tpdu1.applicationControlField(), QKnxTpdu::ApplicationControlField::GroupValueWrite);
    QCOMPARE(frame.tpdu().data(), QByteArray::fromHex("01"));

    QKnxTpdu tpdu(QKnxTpdu::TransportControlField::Invalid);
    QCOMPARE(tpdu.isValid(), false);

    tpdu.setTransportControlField(QKnxTpdu::TransportControlField::DataGroup);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataGroup);

    tpdu.setApplicationControlField(QKnxTpdu::ApplicationControlField::GroupValueRead);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataGroup);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::GroupValueRead);

    tpdu.setTransportControlField(QKnxTpdu::TransportControlField::DataBroadcast);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataBroadcast);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::GroupValueRead);

    tpdu.setApplicationControlField(QKnxTpdu::ApplicationControlField::GroupValueWrite);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataBroadcast);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::GroupValueWrite);

    QCOMPARE(tpdu.isValid(), true);
    tpdu.setData(QByteArray::fromHex("3f"));
    QCOMPARE(tpdu.data(), QByteArray::fromHex("3f"));

    tpdu.setData(QByteArray::fromHex("43"));
    QCOMPARE(tpdu.data(), QByteArray::fromHex("43"));

    tpdu = { QKnxTpdu::TransportControlField::DataGroup,
        QKnxTpdu::ApplicationControlField::GroupValueRead };
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataGroup);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::GroupValueRead);

    tpdu = { QKnxTpdu::TransportControlField::DataGroup,
        QKnxTpdu::ApplicationControlField::GroupValueResponse };
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataGroup);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::GroupValueResponse);

    tpdu.setData(QByteArray::fromHex("3f"));
    QCOMPARE(tpdu.data(), QByteArray::fromHex("3f"));
    QCOMPARE(tpdu.bytes(), QByteArray::fromHex("007f"));

    tpdu.setTransportControlField(QKnxTpdu::TransportControlField::DataBroadcast);
    tpdu.setApplicationControlField(QKnxTpdu::ApplicationControlField::GroupValueWrite);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataBroadcast);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::GroupValueWrite);
    QCOMPARE(tpdu.data(), QByteArray::fromHex("3f"));
    QCOMPARE(tpdu.bytes(), QByteArray::fromHex("00bf"));

    tpdu.setData(QByteArray::fromHex("43"));
    QCOMPARE(tpdu.data(), QByteArray::fromHex("43"));
    QCOMPARE(tpdu.bytes(), QByteArray::fromHex("008043"));

    tpdu = { QKnxTpdu::TransportControlField::DataGroup,
        QKnxTpdu::ApplicationControlField::GroupValueRead };
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataGroup);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::GroupValueRead);

    tpdu.setData(QByteArray::fromHex("3f3f"));
    QCOMPARE(tpdu.data(), QByteArray::fromHex("3f3f"));
    QCOMPARE(tpdu.isValid(), false);

    tpdu.setData({});
    QCOMPARE(tpdu.isValid(), true);
    QCOMPARE(tpdu.data(), QByteArray{});

    tpdu.setApplicationControlField(QKnxTpdu::ApplicationControlField::GroupValueWrite);
    tpdu.setData(QByteArray::fromHex("3f3f"));
    QCOMPARE(tpdu.isValid(), true);
    tpdu.setTransportControlField(QKnxTpdu::TransportControlField::DataBroadcast);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataBroadcast);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::GroupValueWrite);
    QCOMPARE(tpdu.data(), QByteArray::fromHex("3f3f"));

    tpdu.setData(QByteArray::fromHex("3f"));
    QCOMPARE(tpdu.data(), QByteArray::fromHex("3f"));
    QCOMPARE(tpdu.bytes(), QByteArray::fromHex("00bf"));

    tpdu.setData(QByteArray::fromHex("00"));
    QCOMPARE(tpdu.data(), QByteArray::fromHex("0"));
    QCOMPARE(tpdu.bytes(), QByteArray::fromHex("0080"));

    auto tmpTpdu = QKnxTpdu::fromBytes(tpdu.bytes(), 0, quint8(tpdu.size()));
    QCOMPARE(tmpTpdu.bytes(), tpdu.bytes());
}

void tst_QKnxTpduFactory::testGroupValueRead()
{
    auto tpdu = QKnxTpduFactory::Multicast::createGroupValueReadTpdu();

    QCOMPARE(tpdu.size(), quint16(2));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataGroup);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::GroupValueRead);
}

void tst_QKnxTpduFactory::testGroupValueWrite()
{
    auto data = QByteArray::fromHex("01");
    auto tpdu = QKnxTpduFactory::Multicast::createGroupValueWriteTpdu(data);

    QCOMPARE(tpdu.data(), data);
    QCOMPARE(tpdu.size(), quint16(2));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataGroup);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::GroupValueWrite);

    tpdu.setData(QByteArray::fromHex("0101"));
    QCOMPARE(tpdu.size(), quint16(4));
    QCOMPARE(tpdu.data(), QByteArray::fromHex("0101"));

    tpdu.setData(QByteArray::fromHex("40"));
    QCOMPARE(tpdu.size(), quint16(3));
    QCOMPARE(tpdu.data(), QByteArray::fromHex("40"));

    tpdu.setData(QByteArray::fromHex("f0"));
    QCOMPARE(tpdu.size(), quint16(3));
    QCOMPARE(tpdu.data(), QByteArray::fromHex("f0"));

    tpdu.setData(QByteArray::fromHex("ff"));
    QCOMPARE(tpdu.size(), quint16(3));
    QCOMPARE(tpdu.data(), QByteArray::fromHex("ff"));

    tpdu.setData(QKnxCharString("The Qt Company").bytes());
    QCOMPARE(tpdu.isValid(), true);
    QCOMPARE(tpdu.size(), quint16(16));
    QCOMPARE(tpdu.dataSize(), quint8(15));

    tpdu = QKnxTpduFactory::Multicast::createGroupValueWriteTpdu(QKnxCharString("The Qt Company")
        .bytes());
    QCOMPARE(tpdu.isValid(), true);
    QCOMPARE(tpdu.size(), quint16(16));
    QCOMPARE(tpdu.dataSize(), quint8(15));
}

void tst_QKnxTpduFactory::testGroupPropValueRead()
{
    auto tpdu = QKnxTpduFactory::Multicast::createGroupPropertyValueReadTpdu(QKnxInterfaceObjectType
        ::System::Device, 5, QKnxInterfaceObjectProperty::General::ManufacturerData);

    QCOMPARE(tpdu.size(), quint16(6));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataTagGroup);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::GroupPropValueRead);
}

void tst_QKnxTpduFactory::testGroupPropValueWrite()
{
    auto data = QByteArray::fromHex("010203");
    auto tpdu = QKnxTpduFactory::Multicast::createGroupPropertyValueWriteTpdu(QKnxInterfaceObjectType
        ::System::Device, 5, QKnxInterfaceObjectProperty::General::ManufacturerData, data);

    QCOMPARE(tpdu.size(), quint16(9));
    QCOMPARE(tpdu.data(), QByteArray::fromHex("00001305010203"));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataTagGroup);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::GroupPropValueWrite);

    tpdu.setData(QByteArray(253, 1));
    QCOMPARE(tpdu.isValid(), true);
    QCOMPARE(tpdu.size(), quint16(255));
    QCOMPARE(tpdu.dataSize(), quint8(254));

    tpdu = QKnxTpduFactory::Multicast::createGroupPropertyValueWriteTpdu(QKnxInterfaceObjectType
        ::System::Device, 5, QKnxInterfaceObjectProperty::General::ManufacturerData,
        QByteArray(249, 1));
    QCOMPARE(tpdu.isValid(), true);
    QCOMPARE(tpdu.size(), quint16(255));
    QCOMPARE(tpdu.dataSize(), quint8(254));
}

void tst_QKnxTpduFactory::testIndividualAddressRead()
{
    auto tpdu = QKnxTpduFactory::Broadcast::createIndividualAddressReadTpdu();

    QCOMPARE(tpdu.size(), quint16(2));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataBroadcast);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::IndividualAddressRead);
}

void tst_QKnxTpduFactory::testIndividualAddressWrite()
{
    auto address = QKnxAddress::Group::Broadcast;
    auto tpdu = QKnxTpduFactory::Broadcast::createIndividualAddressWriteTpdu(address);
    QCOMPARE(tpdu.size(), quint16(2));

    address = QKnxAddress::createIndividual(1, 1, 1);
    tpdu = QKnxTpduFactory::Broadcast::createIndividualAddressWriteTpdu(address);

    QCOMPARE(tpdu.size(), quint16(4));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataBroadcast);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::IndividualAddressWrite);
    QCOMPARE(QKnxAddress(QKnxAddress::Type::Individual, tpdu.data()), address);
}

void tst_QKnxTpduFactory::testIndividualAddressSerialNumberRead()
{
    auto serialNumber = QByteArray::fromHex("010203");
    auto tpdu = QKnxTpduFactory::Broadcast::createIndividualAddressSerialNumberReadTpdu(serialNumber);
    QCOMPARE(tpdu.size(), quint16(2));

    serialNumber = QByteArray::fromHex("010203040506");
    tpdu = QKnxTpduFactory::Broadcast::createIndividualAddressSerialNumberReadTpdu(serialNumber);

    QCOMPARE(tpdu.size(), quint16(8));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataBroadcast);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::IndividualAddressSerialNumberRead);
}

void tst_QKnxTpduFactory::testIndividualAddressSerialNumberWrite()
{
    auto address = QKnxAddress::Group::Broadcast;
    auto serialNumber = QByteArray::fromHex("010203");

    auto tpdu = QKnxTpduFactory::Broadcast::createIndividualAddressSerialNumberWriteTpdu(serialNumber, address);
    QCOMPARE(tpdu.size(), quint16(2));

    serialNumber = QByteArray::fromHex("010203040506");
    tpdu = QKnxTpduFactory::Broadcast::createIndividualAddressSerialNumberWriteTpdu(serialNumber, address);
    QCOMPARE(tpdu.size(), quint16(2));

    address = QKnxAddress::createIndividual(1, 1, 1);
    tpdu = QKnxTpduFactory::Broadcast::createIndividualAddressSerialNumberWriteTpdu(serialNumber, address);

    QCOMPARE(tpdu.size(), quint16(14));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataBroadcast);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::IndividualAddressSerialNumberWrite);
}

void tst_QKnxTpduFactory::testDomainAddressRead()
{
    auto tpdu = QKnxTpduFactory::Broadcast::createDomainAddressReadTpdu();

    QCOMPARE(tpdu.size(), quint16(2));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataBroadcast);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::DomainAddressRead);
}

void tst_QKnxTpduFactory::testDomainAddressWrite()
{
    auto address = QKnxAddress::createGroup(1, 1, 1);
    auto tpdu = QKnxTpduFactory::Broadcast::createDomainAddressWriteTpdu(address.bytes());

    QCOMPARE(tpdu.size(), quint16(4));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataBroadcast);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::DomainAddressWrite);
}

void tst_QKnxTpduFactory::testDomainAddressSerialNumberRead()
{
    auto serialNumber = QByteArray::fromHex("010203");
    auto tpdu = QKnxTpduFactory::Broadcast::createDomainAddressSerialNumberReadTpdu(serialNumber);
    QCOMPARE(tpdu.size(), quint16(2));

    serialNumber = QByteArray::fromHex("010203040506");
    tpdu = QKnxTpduFactory::Broadcast::createDomainAddressSerialNumberReadTpdu(serialNumber);

    QCOMPARE(tpdu.size(), quint16(8));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataBroadcast);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::DomainAddressSerialNumberRead);
}

void tst_QKnxTpduFactory::testDomainAddressSerialNumberWrite()
{
    auto address = QKnxAddress::createGroup(1, 1, 1).bytes();
    auto serialNumber = QByteArray::fromHex("010203");
    auto tpdu = QKnxTpduFactory::Broadcast::createDomainAddressSerialNumberWriteTpdu(serialNumber, address);
    QCOMPARE(tpdu.size(), quint16(2));

    tpdu = QKnxTpduFactory::Broadcast::createDomainAddressSerialNumberWriteTpdu(serialNumber, serialNumber);
    QCOMPARE(tpdu.size(), quint16(2));

    serialNumber = QByteArray::fromHex("010203040506");
    tpdu = QKnxTpduFactory::Broadcast::createDomainAddressSerialNumberWriteTpdu(serialNumber, address);

    QCOMPARE(tpdu.size(), quint16(10));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataBroadcast);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::DomainAddressSerialNumberWrite);
}

void tst_QKnxTpduFactory::testSystemNetworkParameterRead()
{
    auto tpdu = QKnxTpduFactory::Broadcast::createSystemNetworkParameterReadTpdu(
        QKnxInterfaceObjectType::System::Device, QKnxInterfaceObjectProperty::Device::ErrorFlags,
        QByteArray::fromHex("01020304"));

    QCOMPARE(tpdu.size(), quint16(10));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataSystemBroadcast);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::SystemNetworkParameterRead);
}

void tst_QKnxTpduFactory::testSystemNetworkParameterWrite()
{
    auto tpdu = QKnxTpduFactory::Broadcast::createSystemNetworkParameterWriteTpdu(
        QKnxInterfaceObjectType::System::Device, QKnxInterfaceObjectProperty::Device::ErrorFlags,
        QByteArray::fromHex("01020304"));

    QCOMPARE(tpdu.size(), quint16(10));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataSystemBroadcast);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::SystemNetworkParameterWrite);
}

void tst_QKnxTpduFactory::testNetworkParameterRead()
{
    auto tpdu = QKnxTpduFactory::Broadcast::createNetworkParameterReadTpdu(
        QKnxInterfaceObjectType::System::Device, QKnxInterfaceObjectProperty::Device::ErrorFlags,
        QByteArray::fromHex("01020304"));

    QCOMPARE(tpdu.size(), quint16(9));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataBroadcast);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::NetworkParameterRead);

    tpdu = QKnxTpduFactory::Broadcast::createNetworkParameterReadTpdu(
        QKnxInterfaceObjectType::System::Device, QKnxInterfaceObjectProperty::Device::ErrorFlags,
        QByteArray(250, 1));
    QCOMPARE(tpdu.size(), quint16(255));
    QCOMPARE(tpdu.dataSize(), quint8(254));
}

void tst_QKnxTpduFactory::testNetworkParameterWrite()
{
    auto tpdu = QKnxTpduFactory::Broadcast::createNetworkParameterWriteTpdu(
        QKnxInterfaceObjectType::System::Device, QKnxInterfaceObjectProperty::Device::ErrorFlags,
        QByteArray::fromHex("01020304"));

    QCOMPARE(tpdu.size(), quint16(9));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataBroadcast);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::NetworkParameterWrite);

    tpdu = QKnxTpduFactory::PointToPointConnectionless::createNetworkParameterWriteTpdu(
        QKnxInterfaceObjectType::System::Device, QKnxInterfaceObjectProperty::Device::ErrorFlags,
        QByteArray::fromHex("01020304"));

    QCOMPARE(tpdu.size(), quint16(9));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataIndividual);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::NetworkParameterWrite);
}

void tst_QKnxTpduFactory::testNetworkParameterResponse()
{
   auto tpdu = QKnxTpduFactory::Broadcast::createNetworkParameterResponseTpdu(
        QKnxInterfaceObjectType::System::Device, QKnxInterfaceObjectProperty::Device::ErrorFlags,
        {}, QByteArray(11, 1));

    QCOMPARE(tpdu.size(), quint16(16));
    QCOMPARE(tpdu.dataSize(), quint8(15));

    // TODO: extend test
}

void tst_QKnxTpduFactory::testPropertyValueRead()
{
    auto tpdu = QKnxTpduFactory::PointToPoint::createPropertyValueReadTpdu(
        QKnxTpduFactory::PointToPoint::Mode::Connectionless, 0,
        QKnxInterfaceObjectProperty::Device::ErrorFlags, 1, 1);

    QCOMPARE(tpdu.size(), quint16(6));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataIndividual);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::PropertyValueRead);

    quint8 sequenceNumber = 2;
    tpdu = QKnxTpduFactory::PointToPoint::createPropertyValueReadTpdu(
        QKnxTpduFactory::PointToPoint::Mode::ConnectionOriented, 0,
        QKnxInterfaceObjectProperty::Device::ErrorFlags, 1, 1, sequenceNumber);

    QCOMPARE(tpdu.size(), quint16(6));
    QCOMPARE(tpdu.sequenceNumber(), sequenceNumber);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataConnected);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::PropertyValueRead);
}

void tst_QKnxTpduFactory::testPropertyValueWrite()
{
    auto data = QByteArray::fromHex("01020304");
    auto tpdu = QKnxTpduFactory::PointToPoint::createPropertyValueWriteTpdu(
        QKnxTpduFactory::PointToPoint::Mode::Connectionless, 0,
        QKnxInterfaceObjectProperty::Device::ErrorFlags, 1, 1, data);

    QCOMPARE(tpdu.size(), quint16(10));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataIndividual);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::PropertyValueWrite);

    //connection oriented
    quint8 sequenceNumber = 2;
    tpdu = QKnxTpduFactory::PointToPoint::createPropertyValueWriteTpdu(
        QKnxTpduFactory::PointToPoint::Mode::ConnectionOriented, 0,
        QKnxInterfaceObjectProperty::Device::ErrorFlags, 1, 1, data, sequenceNumber);

    QCOMPARE(tpdu.size(), quint16(10));
    QCOMPARE(tpdu.sequenceNumber(), sequenceNumber);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataConnected);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::PropertyValueWrite);
}

void tst_QKnxTpduFactory::testPropertyDescriptionRead()
{
    auto tpdu = QKnxTpduFactory::PointToPoint::createPropertyDescriptionReadTpdu(
        QKnxTpduFactory::PointToPoint::Mode::Connectionless, 0,
        QKnxInterfaceObjectProperty::Device::ErrorFlags, 1);

    QCOMPARE(tpdu.size(), quint16(5));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataIndividual);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::PropertyDescriptionRead);

    //connection oriented
    quint8 sequenceNumber = 2;
    tpdu = QKnxTpduFactory::PointToPoint::createPropertyDescriptionReadTpdu(
        QKnxTpduFactory::PointToPoint::Mode::ConnectionOriented, 0,
        QKnxInterfaceObjectProperty::Device::ErrorFlags, 1, sequenceNumber);

    QCOMPARE(tpdu.size(), quint16(5));
    QCOMPARE(tpdu.sequenceNumber(), sequenceNumber);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataConnected);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::PropertyDescriptionRead);
}

void tst_QKnxTpduFactory::testFunctionPropertyCommand()
{
    auto data = QByteArray::fromHex("0102030405");
    auto tpdu = QKnxTpduFactory::PointToPoint::createFunctionPropertyCommandTpdu(
        QKnxTpduFactory::PointToPoint::Mode::Connectionless, 0,
        QKnxInterfaceObjectProperty::Device::ErrorFlags, data);

    QCOMPARE(tpdu.size(), quint16(9));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataIndividual);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::FunctionPropertyCommand);

    //connection oriented
    quint8 sequenceNumber = 2;
    tpdu = tpdu = QKnxTpduFactory::PointToPoint::createFunctionPropertyCommandTpdu(
        QKnxTpduFactory::PointToPoint::Mode::ConnectionOriented, 0,
        QKnxInterfaceObjectProperty::Device::ErrorFlags, data, sequenceNumber);

    QCOMPARE(tpdu.size(), quint16(9));
    QCOMPARE(tpdu.sequenceNumber(), sequenceNumber);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataConnected);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::FunctionPropertyCommand);
}

void tst_QKnxTpduFactory::testFunctionPropertyStateRead()
{
    auto data = QByteArray::fromHex("0102030405");
    auto tpdu = QKnxTpduFactory::PointToPoint::createFunctionPropertyStateReadTpdu(
        QKnxTpduFactory::PointToPoint::Mode::Connectionless, 0,
        QKnxInterfaceObjectProperty::Device::ErrorFlags, data);

    QCOMPARE(tpdu.size(), quint16(9));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataIndividual);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::FunctionPropertyStateRead);

    //connection oriented
    quint8 sequenceNumber = 2;
    tpdu = tpdu = QKnxTpduFactory::PointToPoint::createFunctionPropertyStateReadTpdu(
        QKnxTpduFactory::PointToPoint::Mode::ConnectionOriented, 0,
        QKnxInterfaceObjectProperty::Device::ErrorFlags, data, sequenceNumber);

    QCOMPARE(tpdu.size(), quint16(9));
    QCOMPARE(tpdu.sequenceNumber(), sequenceNumber);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataConnected);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::FunctionPropertyStateRead);
}

void tst_QKnxTpduFactory::testLinkRead()
{
    auto data = QByteArray::fromHex("0102030405");
    auto tpdu = QKnxTpduFactory::PointToPoint::createLinkReadTpdu(
        QKnxTpduFactory::PointToPoint::Mode::Connectionless, 0, 1);

    QCOMPARE(tpdu.size(), quint16(4));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataIndividual);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::LinkRead);

    //connection oriented
    quint8 sequenceNumber = 2;
    tpdu = tpdu = QKnxTpduFactory::PointToPoint::createLinkReadTpdu(
        QKnxTpduFactory::PointToPoint::Mode::ConnectionOriented, 0, 1, sequenceNumber);

    QCOMPARE(tpdu.size(), quint16(4));
    QCOMPARE(tpdu.sequenceNumber(), sequenceNumber);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataConnected);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::LinkRead);
}

void tst_QKnxTpduFactory::testLinkWrite()
{
    QKnxAddress individualAddress = QKnxAddress::createIndividual(1, 1, 1);
    auto data = QByteArray::fromHex("0102030405");
    auto tpdu = QKnxTpduFactory::PointToPoint::createLinkWriteTpdu(
        QKnxTpduFactory::PointToPoint::Mode::Connectionless, 0,
        QKnxTpdu::LinkWriteFlags::AddGroupAddress, individualAddress);

    QCOMPARE(tpdu.size(), quint16(2));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::Invalid);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::Invalid);

    QKnxAddress groupAddress = QKnxAddress::createGroup(1, 1);
    tpdu = QKnxTpduFactory::PointToPoint::createLinkWriteTpdu(
        QKnxTpduFactory::PointToPoint::Mode::Connectionless, 0,
        QKnxTpdu::LinkWriteFlags::AddGroupAddress, groupAddress, 1);

    QCOMPARE(tpdu.size(), quint16(6));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataIndividual);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::LinkWrite);

    //connection oriented
    quint8 sequenceNumber = 2;
    tpdu = tpdu = QKnxTpduFactory::PointToPoint::createLinkWriteTpdu(
        QKnxTpduFactory::PointToPoint::Mode::ConnectionOriented, 0,
        QKnxTpdu::LinkWriteFlags::AddGroupAddress, groupAddress, sequenceNumber);

    QCOMPARE(tpdu.size(), quint16(6));
    QCOMPARE(tpdu.sequenceNumber(), sequenceNumber);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataConnected);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::LinkWrite);
}

void tst_QKnxTpduFactory::testDeviceDescriptorRead()
{
    quint8 descriptorType = 64;
    auto tpdu = QKnxTpduFactory::PointToPoint::createDeviceDescriptorReadTpdu(
        QKnxTpduFactory::PointToPoint::Mode::Connectionless, descriptorType);

    QCOMPARE(tpdu.size(), quint16(2));
    QCOMPARE(tpdu.transportControlField(),
        QKnxTpdu::TransportControlField::Invalid);
    QCOMPARE(tpdu.applicationControlField(),
        QKnxTpdu::ApplicationControlField::Invalid);

    tpdu = QKnxTpduFactory::PointToPoint::createDeviceDescriptorReadTpdu(
        QKnxTpduFactory::PointToPoint::Mode::Connectionless, 63);

    QCOMPARE(tpdu.size(), quint16(2));
    QCOMPARE(tpdu.transportControlField(),
        QKnxTpdu::TransportControlField::DataIndividual);
    QCOMPARE(tpdu.applicationControlField(),
        QKnxTpdu::ApplicationControlField::DeviceDescriptorRead);

    //connection oriented
    quint8 sequenceNumber = 2;
    tpdu = tpdu = QKnxTpduFactory::PointToPoint::createDeviceDescriptorReadTpdu(QKnxTpduFactory
        ::PointToPoint::Mode::ConnectionOriented, 0, sequenceNumber);

    QCOMPARE(tpdu.size(), quint16(2));
    QCOMPARE(tpdu.sequenceNumber(), sequenceNumber);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataConnected);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::DeviceDescriptorRead);
}

void tst_QKnxTpduFactory::testDeviceDescriptorResponse()
{
    quint8 descriptorType = 63;
    auto tpdu = QKnxTpduFactory::PointToPoint::createDeviceDescriptorResponseTpdu(
        QKnxTpduFactory::PointToPoint::Mode::Connectionless, descriptorType, QByteArray(253, 0));

    QCOMPARE(tpdu.size(), quint16(255));
    QCOMPARE(tpdu.dataSize(), quint8(254));

    // TODO: extend test
}

void tst_QKnxTpduFactory::testAdcRead()
{
    quint8 sequenceNumber = 2;
    quint8 channelNumber = 2;
    quint8 readCount = 40;
    auto tpdu = QKnxTpduFactory::PointToPointConnectionOriented::createAdcReadTpdu(channelNumber,
        readCount, sequenceNumber);
    QCOMPARE(tpdu.size(), quint16(3));
    QCOMPARE(tpdu.sequenceNumber(), sequenceNumber);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataConnected);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::AdcRead);
}

void tst_QKnxTpduFactory::testMemoryRead()
{
    quint8 sequenceNumber = 2;
    quint8 number = 2;
    quint16 memoryAddress = 0xabcd;
    auto tpdu = QKnxTpduFactory::PointToPoint::createMemoryReadTpdu(QKnxTpduFactory::PointToPoint
        ::Mode::ConnectionOriented, number, memoryAddress, sequenceNumber);

    QCOMPARE(tpdu.size(), quint16(4));
    QCOMPARE(tpdu.sequenceNumber(), sequenceNumber);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataConnected);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::MemoryRead);
}

void tst_QKnxTpduFactory::testMemoryWrite()
{
    auto data = QByteArray::fromHex("0102030405");
    quint8 sequenceNumber = 2;
    quint8 number = 2;
    quint16 memoryAddress = 0x1502;
    auto tpdu = QKnxTpduFactory::PointToPoint::createMemoryWriteTpdu(QKnxTpduFactory::PointToPoint
        ::Mode::ConnectionOriented, number, memoryAddress, data,
        sequenceNumber);

    QCOMPARE(tpdu.size(), quint16(9));
    QCOMPARE(tpdu.sequenceNumber(), sequenceNumber);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataConnected);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::MemoryWrite);
}

void tst_QKnxTpduFactory::testUserMemoryRead()
{
    quint8 sequenceNumber = 2;
    quint8 addressExtention = 1;
    quint8 number = 3;
    quint16 memoryAddress = 0xffff;
    auto tpdu = QKnxTpduFactory::PointToPointConnectionOriented::createUserMemoryReadTpdu(addressExtention,
        number, memoryAddress, sequenceNumber);

    QCOMPARE(tpdu.size(), quint16(5));
    QCOMPARE(tpdu.sequenceNumber(), sequenceNumber);
    QCOMPARE(tpdu.data(), QByteArray::fromHex("13FFFF"));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataConnected);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::UserMemoryRead);
}

void tst_QKnxTpduFactory::testUserMemoryWrite()
{
    auto data = QByteArray::fromHex("0102030405");
    quint8 sequenceNumber = 2;
    quint8 addressExtention = 1;
    quint8 number = 2;
    quint16 memoryAddress = 0x0000;
    auto tpdu = QKnxTpduFactory::PointToPointConnectionOriented::createUserMemoryWriteTpdu(addressExtention,
        number, memoryAddress, data, sequenceNumber);

    QCOMPARE(tpdu.size(), quint16(10));
    QCOMPARE(tpdu.sequenceNumber(), sequenceNumber);
    QCOMPARE(tpdu.data(), QByteArray::fromHex("1200000102030405"));
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataConnected);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::UserMemoryWrite);
}

void tst_QKnxTpduFactory::testUserManufacturerInfoRead()
{
    quint8 sequenceNumber = 2;
    auto tpdu = QKnxTpduFactory::PointToPointConnectionOriented::createUserManufacturerInfoReadTpdu(sequenceNumber);

    QCOMPARE(tpdu.size(), quint16(2));
    QCOMPARE(tpdu.sequenceNumber(), sequenceNumber);
    QCOMPARE(tpdu.transportControlField(), QKnxTpdu::TransportControlField::DataConnected);
    QCOMPARE(tpdu.applicationControlField(), QKnxTpdu::ApplicationControlField::UserManufacturerInfoRead);
}

QTEST_APPLESS_MAIN(tst_QKnxTpduFactory)

#include "tst_qknxtpdufactory.moc"
