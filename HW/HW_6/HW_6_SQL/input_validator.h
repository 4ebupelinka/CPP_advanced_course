#pragma once

#include <string>

class InputValidator {
public:
    InputValidator();

    bool isValidEmail(const std::string& email) const;
    bool isSafeInput(const std::string& text) const;
    bool isValidName(const std::string& name) const;
    bool isValidGroupName(const std::string& groupName) const;
    bool isValidSubject(const std::string& subject) const;
    bool isValidGrade(int grade) const;
};

