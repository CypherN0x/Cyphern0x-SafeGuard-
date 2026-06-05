#include "../../include/scanner/SignatureScanner.hpp"
#include <fstream>
#include <iostream>

namespace SafeGuard {

SignatureScanner::SignatureScanner() {
    // Mock signatures for demonstration
    signatures["e99a18c428cb38d5f260853678922e03"] = "EICAR-Test-File";
}

ScanResult SignatureScanner::scanFile(const std::string& filePath) {
    ScanResult result;
    result.filePath = filePath;
    result.status = ScanStatus::CLEAN;

    std::string hash = calculateHash(filePath);
    if (hash.empty()) {
        result.status = ScanStatus::ERROR;
        result.details = "Could not calculate hash";
        return result;
    }

    if (signatures.find(hash) != signatures.end()) {
        result.status = ScanStatus::INFECTED;
        result.threatName = signatures[hash];
        result.details = "Signature match found in database.";
    }

    return result;
}

std::string SignatureScanner::calculateHash(const std::string& filePath) {
    // Placeholder for actual hashing (MD5/SHA256)
    // In a real implementation, we would use a library like OpenSSL or a custom hash function
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return "";

    // For now, let's just return a mock hash for the EICAR test string if found
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    if (content.find("X5O!P%@AP[4\\PZX54(P^)7CC)7}$EICAR-STANDARD-ANTIVIRUS-TEST-FILE!$H+H*") != std::string::npos) {
        return "e99a18c428cb38d5f260853678922e03";
    }

    return "clean_hash_placeholder";
}

} // namespace SafeGuard
