#include "g_rand.hpp"
#include "drops.hpp"
#include "stats.hpp"
#include "box.hpp"

#include <iostream>
#include <array>
#include <string>
#include <span>
#include <map>

double BoxHits(size_t num_hits, const std::string& map, const std::string& goal_weapon, bool mule, bool give_weapons);
double FirstBox(size_t num_repetitions, const std::string& map, std::span<std::string> goal_weapons);
std::vector<size_t> Trades(size_t num_repetitions, const std::string& map, const std::string& goal_weapon, bool mule);

int main() {

	std::array<std::string, 2> weaps = { "tgun", "gersch" };
	const auto chance = FirstBox(10000000, "ascension", weaps);
	std::cout << chance;
	return 0;
}

double BoxHits(size_t num_hits, const std::string& map, const std::string& weapon, bool mule, bool give_weapons)
{
	rng::G_Rand rand;
	sim::Box box(rand, map);

	size_t x = box.Simulate(num_hits, weapon, mule, give_weapons);

	std::cout << "n = " << num_hits << "\n";
	std::cout << "x = " << x << "\n";
	std::cout << "average = " << (double)num_hits/(double)x << "\n";

	return (double)num_hits / (double)x;
}

/* assumes you have room in inventory for 2 box weapons */
double FirstBox(size_t num_repetitions, const std::string& map, std::span<std::string> goal_weapons) {
	rng::G_Rand rand;
	sim::Box box(rand, map);

	size_t count = 0;
	for (size_t i = 0; i < num_repetitions; i++) {
		count += box.SimulateFirstBox(goal_weapons, true);
	}

	std::cout << "n = " << num_repetitions << "\n";
	std::cout << "x = " << count << "\n";
	std::cout << "chance = " << ((double)count / (double)num_repetitions) * 100.0 << "%" << "\n";

	return (double)count / (double)num_repetitions;
}

/* assumes you start trade with a wall weapon */
std::vector<size_t> Trades(size_t num_repetitions, const std::string& map, const std::string& goal_weapon, bool mule)
{
	rng::G_Rand rand;
	sim::Box box(rand, map);

	std::vector<size_t> results(num_repetitions);

	for (size_t i = 0; i < num_repetitions; i++) {
		results[i] = box.SimulateTrade(goal_weapon, mule, true, true);
	}

	return results;
}
