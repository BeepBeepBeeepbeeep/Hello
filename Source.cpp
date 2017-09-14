#include <iostream>
#include <ctime>
#include <conio.h>

using namespace std;

class Figure
{
public:
	void virtual showFigure()
	{
		system("cls");
		for (int i = 0;i <= height + 1;i++)
			for (int j = 0;j <= width + 1; j++)
			{
				cout << ((height + 1 == i || width + 1 == j || i == 0 || j == 0) ? '#' : screen[i][j]) << ((j <= width) ? " " : "\n");
			}
	}

	void foodSpawn()
	{
		srand(time(NULL));
		int x = 0;
		int y = 0;
		x = rand() % (width - 2 + 1) + 2;
		y = rand() % (height - 2 + 1) + 2;
		if ((this->screen[y][x] != '*') && (this->screen[y][x] != '^') && (this->screen[y][x] != '>') && (this->screen[y][x] != '<') && (this->screen[y][x] != 'v'))
		{
			this->food_x = x;
			this->food_y = y;
			this->screen[y][x] = '+';
		}
		else
		{
			this->foodSpawn();
		}
	}

	bool checkFood()
	{
		if ((food_x == -1) && (food_y == -1))
			return true;
		return false;
	}

public:
	int x[2500], y[2500];
	char screen[2500][2500];
	int food_x = -1, food_y = -1;
protected:
	const int height = 20, width = 30;
};

class Snake :public Figure
{
public:
	Snake()
	{
		this->figure = new Figure();
		this->snakeSize = 2;
		this->figure->x[1] = 3;
		this->figure->y[1] = 4;
		this->figure->x[2] = 3;
		this->figure->y[2] = 3;
		change_x = 1;
		change_y = 0;
	}

	void showFigure()
	{
		if ((change_x == 0) && (change_y == 1)) this->figure->screen[figure->y[1]][figure->x[1]] = 'v';
		if ((change_x == -1) && (change_y == 0)) this->figure->screen[figure->y[1]][figure->x[1]] = '<';
		if ((change_x == 1) && (change_y == 0)) this->figure->screen[figure->y[1]][figure->x[1]] = '>';
		if ((change_x == 0) && (change_y == -1)) this->figure->screen[figure->y[1]][figure->x[1]] = '^';

		for (int i = this->snakeSize;i > 1;i--)
			this->figure->screen[this->figure->y[i]][this->figure->x[i]] = '*';
	}

	void Move()
	{
		this->clearSpace();
		for (int i = this->snakeSize;i >= 2;i--) { figure->x[i] = figure->x[i - 1]; figure->y[i] = figure->y[i - 1]; }
		figure->x[1] += this->change_x;
		figure->y[1] += this->change_y;
		this->Eat();
		this->showFigure();
		this->Eat();
	}

	void changeDirection()
	{
		switch (_getch())
		{
		case 'w': {this->change_x = 0;this->change_y = -1;break;}
		case 'a': {this->change_x = -1;this->change_y = 0;break;
		}
		case 'd': {this->change_x = 1;this->change_y = 0;break;}
		case 's':{this->change_x = 0;this->change_y = 1;break;
		}
		default:
			break;
		}
	}

	void clearSpace()
	{
		for (int i = this->snakeSize;i >= 2;i--)
			this->figure->screen[this->figure->y[i]][this->figure->x[i]] = ' ';
	}

	void Eat()
	{
		for (int i = 2;i <= this->snakeSize;i++)
		{
			if (((this->figure->x[1] == this->figure->x[i]) && (this->figure->y[1] == this->figure->y[i])) || (this->figure->x[1] == width + 1) || (this->figure->y[1] == height + 1) || (this->figure->x[1] == 0) || (this->figure->y[1] == 0))
			{
				system("cls");

				cout << "GAME OVER";
				system("pause");
				exit(0);
			}

		}

		if ((this->figure->food_x == this->figure->x[1]) && (this->figure->food_y == this->figure->y[1]))
		{
			this->snakeSize++;
			this->figure->food_x = -1;
			this->figure->food_y = -1;
		}
	}

public:
	Figure * figure;
private:
	int snakeSize;
	int change_x, change_y;
};

int main()
{
	Snake * snake = new Snake();

	while (true)
	{

		kbhit();
		snake->changeDirection();
		if (snake->figure->checkFood()) { snake->figure->foodSpawn(); }

		snake->Move();
		snake->figure->showFigure();
	}

	system("pause");
	return 0;
}