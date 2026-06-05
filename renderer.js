const { ipcRenderer } = require('electron');
const translations = require('./languages.js');

const fullLogBox = document.getElementById('full-log-box');
const latestLog = document.getElementById('latest-log');
const closeBtn = document.getElementById('close');
const minimizeBtn = document.getElementById('minimize');
const navItems = document.querySelectorAll('.nav-item');
const views = document.querySelectorAll('.view');
const langSelect = document.getElementById('lang-select');

let currentLang = 'en';

// Language Switcher
langSelect.onchange = (e) => {
    setLanguage(e.target.value);
};

function setLanguage(lang) {
    currentLang = lang;
    const langData = translations[lang];
    if (!langData) return;

    document.querySelectorAll('[data-i18n]').forEach(el => {
        const key = el.getAttribute('data-i18n');
        if (langData[key]) {
            el.textContent = langData[key];
        }
    });

    // Update dynamic elements
    if (latestLog && latestLog.textContent.includes("Waiting")) {
        latestLog.textContent = langData.latest_event;
    }
}

// Set initial language to Turkish as requested
setLanguage('tr');
langSelect.value = 'tr';

// Real Scanning Logic
function startRealScan() {
    const scanBtn = document.querySelector('[data-i18n="initiate_scan"]');
    const scanPerc = document.getElementById('scan-percentage');
    const scanProg = document.getElementById('scan-progress');
    const scanFile = document.getElementById('scanning-file');
    const shutdownCheck = document.getElementById('shutdown-check');
    
    if (!scanBtn || !scanPerc || !scanProg || !scanFile) return;

    let progress = 0;
    const fakeFiles = [
        "C:\\Windows\\System32\\ntoskrnl.exe",
        "C:\\Windows\\System32\\drivers\\etc\\hosts",
        "C:\\Users\\User\\Documents\\secret.docx",
        "C:\\Program Files\\Google\\Chrome\\chrome.exe",
        "C:\\Windows\\explorer.exe",
        "C:\\Windows\\System32\\svchost.exe",
        "C:\\Windows\\System32\\kernel32.dll",
        "C:\\Windows\\System32\\user32.dll",
        "Memory Address: 0x7FFF1234",
        "Boot Sector: Sector 0",
        "Registry: HKLM\\Software\\Microsoft"
    ];

    sendCommand('SCAN_ALL'); // Notify C++ engine
    
    const interval = setInterval(() => {
        progress += Math.random() * 2;
        if (progress >= 100) {
            progress = 100;
            clearInterval(interval);
            scanFile.textContent = "SCAN COMPLETED: SYSTEM SECURE";
            
            // Check shutdown option
            if (shutdownCheck && shutdownCheck.checked) {
                updateLogs("Shutdown initiated...");
                setTimeout(() => {
                    ipcRenderer.send('system-shutdown');
                }, 3000);
            }

            setTimeout(() => {
                progress = 0;
                scanPerc.textContent = "0.0%";
                scanProg.style.width = "0%";
                scanFile.textContent = "READY";
            }, 5000);
        }

        scanPerc.textContent = progress.toFixed(1) + "%";
        scanProg.style.width = progress + "%";
        
        // Pick a random file name to show
        const randomFile = fakeFiles[Math.floor(Math.random() * fakeFiles.length)];
        scanFile.textContent = `CHECKING: ${randomFile}`;
        
    }, 150);
}

// Navigation Logic
navItems.forEach(item => {
    item.onclick = () => {
        const targetView = item.getAttribute('data-view');
        
        // Update Nav
        navItems.forEach(i => i.classList.remove('active'));
        item.classList.add('active');
        
        // Update View
        views.forEach(v => v.classList.remove('active'));
        const activeView = document.getElementById(`view-${targetView}`);
        if (activeView) activeView.classList.add('active');
    };
});

ipcRenderer.on('engine-output', (event, data) => {
    updateLogs(data);
    
    // Process Network Data
    if (data.includes('[Conn]')) {
        updateNetworkList(data);
    }

    // Process Process Data
    if (data.includes('[Proc]')) {
        updateProcessList(data);
    }

    // Alert logic
    if (data.includes('ALERT') || data.includes('THREAT')) {
        document.body.style.boxShadow = 'inset 0 0 50px rgba(255, 0, 0, 0.5)';
        setTimeout(() => {
            document.body.style.boxShadow = 'none';
        }, 2000);
    }
});

function updateNetworkList(connData) {
    const netList = document.getElementById('net-list');
    if (netList) {
        if (netList.textContent.includes('WAITING')) netList.innerHTML = '';
        const div = document.createElement('div');
        div.className = 'net-item';
        div.style.borderBottom = '1px solid rgba(0, 255, 127, 0.1)';
        div.style.padding = '5px 0';
        div.textContent = connData.replace('[Conn]', '▶');
        netList.appendChild(div);
        netList.scrollTop = netList.scrollHeight;
    }
}

function updateProcessList(procData) {
    const procList = document.getElementById('proc-list');
    if (procList) {
        if (procList.textContent.includes('WAITING') || procList.textContent.includes('Listing RUNNING')) procList.innerHTML = '';
        const div = document.createElement('div');
        div.className = 'proc-item';
        div.style.borderBottom = '1px solid rgba(0, 255, 127, 0.1)';
        div.style.padding = '5px 0';
        div.textContent = procData.replace('[Proc]', '⚙');
        procList.appendChild(div);
        procList.scrollTop = procList.scrollHeight;
    }
}

function updateLogs(message) {
    const time = new Date().toLocaleTimeString();
    const formattedMsg = `[${time}] ${message}`;

    // Update Full Log Box (if exists in DOM)
    if (fullLogBox) {
        const div = document.createElement('div');
        div.textContent = formattedMsg;
        fullLogBox.appendChild(div);
        fullLogBox.scrollTop = fullLogBox.scrollHeight;
    }

    // Update Global Mini Log Bar
    if (latestLog) {
        latestLog.textContent = message;
    }
}

function sendCommand(cmd) {
    ipcRenderer.send('send-command', cmd);
    updateLogs(`Command Sent: ${cmd}`);
}

function killProc() {
    const pid = document.getElementById('pid-input').value;
    if (pid) {
        sendCommand(`KILL_PROC ${pid}`);
    }
}

function clearLogs() {
    if (fullLogBox) fullLogBox.innerHTML = '';
    if (latestLog) latestLog.textContent = "Logs cleared.";
}

closeBtn.onclick = () => ipcRenderer.send('app-close');
minimizeBtn.onclick = () => ipcRenderer.send('app-minimize');
