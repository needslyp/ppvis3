#include <iostream>
#include <conio.h>
#include <fstream>
#include "place.h"

using namespace std;
using namespace meadow_life;

int main()
{
	char input;
	int x_size = 14, y_size = 5;
	int r = 5,  // rabbit
		d = 3,  // deer
		s = 3, //squirell
		w = 3,  // wolf
		b = 3,  // bear
		p = 10; // plant

	for (int i = 0; i < 40; i++)
		cout << "-";
	cout << "\nUse file\t\t---> TAB\n";
	for (int i = 0; i < 40; i++)
		cout << "-";
	cout << "\nUse keyboard\t\t---> SPACE\n";
	for (int i = 0; i < 40; i++)
		cout << "-";
	cout << "\nUse preset (14x5)\t---> ENTER\n";
	for (int i = 0; i < 40; i++)
		cout << "-";

	input = _getch();
	system("cls");
	if (input == ' ') // SPACE
	{
		try
		{
			cout << "Enter the game table size (AxB): ";
			cin >> x_size >> y_size;
			cout << "Enter organism numbers (R -> D -> S -> W -> B -> P): ";
			cin >> r >> d >> s >> w >> b >> p;
			if (r + d + s + w + b + p > (x_size * y_size) * 4 || p > (x_size * y_size))
			{
				throw;
			}
		}
		catch (...)
		{
			cout << "Too many orgals, using default positioning instead!\n";
			x_size = 14;
			y_size = 5;
			r = 5;
			d = 3;
			s = 3;
			w = 3;
			b = 3;
			p = 10;
			_getch();
		}
	}
	if (input == '\011') // TAB
	{
		string filename;
		fstream file;
		int test;
		while (true)
		{
			cout << "Enter filename: ";
			cin >> filename;
			try
			{
				file.open(filename);
				if (!file.is_open())
				{
					throw 1;
				}
				break;
			}
			catch (int)
			{
				system("cls");
				cout << "File not found!\n";
			}
		}

		file >> x_size >> y_size >> r >> d >> s >> w >> b >> p;
		file.close();
	}
	if (input == '\033')
		return 0; // ESC


	srand(time(0));
	Meadow_master meadow(x_size, y_size);

	system("cls");
	meadow.start_random_place(r, d, s, w, b, p);
	meadow.Show();

	int move_count = 0;
	while (true)
	{
		move_count++;
		cout << "Move #" << move_count << endl;
		input = _getch();
		if (input == '\033')
			return 0; // if you press ESC, the program ends
		meadow.Tick();
	}
}
