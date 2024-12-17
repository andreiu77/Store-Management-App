#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <regex>
#include "Repository/Repository.h"

#define T TrenchCoat

class ValidationException : public std::exception {
public:
    ValidationException(const char* message) : m_message(message) {}

    const char* what() const noexcept override {
        return m_message.c_str();
    }

private:
    std::string m_message;
};

class RepoException : public std::exception {
public:
    RepoException(const char* message) : m_message(message) {}

    const char* what() const noexcept override {
        return m_message.c_str();
    }

private:
    std::string m_message;
};


class Validator {
public:
    static void validateNumbers(std::string choice) {
        std::regex numberRegex(R"(^[+-]?(\d+(\.\d*)?|\.\d+)([eE][+-]?\d+)?$)");
        bool convertible = std::regex_match(choice, numberRegex);
        if (!convertible || choice.length() == 0)
            throw ValidationException("Input is not a number");
    }

    static void validateQuantity(int quantity) {
		if (quantity <= 0)
			throw ValidationException("Out of stock");
	}

    static void validateString(std::string str) {
		if (str.length() == 0)
			throw ValidationException("Input is empty");
	}

    static void validateEntityInexistence(T coat, Repository& repo) {
        if (repo.getPos(coat.getPhotograph()) != -1)
            throw RepoException("A coat with this photo already exists!");
    }

    static void validateEntityExistence(std::string photo, Repository& repo) {
        if (repo.getPos(photo) == -1)
            throw RepoException("A coat with this photo doesn't exist!");
    }

};