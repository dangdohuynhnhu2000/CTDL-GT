#pragma once
#include <conio.h>
#include <iostream>
using namespace std;

struct NODE
{
	int key;
	NODE* p_left;
	NODE* p_right;
};

NODE* CreateNode(int data);

void NLR(NODE* p_root);
void LNR(NODE* p_root);
void LRN(NODE* p_root);

NODE* Search(NODE* p_root, int x);
int Height(NODE* p_root);
void Insert(NODE*& p_root, int x);
//Tim phan tu the mang
void FindStandFor(NODE*& nodeDelete, NODE*& nodeTemp);
void Remove(NODE*& p_root, int x);
//Tim phan tu lon nhat tren cay va nho nhat tren cay
void FindMinAndMax(NODE* p_root, int MIN, int MAX);
bool IsBSTUntil(NODE* p_root, int MIN, int MAX);
bool IsBST(NODE* p_root);
int CountNode(NODE* p_root);
void BuildABST(NODE* &p_root); 

void RunMenu();
void BackToMenu();