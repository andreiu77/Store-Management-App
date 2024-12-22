#include <string>
#include <fstream>
#include <vector>
#include <iostream>

const std::string ENCRYPTION_KEY = "c1a8e34dfe19b7a2c7f5e6d5b8f4c3a2e7d1c5f6a4b3c8f7d6a9e2b4f8d3c1e7e4f3d2c1a5b9c8e7d6f2b3a1c9e8d7f4c3b1a2d6f8e7c4b5a3c1e2f9d7b8a4";

// Simple XOR encryption/decryption
inline std::string encryptDecrypt(const std::string& input, const std::string& key) {
    std::string output = input;
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] ^ key[i % key.size()];
    }
    return output;
}

inline bool checkUniqueId(const std::string& id) {
    std::ifstream file("Encryption/credentials.dat", std::ios::binary);
    if (!file.is_open()) {
        return true; 
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string decryptedLine = encryptDecrypt(line, ENCRYPTION_KEY);
        if (decryptedLine.substr(0, id.size()) == id) {
            file.close();
            return false;
        }
    }
    file.close();
    return true;
}

inline bool addCredentials(const std::string& username, const std::string& password) {
    std::ofstream file("Encryption/credentials.dat", std::ios::binary | std::ios::app);
    if (!file.is_open()) {
        return false;
    }

    std::string credentials = username + " " + password;
    std::string encryptedCredentials = encryptDecrypt(credentials, ENCRYPTION_KEY);
    file.write("\n", 1);
    file.write(encryptedCredentials.c_str(), encryptedCredentials.size());
    file.close();
    return true;
}

inline bool checkCredentials(const std::string& username, const std::string& password) {
    std::ifstream file("Encryption/credentials.dat", std::ios::binary);
    if (!file.is_open()) {
        return false; 
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string decryptedLine = encryptDecrypt(line, ENCRYPTION_KEY);
        if (decryptedLine == username + " " + password) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
