/*
   This file is part of the KDE Baloo project.
 * Copyright (C) 2015  Vishesh Handa <vhanda@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "../positiondb.h"

#include <QTest>
#include <QTemporaryDir>

using namespace Baloo;

class PositionDBTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void test();
};

void PositionDBTest::test()
{
    QTemporaryDir dir;

    MDB_env* env;
    MDB_txn* txn;

    mdb_env_create(&env);
    mdb_env_set_maxdbs(env, 1);

    // The directory needs to be created before opening the environment
    QByteArray path = QFile::encodeName(dir.path());
    mdb_env_open(env, path.constData(), 0, 0664);
    mdb_txn_begin(env, NULL, 0, &txn);

    PositionDB db(txn);

    QByteArray word("fire");
    Position pos1;
    pos1.docId = 1;
    pos1.positions = QVector<uint>() << 1 << 5 << 6;

    Position pos2;
    pos2.docId = 5;
    pos2.positions = QVector<uint>() << 41 << 96 << 116;

    QVector<Position> list = {pos1, pos2};

    db.put(word, list);
    QVector<Position> res = db.get(word);
    QCOMPARE(res, list);

    mdb_txn_abort(txn);
    mdb_env_close(env);
}

QTEST_MAIN(PositionDBTest)

#include "positiondbtest.moc"
