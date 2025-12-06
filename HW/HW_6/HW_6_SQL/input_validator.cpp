#include "input_validator.h"
#include <regex>

InputValidator::InputValidator() {
}

bool InputValidator::isValidEmail(const std::string& email) const {
    std::size_t atPos = email.find('@');
    std::size_t dotPos = email.find('.', atPos == std::string::npos ? 0 : atPos);

    if (atPos == std::string::npos) {
        return false;
    }
    if (dotPos == std::string::npos) {
        return false;
    }
    if (atPos == 0) {
        return false;
    }
    if (dotPos <= atPos + 1) {
        return false;
    }
    if (dotPos == email.length() - 1) {
        return false;
    }
    if (email.length() > 100) {
        return false;
    }

    return true;
}

bool InputValidator::isSafeInput(const std::string& text) const {
    if (text.find("'--") != std::string::npos) {
        return false;
    }
    if (text.find("' AND") != std::string::npos) {
        return false;
    }
    if (text.find("' OR ") != std::string::npos) {
        return false;
    }
    if (text.find("' UNION") != std::string::npos) {
        return false;
    }
    if (text.length() > 200) {
        return false;
    }

    return true;
}

bool InputValidator::isValidName(const std::string& name) const {
    if (name.empty()) {
        return false;
    }
    if (name.length() > 100) {
        return false;
    }
    return isSafeInput(name);
}

bool InputValidator::isValidGroupName(const std::string& groupName) const {
    if (groupName.empty()) {
        return false;
    }
    if (groupName.length() > 50) {
        return false;
    }

    // 3 заглавные буквы (латинские или русские), затем "мд",
    // затем "-" + цифры + "-" + цифры
    std::regex pattern("^[A-Z]{3}md-[0-9]+-[0-9]+$");

    return std::regex_match(groupName, pattern);
}

bool InputValidator::isValidSubject(const std::string& subject) const {
    if (subject.empty()) {
        return false;
    }
    if (subject.length() > 100) {
        return false;
    }
    return isSafeInput(subject);
}

bool InputValidator::isValidGrade(int grade) const {
    return grade >= 0 && grade <= 100;
}
