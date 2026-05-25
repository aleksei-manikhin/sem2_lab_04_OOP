#ifndef FILEREADER_H
#define FILEREADER_H

#include "baseFileReader.h"
#include "figure.h"
#include "vertex.h"

#include <string>
#include <vector>

class FileReader : public BaseFileReader {
private:
    std::vector<std::vector<float>> ReadValues(const std::string& path) const;
    std::vector<float> ParseLine(const std::string& line) const;
    std::vector<Vertex> CreateVertices(const std::vector<std::vector<float>>& values,
                                       const NormalizationParameters& parameters) const;
    Figure CreateAxesFigure(float length) const;
    float GetAxisLength(const std::vector<std::vector<float>>& values,
                        const NormalizationParameters& parameters) const;
    std::pair<float, float> FindValueRange(const std::vector<std::vector<float>>& values) const;
    float NormalizeValue(float value, float sourceMin, float sourceMax,
                         const NormalizationParameters& parameters) const;
    void ValidateValues(const std::vector<std::vector<float>>& values) const;

public:
    Scene ReadScene(const std::string& path, const NormalizationParameters& parameters) override;
};

#endif // FILEREADER_H
