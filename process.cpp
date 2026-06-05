#include "core/ProcessMonitor.hpp"
#include <psapi.h>
#include <iostream>
#include <algorithm>

namespace SafeGuard {

std::vector<ProcessInfo> ProcessMonitor::listRunningProcesses() {
    std::vector<ProcessInfo> processes;
    DWORD aProcesses[1024], cbNeeded, cProcesses;

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
        return processes;
    }

    cProcesses = cbNeeded / sizeof(DWORD);

    for (unsigned int i = 0; i < cProcesses; i++) {
        if (aProcesses[i] != 0) {
            char szProcessName[MAX_PATH] = "<unknown>";
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);

            if (hProcess != NULL) {
                HMODULE hMod;
                DWORD cbNeededMod;
                if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeededMod)) {
                    GetModuleBaseNameA(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(char));
                }
                CloseHandle(hProcess);
            }
            processes.push_back({aProcesses[i], std::string(szProcessName)});
        }
    }
    return processes;
}

bool ProcessMonitor::killProcess(DWORD pid) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProcess == NULL) return false;

    BOOL result = TerminateProcess(hProcess, 1);
    CloseHandle(hProcess);
    
    if (result) {
        std::cout << "[Process] REAL KILL: Process with PID " << pid << " terminated." << std::endl;
    }
    return result != 0;
}

bool ProcessMonitor::killProcessByName(const std::string& name) {
    auto list = listRunningProcesses();
    bool found = false;
    for (const auto& proc : list) {
        if (proc.name == name) {
            killProcess(proc.pid);
            found = true;
        }
    }
    return found;
}

} // namespace SafeGuard
