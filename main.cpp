#include <iostream>
#include "Grid.h"

int main()
{
	// Тест ввода из stdin
	Grid<int> dude1(2, 2);
	dude1 = 0;
	std::cin >> dude1;
	std::cout << dude1 << '\n';

	// Тест присваивания всего
	Grid<int> dude2(2, 2);
	dude2 = 5;
	std::cout << dude2 << '\n';

	// Тест присваивание отдельных значений
	Grid<int> dude3(2, 2);
	dude3 = 0;
	dude3(1, 1) = 6;
	dude3(1, 0) = 89;
	std::cout << dude3 << '\n';

	// Тест получения размера
	Grid<int> dude4(2, 2);
	std::cout << dude4.get_xsize() << ' ' << dude4.get_ysize() << '\n';

	// Тест получения значения
	Grid<int> dude5(2, 2);
	dude5 = 0;
	dude5(1, 1) = 6;
	dude5(1, 0) = 89;
	std::cout << dude5(1, 0) << '\n';

	// Тест вывода
	Grid<int> dude6(2, 2);
	dude6 = 0;
	dude6(1, 1) = 6;
	dude6(1, 0) = 100;
	std::cout << dude6 << '\n';

	// Bugfix
	Grid<int> dude7(1, 100);
	dude7 = 0;
	dude7(0, 50) = 6;
	std::cout << dude7 << '\n';

	Grid<int> dude8(100, 1);
	dude8 = 0;
	dude8(50, 0) = 6;
	std::cout << dude8 << '\n';

	return 0;
}