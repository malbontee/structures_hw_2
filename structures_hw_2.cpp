
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

/* Описать структуру Check (receipt):
Предусмотреть функцию добавления информации о товаре (наименование, количество, цена за единицу товара, скидка) в чек, функцию распечатки чека на экране консоли. */

struct Product_Info {
    string name;
    int quantity;
    double price_per_1;
    int discount;
};

struct Receipt {
    int size = 0;
    Product_Info* product = nullptr;
};
void set_array_size(Receipt& receipt) {
    cout << "How many products you'd like to add? (500 is max)\n";
    cin >> receipt.size;
}
void check_array_size(Receipt& receipt) {
    if (receipt.size > 500)
        receipt.size = 500;
}
void create_array(Receipt& receipt) {
    receipt.product = new Product_Info[receipt.size];
}
void product_user_input(Product_Info& product) {
    cin.ignore();
    cout << "Please enter the name of your product: ";
    getline(cin, product.name);
    cout << "Please enter quantity: ";
    cin >> product.quantity;
    cout << "Please enter the price per unit: ";
    cin >> product.price_per_1;
    cout << "Please enter discount: ";
    cin >> product.discount;
}

void add_product_in_arr(Receipt& receipt) {
    for (int i = 0; i < receipt.size; ++i) {
        product_user_input(receipt.product[i]);
    }
}

double calculate_total_cost(const Receipt& receipt) {
    double total = 0;
    for (int i = 0; i < receipt.size; ++i) {
        double discounted_price = receipt.product[i].price_per_1 * (1 - receipt.product[i].discount / 100.0); // Цена со скидкой=Цена без скидки*(1 - Скидка/100)
        total += discounted_price * receipt.product[i].quantity;
    }
    return total;
}

void print_total_cost(const Receipt& receipt) {
    double total_cost = calculate_total_cost(receipt);
    cout << "Total cost: " << total_cost << "\n";
}
void print_receipt(const Receipt& receipt) {
    for (int i = 0; i < receipt.size; ++i) {
        cout << "===============================================\n";
        cout << "Name of the product: " << receipt.product[i].name << "\n";
        cout << "Quantity: " << receipt.product[i].quantity << "\n";
        cout << "Price per unit: " << receipt.product[i].price_per_1 << "\n";
        cout << "Discount: " << receipt.product[i].discount << "\n";
        cout << "===============================================\n";
    }
    print_total_cost(receipt);
    cout << "===============================================\n";
    cout << "Thanks for your purchase! Come again!\n";
    cout << "===============================================\n";
}

void print_date_time() {
    time_t now = time(0);
    char date_time[26];
    ctime_s(date_time, sizeof(date_time), &now);
    cout << "Purchase date and time: " << date_time;
}
void clear_memory(Receipt& receipt) {
    delete[] receipt.product;
    receipt.product = nullptr;
}

int main() {
    Receipt receipt;

    set_array_size(receipt);
    check_array_size(receipt);
    create_array(receipt);
    add_product_in_arr(receipt);
    print_receipt(receipt);
    print_date_time();
    clear_memory(receipt);
}

