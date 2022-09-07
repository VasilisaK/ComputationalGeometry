#include "DList.h"
#include "Bisect.h"
#include "Voronoi.h"
#include <fstream>

//фуекции проверки открытия файла
void IsOpen(std::ifstream& oi);
void IsOpen(std::ofstream& of);

int main() {
	
	
	char InOutInfoName[] = "inout.txt";
	std::ifstream InOutInfoFile; //файл с названиями имен файлов
	std::ifstream InputFile; //входной файл
	std::ofstream OutputFile; //выходной файл
	char InputFileName[40];
	char OutputFileName[40];
	int VN;
	int i;
	double p1, p2, p3, p4, p1f, p2f;
	std::vector<double> coord(2);

	//чтение названий входного и выходного файлов
	InOutInfoFile.open(InOutInfoName);
	IsOpen(InOutInfoFile);
	InOutInfoFile >> InputFileName;
//	std::cout << InputFileName << "\n";
	InOutInfoFile >> OutputFileName;
//	std::cout << OutputFileName << "\n";
	InOutInfoFile.close();
	
	InputFile.open(InputFileName);
	IsOpen(InputFile);
	InputFile >> VN;
//	std::cout << VN << "\n";


	//создание списка сторон
	DList<Side> * sidepointer;
	Side side1;
	InputFile >> p1f >> p2f;
	InputFile >> p3 >> p4;
	side1.fillside(p1f, p2f, p3, p4, 0);
	sidepointer = init(side1);
	
	
	for (i = 1; i < VN-1; ++i) {
		p1 = p3;
		p2 = p4;
		InputFile >> p3 >> p4;
		side1.fillside(p1, p2, p3, p4, i);
		sidepointer = addelem(sidepointer, side1);
	}
	InputFile.close();
	
	p1 = p3;
	p2 = p4;
	side1.fillside(p1, p2, p1f, p2f, i);
	sidepointer = addelem(sidepointer, side1);


	//создание списка биссектрис
	DList<Bisectrix> * bispointer;
	Bisectrix bis1;
	bis1.read_cross_point(sidepointer->field.pick_coord()[0], sidepointer->field.pick_coord()[1], 10e8, sidepointer->field.pick_number(), 10e8);
	bis1.calc_bis_coeffs((sidepointer->prev)->field.pick_coord()[0], (sidepointer->prev)->field.pick_coord()[1], sidepointer->field.pick_coord()[2], sidepointer->field.pick_coord()[3]);
	bispointer = init(bis1);
	sidepointer = sidepointer->next;
	for (i = 1; i < VN; ++i) {
		bis1.read_cross_point(sidepointer->field.pick_coord()[0], sidepointer->field.pick_coord()[1], 10e8, sidepointer->field.pick_number(), 10e8);
		bis1.calc_bis_coeffs((sidepointer->prev)->field.pick_coord()[0], (sidepointer->prev)->field.pick_coord()[1], sidepointer->field.pick_coord()[2], sidepointer->field.pick_coord()[3]);
		bispointer = addelem(bispointer, bis1);
		sidepointer = sidepointer->next;
	}
	
	sidepointer = sidepointer->prev;
	
	//создание списка точек пересечения биссектрис и списка расстояний от них до сторон
	DList<CrossPoint> * cppointer;
	CrossPoint cp1;
	DList<double> * distpointer;
	double dist1;
	coord = bispointer->field.bis_cross_point(bispointer->field, (bispointer->next)->field);
	cp1.fillcrossp(coord[0], coord[1]);
	dist1 = calc_distance(coord[0], coord[1], bispointer->field.pick_cross_point(bispointer->field)[0], bispointer->field.pick_cross_point(bispointer->field)[1], (bispointer->next)->field.pick_cross_point((bispointer->next)->field)[0], (bispointer->next)->field.pick_cross_point((bispointer->next)->field)[1]);
	cppointer = init(cp1);
	distpointer = init(dist1);
	
//	std::cout << "Initialization\n";
//	std::cout << "\n";
//	sidepointer->field.show();
//	cppointer->field.show();
//	std::cout << distpointer->field << "\n";
//	std::cout << "\n";
		
	for (i = 1; i < VN; ++i) {
		
		sidepointer = sidepointer->next;
		bispointer = bispointer->next;
		
		coord = bispointer->field.bis_cross_point(bispointer->field, (bispointer->next)->field);
		cp1.fillcrossp(coord[0], coord[1]);
		dist1 = calc_distance(coord[0], coord[1], sidepointer->field.pick_coord()[0], sidepointer->field.pick_coord()[1], sidepointer->field.pick_coord()[2], sidepointer->field.pick_coord()[3]);


		cppointer = addelem(cppointer, cp1);
		distpointer = addelem(distpointer, dist1);
		
//		sidepointer->field.show();
//		cppointer->field.show();
//		std::cout << distpointer->field << "\n";
//		std::cout << "\n";

	}
	
		
		DList<double> * dp;
		DList<double> * dpmin;
		double vmin;
  
		DList<CrossPoint> * cp;
		DList<CrossPoint> * cpmin;
		DList<Bisectrix> * bs;
		DList<Bisectrix> * bsmin;
		DList<Side> * sd;
		DList<Side> * sdmin;	

		Bisectrix bis2;
		CrossPoint cp2;
		double dist2;
	
	
	OutputFile.open(OutputFileName);
	IsOpen(OutputFile);
	
//	std::cout << "Continue\n";
//	std::cout << "\n";
	
	//цикл поиска минимального расстояния и ребер диаграммы Вороного	
	for (i = 0; i < VN-3; ++i) {
				
		//поиск минимального расстояния		
		dp = distpointer;
		dpmin = distpointer;		
		vmin = dpmin->field; 
		cp = cppointer;
		bs = bispointer;
		sd = sidepointer;
		cpmin = cppointer;
		bsmin = bispointer;
		sdmin = sidepointer;
		
		do {  
		dp = dp->next; // переход к следующему узлу
		cp = cp->next;
		bs = bs->next;
		sd = sd->next;

		 
			if (dp->field < vmin) {
				vmin = dp->field; 
				dpmin = dp;
				cpmin = cp;
				bsmin = bs;
				sdmin = sd;
				}
		} while (dp != distpointer); // условие окончания обхода
				
		distpointer = dpmin;
		cppointer = cpmin;
		bispointer = bsmin;
		sidepointer = sdmin;
		
		// нахождение новой биссектрисы
		coord = sidepointer->field.side_cross_point((sidepointer->prev)->field,(sidepointer->next)->field);
		bis2.read_cross_point(coord[0], coord[1], (sidepointer->prev)->field.pick_number(), sidepointer->field.pick_number(), (sidepointer->next)->field.pick_number());		
		bis2.calc_bis_coeffs(bispointer->field.pick_cross_point(bispointer->field)[0], bispointer->field.pick_cross_point(bispointer->field)[1], (bispointer->next)->field.pick_cross_point((bispointer->next)->field)[0], (bispointer->next)->field.pick_cross_point((bispointer->next)->field)[1]);
		
		// печать ребер
		bispointer->field.writenumbers(OutputFile);
		bis2.writenumbers(OutputFile);
		OutputFile << std::endl;
		(bispointer->next)->field.writenumbers(OutputFile);
		bis2.writenumbers(OutputFile);
		OutputFile << std::endl;
		
		// удаление стороны
		sidepointer = deletelem(sidepointer);
		//удаление 3 точек пересечения
		cppointer = deletelem(cppointer);
		cppointer = deletelem(cppointer);
		cppointer = deletelem(cppointer->next);
		// удаление 3 расстояний				
		distpointer = deletelem(distpointer);
		distpointer = deletelem(distpointer);
		distpointer = deletelem(distpointer->next);
		// удаление 2 биссектрис
		bispointer = deletelem(bispointer);
		bispointer = deletelem(bispointer->next);
		// добавление новой биссектрисы и сдвиг указателя на нужную сторону		
		bispointer = addelem(bispointer, bis2);
		sidepointer = sidepointer->next;
			
		// нахождение и добавление 2 точек пересечения биссектрис и их расстояний до соответствующих сторон
		coord = (bispointer->prev)->field.bis_cross_point((bispointer->prev)->field, bispointer->field);
		cp2.fillcrossp(coord[0], coord[1]);
		dist2 = calc_distance(coord[0], coord[1], (sidepointer->prev)->field.pick_coord()[0], (sidepointer->prev)->field.pick_coord()[1], (sidepointer->prev)->field.pick_coord()[2], (sidepointer->prev)->field.pick_coord()[3]);
		cppointer = addelem(cppointer, cp2);
		distpointer = addelem(distpointer, dist2);	
		
//		(sidepointer->prev)->field.show();
//		cppointer->field.show();
//		std::cout << distpointer->field << "\n";
//		std::cout << "\n";
					
		coord = bispointer->field.bis_cross_point(bispointer->field, (bispointer->next)->field);
		cp2.fillcrossp(coord[0], coord[1]);
		dist2 = calc_distance(coord[0], coord[1], sidepointer->field.pick_coord()[0], sidepointer->field.pick_coord()[1], sidepointer->field.pick_coord()[2], sidepointer->field.pick_coord()[3]);
		cppointer = addelem(cppointer, cp2);
		distpointer = addelem(distpointer, dist2);	
		
//		sidepointer->field.show();
//		cppointer->field.show();
//		std::cout << distpointer->field << "\n";
//		std::cout << "\n";
	
//	std::cout << "\n";	
//	sidepointer->field.show();
//	bispointer->field.show();
//	(bispointer->next)->field.show();
//	cppointer->field.show();
//	std::cout << distpointer->field << "\n";
//	std::cout << std::endl;	
		
		
	}
	
	
		// печать последних ребер
		bispointer->field.writenumbers(OutputFile);
		OutputFile << "(" << sidepointer->field.pick_number() << " " << (sidepointer->next)->field.pick_number() << " " << (sidepointer->prev)->field.pick_number() << ")";
		OutputFile << std::endl;
		(bispointer->next)->field.writenumbers(OutputFile);
		OutputFile << "(" << sidepointer->field.pick_number() << " " << (sidepointer->next)->field.pick_number() << " " << (sidepointer->prev)->field.pick_number() << ")";
		OutputFile << std::endl;
		(bispointer->prev)->field.writenumbers(OutputFile);
		OutputFile << "(" << sidepointer->field.pick_number() << " " << (sidepointer->next)->field.pick_number() << " " << (sidepointer->prev)->field.pick_number() << ")";
		OutputFile << std::endl;
		
		OutputFile.close();
	
		
	return 0;
}

void IsOpen(std::ifstream& oi)
{
	if (!oi.is_open())
	{
		exit(EXIT_FAILURE);
	}
}

void IsOpen(std::ofstream& of)
{
	if (!of.is_open())
	{
		exit(EXIT_FAILURE);
	}
}

