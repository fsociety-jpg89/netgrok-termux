// ==========================================
// NETGROK v0.4 FULL EDITION FOR TERMUX
// Android Network Toolkit
// ==========================================

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <iomanip>

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
            FULL EDITION v0.4

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
// GEO IP LOCATION (con Python, formato bonito)
// ==========================================

void geoIP() {
    system("clear");
    string ip;
    cout << "=== GEO IP LOCATION ===\n\n";
    cout << "Enter IP or domain (e.g., 8.8.8.8): ";
    cin >> ip;
    cout << "\nQuerying...\n\n";
    string cmd = "curl -s \"http://ip-api.com/json/" + ip + "\" | python3 -c \"\n\
import sys, json\ntry:\n    data = json.load(sys.stdin)\n    if data['status'] == 'success':\n        print('IP:', data['query'])\n        print('Country:', data['country'])\n        print('City:', data['city'])\n        print('Region:', data['regionName'])\n        print('Postal Code:', data.get('zip', 'N/A'))\n        print('ISP:', data['isp'])\n        print('Coordinates:', data['lat'], ',', data['lon'])\n        print('Timezone:', data['timezone'])\n    else:\n        print('Error:', data.get('message', 'Could not geolocate'))\nexcept:\n    print('Error processing response')\n\"";
    system(cmd.c_str());
    cout << "\n";
    waitEnter();
}

// ==========================================
// WIFI NETWORK SCANNER (con Python, columnas bonitas)
// ==========================================

void wifiScanner() {
    system("clear");
    cout << "=== WIFI NETWORK SCANNER ===\n\n";
    cout << "Scanning for nearby WiFi networks...\n\n";
    string cmd = "termux-wifi-scaninfo 2>/dev/null | python3 -c \"\n\
import sys, json\ntry:\n    data = json.load(sys.stdin)\n    print('SSID'.ljust(25), 'BSSID (MAC)'.ljust(20), 'Channel'.ljust(8), 'Signal (dBm)'.ljust(12))\n    print('-' * 70)\n    for ap in data:\n        ssid = ap.get('ssid', 'Hidden')\n        bssid = ap.get('bssid', 'Unknown')\n        channel = ap.get('channel', 'N/A')\n        rssi = ap.get('rssi', 'N/A')\n        print(ssid[:24].ljust(25), bssid.ljust(20), str(channel).ljust(8), str(rssi).ljust(12))\nexcept:\n    print('Error: Could not scan networks.\\nMake sure termux-api is installed and location permission granted.')\n\"";
    system(cmd.c_str());
    cout << "\n";
    waitEnter();
}

// ==========================================
// TRACEROUTE
// ==========================================

void traceroute() {
    system("clear");
    string host;
    cout << "=== TRACEROUTE ===\n\n";
    cout << "Enter host/IP: ";
    cin >> host;
    cout << "\nTracing route to " << host << "...\n\n";
    system(("traceroute " + host + " 2>/dev/null || echo 'Install traceroute: pkg install traceroute'").c_str());
    waitEnter();
}

// ==========================================
// DNS LOOKUP
// ==========================================

void dnsLookup() {
    system("clear");
    string domain;
    cout << "=== DNS LOOKUP ===\n\n";
    cout << "Enter domain: ";
    cin >> domain;
    cout << "\nResolving " << domain << "...\n\n";
    system(("dig " + domain + " ANY +short 2>/dev/null || nslookup " + domain + " 2>/dev/null || echo 'Install dnsutils: pkg install dnsutils'").c_str());
    waitEnter();
}

// ==========================================
// ARP CACHE
// ==========================================

void arpCache() {
    system("clear");
    cout << "=== ARP CACHE (Local Network) ===\n\n";
    system("arp -a 2>/dev/null || ip neigh show 2>/dev/null || echo 'ARP not available'");
    waitEnter();
}

// ==========================================
// NETWORK STATISTICS
// ==========================================

void netStats() {
    system("clear");
    cout << "=== NETWORK STATISTICS ===\n\n";
    system("netstat -s 2>/dev/null || echo 'Install net-tools: pkg install net-tools'");
    waitEnter();
}

// ==========================================
// MAIN MENU (TWO COLUMNS ALIGNED)
// ==========================================

int main() {
    int option;

    while(true) {
        banner();

        // Dos columnas perfectamente alineadas con setw
        cout << left;
        cout << setw(35) << "[1]  Network Information"      << "[9]  Port Scanner (range)" << endl;
        cout << setw(35) << "[2]  Ping Host"                << "[10] Fast Scan (common ports)" << endl;
        cout << setw(35) << "[3]  Active Connections"       << "[11] Geo IP Location" << endl;
        cout << setw(35) << "[4]  System Monitor"           << "[12] WiFi Network Scanner" << endl;
        cout << setw(35) << "[5]  Battery Information"      << "[13] Traceroute" << endl;
        cout << setw(35) << "[6]  WiFi Information"         << "[14] DNS Lookup" << endl;
        cout << setw(35) << "[7]  Public IP"                << "[15] ARP Cache" << endl;
        cout << setw(35) << "[8]  Device Information"       << "[16] Network Statistics" << endl;
        cout << "\n[0]  Exit\n\n";

        cout << "Select option: ";
        cin >> option;

        switch(option) {
            case 1: networkInfo(); break;
            case 2: pingHost(); break;
            case 3: activeConnections(); break;
            case 4: systemMonitor(); break;
            case 5: batteryInfo(); break;
            case 6: wifiInfo(); break;
            case 7: publicIP(); break;
            case 8: deviceInfo(); break;
            case 9: portScanner(); break;
            case 10: commonPortsScanner(); break;
            case 11: geoIP(); break;
            case 12: wifiScanner(); break;
            case 13: traceroute(); break;
            case 14: dnsLookup(); break;
            case 15: arpCache(); break;
            case 16: netStats(); break;
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
    
