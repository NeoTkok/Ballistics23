//
// Created by neodima on 08.12.23.
//

#pragma once

#include <fstream>
#include "Ballistics23/utility/types/BasicTypes.h"

namespace Ballistics23::Utility {

std::string getRootPath(const std::string &filePath, int stepsBack) {
    std::string rootPath = filePath;
    for (int i = 0; i < stepsBack; ++i) {
        size_t lastSeparator = rootPath.rfind('/');
        if (lastSeparator == std::string::npos) {
            lastSeparator = rootPath.rfind('\\');  //  попробуем обратный слеш для Windows
        }

        if (lastSeparator != std::string::npos) {
            rootPath = rootPath.substr(0, lastSeparator);
        } else {
            return rootPath;
        }
    }
    return rootPath;
}

[[nodiscard]] std::vector<scalar> getColumn(const std::string &path, const indexType column,
                                            const indexType &compareColumn, const scalar Begin,
                                            const scalar End) noexcept {
    std::vector<scalar> result;

    std::ifstream file(path);
    if (!file.is_open()) {
        return result;
    }

    std::string line;
    std::getline(file, line);  // Пропускаем первую строку

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

/**
 * Меняет подстроки в строке на заданные
 * @param str строка для изменения
 * @param from что меняем
 * @param to на что меняем
 * @return строка с замененными подстроками
 */
[[nodiscard]] Containers::string ReplaceAll(Containers::string str, const Containers::string &from,
                                            const Containers::string &to) noexcept {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != Containers::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

/**
 * Аналог функции split() на питоне
 * @param s строка
 * @param delimiter разделитель
 * @return вектор разделенных строк
 */
[[nodiscard]] Containers::vector<Containers::string> split(const Containers::string &s,
                                                           const Containers::string &delimiter = " ") noexcept {
    Ballistics23::indexType pos_start = 0, pos_end, delim_len = delimiter.length();
    Containers::vector<Containers::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != Containers::string::npos) {
        const Containers::string token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

struct MJD_DUT {
    Containers::vector<scalar> mjdVector;
    Containers::vector<scalar> dutVector;
};

/**
 * Парсит файлик бюллетени и возвращает значения дута в заданном отрезке (левая
 * и правая границы входят)
 * @param path путь до файла eopc04_IAU2000.62-now
 * @param mjdBegin момент, с которого записываем данные в массив
 * @param mjdEnd момент, до которого записываем данные в массив
 * @return 2 массива: mjd и соответствующие dut
 */
[[nodiscard]] MJD_DUT bulletinGetMJD_DUT(const Containers::string &path, const scalar mjdBegin, const scalar mjdEnd,
                                         bool CSV = false) noexcept {
    Containers::vector<scalar> mjdVector, dutVector;

    std::ifstream inputFile;
    inputFile.open(path);

    Ballistics23::indexType counter = 1;
    Containers::string line, resultLine;
    if (inputFile.is_open()) {
        while (!inputFile.eof()) {
            std::getline(inputFile, line);

            // данные начинаются с 15 строчки (счетчик с 1)
            if (counter >= 15) {
                resultLine = ReplaceAll(line, "    ", " ");
                resultLine = ReplaceAll(resultLine, "   ", " ");
                resultLine = ReplaceAll(resultLine, "  ", " ");

                const Containers::string delimiter = " ";
                const Ballistics23::Containers::vector<Containers::string> stringVector = split(resultLine, delimiter);

                // иначе последняя строчка имеет размер 1 и все падает
                if (stringVector.size() == 16) {
                    const auto mjd = static_cast<scalar>(std::stod(stringVector[3]));
                    const auto dut = static_cast<scalar>(std::stod(stringVector[6]));

                    // добавляем только в нужных границах
                    if (mjd >= mjdBegin && mjd <= mjdEnd) {
                        mjdVector.push_back(mjd);
                        dutVector.push_back(dut);
                    }

                    if (mjd > mjdEnd) {
                        return {mjdVector, dutVector};
                    }
                }
            }

            counter++;
        }

        inputFile.close();
    }

    return {mjdVector, dutVector};
}

/**
 * Парсит файлик СSV и возвращает значения дута в заданном отрезке (левая и
 * правая границы входят)
 * @param path путь до файла CSV
 * @param mjdBegin момент, с которого записываем данные в массив
 * @param mjdEnd момент, до которого записываем данные в массив
 * @return 2 массива: mjd и соответствующие dut
 */
[[nodiscard]] MJD_DUT CSVgetMJD_DUT(const Containers::string &path, const scalar mjdBegin,
                                    const scalar mjdEnd) noexcept {
    Containers::vector<scalar> mjdVector, dutVector;

    std::ifstream inputFile;
    inputFile.open(path);

    Ballistics23::indexType counter = 1;
    Containers::string line;
    if (inputFile.is_open()) {
        while (!inputFile.eof()) {
            std::getline(inputFile, line);

            // данные начинаются с 15 строчки (счетчик с 1)
            if (counter >= 2) {
                const Containers::string delimiter = ",";
                const Ballistics23::Containers::vector<Containers::string> stringVector = split(line, delimiter);

                if (stringVector.size() == 16) {
                    const auto mjd = static_cast<scalar>(std::stod(stringVector[3]));
                    const auto dut = static_cast<scalar>(std::stod(stringVector[6]));

                    // добавляем только в нужных границах
                    if (mjd >= mjdBegin && mjd <= mjdEnd) {
                        mjdVector.push_back(mjd);
                        dutVector.push_back(dut);
                    }

                    if (mjd > mjdEnd) {
                        return {mjdVector, dutVector};
                    }
                }
            }

            counter++;
        }

        inputFile.close();
    }

    return {mjdVector, dutVector};
}

}  // namespace Ballistics23::Utility
