#include "fileReader.h"

#include <algorithm>
#include <fstream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <utility>

Scene FileReader::ReadScene(const std::string& path, const NormalizationParameters& parameters) {
    std::vector<std::vector<float>> values = ReadValues(path);
    std::vector<Vertex> vertices = CreateVertices(values, parameters);

    Scene scene;
    scene.AddFigure(Figure(std::move(vertices), values.size(), values[0].size()));

    return scene;
}

std::vector<std::vector<float>> FileReader::ReadValues(const std::string& path) const {
    std::ifstream file(path);

    if (!file.is_open())
        throw std::runtime_error("Unable to open file");

    std::vector<std::vector<float>> values;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        values.push_back(ParseLine(line));
    }
    ValidateValues(values);

    return values;
}

std::vector<float> FileReader::ParseLine(const std::string& line) const {
    std::string normalizedLine = line;
    std::replace(normalizedLine.begin(), normalizedLine.end(), ';', ',');

    std::vector<float> row;
    std::stringstream stream(normalizedLine);
    std::string token;

    while (std::getline(stream, token, ',')) {
        try {
            row.push_back(std::stof(token));
        } catch (const std::exception&) {
            throw std::invalid_argument("Invalid CSV file");
        }
    }

    return row;
}

std::vector<Vertex> FileReader::CreateVertices(const std::vector<std::vector<float>>& values,
                                               const NormalizationParameters& parameters) const {
    const std::pair<float, float> sourceRange = FindValueRange(values);
    const float sourceMin = sourceRange.first;
    const float sourceMax = sourceRange.second;

    if (sourceMin == sourceMax)
        throw std::invalid_argument("Cannot normalize CSV file");

    std::vector<Vertex> vertices;
    vertices.reserve(values.size() * values[0].size());

    for (std::size_t row = 0; row < values.size(); row++)
        for (std::size_t column = 0; column < values[row].size(); column++) {
            const float x = column * parameters.DxStep;
            const float y = row * parameters.DyStep;
            const float z = NormalizeValue(values[row][column], sourceMin, sourceMax, parameters);

            vertices.emplace_back(x, y, z);
        }

    return vertices;
}

std::pair<float, float> FileReader::FindValueRange(const std::vector<std::vector<float>>& values) const {
    float sourceMin = std::numeric_limits<float>::max();
    float sourceMax = std::numeric_limits<float>::lowest();

    for (const std::vector<float>& row : values) {
        for (float value : row) {
            sourceMin = std::min(sourceMin, value);
            sourceMax = std::max(sourceMax, value);
        }
    }

    return {sourceMin, sourceMax};
}

float FileReader::NormalizeValue(float value, float sourceMin, float sourceMax,
                                 const NormalizationParameters& parameters) const {
    return parameters.Min +
           (value - sourceMin) / (sourceMax - sourceMin) * (parameters.Max - parameters.Min);
}

void FileReader::ValidateValues(const std::vector<std::vector<float>>& values) const {
    if (values.empty()) {
        throw std::invalid_argument("Invalid CSV file");
    }

    const std::size_t columnCount = values[0].size();

    for (const std::vector<float>& row : values) {
        if (row.empty() || row.size() != columnCount) {
            throw std::invalid_argument("Invalid CSV file");
        }
    }
}
