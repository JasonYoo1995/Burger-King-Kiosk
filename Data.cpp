#include "Data.h"
#include "Material.h"

Data::Data(FileManager* fm) {
	this->fm = fm;
	initalize();
	total_sales = 0;
}

void Data::initalize(){
	// 매장 or 포장 초기화
	this->for_here = atoi(fm->tokenize("sold_type.txt", 1, 2)[0].c_str());
	this->to_go = atoi(fm->tokenize("sold_type.txt", 1, 2)[1].c_str());	

	// 재료 카테고리 초기화
	for (size_t i = 0; i < 20; i++)
	{
		string* s = fm->tokenize("material.txt", i + 1, 4);
		materialCategory.push_back(Material(s[0], atoi(s[1].c_str()), atoi(s[2].c_str()), atoi(s[3].c_str())));
	}

	// 제품 초기화 및 카테고리 초기화
	string fileName[5] = { "product_burger.txt", "product_side.txt", "product_drink.txt", "product_dessert.txt", "product_extra_material.txt" };
	for (size_t n = 0; n < 5; n++)
	{
		for (size_t i = 0; i < fm->countLines(fileName[n]); i++)
		{
			string* s = fm->tokenize(fileName[n], i + 1, 10); // 최대 10개의 재료까지 커버 가능
			vector<Material> materialList;
			if (n == 0) addDefaultMaterial(materialList, materialCategory); // 버거만 default 재료 추가
			int j = 1;
			while (s[j] != "") {
				materialList.push_back(materialCategory.at(atoi(s[j].c_str())));
				j++;
			}
			Product p(s[0], materialList);
			switch (n) {
			case 0:
				burgerCategory.push_back(p);
				break;
			case 1:
				sideCategory.push_back(p);
				break;
			case 2:
				drinkCategory.push_back(p);
				break;
			case 3:
				dessertCategory.push_back(p);
				break;
			case 4:
				addmaterialCategory.push_back(p);
				break;
			}
		}
	}

	// categoryArray 초기화
	for (unsigned int i = 0; i < 5; i++)
	{
		categoryArray[0] = &burgerCategory;
		categoryArray[1] = &sideCategory;
		categoryArray[2] = &dessertCategory;
		categoryArray[3] = &drinkCategory;
		categoryArray[4] = &addmaterialCategory;
	}
}

void Data::addDefaultMaterial(vector<Material>& materialList, vector<Material> list)
{
	materialList.push_back(list.at(BREAD));
	materialList.push_back(list.at(LETTUCE));
	materialList.push_back(list.at(SOURCE));
	materialList.push_back(list.at(TOMATO));
}


vector<Product>** Data::getCategoryArray() {
	return categoryArray;
}

vector<vector<Product>>& Data::getCartList() {
	return cartList;
}

vector<Product>& Data::getCurrentCart() {
	return currentCart;
}

vector<Material>* Data::getMaterialCategory(){
	return &materialCategory;
}

int* Data::get_for_here() {
	return &for_here;
}

int* Data::get_to_go() {
	return &to_go;
}

int Data::get_total_sales() {
	return this->total_sales;
}
/*찬종*/
void Data::get_info() {

	int i = 0; int j = 0;
	string token;
	string s;

	ifstream in("sold_list.txt");

	while (in) {
		getline(in, s);
		istringstream ss(s);

		while (getline(ss, token, '/')) {
			save.push_back(token);
		}
		saveList.push_back(save);
		
		save.clear();
	}
}

vector< vector<string>>Data::gettime_match_List() {  //찬종

	return  time_match_List;
}

int Data::get_total_sale_txt() {
	int total = 0;
	for (int i = 0; i < fm->countLines("sold_list.txt"); i++) {
		total += stoi(saveList.at(i).at(6));
	}

	return total;
}

int Data::get_count_product_sale(string productname) {  //찬종
	int count = 0;

	for (int i = 0; i < fm->countLines("sold_list.txt"); i++) {

		if (saveList.at(i).at(5) == productname) {
			count++;
		}
	}

	return count;
}

int Data::get_product_sales(string productname) {  //찬종
	int total = 0;

	for (int i = 0; i < fm->countLines("sold_list.txt"); i++) {

		if (saveList.at(i).at(5) == productname) {
			total += stoi(saveList.at(i).at(6));
		}
	}

	return total;
}

vector< vector<string>>* Data::get_saveList() {  // 찬종 
	return &saveList;
}

vector< vector<string>>* Data::find_time(vector<int>& time_from, vector<int>& time_to) {   // 찬종 입력 시간 받아서 사이 시간에 해당하는 로그 값 가져 온다.
	// 0 : 년 1:월 2:일 3:시 4:분  5:메뉴 6: 가격
	int totalsecond;
	int  save_from_index = 0;
	int save_to_index = 0;

	struct tm timebuf;

	for (int i = 0; i < fm->countLines("sold_list.txt"); i++) {
		timebuf.tm_year = stoi(saveList.at(i).at(0)) - 1900;
		timebuf.tm_mon = stoi(saveList.at(i).at(1)) - 1;
		timebuf.tm_mday = stoi(saveList.at(i).at(2));
		timebuf.tm_hour = stoi(saveList.at(i).at(3));
		timebuf.tm_min = stoi(saveList.at(i).at(4));;
		timebuf.tm_sec = 0;

		int list_time = mktime(&timebuf);

		timebuf.tm_year = time_from.at(0) - 1900;
		timebuf.tm_mon = time_from.at(1) - 1;
		timebuf.tm_mday = time_from.at(2);
		timebuf.tm_hour = time_from.at(3);
		timebuf.tm_min = time_from.at(4);;
		timebuf.tm_sec = 0;

		from_time = mktime(&timebuf);

		if (list_time >= from_time) {
			save_from_index = i;
			break;
		}
	}

	for (int i = 0; i < fm->countLines("sold_list.txt"); i++) {

		int save_from_index;

		timebuf.tm_year = stoi(saveList.at(i).at(0)) - 1900;
		timebuf.tm_mon = stoi(saveList.at(i).at(1)) - 1;
		timebuf.tm_mday = stoi(saveList.at(i).at(2));
		timebuf.tm_hour = stoi(saveList.at(i).at(3));
		timebuf.tm_min = stoi(saveList.at(i).at(4));;
		timebuf.tm_sec = 0;

		int list_time = mktime(&timebuf);

		timebuf.tm_year = time_to.at(0) - 1900;
		timebuf.tm_mon = time_to.at(1) - 1;
		timebuf.tm_mday = time_to.at(2);
		timebuf.tm_hour = time_to.at(3);
		timebuf.tm_min = time_to.at(4);;
		timebuf.tm_sec = 0;

		to_time = mktime(&timebuf);

		if (to_time < list_time) {
			save_to_index = i - 1;
			break;
		}

		save_to_index = i;

	}

	for (int i = save_from_index; i <= save_to_index; i++) {

		for (int k = 0; k < 7; k++) {
			time_match.push_back(saveList.at(i).at(k));
		}
		time_match_List.push_back(time_match);

		time_match.clear();
	}

	interval_time = to_time - from_time;

	return &time_match_List;
}


int Data::get_interval_time() {       // 찬종  

	return interval_time;
}

int Data::get_total_sale_intime() {       // 찬종   
	int total = 0;

	for (int i = 0; i < time_match_List.size(); i++) {

		total += stoi(time_match_List.at(i).at(6));
	}

	return total;
}
/*찬종*/