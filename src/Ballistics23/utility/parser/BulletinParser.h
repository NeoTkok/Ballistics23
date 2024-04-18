//
// Created by neodima on 08.12.23.
//

#pragma once

#include "Ballistics23/utility/types/BasicTypes.h"
#include <fstream>


namespace Ballistics23::Utility {

std::string getRootPath(const std::string& filePath, int stepsBack) {
  std::string rootPath = filePath;
  for (int i = 0; i < stepsBack; ++i) {
    size_t lastSeparator = rootPath.rfind('/');
    if (lastSeparator == std::string::npos) {
      lastSeparator = rootPath.rfind('\\'); //  попробуем обратный слеш для Windows
    }

    if (lastSeparator != std::string::npos) {
      rootPath = rootPath.substr(0, lastSeparator);
    } else {
      return rootPath;
    }
  }
  return rootPath;
}





/**
 * Аналог функции split() на питоне
 * @param s строка
 * @param delimiter разделитель
 * @return вектор разделенных строк
 */
[[nodiscard]] Containers::vector<Containers::string>
split(const Containers::string &s,
      const Containers::string &delimiter = " ") noexcept {
  Ballistics23::indexType pos_start = 0, pos_end,
                          delim_len = delimiter.length();
  Containers::vector<Containers::string> res;

  while ((pos_end = s.find(delimiter, pos_start)) != Containers::string::npos) {
    const Containers::string token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(s.substr(pos_start));
  return res;
}


[[nodiscard]] std::vector<scalar>
getColumn(const std::string &path, const indexType column, const indexType& compareColumn,
          const scalar Begin, const scalar End) noexcept {
  std::vector<scalar> result;

  std::ifstream file(path);
  if (!file.is_open()) {
    return result;
  }

  std::string line;
  std::getline(file, line); // Пропускаем первую строку

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string cell;
    indexType currentColumn = 0;
    scalar value;
    scalar compareValue;

    while (std::getline(ss, cell, ',')) {
      if (currentColumn == compareColumn) {
        try {
          compareValue = std::stod(cell);
        } catch (...) {
          continue;
        }
      }
      if (currentColumn == column) {
        try {
          value = std::stod(cell);
        } catch (...) {
          continue;
        }
      }
      ++currentColumn;
    }

    if (compareValue >= Begin && compareValue <= End) {
      result.push_back(static_cast<scalar>(value));
    }
  }

  return result;
}

} // namespace Ballistics23::Utility
