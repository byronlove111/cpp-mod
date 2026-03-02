#include "HumanA.hpp"

int main(void) {
  Weapon w;
  w.setType("sword");
  HumanA a(w, "Malik");
  a.attack();
}
