#include <iostream>
#include <random>
#include <array>
#include <nlohmann/json.hpp> //Retreived from nlohmann on Github
using namespace std;
using json = nlohmann::json;

namespace ns { //Put into a namespace because otherwise it won't work well with the JSON functions
	struct Product {
		char Name = 'u'; //u for unknown, realistically this doesnt have to be initialised, I just did it to get rid of a warning.
		unsigned int Price = 0;
		unsigned int Quantity = 0;
		unsigned int SaleThreshold = 0; //default values
	public:
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Product, Name, Price, Quantity, SaleThreshold);
		Product(char name, unsigned int price, unsigned int quantity, unsigned int threshold) {
			this->Name = name;
			this->Price = price;
			this->Quantity = quantity;
			this->SaleThreshold = threshold;
		}; //Constructor with most customisability
		Product(char name, unsigned int quantity) {
			this->Name = name;
			switch (Name) {
			case 'A': this->Price = 50; this->SaleThreshold = 3; break;
			case 'B': this->Price = 35; this->SaleThreshold = 2; break;
			case 'C': this->Price = 25; break;
			case 'D': this->Price = 12; break;
			default: break;
			};
			this->Quantity = quantity;
		}; //Constructor for JSON objects
		Product() {} //Default Constructor
		~Product() {}; //Destructor

		int GetPrice() {
			int amount = (Quantity * Price);
			if (SaleThreshold > 0) { //If product has a deal...
				for (unsigned int i = Quantity; i >= SaleThreshold; i -= SaleThreshold) { //Keep removing 10 until there are no more valid deals.
					amount = amount - 10; //Both deals effectively remove 10 from the final price. 
				};
			}
			return amount;
		};

		void SetQuantity(unsigned int quantity) {
			this->Quantity = quantity;
		};
	};
}

using namespace ns;

int main()
{
	//"[{\"code\":\"A\",\"quantity\":3},{\"code\":\"B\",\"quantity\":3},{\"code\":\"C\",\"quantity\":1},{\"code\":\"D\",\"quantity\":2}]" Copy this and paste it into 'parse'
	auto j = json::parse("[{\"code\":\"A\",\"quantity\":3},{\"code\":\"B\",\"quantity\":3},{\"code\":\"C\",\"quantity\":1},{\"code\":\"D\",\"quantity\":2}]");
	array<Product, 4> Basket = { Product('A', 0), Product('B', 0), Product('C', 0), Product('D', 0), }; //Use this array for JSON serialised inputs, use other array for random quantities
	unsigned int i = 0;
	for (json::iterator it = j.begin(); it != j.end(); ++it) { //This for loop iterates through the JSON file, "it", the iterator, will be something like {"code":"A","quantity":"3"}
		json p = *it; //Converting it from an iterator into a JSON object so that I can utilise the [] operator
		Basket[i] = (Product(p["code"].get<string>().front(), p["quantity"].get<unsigned int>())); //Messy way of converting string to char, .get<type>() supports string but not char (throws an exception)
		i++;
	}
	srand((unsigned)time(NULL)); //seed for randomiser
	//array<Product, 4> Basket = { Product('A', (1 + (rand() % 15))), Product('B', (1 + (rand() % 11))), Product('C', (1 + (rand() % 7))), Product('D', (1 + (rand() % 13))) }; //Random range numbers randomly chosen
	int total = 0;
	for (unsigned int i = 0; i < Basket.size(); i++) {
		total += Basket[i].GetPrice();
		cout << "Code: " << Basket[i].Name << ", Quantity: " << Basket[i].Quantity << endl;
	};
	cout << "Total: " << total;
	return 0;
};