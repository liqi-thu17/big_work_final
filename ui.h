#pragma once
#include <string>

class UI {
public:
	//������ð����򻯵ĸ������ܷ�װ�ɽӿڣ�Ȼ����ͳһ����
	void preProcess(std::string&);
	std::stringstream getCommand();
};