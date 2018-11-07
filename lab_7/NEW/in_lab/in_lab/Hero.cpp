#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Hero.h"

namespace sict
{
	Hero::Hero()
		: m_Health(0),
		  m_Attack(0)
	{
		m_Name[0] = '\0';
	}

	Hero::Hero(const char* Name, int Health, int Attack)
	{
		bool paramsValid = Health > 0 && Attack > 0 && (Name[0] != '\0' && Name != nullptr);

		if (paramsValid)
		{
			m_Health = Health;
			m_Attack = Attack;

			// TODO: Check on this later...
			strncpy(m_Name, Name, strlen(Name));
			m_Name[strlen(Name)] = '\0';
		}
	}

	Hero::~Hero()
	{
	}

	void Hero::operator-=(int attack)
	{
		if (attack > 0)
		{
			m_Health -= attack;
			if (m_Health < 0)
				m_Health = 0;
		}
	}

	bool Hero::isAlive() const
	{
		return m_Health > 0;
	}

	bool Hero::isEmpty() const
	{
		return m_Name[0] == '\0' || m_Name == nullptr;
	}

	int Hero::getHealth() const
	{
		return this->m_Health;
	}

	int Hero::attackStrength() const
	{
		return this->m_Attack;
	}

	const char * Hero::getName() const
	{
		return this->m_Name;
	}

	std::ostream& operator<<(std::ostream & os, const Hero& hero)
	{
		if (hero.isEmpty())
			os << "No hero";
		else
			os << hero.m_Name;
		return os;
	}

	// Only locals can be modified
	const Hero & operator*(const Hero& first, const Hero& second)
	{
		Hero left = first, right = second;
		return HeroesBattle(left, right);
	}

	Hero& HeroesBattle(Hero& left, Hero& right)
	{
		int rounds = 0;

		std::cout << "Ancient Battle! " << left.getName() << " vs " << right.getName();

		for (int i = 0; i < max_rounds && left.isAlive() && right.isAlive(); i++)
		{
			left -= right.attackStrength();
			right -= left.attackStrength();
			++rounds;
		}

		Hero winner = HealthCompare(left, right);
		std::cout << " : Winner is " << winner.getName() << " in " << rounds << " rounds." << std::endl;

		return winner;
	}

	Hero & HealthCompare(Hero & first, Hero & second)
	{
		if (first.getHealth() > second.getHealth())
			return first;
		else
			return second;
	}

}

