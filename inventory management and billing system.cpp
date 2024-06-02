#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Structure to represent an item
struct Item {
    string name;
    double price;
    int quantity;
};

// Constants
const int MAX_ITEMS = 100;
Item inventory[MAX_ITEMS];
int itemCount = 0;
double totalSales = 0;

// Function prototypes
void addItem();
void removeItem();
void displayInventory();
void processSale();
void displayTotalSales();
void saveData();
void retrieveData();

int main() {
    // Retrieve saved data
    retrieveData();

    int choice;
    do {
        cout << "\n1. Display Inventory\n2. Process Sale\n3. Display Total Sales\n4. Add Item\n5. Delete Item\n6. Save Data\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayInventory();
            break;
        case 2:
            processSale();
            break;
        case 3:
            displayTotalSales();
            break;
        case 4:
            addItem();
            break;
        case 5:
            removeItem();
            break;
        case 6:
            saveData();
            cout << "Data saved.\n";
            break;
        case 7:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}

// Function to add an item to inventory
void addItem() {
    if (itemCount >= MAX_ITEMS) {
        cout << "Inventory is full. Cannot add more items.\n";
        return;
    }

    cout << "Enter item name: ";
    cin >> inventory[itemCount].name;
    cout << "Enter item price: ";
    cin >> inventory[itemCount].price;
    cout << "Enter item quantity: ";
    cin >> inventory[itemCount].quantity;

    itemCount++;
    cout << "Item added to inventory.\n";
}

// Function to remove an item from inventory
void removeItem() {
    if (itemCount == 0) {
        cout << "Inventory is empty. Cannot remove items.\n";
        return;
    }

    int id;
    cout << "Enter item ID to delete: ";
    cin >> id;

    if (id >= 1 && id <= itemCount) {
        // Remove item by shifting elements
        for (int i = id - 1; i < itemCount - 1; ++i) {
            inventory[i] = inventory[i + 1];
        }
        itemCount--;
        cout << "Item deleted from inventory.\n";
    }
    else {
        cout << "Invalid item ID.\n";
    }
}

// Function to display inventory
void displayInventory() {
    cout << "Inventory:\n";
    cout << "ID\tName\tPrice\tQuantity\n";
    for (int i = 0; i < itemCount; ++i) {
        cout << i + 1 << "\t" << inventory[i].name << "\t" << inventory[i].price << "\t" << inventory[i].quantity << endl;
    }
}

// Function to process a sale
void processSale() {
    int id, quantity;
    cout << "Enter item ID and quantity: ";
    cin >> id >> quantity;

    if (id >= 1 && id <= itemCount) {
        if (inventory[id - 1].quantity >= quantity) {
            double total = quantity * inventory[id - 1].price;
            cout << "Total sale amount: $" << total << endl;
            inventory[id - 1].quantity -= quantity;
            totalSales += total;
        }
        else {
            cout << "Insufficient quantity in stock.\n";
        }
    }
    else {
        cout << "Invalid item ID.\n";
    }
}

// Function to display total sales
void displayTotalSales() {
    cout << "Total Sales: $" << totalSales << endl;
}

// Function to save data to files
void saveData() {
    ofstream inventoryFile("inventory.txt");
    if (inventoryFile.is_open()) {
        inventoryFile << itemCount << endl;
        for (int i = 0; i < itemCount; ++i) {
            inventoryFile << inventory[i].name << " " << inventory[i].price << " " << inventory[i].quantity << endl;
        }
        inventoryFile.close();
    }

    ofstream salesFile("sales.txt");
    if (salesFile.is_open()) {
        salesFile << totalSales << endl;
        salesFile.close();
    }
}

// Function to retrieve data from files
void retrieveData() {
    ifstream inventoryFile("inventory.txt");
    if (inventoryFile.is_open()) {
        inventoryFile >> itemCount;
        for (int i = 0; i < itemCount; ++i) {
            inventoryFile >> inventory[i].name >> inventory[i].price >> inventory[i].quantity;
        }
        inventoryFile.close();
    }

    ifstream salesFile("sales.txt");
    if (salesFile.is_open()) {
        salesFile >> totalSales;
        salesFile.close();
    }
}