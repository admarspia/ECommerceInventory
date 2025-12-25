#include <iostream>
#include <string>
#include <vector>
#include <limits>

#include "Inventory.h"
#include "Order.h"
#include "Utils.h"

void pause() { std::cout << "Press Enter to continue..."; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); }

int readInt(const std::string &prompt) {
    int x;
    std::cout << prompt;
    while (!(std::cin >> x)) {
        std::cin.clear(); std::cin.ignore(10000, '\n');
        std::cout << "Invalid input. Try again: ";
    }
    std::cin.ignore(10000, '\n');
    return x;
}

double readDouble(const std::string &prompt) {
    double x; std::cout << prompt;
    while (!(std::cin >> x)) { std::cin.clear(); std::cin.ignore(10000, '\n'); std::cout << "Invalid input. Try again: "; }
    std::cin.ignore(10000, '\n');
    return x;
}

std::string readLine(const std::string &prompt) {
    std::string s; std::cout << prompt; std::getline(std::cin, s); return s;
}

void printProduct(const Product &p) {
    std::cout << "ID:" << p.id << " | " << p.name << " | Cat:" << p.category << " | Price:" << p.price << " | Stock:" << p.stock << "\n";
}

void addSampleData(Inventory &inv) {
    inv.addProduct(Product(101, "USB-C Cable", "Accessories", 8.99, 150));
    inv.addProduct(Product(102, "Wireless Mouse", "Electronics", 19.99, 60));
    inv.addProduct(Product(103, "Mechanical Keyboard", "Electronics", 69.5, 25));
    inv.addProduct(Product(201, "Curtain A - Blue", "Home", 45.0, 12));
    inv.addProduct(Product(202, "Curtain B - Red", "Home", 52.0, 8));
}

int main() {
    Inventory inv;
    OrderHistory history;
    addSampleData(inv);

    while (true) {
        std::cout << "--- E-Commerce Inventory ---\n";
        std::cout << "1) List all products\n";
        std::cout << "2) Add product\n";
        std::cout << "3) Remove product by ID\n";
        std::cout << "4) Search by ID\n";
        std::cout << "5) Search by name\n";
        std::cout << "6) Filter by category\n";
        std::cout << "7) Restock product\n";
        std::cout << "8) Place order\n";
        std::cout << "9) View order history\n";
        std::cout << "0) Exit\n";
        int choice = readInt("Choose: ");
        if (choice == 0) break;
        switch (choice) {
            case 1: {
                        auto all = inv.allProducts();
                        for (auto &p : all) printProduct(p);
                        pause();
                        break;
                    }
            case 2: {
                        int id = readInt("ID: ");
                        std::string name = readLine("Name: ");
                        std::string cat = readLine("Category: ");
                        double price = readDouble("Price: ");
                        int stock = readInt("Stock: ");
                        bool ok = inv.addProduct(Product(id, name, cat, price, stock));
                        std::cout << (ok? "Added." : "ID already exists.") << "\n";
                        pause();
                        break;
                    }
            case 3: {
                        int id = readInt("ID to remove: ");
                        bool ok = inv.removeProductByID(id);
                        std::cout << (ok? "Removed." : "Not found.") << "\n";
                        pause();
                        break;
                    }
            case 4: {
                        int id = readInt("ID: ");
                        Product* p = inv.searchByID(id);
                        if (p) printProduct(*p); else std::cout << "Not found\n";
                        pause();
                        break;
                    }
            case 5: {
                        std::string q = readLine("Name query: ");
                        auto res = inv.searchByName(q);
                        for (auto &p : res) printProduct(p);
                        if (res.empty()) std::cout << "No match\n";
                        pause();
                        break;
                    }
            case 6: {
                        std::string cat = readLine("Category: ");
                        auto res = inv.filterByCategory(cat);
                        for (auto &p : res) printProduct(p);
                        if (res.empty()) std::cout << "No products in this category\n";
                        pause();
                        break;
                    }
            case 7: {
                        int id = readInt("ID to restock: ");
                        int q = readInt("Quantity: ");
                        bool ok = inv.restock(id, q);
                        std::cout << (ok? "Restocked." : "Product not found.") << "\n";
                        pause();
                        break;
                    }
            case 8: {
                        std::string customer = readLine("Customer name: ");
                        int n = readInt("How many different products in order? ");
                        std::vector<OrderItem> items;
                        for (int i=0;i<n;i++) {
                            int pid = readInt("Product ID: ");
                            int qty = readInt("Quantity: ");
                            items.push_back({pid, "", qty, 0.0});
                        }
                        bool ok = inv.placeOrder(customer, items, history);
                        std::cout << (ok? "Order placed." : "Order failed (missing product or insufficient stock).") << "\n";
                        pause();
                        break;
                    }
            case 9: {
                        history.printAll();
                        pause();
                        break;
                    }
            default:
                    std::cout << "Unknown choice\n";
                    break;
        }
    }

    std::cout << "Goodbye\n";
    return 0;
}

