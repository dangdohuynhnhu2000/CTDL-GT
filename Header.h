#pragma once
#include <math.h>
#include <queue>
#include <conio.h>
#include <iostream>
using namespace std;

struct NODE
{
	int key;
	NODE* p_left;
	NODE* p_right;
	int height = 1;
};

int getHeight(NODE* node);
int max(int a, int b);
NODE* rightRotation(NODE* p_root);
NODE* leftRotation(NODE* p_root);
int getBalance(NODE* node);

NODE* CreateNode(int data);
NODE* InsertBST(NODE*& p_root, int x);
void Insert(NODE*& p_root, int x);
NODE* FindStandFor(NODE* nodeDelete);
NODE* Search(NODE* p_root, int x);
void Remove(NODE*& p_root, int x);
NODE* BuildABinaryTree();
void FindMinAndMax(NODE* p_root, int& MIN, int& MAX);
bool IsBSTUntil(NODE* p_root, int MIN, int MAX);
bool IsBST(NODE* p_root);
bool IsAVL(NODE* p_root);
void NLR(NODE* p_root);
void LNR(NODE* p_root);
void LRN(NODE* p_root);
void LevelOrder(NODE* p_root);
void BackToMenu(NODE*& p_root);
void RunMenu(NODE*& p_root);