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
