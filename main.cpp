/* Import */
#define LAPYS_HOSTED             true
#define LAPYS_PREPROCESSOR       true
#define LAPYS_PREPROCESSOR_GUARD false

#include <cstdio>
#include "lapys.hpp"

/* ... */
using namespace Lapys;

/* Main */
struct add {
  template <typename typeA, typename typeB>
  static int value(typeA, typeB, bool const (*const)[sizeof(typeid(instanceof<typeA>() + instanceof<typeB>()))] = NULL);
};

template <typename cumulation, typename base, std::size_t>
struct cumulate {
  // typedef cumulation (*bruh)[sizeof(*instanceof<base>())];
};

struct object {
  friend int operator +(object const, object const); // must be true
};

template <typename, std::size_t>
struct map {
  typedef void type;
};

// ...
int main(int, char*[]) /* noexcept */ {
  std::printf("[int,    int]   : %4.5s" "\r\n", opinfo::nonoverloaded::has<opinfo::add, int,    int>   ::value ? "true" : "false");
  std::printf("[int,    void]  : %4.5s" "\r\n", opinfo::nonoverloaded::has<opinfo::add, int,    void>  ::value ? "true" : "false");
  std::printf("[int,    object]: %4.5s" "\r\n", opinfo::nonoverloaded::has<opinfo::add, int,    object>::value ? "true" : "false");
  std::printf("[object, object]: %4.5s" "\r\n", opinfo::nonoverloaded::has<opinfo::add, object, object>::value ? "true" : "false");
  std::printf("%1.2s", "\r\n");
  std::printf("[int,    int]   : %4.5s" "\r\n", opinfo::nonoverloaded::has<opinfo::binary, int,    int>   ::valueof<add>::value ? "true" : "false");
  std::printf("[int,    void]  : %4.5s" "\r\n", opinfo::nonoverloaded::has<opinfo::binary, int,    void>  ::valueof<add>::value ? "true" : "false");
  std::printf("[int,    object]: %4.5s" "\r\n", opinfo::nonoverloaded::has<opinfo::binary, int,    object>::valueof<add>::value ? "true" : "false");
  std::printf("[object, object]: %4.5s" "\r\n", opinfo::nonoverloaded::has<opinfo::binary, object, object>::valueof<add>::value ? "true" : "false");

  // instanceof<collection<int (*)[1], int (*)[2], int (*)[3]>::build<trait>::type>() * 2;
  std::printf("%1.13s", "Hello, World!");
  return 0x00; // --> EXIT_SUCCESS
}

// void Lapys::Main(CommandLineArguments const& arguments) {
//   static_cast<void>(arguments);
// }
