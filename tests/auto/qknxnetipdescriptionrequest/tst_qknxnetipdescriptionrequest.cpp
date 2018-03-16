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

#include <QtCore/qdebug.h>
#include <QtTest/qtest.h>
#include <QtKnx/qknxnetipdescriptionrequest.h>

static QString s_msg;
static void myMessageHandler(QtMsgType, const QMessageLogContext &, const QString &msg)
{
    s_msg = msg;
}

class tst_QKnxNetIpDescriptionRequest: public QObject
{
    Q_OBJECT

private slots:
    void testDefaultConstructor();
    void testConstructor();
    void testDebugStream();
};

void tst_QKnxNetIpDescriptionRequest::testDefaultConstructor()
{
    QKnxNetIpFrame frame;
    QKnxNetIpDescriptionRequest descriptionRequest(frame);

    QCOMPARE(descriptionRequest.isValid(), false);
    QCOMPARE(descriptionRequest.controlEndpoint().isValid(), false);
}

void tst_QKnxNetIpDescriptionRequest::testConstructor()
{
    auto frame = QKnxNetIpDescriptionRequest::builder()
        .setControlEndpoint(QKnxNetIpHpaiView::builder()
            .setHostAddress(QHostAddress::LocalHost)
            .setPort(3671).create())
        .create();
    QKnxNetIpDescriptionRequest descriptionRequest(frame);

    QCOMPARE(descriptionRequest.isValid(), true);
    QCOMPARE(frame.size(), quint16(14));
    QCOMPARE(frame.bytes(), QKnxByteArray::fromHex("06100203000e08017f0000010e57"));
    QCOMPARE(frame.data().size(), quint16(8));
    QCOMPARE(frame.data(), QKnxByteArray::fromHex("08017f0000010e57"));

    QCOMPARE(descriptionRequest.controlEndpoint().isValid(), true);
    QCOMPARE(descriptionRequest.controlEndpoint().bytes(),
        QKnxByteArray::fromHex("08017f0000010e57"));
}

void tst_QKnxNetIpDescriptionRequest::testDebugStream()
{
    struct DebugHandler
    {
        explicit DebugHandler(QtMessageHandler newMessageHandler)
            : oldMessageHandler(qInstallMessageHandler(newMessageHandler)) {}
        ~DebugHandler() {
            qInstallMessageHandler(oldMessageHandler);
        }
        QtMessageHandler oldMessageHandler;
    } _(myMessageHandler);

    qDebug() << QKnxNetIpDescriptionRequest::builder().create();
    QCOMPARE(s_msg, QString::fromLatin1("0x061002030006"));

    qDebug() << QKnxNetIpDescriptionRequest::builder()
        .setControlEndpoint(QKnxNetIpHpaiView::builder()
            .setHostAddress(QHostAddress::LocalHost)
            .setPort(3671).create())
        .create();
    QCOMPARE(s_msg, QString::fromLatin1("0x06100203000e08017f0000010e57"));
}

QTEST_APPLESS_MAIN(tst_QKnxNetIpDescriptionRequest)

#include "tst_qknxnetipdescriptionrequest.moc"
