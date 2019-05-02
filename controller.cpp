#include "controller.h"
#include <sstream>

void Controller::operate() {
	while (true) {
		std::stringstream myinput = ui.getCommand();
		static std::string order;
		//��������
		static std::string show;

		myinput >> order;
		//�������ݿ���
		if (order == "CREATE") {
			myinput >> order;
			if (order == "DATABASE") {
				getline(myinput, order, ' ');
				getline(myinput, order);
				system.addBase(order);
			}
			else if (order == "TABLE") {
				getline(myinput, order, ' ');
				getline(myinput, order);
				system.setTable(order);
			}
			else {
				std::cout << "δʶ�������" << std::endl;
			}
		}
		//�л����ݿ�
		else if (order == "USE") {
			getline(myinput, order, ' ');
			getline(myinput, order);
			show = order;
			system.setBase(order);
		}
		//ɾ�����ݿ�
		else if (order == "DROP") {
			myinput >> order;
			if (order == "DATABASE") {
				getline(myinput, order, ' ');
				getline(myinput, order);
				system.dropBase(order);
			}
			else if (order == "TABLE") {
				getline(myinput, order, ' ');
				getline(myinput, order);
				system.dropTable(show,order);
			}
		}
		//�г��������ݿ⼰����������б���
		else if (order == "INSERT") {
			getline(myinput, order, ' ');
			getline(myinput, order);
			system.addData(order);
		}
		else if (order == "SHOW") {
			myinput >> order;
			if (order == "DATABASES") {
				system.showBase();
			}
			else if (order == "TABLES") {
				system.showTable(show);
			}
			else {
				getline(myinput, order, ' ');
				getline(myinput, order, ' ');
				getline(myinput, order);
				system.show_table_colums(show, order);
			}
		}
		//�������ɾ��
		else if (order == "DELETE") {
			getline(myinput, order, ' ');
			getline(myinput, order);
			system.Delete(order);
		}
		//��������޸�
		else if (order == "UPDATE") {
			getline(myinput, order);
			system.updateData(order);
		}
		//��Ĳ�ѯ
		//ʵ��whereClauses���
		else if (order == "SELECT") {
			getline(myinput, order, ' ');
			getline(myinput, order);
			system.select(order);
		}
		else if (order == "QUIT") {
			break;
		}
		else {
			std::cout << "δʶ�������" << std::endl;
		}
	}
}