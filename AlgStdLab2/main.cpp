#include <iostream>
#include <string>
#include <vector>
#include "AVLTree.h"

using namespace std;

bool InputValue(int& value)
{
	string input;
	bool flag = true;
	while (true)
	{
		getline(cin, input);
		flag = true;
		if (input == "")
		{
			return false;
		}
		else
		{
			for (int i = 0; i < input.length(); i++)
			{
				if (!isdigit(input[i]))
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				if (stoi(input) > 0)
					value = stoi(input);
				break;
			}
		}
		cout << "Введен недопустимый символ! Повторите ввод!" << endl;
	}
	return true;
}

void output(AVLTree<int>::Node* p, int n)
{
	if (p == NULL)
		return;

	if (n == 1)
	{
		cout << " " << p->key << " "; //вывод значения
		return;
	}
	output(p->left, n - 1); //рекурсивные вызовы
	output(p->right, n - 1);
	return;
}


int main()
{
	setlocale(LC_ALL, "ru");
	AVLTree<int> *test;
	vector<int> numbers;
	
	cout << "Введите числа:" << endl;
	
	int value;
	while (InputValue(value))
		numbers.push_back(value);
	
	test = new AVLTree<int>(numbers[0]);

	for (int i = 1; i < numbers.size(); i++)
		test->insert(numbers[i]);

	int deep = test->getHeight();

	for (int i = 1; i <= deep; i++)
	{
		output(test->getNode(), i);
		cout << endl;
	}
	

	return 0;
}