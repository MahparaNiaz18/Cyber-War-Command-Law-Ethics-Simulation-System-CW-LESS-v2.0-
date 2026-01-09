#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_THREATS = 100;
const int MAX_CASES = 100;

struct Threat {
    int id;
    string type;
    int severity;
};

struct CaseFile {
    int caseID;
    string threatType;
    string law;
    string verdict;
    int ethicalScore;
};

Threat threats[MAX_THREATS];
CaseFile cases[MAX_CASES];

int threatCount = 0;
int caseCount = 0; 
void header()
 {
    cout << "=================================================\n";
    cout << "   CYBER WAR COMMAND, LAW & ETHICS SIMULATION    \n";
    cout << "                  CW-LESS v2.0                  \n";
    cout << "=================================================\n\n";
}

void pauseScreen() {
    cout << "\nPress ENTER to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}
string severityLabel(int s) {
    if (s == 1) return "LOW";
    if (s == 2) return "MEDIUM";
    return "HIGH";
}

string mapLaw(const string& threat) {
    if (threat == "DDoS") return "Cyber Crime Act Sec-37";
    if (threat == "Ransomware") return "Electronic Fraud Law";
    if (threat == "Phishing") return "Identity Theft Act";
    if (threat == "Insider") return "Internal Security Policy";
    return "General Cyber Law";
}

int ethicalScoreCalc(int severity) {
    if (severity == 1) return 90;
    if (severity == 2) return 70;
    return 50;
};

void saveThreats() {
    ofstream file("threats.txt");
    for (int i = 0; i < threatCount; i++) {
        file << threats[i].id << " "
             << threats[i].type << " "
             << threats[i].severity << endl;
    }
    file.close();
}

void loadThreats() {
    ifstream file("threats.txt");
    while (file >> threats[threatCount].id
                >> threats[threatCount].type
                >> threats[threatCount].severity) {
        threatCount++;
    }
    file.close();
}

void addThreat() {
    header();

    if (threatCount >= MAX_THREATS) {
        cout << "Threat storage full!\n";
        pauseScreen();
        return;
    }

    threats[threatCount].id = threatCount + 1;

    cout << "[ THREAT INPUT PANEL ]\n\n";
    cout << "Threat Type (DDoS/Ransomware/Phishing/Insider/Malware): ";
    cin >> threats[threatCount].type;

    cout << "Severity (1-Low, 2-Medium, 3-High): ";
    cin >> threats[threatCount].severity;
    threatCount++;
    saveThreats();
    cout << "\nThreat registered successfully.\n";
    pauseScreen();
}

void viewThreats() {
    header();

    cout << "[ THREAT MONITORING DASHBOARD ]\n\n";
    cout << left << setw(5) << "ID"
         << setw(15) << "TYPE"
         << setw(10) << "SEVERITY" << endl;
    cout << "---------------------------------------------\n";
    for (int i = 0; i < threatCount; i++) {
        cout << setw(5) << threats[i].id
             << setw(15) << threats[i].type
             << setw(10) << severityLabel(threats[i].severity) << endl;
    }

    pauseScreen();
}

void defenseCommand() {
    header();
    cout << "[ DEFENSE COMMAND CENTER ]\n\n";
    
    for (int i = 0; i < threatCount; i++) {
        cout << "Threat " << threats[i].id << " (" << threats[i].type << ") -> ";
        if (threats[i].severity == 3)
            cout << "[EMERGENCY] NATIONAL CYBER RESPONSE\n";
        else if (threats[i].severity == 2)
            cout << "[WARNING] DEPLOY IDS & PATCHES\n";
        else
            cout << "[INFO] LOG & MONITOR\n";
    }

    pauseScreen();
}

void lawEthicsModule() {
    header();

    cout << "[ CYBER LAW & ETHICS MODULE ]\n\n";

    for (int i = 0; i < threatCount; i++) {
        cases[caseCount].caseID = 1000 + caseCount + 1;
        cases[caseCount].threatType = threats[i].type;
        cases[caseCount].law = mapLaw(threats[i].type);
        cases[caseCount].ethicalScore = ethicalScoreCalc(threats[i].severity);

        if (threats[i].severity == 3)
            cases[caseCount].verdict = "Arrest Simulation";
        else if (threats[i].severity == 2)
            cases[caseCount].verdict = "Fine Issued";
        else
            cases[caseCount].verdict = "Warning Issued";

        cout << "Case ID: " << cases[caseCount].caseID << endl;
        cout << "Threat: " << cases[caseCount].threatType << endl;
        cout << "Law Applied: " << cases[caseCount].law << endl;
        cout << "Verdict: " << cases[caseCount].verdict << endl;
        cout << "Ethical Score: " << cases[caseCount].ethicalScore << endl;
        cout << "--------------------------------------\n";

        caseCount++;
    }

    pauseScreen();
}

void analyticsDashboard() {
    header();

    int ddos = 0, ransom = 0, phishing = 0, insider = 0, malware = 0;

    for (int i = 0; i < threatCount; i++) {
        if (threats[i].type == "DDoS") ddos++;
        else if (threats[i].type == "Ransomware") ransom++;
        else if (threats[i].type == "Phishing") phishing++;
        else if (threats[i].type == "Insider") insider++;
        else malware++;
    }

    cout << "[ INCIDENT ANALYTICS DASHBOARD ]\n\n";
    cout << "DDoS       "; for (int i = 0; i < ddos; i++) cout << "#"; cout << " " << ddos << endl;
    cout << "Ransomware "; for (int i = 0; i < ransom; i++) cout << "#"; cout << " " << ransom << endl;
    cout << "Phishing   "; for (int i = 0; i < phishing; i++) cout << "#"; cout << " " << phishing << endl;
    cout << "Insider    "; for (int i = 0; i < insider; i++) cout << "#"; cout << " " << insider << endl;
    cout << "Malware    "; for (int i = 0; i < malware; i++) cout << "#"; cout << " " << malware << endl;

    pauseScreen();
}

int main() {
    loadThreats();
    int choice;
    do {
        header();

        cout << "[ MAIN CONTROL PANEL ]\n\n";
        cout << "1. Add Threat\n";
        cout << "2. View Threats\n";
        cout << "3. Defense Command\n";
        cout << "4. Law & Ethics Module\n";
        cout << "5. Analytics Dashboard\n";
        cout << "0. Exit System\n\n";
        cout << "Select Option: ";
        cin >> choice;

        switch (choice) {
            case 1: addThreat(); break;
            case 2: viewThreats(); break;
            case 3: defenseCommand(); break;
            case 4: lawEthicsModule(); break;
            case 5: analyticsDashboard(); break;
            case 0: cout << "\nSystem Shutdown...\n"; break;
            default: cout << "Invalid option!\n"; pauseScreen();
        }
    } while (choice != 0);

    return 0;
}

