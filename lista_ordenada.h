/*
  Autor: Francisco Enrique Córdova González
  Esta librería es de uso académico únicamente
  Última actualización: 14/02/16
 */
//Directivas al compilador
#pragma once
#include <iostream>

enum Ubicacion{INICIO,MITAD};

template <class T> struct mult_caja {
  mult_caja<T> *siguiente;
  T var;
  size_t cantidad;
};
template <class T> class list_ord_sin_rep {
private:
  Ubicacion donde;
  bool encontrado;
  mult_caja<T> *principio, *anterior;
  void buscar(T);
public:
  list_ord_sin_rep(): principio(NULL), anterior(NULL), donde(INICIO), encontrado(false){};
  ~list_ord_sin_rep();
  bool agregar(T);
  bool eliminar(T);
  void pintar();
};
/*
 * Destructor de la clas list_ord_sin_rep
 */
template <class T> list_ord_sin_rep<T>::~list_ord_sin_rep() {
  mult_caja<T> *p;
  //Se recorren todos los elementos que haya y se van borrando
  while (principio) {
    p = principio;
    principio = p->siguiente;
    delete p;
  }
  //Volvemos estos valores nulos también.
  donde = INICIO;
  encontrado = false;
  principio = NULL;
  anterior = NULL;
}
/*
 * Función que busca si existe un número en la lista ordenada sin repetición
 * Parámetros:
 * T var; Es el elemento a buscar en la lista ordenada sin repetición.
 */
template <class T> void list_ord_sin_rep<T>::buscar(T var) {
  //Si esto pasa quiere decir que en la lista no hay nada, por lo cual ni para
  //que buscar, simplemente decimos que no lo encontramos y ponemos inicio
  //y lo regresamos, el anterior es opcional pero pues para asegurar.
  if (!principio) {
    encontrado = false;
    donde = INICIO;
    anterior = NULL;
    return;
  }
  mult_caja<T> *p = principio;
  while (p) {
    if (p->var < var){
      anterior = p;
      p = p->siguiente;
    } else if (p->var == var){ //Caso donde encontramos el valor
      encontrado = true;
      if (principio == p) donde = INICIO;
      else donde = MITAD;
      return;
    } else {
      encontrado = false;
      if (principio == p) donde = INICIO;
      else donde = MITAD;
      return;
    }
  }
  encontrado = false;
  donde = MITAD;
}
/*
 * Función que se encarga de agregar un valor a una lista ordenada sin repetición
 * Parámetros:
 * T var; Es el elemento a agregar en la lista ordenada sin repetición
 */
template <class T> bool list_ord_sin_rep<T>::agregar(T var) {
  mult_caja<T> *p;
  buscar(var);
  if (encontrado) return false;
  p = new mult_caja<T>;
  p->var = var;
  if (donde == MITAD) {
    p->siguiente = anterior->siguiente;
    anterior->siguiente = p;
  } else {
    p->siguiente = principio;
    principio = p;
  }
  return true;
}
/*
 * Esta función se encarga de eliminar un elemento de la lista
 */
template <class T> bool list_ord_sin_rep<T>::eliminar(T var) {
  buscar(var);
  mult_caja<T> *p;
  if (!encontrado) return false;
  if (donde == MITAD) {
    p = anterior->siguiente;
    anterior->siguiente = p->siguiente;
  } else {
      p = principio;
      principio = p->siguiente;
  }
  delete p;
  return true;
}
/*
 *Función que se encarga de pintar la lista
 */
template <class T> void list_ord_sin_rep<T>::pintar() {
  mult_caja<T> *p = principio;
  std::cout << "[";
  while (p) {
    std::cout << p->var << ",";
    p = p->siguiente;
  }
  std::cout << "\b]" << std::endl;
}
//**************************************************************************
//Inicia otra clase, la clase de la lista ordenada con mucha repetición.
template <class T> class list_ord_con_mu_rep {
private:
  Ubicacion donde;
  bool encontrado;
  mult_caja<T> *principio, *anterior;
  void buscar(T var);
public:
  list_ord_con_mu_rep(): donde(INICIO), encontrado(false), principio(NULL), anterior(NULL){};
  ~list_ord_con_mu_rep();
  bool agregar(T var);
  bool borrar(T var);
  void pintar();
};
template <class T> list_ord_con_mu_rep<T>::~list_ord_con_mu_rep() {
  mult_caja<T> *p = principio;
  while (principio) {
    p = principio;
    principio=p->siguiente;
    delete p;
  }
  donde = INICIO;
  encontrado = false;
  principio = NULL;
  anterior = NULL;
}
template <class T> void list_ord_con_mu_rep<T>::buscar(T var) {
  if (!principio) {
    encontrado = false;
    donde = INICIO;
    anterior = NULL;
    return;
  }
  mult_caja<T> *p = principio;
  while (p) {
    if (p->var < var) {
      anterior = p;
      p = p->siguiente;
    } else if (p->var == var) {
      encontrado = true;
      if (principio == p) donde = INICIO;
      else donde = MITAD;
      return;
    } else {
      encontrado = false;
      if (principio == p) donde = INICIO;
      else donde = MITAD;
      return;
    }
  }
  encontrado = false;
  donde = MITAD;
}
template <class T> bool list_ord_con_mu_rep<T>::agregar(T var) {
  buscar(var);
  if (encontrado) {
    if (donde == INICIO) principio->cantidad++;
    else anterior->siguiente->cantidad++;
    return true;
  }
  mult_caja<T> *p;
  p = new mult_caja<T>;
  p->var = var;
  p->cantidad = 1;
  if (donde == MITAD){
    p->siguiente = anterior->siguiente;
    anterior->siguiente = p;
  } else {
    p->siguiente = principio;
    principio = p;
  }
  return true;
}
template <class T> bool list_ord_con_mu_rep<T>::borrar(T var) {
  mult_caja<T> *p;
  buscar(var);
  if (encontrado){
    if (donde == INICIO) p = principio;
    else p = anterior->siguiente;
    if (p->cantidad > 1) p->cantidad--;
    else {
      if (donde == INICIO) principio = p->siguiente;
      else anterior->siguiente = p->siguiente;
      delete p;
    }
    return true;
  }
  return false;
}
template <class T> void list_ord_con_mu_rep<T>::pintar() {
  mult_caja<T> *p = principio;
  std::cout << "[";
  while (p) {
    std::cout <<"{"<< p->var << " : " << p->cantidad << "} ";
    p = p->siguiente;
  }
  std::cout << "\b]" << std::endl;
}
//*********************************************************************
//Aquí inicia la clase de lista ordenada con poca repetición
template <class T> class list_ord_con_rep{
private:
  Ubicacion donde;
  bool encontrado;
  mult_caja<T> *principio, *anterior;
  void buscar(T);
public:
  list_ord_con_rep(): donde(INICIO),encontrado(false),principio(NULL),anterior(NULL){};
  ~list_ord_con_rep();
  bool agregar(T);
  bool borrar(T);
  void pintar();

};
template <class T> list_ord_con_rep<T>::~list_ord_con_rep() {
  mult_caja<T> *p;
  while (principio) {
    p = principio;
    principio = p->siguiente;
    delete p;
  }
  encontrado = false;
  donde = INICIO;
  principio = anterior = NULL;
}
template <class T> void list_ord_con_rep<T>::buscar(T var) {
  if (!principio) {
    donde = INICIO;
    encontrado = false;
    return;
  }
  mult_caja<T> *p = principio;
  while (p) {
    if (p->var < var) {
      anterior = p;
      p = p->siguiente;
    } else if (p->var == var) {
      encontrado = true;
      if (p == principio) donde = INICIO;
      else donde = MITAD;
      return;
    } else {
      encontrado = false;
      if (p == principio) donde = INICIO;
      else donde = MITAD;
      return;
    }
  }
  encontrado = false;
  donde = MITAD;
}
template <class T> bool list_ord_con_rep<T>::agregar(T var) {
  mult_caja<T> *p;
  buscar(var);
  p = new mult_caja<T>;
  p->var = var;
  if (donde == MITAD) {
    p->siguiente = anterior->siguiente;
    anterior->siguiente = p;
  } else {
    p->siguiente = principio;
    principio = p;
  }
  return true;
}
template <class T> void list_ord_con_rep<T>::pintar() {
  mult_caja<T> *p = principio;
  std::cout << "[";
  while (p) {
    std::cout << p->var << ",";
    p = p->siguiente;
  }
  std::cout << "\b]" << std::endl;
}
