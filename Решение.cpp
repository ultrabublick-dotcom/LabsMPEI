/* 
В данной работе необходимо разработать класс для представления некоторого объекта.

В первую очередь необходимо разработать интерфейс класса, затем набор переменных для представления данных о заданном объекте.

Для множества обязательно проверять, чтобы каждый элемент входил в множество только один раз!

Кроме указанных в задании функций вы можете определить любые другие функции, которые вы сочтёте нужными.

Необходимо также написать программу, демонстрирующую возможности разработанного класса.

Эта программа и программы всех последующих лабораторных работ должны состоять из заголовочного файла с определением класса, файла с исходным кодом с функциями-членами класса и файла с исходным кодом, содержащим функцию main.


Разработать класс для представления объекта матрица, состоящая из элементов типа double.

Определить конструктор с двумя параметрами целого типа (размеры матрицы), который можно использовать как конструктор умолчания.

Определить конструктор, который создаёт новую матрицу таким образом, что все её элементы больше элементов другой матрицы на заданное число, и который можно использовать как конструктор копирования.

Определить конструктор перемещения.

Определить деструктор.

Определить преобразования из переменной типа double в матрицу (создание матрицы из 1 строки и 1 столбца) и из матрицы в переменную типа double (вычисление среднего арифметического элементов матрицы). */

#include <iostream>
#include <Windows.h>

class Matrix
{
public:
	int Number_of_rows, Number_of_columns;
	double** Mas_of_Mas;
	Matrix(int n = 0, int m = 0) : Number_of_rows(n), Number_of_columns(m)
	{
		if (n == 0 || m == 0)
		{
			Mas_of_Mas = nullptr;
			std::cout << "Создана матрица конструктором умолчания" << std::endl;
		}
		else
		{
			Mas_of_Mas = new double* [n];
			for (int i = 0; i < n; i++)
				Mas_of_Mas[i] = new double[m];
			for (int i = 0; i < Number_of_rows; i++)
				for (int j = 0; j < Number_of_columns; j++)
					Mas_of_Mas[i][j] = 0;
			std::cout << "Создана матрица конструктором с двумя параметрами" << std::endl;
		}
	}

	Matrix(const Matrix& Copy,  double difference = 0)
	{
		Number_of_rows = Copy.Number_of_rows;
		Number_of_columns = Copy.Number_of_columns;

		Mas_of_Mas = new double* [Number_of_rows];
		for (int i = 0; i < Number_of_rows; i++)
			Mas_of_Mas[i] = new double[Number_of_columns];

		for (int i = 0; i < Number_of_rows; i++)
			for (int j = 0; j < Number_of_columns; j++)
				Mas_of_Mas[i][j] = Copy.Mas_of_Mas[i][j] + difference;

		if (difference == 0)
			std::cout << "Создана матрица конструктором копирования" << std::endl;
		else
			std::cout << "Создана матрица конструктором копирования с увеличением элементов на " << difference << std::endl;
	}

	Matrix(Matrix&& Move)
	{
		Number_of_rows = Move .Number_of_rows;
		Number_of_columns = Move.Number_of_columns;
		Mas_of_Mas = Move.Mas_of_Mas;

		Move.Number_of_rows = 0;
		Move.Number_of_columns = 0;
		Move.Mas_of_Mas = nullptr;

		std::cout << "Создана матрица конструктором перемещения" << std::endl;
	}

	~Matrix()
	{
		for (int i = 0; i < Number_of_rows; i++)
			delete Mas_of_Mas[i];

		delete Mas_of_Mas;

		std::cout << "Удалена матрица деструктором" << std::endl;
	}

	Matrix(double Number) : Number_of_rows(1), Number_of_columns(1)
	{
		Mas_of_Mas = new double* [1];
		Mas_of_Mas[0] = new double [1];

		Mas_of_Mas[0][0] = Number;

		std::cout << "Создана матрица из 1 строки и 1 столбца с элеметом " << Number << std::endl;
	}

	double MeanOfMatrix()
	{
		double count = 0, sum = 0;

		for (int i = 0; i < Number_of_rows; i++)
			for (int j = 0; j < Number_of_columns; j++)
			{
				count++;
				sum += Mas_of_Mas[i][j];
			}

		if (count == 0)
			return 0;

//		std::cout << "Вычеслено среднее значение матрицы"<< std::endl;

		return (sum / count);
	}

	void MatrixOut()
	{
		for (int i = 0; i < Number_of_rows; i++)
		{
			for (int j = 0; j < Number_of_columns; j++)
				std::cout << Mas_of_Mas[i][j] << ' ';
			std::cout << std::endl;
		}
		if (Number_of_rows == 0 || Number_of_columns == 0)
			std::cout << "Матрица пуста" << std::endl;
		std::cout << "Выведена матрица" << std::endl;
	}
};

Matrix TRY()
{
	return Matrix();
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	Matrix A;
	std::cout << std::endl;
	std::cout << "Создана матрица A" << std::endl;
	A.MatrixOut();
	std::cout << std::endl;
	std::cout << std::endl;

	Matrix B(3, 4);
	std::cout << std::endl;
	std::cout << "Создана матрица B размером 3 на 4" << std::endl;
	B.MatrixOut();
	std::cout << std::endl;
	std::cout << std::endl;

	Matrix C1(B, 5);
	std::cout << std::endl;
	std::cout << "Создана матрица С1, как копия B с всеми элементами увеличенными на 5" << std::endl;
	C1.MatrixOut();
	std::cout << std::endl;
	std::cout << std::endl;

	Matrix C2(C1);
	std::cout << std::endl;
	std::cout << "Создана матрица С2, как копия С1" << std::endl;
	C2.MatrixOut();
	std::cout << std::endl;
	std::cout << std::endl;

	Matrix D(1.9);
	std::cout << std::endl;
	std::cout << "Создана матрица D, как 1 строка и 1 столбец" << std::endl;
	D.MatrixOut();
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Среднее значение матрицы С1 = " << C1.MeanOfMatrix() << std::endl;
	std::cout << std::endl;

	Matrix C3 = TRY();
	std::cout << "Матрицы в которую перемистили" << std::endl;
	C3.MatrixOut();
}

