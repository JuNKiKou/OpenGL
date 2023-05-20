#include "Stack.h"

static int counts = 1;

ArrayStack<int>* tracks;
int n_cars;
int n_tracks;
int s_car;
int s_track;

void PrintMatchedPairs(std::string expr)
{
	ArrayStack<int> stack;
	int length = (int)expr.size();

	for (int i = 0; i < length; i++)
	{
		if (expr.at(i) == '(')
		{
			stack.push(i);
		}
		else if (expr.at(i) == ')')
		{
			try
			{
				std::cout << stack.top() << ' ' << i << std::endl;
				stack.pop();
			}
			catch (StackEmpty e)
			{
				std::cout << "No Match for right parenthesis at "
					<< i << std::endl;
				e.outputMessage();
			}
		}
	}

	while (!stack.empty())
	{
		std::cout << "No match for left parenthesis at "
			<< stack.top() << std::endl;
		stack.pop();
	}

}

void TowersOfHanoi_Recursion(int n_disk, 
	int n_tower_1, int n_tower_2, int n_tower_3)
{
	if (n_disk == 1)
	{
		std::cout << "Step " << counts << " : ";

		std::cout << "Move top disk from tower " << n_tower_1
			<< " to top of tower " << n_tower_2 << std::endl;

		++counts;
	}
	else
	{
		TowersOfHanoi_Recursion(n_disk - 1,
			n_tower_1, n_tower_3, n_tower_2);

		TowersOfHanoi_Recursion(1,
			n_tower_1, n_tower_2, n_tower_3);

		TowersOfHanoi_Recursion(n_disk - 1,
			n_tower_3, n_tower_2, n_tower_1);
	}

	
}

void PrintHanoi(int n_disk)
{
	TowersOfHanoi_Recursion(n_disk, 1, 2, 3);
}


void OutputFromHoldingTrack()
{
	tracks[s_track].pop();
	std::cout << "Move car " << s_car << " from holding "
		<< "track " << s_track << " to output track" 
		<< std::endl;

	s_car = n_cars + 2;
	for (int i = 1; i <= n_tracks; i++)
	{
		if (!tracks[i].empty() && (tracks[i].top() < s_car))
		{
			s_car = tracks[i].top();
			s_track = i;
		}
	}
}

bool PutIntoHoldingTrack(int car)
{
	int best_track = 0;
	int best_top = n_cars + 1;


	for (int i = 1; i <= n_tracks; i++)
	{
		if (!tracks[i].empty())
		{
			int top_car = tracks[i].top();
			if (car < top_car && top_car < best_top)
			{
				best_top = top_car;
				best_track = i;
			}
		}
		else
		{
			if (best_track == 0)
				best_track = i;
		}
	}

	if (best_track == 0)
	{
		return false;
	}

	tracks[best_track].push(car);
	std::cout << "Move car " << car << " from input track "
		<< "to holding track " << best_track << std::endl;

	if (car < s_car)
	{
		s_car = car;
		s_track = best_track;
	}

	return true;
}

bool Railroad(int input[], int num_cars, int num_tracks)
{
	n_cars = num_cars;
	n_tracks = num_tracks;

	tracks = new ArrayStack<int>[n_tracks + 1];

	int nextOut = 1;
	s_car = n_cars + 1;


	for (int i = 1; i <= n_cars; i++)
	{
		if (input[i] == nextOut)
		{
			std::cout << "Move car " << input[i]
				<< " from input track to output track" 
				<< std::endl;

			++nextOut;

			while (s_car == nextOut)
			{
				OutputFromHoldingTrack();
				++nextOut;
			}

		}
		else
		{
			if (!PutIntoHoldingTrack(input[i]))
			{
				return false;
			}
		}
	}

	return true;
}

bool CheckBox(int net[], int n)
{
	ArrayStack<int>* stack = new ArrayStack<int>(n);

	for (int i = 0; i < n; i++)
	{
		if (!stack->empty())
		{
			if (net[i] == net[stack->top()])
			{
				stack->pop();
			}
			else
			{
				stack->push(i);
			}
		}
		else
		{
			stack->push(i);
		}
	}

	if (stack->empty())
	{
		std::cout << "Switch box is routable" << std::endl;
		delete[] stack;
		return true;
	}
	else
	{
		std::cout << "Switch box is not routable" << std::endl;
		delete[] stack;
		return false;
	}

}

void OfflineEquivalenceClass()
{
	int n_element;
	int n_relation;

	std::cout << "Enter number of elements" << std::endl;
	std::cin >> n_element;

	if (n_element < 2)
	{
		std::cout << "Too few elements" << std::endl;
		return;
	}

	std::cout << "Enter number of relations" << std::endl;
	std::cin >> n_relation;

	if (n_relation < 1)
	{
		std::cout << "Too few relations" << std::endl;
		return;
	}

	ArrayStack<int>* list = new ArrayStack<int>[n_element + 1];

	int a, b;
	for (int i = 1; i <= n_relation; i++)
	{
		std::cout << "Enter next relation/pair" << std::endl;
		std::cin >> a >> b;
		list[a].push(b);
		list[b].push(a);
	}

	ArrayStack<int> unprocessedList;
	bool* out = new bool[n_element + 1];
	for (int i = 1; i <= n_element; i++)
	{
		out[i] = false;
	}

	for (int i = 1; i <= n_element; i++)
	{
		if (!out[i])
		{
			std::cout << "Next class is : " << i << " ";
			out[i] = true;
			unprocessedList.push(i);

			while (!unprocessedList.empty())
			{
				int j = unprocessedList.top();
				unprocessedList.pop();

				while (!list[j].empty())
				{
					int q = list[j].top();
					list[j].pop();
					if (!out[q])
					{
						std::cout << q << " ";
						out[q] = true;
						unprocessedList.push(q);
					}
				}
			}

			std::cout << std::endl;
		}

	}
	
	std::cout << "End of list of equivalence classes" << std::endl;
}

bool findPath(int** matrix, int n_size)
{

	ArrayStack<Position> path = ArrayStack<Position>(n_size * n_size - 1);

	Position offset[4];
	offset[0].row = 0; offset[0].col = 1;   // right
	offset[1].row = 1; offset[1].col = 0;   // down
	offset[2].row = 0; offset[2].col = -1;  // left
	offset[3].row = -1; offset[3].col = 0;  // up

	int** maze = new int*[n_size + 2];

	for (int i = 0; i < n_size + 2; i++)
	{
		maze[i] = new int[n_size + 2];
	}

	for (int i = 0; i < n_size + 2; i++)
	{
		for (int j = 0; j < n_size + 2; j++)
		{
			if (i == 0 || i == n_size + 1 
				|| j == 0 || j == n_size + 1)
			{
				maze[i][j] = 1;
			}
			else
			{
				maze[i][j] = matrix[i - 1][j - 1];
			}
		}
	}

	Position here = { 1, 1 };
	maze[1][1] = 1;
	MazeOption _option = MazeOption::TO_RIGHT;
	MazeOption _lastOption = MazeOption::TO_UP;

	while (here.row != n_size || here.col != n_size)
	{
		Position next;

		while (_option <= _lastOption)
		{
			next = 
			{
				here.row + offset[_option].row,
				here.col + offset[_option].col
			};

			if (maze[next.row][next.col] == 0) break;
			++_option;
		}

		if (_option <= _lastOption)
		{
			// find a path
			path.push(here);
			here = next;
			maze[next.row][next.col] = 1;
			_option = MazeOption::TO_RIGHT;
		}
		else
		{
			// no path find
			if (path.empty())
			{
				return false;
			}

			Position next = path.top();
			path.pop();

			if (next.row == here.row)
			{
				if (next.col > here.col)
				{
					_option = MazeOption::TO_UP;
				}
				else
				{
					_option = MazeOption::TO_DOWN;
				}
			}
			else
			{
				if (next.row > here.row)
				{
					_option = MazeOption::NO_PATH;
				}
				else
				{
					_option = MazeOption::TO_LEFT;
				}
			}

			here = next;
		}
	}

	return true;
}
