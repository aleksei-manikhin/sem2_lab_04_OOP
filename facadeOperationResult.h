#ifndef FACADEOPERATIONRESULT_H
#define FACADEOPERATIONRESULT_H

#include <string>

class FacadeOperationResult {
private:
    std::string errorMessage;
    bool isSuccess;

public:
    FacadeOperationResult(bool isSuccess, const std::string& errorMessage);

    std::string GetErrorMessage() const;
    bool IsSuccess() const;
};

#endif // FACADEOPERATIONRESULT_H
