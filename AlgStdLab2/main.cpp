#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct node // структура для представления узлов дерева
{
	int key;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; }
};

unsigned char height(node* p)
{
	return p?p->height:0;
}

int bfactor(node* p)
{
	return height(p->right)-height(p->left);
}

void fixheight(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // балансировка узла p
{
	fixheight(p);
	if( bfactor(p)==2 )
	{
		if( bfactor(p->right) < 0 )
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if( bfactor(p)==-2 )
	{
		if( bfactor(p->left) > 0  )
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
	if( !p ) return new node(k);
	if( k<p->key )
		p->left = insert(p->left,k);
	else
		p->right = insert(p->right,k);
	return balance(p);
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left?findmin(p->left):p;
}

node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, int k) // удаление ключа k из дерева p
{
	if( !p ) return 0;
	if( k < p->key )
		p->left = remove(p->left,k);
	else if( k > p->key )
		p->right = remove(p->right,k);	
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if( !r ) 
			return q;//если справа пусто - то возврат левого
		//мин - то что будет вместо удаленного узла
		node* min = findmin(r);//находим минимальный эл-т в правом поддереве, если оно есть
		min->right = removemin(r);//удаляем его
		min->left = q;//приписывание левого поддерева вершине, которая будет вместо удаленной
		return balance(min);//балансировка поддерева от новой вершины
	}
	return balance(p);
}

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
int main()
{
	setlocale(LC_ALL, "ru");
	node* test;
	vector<int> numbers;
	int value;
	
	cout << "Введите числа:" << endl;
	
	while (true)
	{
		if (InputValue(value))
		{
			numbers.push_back(value);
		}
		else
		{
			break;
		}

	}
	
	test = new node(numbers[0]);

	for (int i = 1; i < numbers.size(); i++)
	{
		test = insert(test, numbers[i]);
	}









	return 0;
}