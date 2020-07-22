#include "ConsoleView.h"

ConsoleView::ConsoleView(Data* data, FileManager* fm) { // 생성자 / data와 view를 연결
	this->data = data;
	this->option = '\0'; // 초기화
	this->fm = fm;
	this->comboAndSet = '\0'; // 초기화
}

void ConsoleView::gotoxy(short x, short y) { // 키보드 커서의 x,y 좌표를 이동시키는 메소드
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void ConsoleView::showUI() { // 메뉴 사이클 담당
	bool exit = false; // 키오스크 종료 여부
	while (1) {
		switch (page) {
		case 0: // 초기화면 & 카테고리 선택 & 카트 삭제 & 결제
			page = userUI0();
			break;
		case 1: // 제품 선택
			page = userUI1();
			break;
		case 2: // 구성 선택 (단품, 콤보, 세트)
			page = userUI2();
			break;
		case 3: // 재료 선택
			page = userUI3();
			break;
		case 4: // 사이드-음료 변경 & 카트 담기
			page = userUI4();
			break;
		case 5: // 카트 확인
			page = userUI5();
			break;
		case 6: // 매장-포장 & 최종 결제
			page = userUI6();
			break;
		case 7: // 관리자 모드 초기화면
			page = adminUI0();
			break;
		case 8: // 신제품 추가
			page = adminUI1();
			break;
		case 9: // 기존 제품 삭제
			page = adminUI2();
			break;
		case 10: // 재고 입력
			page = adminUI3();
			break;
		case 11: // 통계 자료 조회
			page = adminUI4();
			break;
		case 12: // 가격 변동 /*경원*/
			page = adminUI5(); /*경원*/
			break; /*경원*/
		case 13: // 도움말 /*경원*/
				page = helpUI();
				break;
		case -1: // 종료
			exit = true;
			break;
		}
		if (exit == true) break;
	}
	cout << "키오스크가 종료되었습니다.\n\n" << endl;
}

int ConsoleView::userUI0() { // 초기화면 & 카테고리 선택 & 카트 삭제 & 결제
	while (1) {
		console_clear();
		cout << "h. 사용설명서\n" << endl;
		cout << "□ 카테고리 □" << endl;
		cout << "  a. 햄버거" << endl;
		cout << "  b. 사이드" << endl;
		cout << "  c. 디저트" << endl;
		cout << "  d. 음료\n" << endl;

		// 현재 카트 목록
		border_above(); // 선 그리기

		cout << "│ < 카트 목록 >" << endl;
		gotoxy(101, 9); // 커서 이동
		cout << "│" << endl;

		vector<vector<Product>> cartList = data->getCartList();
		for (unsigned int i = 0; i < cartList.size(); i++)
		{
			cout << "│ " << i + 1 << ". ";
			print_all_elements(cartList.at(i)); // cartList에 있는 모든 요소들을 출력
			gotoxy(101, 10 + i);
			cout << "│ " << endl;
		}

		border_bottom(); // 선 그리기

		pay(); // 결제 버튼 그리기(UI)

		cout << " * 관리자 모드(@)" << endl;
		cout << "\n - 입력 : ";
		inputs(); // 키보드 입력 받기

		console_clear(); // 콘솔 비우기

		if (input == 'h') return 13; // page 13로 이동 /*경원*/

		if ((input >= 'a' && input <= 'd')) { // 카테고리 선택 시
			if (input == 'a') burger = true; // page 2와 page 4 사이의 분기를 위함
			else burger = false; // page 2와 page 4 사이의 분기를 위함
			option = input; // 카테고리 정보를 option에 저장
			return 1; // page 1로 이동
		}
		if (input >= '1' && input <= '1' + cartList.size() - 1) {
			data->getCartList().erase(data->getCartList().begin() + (input - 49)); // 카트 삭제 (카트 리스트의 시작에서 i-1번째 떨어진 곳 삭제) 
		}
		if (input == '$') {
			if (data->getCartList().size()==0)
			{
				console_clear();
				cout << "\n###카트가 비어있습니다. 물건을 먼저 골라주세요.###\n";
				Sleep(2000);
				return 0;
			}
			return 5; 
		} // page 5로 이동
		if (input == '@') return 7; // page 7로 이동
	}
}

/*
 → getCategoryArray()[0] = burgerCategory
 → getCategoryArray()[1] = sideCategory
 → getCategoryArray()[2] = dessertCategory
 → getCategoryArray()[3] = drinkCategory
 → getCategoryArray()[4] = addmaterialCategory
*/

int ConsoleView::userUI1() { // 제품 선택
	while (1) {
		cout << "* 뒤로가기(0)\n" << endl;
		cout << "□ 제품 목록 □" << endl;

		vector<Product>* category = data->getCategoryArray()[0]; // '아무거나'로 초기화 함 
		switch (option) { // option : 이전에 선택한 카테고리
		case 'a': // 햄버거
			category = data->getCategoryArray()[0];
			break;
		case 'b': // 사이드
			category = data->getCategoryArray()[1];
			break;
		case 'c': // 디저트
			category = data->getCategoryArray()[2];
			break;
		case 'd': // 음료
			category = data->getCategoryArray()[3];
			break;
		}

		for (unsigned int i = 0; i < category->size(); i++) // page 0에서 선택한 option(카테고리)에 해당 되는 제품 목록 출력 
		{
			cout << "  " << (char)(i + 97) << ". " << category->at(i).getName(); // (i + 97) 은 a,b,c ... 를 의미
			gotoxy(22, 3 + i); // 간격조절
			cout << category->at(i).getKcal() << "Kcal"; // Kcal출력
			gotoxy(32, 3 + i); // 간격조절
			cout << category->at(i).getPrice() << "원" << endl; // Price출력 
		}

		cout << "\n - 입력 : ";
		inputs();
		console_clear();

		if (input >= 'a' && input <= 'a' + category->size() - 1) { // 제품을 선택한 경우
			// 본승
			for (int i = 0; i < data->getCategoryArray()[option - 'a']->at(input - 97).getMaterialList().size(); i++) {
				data->getCategoryArray()[option - 'a']->at(input - 97).getMaterialList().at(i).decreaseStock(1); // 재고 감소시켜보기
				if (data->getCategoryArray()[option - 'a']->at(input - 97).getMaterialList().at(i).getStock() < 0) soldout = 1; // 품절일 경우 품절 체크
				data->getCategoryArray()[option - 'a']->at(input - 97).getMaterialList().at(i).increaseStock(1); // 재고 원상복귀 시키기
			}
			if (soldout == 1) {
				soldout = 0; // 품절체크 초기화
				gotoxy(0, 6 + data->getCategoryArray()[option - 'a']->size());
				cout << data->getCategoryArray()[option - 'a']->at(input - 97).getName() << "은/는 품절입니다. 다른 제품을 선택해 주십시오." << endl;
				gotoxy(0, 0);
				return 1; // 다시 제품 고르러 가기
			}
			// 본승
			data->getCurrentCart().push_back(data->getCategoryArray()[option - 'a']->at(input - 97));
			// ↑ 카트에 제품 삽입 : [option - 'a']는 (0 ~ 4) 사이의 값으로 카테고리를 의미
			//						 (input - 97)은 방금 선택한 제품의 카테고리 상에서의 인덱스를 의미

			if (burger == true) return 2; // 버거를 선택한 경우, page 2로 이동
			else {
				incresedCartSize = 1;
				return 4;
			} // 버거가 아닌 경우, page 4로 이동
		}
		else if (input == '0')
			return 0;
		// 뒤로 가기
	}}


int ConsoleView::userUI2() { // 구성 선택
	while (1) {
		cout << "* 뒤로가기(0)\n" << endl;
		cout << "[ 카트에 담긴 목록 : ";
		print_carts_elements(data->getCurrentCart()); // 현재 카트 목록 출력 (본승)
			cout << " ]\n" << endl; 
			cout << "□ 구성 선택 □" << endl;

		cout << "  a. 단품 (버거)" << endl;
		cout << "  b. 콤보 (버거 + 음료)" << endl;
		cout << "  c. 세트 (버거 + 사이드 + 음료)" << endl;

		cout << "\n - 입력 : ";
		inputs();
		comboAndSet = input;
		console_clear();

		if (input >= 'a' && input <= 'c') { // 구성 선택 시
			if (input == 'a') {
				side = false;
				drink = false;
			}
			else if (input == 'b') {
				// 본승
				for (int i = 0; i < data->getCategoryArray()[3]->at(0).getMaterialList().size(); i++) {
					data->getCategoryArray()[3]->at(0).getMaterialList().at(i).decreaseStock(1); // 재고 감소시켜보기
					if (data->getCategoryArray()[3]->at(0).getMaterialList().at(i).getStock() < 0) soldout = 1; // 품절일 경우 품절 체크
					data->getCategoryArray()[3]->at(0).getMaterialList().at(i).increaseStock(1); // 재고 원상복귀 시키기
				}
				if (soldout == 1) {
					soldout = 0; // 품절체크 초기화
					gotoxy(0, 7 + data->getCategoryArray()[3]->size());
					cout << data->getCategoryArray()[3]->at(0).getName() << "은/는 품절입니다. 다른 제품을 선택해 주십시오." << endl;
					gotoxy(0, 0);
					return 2; // 다시 제품 고르러 가기
				}
				// 본승
				incresedCartSize = 1; // 카트 1 늘어남
				data->getCurrentCart().push_back(data->getCategoryArray()[3]->at(0)); // 콜라 자동 삽입 
				side = false;
				drink = true;
			}
			else if (input == 'c') {
				// 본승
				for (int i = 0; i < data->getCategoryArray()[1]->at(0).getMaterialList().size(); i++) {
					data->getCategoryArray()[1]->at(0).getMaterialList().at(i).decreaseStock(1); // 재고 감소시켜보기
					if (data->getCategoryArray()[1]->at(0).getMaterialList().at(i).getStock() < 0) soldout = 1; // 품절일 경우 품절 체크
					data->getCategoryArray()[1]->at(0).getMaterialList().at(i).increaseStock(1); // 재고 원상복귀 시키기
				}
				if (soldout == 1) {
					soldout = 0; // 품절체크 초기화
					gotoxy(0, 7 + data->getCategoryArray()[1]->size());
					cout << data->getCategoryArray()[1]->at(0).getName() << "은/는 품절입니다. 다른 제품을 선택해 주십시오." << endl;
					gotoxy(0, 0);
					return 2; // 다시 제품 고르러 가기
				}
				for (int i = 0; i < data->getCategoryArray()[3]->at(0).getMaterialList().size(); i++) {
					data->getCategoryArray()[3]->at(0).getMaterialList().at(i).decreaseStock(1); // 재고 감소시켜보기
					if (data->getCategoryArray()[3]->at(0).getMaterialList().at(i).getStock() < 0) soldout = 1; // 품절일 경우 품절 체크
					data->getCategoryArray()[3]->at(0).getMaterialList().at(i).increaseStock(1); // 재고 원상복귀 시키기
				}
				if (soldout == 1) {
					soldout = 0; // 품절체크 초기화
					gotoxy(0, 7 + data->getCategoryArray()[3]->size());
					cout << data->getCategoryArray()[3]->at(0).getName() << "은/는 품절입니다. 다른 제품을 선택해 주십시오." << endl;
					gotoxy(0, 0);
					return 2; // 다시 제품 고르러 가기
				}
				// 본승
				incresedCartSize = 2; // 카트 2 늘어남
				data->getCurrentCart().push_back(data->getCategoryArray()[1]->at(0)); // 감자튀김 자동 삽입 
				data->getCurrentCart().push_back(data->getCategoryArray()[3]->at(0)); // 콜라 자동 삽입 
				side = true;
				drink = true;
			}
			return 3; // page 3으로 이동
		}
		else if (input == '0') {
			data->getCurrentCart().pop_back(); // 뒤로 가기 시 카트 비움 
			side = false;
			drink = false;
			return 1; // 뒤로 가기
		}
	}
}

int ConsoleView::userUI3() { // 재료 선택
	while (1) {
		cout << "* 뒤로가기(0)\n" << endl;
		cout << "[ 카트에 담긴 목록 : ";
		print_carts_elements(data->getCurrentCart()); // 현재 카트 목록 출력 (본승)
		cout << " ]\n" << endl;
		cout << "□ 추가 재료 선택 □" << endl;

		for (unsigned int i = 0; i < data->getCategoryArray()[4]->size(); i++) // 추가재료 목록 출력 
		{
			cout << "  " << (char)(i + 97) << ". " << data->getCategoryArray()[4]->at(i).getName(); // (i + 97) 은 a,b,c ... 를 의미
			gotoxy(22, 5 + i); // 간격조절
			cout << data->getCategoryArray()[4]->at(i).getKcal() << "Kcal"; // Kcal출력
			gotoxy(32, 5 + i); // 간격조절
			cout << data->getCategoryArray()[4]->at(i).getPrice() << "원" << endl; // Price출력 
		}
		cout << "  * 추가 안 함 : n" << endl;

		cout << "\n - 입력 : ";
		inputs();
		console_clear();
		if (input >= 'a' && input <= 'd' || input == 'n') { // 재료 선택 시
			if (input != 'n') {
				// 본승
				for (int i = 0; i < data->getCategoryArray()[4]->at(input - 'a').getMaterialList().size(); i++) {
					data->getCategoryArray()[4]->at(input - 'a').getMaterialList().at(i).decreaseStock(1); // 재고 감소시켜보기
					if (data->getCategoryArray()[4]->at(input - 'a').getMaterialList().at(i).getStock() < 0) soldout = 1; // 품절일 경우 품절 체크
					data->getCategoryArray()[4]->at(input - 'a').getMaterialList().at(i).increaseStock(1); // 재고 원상복귀 시키기
				}
				if (soldout == 1) {
					soldout = 0; // 품절체크 초기화
					gotoxy(0, 6 + data->getCategoryArray()[4]->size());
					cout << data->getCategoryArray()[4]->at(input - 97).getName() << "은/는 품절입니다. 다른 제품을 선택해 주십시오." << endl;
					gotoxy(0, 0);
					return 3; // 다시 제품 고르러 가기
				}
				// 본승
				data->getCurrentCart().push_back(data->getCategoryArray()[4]->at(input - 'a')); // n이 아닐 때만, 추가 재료 삽입 
				incresedCartSize = 1; // 카트 1 늘어남 
			}
			else incresedCartSize = 0; // 카트 안늘어남 
			return 4; // page 4로 이동
		}
		else if (input == '0') {
			while (incresedCartSize != 0) {
				data->getCurrentCart().pop_back();
				incresedCartSize--;
			} // 늘어난 카트의 사이즈가 0이 될때까지 카트 한개씩 비움 
			return 2; // 뒤로 가기
		}
	}
}

int ConsoleView::userUI4() { // 제품 변경 & 카트 담기
	while (true) {
		cout << "* 뒤로가기(0)\n" << endl;
		cout << "[ 카트에 담긴 목록 : ";
		print_carts_elements(data->getCurrentCart()); // 현재 카트 목록 출력 (본승)
		cout << " ]\n" << endl;
		if (burger == true && (side == true || drink == true)) { // 버거 선택이면서 동시에, 사이드 또는 음료 선택 시에만 출력
			cout << "□ 제품 변경 □" << endl;
			if (side == false) cout << "  a. 음료 변경" << endl;
			else {
				cout << "  a. 사이드 변경" << endl;
				cout << "  b. 음료 변경\n" << endl;
			}
		}
		cout << " * 카트에 담기(y)" << endl;

		cout << "\n - 입력 : ";
		// 본승
		if (sold_out != true) inputs();
		else input = change_option;
		sold_out = false;
		// 본승

		if (input == 'y') { // 카트 담기
			vector<Product> copiedCart;// 현재 카트를 그대로 복사해놓을 카트
			copiedCart.assign(data->getCurrentCart().begin(), data->getCurrentCart().end()); // 복사 
			data->getCartList().push_back(copiedCart); // 복사본을 "모든 카트 목록"에 추가 
			data->getCurrentCart().clear(); // 원본 카트 비우기 (재사용) 
			console_clear();
			return 0;
		}
		else if (input == '0') { // 뒤로 가기
			while (incresedCartSize != 0) {
				data->getCurrentCart().pop_back();
				incresedCartSize--;
			} // 늘어난 카트의 사이즈가 0이 될때까지 카트 한개씩 비움 
			console_clear();
			incresedCartSize = data->getCurrentCart().size() - 1; // 카트사이즈를 이전에 늘어난 카트의 사이즈로 변경 
			if (burger == true) return 3; // 버거를 선택한 경우, page 3으로 뒤로 가기
			else return 1; // 버거가 아닌 경우, page 1로 뒤로 가기
		}

		cout << endl;

		vector<Product>* sideList = data->getCategoryArray()[1];
		vector<Product>* drinkList = data->getCategoryArray()[3];

		if (side == true && input == 'a') { // 사이드 변경
			// 본승
			change_option = 'a';
			gotoxy(0, 12);
			cout << "□ 사이드 변경 □" << endl;
			// 본승

			for (unsigned int i = 0; i < sideList->size(); i++) // 사이드 카테고리 출력
			{
				// 본승
				cout << "  " << (char)(i + 97) << ". " << sideList->at(i).getName();
				gotoxy(22, 13 + i);
				cout << sideList->at(i).getKcal() << "Kacl";
				gotoxy(32, 13 + i);
				cout << sideList->at(i).getPrice() << "원" << endl;
				// 본승
			}

			while (1) {
				cout << "\n - 입력 : ";
				inputs();
				if (input >= 'a' && input <= 'a' + sideList->size() - 1) {
					// 본승
					for (int i = 0; i < sideList->at(input - 'a').getMaterialList().size(); i++) {
						sideList->at(input - 'a').getMaterialList().at(i).decreaseStock(1); // 재고 감소시켜보기
						if (sideList->at(input - 'a').getMaterialList().at(i).getStock() < 0) soldout = 1; // 품절일 경우 품절 체크
						sideList->at(input - 'a').getMaterialList().at(i).increaseStock(1); // 재고 원상복귀 시키기
					}
					if (soldout == 1) {
						soldout = 0; // 품절체크 초기화
						gotoxy(0, 16 + sideList->size());
						cout << sideList->at(input - 97).getName() << "은/는 품절입니다. 다른 제품을 선택해 주십시오." << endl;
						gotoxy(0, 0);
						sold_out = true;
						return 4; // 다시 제품 고르러 가기
					}
					// 본승
					Product newProduct(sideList->at(input - 'a'));
					vector<Product>& currentCart = data->getCurrentCart();
					cout << currentCart.size() << endl;
					switch (option) //burger, side, dessert, drink
					{
					case 'a': //burger
						if (comboAndSet == 'c')
							currentCart.at(1) = newProduct;
						break;
					default:
						break;
					}
					break;
				} // 목록에 없는 선택지 입력시 재입력
				gotoxy(0, 13 + sideList->size());
				line_clear(); // 한 줄 지우기
			}
		}
		else if (input == 'b' || (side == false && input == 'a')) { // 음료 변경
			//본승
			change_option = 'b';
			if (side == false) gotoxy(0, 10);
			else gotoxy(0, 12);
			cout << "□ 음료 변경 □" << endl;
			//본승

			for (unsigned int i = 0; i < drinkList->size(); i++) // 음료 카테고리 출력
			{
				// 본승
				cout << "  " << (char)(i + 97) << ". " << drinkList->at(i).getName();
				if (side == false) gotoxy(22, 11 + i);
				else gotoxy(22, 13 + i);
				cout << drinkList->at(i).getKcal() << "Kcal";
				if (side == false) gotoxy(32, 11 + i);
				else gotoxy(32, 13 + i);
				cout << drinkList->at(i).getPrice() << "원" << endl;
			}

			while (1) {
				cout << "\n - 입력 : ";
				inputs();
				if (input >= 'a' && input <= 'a' + drinkList->size() - 1) {
					// 본승
					for (int i = 0; i < drinkList->at(input - 'a').getMaterialList().size(); i++) {
						drinkList->at(input - 'a').getMaterialList().at(i).decreaseStock(1); // 재고 감소시켜보기
						if (drinkList->at(input - 'a').getMaterialList().at(i).getStock() < 0) soldout = 1; // 품절일 경우 품절 체크
						drinkList->at(input - 'a').getMaterialList().at(i).increaseStock(1); // 재고 원상복귀 시키기
					}
					if (soldout == 1) {
						soldout = 0; // 품절체크 초기화
						if (side == false) gotoxy(0, 14 + sideList->size());
						else gotoxy(0, 15 + sideList->size());
						cout << drinkList->at(input - 97).getName() << "은/는 품절입니다. 다른 제품을 선택해 주십시오." << endl;
						gotoxy(0, 0);
						sold_out = true;
						return 4; // 다시 제품 고르러 가기
					}
					// 본승
					Product newProduct(drinkList->at(input - 'a'));
					vector<Product>& currentCart = data->getCurrentCart();
					switch (option) //burger, side, dessert, drink
					{
					case 'a': //burger
						if (comboAndSet == 'b') //버거 + 음료
							currentCart.at(1) = newProduct;
						else if (comboAndSet == 'c') //버거 + 음료 + 사이드
							currentCart.at(2) = newProduct;
						break;
					default:
						break;
					}
					break;
				}
				gotoxy(0, 13 + drinkList->size());
				line_clear();
			}
		}
		console_clear();
	}
}

int ConsoleView::userUI5() { // 카트 확인
	while (1) {
		cout << "* 카트 더 담기(0)\n" << endl;

		cout << "□ 카트 확인 □" << endl;

		vector<vector<Product>> cartList = data->getCartList(); // 모든 카트 목록 

		border_above();
		for (unsigned int i = 0; i < cartList.size(); i++) // 모든 카트 목록 출력
		{
			cout << "│ " << i + 1 << ". ";
			print_all_elements(cartList.at(i));
			gotoxy(101, 4 + i);
			cout << "│ " << endl;
			//본승
			if (i == cartList.size() - 1) {
				cout << "│ ";
				print_total(cartList);
				gotoxy(101, 5 + i);
				cout << "│ " << endl;
			}
			//본승
		}
		border_bottom();

		cout << "# : 확인" << endl;

		cout << "\n - 입력 : ";
		inputs();
		console_clear();
		if (input == '#') return 6; // 문제 없으면 page 6으로 이동
		else if (input == '0') return 0; // 뒤로 가기
	}
}
int ConsoleView::userUI6() { // 매장-포장 & 최종 결제
	while (1) {
		cout << "* 뒤로가기(0)\n" << endl;
		cout << "□ 매장 식사 / 포장 □" << endl;

		cout << "  a. 매장 식사" << endl;
		cout << "  b. 포장" << endl;

		cout << "\n - 입력 : ";
		inputs();
		char temp = input; // 선택 정보 백업

		if (input == '0') {
			console_clear();
			return 5; // 뒤로 가기
		}
		if (input != 'a' && input != 'b') { // 없는 선택지 입력시 재입력
			console_clear();
			continue;
		}

		cout << "\n * 결제하시겠습니까? (y/n)" << endl;
		inputs();

		console_clear();
		if (input == 'y') { // 결제하기
			if (temp == 'a') { // 매장 주문 횟수 증가
				*(data->get_for_here()) += 1;
			}
			else { // 포장 주문 횟수 증가 
				*(data->get_to_go()) += 1;
			}
			fm->update_for_here_to_go(to_string(*(data->get_for_here())) + "_" + to_string(*(data->get_to_go()))); // 매장 or 포장 - 파일 write

			for (int i = 0; i < data->getCartList().size(); i++) { // 팔린 카트리스트 접근 
				for (int j = 0; j < data->getCartList().at(i).size(); j++) { // 카트리스트의 카트 접근
					fm->setTime("sold_list.txt");   // @ 
					fm->write("sold_list.txt","/");
					fm->write("sold_list.txt",data->getCartList().at(i).at(j).getName());  //@
					fm->write("sold_list.txt", "/");
					fm->write("sold_list.txt",to_string(data->getCartList().at(i).at(j).getPrice()));  //@

					for (int k = 0; k < data->getCartList().at(i).at(j).getMaterialList().size(); k++) { //카트의 제품 접근 
						/*우영*/
						fm->modifyStock("material.txt", 
							data->getCartList().at(i).at(j).getMaterialList().at(k).getName(), 
							data->getCartList().at(i).at(j).getMaterialList().at(k).decreaseStock(1)); // 접근한 재료들 감소 
					}
					fm->write("sold_list.txt", "\n");  //@
				}
			}
			/*우영*/
			data->getCartList().clear(); // 결제 후 카트리스트 비우기 
			return 0; // page 0으로 이동
		}
	}
}

int ConsoleView::helpUI() {
	while (1) {
		cout << "* 뒤로가기(0)\n" << endl;
		cout << "< 도움말 >" << endl;
		// 본승
		cout << " 사용자 모드" << endl;
		cout << "	UI별로 알파벳 소문자로 제품을 선택할 수 있다" << endl;
		cout << "	0을 입력해서 이전 UI로 돌아갈 수 있다" << endl;
		cout << "	콤보 선택시 음료는 콜라가 자동으로 선택되며 세트 선택시 음료는 콜라, 사이드는 감자튀김이 자동으로 선택된다" << endl;
		cout << "	제품 선택이 끝나면 y를 입력해서 선택한 제품들을 카트에 담을 수 있다" << endl;
		cout << "	카트목록안의 숫자를 입력하여 그 카트를 지울 수 있다\n" << endl;
		cout << " 관리자 모드" << endl;
		cout << "	UI별로 숫자를 입력하여 제품추가/재료재고추가/통계확인 등이 가능하다" << endl;
		// 본승
		cout << "\n - 입력 : ";
		inputs();

		if (input == '0') {
			console_clear();
			return 0;
		}
	}
}

int ConsoleView::adminUI0() {
	while (1) {
		cout << "□ 관리자 모드 □" << endl;
		cout << " 1. 신제품 추가" << endl;
		cout << " 2. 기존 제품 삭제" << endl;
		cout << " 3. 재료 재고 추가" << endl;
		cout << " 4. 통계 자료 조회" << endl;
		cout << " 5. 재료 가격 변동" << endl; /*경원*/
		cout << " 6. 사용자 모드\n" << endl; /*경원*/

		cout << " * 키오스크 종료(E)" << endl;

		cout << "\n - 입력 : ";
		inputs();

		console_clear();
		// page 이동
		if (input == '1') return 8;
		if (input == '2') return 9;
		if (input == '3') return 10;
		if (input == '4') return 11;
		if (input == '5') return 12; /*경원*/
		if (input == '6') return 0; /*경원*/
		if (input == 'E') return -1;
	}
	return 0;
}

int ConsoleView::adminUI1() { // 신제품 추가
	while (1) {
		string fileName;
		cout << "* 뒤로가기(0)\n" << endl;
		cout << "□ 신제품 추가 □" << endl;
		cout << " 1. 버거" << endl;
		cout << " 2. 사이드" << endl;
		cout << " 3. 디저트" << endl;
		cout << " 4. 음료\n" << endl;
		cout << "\n - 입력 : ";
		inputs();
		cout << endl;

		if (input == '0') { // 뒤로 가기
			console_clear();
			return 7;
		}

		vector<Product>* selected_category = data->getCategoryArray()[0]; // 초기화 (아무거나로)
		if (input == '1') { 
			selected_category = data->getCategoryArray()[0]; 
			fileName = "product_burger.txt";
		}// 버거 
		else if (input == '2') { 
			selected_category = data->getCategoryArray()[1]; 
			fileName = "product_side.txt";
		} // 사이드 
		else if (input == '3') { 
			selected_category = data->getCategoryArray()[2]; 
			fileName = "product_dessert.txt";
		}// 디저트 
		else if (input == '4') {
			selected_category = data->getCategoryArray()[3]; 
			fileName = "product_drink.txt";
		}// 음료 

		cout << " - 제품 목록 -" << endl;
		for (unsigned int i = 0; i < selected_category->size(); i++) // 선택한 카테고리 목록 출력
		{
			cout << "  * " << selected_category->at(i).getName() << endl;
		}
		cout << "  * 뒤로가기(0)" << endl;
		string product_name = ""; // 신제품명
		cout << "\n → 추가할 신제품명(엔터 2번) : ";
		getline(cin, product_name);
		if (product_name.at(0) == '0') {
			console_clear();
			return 8;
		}
		cin.clear();
		cin.ignore();

		cout << "\n - 재료 목록 -" << endl;
		vector<Material>* materialList = data->getMaterialCategory(); //;
		for (unsigned int i = 0; i < materialList->size(); i++) // 재료 목록 출력
		{
			cout << "  " << (i + 1) << ". " << materialList->at(i).getName() << endl;
		}

		cout << "\n → 신제품을 구성할 재료 (띄어쓰기로 복수 선택 가능) : ";

		string materials_input;
		getline(cin, materials_input); // 띄어쓰기 단위로 tokenizing 할 문장
		stringstream ss(materials_input);

		vector<int> material_indices; // 파싱된 token들을 저장할 벡터
		string token;
		while (getline(ss, token, ' ')) { // tokening
			material_indices.push_back(atoi(token.c_str()) - 1);
		}
		int* materialNumList = new int(material_indices.size());
		vector<Material> materials_for_new;
		materials_for_new.push_back(materialList->at(BREAD));
		materials_for_new.push_back(materialList->at(LETTUCE));
		materials_for_new.push_back(materialList->at(SOURCE));
		materials_for_new.push_back(materialList->at(TOMATO));
		for (unsigned int i = 0; i < material_indices.size(); i++) // 신제품을 구성할 재료 목록을 벡터에 채우기
		{
			materials_for_new.push_back(data->getMaterialCategory()->at(material_indices.at(i)));
			materialNumList[i] = material_indices.at(i)+1;
		}
		fm->addProduct(fileName, product_name, materialNumList, material_indices.size());
		selected_category->push_back(Product(product_name, materials_for_new)); // 신제품을 해당 카테고리에 추가 

		console_clear();
	}
}

int ConsoleView::adminUI2() { // 기존 제품 삭제
	string fileName;
	while (1) {
		cout << "* 뒤로가기(0)\n" << endl;
		cout << "□ 기존 제품 삭제 □" << endl;
		cout << " 1. 버거" << endl;
		cout << " 2. 사이드" << endl;
		cout << " 3. 디저트" << endl;
		cout << " 4. 음료\n" << endl;
		cout << "\n - 입력 : ";
		inputs();
		cout << endl;

		if (input == '0') { // 뒤로 가기
			console_clear();
			return 7;
		}
		if (input <= '0' || input >= '5') { // 선택지에 없는 입력
			console_clear();
			continue;
		}

		vector<Product>* selected_category = data->getCategoryArray()[0]; // 초기화 (아무거나)
		if (input == '1') { 
			selected_category = data->getCategoryArray()[0]; 
			fileName = "product_burger.txt";
		} // 버거
		else if (input == '2') { 
			selected_category = data->getCategoryArray()[1]; 
			fileName = "product_side.txt"; 
		} // 사이드 
		else if (input == '3') { 
			selected_category = data->getCategoryArray()[2]; 
			fileName = "product_dessert.txt"; 
		} // 디저트 
		else if (input == '4') {
			selected_category = data->getCategoryArray()[3];
			fileName = "product_drink.txt";
		}// 음료 

		for (unsigned int i = 0; i < selected_category->size(); i++) // 제품 목록 출력
			cout << "  " << (i + 1) << ". " << selected_category->at(i).getName() << endl;
		cout << "  0. 뒤로 가기" << endl;

		cout << endl;

		while (1) {
			cout << " - 입력 : ";
			inputs();

			int set; char * toss;
			toss = &input;
			set = atoi(toss);

			if (input >= '1' && input <= '1' + selected_category->size() - 1) {
				/*우영*/
				fm->deleteProduct(fileName, selected_category->at(input-'1').getName());
				selected_category->erase(selected_category->begin() + set - 1);

				break; 
			} // 선택지에 있는 번호를 입력해야, break
			else if (input == '0') {
				console_clear();
				return 9;
			}

			gotoxy(0, 12 + selected_category->size());
			line_clear();
		}

		console_clear();
	}
}

int ConsoleView::adminUI3() { // 재료 재고 입력
	while (1) {
		cout << "* 뒤로가기(0)\n" << endl;
		cout << "□ 재료 재고 추가 □" << endl;
		vector<Material>* materialCategory = data->getMaterialCategory(); // 재료 카테고리 
		for (unsigned int i = 0; i < materialCategory->size(); i++)
		{
			cout << "  " << (i + 1) << ". " << materialCategory->at(i).getName()
				<< " : " << materialCategory->at(i).getStock() << "개" << endl;
		}

		cout << "\n - 추가할 재료 : ";
		int num;
		cin >> num;

		if (num >= 1 && num <= 1 + materialCategory->size() - 1) { // 재료 선택
			cout << " - 추가할 개수 : ";
			int stock;
			cin >> stock;
			cin.clear();
			cin.ignore(1, '\n');
			fm->modifyStock("material.txt", materialCategory->at(num - 1).getName(), materialCategory->at(num - 1).getStock() + stock);
			materialCategory->at(num - 1).increaseStock(stock); // 재고 추가
			console_clear();
		}
		else if (num == 0) { // 뒤로 가기
			console_clear();
			return 7;
		}
		console_clear();
	}
	return 0;
}
/*찬종*/
int ConsoleView::adminUI4() { // 통계 자료 조회
	while (1) {
		data->get_info();

		cout << "□ 통계 자료 조회 □\n" << endl;
		cout << " 1. 총 매출액 : " << data->get_total_sale_txt() << "원" << endl;
		cout << "\n 2. 매장 판매 : " << *(data->get_for_here()) << "회" << endl;
		cout << "    포장 판매 : " << *(data->get_to_go()) << "회" << endl;
		cout << "\n 3. 제품별 판매 현황" << endl; // 제품 가격, 판매 개수, 판매 매출
		cout << "\n  §제품명"; gotoxy(22, 9); cout << "§가격"; gotoxy(32, 9); cout << "§판매 개수"; gotoxy(45, 9); cout << "§제품 매출" << endl;

		vector<Product>* selected_category = data->getCategoryArray()[0]; // 초기화 (아무거나)

		int set = 0;
		
		for (int i = 0; i < 5; i++) {
			selected_category = data->getCategoryArray()[i];
			for (unsigned int j = 0; j < selected_category->size(); j++) {
				cout << "    " << selected_category->at(j).getName(); gotoxy(24, 10 + set + j); cout << selected_category->at(j).getPrice() << "원"; gotoxy(34, 10 + set + j);
				cout << data->get_count_product_sale(selected_category->at(j).getName()) << "개";
				gotoxy(47, 10 + set + j); cout << data->get_product_sales(selected_category->at(j).getName()) << "원" << endl;
			}
			set += selected_category->size();
		}
		
		gotoxy(24, 10 + set); cout << "\n 4. 시간대별 검색 : " << endl;
		gotoxy(24, 11 + set); cout << " * 뒤로 가려면 0, 검색하려면 1 입력 : ";
		inputs();

		data->get_saveList()->clear();

		if (input == '0') { // 뒤로 가기
			console_clear();
			return 7;
		}
		else if (input == '1') { // 검색
			console_clear();
		}
		else { // 잘못된 입력
			console_clear();
			continue;
		}

		while (1) {
			data->get_info();

			int year_from, month_from, day_from, hour_from, min_from;
			int year_to, month_to, day_to, hour_to, min_to;

			vector<int> time_from;
			vector<int> time_to;

			cout << "  < From >" << endl;
			cout << "   - 년 : "; cin >> year_from; time_from.push_back(year_from);
			cout << "   - 월 : "; cin >> month_from; time_from.push_back(month_from);
			cout << "   - 일 : "; cin >> day_from; time_from.push_back(day_from);
			cout << "   - 시 : "; cin >> hour_from; time_from.push_back(hour_from);
			cout << "   - 분 : "; cin >> min_from; time_from.push_back(min_from);
			cout << "\n  < To >" << endl;
			cout << "   - 년 : "; cin >> year_to; time_to.push_back(year_to);
			cout << "   - 월 : "; cin >> month_to; time_to.push_back(month_to);
			cout << "   - 일 : "; cin >> day_to; time_to.push_back(day_to);
			cout << "   - 시 : "; cin >> hour_to; time_to.push_back(hour_to);
			cout << "   - 분 : "; cin >> min_to; time_to.push_back(min_to);

			// 결과 출력
			cout << "\n※ " << year_from << "년 " << month_from << "월 " << day_from << "일 " << hour_from << "시 " << min_from << "분 ~ " << year_to << "년 " << month_to << "월 " << day_to << "일 " << hour_to << "시 " << min_to << "분" << endl;
			cout << "\n  §제품명"; gotoxy(22, 16); cout << "§가격"; gotoxy(32, 16); cout << "§판매 시각"; //gotoxy(45, 16); 

			// for문을 돌려서 출력하되, gotoxy의 y좌표는 15부터 1씩 증가
			vector<vector<string>>* time_match_list = data->find_time(time_from, time_to);
			for (unsigned int i = 0; i < time_match_list->size(); i++) {
				gotoxy(0, 18 + i); cout << "    " << time_match_list->at(i).at(5); gotoxy(24, 18 + i);
				cout << time_match_list->at(i).at(6); gotoxy(34, 18 + i);
				cout << time_match_list->at(i).at(0) << "-" <<
					time_match_list->at(i).at(1) << "/" << time_match_list->at(i).at(2) << "-" <<
					time_match_list->at(i).at(3) << ":" << time_match_list->at(i).at(4);    //gotoxy(47, 18);
			}

			gotoxy(0, 19 + time_match_list->size());
			cout << " ◆ 총 이익: " << data->get_total_sale_intime() << "원 (" << (data->get_interval_time() / 60 + 1) << "분 간)" << endl;
			cout << " ◆ 분당 판매이익: " << data->get_total_sale_intime() / (data->get_interval_time() / 60 + 1) << "원" << endl;

			time_match_list->clear();
			data->get_saveList()->clear();

			cout << "\n * 뒤로 가려면 0, 다시 검색하려면 1 입력 : ";
			inputs();
			if (input == '0') { // 뒤로 가기
				console_clear();
				break;
			}
			else { // 다시 검색
				console_clear();
			}
		}
	}
}
/*찬종*/
int ConsoleView::adminUI5() { // 가격 변동 /*경원*/
	while (1) {
		cout << "* 뒤로가기(0)\n" << endl;
		cout << "□ 가격 변동 □\n" << endl;
		vector<Material>* materialCategory = data->getMaterialCategory(); // 재료 카테고리 
		for (unsigned int i = 0; i < materialCategory->size(); i++) // 재료 출력
		{
			cout << "  " << (i + 1) << ". " << materialCategory->at(i).getName()
				<< " : " << materialCategory->at(i).getPrice() << "원" << endl;
		}

		int index;
		cout << "\n - 변동된 재료 : "; 
		cin >> index; // 1 입력시 0번째 재료 선택 / 2 입력시 1번째 재료 선택
		cin.clear();

		if (index == 0) { // 뒤로 가기
			console_clear();
			return 7;
		}

		if (index < 1 || index > 20) { // 재입력
			console_clear();
			continue;
		}
		else {
			int price;
			cout << "\n - 변동된 가격 : ";
			cin >> price;
			cin.clear();
			materialCategory->at(index - 1).increasePrice(price - materialCategory->at(index - 1).getPrice());
			fm->modifyPrice("material.txt", materialCategory->at(index - 1).getName(), price);
			for (int i = 0; i < 5; i++) {
				vector<Product> productCategory = *data->getCategoryArray()[i];
				for (int j = 0; j < productCategory.size(); j++) 
					productCategory.at(j).renewProduct();
			}
			console_clear();
			return 7;
		}
	}
}


//본승
void ConsoleView::print_carts_elements(vector<Product>& list) {
	if (list.size() == 0) return;
	for (unsigned int i = 0; i < list.size() - 1; i++)
	{
		cout << list.at(i).getName() << "(" << list.at(i).getKcal() << "Kcal/" << list.at(i).getPrice() << "원)" << " + ";
		cartkcal += list.at(i).getKcal();
		cartprice += list.at(i).getPrice();
	}
	cout << list.at(list.size() - 1).getName() << "(" << list.at(list.size() - 1).getKcal() << " Kcal/" << list.at(list.size() - 1).getPrice() << "원)";
	cartkcal += list.at(list.size() - 1).getKcal();
	cartprice += list.at(list.size() - 1).getPrice();
	cout << " 총 " << cartkcal << "Kcal/" << cartprice << "원";
	totalkcal = cartkcal;
	totalprice = cartprice;
	cartkcal = 0;
	cartprice = 0;
}

void ConsoleView::print_all_elements(vector<Product>& list) {
	if (list.size() == 0) return;
	for (unsigned int i = 0; i < list.size() - 1; i++)
	{
		cout << list.at(i).getName() << " + ";
		cartkcal += list.at(i).getKcal();
		cartprice += list.at(i).getPrice();
	}
	cout << list.at(list.size() - 1).getName();
	cartkcal += list.at(list.size() - 1).getKcal();
	cartprice += list.at(list.size() - 1).getPrice();
	cout << " 총 " << cartkcal << "Kcal/" << cartprice << "원";
	cartkcal = 0;
	cartprice = 0;
}

void ConsoleView::print_total(vector<vector<Product>> cartList) {
	totalkcal = 0;
	totalprice = 0;
	for (int i = 0; i < cartList.size(); i++) {
		for (int j = 0; j < cartList.at(i).size(); j++) {
			totalkcal += cartList.at(i).at(j).getKcal();
			totalprice += cartList.at(i).at(j).getPrice();
		}
	}
	cout << " [총" << totalkcal << "Kcal/" << totalprice << "원]" << endl;
}
// 본승

void ConsoleView::line_clear() {
	cout << "\33[2K";
}

void ConsoleView::console_clear() {
	system("cls");
}

void ConsoleView::border_above() {
	cout << "┌";
	for (int i = 0; i < 100; i++)
	{
		cout << "─";
	}
	cout << "┐" << endl;
}

void ConsoleView::border_bottom() {
	cout << "└";
	for (int i = 0; i < 100; i++)
	{
		cout << "─";
	}
	cout << "┘" << endl;
}

void ConsoleView::pay() {
	cout << "┌";
	for (int i = 0; i < 12; i++)
	{
		cout << "─";
	}
	cout << "┐" << endl;

	cout << "│ $. 결제하기│" << endl;

	cout << "└";
	for (int i = 0; i < 12; i++)
	{
		cout << "─";
	}
	cout << "┘" << endl;
}

void ConsoleView::inputs() {
	cin >> input;
	cin.clear();
	cin.ignore(1, '\n');
}