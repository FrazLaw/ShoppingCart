#include "produce.h"

using namespace market;

produce::produce(string name, int qty, float price)
{
	this->name = name;
	this->qty = qty;
	this->price = price;
}

produce::~produce()
{
}

float market::getPrice(unordered_map<string, float> stock, string item, int quantity)
{
	float price = 0.0;
	unordered_map<string, float>::iterator it;
	it = stock.find(item);
	if (it != stock.end())
	{
		price = it->second;
	}
	return price;
}

float market::applyDiscount(vector<produce> v, vector<string> dealItems)
{
	float deductions = 0;
	int len = v.size();

	unordered_map<string, int> discMp;

	for (int k = 0; k < len; k++)
	{
		discMp[v[k].name] += v[k].qty;
	}

	//iterator will iterate through the size of the vector, as will k
	int k = 0;
	float discount = 1.0 / 3.0;

	//pay for 2/3 discount
	for (auto it = discMp.begin(); it != discMp.end(); it++)
	{
		int conv = 0;
		if (it->second % 3 == 0 && it->second < 4)
		{
			deductions += v[k].qty * v[k].price * discount;

		}
		else if (it->second > 3)
		{
			int deduct = it->second % 3;
			//wee bug here where i had v[k].qty instead of the actual quantity stored in the value of the node
			conv = it->second - deduct;
			deductions += conv * v[k].price * discount;
		}
		k++;
	}

	//applying the set deal
	unordered_map<string, int>::iterator d;
	int dealApplicableFlag = 3;
	int result_Qty = INT_MAX;
	float result_Price = FLT_MAX;
	int dealLen = dealItems.size();

	int minQty = 0;
	for (int i = 0; i < dealLen; i++)
	{
		d = discMp.find(dealItems[i]);
		if (d != discMp.end())
		{
			//if found, reduce flag val
			dealApplicableFlag--;
			//using the same loop to find the minimum number of sets for the deal to apply	
			minQty = d->second;
			//for  each vector<produce> object, check if the item is on the deal
			for (int j = 0; j < len; j++)
			{

				if (dealItems[i] == v[j].name)
				{
					float minPrice = v[j].price;

					result_Price = min(result_Price, minPrice);
				}
			}
			//only the min quantity need be applied for the deal, also catches '0' entries
			result_Qty = min(result_Qty, minQty);
		}
	}

	if (dealApplicableFlag == 0)
	{
		deductions += result_Qty * result_Price;
	}

	return deductions;
}
