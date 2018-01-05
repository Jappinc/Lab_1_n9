/* 
9. Матрица состоит из нулей и единиц. Найдите в ней самую длинную цепочку подряд идущих нулей по горизонтали, вертикали или диагонали.
*/

#include "stdafx.h"
#include <time.h>
#include <Windows.h>
#include <iostream>
#include <iomanip>
using namespace std;

int n_menu,max_zero,counter,rows,cols;

int nmb_to_search = 0;
char filename[] = "";

//Поиск самой длинной цепочки по вертикали
int Max_Vertical_Chain(int **matr,int rows,int cols, int nmb_to_search)
{
	max_zero = 0;
	for (int i = 0; i < cols; i++)
	{
		counter = 0;
		for (int j = 0; j < rows; j++)
		{
			if (matr[j][i] == nmb_to_search) counter = ++counter;
			else
			{
				if (counter > max_zero) max_zero = counter;
				counter = 0;
			}
		}
	
		if ((matr[rows-1][i] == nmb_to_search) && (counter > max_zero))
		{
			max_zero = counter;
		}
	}
	return max_zero;
}

//Поиск самой длинной цепочки по горизонтали
int Max_Horizontal_Chain(int **matr, int rows, int cols, int nmb_to_search)
{
	max_zero = 0;
	for (int i = 0; i < rows; i++)
	{
		counter = 0;
		for (int j = 0; j < cols; j++)
		{
			if (matr[i][j] == nmb_to_search) counter = ++counter;
			else
			{
				if (counter > max_zero) max_zero = counter;
				counter = 0;
			}	
		}

		if ((matr[i][cols - 1] == nmb_to_search) && (counter > max_zero))
		{
			max_zero = counter;
		}
	}
	return max_zero;
}

//Поиск самой длинной цепочки диагонали
int Max_Diagonal_Chain(int **matr, int rows, int cols, int nmb_to_search)
{
	int dgl;
	(rows > cols) ? dgl = cols : dgl = rows;
	max_zero = 0;
	counter = 0;
	for (int i = 0; i < dgl; i++)
	{
		if (matr[i][i] == nmb_to_search) counter = ++counter;
		else
		{
			if (counter > max_zero) max_zero = counter;
			counter = 0;
		}
	}

	if ((matr[dgl-1][dgl-1] == nmb_to_search) && (counter > max_zero))
	{
		max_zero = counter;
	}
	return max_zero;
}
//Меню выбора ввода матрицы
int Menu()
{
	cout << "---------------------------------------\n";
	cout << "                 МЕНЮ                  \n";
	cout << "---------------------------------------\n";
	cout << "1 - Загрузить матрицу из файла.\n";
	cout << "2 - Ввести матрицу в консоли.\n";
	cout << "---------------------------------------\n";
	cout << ">>> ";
	int nmb_menu;
	do {
		cin >> nmb_menu;
		if ((nmb_menu != 1) && (nmb_menu != 2))
			cout << "Неверное значение.Повторите ввод.\n";
	} while ((nmb_menu != 1) && (nmb_menu != 2));
	getchar();
	cout << "\n";
	return nmb_menu;
}
//Меню для работы с матрицей
int MenuMatrix()
{
	cout << "----------------------------------------------\n";
	cout << "                     МЕНЮ                     \n";
	cout << "----------------------------------------------\n";
	cout << "1 - Печать матрицы.\n";
	cout << "2 - Поиск самой длинной цепочки по вертикали\n";
	cout << "3 - Поиск самой длинной цепочки по горизонтали\n";
	cout << "4 - Поиск самой длинной цепочки диагонали\n";
	cout << "5 - Запись матрицы в файл\n";
	cout << "6 - Выход\n";
	cout << "----------------------------------------------\n";
	cout << ">>> ";
	int nmb_menu;
	do {
		cin >> nmb_menu;
		if ((nmb_menu <= 1) && (nmb_menu >= 6))
			cout << "Неверное значение.Повторите ввод.\n";
		
	} while ((nmb_menu <= 1) && (nmb_menu >= 6));
	getchar();
	cout << "\n";
	return nmb_menu;
}
//Печать матрицы
void PrintMatrix(int **matr, int rows, int cols)
{
	cout << "Матрица: \n";
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << matr[i][j];
		}
		cout << endl;
	}
}
//Выделение памяти для матрицы
int **MemAlloc(const int rows, const int cols)
{
	int **matr = new int *[rows];

	for (int i = 0; i < rows; i++)
		matr[i] = new int[cols];

	return matr;
}
//Создание матрицы 
int** CreateMatrix(int &rows, int &cols)
{
	cout << "Введите n: \n";
	cin >> rows;
	cout << "Введите m: \n";
	cin >> cols;

	int **matr = MemAlloc(rows, cols);
	return matr;
}
//Чтение матрицы из файла
int** ReadMatrFromFile(char *fname, int *rows, int *cols)
{
	FILE *f = fopen(fname, "r");
	int **matr;
	if (f == NULL)
	{
		matr = NULL;
		cout << "Имя файла пустое" << endl;
	}
	else
	{
		if (fscanf_s(f, "%d %d\n", rows, cols) != 2)
		{
			matr = NULL;
			cout << "Отсутствует размерность массива в файле" << endl;
		}
		else
		{	
			matr = MemAlloc(*rows, *cols);
			for (int i = 0; i < *rows; i++)
			{
				for (int j = 0; j < *cols; j++)
					fscanf(f, "%d ", &matr[i][j]);

			}
			for (int i = 0; i < *cols; i++)
				for (int j = 0; j < *rows; j++)
					fscanf(f, "%d", &matr[i][j]);
		}
	}
	fclose(f);
	return matr;
}
//Вывод матрицы в файл
void WriteMatrInFile(char *fname, int **matr, const int rows, const int cols)
{
	FILE *f = fopen(fname, "w");
	if (f == NULL)
		cout << "Имя файла пустое" << endl;
	else
	{
		int i, rm = 0;
		
		for (i = 0; i < rows; i++)
		{
			if (matr[i] != NULL)
				rm++;
		}
		fprintf(f, "%2d %d\n", rm, cols);
		for (i = 0; i < rows; i++)
		{
			
			if (matr[i] != NULL)
			{
				for (int j = 0; j < cols; j++)
					fprintf(f, "%2d", matr[i][j]);

				fprintf(f, "\n");
			}
		}
	}
	fclose(f);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	    int **matr;
		n_menu = Menu();

		switch (n_menu)
		{
		case 1:
			cout << "Введите имя файла" << endl;
			cin >> filename;
			matr = ReadMatrFromFile(filename, &rows, &cols);
			break;
		case 2: 
		{
			matr = CreateMatrix(rows, cols);

			srand((unsigned int)time(0));
			cout << "Заполнение матрицы (random) \n";
			
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{	
					//cin >> matr[i][j];//ввод вручную
					matr[i][j] = rand() % 2;//rnd
				}
			}

		}
			break;
		default:
			printf_s("Введен неверный номер пункта. Повторите ввод");
		}
	

		for (;;)
		{
			n_menu = MenuMatrix();

			switch (n_menu)
			{
			case 1:
				PrintMatrix(matr, rows, cols);
				break;
			case 2:
				printf_s("Максимальное кол-во '0' по вертикали = %d \n", Max_Vertical_Chain(matr, rows, cols, nmb_to_search));				
				break;
			case 3:
				printf_s("Максимальное кол-во '0' по горизонтали = %d \n", Max_Horizontal_Chain(matr, rows, cols, nmb_to_search));
				break;
			case 4:
				printf_s("Максимальное кол-во '0' по диагонали = %d \n", Max_Diagonal_Chain(matr, rows, cols, nmb_to_search));
				break;
			case 5:
				cout << "Введите имя файла" << endl;
				cin >> filename;

				WriteMatrInFile(filename, matr, rows, cols);
				break;
			case 6:
				for (int i = 0; i < rows; i++)
				{
					delete[] matr[i];
				}

				system("pause");
				return 0;
				break;

			 default: printf_s("Введен неверный номер пункта. Повторите ввод");	 
			}
		}

	system("pause");
    return 0;
}

