using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;

namespace SafeGuardUI;

public partial class Form1 : Form
{
    private Process _engineProcess;
    private Panel _statusPanel;
    private Label _statusLabel;
    private RichTextBox _logBox;
    private Label _titleLabel;
    private NotifyIcon _trayIcon;
    private ContextMenuStrip _trayMenu;

    public Form1()
    {
        InitializeComponent();
        SetupMcAfeeTheme();
        SetupTrayIcon();
        StartEngine();
    }

    private void SetupTrayIcon()
    {
        _trayMenu = new ContextMenuStrip();
        _trayMenu.Items.Add("Göster", null, (s, e) => { this.Show(); this.WindowState = FormWindowState.Normal; });
        _trayMenu.Items.Add("Taramayı Durdur", null, (s, e) => { Application.Exit(); });

        _trayIcon = new NotifyIcon
        {
            Text = "SafeGuard Endpoint Security",
            Icon = SystemIcons.Shield, // Profesyonel kalkan ikonu
            ContextMenuStrip = _trayMenu,
            Visible = true
        };

        _trayIcon.DoubleClick += (s, e) => { this.Show(); this.WindowState = FormWindowState.Normal; };
    }

    private void SetupMcAfeeTheme()
    {
        // Global Style Settings - GX Cyberpunk Style
        this.Text = "[ CYPHERN0X SECURITY GX ]";
        this.Size = new Size(1150, 780);
        this.BackColor = Color.FromArgb(18, 22, 28); // Deeper dark background
        this.FormBorderStyle = FormBorderStyle.FixedSingle;
        this.MaximizeBox = false;

        // Colors from your image
        Color neonGreen = Color.FromArgb(0, 255, 170);
        Color cardBg = Color.FromArgb(30, 38, 48);
        Color sideNavBg = Color.FromArgb(22, 27, 34);
        Color headerText = Color.FromArgb(200, 210, 220);

        // Sidebar - Visual Match to Image
        Panel sideNav = new Panel
        {
            Size = new Size(80, 780),
            BackColor = sideNavBg,
            Dock = DockStyle.Left
        };
        this.Controls.Add(sideNav);

        string[] menuItems = { "🏠", "🔍", "📂", "🌐", "📋", "⚙️" };
        string[] menuLabels = { "Home", "Scans", "Files", "Net", "Logs", "Set" };
        for (int i = 0; i < menuItems.Length; i++)
        {
            Label icon = new Label
            {
                Text = menuItems[i],
                ForeColor = (i == 0) ? neonGreen : Color.Gray,
                Font = new Font("Segoe UI", 16),
                Size = new Size(80, 40),
                Location = new Point(0, 100 + (i * 80)),
                TextAlign = ContentAlignment.MiddleCenter
            };
            Label text = new Label
            {
                Text = menuLabels[i],
                ForeColor = (i == 0) ? neonGreen : Color.Gray,
                Font = new Font("Segoe UI", 8),
                Size = new Size(80, 20),
                Location = new Point(0, 140 + (i * 80)),
                TextAlign = ContentAlignment.MiddleCenter
            };
            sideNav.Controls.Add(icon);
            sideNav.Controls.Add(text);
        }

        // Main Title Header - [ CYPHERN0X SECURITY ]
        Label mainTitle = new Label
        {
            Text = "[ CYPHERN0X SECURITY ]",
            ForeColor = headerText,
            Font = new Font("Consolas", 36, FontStyle.Bold),
            Location = new Point(110, 25),
            AutoSize = true
        };
        this.Controls.Add(mainTitle);

        // Status Indicators
        Label statusBadge = new Label
        {
            Text = "> STATUS: OPTIMAL < PROTECTION: ACTIVE <",
            ForeColor = neonGreen,
            BackColor = Color.FromArgb(40, 50, 60),
            Font = new Font("Segoe UI", 11, FontStyle.Bold),
            Location = new Point(115, 95),
            AutoSize = true,
            Padding = new Padding(10, 5, 10, 5)
        };
        this.Controls.Add(statusBadge);

        Label systemEncrypted = new Label
        {
            Text = "[ 🔒 SYSTEM ENCRYPTED ]",
            ForeColor = Color.Yellow,
            Font = new Font("Segoe UI", 11, FontStyle.Bold),
            Location = new Point(480, 95),
            AutoSize = true,
            Padding = new Padding(10, 5, 10, 5)
        };
        this.Controls.Add(systemEncrypted);

        // --- Dashboard Grid (3x2) ---
        int cardW = 320;
        int cardH = 200;
        int gap = 20;
        int startX = 115;
        int startY = 160;

        // Card 1: System Scan
        CreateGXCard("🔍 SYSTEM SCAN", new Point(startX, startY), cardW, cardH, "EXECUTE");
        
        // Card 2: Real-time Guard (The Heart)
        CreateGXCard("🛡️ REAL-TIME GUARD", new Point(startX + cardW + gap, startY), cardW, cardH, "LIVE");

        // Card 3: Quarantine Manager
        CreateGXCard("📦 QUARANTINE MANAGER", new Point(startX + (cardW + gap) * 2, startY), cardW, cardH, "VIEW");

        // Card 4: Firewall Settings
        CreateGXCard("🔥 FIREWALL SETTINGS", new Point(startX, startY + cardH + gap), cardW, cardH, "ACTIVE");

        // Card 5: VPN & Identity
        CreateGXCard("🔐 VPN & IDENTITY", new Point(startX + cardW + gap, startY + cardH + gap), cardW, cardH, "SECURE");

        // Card 6: Updates & License
        CreateGXCard("🔄 UPDATES & LICENSE", new Point(startX + (cardW + gap) * 2, startY + cardH + gap), cardW, cardH, "CHECK");

        // Logs Panel (New Row or Overlay)
        _logBox = new RichTextBox
        {
            Location = new Point(startX, startY + (cardH + gap) * 2),
            Size = new Size((cardW * 3) + (gap * 2), 100),
            BackColor = Color.Black,
            ForeColor = neonGreen,
            Font = new Font("Consolas", 8),
            ReadOnly = true,
            BorderStyle = BorderStyle.None
        };
        this.Controls.Add(_logBox);

        // Footer Info
        Label footerInfo = new Label
        {
            Text = "LAST SCAN RESULT: CLEAN | THREAT DEFINITIONS: VER. 1.392 (UPDATED) | DEVELOPED BY CYPHERN0X",
            ForeColor = Color.FromArgb(100, 110, 120),
            Font = new Font("Segoe UI", 9),
            Location = new Point(115, 620),
            AutoSize = true
        };
        this.Controls.Add(footerInfo);
    }

    private void CreateGXCard(string title, Point loc, int w, int h, string btnText)
    {
        Panel p = new Panel { Location = loc, Size = new Size(w, h), BackColor = Color.FromArgb(30, 38, 48) };
        Label t = new Label { Text = title, ForeColor = Color.FromArgb(0, 255, 170), Font = new Font("Segoe UI", 10, FontStyle.Bold), Location = new Point(10, 10), AutoSize = true };
        
        Button b = new Button
        {
            Text = btnText,
            Size = new Size(110, 35),
            Location = new Point(w - 120, h - 45),
            FlatStyle = FlatStyle.Flat,
            ForeColor = Color.Black,
            BackColor = Color.FromArgb(0, 255, 170),
            Font = new Font("Segoe UI", 9, FontStyle.Bold)
        };
        b.FlatAppearance.BorderSize = 0;
        
        // --- Interactivity ---
        b.Click += (s, e) => {
            string cmd = "";
            if (title.Contains("SCAN")) cmd = "SCAN_ALL";
            else if (title.Contains("UPDATES")) cmd = "UPDATE_DB";
            else if (title.Contains("FIREWALL")) cmd = "FIREWALL_ON";
            else if (title.Contains("VPN")) cmd = "VPN_TOGGLE";
            
            if (!string.IsNullOrEmpty(cmd) && _engineProcess != null && !_engineProcess.HasExited) {
                _engineProcess.StandardInput.WriteLine(cmd);
                AppendLog($"[UI] Command Sent: {cmd}");
            }
        };

        p.Controls.Add(t);
        p.Controls.Add(b);
        this.Controls.Add(p);
    }

    private void CreateCard(string title, Point location, int width, int height, string buttonText)
    {
        Panel card = new Panel
        {
            Location = location,
            Size = new Size(width, height),
            BackColor = Color.FromArgb(40, 50, 60)
        };
        this.Controls.Add(card);

        Label titleLbl = new Label
        {
            Text = title,
            ForeColor = Color.FromArgb(0, 255, 170),
            Font = new Font("Segoe UI", 10, FontStyle.Bold),
            Location = new Point(10, 10),
            AutoSize = true
        };
        card.Controls.Add(titleLbl);

        Button btn = new Button
        {
            Text = buttonText,
            Size = new Size(100, 30),
            Location = new Point(width - 110, height - 40),
            FlatStyle = FlatStyle.Flat,
            ForeColor = Color.Black,
            BackColor = Color.FromArgb(0, 255, 170),
            Font = new Font("Segoe UI", 9, FontStyle.Bold)
        };
        btn.FlatAppearance.BorderSize = 0;
        card.Controls.Add(btn);
    }

    private Button CreateButton(string text, Point location)
    {
        return new Button
        {
            Text = text,
            Location = location,
            Size = new Size(140, 40),
            FlatStyle = FlatStyle.Flat,
            ForeColor = Color.White,
            BackColor = Color.FromArgb(60, 60, 60),
            Font = new Font("Segoe UI", 10, FontStyle.Bold),
            FlatAppearance = { BorderSize = 0 }
        };
    }

    private void StartEngine()
    {
        try
        {
            string baseDir = AppDomain.CurrentDomain.BaseDirectory;
            string rootPath = Path.GetFullPath(Path.Combine(baseDir, "..", "..", "..", ".."));
            string exePath = Path.Combine(rootPath, "SafeGuard.exe");

            if (!File.Exists(exePath))
            {
                exePath = Path.Combine(baseDir, "SafeGuard.exe");
            }

            AppendLog($"İzleme Dizini: {rootPath}");

            ProcessStartInfo psi = new ProcessStartInfo
            {
                FileName = exePath,
                WorkingDirectory = rootPath,
                UseShellExecute = false,
                RedirectStandardOutput = true,
                RedirectStandardInput = true, // Enable commands to C++
                CreateNoWindow = true
            };

            _engineProcess = new Process { StartInfo = psi };
            _engineProcess.OutputDataReceived += (s, e) =>
            {
                if (!string.IsNullOrEmpty(e.Data))
                {
                    this.Invoke(new Action(() => ProcessEngineOutput(e.Data)));
                }
            };

            _engineProcess.Start();
            _engineProcess.BeginOutputReadLine();
            AppendLog("Koruma Motoru başlatıldı.");
        }
        catch (Exception ex)
        {
            AppendLog("Hata: Motor başlatılamadı! " + ex.Message);
        }
    }

    private void ProcessEngineOutput(string line)
    {
        AppendLog(line);

        if (line.Contains("ALERT") || line.Contains("THREAT DETECTED"))
        {
            _statusPanel.BackColor = Color.FromArgb(192, 0, 0); // Dark Red
            _statusLabel.Text = "TEHDİT ALGILANDI!";
            
            _trayIcon.ShowBalloonTip(3000, "SafeGuard Tehdit Uyarısı", 
                "Sisteminizde zararlı bir dosya algılandı ve karantinaya alındı!", 
                ToolTipIcon.Error);
        }
    }

    protected override void OnResize(EventArgs e)
    {
        if (this.WindowState == FormWindowState.Minimized)
        {
            this.Hide();
            _trayIcon.ShowBalloonTip(2000, "SafeGuard", "Koruma arka planda devam ediyor.", ToolTipIcon.Info);
        }
        base.OnResize(e);
    }

    private void AppendLog(string message)
    {
        if (_logBox.InvokeRequired)
        {
            _logBox.Invoke(new Action(() => AppendLog(message)));
            return;
        }
        _logBox.AppendText($"[{DateTime.Now:HH:mm:ss}] {message}\n");
        _logBox.SelectionStart = _logBox.Text.Length;
        _logBox.ScrollToCaret();
    }

    protected override void OnFormClosing(FormClosingEventArgs e)
    {
        if (_engineProcess != null && !_engineProcess.HasExited)
        {
            _engineProcess.Kill();
        }
        base.OnFormClosing(e);
    }
}
