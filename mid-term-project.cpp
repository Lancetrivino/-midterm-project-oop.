#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib> 
#include <limits>

using namespace std;


class Item {
private:
    string id;
    string name;
    int quantity;
    double price;

public:
    Item(string id, string name, int quantity, double price)
        : id(id), name(name), quantity(quantity), price(price) {}

    virtual void displayInfo() const {
        cout << setw(5) << id 
             << setw(15) << name 
             << setw(15) << quantity 
             << setw(15) << fixed << setprecision(2) << price;
    }

    string getId() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    void setQuantity(int quantity) { this->quantity = quantity; }
    void setPrice(double price) { this->price = price; }
};


class ClothingItem : public Item {
public:
    ClothingItem(string id, string name, int quantity, double price)
        : Item(id, name, quantity, price) {}

    void displayInfo() const override {
        Item::displayInfo(); 
    }

    string getCategory() const { return "Clothing"; } 
};


class ElectronicsItem : public Item {
public:
    ElectronicsItem(string id, string name, int quantity, double price)
        : Item(id, name, quantity, price) {}

    void displayInfo() const override {
        Item::displayInfo(); 
    }

    string getCategory() const { return "Electronics"; } 
};


class EntertainmentItem : public Item {
public:
    EntertainmentItem(string id, string name, int quantity, double price)
        : Item(id, name, quantity, price) {}

    void displayInfo() const override {
        Item::displayInfo(); 
    }

    string getCategory() const { return "Entertainment"; } 
};


class Inventory {
private:
    Item* items[100]; 
    int itemCount;

public:
    Inventory() : itemCount(0) {}

    int getItemCount() const { return itemCount; }

    bool isEmpty() const {
        if (itemCount == 0) {
            cout << "\nNo items in the inventory.\n";
            return true;
        }
        return false;
    }

    bool addItem(string category, string id, string name, int quantity, double price) {
    if (itemCount >= 100) {
        cout << "Inventory is full!" << endl;
        return false;
    }
    
    if (quantity <= 0) {
        cout << "Quantity must be greater than 0!" << endl;
        return false;
    }

    if (price <= 0.0) {
        cout << "Price must be greater than 0!" << endl;
        return false;
    }

    if (category == "1" || category == "Clothing") {
        items[itemCount++] = new ClothingItem(id, name, quantity, price);
    } else if (category == "2" || category == "Electronics") {
        items[itemCount++] = new ElectronicsItem(id, name, quantity, price);
    } else if (category == "3" || category == "Entertainment") {
        items[itemCount++] = new EntertainmentItem(id, name, quantity, price);
    } else {
        cout << "Invalid category!" << endl;
        return false;
    }
    cout << "Item added successfully!" << endl;
    return true;
}


  bool updateItem(const string& id) {
    if (itemCount == 0) {
        cout << "\nNo items in the inventory.\n";
        return false;
    }

    for (int i = 0; i < itemCount; ++i) {
        if (items[i]->getId() == id) {
            string updateField;
            cout << "Enter 'quantity' or 'price' to update: ";
            cin >> updateField;

            if (updateField == "quantity") {
                int newQuantity;
                do {
                    cout << "Enter new quantity (must be greater than 0): ";
                    cin >> newQuantity;
                } while (newQuantity <= 0);

                cout << "Quantity of Item " << items[i]->getName() << " is updated from "
                     << items[i]->getQuantity() << " to " << newQuantity << endl;
                items[i]->setQuantity(newQuantity);
                return true; 

            } else if (updateField == "price") {
                double newPrice;
                do {
                    cout << "Enter new price (must be greater than 0): ";
                    cin >> newPrice;
                } while (newPrice <= 0.0);

                cout << "Price of Item " << items[i]->getName() << " is updated from "
                     << items[i]->getPrice() << " to " << newPrice << endl;
                items[i]->setPrice(newPrice);
                return true; 

            } else {
                cout << "Invalid field to update!" << endl;
                return false; 
            }
        }
    }
    cout << "Item not found!" << endl; 
    return false;
}

    bool removeItem(string id) {
    if (isEmpty()) return false;

    for (int i = 0; i < itemCount; ++i) {
        if (items[i]->getId() == id) {
            cout << "Item " << items[i]->getName() << " has been removed from the inventory" << endl;
            delete items[i];
            for (int j = i; j < itemCount - 1; ++j) {
                items[j] = items[j + 1];
            }
            --itemCount;
            return true;
        }
    }
    cout << "Item not found!" << endl;
    return false;
}

    void displayItemsByCategory(string category) {
        if (isEmpty()) return;

        cout << "Items in category " << category << ":\n\n";
        cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Quantity" << setw(15) << "Price" << endl;
        bool found = false;
        for (int i = 0; i < itemCount; ++i) {
            if ((category == "1" && dynamic_cast<ClothingItem*>(items[i])) ||
                (category == "2" && dynamic_cast<ElectronicsItem*>(items[i])) ||
                (category == "3" && dynamic_cast<EntertainmentItem*>(items[i]))) {
                found = true;
                items[i]->displayInfo();
                cout << endl;
            }
        }
        if (!found) {
            cout << "No items found in category " << category << "!" << endl;
        }
    }

    void displayAllItems() {
        if (isEmpty()) return;

        cout << "\n" << setw(70) << setfill('-') << "" << endl; 
        cout << setfill(' ') << ""; 
        cout << setw(5) << "ID" 
             << setw(15) << "Name" 
             << setw(15) << "Quantity" 
             << setw(15) << "Price" 
             << setw(15) << "Category" << endl;
        cout << setw(55) << setfill(' ') << "" << endl; 

        for (int i = 0; i < itemCount; ++i) {
            items[i]->displayInfo();
            cout << setw(15) << (dynamic_cast<ClothingItem*>(items[i]) ? "Clothing" :
                                dynamic_cast<ElectronicsItem*>(items[i]) ? "Electronics" : "Entertainment") << endl;
        }

        cout << setw(70) << setfill('-') << "" << endl; 
    }

    void searchItem(string id) {
        if (isEmpty()) return;

        for (int i = 0; i < itemCount; ++i) {
            if (items[i]->getId() == id) {
                cout << "Item found:\n";
                items[i]->displayInfo();
                cout << endl; 
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    void sortItems(bool sortByPrice, bool ascending) {
        if (isEmpty()) return;

        for (int i = 0; i < itemCount - 1; ++i) {
            for (int j = 0; j < itemCount - i - 1; ++j) {
                bool condition = (ascending ? (sortByPrice ? items[j]->getPrice() > items[j + 1]->getPrice() : items[j]->getQuantity() > items[j + 1]->getQuantity()) :
                                             (sortByPrice ? items[j]->getPrice() < items[j + 1]->getPrice() : items[j]->getQuantity() < items[j + 1]->getQuantity()));

                if (condition) {
                    swap(items[j], items[j + 1]);
                }
            }
        }
        cout << "Items sorted successfully!" << endl; 
    }

    void displayLowStockItems(int threshold = 5) {
        if (isEmpty()) return;

        cout << "Items with quantity less than or equal to " << threshold << ":\n\n";
        cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Quantity" << setw(15) << "Price" << endl;
        bool found = false;
        for (int i = 0; i < itemCount; ++i) {
            if (items[i]->getQuantity() <= threshold) {
                found = true;
                items[i]->displayInfo();
                cout << endl;
            }
        }
        if (!found) {
            cout << "No low stock items found!" << endl;
        }
    }
};


int main() {
    Inventory inventory;
    int choice;

    do {
        const int width = 42; 

        cout << "\n\n" << setw(width) << setfill('#') << "" << endl; 
        cout << setfill(' '); 
        cout << setw(width) << "##                                      ##" << endl; 
        cout << setw(width) << "##         Inventory Management         ##" << endl; 
        cout << setw(width) << "##                System                ##" << endl; 
        cout << setw(width) << "##                                      ##" << endl; 
        cout << setw(width) << setfill('#') << "" << endl; 
        cout << setfill(' ') << endl;

        cout << "Options:\n";
        cout << "1. Add Item\n";
        cout << "2. Update Item\n";
        cout << "3. Remove Item\n";
        cout << "4. Display Items by Category\n";
        cout << "5. Display All Items\n";
        cout << "6. Search Item\n";
        cout << "7. Sort Items\n";
        cout << "8. Display Low Stock Items\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            system("pause");
            system("cls");
            string category, id, name;
            int quantity;
            double price;

            cout << "Enter category (1. Clothing, 2. Electronics, 3. Entertainment): ";
            cin >> category;
            cout << "Enter ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Quantity: ";
            cin >> quantity;
            cout << "Enter Price: ";
            cin >> price;
            inventory.addItem(category, id, name, quantity, price);
            system("pause");
            system("cls");
            break;
        }
        case 2: {
            system("pause");
            system("cls");
            if (inventory.getItemCount() == 0) {
                cout << "No items in the inventory." << endl;
            } else {
                string id;
                cout << "Enter ID of the item to update: ";
                cin >> id;
                inventory.updateItem(id);
            }
            system("pause");
            system("cls");
            break;
        }
        case 3: {
            system("pause");
            system("cls");
            if (inventory.getItemCount() == 0) {
                cout << "No items in the inventory." << endl;
            } else {
                string id;
                cout << "Enter ID of the item to remove: ";
                cin >> id;
                inventory.removeItem(id);
            }
            system("pause");
            system("cls");
            break;
        }
        case 4: {
            system("pause");
            system("cls");
            if (inventory.getItemCount() == 0) {
                cout << "No items in the inventory." << endl;
            } else {
                string category;
                cout << "Enter category (1. Clothing, 2. Electronics, 3. Entertainment): ";
                cin >> category;
                inventory.displayItemsByCategory(category);
            }
            system("pause");
            system("cls");
            break;
        }
        case 5: {
            system("pause");
            system("cls");
            inventory.displayAllItems();
            cout << "\n" << endl;
            system("pause");
            system("cls");
            break;
        }
        case 6: {
            system("pause");
            system("cls");
            if (inventory.getItemCount() == 0) {
                cout << "No items in the inventory." << endl;
            } else {
                string id;
                cout << "Enter ID of the item to search: ";
                cin >> id;
                inventory.searchItem(id);
            }
            system("pause");
            system("cls");
            break;
        }
        case 7: {
            system("pause");
            system("cls");
            if (inventory.getItemCount() == 0) {
                cout << "No items in the inventory." << endl;
            } else {
                bool sortByPrice, ascending;
                char priceChoice, orderChoice;

                cout << "Sort by (1. Price, 2. Quantity): ";
                cin >> priceChoice;
                sortByPrice = (priceChoice == '1');

                cout << "Sort order (1. Ascending, 2. Descending): ";
                cin >> orderChoice;
                ascending = (orderChoice == '1');

                inventory.sortItems(sortByPrice, ascending);
            }
            system("pause");
            system("cls");
            break;
        }
        case 8: {
            system("pause");
            system("cls");
            inventory.displayLowStockItems();
            system("pause");
            system("cls");
            break;
        }
        case 9:
            system("pause");
            system("cls");
            cout << "Exiting program." << endl;
            system("cls");
            break;

        default:
            system("cls");
            cout << "Invalid choice! Please try again." << endl;
            system("pause");
            system("cls");
    }


        
        } while (choice != 9);

    return 0;
}
