#ifndef NORMALIZATIONPARAMETERS_H
#define NORMALIZATIONPARAMETERS_H

class NormalizationParameters {
public:
    float Min = 0.0f;
    float Max = 5.0f;
    float DxStep = 1.0f;
    float DyStep = 1.0f;

    NormalizationParameters(float min, float max, float dxStep, float dyStep)
        : Min(min), Max(max), DxStep(dxStep), DyStep(dyStep){}
};

#endif // NORMALIZATIONPARAMETERS_H
