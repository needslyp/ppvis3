#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <time.h>

using namespace std;


namespace meadow_life
{
	class Meadow_field
	{
		int width, height;
	public:
		char*** scene;
		Meadow_field(int width_inp, int height_inp)
		{
			width = width_inp;
			height = height_inp;
			scene = new char** [width];
			for (int i = 0; i < width; i++)
				scene[i] = new char* [height];

			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					scene[i][j] = new char[4];
					for (int k = 0; k < 4; k++)
					{
						scene[i][j][k] = ' ';
					}
				}
			}
		}

		void put_org(int posX, int posY, int posI, char org_type)
		{
			scene[posX][posY][posI] = org_type;
		}

		void display_field();

		int get_width()
		{
			return width;
		}

		int get_height()
		{
			return height;
		}
	};

	class Organism
	{
	protected:
		char type;
		int age, id, hp, hp_max, food, food_max, moves;
		bool isMale;
		int location[3]; //3 coordinates - x, y, index
	public:
		char get_type()
		{
			return type;
		}
		int get_age()
		{
			return age;
		}
		int get_id()
		{
			return id;
		}
		int get_hp()
		{
			return hp;
		}
		int get_hp_max()
		{
			return hp_max;
		}
		int get_food()
		{
			return food;
		}
		int get_food_max()
		{
			return food_max;
		}
		int get_moves()
		{
			return moves;
		}
		bool get_isMale()
		{
			return isMale;
		}
		int& get_location(int index)
		{
			return location[index];
		}
		void set_type(char inp_type)
		{
			this->type = inp_type;
		}
		void set_age(int inp_age)
		{
			this->age = inp_age;
		}
		void set_id(int inp_id)
		{
			this->id = inp_id;
		}
		void set_hp(int inp_hp)
		{
			this->hp = inp_hp;
		}
		void set_food(int inp_food)
		{
			this->food = inp_food;
		}
		void set_location(int coord, int count)
		{
			location[coord] = count;
		}
	};

	class Plant : public Organism
	{
	public:
		Plant()
		{
			hp_max = 2;
			hp = hp_max;
			moves = 0;
			age = 0;
			type = 'P';
		}
	};

	class Predator : public Organism
	{
	protected:
		int damage;
	public:
		int get_damage()
		{
			return damage;
		}
	};

	class Wolf : public Predator
	{
	public:
		Wolf(string sex)
		{
			hp_max = 140;
			hp = hp_max;
			food_max = 35;
			food = food_max;
			moves = 4;
			damage = 15;
			age = 0;
			type = 'W';
			if (sex == "Male")
				isMale = true;
			if (sex == "Female")
				isMale = false;
			if (sex == "Random")
				isMale = rand() % 2;
		}
	};

	class Bear : public Predator
	{
	public:
		Bear(string sex)
		{
			hp_max = 170;
			hp = hp_max;
			food_max = 40;
			food = food_max;
			moves = 3;
			damage = 20;
			age = 0;
			type = 'B';
			if (sex == "Male")
				isMale = true;
			if (sex == "Female")
				isMale = false;
			if (sex == "Random")
				isMale = rand() % 2;
		}
	};

	class Victim : public Organism
	{
	};

	class Rabbit : public Victim
	{
	public:
		Rabbit(string sex)
		{
			hp_max = 70;
			hp = hp_max;
			food_max = 25;
			food = food_max;
			moves = 3;
			age = 0;
			type = 'R';
			if (sex == "Male")
				isMale = true;
			if (sex == "Female")
				isMale = false;
			if (sex == "Random")
				isMale = rand() % 2;
		}
	};

	class Deer : public Victim
	{
	public:
		Deer(string sex)
		{
			hp_max = 140;
			hp = hp_max;
			food_max = 20;
			food = food_max;
			moves = 4;
			age = 0;
			type = 'D';
			if (sex == "Male")
				isMale = true;
			if (sex == "Female")
				isMale = false;
			if (sex == "Random")
				isMale = rand() % 2;
		}
	};

	class Squirell : public Victim
	{
	public:
		Squirell(string sex)
		{
			hp_max = 50;
			hp = hp_max;
			food_max = 15;
			food = food_max;
			moves = 3;
			age = 0;
			type = 'D';
			if (sex == "Male")
				isMale = true;
			if (sex == "Female")
				isMale = false;
			if (sex == "Random")
				isMale = rand() % 2;
		}
	};


	class Meadow_master
	{
		Meadow_field* meadow_table;

		vector<Rabbit> org_rabbit;
		int rabbit_number;
		vector<Deer> org_deer;
		int deer_number;
		vector<Squirell> org_squirell;
		int squirell_number;
		vector<Wolf> org_wolf;
		int wolf_number;
		vector<Bear> org_bear;
		int bear_number;
		vector<Plant> org_plant;
		int plant_number;
		Plant* p_extra = new Plant();
		Deer* d_extra = new Deer("Random");
		Rabbit* r_extra = new Rabbit("Random");
		Squirell* s_extra = new Squirell("Random");

		int* find_empty_cell(bool isPlant);

		//PLANT

		void Plant_replicate(Plant* p_obj);

		void Plant_age(Plant* p_obj, int order);

		//VICTIMS

		void Victim_move(Victim* c_obj);

		void Victim_eat(Victim* c_obj);

		void Victim_replicate(Victim* c_obj);

		void Victim_age(Victim* c_obj, int order);

		//PREDATORS

		void Predator_move(Predator* c_obj);

		void Predator_eat(Predator* c_obj);

		void Predator_replicate(Predator* c_obj);

		void Predator_age(Predator* c_obj, int order);

		//EVERYTHING ELSE

		Plant& return_plant(int x, int y);

		Deer& return_deer(int x, int y);

		Rabbit& return_rabbit(int x, int y);

		Squirell& return_squirell(int x, int y);

		int empty_place(int x, int y, bool isPlant); //checking what cell is available for moving into

	public:
		Meadow_master(int width_inp, int height_inp)
		{
			srand(time(0));
			meadow_table = new Meadow_field(width_inp, height_inp);
			rabbit_number = 0;
			deer_number = 0;
			squirell_number = 0;
			wolf_number = 0;
			bear_number = 0;
			plant_number = 0;
		}

		void Tick();

		void Show();

		void start_random_place(int r_c, int d_c, int s_c, int w_c, int b_c, int p_c);

		void UpdateMap();
	};
}