Задача
------------------------
Матрица состоит из нулей и единиц. Найдите в ней самую длинную цепочку подряд идущих нулей по горизонтали, вертикали или диагонали.
======

Поиск самой длинной цепочки по вертикали
```
int Max_Vertical_Chain(int **matr,int rows,int cols, int nmb_to_search)
```

Поиск самой длинной цепочки по горизонтали
```
int Max_Horizontal_Chain(int **matr, int rows, int cols, int nmb_to_search)
```

Поиск самой длинной цепочки диагонали
```
int Max_Diagonal_Chain(int **matr, int rows, int cols, int nmb_to_search)
```

Печать матрицы
```
void PrintMatrix(int **matr, int rows, int cols)
```

Выделение памяти для матрицы
```
int** MemAlloc(const int rows, const int cols)
```

Создание матрицы 
```
int** CreateMatrix(int &rows, int &cols)
```

Чтение матрицы из файла
```
int** ReadMatrFromFile(char *fname, int *rows, int *cols)
```

Вывод матрицы в файл
```
void WriteMatrInFile(char *fname, int **matr, const int rows, const int cols)
```
