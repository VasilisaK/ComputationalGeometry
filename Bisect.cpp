#include "Bisect.h"



// ------------------------------------ Методы класса биссектрисы --------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------


// конструктор класса биссектрисы
Bisectrix::Bisectrix() {};


// чтение координат точки, лежащей на данной биссектрисе 
// (точка пересечения двух других биссектрис, образующих угол, биссектрисой которого является текущая биссектриса)
void Bisectrix::read_cross_point(double x, double y, int n1, int n2, int n3) {
	
	cross_point_X = x;
	cross_point_Y = y;
	nL = n1;
	n = n2;
	nR = n3;
//	std::cout << "Cross point: " << x << " " << y << "\n";
	
}


// коэффициенты в уравнении биссектрисы	
void Bisectrix::calc_bis_coeffs(double xR, double yR, double xL, double yL) {
	
	double L1, L2, Xp1, Yp1, Xp2, Yp2, x_extra, y_extra;
	double x1, y1, x2, y2;
	
	// длины отрезков прямых, проходящих через общую точку
	L1 = sqrt( (xR - cross_point_X)*(xR - cross_point_X) + (yR - cross_point_Y)*(yR - cross_point_Y) );
	L2 = sqrt( (xL - cross_point_X)*(xL - cross_point_X) + (yL - cross_point_Y)*(yL - cross_point_Y) );
	
	// точка на первой прямой 
	// (справа от общей точки - при обходе против час.стрелки)
	Xp1 = xR;
	Yp1 = yR;
	
	// точка на второй прямой, находится на том же расстоянии от общей точки пересечения прямых, что и первая
	// (слева от общеей точки - при обходе против час.стрелки)
	Xp2 = cross_point_X + (L1/L2) * (xL - cross_point_X);
	Yp2 = cross_point_Y + (L1/L2) * (yL - cross_point_Y);
	
	// дополнительная (вторая) точка, лежащая на биссектрисе
	x_extra = (Xp1 + Xp2)/2.0;
	y_extra = (Yp1 + Yp2)/2.0;
	
//	std::cout << "x_extra = " << x_extra << " y_extra = " << y_extra << "\n";

	x1 = x_extra;
	y1 = y_extra;
	x2 = cross_point_X;
	y2 = cross_point_Y;

	A_bis = y2 - y1;
	B_bis = x1 - x2;
	C_bis = y1*x2 - x1*y2;
	
//	std::cout << "A = " << A_bis << " B = " << B_bis << " C = " << C_bis << "\n";
	
}


// вычисление точки пересечения двух биссектрис
std::vector<double> Bisectrix::bis_cross_point(Bisectrix b1, Bisectrix b2) {
	
	double x0, y0;
	std::vector<double> coord(2);
	double DetM, DetX, DetY; 
	
	DetM = b1.A_bis*b2.B_bis - b2.A_bis*b1.B_bis;
	DetX = -b1.C_bis*b2.B_bis + b2.C_bis*b1.B_bis;
	DetY = -b1.A_bis*b2.C_bis + b2.A_bis*b1.C_bis;
	
//	std::cout << "DetM = " << DetM << "\n";
	
	x0 = DetX/DetM;
	y0 = DetY/DetM;
	
	coord[0] = x0;
	coord[1] = y0;
	
	return coord;
}

// возвращение точки пересечения данной биссектрисы с другими

std::vector<double> Bisectrix::pick_cross_point(Bisectrix bis){
	
	std::vector<double> coord(2);
	coord[0] = bis.cross_point_X;
	coord[1] = bis.cross_point_Y;
	
	return coord;
}


void Bisectrix::show(){
	std::cout << "Bisectrix:\n";
	std::cout << "X = " << cross_point_X << " Y = " << cross_point_Y << " (" << nL << " " << n << " " << nR << ")" << "\n";
	std::cout << "A = " << A_bis << " B = " << B_bis << " C = " << C_bis << "\n";
}

void Bisectrix::writenumbers(std::ostream &OutputFile) {
	if (nL > 10e7) {
		OutputFile << "(" << n << ") ";
//		std::cout << "(" << n << ") \n";
	}
	else {
		OutputFile << "(" << nL << " " << n << " " << nR <<  ") ";
//		std::cout << "(" << nL << " " << n << " " << nR <<  ") \n";
	}
}