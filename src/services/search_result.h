/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEEPIN_APPSTORE_SERVICES_SEARCH_RESULT_H
#define DEEPIN_APPSTORE_SERVICES_SEARCH_RESULT_H

#include <QList>
#include <QHash>
#include <QtCore/QMetaType>

namespace dstore {

// App entry used in search service.
struct AppSearchRecord {
  QString name;
  QString local_name;
  QString slogan;
  QString description;
  QStringList package_uris;

  // Package name used in deb format.
  QString deb;

  // Package name used in flatpak format.
  QString flatpak;
};

bool operator==(const AppSearchRecord& a, const AppSearchRecord& b);

void RegisterAppSearchRecordMetaType();

bool operator<(const AppSearchRecord& a, const AppSearchRecord& b);

typedef QList<AppSearchRecord> AppSearchRecordList;

typedef QHash<QString, AppSearchRecord> AppSearchRecordMap;

}  // namespace dstore

Q_DECLARE_METATYPE(dstore::AppSearchRecord);
Q_DECLARE_METATYPE(dstore::AppSearchRecordList);

#endif  // DEEPIN_APPSTORE_SERVICES_SEARCH_RESULT_H
