#include "Player.h"

void testPlayers()
{
	vector<string *> terList;
	vector<string *> cardList;
	vector<Order *> orderList;

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

	string value = "Yason";
	string *name = &value;
	Player *p1 = new Player(name, terList, cardList, orderList);
	string value1 = "deploy";
	string *issue1 = &value1;
	string value2 = "bomb";
	string *issue2 = &value2;
	string value3 = "negotiate";
	string *issue3 = &value3;
	(*p1).issueOrder(issue1);
	(*p1).issueOrder(issue2);
	(*p1).issueOrder(issue3);
	(*p1).toAttack();
	(*p1).toDefend();
}