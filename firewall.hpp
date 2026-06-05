#ifndef SAFEGUARD_ENGINE_HPP
#define SAFEGUARD_ENGINE_HPP

#include "../scanner/IScanner.hpp"
#include "../monitor/FileMonitor.hpp"
#include "Quarantine.hpp"
#include "Firewall.hpp"
#include <vector>
#include <memory>

namespace SafeGuard {

class Engine {
public:
    Engine();
    ~Engine();

    void init();
    void run();
    void stop();

    void checkForUpdates();
    void addScanner(std::unique_ptr<IScanner> scanner);
    void onFileEvent(const std::string& filePath, FileAction action);
    void listNetworkActivity();

private:
    bool running;
    std::vector<std::unique_ptr<IScanner>> scanners;
    std::unique_ptr<FileMonitor> monitor;
    std::unique_ptr<Quarantine> quarantine;
    std::unique_ptr<Firewall> firewall;
};

} // namespace SafeGuard

#endif // SAFEGUARD_ENGINE_HPP
