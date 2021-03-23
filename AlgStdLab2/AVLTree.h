#pragma once
#define NULL 0

template<typename T>
class AVLTree
{
public:
	struct Node
	{
		T key;
		unsigned char height;
		Node* left;
		Node* right;
		Node(T k) { key = k; left = right = 0; height = 1; }

	};

	AVLTree(const T &firstValue);

	// ������ ��� ������� ����
	Node* insert(const T& value, Node* p);
	Node* remove(const T& value, Node* p);
	int getHeight(Node* p) const;

	// ������ ��� ������� ������
	Node* insert(const T& value);
	Node* remove(const T& value);
	int getHeight() const;

	Node* getNode() const;

private:
	// ��������� ��� ������������� ����� ������
	Node* node;

	unsigned char height(Node* p);
	int bFactor(Node* p);
	void fixHeight(Node* p);
	Node* rotateRight(Node* p);
	Node* rotateLeft(Node* p);
	Node* balance(Node* p);
	Node* findMin(Node* p);
	Node* removeMin(Node* p);
};

template<typename T>
AVLTree<T>::AVLTree(const T& firstValue)
{
	node = new Node(firstValue);
}

template<typename T>
unsigned char AVLTree<T>::height(Node* p)
{
	return p ? p->height : 0;
}

template<typename T>
int AVLTree<T>::bFactor(Node* p)
{
	return height(p->right) - height(p->left);
}

template<typename T>
void AVLTree<T>::fixHeight(Node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::rotateRight(Node* p) // ������ ������� ������ p
{
	Node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixHeight(p);
	fixHeight(q);
	return q;
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::rotateLeft(Node* q) // ����� ������� ������ q
{
	Node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixHeight(q);
	fixHeight(p);
	return p;
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::balance(Node* p) // ������������ ���� p
{
	fixHeight(p);
	if (bFactor(p) == 2)
	{
		if (bFactor(p->right) < 0)
			p->right = rotateRight(p->right);
		return rotateLeft(p);
	}
	if (bFactor(p) == -2)
	{
		if (bFactor(p->left) > 0)
			p->left = rotateLeft(p->left);
		return rotateRight(p);
	}
	return p; // ������������ �� �����
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::insert(const T& k, Node* p) // ������� ����� k � ������ � ������ p
{
	if (!p) return new Node(k);
	if (k < p->key)
		p->left = insert(k, p->left);
	else
		p->right = insert(k, p->right);
	node = balance(p);
	return node;
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::findMin(Node* p) // ����� ���� � ����������� ������ � ������ p 
{
	return p->left ? findMin(p->left) : p;
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::removeMin(Node* p) // �������� ���� � ����������� ������ �� ������ p
{
	if (p->left == 0)
		return p->right;
	p->left = removeMin(p->left);
	return balance(p);
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::remove(const T& k, Node* p) // �������� ����� k �� ������ p
{
	if (!p) return 0;

	if (k < p->key)
		p->left = remove(k, p->left);
	else if (k > p->key)
		p->right = remove(k, p->right);
	else //  k == p->key 
	{
		Node* q = p->left;
		Node* r = p->right;
		delete p;
		if (!r)
			return q;//���� ������ ����� - �� ������� ������
		//��� - �� ��� ����� ������ ���������� ����
		Node* min = findMin(r);//������� ����������� ��-� � ������ ���������, ���� ��� ����
		min->right = removeMin(r);//������� ���
		min->left = q;//������������ ������ ��������� �������, ������� ����� ������ ���������
		return balance(min);//������������ ��������� �� ����� �������
	}
	node = balance(p);
	return node;
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::getNode() const
{
	return node;
}

template<typename T>
int AVLTree<T>::getHeight(Node* p) const
{
	int k1, k2;

	if (p == NULL)
		return 0;

	k1 = getHeight(p->left);
	k2 = getHeight(p->right);

	if (k1 > k2)
		return (k1 + 1);

	return (k2 + 1);
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::insert(const T& value)
{
	return insert(value, node);
}

template<typename T>
typename AVLTree<T>::Node* AVLTree<T>::remove(const T& value)
{
	return remove(value, node);
}

template<typename T>
int AVLTree<T>::getHeight() const
{
	return getHeight(node);
}