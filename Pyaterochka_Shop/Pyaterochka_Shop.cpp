// Pyaterochka_Shop.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "2ЛАБ.h";
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

class Record {
public:
	int id;
	std:: string name;
	double price;

	Record(const int& i,const std::string& n,const double pr) :id(i), name(n),price(pr) {} //id(id), name(n), price(price) {}
	

	virtual void display() const {
		std::cout << "Base Record";
	}
	const std::string& GetName() const {
		return name;
	}

	const double& GetPrice() const {
		return price;
	}
	const double& GetId() const {
		return id;
	}
};

std::vector<Record*> Product_Database;
std::vector<Record*> Cart;
My_Array<int, 1000> pos;/// my_array
class EdibleProduct: public Record {

public:
	EdibleProduct(int& id, std::string& name, double& price) :Record(id,name,price) {}
		//Record(id), Record(name), Record(price){}



	void display() const override {
		std::cout<< "Id:"<<id << "    Name:    " << name << "   Price: " << price ;
	}
};

class NonEdibleProduct : public Record {
private:
	int random = std::rand() % 10 + 1;
public:
	NonEdibleProduct(int& id, std::string& name, double& price) :Record(id, name, price) {}
	//Record(id), Record(name), Record(price){}



	void display() const override {
		std::cout << "Id:" << id << "    Name:    " << name << "   Price: " << price << "  Discount:  " <<random<<"%" ;
	}
};





class Account {
	void Login() {};
	void Register() {};
	void LogOut() {};



};

class Administrator : public Account {
private:
	int id;
	std::string name;
public:
	void CallSupply() {};
	void Access_Products() {};

};

class Customer : public Account {
private:
	int id;
	std::string name;
	int points;
public:
	void AddtoCart() {};
	void BuyProduct() {};

};




void print(const Record& product) {
	product.display();
}


void  SearchProductByPrice(const std::vector<Record*> elements, const double pr) {
	bool a = 0;
	for (int i = 0; i < size(elements); i++) {
		if (elements[i]->GetPrice() == pr) {
			a = 1;
			print(*elements[i]);
			//std::cout << "Name: " << Process(*elements[i]).GetName() << "    Price: " << Process(*elements[i]).GetPrice() << std::endl;
		}

	}
	if (!a) std::cout << "No such Product" << std::endl;

}


void  SearchProductById(const std::vector<Record*> elements, const int id) {
	bool a = 0;
	for (int i = 0; i < size(elements); i++) {
		if (elements[i]->GetId() == id) {
			a = 1;
			print(*elements[i]);
			//std::cout << "Name: " << Process(*elements[i]).GetName() << "    Price: " << Process(*elements[i]).GetPrice() << std::endl;
		}

	}
	if (!a) std::cout << "No such Product" << std::endl;

}

void  ChangeProductName(Record& element,  std::string name) {
	bool a = 0;
	
	element.name = name;
			a = 1;
			print(element);
			//std::cout << "Name: " << Process(*elements[i]).GetName() << "    Price: " << Process(*elements[i]).GetPrice() << std::endl;
		

	
	if (!a) std::cout << "No such Product" << std::endl;

}

void  ChangeProductPrice(Record& element, double price) {
	bool a = 0;

	element.price = price;
	a = 1;
	print(element);
	//std::cout << "Name: " << Process(*elements[i]).GetName() << "    Price: " << Process(*elements[i]).GetPrice() << std::endl;



	if (!a) std::cout << "No such Product" << std::endl;

}



void  SearchProductByName(const std::vector<Record*> elements, const std::string name) {
	bool a=0;
	for (int i = 0; i < size(elements); i++) {
		if (elements[i]->GetName() == name) {
			a = 1;
			print(*elements[i]);
			//std::cout << "Name: " << Process(*elements[i]).GetName() << "    Price: " << Process(*elements[i]).GetPrice() << std::endl;
	}
		
	}
	if (!a) std::cout << "No such Product" << std::endl;
	
}
int id=1;
void EdibleProductsInput(std::vector<Record*>& record) {
	std::ifstream file("EdibleProductInput.txt");
	std::string str;
	std::string name;
	//int id=1;
	double price;
	while (!file.eof()) {
		std::getline(file, str, ' ');
		if (str != "") {
			//id = std::stoi(str);
			//std::getline(file, str, ' ');
			name = str;
			std::getline(file, str, '\n');
			price = std::stod(str);
			record.push_back(new EdibleProduct(id, name, price));
			id++;
		}

	}
}

void NonEdibleProductsInput(std::vector<Record*>& record) {
	std::ifstream file("NonEdibleProductInput.txt");
	std::string str;
	std::string name;
	//int id=1;
	double price;
	while (!file.eof()) {
		std::getline(file, str, ' ');
		if (str != "") {
			
			//std::getline(file, str, ' ');
			name = str;
			std::getline(file, str, '\n');
			price = std::stod(str);
			record.push_back(new NonEdibleProduct(id, name, price));
			id++;
		}

	}
}
int ids=0;

void CartInput(std::vector<Record*> elements, std::vector<Record*>& Cart,std::string name,My_Array<int,1000>& position) {/// my_array
	bool a = 0;
	for (int i = 0; i < size(elements); i++) {
		if (elements[i]->GetName() == name) {
			a = 1;
			Cart.push_back(elements[i]);
			ids++;
			position.push(ids);/// my_array
			//Process(*Cart[i]).display();
			//std::cout << "Name: " << Process(*elements[i]).GetName() << "    Price: " << Process(*elements[i]).GetPrice() << std::endl;
		}

	}
	if (!a) std::cout << "No such Product" << std::endl;

}

void DeleteByName(std::vector<Record*>& elements, std::string name,My_Array<int, 1000>& position) {/// my_array
	bool a = 0;
	for (int i = 0; i < size(elements); i++) {
		if (elements[i]->GetName() == name) {
			a = 1;
			elements.erase(elements.begin()+i);
			position.erase(i);/// my_array
			ids--;
			//Process(*Cart[i]).display();
			//std::cout << "Name: " << Process(*elements[i]).GetName() << "    Price: " << Process(*elements[i]).GetPrice() << std::endl;
		}

	}
	if (!a) std::cout << "No such Product" << std::endl;

}






int StartPrint() {
	int flag;
	std::cout << "Choose what to do" << std::endl;
	std::cout << "Please log in or Register: " <<std:: endl;
	std::cout << "1. Log as admin" << std::endl;
	std::cout << "2. Log as customer" << std::endl;
	std::cout << "3. Exit. " << std::endl;
	std::cin >> flag;
	return flag;
}


int AdminPrint() {
	int flag1;
	std::cout <<  std::endl;
	std::cout << "Choose what to do" << std::endl;
	std::cout << "1. Print ProductDatabase" << std::endl;
	std::cout << "2. Search for product by name" << std::endl;
	std::cout << "3. Search for product by id" << std::endl;
	std::cout << "4. Search for product by price" << std::endl;
	std::cout << "5. Change product name. " << std::endl;
	std::cout << "6. Change product price. " << std::endl;
	std::cout << "7. Log out " << std::endl;
	std::cin >> flag1;
	return flag1;
}


int CustomerPrint() {
	int flag2;
	std::cout << std::endl;
	std::cout << "Choose what to do" << std::endl;
	std::cout << "1. Print ProductDatabase" << std::endl;
	std::cout << "2. Search for product by name" << std::endl;
	std::cout << "3. Search for product by price" << std::endl;
	std::cout << "4. Add product to cart. " << std::endl;
	std::cout << "5.Print cart. " << std::endl;
	std::cout << "6.Remove product from cart " << std::endl;
	std::cout << "7.Log Out " << std::endl;
	std::cin >> flag2;
	return flag2;
}




void start() {
	int flag{ 0 };
	int flag1{ 0 };
	int flag2{ 0 };
	std::string nam;
	
	int j;
	double p;
	do {
		switch (StartPrint())
		{
		case 1:flag = 3;
			do {
				switch (AdminPrint()) {
				case 1:
					for (const auto& record : Product_Database) {
						record->display();
					}
					break;
				case 2:

					std::cin >> nam;
					SearchProductByName(Product_Database, nam);
					break;
				case 3:
					std::cin >> j;
					SearchProductById(Product_Database, j);
					break;
				case 4:
					std::cin >> p;
					SearchProductByPrice(Product_Database, p);
					break;
				case 5:
					std::cout << "Name:" << std::endl;
					std::cin >> nam;
					std::cout << "Id:" << std::endl;
					std::cin >> j;
					ChangeProductName(*Product_Database[j - 1], nam);
					break;
				case 6:
					std::cout << "Price:" << std::endl;
					std::cin >> p;
					std::cout << "Id:" << std::endl;
					std::cin >> j;
					ChangeProductPrice(*Product_Database[j - 1], p);
					break;

				default:
					flag1 = 8;
				}
			} while (flag1 != 8);
		case 2: flag = 3;
			do {
				switch (CustomerPrint()) {
				case 1:
					for (const auto& record : Product_Database) {
						record->display();
					}
					break;
				case 2:

					std::cin >> nam;
					SearchProductByName(Product_Database, nam);
					break;

				case 3:
					std::cin >> p;
					SearchProductByPrice(Product_Database, p);
					break;
				case 4:
					std::cin >> nam;
					CartInput(Product_Database, Cart, nam,pos);
					break;
				case 5: {My_Array < int, 1000 > ::Iterator i = pos.begin();/// my_array
					for (const auto& record : Cart) {
						record->display();
						//for (My_Array < int, 1000 > ::Iterator i = pos.begin(); i < pos.end(); i++) {

						std::cout << "   pos:" << *i << " ";/// my_array
						i++;/// my_array
						//	break;

						//}
						std::cout << "\n";
					}
					}
					break;
				case 6:
					std::cin >> nam;
					DeleteByName(Cart, nam,pos);/// my_array


					break;
				default:
					flag2 = 6;
				}
				} while (flag2 != 6);
				break;

		default:
			flag = 8;
			}
		} while (flag != 8);

	}

int main()
{
	
	std::srand(std::time(0));
	
	EdibleProductsInput(Product_Database);
	NonEdibleProductsInput(Product_Database);
	
	start();


}


