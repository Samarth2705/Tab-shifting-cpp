#include <iostream>
#include <string>
using namespace std;

// ---------- Structures ----------
struct Tab {
    string url;
    Tab* nextTab;
    Tab* prevTab;
};

struct History {
    string url;
    History* next;
};

// ---------- Global pointers ----------
Tab* firstTab = nullptr;
Tab* lastTab = nullptr;
Tab* activeTab = nullptr;
History* historyTop = nullptr;
int totalTabs = 0;

// ---------- HISTORY FUNCTIONS ----------
bool historyEmpty() {
    return historyTop == nullptr;
}

void addToHistory(const string& site) {
    History* node = new History{site, historyTop};
    historyTop = node;
    cout << "History updated → " << site << "\n";
}

string removeFromHistory() {
    if (historyEmpty()) return "No previous sites";
    History* temp = historyTop;
    string site = temp->url;
    historyTop = historyTop->next;
    delete temp;
    return site;
}

string showTopHistory() {
    return historyEmpty() ? "No previous sites" : historyTop->url;
}

// ---------- TAB FUNCTIONS ----------
void openTab(const string& site) {
    Tab* newTab = new Tab{site, nullptr, nullptr};

    if (!firstTab) {
        firstTab = lastTab = activeTab = newTab;
    } else {
        lastTab->nextTab = newTab;
        newTab->prevTab = lastTab;
        lastTab = newTab;
        activeTab = newTab;
    }

    totalTabs++;
    cout << " New tab opened: " << site << " | Total: " << totalTabs << "\n";
}

void closeTab() {
    if (!activeTab) {
        cout << "No tabs to close!\n";
        return;
    }

    string closed = activeTab->url;
    Tab* temp = activeTab;

    if (firstTab == lastTab) {
        firstTab = lastTab = activeTab = nullptr;
    } else if (activeTab == firstTab) {
        firstTab = firstTab->nextTab;
        firstTab->prevTab = nullptr;
        activeTab = firstTab;
    } else if (activeTab == lastTab) {
        lastTab = lastTab->prevTab;
        lastTab->nextTab = nullptr;
        activeTab = lastTab;
    } else {
        activeTab->prevTab->nextTab = activeTab->nextTab;
        activeTab->nextTab->prevTab = activeTab->prevTab;
        activeTab = activeTab->nextTab;
    }

    delete temp;
    totalTabs--;
    cout << " Closed: " << closed << " | Remaining: " << totalTabs << "\n";
}

void moveNextTab() {
    if (!activeTab || !activeTab->nextTab) {
        cout << "  No next tab available.\n";
        return;
    }
    activeTab = activeTab->nextTab;
    cout << "Switched to --> " << activeTab->url << "\n";
}

void movePrevTab() {
    if (!activeTab || !activeTab->prevTab) {
        cout << "<--  No previous tab available.\n";
        return;
    }
    activeTab = activeTab->prevTab;
    cout << "Switched to --> " << activeTab->url << "\n";
}

void showTabs() {
    if (!firstTab) {
        cout << "No tabs currently open.\n";
        return;
    }

    cout << "\n Tabs list:\n";
    Tab* temp = firstTab;
    int count = 1;
    while (temp) {
        cout << " " << count << ". " << temp->url;
        if (temp == activeTab) cout << "  <-- ACTIVE";
        cout << "\n";
        temp = temp->nextTab;
        count++;
    }
}

void goBack() {
    if (historyEmpty()) {
        cout << "No browsing history available.\n";
        return;
    }

    removeFromHistory();
    if (!historyEmpty()) {
        cout << " Returned to: " << showTopHistory() << "\n";
    } else {
        cout << "You've reached the start of your browsing history.\n";
    }
}

void visitSite(const string& site) {
    openTab(site);
    addToHistory(site);
}

// ---------- MAIN FUNCTION ----------
int main() {
    int choice;
    string site;

    cout << "\n===== MINI WEB BROWSER SIMULATOR =====\n";

    do {
        cout << "\nMenu Options:\n";
        cout << " 1. Open new tab\n";
        cout << " 2. Close active tab\n";
        cout << " 3. Show active tab\n";
        cout << " 4. Display all tabs\n";
        cout << " 5. Go back (History)\n";
        cout << " 6. Switch to next tab\n";
        cout << " 7. Switch to previous tab\n";
        cout << " 0. Exit browser\n";
        cout << "Enter your option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter website URL: ";
                cin >> site;
                visitSite(site);
                break;
            case 2:
                closeTab();
                break;
            case 3:
                cout << "Current tab: " 
                     << (activeTab ? activeTab->url : "No tabs open") << "\n";
                break;
            case 4:
                showTabs();
                break;
            case 5:
                goBack();
                break;
            case 6:
                moveNextTab();
                break;
            case 7:
                movePrevTab();
                break;
            case 0:
                cout << "Browser closed. Goodbye!\n";
                break;
            default:
                cout << "Invalid input! Please try again.\n";
        }

    } while (choice != 0);

   return 0;
}
