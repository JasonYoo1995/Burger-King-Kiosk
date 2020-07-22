#include "ConsoleView.h"

ConsoleView::ConsoleView(Data* data, FileManager* fm) { // ������ / data�� view�� ����
	this->data = data;
	this->option = '\0'; // �ʱ�ȭ
	this->fm = fm;
	this->comboAndSet = '\0'; // �ʱ�ȭ
}

void ConsoleView::gotoxy(short x, short y) { // Ű���� Ŀ���� x,y ��ǥ�� �̵���Ű�� �޼ҵ�
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void ConsoleView::showUI() { // �޴� ����Ŭ ���
	bool exit = false; // Ű����ũ ���� ����
	while (1) {
		switch (page) {
		case 0: // �ʱ�ȭ�� & ī�װ� ���� & īƮ ���� & ����
			page = userUI0();
			break;
		case 1: // ��ǰ ����
			page = userUI1();
			break;
		case 2: // ���� ���� (��ǰ, �޺�, ��Ʈ)
			page = userUI2();
			break;
		case 3: // ��� ����
			page = userUI3();
			break;
		case 4: // ���̵�-���� ���� & īƮ ���
			page = userUI4();
			break;
		case 5: // īƮ Ȯ��
			page = userUI5();
			break;
		case 6: // ����-���� & ���� ����
			page = userUI6();
			break;
		case 7: // ������ ��� �ʱ�ȭ��
			page = adminUI0();
			break;
		case 8: // ����ǰ �߰�
			page = adminUI1();
			break;
		case 9: // ���� ��ǰ ����
			page = adminUI2();
			break;
		case 10: // ��� �Է�
			page = adminUI3();
			break;
		case 11: // ��� �ڷ� ��ȸ
			page = adminUI4();
			break;
		case 12: // ���� ���� /*���*/
			page = adminUI5(); /*���*/
			break; /*���*/
		case 13: // ���� /*���*/
				page = helpUI();
				break;
		case -1: // ����
			exit = true;
			break;
		}
		if (exit == true) break;
	}
	cout << "Ű����ũ�� ����Ǿ����ϴ�.\n\n" << endl;
}

int ConsoleView::userUI0() { // �ʱ�ȭ�� & ī�װ� ���� & īƮ ���� & ����
	while (1) {
		console_clear();
		cout << "h. ��뼳��\n" << endl;
		cout << "�� ī�װ� ��" << endl;
		cout << "  a. �ܹ���" << endl;
		cout << "  b. ���̵�" << endl;
		cout << "  c. ����Ʈ" << endl;
		cout << "  d. ����\n" << endl;

		// ���� īƮ ���
		border_above(); // �� �׸���

		cout << "�� < īƮ ��� >" << endl;
		gotoxy(101, 9); // Ŀ�� �̵�
		cout << "��" << endl;

		vector<vector<Product>> cartList = data->getCartList();
		for (unsigned int i = 0; i < cartList.size(); i++)
		{
			cout << "�� " << i + 1 << ". ";
			print_all_elements(cartList.at(i)); // cartList�� �ִ� ��� ��ҵ��� ���
			gotoxy(101, 10 + i);
			cout << "�� " << endl;
		}

		border_bottom(); // �� �׸���

		pay(); // ���� ��ư �׸���(UI)

		cout << " * ������ ���(@)" << endl;
		cout << "\n - �Է� : ";
		inputs(); // Ű���� �Է� �ޱ�

		console_clear(); // �ܼ� ����

		if (input == 'h') return 13; // page 13�� �̵� /*���*/

		if ((input >= 'a' && input <= 'd')) { // ī�װ� ���� ��
			if (input == 'a') burger = true; // page 2�� page 4 ������ �б⸦ ����
			else burger = false; // page 2�� page 4 ������ �б⸦ ����
			option = input; // ī�װ� ������ option�� ����
			return 1; // page 1�� �̵�
		}
		if (input >= '1' && input <= '1' + cartList.size() - 1) {
			data->getCartList().erase(data->getCartList().begin() + (input - 49)); // īƮ ���� (īƮ ����Ʈ�� ���ۿ��� i-1��° ������ �� ����) 
		}
		if (input == '$') {
			if (data->getCartList().size()==0)
			{
				console_clear();
				cout << "\n###īƮ�� ����ֽ��ϴ�. ������ ���� ����ּ���.###\n";
				Sleep(2000);
				return 0;
			}
			return 5; 
		} // page 5�� �̵�
		if (input == '@') return 7; // page 7�� �̵�
	}
}

/*
 �� getCategoryArray()[0] = burgerCategory
 �� getCategoryArray()[1] = sideCategory
 �� getCategoryArray()[2] = dessertCategory
 �� getCategoryArray()[3] = drinkCategory
 �� getCategoryArray()[4] = addmaterialCategory
*/

int ConsoleView::userUI1() { // ��ǰ ����
	while (1) {
		cout << "* �ڷΰ���(0)\n" << endl;
		cout << "�� ��ǰ ��� ��" << endl;

		vector<Product>* category = data->getCategoryArray()[0]; // '�ƹ��ų�'�� �ʱ�ȭ �� 
		switch (option) { // option : ������ ������ ī�װ�
		case 'a': // �ܹ���
			category = data->getCategoryArray()[0];
			break;
		case 'b': // ���̵�
			category = data->getCategoryArray()[1];
			break;
		case 'c': // ����Ʈ
			category = data->getCategoryArray()[2];
			break;
		case 'd': // ����
			category = data->getCategoryArray()[3];
			break;
		}

		for (unsigned int i = 0; i < category->size(); i++) // page 0���� ������ option(ī�װ�)�� �ش� �Ǵ� ��ǰ ��� ��� 
		{
			cout << "  " << (char)(i + 97) << ". " << category->at(i).getName(); // (i + 97) �� a,b,c ... �� �ǹ�
			gotoxy(22, 3 + i); // ��������
			cout << category->at(i).getKcal() << "Kcal"; // Kcal���
			gotoxy(32, 3 + i); // ��������
			cout << category->at(i).getPrice() << "��" << endl; // Price��� 
		}

		cout << "\n - �Է� : ";
		inputs();
		console_clear();

		if (input >= 'a' && input <= 'a' + category->size() - 1) { // ��ǰ�� ������ ���
			// ����
			for (int i = 0; i < data->getCategoryArray()[option - 'a']->at(input - 97).getMaterialList().size(); i++) {
				data->getCategoryArray()[option - 'a']->at(input - 97).getMaterialList().at(i).decreaseStock(1); // ��� ���ҽ��Ѻ���
				if (data->getCategoryArray()[option - 'a']->at(input - 97).getMaterialList().at(i).getStock() < 0) soldout = 1; // ǰ���� ��� ǰ�� üũ
				data->getCategoryArray()[option - 'a']->at(input - 97).getMaterialList().at(i).increaseStock(1); // ��� ���󺹱� ��Ű��
			}
			if (soldout == 1) {
				soldout = 0; // ǰ��üũ �ʱ�ȭ
				gotoxy(0, 6 + data->getCategoryArray()[option - 'a']->size());
				cout << data->getCategoryArray()[option - 'a']->at(input - 97).getName() << "��/�� ǰ���Դϴ�. �ٸ� ��ǰ�� ������ �ֽʽÿ�." << endl;
				gotoxy(0, 0);
				return 1; // �ٽ� ��ǰ ���� ����
			}
			// ����
			data->getCurrentCart().push_back(data->getCategoryArray()[option - 'a']->at(input - 97));
			// �� īƮ�� ��ǰ ���� : [option - 'a']�� (0 ~ 4) ������ ������ ī�װ��� �ǹ�
			//						 (input - 97)�� ��� ������ ��ǰ�� ī�װ� �󿡼��� �ε����� �ǹ�

			if (burger == true) return 2; // ���Ÿ� ������ ���, page 2�� �̵�
			else {
				incresedCartSize = 1;
				return 4;
			} // ���Ű� �ƴ� ���, page 4�� �̵�
		}
		else if (input == '0')
			return 0;
		// �ڷ� ����
	}}


int ConsoleView::userUI2() { // ���� ����
	while (1) {
		cout << "* �ڷΰ���(0)\n" << endl;
		cout << "[ īƮ�� ��� ��� : ";
		print_carts_elements(data->getCurrentCart()); // ���� īƮ ��� ��� (����)
			cout << " ]\n" << endl; 
			cout << "�� ���� ���� ��" << endl;

		cout << "  a. ��ǰ (����)" << endl;
		cout << "  b. �޺� (���� + ����)" << endl;
		cout << "  c. ��Ʈ (���� + ���̵� + ����)" << endl;

		cout << "\n - �Է� : ";
		inputs();
		comboAndSet = input;
		console_clear();

		if (input >= 'a' && input <= 'c') { // ���� ���� ��
			if (input == 'a') {
				side = false;
				drink = false;
			}
			else if (input == 'b') {
				// ����
				for (int i = 0; i < data->getCategoryArray()[3]->at(0).getMaterialList().size(); i++) {
					data->getCategoryArray()[3]->at(0).getMaterialList().at(i).decreaseStock(1); // ��� ���ҽ��Ѻ���
					if (data->getCategoryArray()[3]->at(0).getMaterialList().at(i).getStock() < 0) soldout = 1; // ǰ���� ��� ǰ�� üũ
					data->getCategoryArray()[3]->at(0).getMaterialList().at(i).increaseStock(1); // ��� ���󺹱� ��Ű��
				}
				if (soldout == 1) {
					soldout = 0; // ǰ��üũ �ʱ�ȭ
					gotoxy(0, 7 + data->getCategoryArray()[3]->size());
					cout << data->getCategoryArray()[3]->at(0).getName() << "��/�� ǰ���Դϴ�. �ٸ� ��ǰ�� ������ �ֽʽÿ�." << endl;
					gotoxy(0, 0);
					return 2; // �ٽ� ��ǰ ���� ����
				}
				// ����
				incresedCartSize = 1; // īƮ 1 �þ
				data->getCurrentCart().push_back(data->getCategoryArray()[3]->at(0)); // �ݶ� �ڵ� ���� 
				side = false;
				drink = true;
			}
			else if (input == 'c') {
				// ����
				for (int i = 0; i < data->getCategoryArray()[1]->at(0).getMaterialList().size(); i++) {
					data->getCategoryArray()[1]->at(0).getMaterialList().at(i).decreaseStock(1); // ��� ���ҽ��Ѻ���
					if (data->getCategoryArray()[1]->at(0).getMaterialList().at(i).getStock() < 0) soldout = 1; // ǰ���� ��� ǰ�� üũ
					data->getCategoryArray()[1]->at(0).getMaterialList().at(i).increaseStock(1); // ��� ���󺹱� ��Ű��
				}
				if (soldout == 1) {
					soldout = 0; // ǰ��üũ �ʱ�ȭ
					gotoxy(0, 7 + data->getCategoryArray()[1]->size());
					cout << data->getCategoryArray()[1]->at(0).getName() << "��/�� ǰ���Դϴ�. �ٸ� ��ǰ�� ������ �ֽʽÿ�." << endl;
					gotoxy(0, 0);
					return 2; // �ٽ� ��ǰ ���� ����
				}
				for (int i = 0; i < data->getCategoryArray()[3]->at(0).getMaterialList().size(); i++) {
					data->getCategoryArray()[3]->at(0).getMaterialList().at(i).decreaseStock(1); // ��� ���ҽ��Ѻ���
					if (data->getCategoryArray()[3]->at(0).getMaterialList().at(i).getStock() < 0) soldout = 1; // ǰ���� ��� ǰ�� üũ
					data->getCategoryArray()[3]->at(0).getMaterialList().at(i).increaseStock(1); // ��� ���󺹱� ��Ű��
				}
				if (soldout == 1) {
					soldout = 0; // ǰ��üũ �ʱ�ȭ
					gotoxy(0, 7 + data->getCategoryArray()[3]->size());
					cout << data->getCategoryArray()[3]->at(0).getName() << "��/�� ǰ���Դϴ�. �ٸ� ��ǰ�� ������ �ֽʽÿ�." << endl;
					gotoxy(0, 0);
					return 2; // �ٽ� ��ǰ ���� ����
				}
				// ����
				incresedCartSize = 2; // īƮ 2 �þ
				data->getCurrentCart().push_back(data->getCategoryArray()[1]->at(0)); // ����Ƣ�� �ڵ� ���� 
				data->getCurrentCart().push_back(data->getCategoryArray()[3]->at(0)); // �ݶ� �ڵ� ���� 
				side = true;
				drink = true;
			}
			return 3; // page 3���� �̵�
		}
		else if (input == '0') {
			data->getCurrentCart().pop_back(); // �ڷ� ���� �� īƮ ��� 
			side = false;
			drink = false;
			return 1; // �ڷ� ����
		}
	}
}

int ConsoleView::userUI3() { // ��� ����
	while (1) {
		cout << "* �ڷΰ���(0)\n" << endl;
		cout << "[ īƮ�� ��� ��� : ";
		print_carts_elements(data->getCurrentCart()); // ���� īƮ ��� ��� (����)
		cout << " ]\n" << endl;
		cout << "�� �߰� ��� ���� ��" << endl;

		for (unsigned int i = 0; i < data->getCategoryArray()[4]->size(); i++) // �߰���� ��� ��� 
		{
			cout << "  " << (char)(i + 97) << ". " << data->getCategoryArray()[4]->at(i).getName(); // (i + 97) �� a,b,c ... �� �ǹ�
			gotoxy(22, 5 + i); // ��������
			cout << data->getCategoryArray()[4]->at(i).getKcal() << "Kcal"; // Kcal���
			gotoxy(32, 5 + i); // ��������
			cout << data->getCategoryArray()[4]->at(i).getPrice() << "��" << endl; // Price��� 
		}
		cout << "  * �߰� �� �� : n" << endl;

		cout << "\n - �Է� : ";
		inputs();
		console_clear();
		if (input >= 'a' && input <= 'd' || input == 'n') { // ��� ���� ��
			if (input != 'n') {
				// ����
				for (int i = 0; i < data->getCategoryArray()[4]->at(input - 'a').getMaterialList().size(); i++) {
					data->getCategoryArray()[4]->at(input - 'a').getMaterialList().at(i).decreaseStock(1); // ��� ���ҽ��Ѻ���
					if (data->getCategoryArray()[4]->at(input - 'a').getMaterialList().at(i).getStock() < 0) soldout = 1; // ǰ���� ��� ǰ�� üũ
					data->getCategoryArray()[4]->at(input - 'a').getMaterialList().at(i).increaseStock(1); // ��� ���󺹱� ��Ű��
				}
				if (soldout == 1) {
					soldout = 0; // ǰ��üũ �ʱ�ȭ
					gotoxy(0, 6 + data->getCategoryArray()[4]->size());
					cout << data->getCategoryArray()[4]->at(input - 97).getName() << "��/�� ǰ���Դϴ�. �ٸ� ��ǰ�� ������ �ֽʽÿ�." << endl;
					gotoxy(0, 0);
					return 3; // �ٽ� ��ǰ ���� ����
				}
				// ����
				data->getCurrentCart().push_back(data->getCategoryArray()[4]->at(input - 'a')); // n�� �ƴ� ����, �߰� ��� ���� 
				incresedCartSize = 1; // īƮ 1 �þ 
			}
			else incresedCartSize = 0; // īƮ �ȴþ 
			return 4; // page 4�� �̵�
		}
		else if (input == '0') {
			while (incresedCartSize != 0) {
				data->getCurrentCart().pop_back();
				incresedCartSize--;
			} // �þ īƮ�� ����� 0�� �ɶ����� īƮ �Ѱ��� ��� 
			return 2; // �ڷ� ����
		}
	}
}

int ConsoleView::userUI4() { // ��ǰ ���� & īƮ ���
	while (true) {
		cout << "* �ڷΰ���(0)\n" << endl;
		cout << "[ īƮ�� ��� ��� : ";
		print_carts_elements(data->getCurrentCart()); // ���� īƮ ��� ��� (����)
		cout << " ]\n" << endl;
		if (burger == true && (side == true || drink == true)) { // ���� �����̸鼭 ���ÿ�, ���̵� �Ǵ� ���� ���� �ÿ��� ���
			cout << "�� ��ǰ ���� ��" << endl;
			if (side == false) cout << "  a. ���� ����" << endl;
			else {
				cout << "  a. ���̵� ����" << endl;
				cout << "  b. ���� ����\n" << endl;
			}
		}
		cout << " * īƮ�� ���(y)" << endl;

		cout << "\n - �Է� : ";
		// ����
		if (sold_out != true) inputs();
		else input = change_option;
		sold_out = false;
		// ����

		if (input == 'y') { // īƮ ���
			vector<Product> copiedCart;// ���� īƮ�� �״�� �����س��� īƮ
			copiedCart.assign(data->getCurrentCart().begin(), data->getCurrentCart().end()); // ���� 
			data->getCartList().push_back(copiedCart); // ���纻�� "��� īƮ ���"�� �߰� 
			data->getCurrentCart().clear(); // ���� īƮ ���� (����) 
			console_clear();
			return 0;
		}
		else if (input == '0') { // �ڷ� ����
			while (incresedCartSize != 0) {
				data->getCurrentCart().pop_back();
				incresedCartSize--;
			} // �þ īƮ�� ����� 0�� �ɶ����� īƮ �Ѱ��� ��� 
			console_clear();
			incresedCartSize = data->getCurrentCart().size() - 1; // īƮ����� ������ �þ īƮ�� ������� ���� 
			if (burger == true) return 3; // ���Ÿ� ������ ���, page 3���� �ڷ� ����
			else return 1; // ���Ű� �ƴ� ���, page 1�� �ڷ� ����
		}

		cout << endl;

		vector<Product>* sideList = data->getCategoryArray()[1];
		vector<Product>* drinkList = data->getCategoryArray()[3];

		if (side == true && input == 'a') { // ���̵� ����
			// ����
			change_option = 'a';
			gotoxy(0, 12);
			cout << "�� ���̵� ���� ��" << endl;
			// ����

			for (unsigned int i = 0; i < sideList->size(); i++) // ���̵� ī�װ� ���
			{
				// ����
				cout << "  " << (char)(i + 97) << ". " << sideList->at(i).getName();
				gotoxy(22, 13 + i);
				cout << sideList->at(i).getKcal() << "Kacl";
				gotoxy(32, 13 + i);
				cout << sideList->at(i).getPrice() << "��" << endl;
				// ����
			}

			while (1) {
				cout << "\n - �Է� : ";
				inputs();
				if (input >= 'a' && input <= 'a' + sideList->size() - 1) {
					// ����
					for (int i = 0; i < sideList->at(input - 'a').getMaterialList().size(); i++) {
						sideList->at(input - 'a').getMaterialList().at(i).decreaseStock(1); // ��� ���ҽ��Ѻ���
						if (sideList->at(input - 'a').getMaterialList().at(i).getStock() < 0) soldout = 1; // ǰ���� ��� ǰ�� üũ
						sideList->at(input - 'a').getMaterialList().at(i).increaseStock(1); // ��� ���󺹱� ��Ű��
					}
					if (soldout == 1) {
						soldout = 0; // ǰ��üũ �ʱ�ȭ
						gotoxy(0, 16 + sideList->size());
						cout << sideList->at(input - 97).getName() << "��/�� ǰ���Դϴ�. �ٸ� ��ǰ�� ������ �ֽʽÿ�." << endl;
						gotoxy(0, 0);
						sold_out = true;
						return 4; // �ٽ� ��ǰ ���� ����
					}
					// ����
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
				} // ��Ͽ� ���� ������ �Է½� ���Է�
				gotoxy(0, 13 + sideList->size());
				line_clear(); // �� �� �����
			}
		}
		else if (input == 'b' || (side == false && input == 'a')) { // ���� ����
			//����
			change_option = 'b';
			if (side == false) gotoxy(0, 10);
			else gotoxy(0, 12);
			cout << "�� ���� ���� ��" << endl;
			//����

			for (unsigned int i = 0; i < drinkList->size(); i++) // ���� ī�װ� ���
			{
				// ����
				cout << "  " << (char)(i + 97) << ". " << drinkList->at(i).getName();
				if (side == false) gotoxy(22, 11 + i);
				else gotoxy(22, 13 + i);
				cout << drinkList->at(i).getKcal() << "Kcal";
				if (side == false) gotoxy(32, 11 + i);
				else gotoxy(32, 13 + i);
				cout << drinkList->at(i).getPrice() << "��" << endl;
			}

			while (1) {
				cout << "\n - �Է� : ";
				inputs();
				if (input >= 'a' && input <= 'a' + drinkList->size() - 1) {
					// ����
					for (int i = 0; i < drinkList->at(input - 'a').getMaterialList().size(); i++) {
						drinkList->at(input - 'a').getMaterialList().at(i).decreaseStock(1); // ��� ���ҽ��Ѻ���
						if (drinkList->at(input - 'a').getMaterialList().at(i).getStock() < 0) soldout = 1; // ǰ���� ��� ǰ�� üũ
						drinkList->at(input - 'a').getMaterialList().at(i).increaseStock(1); // ��� ���󺹱� ��Ű��
					}
					if (soldout == 1) {
						soldout = 0; // ǰ��üũ �ʱ�ȭ
						if (side == false) gotoxy(0, 14 + sideList->size());
						else gotoxy(0, 15 + sideList->size());
						cout << drinkList->at(input - 97).getName() << "��/�� ǰ���Դϴ�. �ٸ� ��ǰ�� ������ �ֽʽÿ�." << endl;
						gotoxy(0, 0);
						sold_out = true;
						return 4; // �ٽ� ��ǰ ���� ����
					}
					// ����
					Product newProduct(drinkList->at(input - 'a'));
					vector<Product>& currentCart = data->getCurrentCart();
					switch (option) //burger, side, dessert, drink
					{
					case 'a': //burger
						if (comboAndSet == 'b') //���� + ����
							currentCart.at(1) = newProduct;
						else if (comboAndSet == 'c') //���� + ���� + ���̵�
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

int ConsoleView::userUI5() { // īƮ Ȯ��
	while (1) {
		cout << "* īƮ �� ���(0)\n" << endl;

		cout << "�� īƮ Ȯ�� ��" << endl;

		vector<vector<Product>> cartList = data->getCartList(); // ��� īƮ ��� 

		border_above();
		for (unsigned int i = 0; i < cartList.size(); i++) // ��� īƮ ��� ���
		{
			cout << "�� " << i + 1 << ". ";
			print_all_elements(cartList.at(i));
			gotoxy(101, 4 + i);
			cout << "�� " << endl;
			//����
			if (i == cartList.size() - 1) {
				cout << "�� ";
				print_total(cartList);
				gotoxy(101, 5 + i);
				cout << "�� " << endl;
			}
			//����
		}
		border_bottom();

		cout << "# : Ȯ��" << endl;

		cout << "\n - �Է� : ";
		inputs();
		console_clear();
		if (input == '#') return 6; // ���� ������ page 6���� �̵�
		else if (input == '0') return 0; // �ڷ� ����
	}
}
int ConsoleView::userUI6() { // ����-���� & ���� ����
	while (1) {
		cout << "* �ڷΰ���(0)\n" << endl;
		cout << "�� ���� �Ļ� / ���� ��" << endl;

		cout << "  a. ���� �Ļ�" << endl;
		cout << "  b. ����" << endl;

		cout << "\n - �Է� : ";
		inputs();
		char temp = input; // ���� ���� ���

		if (input == '0') {
			console_clear();
			return 5; // �ڷ� ����
		}
		if (input != 'a' && input != 'b') { // ���� ������ �Է½� ���Է�
			console_clear();
			continue;
		}

		cout << "\n * �����Ͻðڽ��ϱ�? (y/n)" << endl;
		inputs();

		console_clear();
		if (input == 'y') { // �����ϱ�
			if (temp == 'a') { // ���� �ֹ� Ƚ�� ����
				*(data->get_for_here()) += 1;
			}
			else { // ���� �ֹ� Ƚ�� ���� 
				*(data->get_to_go()) += 1;
			}
			fm->update_for_here_to_go(to_string(*(data->get_for_here())) + "_" + to_string(*(data->get_to_go()))); // ���� or ���� - ���� write

			for (int i = 0; i < data->getCartList().size(); i++) { // �ȸ� īƮ����Ʈ ���� 
				for (int j = 0; j < data->getCartList().at(i).size(); j++) { // īƮ����Ʈ�� īƮ ����
					fm->setTime("sold_list.txt");   // @ 
					fm->write("sold_list.txt","/");
					fm->write("sold_list.txt",data->getCartList().at(i).at(j).getName());  //@
					fm->write("sold_list.txt", "/");
					fm->write("sold_list.txt",to_string(data->getCartList().at(i).at(j).getPrice()));  //@

					for (int k = 0; k < data->getCartList().at(i).at(j).getMaterialList().size(); k++) { //īƮ�� ��ǰ ���� 
						/*�쿵*/
						fm->modifyStock("material.txt", 
							data->getCartList().at(i).at(j).getMaterialList().at(k).getName(), 
							data->getCartList().at(i).at(j).getMaterialList().at(k).decreaseStock(1)); // ������ ���� ���� 
					}
					fm->write("sold_list.txt", "\n");  //@
				}
			}
			/*�쿵*/
			data->getCartList().clear(); // ���� �� īƮ����Ʈ ���� 
			return 0; // page 0���� �̵�
		}
	}
}

int ConsoleView::helpUI() {
	while (1) {
		cout << "* �ڷΰ���(0)\n" << endl;
		cout << "< ���� >" << endl;
		// ����
		cout << " ����� ���" << endl;
		cout << "	UI���� ���ĺ� �ҹ��ڷ� ��ǰ�� ������ �� �ִ�" << endl;
		cout << "	0�� �Է��ؼ� ���� UI�� ���ư� �� �ִ�" << endl;
		cout << "	�޺� ���ý� ����� �ݶ� �ڵ����� ���õǸ� ��Ʈ ���ý� ����� �ݶ�, ���̵�� ����Ƣ���� �ڵ����� ���õȴ�" << endl;
		cout << "	��ǰ ������ ������ y�� �Է��ؼ� ������ ��ǰ���� īƮ�� ���� �� �ִ�" << endl;
		cout << "	īƮ��Ͼ��� ���ڸ� �Է��Ͽ� �� īƮ�� ���� �� �ִ�\n" << endl;
		cout << " ������ ���" << endl;
		cout << "	UI���� ���ڸ� �Է��Ͽ� ��ǰ�߰�/�������߰�/���Ȯ�� ���� �����ϴ�" << endl;
		// ����
		cout << "\n - �Է� : ";
		inputs();

		if (input == '0') {
			console_clear();
			return 0;
		}
	}
}

int ConsoleView::adminUI0() {
	while (1) {
		cout << "�� ������ ��� ��" << endl;
		cout << " 1. ����ǰ �߰�" << endl;
		cout << " 2. ���� ��ǰ ����" << endl;
		cout << " 3. ��� ��� �߰�" << endl;
		cout << " 4. ��� �ڷ� ��ȸ" << endl;
		cout << " 5. ��� ���� ����" << endl; /*���*/
		cout << " 6. ����� ���\n" << endl; /*���*/

		cout << " * Ű����ũ ����(E)" << endl;

		cout << "\n - �Է� : ";
		inputs();

		console_clear();
		// page �̵�
		if (input == '1') return 8;
		if (input == '2') return 9;
		if (input == '3') return 10;
		if (input == '4') return 11;
		if (input == '5') return 12; /*���*/
		if (input == '6') return 0; /*���*/
		if (input == 'E') return -1;
	}
	return 0;
}

int ConsoleView::adminUI1() { // ����ǰ �߰�
	while (1) {
		string fileName;
		cout << "* �ڷΰ���(0)\n" << endl;
		cout << "�� ����ǰ �߰� ��" << endl;
		cout << " 1. ����" << endl;
		cout << " 2. ���̵�" << endl;
		cout << " 3. ����Ʈ" << endl;
		cout << " 4. ����\n" << endl;
		cout << "\n - �Է� : ";
		inputs();
		cout << endl;

		if (input == '0') { // �ڷ� ����
			console_clear();
			return 7;
		}

		vector<Product>* selected_category = data->getCategoryArray()[0]; // �ʱ�ȭ (�ƹ��ų���)
		if (input == '1') { 
			selected_category = data->getCategoryArray()[0]; 
			fileName = "product_burger.txt";
		}// ���� 
		else if (input == '2') { 
			selected_category = data->getCategoryArray()[1]; 
			fileName = "product_side.txt";
		} // ���̵� 
		else if (input == '3') { 
			selected_category = data->getCategoryArray()[2]; 
			fileName = "product_dessert.txt";
		}// ����Ʈ 
		else if (input == '4') {
			selected_category = data->getCategoryArray()[3]; 
			fileName = "product_drink.txt";
		}// ���� 

		cout << " - ��ǰ ��� -" << endl;
		for (unsigned int i = 0; i < selected_category->size(); i++) // ������ ī�װ� ��� ���
		{
			cout << "  * " << selected_category->at(i).getName() << endl;
		}
		cout << "  * �ڷΰ���(0)" << endl;
		string product_name = ""; // ����ǰ��
		cout << "\n �� �߰��� ����ǰ��(���� 2��) : ";
		getline(cin, product_name);
		if (product_name.at(0) == '0') {
			console_clear();
			return 8;
		}
		cin.clear();
		cin.ignore();

		cout << "\n - ��� ��� -" << endl;
		vector<Material>* materialList = data->getMaterialCategory(); //;
		for (unsigned int i = 0; i < materialList->size(); i++) // ��� ��� ���
		{
			cout << "  " << (i + 1) << ". " << materialList->at(i).getName() << endl;
		}

		cout << "\n �� ����ǰ�� ������ ��� (����� ���� ���� ����) : ";

		string materials_input;
		getline(cin, materials_input); // ���� ������ tokenizing �� ����
		stringstream ss(materials_input);

		vector<int> material_indices; // �Ľ̵� token���� ������ ����
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
		for (unsigned int i = 0; i < material_indices.size(); i++) // ����ǰ�� ������ ��� ����� ���Ϳ� ä���
		{
			materials_for_new.push_back(data->getMaterialCategory()->at(material_indices.at(i)));
			materialNumList[i] = material_indices.at(i)+1;
		}
		fm->addProduct(fileName, product_name, materialNumList, material_indices.size());
		selected_category->push_back(Product(product_name, materials_for_new)); // ����ǰ�� �ش� ī�װ��� �߰� 

		console_clear();
	}
}

int ConsoleView::adminUI2() { // ���� ��ǰ ����
	string fileName;
	while (1) {
		cout << "* �ڷΰ���(0)\n" << endl;
		cout << "�� ���� ��ǰ ���� ��" << endl;
		cout << " 1. ����" << endl;
		cout << " 2. ���̵�" << endl;
		cout << " 3. ����Ʈ" << endl;
		cout << " 4. ����\n" << endl;
		cout << "\n - �Է� : ";
		inputs();
		cout << endl;

		if (input == '0') { // �ڷ� ����
			console_clear();
			return 7;
		}
		if (input <= '0' || input >= '5') { // �������� ���� �Է�
			console_clear();
			continue;
		}

		vector<Product>* selected_category = data->getCategoryArray()[0]; // �ʱ�ȭ (�ƹ��ų�)
		if (input == '1') { 
			selected_category = data->getCategoryArray()[0]; 
			fileName = "product_burger.txt";
		} // ����
		else if (input == '2') { 
			selected_category = data->getCategoryArray()[1]; 
			fileName = "product_side.txt"; 
		} // ���̵� 
		else if (input == '3') { 
			selected_category = data->getCategoryArray()[2]; 
			fileName = "product_dessert.txt"; 
		} // ����Ʈ 
		else if (input == '4') {
			selected_category = data->getCategoryArray()[3];
			fileName = "product_drink.txt";
		}// ���� 

		for (unsigned int i = 0; i < selected_category->size(); i++) // ��ǰ ��� ���
			cout << "  " << (i + 1) << ". " << selected_category->at(i).getName() << endl;
		cout << "  0. �ڷ� ����" << endl;

		cout << endl;

		while (1) {
			cout << " - �Է� : ";
			inputs();

			int set; char * toss;
			toss = &input;
			set = atoi(toss);

			if (input >= '1' && input <= '1' + selected_category->size() - 1) {
				/*�쿵*/
				fm->deleteProduct(fileName, selected_category->at(input-'1').getName());
				selected_category->erase(selected_category->begin() + set - 1);

				break; 
			} // �������� �ִ� ��ȣ�� �Է��ؾ�, break
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

int ConsoleView::adminUI3() { // ��� ��� �Է�
	while (1) {
		cout << "* �ڷΰ���(0)\n" << endl;
		cout << "�� ��� ��� �߰� ��" << endl;
		vector<Material>* materialCategory = data->getMaterialCategory(); // ��� ī�װ� 
		for (unsigned int i = 0; i < materialCategory->size(); i++)
		{
			cout << "  " << (i + 1) << ". " << materialCategory->at(i).getName()
				<< " : " << materialCategory->at(i).getStock() << "��" << endl;
		}

		cout << "\n - �߰��� ��� : ";
		int num;
		cin >> num;

		if (num >= 1 && num <= 1 + materialCategory->size() - 1) { // ��� ����
			cout << " - �߰��� ���� : ";
			int stock;
			cin >> stock;
			cin.clear();
			cin.ignore(1, '\n');
			fm->modifyStock("material.txt", materialCategory->at(num - 1).getName(), materialCategory->at(num - 1).getStock() + stock);
			materialCategory->at(num - 1).increaseStock(stock); // ��� �߰�
			console_clear();
		}
		else if (num == 0) { // �ڷ� ����
			console_clear();
			return 7;
		}
		console_clear();
	}
	return 0;
}
/*����*/
int ConsoleView::adminUI4() { // ��� �ڷ� ��ȸ
	while (1) {
		data->get_info();

		cout << "�� ��� �ڷ� ��ȸ ��\n" << endl;
		cout << " 1. �� ����� : " << data->get_total_sale_txt() << "��" << endl;
		cout << "\n 2. ���� �Ǹ� : " << *(data->get_for_here()) << "ȸ" << endl;
		cout << "    ���� �Ǹ� : " << *(data->get_to_go()) << "ȸ" << endl;
		cout << "\n 3. ��ǰ�� �Ǹ� ��Ȳ" << endl; // ��ǰ ����, �Ǹ� ����, �Ǹ� ����
		cout << "\n  ����ǰ��"; gotoxy(22, 9); cout << "�װ���"; gotoxy(32, 9); cout << "���Ǹ� ����"; gotoxy(45, 9); cout << "����ǰ ����" << endl;

		vector<Product>* selected_category = data->getCategoryArray()[0]; // �ʱ�ȭ (�ƹ��ų�)

		int set = 0;
		
		for (int i = 0; i < 5; i++) {
			selected_category = data->getCategoryArray()[i];
			for (unsigned int j = 0; j < selected_category->size(); j++) {
				cout << "    " << selected_category->at(j).getName(); gotoxy(24, 10 + set + j); cout << selected_category->at(j).getPrice() << "��"; gotoxy(34, 10 + set + j);
				cout << data->get_count_product_sale(selected_category->at(j).getName()) << "��";
				gotoxy(47, 10 + set + j); cout << data->get_product_sales(selected_category->at(j).getName()) << "��" << endl;
			}
			set += selected_category->size();
		}
		
		gotoxy(24, 10 + set); cout << "\n 4. �ð��뺰 �˻� : " << endl;
		gotoxy(24, 11 + set); cout << " * �ڷ� ������ 0, �˻��Ϸ��� 1 �Է� : ";
		inputs();

		data->get_saveList()->clear();

		if (input == '0') { // �ڷ� ����
			console_clear();
			return 7;
		}
		else if (input == '1') { // �˻�
			console_clear();
		}
		else { // �߸��� �Է�
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
			cout << "   - �� : "; cin >> year_from; time_from.push_back(year_from);
			cout << "   - �� : "; cin >> month_from; time_from.push_back(month_from);
			cout << "   - �� : "; cin >> day_from; time_from.push_back(day_from);
			cout << "   - �� : "; cin >> hour_from; time_from.push_back(hour_from);
			cout << "   - �� : "; cin >> min_from; time_from.push_back(min_from);
			cout << "\n  < To >" << endl;
			cout << "   - �� : "; cin >> year_to; time_to.push_back(year_to);
			cout << "   - �� : "; cin >> month_to; time_to.push_back(month_to);
			cout << "   - �� : "; cin >> day_to; time_to.push_back(day_to);
			cout << "   - �� : "; cin >> hour_to; time_to.push_back(hour_to);
			cout << "   - �� : "; cin >> min_to; time_to.push_back(min_to);

			// ��� ���
			cout << "\n�� " << year_from << "�� " << month_from << "�� " << day_from << "�� " << hour_from << "�� " << min_from << "�� ~ " << year_to << "�� " << month_to << "�� " << day_to << "�� " << hour_to << "�� " << min_to << "��" << endl;
			cout << "\n  ����ǰ��"; gotoxy(22, 16); cout << "�װ���"; gotoxy(32, 16); cout << "���Ǹ� �ð�"; //gotoxy(45, 16); 

			// for���� ������ ����ϵ�, gotoxy�� y��ǥ�� 15���� 1�� ����
			vector<vector<string>>* time_match_list = data->find_time(time_from, time_to);
			for (unsigned int i = 0; i < time_match_list->size(); i++) {
				gotoxy(0, 18 + i); cout << "    " << time_match_list->at(i).at(5); gotoxy(24, 18 + i);
				cout << time_match_list->at(i).at(6); gotoxy(34, 18 + i);
				cout << time_match_list->at(i).at(0) << "-" <<
					time_match_list->at(i).at(1) << "/" << time_match_list->at(i).at(2) << "-" <<
					time_match_list->at(i).at(3) << ":" << time_match_list->at(i).at(4);    //gotoxy(47, 18);
			}

			gotoxy(0, 19 + time_match_list->size());
			cout << " �� �� ����: " << data->get_total_sale_intime() << "�� (" << (data->get_interval_time() / 60 + 1) << "�� ��)" << endl;
			cout << " �� �д� �Ǹ�����: " << data->get_total_sale_intime() / (data->get_interval_time() / 60 + 1) << "��" << endl;

			time_match_list->clear();
			data->get_saveList()->clear();

			cout << "\n * �ڷ� ������ 0, �ٽ� �˻��Ϸ��� 1 �Է� : ";
			inputs();
			if (input == '0') { // �ڷ� ����
				console_clear();
				break;
			}
			else { // �ٽ� �˻�
				console_clear();
			}
		}
	}
}
/*����*/
int ConsoleView::adminUI5() { // ���� ���� /*���*/
	while (1) {
		cout << "* �ڷΰ���(0)\n" << endl;
		cout << "�� ���� ���� ��\n" << endl;
		vector<Material>* materialCategory = data->getMaterialCategory(); // ��� ī�װ� 
		for (unsigned int i = 0; i < materialCategory->size(); i++) // ��� ���
		{
			cout << "  " << (i + 1) << ". " << materialCategory->at(i).getName()
				<< " : " << materialCategory->at(i).getPrice() << "��" << endl;
		}

		int index;
		cout << "\n - ������ ��� : "; 
		cin >> index; // 1 �Է½� 0��° ��� ���� / 2 �Է½� 1��° ��� ����
		cin.clear();

		if (index == 0) { // �ڷ� ����
			console_clear();
			return 7;
		}

		if (index < 1 || index > 20) { // ���Է�
			console_clear();
			continue;
		}
		else {
			int price;
			cout << "\n - ������ ���� : ";
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


//����
void ConsoleView::print_carts_elements(vector<Product>& list) {
	if (list.size() == 0) return;
	for (unsigned int i = 0; i < list.size() - 1; i++)
	{
		cout << list.at(i).getName() << "(" << list.at(i).getKcal() << "Kcal/" << list.at(i).getPrice() << "��)" << " + ";
		cartkcal += list.at(i).getKcal();
		cartprice += list.at(i).getPrice();
	}
	cout << list.at(list.size() - 1).getName() << "(" << list.at(list.size() - 1).getKcal() << " Kcal/" << list.at(list.size() - 1).getPrice() << "��)";
	cartkcal += list.at(list.size() - 1).getKcal();
	cartprice += list.at(list.size() - 1).getPrice();
	cout << " �� " << cartkcal << "Kcal/" << cartprice << "��";
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
	cout << " �� " << cartkcal << "Kcal/" << cartprice << "��";
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
	cout << " [��" << totalkcal << "Kcal/" << totalprice << "��]" << endl;
}
// ����

void ConsoleView::line_clear() {
	cout << "\33[2K";
}

void ConsoleView::console_clear() {
	system("cls");
}

void ConsoleView::border_above() {
	cout << "��";
	for (int i = 0; i < 100; i++)
	{
		cout << "��";
	}
	cout << "��" << endl;
}

void ConsoleView::border_bottom() {
	cout << "��";
	for (int i = 0; i < 100; i++)
	{
		cout << "��";
	}
	cout << "��" << endl;
}

void ConsoleView::pay() {
	cout << "��";
	for (int i = 0; i < 12; i++)
	{
		cout << "��";
	}
	cout << "��" << endl;

	cout << "�� $. �����ϱ⦢" << endl;

	cout << "��";
	for (int i = 0; i < 12; i++)
	{
		cout << "��";
	}
	cout << "��" << endl;
}

void ConsoleView::inputs() {
	cin >> input;
	cin.clear();
	cin.ignore(1, '\n');
}