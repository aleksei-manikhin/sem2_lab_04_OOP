#include "facadeOperationResult.h"

FacadeOperationResult::FacadeOperationResult(bool isSuccess, const std::string& errorMessage)
    : errorMessage(errorMessage), isSuccess(isSuccess) {}

std::string FacadeOperationResult::GetErrorMessage() const {
    return errorMessage;
}

bool FacadeOperationResult::IsSuccess() const {
    return isSuccess;
}
