#include <iostream>
#include <vector>
using namespace std;

class Pizza {
public:
	std::string getName() { return name; }
	void setName(std::string newName) { name = newName; }
	
	std::string getDescription() { return description; }
	void setDescription(std::string newDescription) { description = newDescription; }

	short getSize() { return size; }
	void setSize(short newSize) { size = newSize; }

	float getPrice() { return price; }
	void setPrice(float newPrice) { price = newPrice; }

	int getSaltCount() { return saltCount; }
	void setSaltCount(int newSaltCount) { saltCount = newSaltCount; }

	int getCheeseCount() { return cheeseCount; }
	void setCheeseCount(int newCheeseCount) { cheeseCount = newCheeseCount; }

	virtual void countPrice() = 0;
protected:
	std::string name;
	std::string description;
	short size;
	float price;
	int saltCount;
	int cheeseCount;
};

class Pepperoni : public Pizza {
public:
	void countPrice() override {
		int defaultPrice = 500;
		float sizeMult = size / 2.f;
		price = defaultPrice * sizeMult + saltCount * 10 + cheeseCount * 40;
	}

	Pepperoni(short mySize, int mySaltCount, int myCheeseCount) {
		size = mySize;
		saltCount = mySaltCount;
		cheeseCount = myCheeseCount;
		name = "Pepperoni";
		description = "Regular, simple and tasty.";
		countPrice();
	}
};

class FourCheese : public Pizza {
public:
	void countPrice() override {
		int defaultPrice = 350;
		float sizeMult = size / 2.f;
		price = defaultPrice * sizeMult + saltCount * 10 + cheeseCount * 40;
	}

	FourCheese(short mySize, int mySaltCount, int myCheeseCount) {
		size = mySize;
		saltCount = mySaltCount;
		cheeseCount = myCheeseCount;
		name = "Four cheese";
		description = "Maybe, there's too much cheese...";
		countPrice();
	}
};

class Carbonara : public Pizza {
public:
	void countPrice() override {
		int defaultPrice = 650;
		float sizeMult = size / 2.f;
		price = defaultPrice * sizeMult + saltCount * 10 + cheeseCount * 40;
	}

	Carbonara(short mySize, int mySaltCount, int myCheeseCount) {
		size = mySize;
		saltCount = mySaltCount;
		cheeseCount = myCheeseCount;
		name = "Carbonara";
		description = "Pizza with an egg. Interesting choice.";
		countPrice();
	}
};

class Hawaiian : public Pizza {
public:
	void countPrice() override {
		int defaultPrice = 425;
		float sizeMult = size / 2.f;
		price = defaultPrice * sizeMult + saltCount * 10 + cheeseCount * 40;
	}

	Hawaiian(short mySize, int mySaltCount, int myCheeseCount) {
		size = mySize;
		saltCount = mySaltCount;
		cheeseCount = myCheeseCount;
		name = "Hawaiian Pizza";
		description = "Pizza with pineapples. Yes. This is a pizza with pineapples";
		countPrice();
	}
};

Pizza* makePizza(int type) {
	int salt = -1; int cheese = -1; int size = -1;
	while (salt < 0) {
		std::cout << "How much salt do you want?" << endl;
		cin >> salt;
	}
	while (cheese < 0) {
		std::cout << "How much cheese do you want?" << endl;
		cin >> cheese;
	}
	while (size < 0 || size > 4) {
		std::cout << "What size will the pizza be?\n1. 25\n2. 30\n3. 35\n4. 40" << endl << "Enter size Number: ";
		cin >> size;
	}
	switch (type) {
	case 1:
		return new Pepperoni(size, salt, cheese);
		break;
	case 2:
		return new FourCheese(size, salt, cheese);
		break;
	case 3:
		return new Carbonara(size, salt, cheese);
		break;
	case 4:
		return new Hawaiian(size, salt, cheese);
		break;
	default:
		break;
	}
	return nullptr;
}

void adding(vector<Pizza*>& order) {
	int menu; bool exit = true;
	while (exit) {
		std::cout << "1. Add Pepperoni. \n2. Add Four cheese. \n3. Add Carbonara. \n4. Add Hawaiian pizza. \n5. Back." << endl;
		cin >> menu;
		if (menu > 0 && menu < 5) {
			system("CLS");
			order.push_back(makePizza(menu));
		}
		else if (menu == 5) {
			system("CLS");
			exit = 0;
		}			
	}
}

int main()
{
	bool exit = false; bool isNotCorrect;
	int totalPrice = 0; int chosen;
	int menu;
	vector<Pizza*> order;
	
	while (!exit) {
		
		std::cout << "1. Add Pizza. \n2. Remove Pizza. \n3. Show order. \n4. New order \n5. Exit." << endl;
		cin >> menu;
		switch (menu) {
		case 1:
			system("CLS");
			adding(order);
			break;
		case 2:
			system("CLS");
			if (!order.size())
				std::cout << "Your order is empty..." << endl;
			else {
				for (int i = 0; i < order.size(); i++) {
					std::cout << i << ". " << order.at(i)->getName() << " - " << order.at(i)->getPrice() << "RUB" << endl;
				}
				isNotCorrect = false;
				do {
					std::cout << "Choose number of the pizza: ";
					cin >> chosen;
					if (chosen > order.size() || chosen < 0) {
						std::cout << "This is the wrong number." << endl;
						isNotCorrect = true;
					}
					else isNotCorrect = false;
				} while (isNotCorrect);
				order.erase(std::next(order.begin(), chosen)); //order.at(chosen)
			}
			break;
		case 3:
			system("CLS");
			totalPrice = 0;
			if (!order.size())
				std::cout << "Your order is empty..." << endl;
			else {
				std::cout << "|-------------------------|" << endl;
				for (int i = 0; i < order.size(); i++) {
					std::cout << i << ". " << order.at(i)->getName() << " - " << order.at(i)->getPrice() << "RUB" << endl;
					std::cout << "Description: " << order.at(i)->getDescription() << endl;
					std::cout << "Salt count: " << order.at(i)->getSaltCount() << " (" << order.at(i)->getSaltCount() * 10 << "RUB)" << endl;
					std::cout << "Cheese count: " << order.at(i)->getCheeseCount() << " (" << order.at(i)->getCheeseCount() * 40 << "RUB)" << endl;
					std::cout << "Size: " << 20 + (5 * order.at(i)->getSize()) << endl << endl;
					totalPrice += order.at(i)->getPrice();
				}
				std::cout << "Total price: " << totalPrice << "RUB" << endl << "|-------------------------|" << endl << endl;
			}
			break;
		case 4:
			system("CLS");
			order.clear();
			std::cout << "Your old order was dismissed. Now you can make a new order." << endl;
			break;
		case 5:
			system("CLS");
			exit = 1;
			break;
		default:
			break;
		}
	}
	std::cout << "Goodbye!" << endl;
}
