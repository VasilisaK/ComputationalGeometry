#include "Voronoi.h"

//конструктор
Side::Side() {};

//запись информации о стороне
void Side::fillside(double bx, double by, double ex, double ey, int numb) {
	BeginX = bx;
	BeginY = by;
	EndX = ex;
	EndY = ey;
	Number = numb;
//	std::cout << "side: " << BeginX << " " << BeginY << " " << EndX << " " << EndY << " " << Number << "\n"; 
}

std::vector<double> Side::pick_coord(){
	
	std::vector<double> coord(4);
	coord[0] = BeginX;
	coord[1] = BeginY;
	coord[2] = EndX;
	coord[3] = EndY;
	
	return coord;
}

int Side::pick_number(){
	return Number;
}

std::vector<double> Side::side_cross_point(Side s1, Side s2) {
	
	double A_s1, B_s1, C_s1, A_s2, B_s2, C_s2;
	double x0, y0;
	std::vector<double> coord(2);
	double DetM, DetX, DetY; 
	
	A_s1 = s1.EndY - s1.BeginY;
	B_s1 = s1.BeginX - s1.EndX;
	C_s1 = s1.BeginY*s1.EndX - s1.BeginX*s1.EndY;
	
//	std::cout << "A = " << A_s1 << " B = " << B_s1 << " C = " << C_s1 << "\n";

	A_s2 = s2.EndY - s2.BeginY;
	B_s2 = s2.BeginX - s2.EndX;
	C_s2 = s2.BeginY*s2.EndX - s2.BeginX*s2.EndY;
	
//	std::cout << "A = " << A_s2 << " B = " << B_s2 << " C = " << C_s2 << "\n";
	
	DetM = A_s1*B_s2 - A_s2*B_s1;
	DetX = -C_s1*B_s2 + C_s2*B_s1;
	DetY = -A_s1*C_s2 + A_s2*C_s1;
	
//	std::cout << "DetM = " << DetM << "\n";
	
	x0 = DetX/DetM;
	y0 = DetY/DetM;
	
	coord[0] = x0;
	coord[1] = y0;
	
	return coord;
}

void Side::show(){
	std::cout << "Side:\n";
	std::cout << "(" << BeginX << " ; " << BeginY << ") (" << EndX << " ; " << EndY << ") (" << Number << ")" << "\n";
}

//конструктор
CrossPoint::CrossPoint(){};

//запись координат точки
void CrossPoint::fillcrossp(double x, double y) {
	CrossPointX = x;
	CrossPointY = y;
}


//взятие координат
std::vector<double> CrossPoint::pick_cross_point_cp(){
	
	std::vector<double> coord(2);
	coord[0] = CrossPointX;
	coord[1] = CrossPointY;
	
	return coord;
}

void CrossPoint::show() {
	std::cout << "Cross point:\n";
	std::cout << "(" << CrossPointX << " ; " << CrossPointY << ")\n";
}


// ------------------------------------ Другие необходимые функции -------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------

void outint(int n) {std::cout << n << " ";}

// вычисление расстояния от текущей точки до прямой, проходящей через две точки
double calc_distance(double x_curr, double y_curr, double xL, double yL, double xR, double yR) {
	
	double dist;
	dist = fabs( (xR - xL) * (y_curr - yL) - (yR - yL) * (x_curr - xL) ) / sqrt( (yR - yL)*(yR - yL) + (xR - xL)*(xR - xL) );
//	std::cout << dist << "\n";
	
	return dist;
}