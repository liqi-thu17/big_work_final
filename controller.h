#pragma once
#include "ui.h"
#include "basesystem.h"
#include <unordered_map>

class Controller {
	UI ui;
	BaseSystem system;
public:
	//ʵ��Base�ĸ��ֹ���
	void operate();
};