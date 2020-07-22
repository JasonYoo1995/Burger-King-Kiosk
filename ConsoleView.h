#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "Product.h"
#include "Data.h"
#include "FileManager.h"
using namespace std;

class ConsoleView {
private:
	Data* data;
	FileManager* fm;
	char input = '0';
	int page = 0;
	boolean burger = false;
	boolean side = false;
	boolean drink = false;
	boolean sold_out = false; // ǰ��Ȯ�� (����)
	char comboAndSet;
	char option;// � ī�װ��� �����ߴ���
	char change_option; // � ��ǰ �������� (����)
	int incresedCartSize = 0; // �Է½� �þ�� īƮ ������ üũ
	// ����
	int soldout = 0; // ǰ��Ȯ�� 1�϶� ǰ��
	int cartkcal = 0; // ���õ� ��ǰ���� �� Į�θ� 
	int cartprice = 0; // ���õ� ��ǰ���� �� ����
	int totalkcal = 0; // ��ü ��ǰ���� �� Į�θ�
	int totalprice = 0; // ��ü ��ǰ���� �� ����
	// ����

public:
	ConsoleView(Data* data, FileManager* fm);
	void gotoxy(short x, short y);
	void showUI();
	int userUI0();
	int userUI1();
	int userUI2();
	int userUI3();
	int userUI4();
	// ����
	void print_carts_elements(vector<Product>& list); // īƮ �ȿ��� ��ǰ ǥ��
	void print_all_elements(vector<Product>& list); // �ʱ�ȭ��, ����â ��ǰ ǥ��
	void print_total(vector<vector<Product>> cartList);  // ����â ��� īƮ�� Į�θ�, ���� �� ǥ��
	// ����
	int userUI5();
	int userUI6();
	int helpUI();
	int adminUI0();
	int adminUI1();
	int adminUI2();
	int adminUI3();
	int adminUI4();
	int adminUI5(); /*���*/
	void line_clear();
	void console_clear();
	void border_above();
	void border_bottom();
	void pay();
	void inputs();
};
