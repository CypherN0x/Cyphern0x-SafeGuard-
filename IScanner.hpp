#ifndef SAFEGUARD_ISCANNER_HPP
#define SAFEGUARD_ISCANNER_HPP

#include <string>
#include <vector>

namespace SafeGuard {

enum class ScanStatus {
    CLEAN,
    INFECTED,
    SUSPICIOUS,
    ERROR
};

struct ScanResult {
    ScanStatus status;
    std::string threatName;
    std::string filePath;
    std::string details;
};

class IScanner {
public:
    virtual ~IScanner() = default;
    virtual ScanResult scanFile(const std::string& filePath) = 0;
    virtual std::string getName() const = 0;
};

} // namespace SafeGuard

#endif // SAFEGUARD_ISCANNER_HPP
