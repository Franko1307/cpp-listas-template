/*
  Autor: Francisco Enrique Córdova González
  Esta librería es de uso académico únicamente
  Última actualización: 14/02/16
 */
//Directivas al compilador
#pragma once
#include <iostream>

enum Ubicacion{VACIO, INICIO, MITAD, FINAL};
enum Encontrado{SI,NO};

template <class T> struct mult_caja {
  mult_caja<T> *siguiente;
  T var;
  size_t cantidad;
};
template <class T> class list_ord_sin_rep {
private:
  Ubicacion donde;
  Encontrado encontrado;
  mult_caja<T> *principio, *anterior;
  void buscar(T var);
public:
  list_ord_sin_rep(): principio(NULL), anterior(NULL), donde(VACIO), encontrado(NO){};
  ~list_ord_sin_rep();
  bool agregar(T var);
  bool eliminar(T var);
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
  donde = VACIO;
  encontrado = NO;
  principio = NULL;
  anterior = NULL;
}
/*
 * Función que busca si existe un número en la lista ordenada sin repetición
 * Parámetros:
 * T var; Es el elemento a buscar en la lista ordenada sin repetición.
 */
template <class T> void list_ord_sin_rep<T>::buscar(T var) {
  mult_caja<T> *p;
  //Si esto pasa quiere decir que en la lista no hay nada, por lo cual ni para
  //que buscar, simplemente decimos que no lo encontramos y ponemos vacio
  //y lo regresamos, el anterior es opcional pero pues para asegurar.
  if (principio == NULL) {
    encontrado = NO;
    donde = VACIO;
    anterior = NULL;
    return;
  }
  p = principio;
  //Sino está vacía entonces la recorreremos
  while (p) {
    //El mejor caso, encontramos el valor
    if (p->var == var){
      encontrado = SI; //encontrado
      //Ahora vamos a ver dónde está.
      if (principio == p) donde = INICIO;
      else if (p->siguiente == NULL) donde = FINAL;
      else donde = MITAD;
      //Y ya terminamos y regresamos.
      return;
    }
    //Esto quiere decir que el valor actual de p es menor que el de var
    //Lo cual no nos dice nada así que seguimos recorriendo
    else if (p->var < var){
      anterior = p;
      p = p->siguiente;
    } else {
      //Pero si pasa esto 'p->var > var' quiere decir que nos pasamos
      //Y ya no va a estar en el otro lado ya que está ordenada
      encontrado = NO;
      //Y buscamos dónde nos quedamos.
      if (principio == p) donde = INICIO;
      else if (p->siguiente == NULL) donde = FINAL;
      else donde = MITAD;
      return;
    }
  }
  encontrado = NO;
  donde = FINAL;
}
/*
 * Función que se encarga de agregar un valor a una lista ordenada sin repetición
 * Parámetros:
 * T var; Es el elemento a agregar en la lista ordenada sin repetición
 */
template <class T> bool list_ord_sin_rep<T>::agregar(T var) {
  mult_caja<T> *p;
  //Utilizamos buscar para que nos asigne las variables
  //encontrado y donde
  buscar(var);
  //Si el elemento ya se encuentra en la lista no lo agregamos
  if (encontrado == SI) return false;
  p = new mult_caja<T>;
  p->var = var;
  //Si donde es vacío quiere decir que no había ningún elemento en la lista
  if (donde == VACIO) {
    p->siguiente = NULL;
    principio = p;
  }
  else if (donde == INICIO) {
    p->siguiente = principio;
    principio = p;
  //Aquí cambié el código original, quité la parte de final ya que
  //Aunque no en todos los casos de estructura de datos es así
  //En este caso, es decir este programa el final y el medio se comportan igual
  //Y de hecho, de la manera del código original fallaba y así funciona
  } else {
    p->siguiente = anterior->siguiente;
    anterior->siguiente = p;
  }
  return true;
}
/*
 * Esta función se encarga de eliminar un elemento de la lista
 */
template <class T> bool list_ord_sin_rep<T>::eliminar(T var) {
  mult_caja<T> *p;
  buscar(var);
  //Buscamos si el elemento está en la lista, si no está devolvemos falso
  if (encontrado == NO) return false;
  //Con donde conseguimos la ubicación del elemento
  if (donde == INICIO) {
    p = principio;
    principio = p->siguiente;
  } else if (donde == FINAL) {
      p = anterior->siguiente;
      anterior->siguiente = NULL;
  } else {
      p = anterior->siguiente;
      anterior->siguiente = p->siguiente;
  }
  delete p;
  return true;
}
/*
 *Función que se encarga de pintar la lista
 */
template <class T> void list_ord_sin_rep<T>::pintar() {
  mult_caja<T> *p = principio;
  //Vamos recorriendo la lista con p e imprimiendo sus valores.
  while (p) {
    std::cout << p->var << std::endl;
    p = p->siguiente;
  }
}
//**************************************************************************
//Inicia otra clase, la clase de la lista ordenada con mucha repetición.
template <class T> class list_ord_con_mu_rep {
private:
  Ubicacion donde;
  Encontrado encontrado;
  mult_caja<T> *principio, *anterior;
  void buscar(T var);
public:
  list_ord_con_mu_rep(): donde(VACIO), encontrado(NO), principio(NULL), anterior(NULL){};
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
  donde = VACIO;
  encontrado = NO;
  principio = NULL;
  anterior = NULL;
}
template <class T> void list_ord_con_mu_rep<T>::buscar(T var) {
  mult_caja<T> *p;
  if (principio == NULL) {
    encontrado = NO;
    donde = VACIO;
    return;
  }
  p = principio;
  while (p) {
    if (p->var == var) {
      encontrado = SI;
      if (principio == p) donde = INICIO;
      else if (p->siguiente == NULL) donde = FINAL;
      else donde = MITAD;
      return;
    } else if (p->var < var) {
      anterior = p;
      p = p->siguiente;
    } else {
      encontrado = NO;
      if (principio == p) donde = INICIO;
      else if (p->siguiente == NULL) donde = FINAL;
      else donde = MITAD;
      return;
    }
  }
  encontrado = NO;
  donde = FINAL;
}
template <class T> bool list_ord_con_mu_rep<T>::agregar(T var) {
  buscar(var);
  if (encontrado == SI) {
    if (donde == INICIO) principio->cantidad++;
    else anterior->siguiente->cantidad++;
    return true;
  }
  mult_caja<T> *p;
  p = new mult_caja<T>;
  p->var = var;
  p->cantidad = 1;
  if (donde == VACIO) {
    p->siguiente = NULL;
    principio = p;
  } else if (donde == INICIO){
    p->siguiente = principio;
    principio = p;
  } else {
    p->siguiente = anterior->siguiente;
    anterior->siguiente = p;
  }
  return true;
}
template <class T> bool list_ord_con_mu_rep<T>::borrar(T var) {
  mult_caja<T> *p;
  buscar(var);
  if (encontrado == SI){
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
  while (p) {
    std::cout << p->var << " : " << p->cantidad << std::endl;
    p = p->siguiente;
  }
}
//*********************************************************************
//Aquí inicia la clase de lista ordenada con poca repetición
template <class T> class list_ord_con_rep{
private:
  Ubicacion donde;
  Encontrado encontrado;
  mult_caja<T> *principio, *anterior;
  void buscar(T var);
public:
  list_ord_con_rep(): donde(VACIO),encontrado(NO),principio(NULL),anterior(NULL){};
  ~list_ord_con_rep();
  bool agregar(T var);
  bool borrar(T var);
  void pintar();

};
template <class T> list_ord_con_rep<T>::~list_ord_con_rep() {
  mult_caja<T> *p;
  while (principio) {
    p = principio;
    principio = p->siguiente;
    delete p;
  }
}
template <class T> void list_ord_con_rep<T>::buscar(T var) {
  mult_caja<T> *p;
  if (principio == NULL) {
    donde = VACIO;
    encontrado = NO;
    return;
  }
  p = principio;
  while (p) {
    if (p->var == var) {
      encontrado = SI;
      if (p == principio) donde = INICIO;
      else if (p->siguiente == NULL) donde = FINAL;
      else donde = MITAD;
      return;
    } else if (p->var < var) {
      anterior = p;
      p = p->siguiente;
    } else {
      encontrado = NO;
      if (p == principio) donde = INICIO;
      else if (p->siguiente == NULL) donde = FINAL;
      else donde = MITAD;
      return;
    }
  }
  encontrado = NO;
  donde = FINAL;
}
template <class T> bool list_ord_con_rep<T>::agregar(T var) {
  mult_caja<T> *p;
  buscar(var);
  p = new mult_caja<T>;
  p->var = var;
  if (donde == VACIO) {
    p->siguiente = NULL;
    principio = p;
  } else if (donde == INICIO) {
    p->siguiente = principio;
    principio = p;
  } else {
    p->siguiente = anterior->siguiente;
    anterior->siguiente = p;
  }
  return true;
}
template <class T> void list_ord_con_rep<T>::pintar() {
  mult_caja<T> *p = principio;
  while (p) {
    std::cout << p->var << std::endl;
    p = p->siguiente;
  }
}
