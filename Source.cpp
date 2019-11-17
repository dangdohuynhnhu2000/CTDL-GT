#include "Header.h"

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
	}
	return pNode;
}

void NLR(NODE* p_root)
{
	if (p_root != NULL)
	{
		cout << p_root->key << " ";
		NLR(p_root->p_left);
		NLR(p_root->p_right);
	}
}

void LNR(NODE* p_root)
{
	if (p_root != NULL)
	{
		LNR(p_root->p_left);
		cout << p_root->key << " ";
		LNR(p_root->p_right);
	}
}

void LRN(NODE* p_root)
{
	if (p_root != NULL)
	{
		LRN(p_root->p_left);
		LRN(p_root->p_right);
		cout << p_root->key << " ";
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
		return Search(p_root->p_right, x);
	}

	if (p_root->key < x)
	{
		return Search(p_root->p_left, x);
	}
}

int Height(NODE* p_root)
{
	int leftHeight = 0, rightHeight = 0;
	if (p_root == NULL)
	{
		return 0;
	}

	leftHeight = Height(p_root->p_left);
	rightHeight = Height(p_root->p_right);
	
	if (leftHeight > rightHeight)
	{
		return 1 + leftHeight;
	}
	else
	{
		return 1 + rightHeight;
	}
}

void Insert(NODE*& p_root, int x)
{
	NODE* newNode = CreateNode(x);

	if (p_root == NULL)
	{
		p_root = newNode;
		return;
	}

	if (p_root->key > x)
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
	}
}

void FindStandFor(NODE*& nodeDelete, NODE*& nodeTemp)
{
	//tim phan tu the mang
	if (nodeTemp->p_left) 
	{
		FindStandFor(nodeDelete, nodeTemp->p_left);
	}
	else
	{
		//dua gia tri cua nut the mang len nut can xoa
		nodeDelete->key = nodeTemp->key;

		//nut can xoa bay gio la nut the mang
		nodeDelete = nodeTemp;

		//noi node phai cua nut the mang voi cha cua node the mang
		//node con nay bay gio thay the cua node the mang
		nodeTemp = nodeTemp->p_right;
	}
}

void Remove(NODE*& p_root, int x)
{
	NODE* nodeDelete = p_root;

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
		if (p_root->p_left == NULL)
		{
			p_root = p_root->p_right;
		}
		else if (p_root->p_right == NULL)
		{
			p_root = p_root->p_left;
		}
		//Truong hop node can xoa co 2 con
		else
		{
			NODE* nodeTemp = p_root->p_right;
			FindStandFor(nodeDelete, nodeTemp);
		}

		free(nodeDelete);
	}
}

void FindMinAndMax(NODE* p_root, int MIN, int MAX)
{
	MIN = p_root->key;
	MAX = p_root->key;

	//duyet theo kieu NLR
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

		NLR(p_root->p_left);
		NLR(p_root->p_right);
	}
}

bool IsBSTUntil(NODE* p_root, int MIN, int MAX)
{
	if (p_root == NULL)
	{
		return true;
	}

	if ((p_root->key < MIN) && (p_root->key > MAX))
	{
		return false;
	}

	return IsBSTUntil(p_root->p_left, MIN, MAX) && IsBSTUntil(p_root->p_right, MIN, MAX);
}

bool IsBST(NODE* p_root)
{
	if (p_root == NULL)
	{
		return true;
	}

	int MIN = 0, MAX = 0;
	FindMinAndMax(p_root, MIN, MAX);
	return IsBSTUntil(p_root, MIN, MAX);
}

int CountNode(NODE* p_root)
{
	int count = 1;
	if (p_root == NULL)
	{
		return 0;
	}

	if (p_root->p_left != NULL)
	{
		count += CountNode(p_root->p_left);
	}

	if (p_root->p_right != NULL)
	{
		count += CountNode(p_root->p_right);
	}

	return count;
}

void BuildABST(NODE*& p_root)
{
	int n;

	cout << "So phan tu ban muon them vao BST: ";
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

void RunMenu()
{
	int select, x;
	NODE* p_root = NULL;

	do
	{
		cout << "1. Tao 1 cay nhi phan can bang." << endl;
		cout << "2. Duyet cay theo kieu NLR." << endl;
		cout << "3. Duyet cay theo kieu LNR." << endl;
		cout << "4. Duyet cay theo kieu LRN." << endl;
		cout << "5. Tim tren cay." << endl;
		cout << "6. Tinh chieu cao cua cay." << endl;
		cout << "7. Them 1 node vao cay." << endl;
		cout << "8. Xoa 1 node khoi cay." << endl;
		cout << "9. Kiem tra 1 cay co phai cay BST." << endl;
		cout << "10. Dem so node tren cay." << endl;
		cout << "11. Thoat." << endl;
		cout << "Lua chon: " << endl;
		cin >> select;
		if (select == 1)
		{
			system("cls");
			BuildABST(p_root);
			BackToMenu();
		}
		else if (select == 2)
		{
			system("cls");
			cout << "Duyet cay theo kieu Node-Left-Right: " << endl;
			NLR(p_root);
			BackToMenu();
		}
		else if (select == 3)
		{
			system("cls");
			cout << "Duyet cay theo kieu Left-Node-Right: " << endl;
			LNR(p_root);
			BackToMenu();
		}
		else if (select == 4)
		{
			system("cls");
			cout << "Duyet cay theo kieu Left-Right-Node: " << endl;
			LRN(p_root);
			BackToMenu();
		}
		else if (select == 5)
		{
			system("cls");
			NODE* nodeSearch;
			cout << "Nhap gia tri ban muon tim vao cay: ";
			cin >> x;
			nodeSearch = Search(p_root, x);
			if (nodeSearch == NULL)
			{
				cout << "Khong tim thay!" << endl;
			}
			else
			{
				cout << "Node can tim ton tai tren cay!" << endl;
			}
			BackToMenu();
		}
		else if (select == 6)
		{
			system("cls");
			int height;
			height = Height(p_root);
			cout << "Chieu cao cua cay la: " << height << endl;
			BackToMenu();
		}
		else if (select == 7)
		{
			system("cls");
			int x;
			cout << "Nhap gia tri ban muon them vao cay: ";
			cin >> x;
			Insert(p_root, x);
			BackToMenu();
		}
		else if (select == 8)
		{
			system("cls");
			cout << "Nhap gia tri ban muon xoa khoi cay: ";
			cin >> x;
			if (Search(p_root, x) == NULL)
			{
				cout << "Node can xoa khong ton tai tren cay!" << endl;
			}
			else
			{
				Remove(p_root, x);
			}
			BackToMenu();
		}
		else if (select == 9)
		{
			system("cls");
			cout << "Moi tao mot cay." << endl;
			NODE* p_root1 = new NODE;
			BuildABST(p_root1);
			if (IsBST(p_root1))
			{
				cout << "Day la 1 cay nhi phan can bang!" << endl;
			}
			else
			{
				cout << "Day khong phai la 1 cay nhi phan can bang!" << endl;
			}
			BackToMenu();
		}
		else if (select == 10)
		{
			system("cls");
			cout << "So node tren cay la: " << CountNode(p_root) << endl;
			BackToMenu();
		}
		else if (select == 11)
		{
			return;
		}
		else
		{
			cout << "Lua chon khong hop le! " << endl;
		}
	} while (select < 1 || select > 11);
}

void BackToMenu()
{
	system("cls");
	int select;
	do 
	{
		cout << "==================================" << endl;
		cout << "1. Quay tro lai menu." << endl;
		cout << "2. Thoat." << endl;
		cout << "Lua chon: ";
		cin >> select;
		if (select == 1)
		{
			RunMenu();
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