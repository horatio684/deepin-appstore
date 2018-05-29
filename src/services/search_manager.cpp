/*
 * Copyright (C) 2018 Deepin Technology Co., Ltd.
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

#include "services/search_manager.h"

#include <algorithm>
#include <QDebug>

namespace dstore {

namespace {

const int kMaxSearchResult = 10;

AppSearchRecordList SearchApp(const QString& keyword,
                              const AppSearchRecordList& apps) {
  AppSearchRecordList result;
  for (const AppSearchRecord& app : apps) {
    if (app.name.contains(keyword, Qt::CaseInsensitive) ||
        app.local_name.contains(keyword, Qt::CaseInsensitive)) {
      result.append(app);
    }
  }

  for (const AppSearchRecord& app : apps) {
    if (app.description.contains(keyword, Qt::CaseInsensitive) ||
        app.slogan.contains(keyword, Qt::CaseInsensitive)) {
      result.append(app);
    }
  }

  auto last = std::unique(result.begin(), result.end());
  result.erase(last, result.end());

  return result;
}

}  // namespace

SearchManager::SearchManager(QObject* parent)
    : QObject(parent),
      record_list_() {
  this->setObjectName("SearchManager");
}

SearchManager::~SearchManager() {

}

void SearchManager::searchApp(const QString& keyword) {
  AppSearchRecordList result = SearchApp(keyword, record_list_);
  result = result.mid(0, kMaxSearchResult);
  emit this->searchAppResult(keyword, result);
}

void SearchManager::completeSearchApp(const QString& keyword) {
  AppSearchRecordList result = SearchApp(keyword, record_list_);
  emit this->completeSearchAppResult(keyword, result);
}

void SearchManager::updateAppList(const AppSearchRecordList& record_list) {
  record_list_ = record_list;

  // Sort application list by appName.
  std::sort(record_list_.begin(), record_list_.end());
}

}  // namespace dstore