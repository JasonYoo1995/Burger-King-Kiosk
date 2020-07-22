#pragma once
#include <iostream>
#include "Product.h"
#include "FileManager.h"
using namespace std;

#define BREAD 0
#define CHEESE 1
#define TOMATO 2
#define LETTUCE 3
#define SOURCE 4
#define MEAT 5
#define SHRIMP 6
#define CHICKEN 7
#define POTATO 8
#define CORN 9
#define BEAN 10
#define WATER 11
#define MILK 12
#define ICECREAM 13
#define MUSHROOM 14
#define BACON 15
#define JALAPENO 16
#define CHOCO 17
#define COKE 18
#define CIDER 19

class Data {
private:
	FileManager* fm;
	vector<Material> materialCategory; // ��� ī�װ�
	vector<Product>* categoryArray[5]; // ��� ī�װ����� �����͵��� ��Ƴ��� �迭
	vector<Product> burgerCategory; // *categoryArray[0]
	vector<Product> sideCategory; // *categoryArray[1]
	vector<Product> dessertCategory; // *categoryArray[2]
	vector<Product> drinkCategory; // *categoryArray[3]
	vector<Product> addmaterialCategory; // *categoryArray[4]
	/*����*/
	vector<string> save;  //@  ��� ���� �� ����� ����, �� ���� ������ �����Ѵ�
	vector< vector<string>> saveList;  //@ ��� ���� �� ����� ����, �� �ϳ� �ϳ��� �����Ѵ�.
	vector< vector<string>> time_match_List;
	vector<string> time_match;
	int from_time;
	int to_time;
	int interval_time;
	/*����*/
	vector<Product> currentCart; // ���� ����Ŭ�� īƮ �ϳ�
	vector<vector<Product>> cartList; // ���� ��� �ִ� ��� īƮ
	
	int for_here; // ���� �ֹ� Ƚ�� ������
	int to_go; // ���� �ֹ� Ƚ�� ������
	int total_sales; // �����

public:
	Data(FileManager* fm);
	void initalize();
	void addDefaultMaterial(vector<Material>& materialList, vector<Material> list);
	vector<Product>** getCategoryArray();
	vector<vector<Product>>& getCartList();
	vector<Product>& getCurrentCart();
	vector<Material>* getMaterialCategory();
	int* get_for_here();
	int* get_to_go();
	int get_total_sales();
	/*����*/
	void get_info();
	vector< vector<string>>* find_time(vector<int>& time_from, vector<int>& time_to);
	vector< vector<string>> gettime_match_List();
	int get_total_sale_txt();
	int get_count_product_sale(string productname);
	int get_product_sales(string productname);
	vector< vector<string>>* get_saveList();
	int get_interval_time();
	int get_total_sale_intime();
	/*����*/
};