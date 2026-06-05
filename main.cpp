#include <iostream>
#include <string>
#include "../include/core/Engine.hpp"
#include "../include/core/ProcessMonitor.hpp"

int main() {
    SafeGuard::Engine engine;
    engine.init();
    
    // Create a thread for the engine to run
    std::thread engineThread([&engine]() {
        engine.run();
    });

    // Main thread handles UI commands via stdin
    std::string command;
    while (std::getline(std::cin, command)) {
        if (command == "SCAN_ALL") {
            std::cout << "[Engine] Full System Scan Triggered..." << std::endl;
        } else if (command == "UPDATE_DB") {
            engine.checkForUpdates();
        } else if (command == "FIREWALL_ON") {
            std::cout << "[Engine] Firewall Rules Reloaded." << std::endl;
        } else if (command == "LIST_NET") {
            engine.listNetworkActivity();
        } else if (command == "LIST_PROCS") {
            auto procs = SafeGuard::ProcessMonitor::listRunningProcesses();
            std::cout << "[Process] Listing RUNNING Processes (" << procs.size() << "):" << std::endl;
            for (const auto& p : procs) {
                if (p.name != "<unknown>") {
                    std::cout << "[Proc] " << p.name << " (PID: " << p.pid << ")" << std::endl;
                }
            }
        } else if (command.find("KILL_PROC ") == 0) {
            std::string pidStr = command.substr(10);
            DWORD pid = std::stoul(pidStr);
            SafeGuard::ProcessMonitor::killProcess(pid);
        } else if (command == "QUIT") {
            engine.stop();
            break;
        }
    }

    if (engineThread.joinable()) engineThread.join();
    return 0;
}
