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
// PORT SCANNER (RANGE)
// ==========================================

void portScanner() {
    system("clear");
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
        waitEnter();
        return;
    }

    cout << "\nScanning " << host << " from port " << startPort << " to " << endPort << "...\n";
    cout << "(This may take a while)\n\n";

    string command = "for p in $(seq " + to_string(startPort) + " " + to_string(endPort) + "); do (echo >/dev/tcp/" + host + "/$p) 2>/dev/null && echo \"[OPEN] Port $p\"; done";

    system(("bash -c '" + command + "'").c_str());

    cout << "\nScan completed.\n";
    waitEnter();
}

// ==========================================
// COMMON PORTS SCANNER (FAST)
// ==========================================

void commonPortsScanner() {
    system("clear");
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
    waitEnter();
}

// ==========================================
// GEO IP LOCATION
// ==========================================

void geoIP() {
    system("clear");
    string ip;
    
    cout << "=== GEO IP LOCATION ===\n\n";
    cout << "Enter IP or domain (e.g., 8.8.8.8 or google.com): ";
    cin >> ip;
    
    cout << "\nQuerying...\n\n";
    
    string cmd = "curl -s \"http://ip-api.com/json/" + ip + "\" | python3 -c \"\n\
import sys, json\ntry:\n    data = json.load(sys.stdin)\n    if data['status'] == 'success':\n        print('IP:', data['query'])\n        print('Country:', data['country'])\n        print('City:', data['city'])\n        print('Region:', data['regionName'])\n        print('Postal Code:', data.get('zip', 'N/A'))\n        print('ISP:', data['isp'])\n        print('Coordinates:', data['lat'], ',', data['lon'])\n        print('Timezone:', data['timezone'])\n    else:\n        print('Error:', data.get('message', 'Could not geolocate'))\nexcept:\n    print('Error processing response')\n\"";
    
    system(cmd.c_str());
    
    cout << "\n";
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
        cout << "[9] Port Scanner (range)\n";
        cout << "[10] Fast Scan (common ports)\n";
        cout << "[11] Geo IP Location\n";
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

            case 9:
                portScanner();
                break;

            case 10:
                commonPortsScanner();
                break;

            case 11:
                geoIP();
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
