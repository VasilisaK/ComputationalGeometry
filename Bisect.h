#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>


// класс биссектрисы
class Bisectrix {
private:
	double A_bis; // коэффициенты биссектрисы
	double B_bis; 
	double C_bis;
	double cross_point_X; // точка пересечения двух других биссектрис, образующих угол, биссектрисой которого является текущая биссектриса
	double cross_point_Y;
	int nL;
	int n;
	int nR;

public:
	Bisectrix();
	void read_cross_point(double x, double y, int n1, int n2, int n3); // чтение координат вышеназванной точки пересечения 
	void calc_bis_coeffs(double x1, double y1, double x2, double y2); // коэффициенты в уравнении биссектрисы	
	std::vector<double> bis_cross_point(Bisectrix b1, Bisectrix b2); // вычисление точки пересечения двух биссектрис
	std::vector<double> pick_cross_point(Bisectrix bis); // возвращение точки пересечения данной биссектрисы с другой
	void show();
	void writenumbers(std::ostream &OutputFile);
};

	