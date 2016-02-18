#include <iostream>
#include "lista_ordenada.h"

int main() {
  list_ord_sin_rep<std::string> lista;
  lista.agregar("g");
  lista.agregar("a");
  lista.agregar("c");
  lista.agregar("d");
  lista.agregar("e");
  lista.agregar("b");
  lista.agregar("f");
  lista.eliminar("a");
  lista.eliminar("g");
  lista.eliminar("e");
  lista.pintar();
  std::cout << "---------------------------------" << std::endl;
  list_ord_con_mu_rep<int>lista2;
  lista2.agregar(5);
  lista2.agregar(5);
  lista2.agregar(5);
  lista2.agregar(5);
  lista2.agregar(5);
  lista2.agregar(5);
  lista2.agregar(2);
  lista2.agregar(2);
  lista2.agregar(5);
  lista2.agregar(10);
  lista2.agregar(1);
  lista2.agregar(1);
  lista2.agregar(1);
  lista2.agregar(1);
  lista2.agregar(1);
  lista2.agregar(1);
  lista2.agregar(1);
  lista2.agregar(1);
  lista2.agregar(1);
  lista2.agregar(1);
  lista2.borrar(2);
  lista2.borrar(2);
  lista2.borrar(10);
  lista2.borrar(135);
  lista2.pintar();
  std::cout << "---------------------------------" << std::endl;
  list_ord_con_rep<int> lista3;
  lista3.agregar(6.323);
  lista3.agregar(4.13);
  lista3.agregar(5.123);
  lista3.agregar(7.123);
  lista3.pintar();
  return 0;
}
