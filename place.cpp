#include "place.h"

using namespace std;
using namespace meadow_life;


void Meadow_field::display_field()
{
	for (int i = 0; i < width; i++)
		cout << "----";
	cout << "-" << endl;
	for (int i = 0; i < height; i++)
	{
		cout << "|";
		for (int j = 0; j < width; j++)
			cout << scene[j][i][0] << " " << scene[j][i][1] << "|";
		cout << endl << "|";
		for (int j = 0; j < width; j++)
			cout << "   |";
		cout << endl << "|";
		for (int j = 0; j < width; j++)
			cout << scene[j][i][2] << " " << scene[j][i][3] << "|";
		cout << endl << "-";
		for (int j = 0; j < width; j++)
			cout << "----";
		cout << endl;
	}
}

int* Meadow_master::find_empty_cell(bool isPlant)
{
	int width = meadow_table->get_width();
	int height = meadow_table->get_height();
	int* coords = new int[3];
	int variations = 0;
	int i = rand() % width;
	int j = rand() % height;
	int k = 0;

	while (meadow_table->scene[i][j][k] != ' ' && variations < width * height) // if we are looking for an empty cell and not every cell is full
	{
		for (int c = 0; c < 4; c++)
		{
			if (isPlant)
				if (meadow_table->scene[i][j][c] == 'P') break;
			if (meadow_table->scene[i][j][c] == ' ')
			{
				coords[0] = i; coords[1] = j; coords[2] = c;
				return coords;
			}
		}
		i = rand() % width;
		j = rand() % height;
		variations++;
	}
	if (variations < width * height)
	{
		coords[0] = i; coords[1] = j; coords[2] = k;
		return coords;
	} // if an empty cell is found

	coords[0] = -1; coords[1] = -1; coords[2] = -1;
	return coords; // if an empty field does not exist
}

void Meadow_master::Tick()
{
	system("cls");
	int plant_count = org_plant.size(),
		rabbit_count = org_rabbit.size(),
		deer_count = org_deer.size(),
		squirell_count = org_squirell.size(),
		bear_count = org_bear.size(),
		wolf_count = org_wolf.size();

	// PLANT MOVES
	for (int i = 0; i < plant_count; i++)
		Plant_replicate(&org_plant[i]);
	for (int i = plant_count - 1; i >= 0; i--)
		Plant_age(&org_plant[i], i);


	// DEER MOVES
	for (int i = 0; i < deer_count; i++)
		for (int j = 0; j < org_deer[i].get_moves(); j++)
			Victim_move(&org_deer[i]);
	for (int i = 0; i < deer_count; i++)
		Victim_eat(&org_deer[i]);
	for (int i = 0; i < deer_count; i++)
		Victim_replicate(&org_deer[i]);
	for (int i = deer_count - 1; i >= 0; --i)
		Victim_age(&org_deer[i], i);

	// RABBIT MOVES
	for (int i = 0; i < rabbit_count; i++)
		for (int j = 0; j < org_rabbit[i].get_moves(); j++)
			Victim_move(&org_rabbit[i]);
	for (int i = 0; i < rabbit_count; i++)
		Victim_eat(&org_rabbit[i]);
	for (int i = 0; i < rabbit_count; i++)
		Victim_replicate(&org_rabbit[i]);
	for (int i = rabbit_count - 1; i >= 0; --i)
		Victim_age(&org_rabbit[i], i);

	// SQUIRELL MOVES
	for (int i = 0; i < squirell_count; i++)
		for (int j = 0; j < org_squirell[i].get_moves(); j++)
			Victim_move(&org_squirell[i]);
	for (int i = 0; i < squirell_count; i++)
		Victim_eat(&org_squirell[i]);
	for (int i = 0; i < squirell_count; i++)
		Victim_replicate(&org_squirell[i]);
	for (int i = squirell_count - 1; i >= 0; --i)
		Victim_age(&org_squirell[i], i);

	// WOLF MOVES
	for (int i = 0; i < wolf_count; i++)
		for (int j = 0; j < org_wolf[i].get_moves(); j++)
			Predator_move(&org_wolf[i]);
	for (int i = 0; i < wolf_count; i++)
		Predator_eat(&org_wolf[i]);
	for (int i = 0; i < wolf_count; i++)
		Predator_replicate(&org_wolf[i]);
	for (int i = wolf_count - 1; i >= 0; --i)
		Predator_age(&org_wolf[i], i);

	// BEAR MOVES
	for (int i = 0; i < bear_count; i++)
		for (int j = 0; j < org_bear[i].get_moves(); j++)
			Predator_move(&org_bear[i]);
	for (int i = 0; i < bear_count; i++)
		Predator_eat(&org_bear[i]);
	for (int i = 0; i < bear_count; i++)
		Predator_replicate(&org_bear[i]);
	for (int i = bear_count - 1; i >= 0; --i)
		Predator_age(&org_bear[i], i);

	UpdateMap();
	Show();
}

void Meadow_master::Show()
{
	meadow_table->display_field();
}

void Meadow_master::start_random_place(int r_c, int d_c, int s_c, int w_c, int b_c, int p_c)
{
	// number of mobs
	for (int i = 1; i <= r_c; i++)
	{
		if (i % 2 != 0)
		{
			Rabbit org_rabbit_obj("Male");
			org_rabbit_obj.set_id(rabbit_number);
			org_rabbit.push_back(org_rabbit_obj);
		}
		else
		{
			Rabbit org_rabbit_obj("Female");
			org_rabbit_obj.set_id(rabbit_number);
			org_rabbit.push_back(org_rabbit_obj);
		}
		rabbit_number++;
	}

	for (int i = 1; i <= d_c; i++)
	{
		if (i % 2 != 0)
		{
			Deer org_deer_obj("Male");
			org_deer_obj.set_id(deer_number);
			org_deer.push_back(org_deer_obj);
		}
		else
		{
			Deer org_deer_obj("Female");
			org_deer_obj.set_id(deer_number);
			org_deer.push_back(org_deer_obj);
		}
		deer_number++;
	}

	for (int i = 1; i <= s_c; i++)
	{
		if (i % 2 != 0)
		{
			Squirell org_squirell_obj("Male");
			org_squirell_obj.set_id(squirell_number);
			org_squirell.push_back(org_squirell_obj);
		}
		else
		{
			Squirell org_squirell_obj("Female");
			org_squirell_obj.set_id(squirell_number);
			org_squirell.push_back(org_squirell_obj);
		}
		squirell_number++;
	}

	for (int i = 1; i <= w_c; i++)
	{
		if (i % 2 != 0)
		{
			Wolf org_wolf_obj("Male");
			org_wolf_obj.set_id(wolf_number);
			org_wolf.push_back(org_wolf_obj);
		}
		else
		{
			Wolf org_wolf_obj("Female");
			org_wolf_obj.set_id(wolf_number);
			org_wolf.push_back(org_wolf_obj);
		}
		wolf_number++;
	}

	for (int i = 1; i <= b_c; i++)
	{
		if (i % 2 != 0)
		{
			Bear org_bear_obj("Male");
			org_bear_obj.set_id(bear_number);
			org_bear.push_back(org_bear_obj);
		}
		else
		{
			Bear org_bear_obj("Female");
			org_bear_obj.set_id(bear_number);
			org_bear.push_back(org_bear_obj);
		}
		bear_number++;
	}


	for (int i = 0; i < p_c; i++)
	{
		Plant org_plant_obj;
		org_plant_obj.set_id(plant_number);
		plant_number++;
		org_plant.push_back(org_plant_obj);
	}

	// start place
	for (int i = 0; i < org_rabbit.size(); i++)
	{
		int* cell_coords;
		cell_coords = find_empty_cell(0);

		for (int j = 0; j < 3; j++)
			org_rabbit[i].get_location(j) = cell_coords[j];
		meadow_table->put_org(cell_coords[0], cell_coords[1], cell_coords[2], 'R');
	}

	for (int i = 0; i < org_squirell.size(); i++)
	{
		int* cell_coords;
		cell_coords = find_empty_cell(0);

		for (int j = 0; j < 3; j++)
			org_squirell[i].get_location(j) = cell_coords[j];
		meadow_table->put_org(cell_coords[0], cell_coords[1], cell_coords[2], 'R');
	}

	for (int i = 0; i < org_bear.size(); i++)
	{
		int* cell_coords;
		cell_coords = find_empty_cell(0);

		for (int j = 0; j < 3; j++)
			org_bear[i].get_location(j) = cell_coords[j];
		meadow_table->put_org(cell_coords[0], cell_coords[1], cell_coords[2], 'B');
	}

	for (int i = 0; i < org_wolf.size(); i++)
	{
		int* cell_coords;
		cell_coords = find_empty_cell(0);

		for (int j = 0; j < 3; j++)
			org_wolf[i].get_location(j) = cell_coords[j];
		meadow_table->put_org(cell_coords[0], cell_coords[1], cell_coords[2], 'W');
	}

	for (int i = 0; i < org_deer.size(); i++)
	{
		int* cell_coords;
		cell_coords = find_empty_cell(0);

		for (int j = 0; j < 3; j++)
			org_deer[i].get_location(j) = cell_coords[j];
		meadow_table->put_org(cell_coords[0], cell_coords[1], cell_coords[2], 'D');
	}

	for (int i = 0; i < org_plant.size(); i++)
	{
		int* cell_coords;
		cell_coords = find_empty_cell(1);

		for (int j = 0; j < 3; j++)
			org_plant[i].get_location(j) = cell_coords[j];
		meadow_table->put_org(cell_coords[0], cell_coords[1], cell_coords[2], 'P');
	}

	UpdateMap();
}

void Meadow_master::UpdateMap()
{
	for (int i = 0; i < meadow_table->get_width(); i++)
		for (int j = 0; j < meadow_table->get_height(); j++)
			for (int k = 0; k < 4; k++)
				meadow_table->scene[i][j][k] = ' ';

	for (int i = 0; i < org_plant.size(); i++)
		meadow_table->scene[org_plant[i].get_location(0)][org_plant[i].get_location(1)][org_plant[i].get_location(2)] = 'P';
	for (int i = 0; i < org_rabbit.size(); i++)
		meadow_table->scene[org_rabbit[i].get_location(0)][org_rabbit[i].get_location(1)][org_rabbit[i].get_location(2)] = 'R';
	for (int i = 0; i < org_squirell.size(); i++)
		meadow_table->scene[org_squirell[i].get_location(0)][org_squirell[i].get_location(1)][org_squirell[i].get_location(2)] = 'S';
	for (int i = 0; i < org_wolf.size(); i++)
		meadow_table->scene[org_wolf[i].get_location(0)][org_wolf[i].get_location(1)][org_wolf[i].get_location(2)] = 'W';
	for (int i = 0; i < org_deer.size(); i++)
		meadow_table->scene[org_deer[i].get_location(0)][org_deer[i].get_location(1)][org_deer[i].get_location(2)] = 'D';
	for (int i = 0; i < org_bear.size(); i++)
		meadow_table->scene[org_bear[i].get_location(0)][org_bear[i].get_location(1)][org_bear[i].get_location(2)] = 'B';
}


void Meadow_master::Plant_replicate(Plant* p_obj)
{
	int x = p_obj->get_location(0), y = p_obj->get_location(1);
	int direction = rand() % 4 + 1; //1 - up, 2 - down, 3 - right, 4 - left
	int index_plant, index;
	int current_width = meadow_table->get_width(),
		current_height = meadow_table->get_height(),
		variations = 0;


	while (variations < current_width * current_height)
	{
		if (direction == 1)
		{
			index_plant = empty_place(x, y - 1, 1);
			index = empty_place(x, y - 1, 0);
			if (index_plant != -1) // if there is no plant in this direction
			{
				Plant p_child;
				p_child.set_location(0, x);
				p_child.set_location(1, y - 1);
				p_child.set_location(2, index_plant);
				p_child.set_id(plant_number);
				plant_number++;
				org_plant.push_back(p_child);
				meadow_table->scene[p_child.get_location(0)][p_child.get_location(1)][p_child.get_location(2)] = 'P';
				break;
			}
			if (index_plant == -1 && index != -1) // if there is plant in this direction
			{
				for (int i = 0; i < org_plant.size(); i++)
					if (org_plant[i].get_location(0) == x && org_plant[i].get_location(1) == y - 1)
						org_plant[i].set_hp(org_plant[i].get_hp_max());
				break;
			}
			if (index == -1)
				direction = rand() % 4 + 1;
		}

		if (direction == 2)
		{
			index_plant = empty_place(x, y + 1, 1);
			index = empty_place(x, y + 1, 0);
			if (index_plant != -1) // if there is no plant in this direction
			{
				Plant p_child;
				p_child.set_location(0, x);
				p_child.set_location(1, y + 1);
				p_child.set_location(2, index_plant);
				org_plant.push_back(p_child);
				meadow_table->scene[p_child.get_location(0)][p_child.get_location(1)][p_child.get_location(2)] = 'P';
				break;
			}
			if (index_plant == -1 && index != -1) // if there is plant in this direction
			{
				for (int i = 0; i < org_plant.size(); i++)
					if (org_plant[i].get_location(0) == x && org_plant[i].get_location(1) == y + 1)
						org_plant[i].set_hp(org_plant[i].get_hp_max());
				break;
			}
			if (index == -1)
				direction = rand() % 4 + 1;
		}

		if (direction == 3)
		{
			index_plant = empty_place(x + 1, y, 1);
			index = empty_place(x + 1, y, 0);
			if (index_plant != -1) // if there is no plant in this direction
			{
				Plant p_child;
				p_child.set_location(0, x + 1);
				p_child.set_location(1, y);
				p_child.set_location(2, index_plant);
				org_plant.push_back(p_child);
				meadow_table->scene[p_child.get_location(0)][p_child.get_location(1)][p_child.get_location(2)] = 'P';
				break;
			}
			if (index_plant == -1 && index != -1) // if there is plant in this direction
			{
				for (int i = 0; i < org_plant.size(); i++)
					if (org_plant[i].get_location(0) == x + 1 && org_plant[i].get_location(1) == y)
						org_plant[i].set_hp(org_plant[i].get_hp_max());
				break;
			}
			if (index == -1)
				direction = rand() % 4 + 1;
		}

		if (direction == 4)
		{
			index_plant = empty_place(x - 1, y, 1);
			index = empty_place(x - 1, y, 0);
			if (index_plant != -1) // if there is no plant in this direction
			{
				Plant p_child;
				p_child.set_location(0, x - 1);
				p_child.set_location(1, y);
				p_child.set_location(2, index_plant);
				org_plant.push_back(p_child);
				meadow_table->scene[p_child.get_location(0)][p_child.get_location(1)][p_child.get_location(2)] = 'P';
				break;
			}
			if (index_plant == -1 && index != -1) // if there is plant in this direction but the space is ready
			{
				for (int i = 0; i < org_plant.size(); i++)
					if (org_plant[i].get_location(0) == x - 1 && org_plant[i].get_location(1) == y)
						org_plant[i].set_hp(org_plant[i].get_hp_max());
				break;
			}
			if (index == -1)
				direction = rand() % 4 + 1;
		}
		variations++;
	}
}

void Meadow_master::Plant_age(Plant* p_obj, int order)
{
	p_obj->set_age(p_obj->get_age() + 1);
	p_obj->set_hp(p_obj->get_hp() - 1);
	if (p_obj->get_hp() <= 0)
	{
		meadow_table->scene[p_obj->get_location(0)][p_obj->get_location(1)][p_obj->get_location(2)] = ' ';
		org_plant.erase(org_plant.begin() + order);
	}
}

// VICTIM PHASE

void Meadow_master::Victim_move(Victim* c_obj)
{
	int x = c_obj->get_location(0), y = c_obj->get_location(1), index = 0;
	int direction = rand() % 4 + 1; // 1 - up, 2 - down, 3 - right, 4 - left
	int variations = 0,
		current_width = meadow_table->get_width(),
		current_height = meadow_table->get_height();

	// CHECKING IF PLANT IS RIGHT THERE
	if (c_obj->get_food() <= 0.8 * c_obj->get_food_max())
	{
		Plant plant_obj = return_plant(x, y);
		if (plant_obj.get_location(0) == x && plant_obj.get_location(1) == y)
			return;
	}


	// MOVING PHASE

	while (variations < current_width * current_height)
	{
		if (direction == 1)
		{
			index = empty_place(x, y - 1, 0);
			if (index != -1) // the place is busy
			{
				c_obj->set_location(1, y - 1);
				c_obj->set_location(2, index);
				break;
			}
			else
				direction = rand() % 4 + 1;
		}
		if (direction == 2)
		{
			index = empty_place(x, y + 1, 0);
			if (index != -1)
			{
				c_obj->set_location(1, y + 1);
				c_obj->set_location(2, index);
				break;
			}
			else
				direction = rand() % 4 + 1;
		}
		if (direction == 3)
		{
			index = empty_place(x + 1, y, 0);
			if (index != -1)
			{
				c_obj->set_location(0, x + 1);
				c_obj->set_location(2, index);
				break;
			}
			else
				direction = rand() % 4 + 1;
		}
		if (direction == 4)
		{
			index = empty_place(x - 1, y, 0);
			if (index != -1)
			{
				c_obj->set_location(0, x - 1);
				c_obj->set_location(2, index);
				break;
			}
			else
				direction = rand() % 4 + 1;
		}
		variations++;
	}
	meadow_table->scene[c_obj->get_location(0)][c_obj->get_location(1)][c_obj->get_location(2)] = c_obj->get_type();
}

void Meadow_master::Victim_eat(Victim* c_obj)
{
	int x = c_obj->get_location(0), y = c_obj->get_location(1), index = 0;

	if (c_obj->get_food() <= 0.7 * c_obj->get_food_max())
	{
		Plant plant_obj = return_plant(x, y);
		int x_plant = plant_obj.get_location(0), y_plant = plant_obj.get_location(1);

		if (x_plant == x && y_plant == y)
		{
			c_obj->set_food(c_obj->get_food() + plant_obj.get_hp_max());
			if (c_obj->get_food() > c_obj->get_food_max())
				c_obj->set_food(c_obj->get_food_max());
			meadow_table->scene[x_plant][y_plant][plant_obj.get_location(2)] = ' ';
			for (int i = 0; i < org_plant.size(); i++)
			{
				if (org_plant[i].get_location(0) == x_plant && org_plant[i].get_location(1) == y_plant)
				{
					org_plant.erase(org_plant.begin() + i);
					return;
				}
			}
			// Killing plant, replenishing amount of food corresponding to plant's max hp, 	
		}
	}

}

void Meadow_master::Victim_replicate(Victim* c_obj)
{
	if (c_obj->get_hp() <= 0)
		return;

	int x1 = c_obj->get_location(0), y1 = c_obj->get_location(1), index = 0;
	int replica_result;

	if (c_obj->get_type() == 'D')
	{
		if (c_obj->get_food() >= c_obj->get_food_max() * 0.7)
		{
			for (int i = 0; i < org_deer.size(); i++)
			{
				if (org_deer[i].get_location(0) == x1 && org_deer[i].get_location(1) == y1)
				{
					if (org_deer[i].get_location(2) != c_obj->get_location(2)) // if they are not in the same sub-cell
					{
						if (c_obj->get_isMale() == org_deer[i].get_isMale())
							return;
						replica_result = empty_place(x1, y1, 0);
						if (replica_result == -1)
							return;
						else
						{
							c_obj->set_food(c_obj->get_food() - c_obj->get_food_max() * 0.5);
							Deer c_child("Random");
							c_child.set_id(deer_number);
							deer_number++;
							c_child.set_location(0, x1);
							c_child.set_location(1, y1);
							c_child.set_location(2, replica_result);
							meadow_table->scene[c_child.get_location(0)][c_child.get_location(1)][c_child.get_location(2)] = 'D';
							org_deer.push_back(c_child);
						}
					}
				}
			}
		}
	}

	if (c_obj->get_type() == 'R')
	{
		if (c_obj->get_food() >= c_obj->get_food_max() * 0.9)
		{
			for (int i = 0; i < org_rabbit.size(); i++)
			{
				if (org_rabbit[i].get_location(0) == x1 && org_rabbit[i].get_location(1) == y1)
				{
					if (org_rabbit[i].get_location(2) != c_obj->get_location(2)) // if they are not in the same sub-cell
					{
						if (c_obj->get_isMale() == org_rabbit[i].get_isMale())
							return;
						replica_result = empty_place(x1, y1, 0);
						if (replica_result == -1)
							return;
						else
						{
							c_obj->set_food(c_obj->get_food() - c_obj->get_food_max() * 0.6);
							Rabbit c_child("Random");
							c_child.set_id(rabbit_number);
							rabbit_number++;
							c_child.set_location(0, x1);
							c_child.set_location(1, y1);
							c_child.set_location(2, replica_result);
							meadow_table->scene[c_child.get_location(0)][c_child.get_location(1)][c_child.get_location(2)] = 'R';
							org_rabbit.push_back(c_child);
						}
					}
				}
			}
		}
	}

	if (c_obj->get_type() == 'S')
	{
		if (c_obj->get_food() >= c_obj->get_food_max() * 0.8)
		{
			for (int i = 0; i < org_squirell.size(); i++)
			{
				if (org_squirell[i].get_location(0) == x1 && org_squirell[i].get_location(1) == y1)
				{
					if (org_squirell[i].get_location(2) != c_obj->get_location(2)) // if they are not in the same sub-cell
					{
						if (c_obj->get_isMale() == org_squirell[i].get_isMale())
							return;
						replica_result = empty_place(x1, y1, 0);
						if (replica_result == -1)
							return;
						else
						{
							c_obj->set_food(c_obj->get_food() - c_obj->get_food_max() * 0.6);
							Squirell c_child("Random");
							c_child.set_id(squirell_number);
							squirell_number++;
							c_child.set_location(0, x1);
							c_child.set_location(1, y1);
							c_child.set_location(2, replica_result);
							meadow_table->scene[c_child.get_location(0)][c_child.get_location(1)][c_child.get_location(2)] = 'S';
							org_squirell.push_back(c_child);
						}
					}
				}
			}
		}
	}
}

void Meadow_master::Victim_age(Victim* c_obj, int order)
{
	c_obj->set_age(c_obj->get_age() + 1);
	c_obj->set_hp(c_obj->get_hp() - 1);
	c_obj->set_food(c_obj->get_food() - 1);

	if (c_obj->get_food() <= 0)
		c_obj->set_hp(c_obj->get_hp() - 3);
	if (c_obj->get_hp() <= 0)
	{
		meadow_table->scene[c_obj->get_location(0)][c_obj->get_location(1)][c_obj->get_location(2)] = ' ';
		
		if (c_obj->get_type() == 'R')
			org_rabbit.erase(org_rabbit.begin() + order);
		if (c_obj->get_type() == 'S')
			org_squirell.erase(org_squirell.begin() + order);

	}
}


// PREDATOR PHASE

void Meadow_master::Predator_move(Predator* c_obj)
{
	int x = c_obj->get_location(0), y = c_obj->get_location(1), index = 0;
	int direction = rand() % 4 + 1; // 1 - up, 2 - down, 3 - right, 4 - left
	int variations = 0,
		current_width = meadow_table->get_width(),
		current_height = meadow_table->get_height();

	if (c_obj->get_food() <= 0.7 * c_obj->get_food_max())
	{
		Deer deer_obj = return_deer(x, y);
		Rabbit rabbit_obj = return_rabbit(x, y);
		Squirell squirell_obj = return_squirell(x, y);
		if (deer_obj.get_location(0) == x && deer_obj.get_location(1) == y)
			return;
		if (rabbit_obj.get_location(0) == x && rabbit_obj.get_location(1) == y)
			return;
		if (squirell_obj.get_location(0) == x && squirell_obj.get_location(1) == y)
			return;
	}

	// MOVING PHASE

	while (variations < current_width * current_height)
	{
		if (direction == 1)
		{
			index = empty_place(x, y - 1, 0);
			if (index != -1) // the place is busy
			{
				c_obj->set_location(1, y - 1);
				c_obj->set_location(2, index);
				break;
			}
			else
				direction = rand() % 4 + 1;
		}
		if (direction == 2)
		{
			index = empty_place(x, y + 1, 0);
			if (index != -1)
			{
				c_obj->set_location(1, y + 1);
				c_obj->set_location(2, index);
				break;
			}
			else
				direction = rand() % 4 + 1;
		}
		if (direction == 3)
		{
			index = empty_place(x + 1, y, 0);
			if (index != -1)
			{
				c_obj->set_location(0, x + 1);
				c_obj->set_location(2, index);
				break;
			}
			else
				direction = rand() % 4 + 1;
		}
		if (direction == 4)
		{
			index = empty_place(x - 1, y, 0);
			if (index != -1)
			{
				c_obj->set_location(0, x - 1);
				c_obj->set_location(2, index);
				break;
			}
			else
				direction = rand() % 4 + 1;
		}
		variations++;
	}
	meadow_table->scene[c_obj->get_location(0)][c_obj->get_location(1)][c_obj->get_location(2)] = c_obj->get_type();
}

void Meadow_master::Predator_eat(Predator* c_obj)
{
	int x = c_obj->get_location(0), y = c_obj->get_location(1), index = 0;

	if (c_obj->get_food() <= 0.7 * c_obj->get_food_max())
	{
		Deer deer_obj = return_deer(x, y);
		Rabbit rabbit_obj = return_rabbit(x, y);
		Squirell squirell_obj = return_squirell(x, y);
		int x_deer = deer_obj.get_location(0), y_deer = deer_obj.get_location(1);
		int x_rabbit = rabbit_obj.get_location(0), y_rabbit = rabbit_obj.get_location(1);
		int x_squirell = squirell_obj.get_location(0), y_squirell = squirell_obj.get_location(1);

		if (x_deer == x && y_deer == y)
		{
			if (c_obj->get_damage() >= deer_obj.get_hp())	// KILLING DEER
			{
				if (c_obj->get_food() + c_obj->get_damage() > c_obj->get_food_max())
					c_obj->set_food(c_obj->get_food() + c_obj->get_food_max() - c_obj->get_food());
				else
					c_obj->set_food(c_obj->get_food() + c_obj->get_damage());
				meadow_table->scene[x_deer][y_deer][deer_obj.get_location(2)] = ' ';
				for (int i = 0; i < org_deer.size(); i++)
				{
					if (org_deer[i].get_location(0) == x_deer && org_deer[i].get_location(1) == y_deer)
					{
						org_deer.erase(org_deer.begin() + i);
						return;
					}
				}
			}
			else                                   // DAMAGE DEER
			{
				if (c_obj->get_food() + c_obj->get_damage() > c_obj->get_food_max())
					c_obj->set_food(c_obj->get_food() + c_obj->get_food_max() - c_obj->get_food());
				else
					c_obj->set_food(c_obj->get_food() + c_obj->get_damage());
				for (int i = 0; i < org_deer.size(); i++)
				{
					if (org_deer[i].get_location(0) == x_deer && org_deer[i].get_location(1) == y_deer)
					{
						org_deer[i].set_hp(org_deer[i].get_hp() - c_obj->get_damage());
						return;
					}
				}
			}
		}
		if (x_rabbit == x && y_rabbit == y)
		{
			if (c_obj->get_damage() >= rabbit_obj.get_hp())	// KILLING RABBIT
			{
				if (c_obj->get_food() + c_obj->get_damage() > c_obj->get_food_max())
					c_obj->set_food(c_obj->get_food() + c_obj->get_food_max() - c_obj->get_food());
				else
					c_obj->set_food(c_obj->get_food() + c_obj->get_damage());
				meadow_table->scene[x_rabbit][y_rabbit][rabbit_obj.get_location(2)] = ' ';
				for (int i = 0; i < org_rabbit.size(); i++)
				{
					if (org_rabbit[i].get_location(0) == x_rabbit && org_rabbit[i].get_location(1) == y_rabbit)
					{
						org_rabbit.erase(org_rabbit.begin() + i);
						return;
					}
				}
			}
			else                                   // DAMAGE RABBIT
			{
				if (c_obj->get_food() + c_obj->get_damage() > c_obj->get_food_max())
					c_obj->set_food(c_obj->get_food() + c_obj->get_food_max() - c_obj->get_food());
				else
					c_obj->set_food(c_obj->get_food() + c_obj->get_damage());
				for (int i = 0; i < org_rabbit.size(); i++)
				{
					if (org_rabbit[i].get_location(0) == x_rabbit && org_rabbit[i].get_location(1) == y_rabbit)
					{
						org_rabbit[i].set_hp(org_rabbit[i].get_hp() - c_obj->get_damage());
						return;
					}
				}
			}
		}
		if (x_squirell == x && y_squirell == y)
		{
			if (c_obj->get_damage() >= squirell_obj.get_hp())	// KILLING squirell
			{
				if (c_obj->get_food() + c_obj->get_damage() > c_obj->get_food_max())
					c_obj->set_food(c_obj->get_food() + c_obj->get_food_max() - c_obj->get_food());
				else
					c_obj->set_food(c_obj->get_food() + c_obj->get_damage());
				meadow_table->scene[x_squirell][y_squirell][squirell_obj.get_location(2)] = ' ';
				for (int i = 0; i < org_squirell.size(); i++)
				{
					if (org_squirell[i].get_location(0) == x_squirell && org_squirell[i].get_location(1) == y_squirell)
					{
						org_squirell.erase(org_squirell.begin() + i);
						return;
					}
				}
			}
			else                                   // DAMAGE squirell
			{
				if (c_obj->get_food() + c_obj->get_damage() > c_obj->get_food_max())
					c_obj->set_food(c_obj->get_food() + c_obj->get_food_max() - c_obj->get_food());
				else
					c_obj->set_food(c_obj->get_food() + c_obj->get_damage());
				for (int i = 0; i < org_squirell.size(); i++)
				{
					if (org_squirell[i].get_location(0) == x_squirell && org_squirell[i].get_location(1) == y_squirell)
					{
						org_squirell[i].set_hp(org_squirell[i].get_hp() - c_obj->get_damage());
						return;
					}
				}
			}
		}
	}
}

void Meadow_master::Predator_replicate(Predator* c_obj)
{
	if (c_obj->get_hp() <= 0)
		return;

	int x1 = c_obj->get_location(0), y1 = c_obj->get_location(1), index = 0;
	int replica_result;

	if (c_obj->get_type() == 'B')
	{
		if (c_obj->get_food() >= c_obj->get_food_max() * 0.8)
		{
			for (int i = 0; i < org_bear.size(); i++)
			{
				if (org_bear[i].get_location(0) == x1 && org_bear[i].get_location(1) == y1)
				{
					if (org_bear[i].get_location(2) != c_obj->get_location(2)) // if they are not in the same sub-cell
					{
						if (c_obj->get_isMale() == org_bear[i].get_isMale())
							return;
						replica_result = empty_place(x1, y1, 0);
						if (replica_result == -1)
							return;
						else
						{
							c_obj->set_food(c_obj->get_food() - c_obj->get_food_max() * 0.5);
							Bear c_child("Random");
							c_child.set_id(bear_number);
							bear_number++;
							c_child.set_location(0, x1);
							c_child.set_location(1, y1);
							c_child.set_location(2, replica_result);
							meadow_table->scene[c_child.get_location(0)][c_child.get_location(1)][c_child.get_location(2)] = 'B';
							org_bear.push_back(c_child);
						}
					}
				}
			}
		}
	}

	if (c_obj->get_type() == 'W')
	{
		if (c_obj->get_food() >= c_obj->get_food_max() * 0.8)
		{
			for (int i = 0; i < org_wolf.size(); i++)
			{
				if (org_wolf[i].get_location(0) == x1 && org_wolf[i].get_location(1) == y1)
				{
					if (org_wolf[i].get_location(2) != c_obj->get_location(2)) // if they are not in the same sub-cell
					{
						if (c_obj->get_isMale() == org_wolf[i].get_isMale())
							return;
						replica_result = empty_place(x1, y1, 0);
						if (replica_result == -1)
							return;
						else
						{
							c_obj->set_food(c_obj->get_food() - c_obj->get_food_max() * 0.6);
							Wolf c_child("Random");
							c_child.set_id(wolf_number);
							wolf_number++;
							c_child.set_location(0, x1);
							c_child.set_location(1, y1);
							c_child.set_location(2, replica_result);
							meadow_table->scene[c_child.get_location(0)][c_child.get_location(1)][c_child.get_location(2)] = 'W';
							org_wolf.push_back(c_child);
						}
					}
				}
			}
		}
	}
}

void Meadow_master::Predator_age(Predator* c_obj, int order)
{
	c_obj->set_age(c_obj->get_age() + 1);
	c_obj->set_hp(c_obj->get_hp() - 1);
	c_obj->set_food(c_obj->get_food() - 1);

	if (c_obj->get_food() <= 0)
		c_obj->set_hp(c_obj->get_hp() - 3);
	if (c_obj->get_hp() <= 0)
	{
		meadow_table->scene[c_obj->get_location(0)][c_obj->get_location(1)][c_obj->get_location(2)] = ' ';
		if (c_obj->get_type() == 'B')
			org_bear.erase(org_bear.begin() + order);
		if (c_obj->get_type() == 'W')
			org_wolf.erase(org_wolf.begin() + order);
	}
}



Plant& Meadow_master::return_plant(int x1, int y1)
{
	for (int i = 0; i < org_plant.size(); i++)
		if (org_plant[i].get_location(0) == x1 && org_plant[i].get_location(1) == y1)
			return org_plant[i];
	p_extra->set_location(0, -1);
	p_extra->set_location(1, -1);
	p_extra->set_location(2, -1);
	return *p_extra;
}

Deer& Meadow_master::return_deer(int x1, int y1)
{
	for (int i = 0; i < org_deer.size(); i++)
		if (org_deer[i].get_location(0) == x1 && org_deer[i].get_location(1) == y1)
			return org_deer[i];
	d_extra->set_location(0, -1);
	d_extra->set_location(1, -1);
	d_extra->set_location(2, -1);
	return *d_extra;
}

Squirell& Meadow_master::return_squirell(int x1, int y1)
{
	for (int i = 0; i < org_squirell.size(); i++)
		if (org_squirell[i].get_location(0) == x1 && org_squirell[i].get_location(1) == y1)
			return org_squirell[i];
	s_extra->set_location(0, -1);
	s_extra->set_location(1, -1);
	s_extra->set_location(2, -1);
	return *s_extra;
}

Rabbit& Meadow_master::return_rabbit(int x1, int y1)
{
	for (int i = 0; i < org_rabbit.size(); i++)
		if (org_rabbit[i].get_location(0) == x1 && org_rabbit[i].get_location(1) == y1)
			return org_rabbit[i];
	r_extra->set_location(0, -1);
	r_extra->set_location(1, -1);
	r_extra->set_location(2, -1);
	return *r_extra;
}

int Meadow_master::empty_place(int x1, int y1, bool isPlant)
{
	if (x1 < 0 || y1 < 0 || x1 >= meadow_table->get_width() || y1 >= meadow_table->get_height())
		return -1;
	if (isPlant)			// only 1 plant per 1 cell
		for (int i = 0; i < org_plant.size(); i++)
			if (org_plant[i].get_location(0) == x1 && org_plant[i].get_location(1) == y1)
				return -1;
	for (int i = 0; i < 4; i++)
		if (meadow_table->scene[x1][y1][i] == ' ')
			return i;
	return -1;
}