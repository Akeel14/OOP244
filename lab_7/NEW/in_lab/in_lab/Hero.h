#pragma once

#include <iostream>
namespace sict
{
	const int max_rounds = 100;

	class Hero
	{
		int m_Health;
		int m_Attack;
		char m_Name[41];
	public:
		Hero();
		Hero(const char* Name, int Health, int Attack);
		~Hero();

		void operator-=(int attack);
		bool isAlive() const;
		bool isEmpty() const;
		int getHealth() const;
		int attackStrength() const;
		friend std::ostream& operator<<(std::ostream& os, const Hero& hero);

		const char* getName() const;
	};

	const Hero& operator*(const Hero& first, const Hero& second);
	Hero& HeroesBattle(Hero& first, Hero& second);
	Hero& HealthCompare(Hero& first, Hero& second);
}
