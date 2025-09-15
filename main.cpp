#include<iostream> // for cin and cout commands
#include<string> // for using string data type
using namespace std; // standard namespace to avoid std:: prefix 

class Item { // defining a class for representing the items
    public: // Making it's variables accessible from outside the class
    string code; // product code (e.g. "A1")
    string name; // product name (e.g. "Coffee")
    string category; // category (e.g. "Hot", "Cold", "Snack")
    double price; // product price (e.g. 1.5)
    int stock; // quantity in stock (e.g. 3)
};

void showMenu(Item items[], int count) { // function to display the menu
    cout << "\n=== VENDING MACHINE MENU ===\n"; // Displaying the title of the menu
    for (int i = 0; i < count; i++) { // Looping through the items array
        cout << items[i].code << " - " << items[i].name // Displaying item name
             << " (" << items[i].category << ") " // Category
             << "£" << items[i].price //  Price
             << " | Stock: " << items[i].stock << "\n"; // Stock
    }
    cout << "------------------------------\n";
}
int findByCode(Item items[], int count, string code) { // function to find item index by code
    for (int i = 0; i < count; i++) { // Looping through the items array
        if (items[i].code == code) return i; // If code matches, return index
    }
    return -1; // If not found, return -1
}

double readMoney(const string& prompt) { // to read the money amount and check if valid
    double x; // variable to store the amount
    while (true) { // Loop until valid input is received
        cout << prompt; // Display the prompt
        if (cin >> x && x >= 0.0) { // If input is valid (zero or more)
            return x;// return the amount so we can use it in our program
        } else {// If input is invalid
            cout << "Invalid input. Please enter a valid amount (>= 0).\n";// Display error message
            cin.clear(); // in case user types something invalid, this resets the cin
            cin.ignore(10000, '\n');// remove the invalid input from 
        }
    }
}

void suggest(const Item& bought) { // function to suggest another item based on the category
    if (bought.category == "Hot") { // If the bought item is Hot
        cout << "Maybe you fancy a snack as well (Chips/Biscuits) :)\n"; // Suggest snack
    } else if (bought.category == "Snack") { // If the bought item is Snack
        cout << "Maybe you fancy a drink as well (Hot/Cold) :)\n"; // Suggest drink
    }
}

bool vendItem(Item& item) { // function to sell an item: check stock, handle money, calculate change
    if (item.stock <= 0) { // If the item is out of stock
        cout << "Sorry, " << item.name << " is OUT OF STOCK.\n"; // Display out of stock message
        return false; // Return false to indicate failure
    }

    cout << "Selected: " << item.name << " | Price: £" << item.price << "\n"; // Display selected item and price

    double money = readMoney("Insert money: £"); // Read initial money input

    while (money < item.price) { // While the inserted money is less than the item price
        cout << "Insufficient funds. You need £" << (item.price - money) << " more.\n"; // Display insufficient funds message
        double more = readMoney("Insert more: £"); // Read additional money input
        money += more; // Add the additional money to the total
    }/*Keeps asking for money until there is enough*/

    double change = money - item.price; // Calculate change to be dispensed
    item.stock--; // Decrease the stock of the item by 1
    cout << "Ready. Please pick up your: " << item.name << "\n"; // Prompt user to pick up the item
    cout << "Change Dispensed: £" << change << "\n"; // Display the change dispensed
    suggest(item); // Suggest another item based on the category of the bought item
    return true; // Return true to indicate successful vending
}

int main() {
    
    Item items[6]; // This is our array of items
    int count = 6; // with 6 items in it 
    
    items[0] = {"A1", "Coffee",  "Hot",   1.5, 3}; 
    items[1] = {"A2", "Tea",     "Hot",   1.2, 2};
    items[2] = {"B1", "Water",   "Cold",  1.0, 5};
    items[3] = {"B2", "Cola",    "Cold",  1.3, 2};
    items[4] = {"C1", "Chips",   "Snack", 1.1, 3};
    items[5] = {"C2", "Biscuits","Snack", 0.9, 2};
 
    /*Initialised all the items. Each is set up with a code, name , category, price, and stock. */

    int itemsSold = 0;     // Counts how many items have been sold
    double totalSales = 0; // Adds up the total sales value
        
    bool running = true; // Variable to control the main loop
    while (running) {
        showMenu (items, count); // Display the menu
        cout << "Enter product code to buy or 'exit' to quit: "; // Prompt user for input
        string code; // Variable to store user input
        cin >> code; // Read user input

        if (code == "X" || code == "x") {// If user wants to exit
            cout << "Goodbye!\n";// Display goodbye message
            break;// Exit the loop and end the program
        } 

        int idx = findByCode(items, count, code); // Find the item by code
        if (idx == -1) {// If the code is invalid
            cout << "Invalid code. Try again.\n";// Display error message
        } else { //. If the code is valid
            bool ok = vendItem(items[idx]); // Attempt to vend the item
            if (ok) {// If vending was successful
                itemsSold += 1;// Increment the items sold counter
                totalSales += items[idx].price;// Add the item price to total sales
            }
        }

        cout << "Want to buy something else? (y/n): "; // prompt user to continue or exit
        char again; // this variable stores the user's response
        cin >> again; // read the user's response
        if (again != 'y' && again != 'Y') { // if the response is not 'y' or 'Y'
            running = false;// set running to false and exit the loop
        }
    }

     // Print session summary with total items sold and total sales amount 
    cout << "\n=== SESSION SUMMARY ===\n";
    cout << "Items purchased: " << itemsSold << "\n";
    cout << "Total spent: £" << totalSales << "\n";
    cout << "Thank you! Have a nice day!\n";

    return 0; // End of the program
}


    
