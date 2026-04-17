#include "Data.hpp"
#include "Serializer.hpp"
#include <iostream>

int main() {
  Data data;
  data.value = 42;

  uintptr_t raw = Serializer::serialize(&data);
  Data *result = Serializer::deserialize(raw);

  std::cout << "Original pointer : " << &data << std::endl;
  std::cout << "Deserialized pointer: " << result << std::endl;
  std::cout << "Pointers are equal : " << (result == &data ? "true" : "false") << std::endl;
  std::cout << "Data value : " << result->value << std::endl;

  return 0;
}
