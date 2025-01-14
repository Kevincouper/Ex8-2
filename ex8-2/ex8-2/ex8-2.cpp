#include "pch.h"
#include <iostream>
#include <vector>
#include "dragon.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

int main() {
	
	json jsonDragon;
	std::ifstream inFileDragon("Dragon.json");
	inFileDragon >> jsonDragon;
	Dragon dragon = Dragon(jsonDragon["health"], jsonDragon["attack"]);
	inFileDragon.close();

	json jsonPigs;
	std::ifstream inFilePigs("Pigs.json");
	inFilePigs >> jsonPigs;
	std::vector<Pig>pigs;

	const auto nbPig = 10;

	pigs.reserve(nbPig);
	for (auto i = 0; i < nbPig; i++)
	{
		pigs.emplace_back(Pig(jsonPigs["health"], jsonPigs["attack"]));
	}
	inFilePigs.close();

	bool finish = false;
	while (!finish)
	{
		//Dragon attack
		for (auto& pig : pigs)
		{
			if (pig.IsAlive())
			{
				dragon.Attack(pig);
				break; //Dragon attack once
			}
		}

		//Pigs attack
		for (auto& pig : pigs)
		{
			pig.Attack(dragon);
		}

		//print Dragon
		dragon.Print();

		//print Pigs
		for (auto& pig : pigs)
		{
			pig.Print();
		}

		std::cout << "=======================\n";

		//Victory conditions
		if (!dragon.IsAlive())
		{
			finish = true;
		}

		bool allPigsDead = true;
		for (auto& pig : pigs)
		{
			if (pig.IsAlive())
			{
				allPigsDead = false;
				break;
			}
		}
		if (allPigsDead)
		{
			finish = true;
		}
	}
	system("pause");
	return 0;

}