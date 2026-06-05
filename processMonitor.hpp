#ifndef SAFEGUARD_PROCESS_MONITOR_HPP
#define SAFEGUARD_PROCESS_MONITOR_HPP

#include <string>
#include <vector>
#include <windows.h>

namespace SafeGuard {

struct ProcessInfo {
    DWORD pid;
    std::string name;
};

class ProcessMonitor {
public:
    static std::vector<ProcessInfo> listRunningProcesses();
    static bool killProcess(DWORD pid);
    static bool killProcessByName(const std::string& name);
};

} // namespace SafeGuard

#endif // SAFEGUARD_PROCESS_MONITOR_HPP
