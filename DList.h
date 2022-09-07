#pragma once
#include <cstdlib>
#include <cstdio>
#include <iostream>

// Узел ДЦС
template <class T>
struct DList
{
  T field; // поле данных
  struct DList *next; // указатель на следующий элемент
  struct DList *prev; // указатель на предыдущий элемент
};

// Инициализация ДЦС
template <class T>
struct DList<T> * init(T a)  // а- значение первого узла
{
  struct DList<T> *lst;
  // выделение памяти под корень списка
  lst = (struct DList<T>*)malloc(sizeof(struct DList<T>));
  lst->field = a;
  lst->next = lst; // указатель на следующий узел
  lst->prev = lst; // указатель на предыдущий узел
  return(lst);
}

// Добавление узла в ДЦС
template <class T>
struct DList<T> * addelem(DList<T> *lst, T number)
{
  struct DList<T> *temp, *p;
  temp = (struct DList<T>*)malloc(sizeof(struct DList<T>));
  p = lst->next; // сохранение указателя на следующий узел
  lst->next = temp; // предыдущий узел указывает на создаваемый
  temp->field = number; // сохранение поля данных добавляемого узла
  temp->next = p; // созданный узел указывает на следующий узел
  temp->prev = lst; // созданный узел указывает на предыдущий узел
  p->prev = temp;
  return(temp);
}

// Поиск элемента с определенным значением
template <class T>
struct DList<T> * findelem(DList<T> *lst, T a)
{
  struct DList<T> *p;
  p = lst;
  do {
    p = p->next; // переход к следующему узлу
  } while (p->field != a); // условие окончания обхода
  return(p);
}



// Удаление узла ДЦС
template <class T>
struct DList<T> * deletelem(DList<T> *lst)
{
  struct DList<T> *prev, *next;
  prev = lst->prev; // узел, предшествующий lst
  next = lst->next; // узел, следующий за lst
  prev->next = lst->next; // переставляем указатель
  next->prev = lst->prev; // переставляем указатель
  free(lst); // освобождаем память удаляемого элемента
  return(prev);
}


// Вывод элементов ДЦС
template <class T>
void listprint(DList<T> *lst)
{
  struct DList<T> *p;
  p = lst;
  do {
    std::cout << p->field << " "; // вывод значения элемента p
    p = p->next; // переход к следующему узлу
  } while (p != lst); // условие окончания обхода
  std::cout << "\n";
}


// Поиск элемента с минимальным значением
template <class T>
struct DList<T> * minimum(DList<T> *lst)
{
	
  struct DList<T> *p;
  struct DList<T> *pmin;
  int vmin;
    
  pmin = lst;  
  vmin = pmin->field; 
  p = lst;
  
  do {  
  p = p->next; // переход к следующему узлу
	if (p->field < vmin) {
		vmin = p->field; 
		pmin = p;
		}
	
  } while (p != lst); // условие окончания обхода
  return(pmin);
  
}

/*
// Вывод элементов ДЦС в обратном порядке
template <class T>
void listprintr(DList<T> *lst)
{
  struct DList<T> *p;
  p = lst;
  do {
    p = p->prev;  // переход к предыдущему узлу
	std::cout << p->field << " ";
  } while (p != lst); // условие окончания обхода
  std::cout << "\n";
}
*/

