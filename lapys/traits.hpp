#if CPP_COMPILER == CPP__CLANG__COMPILER
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wlong-long"
#elif CPP_COMPILER == CPP__GCC__COMPILER
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wlong-long"
#endif
  /* Import > C++ Standard Library */
  #if CPP_VERSION >= 2011uL
  # include <type_traits> // Type Traits
  #endif
  #if CPP_VERSION >= 2020uL
  # include <compare> // Compare
  #endif

  /* Namespace */
  namespace Lapys {
    /* Class */
  }
#if CPP_COMPILER == CPP__CLANG__COMPILER
# pragma clang diagnostic pop
#elif CPP_COMPILER == CPP__GCC__COMPILER
# pragma GCC diagnostic pop
#endif
