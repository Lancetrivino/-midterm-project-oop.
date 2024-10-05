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
        brea