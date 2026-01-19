# Pac-Man

Dieses Projekt ist meine Implementierung des Arcade-Klassikers Pac-Man, entwickelt in C++ unter Verwendung der SFML (Simple and Fast Multimedia Library). Das Ziel war es, die grundlegenden Mechaniken eines Labyrinth-Spiels sowie die Logik der Gegner-KI von Grund auf zu programmieren.

---

## 🕹️ Das Spiel

### Gameplay

Der Spieler steuert Pac-Man durch ein Labyrinth mit dem Ziel, alle Punkte (Pellets) zu fressen, während er vier Geistern ausweicht. Die Kern-Features umfassen:

- **KI-Verhalten:** Jeder Geist (Blinky, Pinky, Inky und Clyde) besitzt ein individuelles Verfolgungsmuster.

- **Power-Pellets:** Das Einsammeln großer Punkte macht die Geister kurzzeitig verwundbar und ermöglicht es Pac-Man, sie zu fressen.

- **Level-Struktur:** Ein klassisches Kachel-basiertes Labyrinth mit Teleport-Tunneln an den Seiten.

---

### Steuerung

- **Pac-Man bewegen:** W (Hoch), A (Links), S (Unter), D (Rechts) oder die Pfeiltasten.

---

## 🚀 Download & Website

Du möchtest das Spiel direkt ausprobieren, ohne es selbst zu kompilieren? Die ausführbare Datei (.exe / App) sowie weitere Informationen findest du auf meiner Website:

[Website]: https://jjmercado.github.io/portfolioSite/games/pac-man
🔗 Hier geht's zur [Website] und zum Download

---

## 🛠️ Build-Anleitung (Lokal bauen)

Dieses Projekt verwendet CMake, um den Build-Prozess plattformübergreifend zu verwalten.

### Voraussetzungen

- Ein C++17 fähiger Compiler (GCC, Clang oder MSVC).
- CMake (Version 3.10 oder höher).
- SFML 2.6.2 (Update auf die aktuellste SFML-Version folgt, sobald Zeit dafür ist).

### Schritt-für-Schritt

1. **Repository klonen**:

```bash
git clone https://github.com/jjmercado/Pac-Man
cd pac-man
```

2. **Build-Verzeichnis erstellen:**

```bash
mkdir build
cd build
```

3. **CMake konfigurieren:**

```bash
cmake ..
```

4. **CMake konfigurieren:**

```bash
cmake --build .
```

5. **Spiel starten:**
Nach dem Build findest du die ausführbare Datei im build-Ordner (oder unter build/Debug / build/Release bei Windows).

---

## 📜 Lizenzhinweis & Urheberrecht

Der Code dieser Website steht unter der **MIT Lizenz**.

- **Code:** Der Quellcode dieser Website steht unter der MIT-Lizenz. Du darfst ihn gerne studieren und für eigene Projekte verwenden.

- **Assets & Inhalt:** Alle Bilder, Videos und Texte sind mein geistiges Eigentum (Copyright) und stehen **nicht** unter der MIT-Lizenz. Eine Kommerzielle Verwendung dieser Assets ist ohne ausdrückliche Genehmigung nicht gestattet.