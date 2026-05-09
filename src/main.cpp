// ==========================================
// NETGROK v0.2 FOR TERMUX
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

    system("clear");

    cout << "=== WIFI INFORMATION ===\n\n";

    system("termux-wifi-connectioninfo");

    cout << "\n=== DEVICE IP ===\n\n";

    system("termux-wifi-connectioninfo");

    waitEnter();
}

// ==========================================
// PING HOST
// ==========================================

void pingHost() {

    string host;

    system("clear");

    cout << "=== PING HOST ===\n\n";

    cout << "Enter host/IP: ";
    cin >> host;

    string command = "ping -c 4 " + host;

    system(command.c_str());

    waitEnter();
}

// ==========================================
// ACTIVE CONNECTIONS
// ==========================================

void activeConnections() {

    system("clear");

    cout << "=== ACTIVE CONNECTIONS ===\n\n";

    system("ss -tun 2>/dev/null");

    waitEnter();
}

// ==========================================
// SYSTEM MONITOR
// ==========================================

void systemMonitor() {

    system("clear");

    cout << "=== SYSTEM MONITOR ===\n\n";

    system("top -n 1 | head -20");

    waitEnter();
}

// ==========================================
// BATTERY INFO
// ==========================================

void batteryInfo() {

    system("clear");

    cout << "=== BATTERY INFORMATION ===\n\n";

    system("termux-battery-status");

    waitEnter();
}

// ==========================================
// WIFI INFO
// ==========================================

void wifiInfo() {

    system("clear");

    cout << "=== WIFI STATUS ===\n\n";

    system("termux-wifi-connectioninfo");

    waitEnter();
}

// ==========================================
// PUBLIC IP
// ==========================================

void publicIP() {

    system("clear");

    cout << "=== PUBLIC IP ===\n\n";

    system("curl ifconfig.me");

    cout << endl;

    waitEnter();
}

// ==========================================
// DEVICE INFO
// ==========================================

void deviceInfo() {

    system("clear");

    cout << "=== DEVICE INFORMATION ===\n\n";

    system("getprop ro.product.model");

    cout << "\n=== ANDROID VERSION ===\n\n";

    system("getprop ro.build.version.release");

    waitEnter();
}

// ==========================================
// MAIN MENU
// ==========================================

int main() {

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
        cout << "[0] Exit\n\n";

        cout << "Select option: ";
        cin >> option;

        switch(option) {

            case 1:
                networkInfo();
                break;

            case 2:
                pingHost();
                break;

            case 3:
                activeConnections();
                break;

            case 4:
                systemMonitor();
                break;

            case 5:
                batteryInfo();
                break;

            case 6:
                wifiInfo();
                break;

            case 7:
                publicIP();
                break;

            case 8:
                deviceInfo();
                break;

            case 0:
                system("clear");
                cout << "Goodbye.\n";
                return 0;

            default:
                cout << "\nInvalid option.\n";
                sleep(1);
        }
    }

    return 0;
}

