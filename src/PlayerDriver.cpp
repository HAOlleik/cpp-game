#pragma once

#include "Player.h"


void testPlayers()
{
	vector<string*>terList;
	vector<string*>cardList;
	vector<Order*>orderList;

	string asia = "Asia";
	string africa = "Africa";
	string europe = "Europe";
	string southAm = "South America";
	string northAm = "North America";

	terList.push_back(&asia);
	terList.push_back(&africa);
	terList.push_back(&europe);
	terList.push_back(&southAm);
	terList.push_back(&northAm);

	string bombC = "bomb";
	string reinf = "reinforcement";
	string blockadeC = "blockade";
	string airliftC = "airlift";
	string diplomacy = "diplomacy";

	cardList.push_back(&bombC);
	cardList.push_back(&reinf);
	cardList.push_back(&blockadeC);
	cardList.push_back(&airliftC);
	cardList.push_back(&diplomacy);

	string name = "Yason";
	Player* p1 = new Player(name, terList, cardList, orderList);
	(*p1).issueOrder("deploy");
	(*p1).issueOrder("bomb");
	(*p1).issueOrder("negotiate");
	(*p1).toAttack();
	(*p1).toDefend();
}