#ifndef NORMALIZATIONPARAMETERS_H
#define NORMALIZATIONPARAMETERS_H

#include <cmath>
#include <stdexcept>

class NormalizationParameters {
public:
    float Min = 0.0f;
    float Max = 5.0f;
    float DxStep = 1.0f;
    float DyStep = 1.0f;

    NormalizationParameters(float min, float max, float dxStep, float dyStep)
        : Min(min), Max(max), DxStep(dxStep), DyStep(dyStep) {
        if (!std::isfinite(min) || !std::isfinite(max) ||
            !std::isfinite(dxStep) || !std::isfinite(dyStep)) {
            throw std::invalid_argument("Normalization parameters must be finite");
        }

        if (min >= max) {
            throw std::invalid_argument("Normalization minimum must be less than maximum");
        }

        if (dxStep <= 0.0f || dyStep <= 0.0f) {
            throw std::invalid_argument("Normalization steps must be positive");
        }
    }
};

#endif // NORMALIZATIONPARAMETERS_H
