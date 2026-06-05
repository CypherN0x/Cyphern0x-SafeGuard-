#ifndef SAFEGUARD_SIGNATURE_SCANNER_HPP
#define SAFEGUARD_SIGNATURE_SCANNER_HPP

#include "IScanner.hpp"
#include <unordered_map>

namespace SafeGuard {

class SignatureScanner : public IScanner {
public:
    SignatureScanner();
    ScanResult scanFile(const std::string& filePath) override;
    std::string getName() const override { return "SignatureScanner"; }

    void loadSignatures(const std::string& signatureFile);

private:
    // Simple MD5 or SHA256 based signatures for now
    std::unordered_map<std::string, std::string> signatures; 
    std::string calculateHash(const std::string& filePath);
};

} // namespace SafeGuard

#endif // SAFEGUARD_SIGNATURE_SCANNER_HPP
