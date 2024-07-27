#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

//prototype functions
void programGreet();
int shirtSizes();
int shirtQuantity();
int numberofColors();
bool secondPrint();
double getPricePerShirt(int quantityCategory, int numColors, int sizeCategory);
double totalPrice(double pricePerShirt, int numShirts, bool addSecondPrint);

void programGreet() {
    cout << "Hello, welcome to our t-shirt catalog." << endl;
}
vector<vector<vector<double>>> shirtPrices = {
    // 1 color prinnt
    {
        {19.69, 9.69, 7.70, 6.70, 0.00},  // Youth
        {19.99, 9.99, 8.00, 7.00, 0.00},  // Adult S-XL
        {21.64, 11.64, 9.65, 8.65, 0.00}  // Adult 2XL-5XL
    },
    // 2 color print
    {
        {20.69, 11.69, 9.70, 8.70, 0.00}, // Youth
        {21.99, 11.99, 10.00, 9.00, 0.00}, // Adult S-XL
        {22.64, 12.64, 11.65, 10.65, 0.00} // Adult 2XL-5XL
    },
    // 3 color print
    {
        {21.69, 12.69, 10.70, 9.70, 0.00}, // Youth
        {22.99, 12.99, 11.00, 10.00, 0.00}, // Adult S-XL
        {23.64, 13.64, 12.65, 11.65, 0.00} // Adult 2XL-5XL
    },
    // 4 color print
    {
        {22.69, 13.69, 11.70, 10.70, 0.00}, // Youth
        {23.99, 13.99, 12.00, 11.00, 0.00}, // Adult S-XL
        {24.64, 14.64, 13.65, 12.65, 0.00} // Adult 2XL-5XL
    },
    // 5 color print
    {
        {23.69, 14.69, 12.70, 11.70, 0.00}, // Youth
        {24.99, 14.99, 13.00, 12.00, 0.00}, // Adult S-XL
        {25.64, 15.64, 14.65, 13.65, 0.00} // Adult 2XL-5XL
    }
};

int shirtSizes() {
    cout << "Enter a shirt size: Youth, Adult Small, Adult  Medium, Adult Large, Adult XL" << endl;
    string size;
    cin.ignore();
    getline(cin, size);

    if (size == "youth") return 0;
    else if (size == "adult small") return 1;
    else if (size == "adult medium") return 2;
    else if (size == "adult large") return 3;
    else if (size == "adult xl") return 4;
    else {
        cout << "Invalid size entered. Please enter the specified sizes." << endl;

        return -1;
    }
}
int shirtQuantity() {
    cout << "Enter the number of shirts (minimum order is 12): ";
    int quantity;
    cin >> quantity;

    if (quantity < 12) {
        cout << "Invalid quantity. Minimum order is 12 shirts." << endl;
        return -1;
    }
    else if (quantity >= 12 && quantity <= 24) {
        return 0;
    }
    else if (quantity >= 25 && quantity <= 49) {
        return 1;
    }
    else if (quantity >= 50 && quantity <= 199) {
        return 2;
    }
    else if (quantity >= 200 && quantity <= 299) {
        return 3;
    }
    else {
        cout << "For orders of 300 or more shirts, please call for a quote." << endl;
        return -2; 
    }
}

int numberofColors() {
    cout << "Enter the number of colors (up to 5): ";
    int colors;
    cin >> colors;

    if (colors < 1 || colors > 5) {
        cout << "Invalid number of colors. Must be between 1 and 5." << endl;
        return -1;
    }
    return colors;
}

bool secondPrint() {
    cout << "Would you like to add a second print onto the shirt(s)? Type (Y/N): ";
    char response;
    cin >> response;
    response = tolower(response);

    if (response == 'y') {
        return true;
    }
    else if (response == 'n') {
        return false;
    }
    else {
        cout << "Invalid input. Assuming no second print location." << endl;
        return false;
    }
}

double getPricePerShirt(int quantityCategory, int numColors, int sizeCategory) {
    if (quantityCategory == 4) {
        cout << "For orders over 300 shirts, call for a quote." << endl;
        return -1;
    }
    return shirtPrices[numColors - 1][sizeCategory][quantityCategory];
}

double totalPrice(double pricePerShirt, int numShirts, bool addSecondPrint) {
    double total = pricePerShirt * numShirts;

    if (addSecondPrint) {
        double additionalCost = 3.00;
        total += additionalCost * numShirts;
    }

    return total;
}

int main() {
    programGreet();

    int quantityCategory = shirtQuantity();
    if (quantityCategory == -1) {
        cout << "Invalid quantity entered. Exiting program." << endl;
        return 1;
    }
    if (quantityCategory == -2) {
        
        return 0;
    }

    int numColors = numberofColors();
    if (numColors == -1) {
        cout << "Invalid number of colors entered. Exiting program." << endl;
        return 1;
    }

    int sizeCategory = shirtSizes();
    if (sizeCategory == -1) {
        cout << "Invalid size entered. Exiting program." << endl;
        return 1;
    }

    bool addSecondPrint = secondPrint();

    double pricePerShirt = getPricePerShirt(quantityCategory, numColors, sizeCategory);
    if (pricePerShirt == -1) {
        cout << "For large orders, please call for a quote. Exiting program." << endl;
        return 1;
    }

    int numShirts = 0;
    switch (quantityCategory) {
    case 0: numShirts = 12; break;
    case 1: numShirts = 25; break;
    case 2: numShirts = 50; break;
    case 3: numShirts = 200; break;
    default:
        cout << "Unexpected error in determining shirt quantity. Exiting program." << endl;
        return 1;
    }

    double totalCost = totalPrice(pricePerShirt, numShirts, addSecondPrint);
    cout << "Total cost: $" << fixed << setprecision(2) << totalCost << endl;

    return 0;
}