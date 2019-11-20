#include "Header.h"

int getHeight(NODE* node)
{
	if (node == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + max(getHeight(node->p_left), getHeight(node->p_right));
	}
}

int max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}

NODE* CreateNode(int data)
{
	NODE* pNode = new NODE;
	if (pNode == NULL)
	{
		cout << "Cannot create node!" << endl;
	}
	else
	{
		pNode->key = data;
		pNode->p_left = NULL;
		pNode->p_right = NULL;
		pNode->height = 1;
	}
	return pNode;
}

NODE* rightRotation(NODE* p_root)
{
	NODE* x = p_root->p_left;
	NODE* T2 = x->p_right;

	//rotate
	x->p_right = p_root;
	p_root->p_left = T2;

	//Update heights
	x->height = max(getHeight(x->p_left), getHeight(x->p_right)) + 1;
	p_root->height = max(getHeight(p_root->p_left), getHeight(p_root->p_right)) + 1;

	//return new root of tree
	return x;
}

NODE* leftRotation(NODE* p_root)
{
	NODE* x = p_root->p_right;
	NODE* T2 = x->p_left;

	//rotate
	x->p_left = p_root;
	p_root->p_right = T2;

	//Update heights
	x->height = max(getHeight(x->p_left), getHeight(x->p_right)) + 1;
	p_root->height = max(getHeight(p_root->p_left), getHeight(p_root->p_right)) + 1;

	//return new root
	return x;
}

int getBalance(NODE* node)
{
	if (node == NULL)
	{
		return 0;
	}

	return getHeight(node->p_left) - getHeight(node->p_right);
}

NODE* InsertBST(NODE*& p_root, int x)
{
	NODE* newNode = CreateNode(x);

	if (p_root == NULL)
	{
		p_root = newNode;
		return p_root;
	}

	p_root->height++;
	if (p_root->key > x)
	{
		p_root->p_left = InsertBST(p_root->p_left, x);
	}
	else if (p_root->key < x)
	{
		p_root->p_right = InsertBST(p_root->p_right, x);
	}
	else
	{
		cout << "This value existed!" << endl;
		return NULL;
	} 
	return p_root;
}

void Insert(NODE*& p_root, int x)
{
	//insert as a BST
	NODE* newNode = CreateNode(x);

	if (p_root == NULL)
	{
		p_root = newNode;
	}
	else if (p_root->key > x)
	{
		Insert(p_root->p_left, x);
	}
	else if (p_root->key < x)
	{
		Insert(p_root->p_right, x);
	}
	else
	{
		cout << "This value existed!" << endl;
		return;
	}
	//update height
	p_root->height = max(getHeight(p_root->p_left), getHeight(p_root->p_right)) + 1;

	//balance the tree
	int balance = getBalance(p_root);
	//left left case
	if (balance > 1 && x < p_root->p_left->key)
	{
		p_root = rightRotation(p_root);
	}
	//right right case
	else if (balance<-1 && x>p_root->p_right->key)
	{
		p_root = leftRotation(p_root);
	}
	//left right rotation
	else if (balance > 1 && x > p_root->p_left->key)
	{
		p_root->p_left = leftRotation(p_root->p_left);
		p_root = rightRotation(p_root);
	}
	//right left rotation
	else if (balance < -1 && x < p_root->p_right->key)
	{
		p_root->p_right = rightRotation(p_root->p_right);
		p_root = leftRotation(p_root);
	}
}

NODE* FindStandFor(NODE* nodeDelete)
{
	//tim phan tu the mang
	NODE* nodeTemp = nodeDelete->p_right;
	if (nodeTemp->p_left)
	{
		FindStandFor(nodeTemp);
	}
	else
	{
		return nodeTemp;
	}
}

NODE* Search(NODE* p_root, int x)
{
	if (p_root == NULL || p_root->key == x)
	{
		return p_root;
	}

	if (p_root->key > x)
	{
		return Search(p_root->p_left, x);
	}

	if (p_root->key < x)
	{
		return Search(p_root->p_right, x);
	}
}

void Remove(NODE*& p_root, int x)
{
	if (Search(p_root, x) == NULL)
	{
		cout << "This node doesn't exist!" << endl;
		return;
	}

	if (p_root == NULL)
	{
		cout << "Nothing to remove!" << endl;
		return;
	}

	if (p_root->key > x)
	{
		Remove(p_root->p_left, x);
	}
	else if (p_root->key < x)
	{
		Remove(p_root->p_right, x);
	}
	else
	{
		//Truong hop node can xoa co 1 con hoac khong co con
		if ((p_root->p_left == NULL) ||(p_root->p_right == NULL))
		{
			NODE* nodeTemp;
			if (p_root->p_left)
			{
				nodeTemp = p_root->p_left;
			}
			else
			{
				nodeTemp = p_root->p_right;
			}

			//truong hop khong co con
			if (nodeTemp == NULL)
			{
				nodeTemp = p_root;
				p_root = NULL;
			}
			//truong hop co 1 con
			else
			{
				*p_root = *nodeTemp;
			}
			free(nodeTemp);
		}
		//Truong hop node can xoa co 2 con
		else
		{
			NODE* nodeTemp;
			nodeTemp = FindStandFor(p_root);
			p_root->key = nodeTemp->key;
			Remove(p_root->p_right, nodeTemp->key);
		}
	}

	if (p_root == NULL) //khong co gi de can bang
	{
		return;
	} //neu cay rong thi khoi can bang

	//Dieu chinh lai cay cho can bang

	//dieu chinh lai chieu cao cua cay
	p_root->height = max(getHeight(p_root->p_left), getHeight(p_root->p_right)) + 1;

	//balance the tree
	int balance = getBalance(p_root);
	//left left case
	if (balance > 1 && getBalance(p_root->p_left) >= 0)
	{
		p_root = rightRotation(p_root);
	}
	//right right case
	else if (balance < -1 && getBalance(p_root->p_left) <= 0)
	{
		p_root = leftRotation(p_root);
	}
	//left right case
	else if (balance < -1 && getBalance(p_root->p_left) < 0)
	{
		p_root->p_left = leftRotation(p_root->p_left);
		p_root = rightRotation(p_root);
	}
	//right left case
	else if (balance < -1 && getBalance(p_root->p_right)>0)
	{
		p_root->p_right = rightRotation(p_root->p_right);
		p_root = leftRotation(p_root);
	}
}

NODE* BuildABinaryTree()
{
	int x;
	cout << "Nhap gia tri ban muon them: " << endl;
	cin >> x;
	if (x == -1000)
	{
		return NULL;
	}

	NODE* p_root = CreateNode(x);
	cout << "Nhanh trai cua " << x << ":" << endl;
	p_root->p_left = BuildABinaryTree();
	cout << "Nhanh phai cua " << x << ":" << endl;
	p_root->p_right = BuildABinaryTree();
	return p_root;
}

void FindMinAndMax(NODE* p_root, int& MIN, int& MAX)
{
	if (p_root != NULL)
	{
		if (p_root->key < MIN)
		{
			MIN = p_root->key;
		}

		if (p_root->key > MAX)
		{
			MAX = p_root->key;
		}

		FindMinAndMax(p_root->p_left, MIN, MAX);
		FindMinAndMax(p_root->p_right, MIN, MAX);
	}
}

bool IsBSTUntil(NODE* p_root, int MIN, int MAX)
{
	if (p_root == NULL)
	{
		return true;
	}

	if ((p_root->key < MIN) || (p_root->key > MAX))
	{
		return false;
	}

	bool temp1, temp2;
	temp1 = IsBSTUntil(p_root->p_left, MIN, p_root->key - 1);
	temp2 = IsBSTUntil(p_root->p_right, p_root->key + 1, MAX);

	return  temp1 && temp2;
}

bool IsBST(NODE* p_root)
{
	if (p_root == NULL)
	{
		return true;
	}

	int MIN, MAX;
	MIN = p_root->key;
	MAX = p_root->key;
	FindMinAndMax(p_root, MIN, MAX);
	return IsBSTUntil(p_root, MIN, MAX);

}

bool IsAVL(NODE* p_root)
{
	if (!IsBST(p_root))
	{
		cout << "It is not a AVL tree!" << endl;
		return false;
	}
	else
	{
		int balance = getBalance(p_root);
		if (abs(balance) <= 1)
		{
			return true;
		}
	}
	return false;
}

void NLR(NODE* p_root)
{
	if (p_root != NULL)
	{
		cout << "Key: " << p_root->key << endl;
		cout << "Height of " << p_root->key << ": " << p_root->height << endl;
		if(p_root->p_left != NULL) cout << "Left: " << p_root->p_left->key << endl;
		if (p_root->p_right != NULL) cout << "Right: " << p_root->p_right->key << endl;
		NLR(p_root->p_left);
		NLR(p_root->p_right);
	}
}

void LNR(NODE* p_root)
{
	if (p_root != NULL)
	{
		LNR(p_root->p_left);
		cout << "Key: " << p_root->key << endl;
		cout << "Height of " << p_root->key << ": " << p_root->height << endl;
		LNR(p_root->p_right);
	}
}

void LRN(NODE* p_root)
{
	if (p_root != NULL)
	{
		LRN(p_root->p_left);
		LRN(p_root->p_right);
		cout << "Key: " << p_root->key << endl;
		cout << "Height of " << p_root->key << ": " << p_root->height << endl;
	}
}

void LevelOrder(NODE* p_root)
{
	if (p_root == NULL)
	{
		cout << "The tree has no node!" << endl;
		return;
	}

	queue<NODE*> q;
	//Firstly, we need push the root to the queue
	q.push(p_root);

	//Then traverse the tree
	while (!q.empty())
	{
		NODE* node = q.front();
		cout << node->key << " ";
		q.pop();

		if (node->p_left != NULL)
		{
			q.push(node->p_left);
		}

		if (node->p_right != NULL)
		{
			q.push(node->p_right);
		}

	}
}

void BackToMenu(NODE*& p_root)
{
	int select;
	do
	{
		cout << endl;
		cout << "==================================" << endl;
		cout << "1. Quay tro lai menu." << endl;
		cout << "2. Thoat." << endl;
		cout << "Lua chon: ";
		cin >> select;
		if (select == 1)
		{
			RunMenu(p_root);
		}
		else if (select == 2)
		{
			return;
		}
		else
		{
			cout << "Lua chon khong hop le! " << endl;
		}
	} while (select < 1 || select>2);
}

void BuildAVLTree(NODE*& p_root)
{
	int n;

	cout << "So phan tu ban muon them vao cay AVL: ";
	cin >> n;
	int* a = new int[n];

	cout << "Nhap cac phan tu do: " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "Phan tu thu " << i + 1 << ": ";
		cin >> a[i];
		Insert(p_root, a[i]);
	}
}

void RunMenu(NODE*& p_root)
{
	int select, x;

	do
	{
		system("cls");
		cout << "----------------MENU----------------" << endl << endl;
		cout << "1. Tao 1 cay AVL." << endl;
		cout << "2. Duyet cay theo kieu NLR." << endl;
		cout << "3. Duyet cay theo kieu LNR." << endl;
		cout << "4. Duyet cay theo kieu LRN." << endl;
		cout << "5. Duyet cay theo tung tang." << endl;
		cout << "6. Them 1 node vao cay." << endl;
		cout << "7. Xoa 1 node khoi cay." << endl;
		cout << "8. Kiem tra 1 cay nhi phan co phai cay AVL." << endl;
		cout << "9. Thoat." << endl;
		cout << "Lua chon: " << endl;
		cin >> select;
		if (select == 1)
		{
			p_root = NULL;
			system("cls");
			BuildAVLTree(p_root);
			BackToMenu(p_root);
		}
		else if (select == 2)
		{
			system("cls");
			cout << "Duyet cay theo kieu Node-Left-Right: " << endl;
			NLR(p_root);
			BackToMenu(p_root);
		}
		else if (select == 3)
		{
			system("cls");
			cout << "Duyet cay theo kieu Left-Node-Right: " << endl;
			LNR(p_root);
			BackToMenu(p_root);
		}
		else if (select == 4)
		{
			system("cls");
			cout << "Duyet cay theo kieu Left-Right-Node: " << endl;
			LRN(p_root);
			BackToMenu(p_root);
		}
		else if (select == 5)
		{
			system("cls");
			cout << "Duyet cay theo tung tang: " << endl;
			LevelOrder(p_root);
			BackToMenu(p_root);
		}
		else if (select == 6)
		{
			system("cls");
			int x;
			cout << "Nhap gia tri ban muon them vao cay: ";
			cin >> x;
			Insert(p_root, x);
			BackToMenu(p_root);
		}
		else if (select == 7)
		{
			system("cls");
			int x;
			cout << "Nhap gia tri ban muon xoa: ";
			cin >> x;
			Remove(p_root, x);
			BackToMenu(p_root);
		}
		else if (select == 8)
		{
			system("cls");
			cout << "Moi tao mot cay." << endl;
			cout << "Luu y: Nhap -1000 de chi phan tu rong!" << endl;
			NODE* p_root1;
			p_root1 = BuildABinaryTree();
			if (IsAVL(p_root1))
			{
				cout << "Day la 1 cay AVL!" << endl;
			}
			else
			{
				cout << "Day khong phai la 1 cay AVL!" << endl;
			}
			BackToMenu(p_root);
		}
		else if (select == 9)
		{
			return;
		}
		else
		{
			cout << "Lua chon khong hop le! " << endl;
		}
	} while (select < 1 || select > 9);
}

