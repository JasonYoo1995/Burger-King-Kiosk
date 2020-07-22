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
	vector<Material> materialCategory; // 재료 카테고리
	vector<Product>* categoryArray[5]; // 모든 카테고리들의 포인터들을 담아놓은 배열
	vector<Product> burgerCategory; // *categoryArray[0]
	vector<Product> sideCategory; // *categoryArray[1]
	vector<Product> dessertCategory; // *categoryArray[2]
	vector<Product> drinkCategory; // *categoryArray[3]
	vector<Product> addmaterialCategory; // *categoryArray[4]
	/*찬종*/
	vector<string> save;  //@  통계 구할 때 사용할 벡터, 한 줄의 정보를 저장한다
	vector< vector<string>> saveList;  //@ 통계 구할 때 사용할 벡터, 줄 하나 하나를 저장한다.
	vector< vector<string>> time_match_List;
	vector<string> time_match;
	int from_time;
	int to_time;
	int interval_time;
	/*찬종*/
	vector<Product> currentCart; // 현재 사이클의 카트 하나
	vector<vector<Product>> cartList; // 현재 담겨 있는 모든 카트
	
	int for_here; // 매장 주문 횟수 포인터
	int to_go; // 포장 주문 횟수 포인터
	int total_sales; // 매출액

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
	/*찬종*/
	void get_info();
	vector< vector<string>>* find_time(vector<int>& time_from, vector<int>& time_to);
	vector< vector<string>> gettime_match_List();
	int get_total_sale_txt();
	int get_count_product_sale(string productname);
	int get_product_sales(string productname);
	vector< vector<string>>* get_saveList();
	int get_interval_time();
	int get_total_sale_intime();
	/*찬종*/
};