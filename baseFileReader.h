#ifndef BASEFILEREADER_H
#define BASEFILEREADER_H

#include "normalizationParameters.h"
#include "scene.h"

#include <string>

class BaseFileReader {
public:
    virtual ~BaseFileReader() = default;

    virtual Scene ReadScene(const std::string& path, const NormalizationParameters& parameters) = 0;
};

#endif // BASEFILEREADER_H
