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
	boolean sold_out = false; // 품절확인 (본승)
	char comboAndSet;
	char option;// 어떤 카테고리를 선택했는지
	char change_option; // 어떤 제품 변경할지 (본승)
	int incresedCartSize = 0; // 입력시 늘어나는 카트 사이즈 체크
	// 본승
	int soldout = 0; // 품절확인 1일때 품절
	int cartkcal = 0; // 선택된 제품들의 총 칼로리 
	int cartprice = 0; // 선택된 제품들의 총 가격
	int totalkcal = 0; // 전체 제품들의 총 칼로리
	int totalprice = 0; // 전체 제품들의 총 가격
	// 본승

public:
	ConsoleView(Data* data, FileManager* fm);
	void gotoxy(short x, short y);
	void showUI();
	int userUI0();
	int userUI1();
	int userUI2();
	int userUI3();
	int userUI4();
	// 본승
	void print_carts_elements(vector<Product>& list); // 카트 안에서 제품 표시
	void print_all_elements(vector<Product>& list); // 초기화면, 결제창 제품 표시
	void print_total(vector<vector<Product>> cartList);  // 결제창 모든 카트의 칼로리, 가격 합 표시
	// 본승
	int userUI5();
	int userUI6();
	int helpUI();
	int adminUI0();
	int adminUI1();
	int adminUI2();
	int adminUI3();
	int adminUI4();
	int adminUI5(); /*경원*/
	void line_clear();
	void console_clear();
	void border_above();
	void border_bottom();
	void pay();
	void inputs();
};
