#pragma once
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <string> 

//класс точки пересечения
class CrossPoint {
private:
	double CrossPointX; //координаты
	double CrossPointY;

public:
	CrossPoint(); //конструктор
	void fillcrossp(double x, double y); //запись координат точки
	std::vector<double> pick_cross_point_cp(); //взятие координат
	void show();
};

//класс стороны многоугольника
class Side {
private:	
	double BeginX; //координаты начальной точки
	double BeginY;
	double EndX; //координаты конечной точки
	double EndY;
	int Number; //номер стороны
	
public:
	Side();//конструктор
	void fillside(double bx, double by, double ex, double ey, int numb); //запись информации о стороне
	std::vector<double> pick_coord();
	std::vector<double> side_cross_point(Side s1, Side s2);
	int pick_number();
	void show();
};
 
void outint(int n);
 
// вычисление расстояния от текущей точки до прямой, проходящей через две точки
double calc_distance(double x_curr, double y_curr, double xL, double yL, double xR, double yR);