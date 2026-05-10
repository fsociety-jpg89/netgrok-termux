// ==========================================
// NETGROK v0.3 FOR TERMUX
// Android Network Toolkit
// ==========================================

#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

// ==========================================
// BANNER
// ==========================================

void banner() {

    system("clear");

    cout << R"(

███╗   ██╗███████╗████████╗ ██████╗ ██████╗  ██████╗ ██╗  ██╗
████╗  ██║██╔════╝╚══██╔══╝██╔════╝ ██╔══██╗██╔═══██╗██║ ██╔╝
██╔██╗ ██║█████╗     ██║   ██║  ███╗██████╔╝██║   ██║█████╔╝
██║╚██╗██║██╔══╝     ██║   ██║   ██║██╔══██╗██║   ██║██╔═██╗
██║ ╚████║███████╗   ██║   ╚██████╔╝██║  ██║╚██████╔╝██║  ██╗
╚═╝  ╚═══╝╚══════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝

        NETWORK TOOLKIT FOR TERMUX
               v0.3

)" << endl;
}

// ==========================================
// WAIT FUNCTION
// ==========================================

void waitEnter() {

    cout << "\nPress ENTER to continue...";
    cin.ignore();
    cin.get();
}

// ==========================================
// NETWORK INFO
// ==========================================

void networkInfo() {

    cout << "=== WIFI INFORMATION ===\n\n";

    system("termux-wifi-connectioninfo");

    cout << "\n=== DEVICE IP ===\n\n";

    system("termux-wifi-connectioninfo");
}

// ==========================================
// PING HOST
// ==========================================

void pingHost() {

    string host;

    cout << "=== PING HOST ===\n\n";

    cout << "Enter host/IP: ";
    cin >> host;

    string command = "ping -c 4 " + host;

    system(command.c_str());
}

// ==========================================
// ACTIVE CONNECTIONS
// ==========================================

void activeConnections() {

    cout << "=== ACTIVE CONNECTIONS ===\n\n";

    system("ss -tun 2>/dev/null");
}

// ==========================================
// SYSTEM MONITOR
// ==========================================

void systemMonitor() {

    cout << "=== SYSTEM MONITOR ===\n\n";

    system("top -n 1 | head -20");
}

// ==========================================
// BATTERY INFO
// ==========================================

void batteryInfo() {

    cout << "=== BATTERY INFORMATION ===\n\n";

    system("termux-battery-status");
}

// ==========================================
// WIFI INFO
// ==========================================

void wifiInfo() {

    cout << "=== WIFI STATUS ===\n\n";

    system("termux-wifi-connectioninfo");
}

// ==========================================
// PUBLIC IP
// ==========================================

void publicIP() {

    cout << "=== PUBLIC IP ===\n\n";

    system("curl ifconfig.me");

    cout << endl;
}

// ==========================================
// DEVICE INFO
// ==========================================

void deviceInfo() {

    cout << "=== DEVICE INFORMATION ===\n\n";

    system("getprop ro.product.model");

    cout << "\n=== ANDROID VERSION ===\n\n";

    system("getprop ro.build.version.release");
}

// ==========================================
// PORT SCANNER (RANGE)
// ==========================================

void portScanner() {
    string host;
    int startPort, endPort;

    cout << "=== PORT SCANNER (RANGE) ===\n\n";
    cout << "Target IP or hostname: ";
    cin >> host;

    cout << "Start port (1-65535): ";
    cin >> startPort;
    cout << "End port: ";
    cin >> endPort;

    if (startPort < 1 || endPort > 65535 || startPort > endPort) {
        cout << "\nInvalid port range.\n";
        return;
    }

    cout << "\nScanning " << host << " from port " << startPort << " to " << endPort << "...\n";
    cout << "(This may take a while)\n\n";

    // Usamos bash para probar conexión TCP con timeout de 1 segundo
    string command = "for p in $(seq " + to_string(startPort) + " " + to_string(endPort) + "); do (echo >/dev/tcp/" + host + "/$p) 2>/dev/null && echo \"[OPEN] Port $p\"; done";

    // Ejecutamos el comando dentro de bash
    system(("bash -c '" + command + "'").c_str());

    cout << "\nScan completed.\n";
}

// ==========================================
// COMMON PORTS SCANNER (FAST)
// ==========================================

void commonPortsScanner() {
    string host;
    cout << "=== FAST SCAN (COMMON PORTS) ===\n\nTarget: ";
    cin >> host;

    int commonPorts[] = {21,22,23,25,53,80,110,135,139,143,443,445,993,995,1723,3306,3389,5432,5900,8080};
    int size = sizeof(commonPorts)/sizeof(commonPorts[0]);

    cout << "\nScanning common ports...\n\n";
    for (int i = 0; i < size; i++) {
        string cmd = "bash -c \"(echo >/dev/tcp/" + host + "/" + to_string(commonPorts[i]) + ") 2>/dev/null && echo '[OPEN] Port " + to_string(commonPorts[i]) + "'\"";
        system(cmd.c_str());
    }
}

// ==========================================
// MAIN MENU
// ==========================================

int main() {
    void (*options[])() = {
        networkInfo, pingHost, activeConnections, systemMonitor,
        batteryInfo, wifiInfo, publicIP, deviceInfo, portScanner,
        commonPortsScanner
    };
    int option;

    while(true) {

        banner();

        cout << "[1] Network Information\n";
        cout << "[2] Ping Host\n";
        cout << "[3] Active Connections\n";
        cout << "[4] System Monitor\n";
        cout << "[5] Battery Information\n";
        cout << "[6] WiFi Information\n";
        cout << "[7] Public IP\n";
        cout << "[8] Device Information\n";
        cout << "[9] Port Scanner (range)\n";
        cout << "[10] Fast Scan (common ports)\n";
        cout << "[0] Exit\n\n";

        cout << "Select option: ";
        cin >> option;

        // Exit case
        if (option == 0) {
            system("clear");
            cout << "Goodbye.\n";
            return 0;
        }
        // Option selector
        if (option > 0 && option < 11) {
            system("clear");
            options[option - 1]();
            waitEnter();
        // Default case
        } else {
            cout << "\nInvalid option.\n";
            sleep(1);
        }
    }

    return 0;
}
