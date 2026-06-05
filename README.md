# Cyphern0x-SafeGuard-# CypherN0x SafeGuard

Kısa Açıklama
------------
CypherN0x SafeGuard, uç nokta ve sistem güvenliği amaçlı bir uygulama olarak tasarlanmış bir projedir. Kullanıcı arayüzü üzerinden tam/hızlı/heuristic taramalar başlatma, süreçleri izleme ve sonlandırma, ağ trafiğini kontrol etme, güvenlik duvarı ve karantina yönetimi, şifreleme desteği ve küresel ağ durumunu izleme gibi özellikleri hedefler. Proje, performans için native C++ modülleri, sunucu/servis mantığı için C# bileşenleri ve web arayüzü için JavaScript/HTML/CSS içerir.

Dil Dağılımı (repo ölçümü)
- JavaScript — %35.5  
- C# — %19.7  
- C++ — %16.2  
- HTML — %16.1  
- CSS — %12.5

Ana Özellikler
-------------
- Hızlı, Tam ve Heuristik tarama modları  
- Sistem süreçleri izleme ve süreçleri sonlandırma (terminate)  
- Ağ trafiği ve aktif ağ düğümleri hakkında görünüm ve kontrol  
- Güvenlik duvarı / firewall entegrasyonu ve karantina yönetimi  
- Şifreleme/kriptografi destekleri (native modüllerle)  
- Olay günlükleri (logs) ve sistem aktivite monitörü  
- Basit web tabanlı kontrol paneli (dashboard)

Proje Mimarisi (Genel)
----------------------
1. Ön Yüz (Frontend): HTML/CSS/JavaScript — kullanıcı arayüzü, yerel kontroller ve görselleştirme.  
2. Sunucu/Servis Katmanı: C# (.NET) — API'ler, görev zamanlama, veri yönetimi, yetkilendirme.  
3. Native Katman: C++ — performans-kritik kod (örn. kriptografi, düşük seviyeli süreç/işlem kontrolü).  
Bu ayrım, UI ile kullanıcı etkileşimini birbirinden ayırır ve kritik işlemleri yüksek performanslı native koda bırakır.

Kurulum (örnek, klasör adları repoya göre değişebilir)
-----------------------------------------------------
1. Depoyu klonla:
   git clone https://github.com/CypherN0x/Cyphern0x-SafeGuard-.git
   cd Cyphern0x-SafeGuard-
2. Frontend (örnek):
   cd frontend
   npm install
   npm run dev
3. Backend (örnek, C#):
   cd backend
   dotnet restore
   dotnet build
   dotnet run --project ./ProjectName/ProjectName.csproj
4. C++ (örnek):
   cd cpp
   mkdir build && cd build
   cmake ..
   make

Çalıştırma ve Kullanım
----------------------
- Web arayüzünü aç: http://localhost:3000 ( veya projede belirtilen port)  
- Taramalar: UI üzerinden "Hızlı", "Tam" veya "Heuristik" tarama başlatın.  
- Süreç yönetimi: "Süreçleri Tara" ile şüpheli süreçleri tespit edip gerekirse sonlandırın.  
- Kayıtlar (logs): Olay geçmişini denetleyin, son uyarıları ve aktiviteleri inceleyin.  
- Karantina: Şüpheli dosyaları karantinaya alıp inceleyin veya temizleyin.

Antivirüs/Endpoint Korumasının Ne Yaptığı (kısa)
------------------------------------------------
- Tespit: İmza tabanlı (bilinen tehditler), heuristik (şüpheli davranış kalıpları) ve davranışsal analiz ile kötü amaçlı yazılımlar tespit edilir.  
- Önleme: Gerçek zamanlı tarama, dosya/işlem erişim kontrolü ve ağ trafiği kuralları ile saldırılar engellenir.  
- Müdahale: Karantina, süreç sonlandırma, temizleme/geri alma ve olay raporlaması.  
- Güncelleme/İtibar: İmza veritabanı ve itibar mekanizmaları ile yeni tehditlere karşı korunma sağlanır.

SmartScreen / Benzeri Uyarıların Nedenleri (kısa)
------------------------------------------------
- Uygulama yeni veya düşük itibar sahibi olabilir (yeterli indirme/kurulum geçmişi yok).  
- İmzalanmamış ya da geçersiz (expired) kod imzası bulunması.  
- Kurulum paketinin veya ikilinin şüpheli paketleme/obfuscation içermesi.  
- Heuristik inceleme sonucu şüpheli davranış tespit edilmesi.  
- Yanlış pozitifler: temiz yazılımlar da bazen işaretlenebilir.

SmartScreen/AV Sorunlarını Azaltma Önerileri
-------------------------------------------
- Uygulamayı geçerli bir code-signing sertifikasıyla imzala (tercihen EV).  
- Güvenilir dağıtım kanalları kullan (ör. GitHub Releases, resmi site, mağazalar).  
- Sürüm, yayıncı bilgileri ve SHA256 checksum gibi doğrulayıcı bilgiler sağla.  
- Microsoft ve büyük AV üreticilerine false-positive başvurusu gönder.

Güvenlik ve Sorumluluk
---------------------
- Gizli anahtarları/şifreleri repoya koymayın (.env dosyalarını .gitignore ile hariç tutun).  
- Bağımlılıkları düzenli olarak güncelleyin ve tarayın.  
- Native kodda bellek güvenliği ve güvenli kriptografi uygulamalarına dikkat edin.

Katkıda Bulunma
---------------
1. Fork yapın.  
2. Yeni bir branch açın: git checkout -b feature/özellik-ismi  
3. Değişiklikleri commit edip pushlayın.  
4. Pull request oluşturun.
Lisans ve İletişim
------------------
- Depoda lisans belirtilmemiş — bir açık lisans (MIT veya Apache-2.0 gibi) eklemeniz önerilir.  
- Sorumlu/sağlayıcı: CypherN0x — sorun raporları ve katkılar için GitHub Issues kullanın.
# CypherN0x SafeGuard
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Short Description
-----------------
CypherN0x SafeGuard is designed as a system/endpoint security and monitoring project. It aims to provide UI-driven full/quick/heuristic scans, process monitoring and termination, network traffic control, firewall and quarantine management, encryption support and global network monitoring. The project includes native C++ modules for performance-critical tasks, C# components for server/service logic, and a web UI built with JavaScript/HTML/CSS.

Language Composition (repo)
- JavaScript — 35.5%  
- C# — 19.7%  
- C++ — 16.2%  
- HTML — 16.1%  
- CSS — 12.5%

Key Features
------------
- Quick, Full and Heuristic scan modes  
- Monitor and terminate system processes  
- Network traffic monitoring and control, active node view  
- Firewall integration and quarantine management  
- Encryption/crypto support via native modules  
- Event logging and system activity monitor  
- Web-based control dashboard

Architecture (High-level)
-------------------------
1. Frontend: HTML/CSS/JavaScript — UI, local controls and visualization.  
2. Server/Service Layer: C# (.NET) — APIs, scheduling, data management, auth.  
3. Native Layer: C++ — performance-sensitive operations (e.g. crypto, low-level process control).  
Separation improves security and performance by isolating critical tasks.

Installation (example — folder names may vary)
----------------------------------------------
1. Clone:
   git clone https://github.com/CypherN0x/Cyphern0x-SafeGuard-.git
   cd Cyphern0x-SafeGuard-
2. Frontend (example):
   cd frontend
   npm install
   npm run dev
3. Backend (example, C#):
   cd backend
   dotnet restore
   dotnet build
   dotnet run --project ./ProjectName/ProjectName.csproj
4. C++ components (example):
   cd cpp
   mkdir build && cd build
   cmake ..
   make

Running & Usage
---------------
- Open the web UI at http://localhost:3000 (or configured port).  
- Start scans from the UI: Quick, Full or Heuristic.  
- Manage processes: scan and optionally terminate suspicious processes.  
- Check logs and system activity for alerts and recent events.  
- Use quarantine to isolate suspicious files for analysis.

What an Antivirus / Endpoint Protection Does (brief)
----------------------------------------------------
- Detection: signature-based (known threats), heuristic (suspicious patterns) and behavioral analysis.  
- Prevention: real-time scanning, file/process access control, network rules.  
- Response: quarantine, terminate processes, clean/remove infected files, event reporting.  
- Updates & Reputation: signature updates and reputation checks to reduce false positives.

Why SmartScreen / Similar Warnings Appear (brief)
------------------------------------------------
- Low application reputation or too new — insufficient download/install history.  
- Unsigned or invalid code signing certificate.  
- Suspicious packaging or obfuscation in the installer/binary.  
- Heuristic detection of risky behavior.  
- False positives can also occur.

How to Reduce SmartScreen/AV Warnings
-------------------------------------
- Sign binaries and installers with a valid code-signing certificate (EV recommended).  
- Use trusted distribution channels (GitHub Releases, official sites, app stores).  
- Provide publisher info, version, and SHA256 checksums.  
- Submit false-positive reports to Microsoft and major AV vendors.

Security Best Practices
-----------------------
- Do not commit secrets (.env) to the repository.  
- Keep dependencies up to date and scan for vulnerabilities.  
- Ensure memory safety and use vetted crypto libraries in native code.

Contributing
------------
1. Fork the repo.  
2. Create a branch: git checkout -b feature/name  
3. Implement changes, commit and push.  
4. Open a Pull Request.

License & Contact
-----------------
- No license specified in the repository; add an open-source license (MIT, Apache-2.0, etc.) to clarify legal terms.  
- Owner / Maintainer: CypherN0x — use GitHub Issues for bug reports and contributions.
