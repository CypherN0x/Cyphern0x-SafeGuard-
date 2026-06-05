#include "../../include/monitor/FileMonitor.hpp"
#include <iostream>
#include <windows.h>
#include <vector>

namespace SafeGuard {

FileMonitor::FileMonitor() : running(false) {}

FileMonitor::~FileMonitor() {
    stop();
}

void FileMonitor::start(const std::string& path) {
    if (running) return;
    
    running = true;
    std::cout << "[FileMonitor] Windows API Monitoring started on: " << path << std::endl;
    monitorThread = std::thread(&FileMonitor::monitorLoop, this, path);
}

void FileMonitor::stop() {
    running = false;
    // We need to trigger an event or use a timeout to break ReadDirectoryChangesW
    // For simplicity in this example, we'll just let the thread handle its closure
    if (monitorThread.joinable()) {
        // monitorThread.join(); // Joining might block if ReadDirectoryChangesW is waiting
        monitorThread.detach(); 
    }
}

void FileMonitor::setCallback(FileCallback cb) {
    callback = cb;
}

void FileMonitor::monitorLoop(const std::string& path) {
    HANDLE hDir = CreateFileA(
        path.c_str(),
        FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        NULL
    );

    if (hDir == INVALID_HANDLE_VALUE) {
        std::cerr << "[FileMonitor] Error: Could not open directory for monitoring." << std::endl;
        return;
    }

    char buffer[1024 * 8];
    DWORD bytesReturned;

    while (running) {
        if (ReadDirectoryChangesW(
            hDir,
            buffer,
            sizeof(buffer),
            TRUE,
            FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE,
            &bytesReturned,
            NULL,
            NULL
        )) {
            FILE_NOTIFY_INFORMATION* pNotify;
            int offset = 0;
            do {
                pNotify = (FILE_NOTIFY_INFORMATION*)((char*)buffer + offset);
                
                std::wstring fileName(pNotify->FileName, pNotify->FileNameLength / sizeof(WCHAR));
                std::string fileStr(fileName.begin(), fileName.end());
                
                FileAction action;
                switch (pNotify->Action) {
                    case FILE_ACTION_ADDED: action = FileAction::ADDED; break;
                    case FILE_ACTION_MODIFIED: action = FileAction::MODIFIED; break;
                    case FILE_ACTION_REMOVED: action = FileAction::DELETED; break;
                    case FILE_ACTION_RENAMED_OLD_NAME:
                    case FILE_ACTION_RENAMED_NEW_NAME: action = FileAction::RENAMED; break;
                    default: continue;
                }

                if (callback) {
                    callback(fileStr, action);
                }

                offset += pNotify->NextEntryOffset;
            } while (pNotify->NextEntryOffset != 0);
        }
    }

    CloseHandle(hDir);
}

} // namespace SafeGuard
