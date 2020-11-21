#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std;

namespace market {

	class produce
	{
	public:
		string name;
		int qty;
		double price;
		produce(string name, int qty, float price);
		~produce();
	};

	float getPrice(unordered_map<string, float> stock, string item, int quantity);
	float applyDiscount(vector<produce> v, vector<string> dealItems);
}