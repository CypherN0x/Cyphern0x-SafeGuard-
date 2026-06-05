#include "../../include/core/Quarantine.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

namespace fs = std::filesystem;

namespace SafeGuard {

Quarantine::Quarantine(const std::string& dir) : quarantineDir(dir) {
    ensureDirectoryExists();
}

bool Quarantine::isolateFile(const std::string& filePath, const std::string& threatName) {
    try {
        fs::path src(filePath);
        if (!fs::exists(src)) return false;

        std::string fileName = src.filename().string();
        std::string encryptedName = encryptFileName(fileName) + ".sglock";
        fs::path dest = fs::path(quarantineDir) / encryptedName;

        std::cout << "[Quarantine] Isolating threat: " << threatName << " (" << fileName << ")" << std::endl;
        
        // In a real AV, we would XOR encrypt the file content here
        // For now, we just move it to the quarantine directory
        fs::copy(src, dest, fs::copy_options::overwrite_existing);
        fs::remove(src);

        std::cout << "[Quarantine] File moved to: " << dest.string() << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[Quarantine] Error isolating file: " << e.what() << std::endl;
        return false;
    }
}

void Quarantine::ensureDirectoryExists() {
    if (!fs::exists(quarantineDir)) {
        fs::create_directories(quarantineDir);
    }
}

std::string Quarantine::encryptFileName(const std::string& originalName) {
    // Simple mock encryption for the filename
    std::string result = originalName;
    for(char &c : result) c ^= 0xFF; 
    return "THREAT_" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
}

bool Quarantine::restoreFile(const std::string& threatId, const std::string& destinationPath) {
    // Logic to decrypt and move back
    return false;
}

void Quarantine::listQuarantinedFiles() {
    std::cout << "--- Quarantined Files ---" << std::endl;
    for (const auto& entry : fs::directory_iterator(quarantineDir)) {
        std::cout << entry.path().filename().string() << std::endl;
    }
}

} // namespace SafeGuard
