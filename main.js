const { app, BrowserWindow, ipcMain } = require('electron');
const path = require('path');
const { spawn } = require('child_process');

let mainWindow;
let engineProcess;

function createWindow() {
  mainWindow = new BrowserWindow({
    width: 1400,
    height: 900,
    minWidth: 1000,
    minHeight: 700,
    frame: false, 
    backgroundColor: '#004d26', // Bursaspor Dark Green
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false
    }
  });

  mainWindow.maximize(); // Start maximized for better view
  mainWindow.loadFile('index.html');
}

app.whenReady().then(() => {
  createWindow();
  startEngine();
});

function startEngine() {
  let exePath;
  
  // Try local directory first (for packager or dev)
  const localExe = path.join(__dirname, 'SafeGuard.exe');
  const parentExe = path.join(__dirname, '..', 'SafeGuard.exe');
  const resourcesExe = path.join(process.resourcesPath, 'SafeGuard.exe');

  if (require('fs').existsSync(localExe)) {
    exePath = localExe;
  } else if (require('fs').existsSync(resourcesExe)) {
    exePath = resourcesExe;
  } else {
    exePath = parentExe;
  }

  console.log(`Starting engine at: ${exePath}`);
  
  engineProcess = spawn(exePath, [], {
    cwd: path.dirname(exePath)
  });

  engineProcess.stdout.on('data', (data) => {
    if (mainWindow) {
      mainWindow.webContents.send('engine-output', data.toString());
    }
  });

  engineProcess.stderr.on('data', (data) => {
    console.error(`Engine Error: ${data}`);
  });
}

ipcMain.on('send-command', (event, command) => {
  if (engineProcess) {
    engineProcess.stdin.write(command + '\n');
  }
});

ipcMain.on('app-close', () => {
  if (engineProcess) engineProcess.kill();
  app.quit();
});

ipcMain.on('app-minimize', () => {
  mainWindow.minimize();
});

ipcMain.on('system-shutdown', () => {
  console.log("System shutdown command received.");
  const { exec } = require('child_process');
  // shutdown /s /t 0 -> /s is shutdown, /t 0 is immediate
  exec('shutdown /s /t 60', (err) => {
    if (err) console.error("Shutdown failed:", err);
  });
});
