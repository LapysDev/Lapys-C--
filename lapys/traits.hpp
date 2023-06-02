#ifndef LAPYS_MODULE_TRAITS
# define LAPYS_MODULE_TRAITS
  /* Guard > ... */
  #ifdef Traits
  # error Lapys C++: Awkward. Unexpected `Traits` macro definition
  #endif

  #ifdef widthof
  # error Lapys C++: Unexpected `widthof` macro definition
  #endif

  /* Import */
  // : [...]
  #include "extensions.hpp"

  // : [C/ C++ Standard Library]
  #include <climits>  // C Limits
  #include <stdint.h> // Standard Integer
  #if CPP_VERSION >= 2011uL
  # include <type_traits> // Type Traits
  #endif

  #if defined(__cpp_impl_three_way_comparison) and defined(__cpp_lib_three_way_comparison) // --> 201907L
  # include <compare> // Compare
  #endif

  /* Definition > Maximum Size */
  #if CPP_COMPILER == CPP_CLANG_COMPILER
  # define CPP_MAX_SIZE UINT_MAX
  #elif CPP_COMPILER == CPP_MSVC_COMPILER
  # define CPP_MAX_SIZE 0x7FFFFFFFu
  #else
  # define CPP_MAX_SIZE PTRDIFF_MAX
  #endif

  /* Namespace ->> All concepts/ metafunctions/ traits should be `struct ... final`, everything else a `union ...` */
  namespace Lapys {
    /* Class > Bit ->> Distinct (unsigned) type similar to `byte` for bitwise storage */
    template <std::size_t>
    struct bit;

    /* Function */
    // Instance Of ->> Plain & simple type deduction with no reference-qualifications
    template <typename type>
    constfunc(true) type (instanceof)() noexcept;

    // Pass ->> Prevent redundant copying (and preserve type qualifications) when forwarding parameters between functions
    #ifdef __cpp_rvalue_references // --> 200610L
      template <typename type> constfunc(true) mustinline type&  (pass)(type&  object) noexcept { return static_cast<type&&>(object); }
      template <typename type> constfunc(true) mustinline type&& (pass)(type&& object) noexcept { return static_cast<type&&>(object); }
    #else
      template <typename type> constfunc(true) mustinline type&                (pass)(type&                object) noexcept { return object; }
      template <typename type> constfunc(true) mustinline type const&          (pass)(type const&          object) noexcept { return object; }
      template <typename type> constfunc(true) mustinline type const volatile& (pass)(type const volatile& object) noexcept { return object; }
      template <typename type> constfunc(true) mustinline type volatile&       (pass)(type volatile&       object) noexcept { return object; }
    #endif

    // Width Of ->> Queries bit width of expression (object)
    #define widthof(expression) (CPP_MAX_SIZE <= sizeof(::Lapys::widthof(expression)) / sizeof(unsigned char) ? sizeof(::Lapys::widthof(expression)) / sizeof(unsigned char) : 0u)

    constfunc(true)                              mustinline unsigned char /* --> byte */ (&(widthof)(bit<0u>    const)   noexcept)[CPP_MAX_SIZE];
    template <std::size_t width> constfunc(true) mustinline unsigned char /* --> byte */ (&(widthof)(bit<width> const)   noexcept)[width];
    template <typename    type>  constfunc(true) mustinline unsigned char /* --> byte */ (&(widthof)(type       nodecay) noexcept)[CHAR_BIT * sizeof(type)];

    /* Alias */
    // Byte ->> Aliases to an (unsigned) byte type blessed by the standard (as specified in the C++ language definition)
    #ifndef __cpp_lib_byte // --> 201603L
      typedef unsigned char byte;
    #else
      typedef std::byte byte;

      // ... ->> Make `Lapys::byte` types operationally consistent; cannot override standard-defined operator overloads
      constfunc(true) mustinline std::byte (operator +)(std::byte const byte) noexcept { return byte; }
      constfunc(true) mustinline std::byte (operator -)(std::byte const byte) noexcept { return static_cast<std::byte>(-std::to_integer<unsigned char>(byte)); }
      constfunc(true) mustinline bool      (operator !)(std::byte const byte) noexcept { return !std::to_integer<unsigned char>(byte); }

      template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          +=  instanceof<type nodecay>())                    (operator += )(std::byte&          byte, type nodecay object) exceptspec(exceptof(instanceof<unsigned char&>()          +=  instanceof<type nodecay>()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          +=  instanceof<type nodecay>()) evaluation = (value +=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          +=  instanceof<type nodecay>())>(evaluation); }
      template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() +=  instanceof<type nodecay>())                    (operator += )(std::byte volatile& byte, type nodecay object) exceptspec(exceptof(instanceof<unsigned char volatile&>() +=  instanceof<type nodecay>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() +=  instanceof<type nodecay>()) evaluation = (value +=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() +=  instanceof<type nodecay>())>(evaluation); }
      template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          -=  instanceof<type nodecay>())                    (operator -= )(std::byte&          byte, type nodecay object) exceptspec(exceptof(instanceof<unsigned char&>()          -=  instanceof<type nodecay>()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          -=  instanceof<type nodecay>()) evaluation = (value -=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          -=  instanceof<type nodecay>())>(evaluation); }
      template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() -=  instanceof<type nodecay>())                    (operator -= )(std::byte volatile& byte, type nodecay object) exceptspec(exceptof(instanceof<unsigned char volatile&>() -=  instanceof<type nodecay>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() -=  instanceof<type nodecay>()) evaluation = (value -=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() -=  instanceof<type nodecay>())>(evaluation); }
      template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          *=  instanceof<type nodecay>())                    (operator *= )(std::byte&          byte, type nodecay object) exceptspec(exceptof(instanceof<unsigned char&>()          *=  instanceof<type nodecay>()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          *=  instanceof<type nodecay>()) evaluation = (value *=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          *=  instanceof<type nodecay>())>(evaluation); }
      template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() *=  instanceof<type nodecay>())                    (operator *= )(std::byte volatile& byte, type nodecay object) exceptspec(exceptof(instanceof<unsigned char volatile&>() *=  instanceof<type nodecay>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() *=  instanceof<type nodecay>()) evaluation = (value *=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() *=  instanceof<type nodecay>())>(evaluation); }
      template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          /=  instanceof<type nodecay>())                    (operator /= )(std::byte&          byte, type nodecay object) exceptspec(exceptof(instanceof<unsigned char&>()          /=  instanceof<type nodecay>()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          /=  instanceof<type nodecay>()) evaluation = (value /=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          /=  instanceof<type nodecay>())>(evaluation); }
      template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() /=  instanceof<type nodecay>())                    (operator /= )(std::byte volatile& byte, type nodecay object) exceptspec(exceptof(instanceof<unsigned char volatile&>() /=  instanceof<type nodecay>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() /=  instanceof<type nodecay>()) evaluation = (value /=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() /=  instanceof<type nodecay>())>(evaluation); }
      template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          %=  instanceof<type nodecay>())                    (operator %= )(std::byte&          byte, type nodecay object) exceptspec(exceptof(instanceof<unsigned char&>()          %=  instanceof<type nodecay>()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          %=  instanceof<type nodecay>()) evaluation = (value %=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          %=  instanceof<type nodecay>())>(evaluation); }
      template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() %=  instanceof<type nodecay>())                    (operator %= )(std::byte volatile& byte, type nodecay object) exceptspec(exceptof(instanceof<unsigned char volatile&>() %=  instanceof<type nodecay>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() %=  instanceof<type nodecay>()) evaluation = (value %=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() %=  instanceof<type nodecay>())>(evaluation); }
      template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() &=  instanceof<type nodecay>())                    (operator &= )(std::byte volatile& byte, type nodecay object) exceptspec(exceptof(instanceof<unsigned char volatile&>() &=  instanceof<type nodecay>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() &=  instanceof<type nodecay>()) evaluation = (value &=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() &=  instanceof<type nodecay>())>(evaluation); }
      template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() |=  instanceof<type nodecay>())                    (operator |= )(std::byte volatile& byte, type nodecay object) exceptspec(exceptof(instanceof<unsigned char volatile&>() |=  instanceof<type nodecay>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() |=  instanceof<type nodecay>()) evaluation = (value |=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() |=  instanceof<type nodecay>())>(evaluation); }
      template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() ^=  instanceof<type nodecay>())                    (operator ^= )(std::byte volatile& byte, type nodecay object) exceptspec(exceptof(instanceof<unsigned char volatile&>() ^=  instanceof<type nodecay>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() ^=  instanceof<type nodecay>()) evaluation = (value ^=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() ^=  instanceof<type nodecay>())>(evaluation); }
      template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() <<= instanceof<type nodecay>())                    (operator <<=)(std::byte volatile& byte, type nodecay object) exceptspec(exceptof(instanceof<unsigned char volatile&>() <<= instanceof<type nodecay>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() <<= instanceof<type nodecay>()) evaluation = (value <<= pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() <<= instanceof<type nodecay>())>(evaluation); }
      template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() >>= instanceof<type nodecay>())                    (operator >>=)(std::byte volatile& byte, type nodecay object) exceptspec(exceptof(instanceof<unsigned char volatile&>() >>= instanceof<type nodecay>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() >>= instanceof<type nodecay>()) evaluation = (value >>= pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() >>= instanceof<type nodecay>())>(evaluation); }
      template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) == instanceof<type nodecay>())) (operator == )(std::byte const     byte, type nodecay object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) == instanceof<type nodecay>())) { return std::to_integer<unsigned char>(byte) == pass<type>(object); }
      template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) != instanceof<type nodecay>())) (operator != )(std::byte const     byte, type nodecay object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) != instanceof<type nodecay>())) { return std::to_integer<unsigned char>(byte) != pass<type>(object); }
      template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) <  instanceof<type nodecay>())) (operator <  )(std::byte const     byte, type nodecay object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) <  instanceof<type nodecay>())) { return std::to_integer<unsigned char>(byte) <  pass<type>(object); }
      template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) >  instanceof<type nodecay>())) (operator >  )(std::byte const     byte, type nodecay object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) >  instanceof<type nodecay>())) { return std::to_integer<unsigned char>(byte) >  pass<type>(object); }
      template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) <= instanceof<type nodecay>())) (operator <= )(std::byte const     byte, type nodecay object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) <= instanceof<type nodecay>())) { return std::to_integer<unsigned char>(byte) <= pass<type>(object); }
      template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) >= instanceof<type nodecay>())) (operator >= )(std::byte const     byte, type nodecay object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) >= instanceof<type nodecay>())) { return std::to_integer<unsigned char>(byte) >= pass<type>(object); }

      #if defined(__cpp_impl_three_way_comparison) or defined(__cpp_lib_three_way_comparison) // --> 201907L
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) <=> instanceof<type nodecay>())) (operator <=>)(std::byte const byte, type nodecay object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) <=> instanceof<type nodecay>())) { return std::to_integer<unsigned char>(byte) <=> pass<type>(object); }
      #endif

      #if CPP_VERSION < 2011uL
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          +=  instanceof<type&>               ())                    (operator += )(std::byte&          byte, type&                object) exceptspec(exceptof(instanceof<unsigned char&>()          +=  instanceof<type&>               ()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          +=  instanceof<type&>               ()) evaluation = (value +=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          +=  instanceof<type&>               ())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          +=  instanceof<type       volatile&>())                    (operator += )(std::byte&          byte, type       volatile& object) exceptspec(exceptof(instanceof<unsigned char&>()          +=  instanceof<type       volatile&>()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          +=  instanceof<type       volatile&>()) evaluation = (value +=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          +=  instanceof<type       volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          +=  instanceof<type const volatile&>())                    (operator += )(std::byte&          byte, type const volatile& object) exceptspec(exceptof(instanceof<unsigned char&>()          +=  instanceof<type const volatile&>()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          +=  instanceof<type const volatile&>()) evaluation = (value +=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          +=  instanceof<type const volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() +=  instanceof<type&>               ())                    (operator += )(std::byte volatile& byte, type&                object) exceptspec(exceptof(instanceof<unsigned char volatile&>() +=  instanceof<type&>               ()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() +=  instanceof<type&>               ()) evaluation = (value +=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() +=  instanceof<type&>               ())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() +=  instanceof<type       volatile&>())                    (operator += )(std::byte volatile& byte, type       volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() +=  instanceof<type       volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() +=  instanceof<type       volatile&>()) evaluation = (value +=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() +=  instanceof<type       volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() +=  instanceof<type const volatile&>())                    (operator += )(std::byte volatile& byte, type const volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() +=  instanceof<type const volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() +=  instanceof<type const volatile&>()) evaluation = (value +=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() +=  instanceof<type const volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          -=  instanceof<type&>               ())                    (operator -= )(std::byte&          byte, type&                object) exceptspec(exceptof(instanceof<unsigned char&>()          -=  instanceof<type&>               ()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          -=  instanceof<type&>               ()) evaluation = (value -=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          -=  instanceof<type&>               ())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          -=  instanceof<type       volatile&>())                    (operator -= )(std::byte&          byte, type       volatile& object) exceptspec(exceptof(instanceof<unsigned char&>()          -=  instanceof<type       volatile&>()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          -=  instanceof<type       volatile&>()) evaluation = (value -=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          -=  instanceof<type       volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          -=  instanceof<type const volatile&>())                    (operator -= )(std::byte&          byte, type const volatile& object) exceptspec(exceptof(instanceof<unsigned char&>()          -=  instanceof<type const volatile&>()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          -=  instanceof<type const volatile&>()) evaluation = (value -=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          -=  instanceof<type const volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() -=  instanceof<type&>               ())                    (operator -= )(std::byte volatile& byte, type&                object) exceptspec(exceptof(instanceof<unsigned char volatile&>() -=  instanceof<type&>               ()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() -=  instanceof<type&>               ()) evaluation = (value -=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() -=  instanceof<type&>               ())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() -=  instanceof<type       volatile&>())                    (operator -= )(std::byte volatile& byte, type       volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() -=  instanceof<type       volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() -=  instanceof<type       volatile&>()) evaluation = (value -=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() -=  instanceof<type       volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() -=  instanceof<type const volatile&>())                    (operator -= )(std::byte volatile& byte, type const volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() -=  instanceof<type const volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() -=  instanceof<type const volatile&>()) evaluation = (value -=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() -=  instanceof<type const volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          *=  instanceof<type&>               ())                    (operator *= )(std::byte&          byte, type&                object) exceptspec(exceptof(instanceof<unsigned char&>()          *=  instanceof<type&>               ()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          *=  instanceof<type&>               ()) evaluation = (value *=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          *=  instanceof<type&>               ())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          *=  instanceof<type       volatile&>())                    (operator *= )(std::byte&          byte, type       volatile& object) exceptspec(exceptof(instanceof<unsigned char&>()          *=  instanceof<type       volatile&>()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          *=  instanceof<type       volatile&>()) evaluation = (value *=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          *=  instanceof<type       volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          *=  instanceof<type const volatile&>())                    (operator *= )(std::byte&          byte, type const volatile& object) exceptspec(exceptof(instanceof<unsigned char&>()          *=  instanceof<type const volatile&>()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          *=  instanceof<type const volatile&>()) evaluation = (value *=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          *=  instanceof<type const volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() *=  instanceof<type&>               ())                    (operator *= )(std::byte volatile& byte, type&                object) exceptspec(exceptof(instanceof<unsigned char volatile&>() *=  instanceof<type&>               ()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() *=  instanceof<type&>               ()) evaluation = (value *=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() *=  instanceof<type&>               ())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() *=  instanceof<type       volatile&>())                    (operator *= )(std::byte volatile& byte, type       volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() *=  instanceof<type       volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() *=  instanceof<type       volatile&>()) evaluation = (value *=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() *=  instanceof<type       volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() *=  instanceof<type const volatile&>())                    (operator *= )(std::byte volatile& byte, type const volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() *=  instanceof<type const volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() *=  instanceof<type const volatile&>()) evaluation = (value *=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() *=  instanceof<type const volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          /=  instanceof<type&>               ())                    (operator /= )(std::byte&          byte, type&                object) exceptspec(exceptof(instanceof<unsigned char&>()          /=  instanceof<type&>               ()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          /=  instanceof<type&>               ()) evaluation = (value /=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          /=  instanceof<type&>               ())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          /=  instanceof<type       volatile&>())                    (operator /= )(std::byte&          byte, type       volatile& object) exceptspec(exceptof(instanceof<unsigned char&>()          /=  instanceof<type       volatile&>()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          /=  instanceof<type       volatile&>()) evaluation = (value /=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          /=  instanceof<type       volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          /=  instanceof<type const volatile&>())                    (operator /= )(std::byte&          byte, type const volatile& object) exceptspec(exceptof(instanceof<unsigned char&>()          /=  instanceof<type const volatile&>()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          /=  instanceof<type const volatile&>()) evaluation = (value /=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          /=  instanceof<type const volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() /=  instanceof<type&>               ())                    (operator /= )(std::byte volatile& byte, type&                object) exceptspec(exceptof(instanceof<unsigned char volatile&>() /=  instanceof<type&>               ()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() /=  instanceof<type&>               ()) evaluation = (value /=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() /=  instanceof<type&>               ())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() /=  instanceof<type       volatile&>())                    (operator /= )(std::byte volatile& byte, type       volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() /=  instanceof<type       volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() /=  instanceof<type       volatile&>()) evaluation = (value /=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() /=  instanceof<type       volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() /=  instanceof<type const volatile&>())                    (operator /= )(std::byte volatile& byte, type const volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() /=  instanceof<type const volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() /=  instanceof<type const volatile&>()) evaluation = (value /=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() /=  instanceof<type const volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          %=  instanceof<type&>               ())                    (operator %= )(std::byte&          byte, type&                object) exceptspec(exceptof(instanceof<unsigned char&>()          %=  instanceof<type&>               ()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          %=  instanceof<type&>               ()) evaluation = (value %=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          %=  instanceof<type&>               ())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          %=  instanceof<type       volatile&>())                    (operator %= )(std::byte&          byte, type       volatile& object) exceptspec(exceptof(instanceof<unsigned char&>()          %=  instanceof<type       volatile&>()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          %=  instanceof<type       volatile&>()) evaluation = (value %=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          %=  instanceof<type       volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char&>()          %=  instanceof<type const volatile&>())                    (operator %= )(std::byte&          byte, type const volatile& object) exceptspec(exceptof(instanceof<unsigned char&>()          %=  instanceof<type const volatile&>()))                  { unsigned char          value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char&>()          %=  instanceof<type const volatile&>()) evaluation = (value %=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char&>()          %=  instanceof<type const volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() %=  instanceof<type&>               ())                    (operator %= )(std::byte volatile& byte, type&                object) exceptspec(exceptof(instanceof<unsigned char volatile&>() %=  instanceof<type&>               ()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() %=  instanceof<type&>               ()) evaluation = (value %=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() %=  instanceof<type&>               ())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() %=  instanceof<type       volatile&>())                    (operator %= )(std::byte volatile& byte, type       volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() %=  instanceof<type       volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() %=  instanceof<type       volatile&>()) evaluation = (value %=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() %=  instanceof<type       volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() %=  instanceof<type const volatile&>())                    (operator %= )(std::byte volatile& byte, type const volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() %=  instanceof<type const volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() %=  instanceof<type const volatile&>()) evaluation = (value %=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() %=  instanceof<type const volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() &=  instanceof<type&>               ())                    (operator &= )(std::byte volatile& byte, type&                object) exceptspec(exceptof(instanceof<unsigned char volatile&>() &=  instanceof<type&>               ()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() &=  instanceof<type&>               ()) evaluation = (value &=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() &=  instanceof<type&>               ())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() &=  instanceof<type       volatile&>())                    (operator &= )(std::byte volatile& byte, type       volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() &=  instanceof<type       volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() &=  instanceof<type       volatile&>()) evaluation = (value &=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() &=  instanceof<type       volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() &=  instanceof<type const volatile&>())                    (operator &= )(std::byte volatile& byte, type const volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() &=  instanceof<type const volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() &=  instanceof<type const volatile&>()) evaluation = (value &=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() &=  instanceof<type const volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() |=  instanceof<type&>               ())                    (operator |= )(std::byte volatile& byte, type&                object) exceptspec(exceptof(instanceof<unsigned char volatile&>() |=  instanceof<type&>               ()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() |=  instanceof<type&>               ()) evaluation = (value |=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() |=  instanceof<type&>               ())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() |=  instanceof<type       volatile&>())                    (operator |= )(std::byte volatile& byte, type       volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() |=  instanceof<type       volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() |=  instanceof<type       volatile&>()) evaluation = (value |=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() |=  instanceof<type       volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() |=  instanceof<type const volatile&>())                    (operator |= )(std::byte volatile& byte, type const volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() |=  instanceof<type const volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() |=  instanceof<type const volatile&>()) evaluation = (value |=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() |=  instanceof<type const volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() ^=  instanceof<type&>               ())                    (operator ^= )(std::byte volatile& byte, type&                object) exceptspec(exceptof(instanceof<unsigned char volatile&>() ^=  instanceof<type&>               ()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() ^=  instanceof<type&>               ()) evaluation = (value ^=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() ^=  instanceof<type&>               ())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() ^=  instanceof<type       volatile&>())                    (operator ^= )(std::byte volatile& byte, type       volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() ^=  instanceof<type       volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() ^=  instanceof<type       volatile&>()) evaluation = (value ^=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() ^=  instanceof<type       volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() ^=  instanceof<type const volatile&>())                    (operator ^= )(std::byte volatile& byte, type const volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() ^=  instanceof<type const volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() ^=  instanceof<type const volatile&>()) evaluation = (value ^=  pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() ^=  instanceof<type const volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() <<= instanceof<type&>               ())                    (operator <<=)(std::byte volatile& byte, type&                object) exceptspec(exceptof(instanceof<unsigned char volatile&>() <<= instanceof<type&>               ()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() <<= instanceof<type&>               ()) evaluation = (value <<= pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() <<= instanceof<type&>               ())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() <<= instanceof<type       volatile&>())                    (operator <<=)(std::byte volatile& byte, type       volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() <<= instanceof<type       volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() <<= instanceof<type       volatile&>()) evaluation = (value <<= pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() <<= instanceof<type       volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() <<= instanceof<type const volatile&>())                    (operator <<=)(std::byte volatile& byte, type const volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() <<= instanceof<type const volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() <<= instanceof<type const volatile&>()) evaluation = (value <<= pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() <<= instanceof<type const volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() >>= instanceof<type&>               ())                    (operator >>=)(std::byte volatile& byte, type&                object) exceptspec(exceptof(instanceof<unsigned char volatile&>() >>= instanceof<type&>               ()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() >>= instanceof<type&>               ()) evaluation = (value >>= pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() >>= instanceof<type&>               ())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() >>= instanceof<type       volatile&>())                    (operator >>=)(std::byte volatile& byte, type       volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() >>= instanceof<type       volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() >>= instanceof<type       volatile&>()) evaluation = (value >>= pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() >>= instanceof<type       volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof(instanceof<unsigned char volatile&>() >>= instanceof<type const volatile&>())                    (operator >>=)(std::byte volatile& byte, type const volatile& object) exceptspec(exceptof(instanceof<unsigned char volatile&>() >>= instanceof<type const volatile&>()))                  { unsigned char volatile value = std::to_integer<unsigned char>(byte); typeof(instanceof<unsigned char volatile&>() >>= instanceof<type const volatile&>()) evaluation = (value >>= pass<type>(object)); byte = static_cast<std::byte>(value); return static_cast<typeof(instanceof<unsigned char volatile&>() >>= instanceof<type const volatile&>())>(evaluation); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) == instanceof<type&>               ())) (operator == )(std::byte const     byte, type&                object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) == instanceof<type&>               ())) { return std::to_integer<unsigned char>(byte) == pass<type>(object); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) == instanceof<type       volatile&>())) (operator == )(std::byte const     byte, type       volatile& object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) == instanceof<type       volatile&>())) { return std::to_integer<unsigned char>(byte) == pass<type>(object); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) == instanceof<type const volatile&>())) (operator == )(std::byte const     byte, type const volatile& object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) == instanceof<type const volatile&>())) { return std::to_integer<unsigned char>(byte) == pass<type>(object); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) != instanceof<type&>               ())) (operator != )(std::byte const     byte, type&                object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) != instanceof<type&>               ())) { return std::to_integer<unsigned char>(byte) != pass<type>(object); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) != instanceof<type       volatile&>())) (operator != )(std::byte const     byte, type       volatile& object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) != instanceof<type       volatile&>())) { return std::to_integer<unsigned char>(byte) != pass<type>(object); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) != instanceof<type const volatile&>())) (operator != )(std::byte const     byte, type const volatile& object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) != instanceof<type const volatile&>())) { return std::to_integer<unsigned char>(byte) != pass<type>(object); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) <  instanceof<type&>               ())) (operator <  )(std::byte const     byte, type&                object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) <  instanceof<type&>               ())) { return std::to_integer<unsigned char>(byte) <  pass<type>(object); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) <  instanceof<type       volatile&>())) (operator <  )(std::byte const     byte, type       volatile& object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) <  instanceof<type       volatile&>())) { return std::to_integer<unsigned char>(byte) <  pass<type>(object); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) <  instanceof<type const volatile&>())) (operator <  )(std::byte const     byte, type const volatile& object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) <  instanceof<type const volatile&>())) { return std::to_integer<unsigned char>(byte) <  pass<type>(object); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) >  instanceof<type&>               ())) (operator >  )(std::byte const     byte, type&                object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) >  instanceof<type&>               ())) { return std::to_integer<unsigned char>(byte) >  pass<type>(object); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) >  instanceof<type       volatile&>())) (operator >  )(std::byte const     byte, type       volatile& object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) >  instanceof<type       volatile&>())) { return std::to_integer<unsigned char>(byte) >  pass<type>(object); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) >  instanceof<type const volatile&>())) (operator >  )(std::byte const     byte, type const volatile& object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) >  instanceof<type const volatile&>())) { return std::to_integer<unsigned char>(byte) >  pass<type>(object); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) <= instanceof<type&>               ())) (operator <= )(std::byte const     byte, type&                object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) <= instanceof<type&>               ())) { return std::to_integer<unsigned char>(byte) <= pass<type>(object); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) <= instanceof<type       volatile&>())) (operator <= )(std::byte const     byte, type       volatile& object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) <= instanceof<type       volatile&>())) { return std::to_integer<unsigned char>(byte) <= pass<type>(object); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) <= instanceof<type const volatile&>())) (operator <= )(std::byte const     byte, type const volatile& object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) <= instanceof<type const volatile&>())) { return std::to_integer<unsigned char>(byte) <= pass<type>(object); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) >= instanceof<type&>               ())) (operator >= )(std::byte const     byte, type&                object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) >= instanceof<type&>               ())) { return std::to_integer<unsigned char>(byte) >= pass<type>(object); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) >= instanceof<type       volatile&>())) (operator >= )(std::byte const     byte, type       volatile& object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) >= instanceof<type       volatile&>())) { return std::to_integer<unsigned char>(byte) >= pass<type>(object); }
        template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) >= instanceof<type const volatile&>())) (operator >= )(std::byte const     byte, type const volatile& object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) >= instanceof<type const volatile&>())) { return std::to_integer<unsigned char>(byte) >= pass<type>(object); }

        #if defined(__cpp_impl_three_way_comparison) or defined(__cpp_lib_three_way_comparison) // --> 201907L
          template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) <=> instanceof<type&>               ())) (operator <=>)(std::byte const byte, type&                object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) <=> instanceof<type&>               ())) { return std::to_integer<unsigned char>(byte) <=> pass<type>(object); }
          template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) <=> instanceof<type       volatile&>())) (operator <=>)(std::byte const byte, type       volatile& object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) <=> instanceof<type       volatile&>())) { return std::to_integer<unsigned char>(byte) <=> pass<type>(object); }
          template <typename type> constfunc(false) mustinline typeof((std::to_integer<unsigned char>(instanceof<std::byte>()) <=> instanceof<type const volatile&>())) (operator <=>)(std::byte const byte, type const volatile& object) exceptspec(exceptof(std::to_integer<unsigned char>(instanceof<std::byte>()) <=> instanceof<type const volatile&>())) { return std::to_integer<unsigned char>(byte) <=> pass<type>(object); }
        #endif
      #endif
    #endif

    // ...
    typedef unsigned long uintmax_template_t;

    /* Trait */
    // Null ->> Specialization type denoting an "empty set of values"; See `void` type
    typedef union empty &null;

    // SFINAE Pointer ->> Specialization-only type
    #if CPP_VERSION < 2011uL
      #define sfinaeptr sfinaeptr
      enum sfinaeptr_t /* : unsigned char */ { sfinaeptr /* = 0x00hhu */ };
    #else
      #define sfinaeptr nullptr
      typedef std::nullptr_t sfinaeptr_t;
    #endif

    /* Namespace */
    namespace Traits {
      /* Alias > Boolean (False, True) */
      typedef bool nodecayparam(boolean_false)[false + 1u];
      typedef bool nodecayparam(boolean_true) [true  + 1u];

      /* Trait > ... ->> Not all traits are neatly declarable without their definition */
      struct defer;
      struct enumtypeinfo;
      struct opinfo;

      template <typename>                               struct alias;
      template <typename, bool = false>                 struct classinfo;
      template <bool, typename = null, typename = null> struct conditional;
      template <typename base, base, bool>              struct constant;
      template <typename>                               struct enuminfo;
      template <std::size_t>                            struct float_fast_t;
      template <std::size_t>                            struct float_fast_width_t;
      template <std::size_t>                            struct float_least_t;
      template <std::size_t>                            struct float_least_width_t;
      template <std::size_t>                            struct float_t;
      template <std::size_t>                            struct float_width_t;
      template <typename>                               struct functioninfo;
      template <std::size_t>                            struct int_fast_t;
      template <std::size_t>                            struct int_fast_width_t;
      template <std::size_t>                            struct int_least_t;
      template <std::size_t>                            struct int_least_width_t;
      template <std::size_t>                            struct int_t;
      template <std::size_t>                            struct int_width_t;
      template <typename>                               struct is_class;
      template <typename>                               struct is_const;
      template <typename>                               struct is_enum;
      template <typename>                               struct is_final;
      template <typename>                               struct is_function;
      template <typename, bool = false>                 struct is_integer;
      template <typename>                               struct is_null;
      template <typename, typename>                     struct is_same;
      template <typename>                               struct is_signed;
      template <typename>                               struct is_similar;
      template <typename>                               struct is_union;
      template <typename>                               struct is_unsigned;
      template <typename>                               struct is_volatile;
      template <typename>                               struct maxof;
      template <typename>                               struct minof;
      template <typename>                               struct nilof;
      template <typename>                               struct remove_const;
      template <typename>                               struct remove_const_volatile;
      template <typename>                               struct remove_volatile;
      template <typename>                               struct signedof;
      template <std::size_t>                            struct uint_fast_t;
      template <std::size_t>                            struct uint_fast_width_t;
      template <std::size_t>                            struct uint_least_t;
      template <std::size_t>                            struct uint_least_width_t;
      template <std::size_t>                            struct uint_t;
      template <std::size_t>                            struct uint_width_t;
      template <typename>                               struct unsignedof;

      #ifdef __cpp_variadic_templates // --> 200704L
        template <bool, bool...> struct boolean_and;
        template <bool, bool...> struct boolean_or;
        template <typename...>   struct collection;
      #else
        template <bool, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true>                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    struct boolean_and;
        template <bool, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true, bool = true>                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    struct boolean_or;
        template <typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null, typename = null> struct collection;
      #endif
    }

    /* ... */
    using namespace Traits;
  }

  namespace Lapys {
    /* Namespace */
    namespace Traits {
      /* Trait */
      // ... ->> Aliases specified type (plain and simple)
      template <typename base>
      struct alias final {
        typedef base type;
      };

      // ... ->> Class type diagnostics
      template <typename base, bool fallback>
      struct classinfo final {
        private:
          // ... ->> Evaluates if type is a union type
          template <typename subbase, bool subfallback = false>
          struct unionof final {
            private:
              template <typename type>
              constfunc(false) static boolean_true (valueof)(sfinaeptr_t const, byte type::* const = NULL) noexcept;

              template <typename>
              constfunc(false) static boolean_false (valueof)(...) noexcept;

            public:
              static bool const value =
                #if CPP_VERSION >= 2011uL
                  std::is_union<subbase>::value or
                #elif CPP_COMPILER == CPP_CIRCLE_COMPILER or CPP_COMPILER == CPP_CLANG_COMPILER or CPP_COMPILER == CPP_GNUC_COMPILER or CPP_COMPILER == CPP_INTEL_COMPILER or CPP_COMPILER == CPP_LLVM_COMPILER or CPP_COMPILER == CPP_NVCC_COMPILER
                # ifdef __has_builtin // --> `__is_union(...)` may still exist otherwise
                #   if __has_builtin(__is_union)
                      __is_union(subbase) or
                #   endif
                # endif
                #elif CPP_COMPILER == CPP_MSVC_COMPILER
                  __is_union(subbase) or
                #endif
              sizeof(boolean_true) == sizeof(valueof<subbase>(sfinaeptr)) or
              subfallback;
          };

          // ... ->> Evaluates if type is a class or union type
          template <typename subbase>
          struct valueof final {
            static bool const value =
              #if CPP_VERSION >= 2011uL
                std::is_class<subbase>::value or
              #elif CPP_COMPILER == CPP_MSVC_COMPILER
                __is_class(subbase) or
              #elif CPP_COMPILER == CPP_CIRCLE_COMPILER or CPP_COMPILER == CPP_CLANG_COMPILER or CPP_COMPILER == CPP_GNUC_COMPILER or CPP_COMPILER == CPP_INTEL_COMPILER or CPP_COMPILER == CPP_LLVM_COMPILER or CPP_COMPILER == CPP_NVCC_COMPILER
              # ifdef __has_builtin // --> `__is_class(...)` may still exist otherwise
              #   if __has_builtin(__is_class)
                    __is_class(subbase) or
              #   endif
              # endif
              #endif
            unionof<subbase, fallback>::value;
          };

          // ... ->> Evaluates if class type is specified `final`; Union types always evaluate falsy
          template <typename subbase, bool = valueof<subbase>::value>
          struct finalof final {
            static bool const value = false;
          };

          template <typename subbase>
          struct finalof<subbase, true> final {
            static bool const value =
              #if CPP_VERSION >= 2014uL
                std::is_final<subbase>::value and
              #elif CPP_VERSION >= 2011uL
              # if CPP_COMPILER == CPP_CIRCLE_COMPILER or CPP_COMPILER == CPP_CLANG_COMPILER or CPP_COMPILER == CPP_GNUC_COMPILER or CPP_COMPILER == CPP_INTEL_COMPILER or CPP_COMPILER == CPP_LLVM_COMPILER or CPP_COMPILER == CPP_NVCC_COMPILER
              #   ifdef __has_builtin // --> `__is_final(...)` may still exist otherwise
              #     if __has_builtin(__is_final)
                      __is_final(subbase) and
              #     endif
              #   endif
              # elif CPP_COMPILER == CPP_MSVC_COMPILER
                  __is_sealed(subbase) and
              # endif
              #endif
            false;
          };

        public:
          static bool const derivable = not finalof<base>::value and not unionof<base>::value;
          static bool const value     = valueof<base>::value;
          static bool const variant   = unionof<base>::value;
      };

      // ... ->> Aliases dependent type based on (boolean) condition
      template <typename baseA, typename baseB>
      struct conditional<false, baseA, baseB> final {
        typedef baseB type;
      };

      template <typename base>
      struct conditional<false, base, null> final {};

      template <typename baseA, typename baseB>
      struct conditional<true, baseA, baseB> final {
        typedef baseA type;
      };

      template <typename base>
      struct conditional<true, null, base> final {};

      // ... ->> Dummy type for overarching evaluation eg: `sizeof defer::type<T>` instead of `sizeof T` for incomplete type `T`
      struct defer final {
        template <typename base, base>
        struct constant final {};

        // ...
        template <typename>
        struct type final {};
      };

      // ... ->> Collection of types
      #ifdef __cpp_variadic_templates // --> 200704L
        template <typename...>
        struct collection final {};
      #else
        template <typename base1u, typename base2u, typename base3u, typename base4u, typename base5u, typename base6u, typename base7u, typename base8u, typename base9u, typename base10u, typename base11u, typename base12u, typename base13u, typename base14u, typename base15u, typename base16u, typename base17u, typename base18u, typename base19u, typename base20u, typename base21u, typename base22u, typename base23u, typename base24u, typename base25u, typename base26u, typename base27u, typename base28u, typename base29u, typename base30u, typename base31u, typename base32u, typename base33u, typename base34u, typename base35u, typename base36u, typename base37u, typename base38u, typename base39u, typename base40u, typename base41u, typename base42u, typename base43u, typename base44u, typename base45u, typename base46u, typename base47u, typename base48u, typename base49u, typename base50u, typename base51u, typename base52u, typename base53u, typename base54u, typename base55u, typename base56u, typename base57u, typename base58u, typename base59u, typename base60u, typename base61u, typename base62u, typename base63u, typename base64u, typename base65u, typename base66u, typename base67u, typename base68u, typename base69u, typename base70u, typename base71u, typename base72u, typename base73u, typename base74u, typename base75u, typename base76u, typename base77u, typename base78u, typename base79u, typename base80u, typename base81u, typename base82u, typename base83u, typename base84u, typename base85u, typename base86u, typename base87u, typename base88u, typename base89u, typename base90u, typename base91u, typename base92u, typename base93u, typename base94u, typename base95u, typename base96u, typename base97u, typename base98u, typename base99u, typename base100u, typename base101u, typename base102u, typename base103u, typename base104u, typename base105u, typename base106u, typename base107u, typename base108u, typename base109u, typename base110u, typename base111u, typename base112u, typename base113u, typename base114u, typename base115u, typename base116u, typename base117u, typename base118u, typename base119u, typename base120u, typename base121u, typename base122u, typename base123u, typename base124u, typename base125u, typename base126u, typename base127u>
        struct collection final {
          template <typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename>
          friend struct collection;

          static std::size_t const length  = not is_null<base1u>::value + not is_null<base2u>::value + not is_null<base3u>::value + not is_null<base4u>::value + not is_null<base5u>::value + not is_null<base6u>::value + not is_null<base7u>::value + not is_null<base8u>::value + not is_null<base9u>::value + not is_null<base10u>::value + not is_null<base11u>::value + not is_null<base12u>::value + not is_null<base13u>::value + not is_null<base14u>::value + not is_null<base15u>::value + not is_null<base16u>::value + not is_null<base17u>::value + not is_null<base18u>::value + not is_null<base19u>::value + not is_null<base20u>::value + not is_null<base21u>::value + not is_null<base22u>::value + not is_null<base23u>::value + not is_null<base24u>::value + not is_null<base25u>::value + not is_null<base26u>::value + not is_null<base27u>::value + not is_null<base28u>::value + not is_null<base29u>::value + not is_null<base30u>::value + not is_null<base31u>::value + not is_null<base32u>::value + not is_null<base33u>::value + not is_null<base34u>::value + not is_null<base35u>::value + not is_null<base36u>::value + not is_null<base37u>::value + not is_null<base38u>::value + not is_null<base39u>::value + not is_null<base40u>::value + not is_null<base41u>::value + not is_null<base42u>::value + not is_null<base43u>::value + not is_null<base44u>::value + not is_null<base45u>::value + not is_null<base46u>::value + not is_null<base47u>::value + not is_null<base48u>::value + not is_null<base49u>::value + not is_null<base50u>::value + not is_null<base51u>::value + not is_null<base52u>::value + not is_null<base53u>::value + not is_null<base54u>::value + not is_null<base55u>::value + not is_null<base56u>::value + not is_null<base57u>::value + not is_null<base58u>::value + not is_null<base59u>::value + not is_null<base60u>::value + not is_null<base61u>::value + not is_null<base62u>::value + not is_null<base63u>::value + not is_null<base64u>::value + not is_null<base65u>::value + not is_null<base66u>::value + not is_null<base67u>::value + not is_null<base68u>::value + not is_null<base69u>::value + not is_null<base70u>::value + not is_null<base71u>::value + not is_null<base72u>::value + not is_null<base73u>::value + not is_null<base74u>::value + not is_null<base75u>::value + not is_null<base76u>::value + not is_null<base77u>::value + not is_null<base78u>::value + not is_null<base79u>::value + not is_null<base80u>::value + not is_null<base81u>::value + not is_null<base82u>::value + not is_null<base83u>::value + not is_null<base84u>::value + not is_null<base85u>::value + not is_null<base86u>::value + not is_null<base87u>::value + not is_null<base88u>::value + not is_null<base89u>::value + not is_null<base90u>::value + not is_null<base91u>::value + not is_null<base92u>::value + not is_null<base93u>::value + not is_null<base94u>::value + not is_null<base95u>::value + not is_null<base96u>::value + not is_null<base97u>::value + not is_null<base98u>::value + not is_null<base99u>::value + not is_null<base100u>::value + not is_null<base101u>::value + not is_null<base102u>::value + not is_null<base103u>::value + not is_null<base104u>::value + not is_null<base105u>::value + not is_null<base106u>::value + not is_null<base107u>::value + not is_null<base108u>::value + not is_null<base109u>::value + not is_null<base110u>::value + not is_null<base111u>::value + not is_null<base112u>::value + not is_null<base113u>::value + not is_null<base114u>::value + not is_null<base115u>::value + not is_null<base116u>::value + not is_null<base117u>::value + not is_null<base118u>::value + not is_null<base119u>::value + not is_null<base120u>::value + not is_null<base121u>::value + not is_null<base122u>::value + not is_null<base123u>::value + not is_null<base124u>::value + not is_null<base125u>::value + not is_null<base126u>::value + not is_null<base127u>::value;
          static std::size_t const maximum = 127u;

          private:
            template <std::size_t count, sfinaeptr_t = sfinaeptr>
            struct _slice final {
              typedef typename collection<base2u, base3u, base4u, base5u, base6u, base7u, base8u, base9u, base10u, base11u, base12u, base13u, base14u, base15u, base16u, base17u, base18u, base19u, base20u, base21u, base22u, base23u, base24u, base25u, base26u, base27u, base28u, base29u, base30u, base31u, base32u, base33u, base34u, base35u, base36u, base37u, base38u, base39u, base40u, base41u, base42u, base43u, base44u, base45u, base46u, base47u, base48u, base49u, base50u, base51u, base52u, base53u, base54u, base55u, base56u, base57u, base58u, base59u, base60u, base61u, base62u, base63u, base64u, base65u, base66u, base67u, base68u, base69u, base70u, base71u, base72u, base73u, base74u, base75u, base76u, base77u, base78u, base79u, base80u, base81u, base82u, base83u, base84u, base85u, base86u, base87u, base88u, base89u, base90u, base91u, base92u, base93u, base94u, base95u, base96u, base97u, base98u, base99u, base100u, base101u, base102u, base103u, base104u, base105u, base106u, base107u, base108u, base109u, base110u, base111u, base112u, base113u, base114u, base115u, base116u, base117u, base118u, base119u, base120u, base121u, base122u, base123u, base124u, base125u, base126u, base127u>::template _slice<count - 1u>::type type;
            };

            template <sfinaeptr_t sfinae>
            struct _slice<0u, sfinae> final {
              typedef collection<base1u, base2u, base3u, base4u, base5u, base6u, base7u, base8u, base9u, base10u, base11u, base12u, base13u, base14u, base15u, base16u, base17u, base18u, base19u, base20u, base21u, base22u, base23u, base24u, base25u, base26u, base27u, base28u, base29u, base30u, base31u, base32u, base33u, base34u, base35u, base36u, base37u, base38u, base39u, base40u, base41u, base42u, base43u, base44u, base45u, base46u, base47u, base48u, base49u, base50u, base51u, base52u, base53u, base54u, base55u, base56u, base57u, base58u, base59u, base60u, base61u, base62u, base63u, base64u, base65u, base66u, base67u, base68u, base69u, base70u, base71u, base72u, base73u, base74u, base75u, base76u, base77u, base78u, base79u, base80u, base81u, base82u, base83u, base84u, base85u, base86u, base87u, base88u, base89u, base90u, base91u, base92u, base93u, base94u, base95u, base96u, base97u, base98u, base99u, base100u, base101u, base102u, base103u, base104u, base105u, base106u, base107u, base108u, base109u, base110u, base111u, base112u, base113u, base114u, base115u, base116u, base117u, base118u, base119u, base120u, base121u, base122u, base123u, base124u, base125u, base126u, base127u> type;
            };

            // ...
            template <class subcollection = collection<>, std::size_t = length>
            struct _reverse final {
              typedef typename collection::pop::template _reverse<typename subcollection::template add<typename collection::last>::type>::type type;
            };

            template <class subcollection>
            struct _reverse<subcollection, 0u> final {
              typedef subcollection type;
            };

            // ...
            template <typename base>
            struct _index final {
              static std::size_t const value = is_same<base, base1u>::value ? 0u : is_same<base, base2u>::value ? 1u : is_same<base, base3u>::value ? 2u : is_same<base, base4u>::value ? 3u : is_same<base, base5u>::value ? 4u : is_same<base, base6u>::value ? 5u : is_same<base, base7u>::value ? 6u : is_same<base, base8u>::value ? 7u : is_same<base, base9u>::value ? 8u : is_same<base, base10u>::value ? 9u : is_same<base, base11u>::value ? 10u : is_same<base, base12u>::value ? 11u : is_same<base, base13u>::value ? 12u : is_same<base, base14u>::value ? 13u : is_same<base, base15u>::value ? 14u : is_same<base, base16u>::value ? 15u : is_same<base, base17u>::value ? 16u : is_same<base, base18u>::value ? 17u : is_same<base, base19u>::value ? 18u : is_same<base, base20u>::value ? 19u : is_same<base, base21u>::value ? 20u : is_same<base, base22u>::value ? 21u : is_same<base, base23u>::value ? 22u : is_same<base, base24u>::value ? 23u : is_same<base, base25u>::value ? 24u : is_same<base, base26u>::value ? 25u : is_same<base, base27u>::value ? 26u : is_same<base, base28u>::value ? 27u : is_same<base, base29u>::value ? 28u : is_same<base, base30u>::value ? 29u : is_same<base, base31u>::value ? 30u : is_same<base, base32u>::value ? 31u : is_same<base, base33u>::value ? 32u : is_same<base, base34u>::value ? 33u : is_same<base, base35u>::value ? 34u : is_same<base, base36u>::value ? 35u : is_same<base, base37u>::value ? 36u : is_same<base, base38u>::value ? 37u : is_same<base, base39u>::value ? 38u : is_same<base, base40u>::value ? 39u : is_same<base, base41u>::value ? 40u : is_same<base, base42u>::value ? 41u : is_same<base, base43u>::value ? 42u : is_same<base, base44u>::value ? 43u : is_same<base, base45u>::value ? 44u : is_same<base, base46u>::value ? 45u : is_same<base, base47u>::value ? 46u : is_same<base, base48u>::value ? 47u : is_same<base, base49u>::value ? 48u : is_same<base, base50u>::value ? 49u : is_same<base, base51u>::value ? 50u : is_same<base, base52u>::value ? 51u : is_same<base, base53u>::value ? 52u : is_same<base, base54u>::value ? 53u : is_same<base, base55u>::value ? 54u : is_same<base, base56u>::value ? 55u : is_same<base, base57u>::value ? 56u : is_same<base, base58u>::value ? 57u : is_same<base, base59u>::value ? 58u : is_same<base, base60u>::value ? 59u : is_same<base, base61u>::value ? 60u : is_same<base, base62u>::value ? 61u : is_same<base, base63u>::value ? 62u : is_same<base, base64u>::value ? 63u : is_same<base, base65u>::value ? 64u : is_same<base, base66u>::value ? 65u : is_same<base, base67u>::value ? 66u : is_same<base, base68u>::value ? 67u : is_same<base, base69u>::value ? 68u : is_same<base, base70u>::value ? 69u : is_same<base, base71u>::value ? 70u : is_same<base, base72u>::value ? 71u : is_same<base, base73u>::value ? 72u : is_same<base, base74u>::value ? 73u : is_same<base, base75u>::value ? 74u : is_same<base, base76u>::value ? 75u : is_same<base, base77u>::value ? 76u : is_same<base, base78u>::value ? 77u : is_same<base, base79u>::value ? 78u : is_same<base, base80u>::value ? 79u : is_same<base, base81u>::value ? 80u : is_same<base, base82u>::value ? 81u : is_same<base, base83u>::value ? 82u : is_same<base, base84u>::value ? 83u : is_same<base, base85u>::value ? 84u : is_same<base, base86u>::value ? 85u : is_same<base, base87u>::value ? 86u : is_same<base, base88u>::value ? 87u : is_same<base, base89u>::value ? 88u : is_same<base, base90u>::value ? 89u : is_same<base, base91u>::value ? 90u : is_same<base, base92u>::value ? 91u : is_same<base, base93u>::value ? 92u : is_same<base, base94u>::value ? 93u : is_same<base, base95u>::value ? 94u : is_same<base, base96u>::value ? 95u : is_same<base, base97u>::value ? 96u : is_same<base, base98u>::value ? 97u : is_same<base, base99u>::value ? 98u : is_same<base, base100u>::value ? 99u : is_same<base, base101u>::value ? 100u : is_same<base, base102u>::value ? 101u : is_same<base, base103u>::value ? 102u : is_same<base, base104u>::value ? 103u : is_same<base, base105u>::value ? 104u : is_same<base, base106u>::value ? 105u : is_same<base, base107u>::value ? 106u : is_same<base, base108u>::value ? 107u : is_same<base, base109u>::value ? 108u : is_same<base, base110u>::value ? 109u : is_same<base, base111u>::value ? 110u : is_same<base, base112u>::value ? 111u : is_same<base, base113u>::value ? 112u : is_same<base, base114u>::value ? 113u : is_same<base, base115u>::value ? 114u : is_same<base, base116u>::value ? 115u : is_same<base, base117u>::value ? 116u : is_same<base, base118u>::value ? 117u : is_same<base, base119u>::value ? 118u : is_same<base, base120u>::value ? 119u : is_same<base, base121u>::value ? 120u : is_same<base, base122u>::value ? 121u : is_same<base, base123u>::value ? 122u : is_same<base, base124u>::value ? 123u : is_same<base, base125u>::value ? 124u : is_same<base, base126u>::value ? 125u : is_same<base, base127u>::value ? 126u : static_cast<std::size_t>(-1);
            };

            // ...
            template <bool, typename, typename>
            struct _conditional;

            template <typename baseA, typename baseB>
            struct _conditional<false, baseA, baseB> final {
              typedef baseB type;
            };

            template <typename baseA, typename baseB>
            struct _conditional<true, baseA, baseB> final {
              typedef baseA type;
            };

            template <typename base>
            struct _add final {
              typedef collection<typename _conditional<length == 0u, base, base1u>::type, typename _conditional<length == 1u, base, base2u>::type, typename _conditional<length == 2u, base, base3u>::type, typename _conditional<length == 3u, base, base4u>::type, typename _conditional<length == 4u, base, base5u>::type, typename _conditional<length == 5u, base, base6u>::type, typename _conditional<length == 6u, base, base7u>::type, typename _conditional<length == 7u, base, base8u>::type, typename _conditional<length == 8u, base, base9u>::type, typename _conditional<length == 9u, base, base10u>::type, typename _conditional<length == 10u, base, base11u>::type, typename _conditional<length == 11u, base, base12u>::type, typename _conditional<length == 12u, base, base13u>::type, typename _conditional<length == 13u, base, base14u>::type, typename _conditional<length == 14u, base, base15u>::type, typename _conditional<length == 15u, base, base16u>::type, typename _conditional<length == 16u, base, base17u>::type, typename _conditional<length == 17u, base, base18u>::type, typename _conditional<length == 18u, base, base19u>::type, typename _conditional<length == 19u, base, base20u>::type, typename _conditional<length == 20u, base, base21u>::type, typename _conditional<length == 21u, base, base22u>::type, typename _conditional<length == 22u, base, base23u>::type, typename _conditional<length == 23u, base, base24u>::type, typename _conditional<length == 24u, base, base25u>::type, typename _conditional<length == 25u, base, base26u>::type, typename _conditional<length == 26u, base, base27u>::type, typename _conditional<length == 27u, base, base28u>::type, typename _conditional<length == 28u, base, base29u>::type, typename _conditional<length == 29u, base, base30u>::type, typename _conditional<length == 30u, base, base31u>::type, typename _conditional<length == 31u, base, base32u>::type, typename _conditional<length == 32u, base, base33u>::type, typename _conditional<length == 33u, base, base34u>::type, typename _conditional<length == 34u, base, base35u>::type, typename _conditional<length == 35u, base, base36u>::type, typename _conditional<length == 36u, base, base37u>::type, typename _conditional<length == 37u, base, base38u>::type, typename _conditional<length == 38u, base, base39u>::type, typename _conditional<length == 39u, base, base40u>::type, typename _conditional<length == 40u, base, base41u>::type, typename _conditional<length == 41u, base, base42u>::type, typename _conditional<length == 42u, base, base43u>::type, typename _conditional<length == 43u, base, base44u>::type, typename _conditional<length == 44u, base, base45u>::type, typename _conditional<length == 45u, base, base46u>::type, typename _conditional<length == 46u, base, base47u>::type, typename _conditional<length == 47u, base, base48u>::type, typename _conditional<length == 48u, base, base49u>::type, typename _conditional<length == 49u, base, base50u>::type, typename _conditional<length == 50u, base, base51u>::type, typename _conditional<length == 51u, base, base52u>::type, typename _conditional<length == 52u, base, base53u>::type, typename _conditional<length == 53u, base, base54u>::type, typename _conditional<length == 54u, base, base55u>::type, typename _conditional<length == 55u, base, base56u>::type, typename _conditional<length == 56u, base, base57u>::type, typename _conditional<length == 57u, base, base58u>::type, typename _conditional<length == 58u, base, base59u>::type, typename _conditional<length == 59u, base, base60u>::type, typename _conditional<length == 60u, base, base61u>::type, typename _conditional<length == 61u, base, base62u>::type, typename _conditional<length == 62u, base, base63u>::type, typename _conditional<length == 63u, base, base64u>::type, typename _conditional<length == 64u, base, base65u>::type, typename _conditional<length == 65u, base, base66u>::type, typename _conditional<length == 66u, base, base67u>::type, typename _conditional<length == 67u, base, base68u>::type, typename _conditional<length == 68u, base, base69u>::type, typename _conditional<length == 69u, base, base70u>::type, typename _conditional<length == 70u, base, base71u>::type, typename _conditional<length == 71u, base, base72u>::type, typename _conditional<length == 72u, base, base73u>::type, typename _conditional<length == 73u, base, base74u>::type, typename _conditional<length == 74u, base, base75u>::type, typename _conditional<length == 75u, base, base76u>::type, typename _conditional<length == 76u, base, base77u>::type, typename _conditional<length == 77u, base, base78u>::type, typename _conditional<length == 78u, base, base79u>::type, typename _conditional<length == 79u, base, base80u>::type, typename _conditional<length == 80u, base, base81u>::type, typename _conditional<length == 81u, base, base82u>::type, typename _conditional<length == 82u, base, base83u>::type, typename _conditional<length == 83u, base, base84u>::type, typename _conditional<length == 84u, base, base85u>::type, typename _conditional<length == 85u, base, base86u>::type, typename _conditional<length == 86u, base, base87u>::type, typename _conditional<length == 87u, base, base88u>::type, typename _conditional<length == 88u, base, base89u>::type, typename _conditional<length == 89u, base, base90u>::type, typename _conditional<length == 90u, base, base91u>::type, typename _conditional<length == 91u, base, base92u>::type, typename _conditional<length == 92u, base, base93u>::type, typename _conditional<length == 93u, base, base94u>::type, typename _conditional<length == 94u, base, base95u>::type, typename _conditional<length == 95u, base, base96u>::type, typename _conditional<length == 96u, base, base97u>::type, typename _conditional<length == 97u, base, base98u>::type, typename _conditional<length == 98u, base, base99u>::type, typename _conditional<length == 99u, base, base100u>::type, typename _conditional<length == 100u, base, base101u>::type, typename _conditional<length == 101u, base, base102u>::type, typename _conditional<length == 102u, base, base103u>::type, typename _conditional<length == 103u, base, base104u>::type, typename _conditional<length == 104u, base, base105u>::type, typename _conditional<length == 105u, base, base106u>::type, typename _conditional<length == 106u, base, base107u>::type, typename _conditional<length == 107u, base, base108u>::type, typename _conditional<length == 108u, base, base109u>::type, typename _conditional<length == 109u, base, base110u>::type, typename _conditional<length == 110u, base, base111u>::type, typename _conditional<length == 111u, base, base112u>::type, typename _conditional<length == 112u, base, base113u>::type, typename _conditional<length == 113u, base, base114u>::type, typename _conditional<length == 114u, base, base115u>::type, typename _conditional<length == 115u, base, base116u>::type, typename _conditional<length == 116u, base, base117u>::type, typename _conditional<length == 117u, base, base118u>::type, typename _conditional<length == 118u, base, base119u>::type, typename _conditional<length == 119u, base, base120u>::type, typename _conditional<length == 120u, base, base121u>::type, typename _conditional<length == 121u, base, base122u>::type, typename _conditional<length == 122u, base, base123u>::type, typename _conditional<length == 123u, base, base124u>::type, typename _conditional<length == 124u, base, base125u>::type, typename _conditional<length == 125u, base, base126u>::type, typename _conditional<length == 126u, base, base127u>::type> type;
            };

            // ...
            template <class subcollection, std::size_t = subcollection::length>
            struct _concatenate final {
              typedef typename _add<typename subcollection::first>::type::template _concatenate<typename subcollection::_slice<1u>::type>::type type;
            };

            template <class subcollection>
            struct _concatenate<subcollection, 0u> final {
              typedef collection<base1u, base2u, base3u, base4u, base5u, base6u, base7u, base8u, base9u, base10u, base11u, base12u, base13u, base14u, base15u, base16u, base17u, base18u, base19u, base20u, base21u, base22u, base23u, base24u, base25u, base26u, base27u, base28u, base29u, base30u, base31u, base32u, base33u, base34u, base35u, base36u, base37u, base38u, base39u, base40u, base41u, base42u, base43u, base44u, base45u, base46u, base47u, base48u, base49u, base50u, base51u, base52u, base53u, base54u, base55u, base56u, base57u, base58u, base59u, base60u, base61u, base62u, base63u, base64u, base65u, base66u, base67u, base68u, base69u, base70u, base71u, base72u, base73u, base74u, base75u, base76u, base77u, base78u, base79u, base80u, base81u, base82u, base83u, base84u, base85u, base86u, base87u, base88u, base89u, base90u, base91u, base92u, base93u, base94u, base95u, base96u, base97u, base98u, base99u, base100u, base101u, base102u, base103u, base104u, base105u, base106u, base107u, base108u, base109u, base110u, base111u, base112u, base113u, base114u, base115u, base116u, base117u, base118u, base119u, base120u, base121u, base122u, base123u, base124u, base125u, base126u, base127u> type;
            };

            // ...
            template <std::size_t index, sfinaeptr_t = sfinaeptr>
            struct _at final {
              typedef typename _slice<index>::type::first type;
            };

            template <sfinaeptr_t sfinae>
            struct _at<0u, sfinae> final {
              typedef base1u type;
            };

            // ...
            struct _apply final {
              template <typename base, std::size_t>
              struct value final {
                typedef base type;
              };
            };

          public:
            template <typename base>
            struct add final {
              private:
                typedef constant<bool, length != maximum, true> invalid_collection_modification;

              public:
                static_assert(invalid_collection_modification::value, "Unable to add to `collection<...>` trait");
                typedef typename _add<base>::type type;
            };

            // ...
            template <template <typename, std::size_t> class trait>
            struct apply final {
              private:
                template <typename base, std::size_t index>
                struct value final {
                  typedef typename trait<base, index>::type type;
                };

              public:
                typedef collection<typename _conditional<(length > 0u), apply<trait>, _apply>::type::template value<base1u, 0u>::type, typename _conditional<(length > 1u), apply<trait>, _apply>::type::template value<base2u, 1u>::type, typename _conditional<(length > 2u), apply<trait>, _apply>::type::template value<base3u, 2u>::type, typename _conditional<(length > 3u), apply<trait>, _apply>::type::template value<base4u, 3u>::type, typename _conditional<(length > 4u), apply<trait>, _apply>::type::template value<base5u, 4u>::type, typename _conditional<(length > 5u), apply<trait>, _apply>::type::template value<base6u, 5u>::type, typename _conditional<(length > 6u), apply<trait>, _apply>::type::template value<base7u, 6u>::type, typename _conditional<(length > 7u), apply<trait>, _apply>::type::template value<base8u, 7u>::type, typename _conditional<(length > 8u), apply<trait>, _apply>::type::template value<base9u, 8u>::type, typename _conditional<(length > 9u), apply<trait>, _apply>::type::template value<base10u, 9u>::type, typename _conditional<(length > 10u), apply<trait>, _apply>::type::template value<base11u, 10u>::type, typename _conditional<(length > 11u), apply<trait>, _apply>::type::template value<base12u, 11u>::type, typename _conditional<(length > 12u), apply<trait>, _apply>::type::template value<base13u, 12u>::type, typename _conditional<(length > 13u), apply<trait>, _apply>::type::template value<base14u, 13u>::type, typename _conditional<(length > 14u), apply<trait>, _apply>::type::template value<base15u, 14u>::type, typename _conditional<(length > 15u), apply<trait>, _apply>::type::template value<base16u, 15u>::type, typename _conditional<(length > 16u), apply<trait>, _apply>::type::template value<base17u, 16u>::type, typename _conditional<(length > 17u), apply<trait>, _apply>::type::template value<base18u, 17u>::type, typename _conditional<(length > 18u), apply<trait>, _apply>::type::template value<base19u, 18u>::type, typename _conditional<(length > 19u), apply<trait>, _apply>::type::template value<base20u, 19u>::type, typename _conditional<(length > 20u), apply<trait>, _apply>::type::template value<base21u, 20u>::type, typename _conditional<(length > 21u), apply<trait>, _apply>::type::template value<base22u, 21u>::type, typename _conditional<(length > 22u), apply<trait>, _apply>::type::template value<base23u, 22u>::type, typename _conditional<(length > 23u), apply<trait>, _apply>::type::template value<base24u, 23u>::type, typename _conditional<(length > 24u), apply<trait>, _apply>::type::template value<base25u, 24u>::type, typename _conditional<(length > 25u), apply<trait>, _apply>::type::template value<base26u, 25u>::type, typename _conditional<(length > 26u), apply<trait>, _apply>::type::template value<base27u, 26u>::type, typename _conditional<(length > 27u), apply<trait>, _apply>::type::template value<base28u, 27u>::type, typename _conditional<(length > 28u), apply<trait>, _apply>::type::template value<base29u, 28u>::type, typename _conditional<(length > 29u), apply<trait>, _apply>::type::template value<base30u, 29u>::type, typename _conditional<(length > 30u), apply<trait>, _apply>::type::template value<base31u, 30u>::type, typename _conditional<(length > 31u), apply<trait>, _apply>::type::template value<base32u, 31u>::type, typename _conditional<(length > 32u), apply<trait>, _apply>::type::template value<base33u, 32u>::type, typename _conditional<(length > 33u), apply<trait>, _apply>::type::template value<base34u, 33u>::type, typename _conditional<(length > 34u), apply<trait>, _apply>::type::template value<base35u, 34u>::type, typename _conditional<(length > 35u), apply<trait>, _apply>::type::template value<base36u, 35u>::type, typename _conditional<(length > 36u), apply<trait>, _apply>::type::template value<base37u, 36u>::type, typename _conditional<(length > 37u), apply<trait>, _apply>::type::template value<base38u, 37u>::type, typename _conditional<(length > 38u), apply<trait>, _apply>::type::template value<base39u, 38u>::type, typename _conditional<(length > 39u), apply<trait>, _apply>::type::template value<base40u, 39u>::type, typename _conditional<(length > 40u), apply<trait>, _apply>::type::template value<base41u, 40u>::type, typename _conditional<(length > 41u), apply<trait>, _apply>::type::template value<base42u, 41u>::type, typename _conditional<(length > 42u), apply<trait>, _apply>::type::template value<base43u, 42u>::type, typename _conditional<(length > 43u), apply<trait>, _apply>::type::template value<base44u, 43u>::type, typename _conditional<(length > 44u), apply<trait>, _apply>::type::template value<base45u, 44u>::type, typename _conditional<(length > 45u), apply<trait>, _apply>::type::template value<base46u, 45u>::type, typename _conditional<(length > 46u), apply<trait>, _apply>::type::template value<base47u, 46u>::type, typename _conditional<(length > 47u), apply<trait>, _apply>::type::template value<base48u, 47u>::type, typename _conditional<(length > 48u), apply<trait>, _apply>::type::template value<base49u, 48u>::type, typename _conditional<(length > 49u), apply<trait>, _apply>::type::template value<base50u, 49u>::type, typename _conditional<(length > 50u), apply<trait>, _apply>::type::template value<base51u, 50u>::type, typename _conditional<(length > 51u), apply<trait>, _apply>::type::template value<base52u, 51u>::type, typename _conditional<(length > 52u), apply<trait>, _apply>::type::template value<base53u, 52u>::type, typename _conditional<(length > 53u), apply<trait>, _apply>::type::template value<base54u, 53u>::type, typename _conditional<(length > 54u), apply<trait>, _apply>::type::template value<base55u, 54u>::type, typename _conditional<(length > 55u), apply<trait>, _apply>::type::template value<base56u, 55u>::type, typename _conditional<(length > 56u), apply<trait>, _apply>::type::template value<base57u, 56u>::type, typename _conditional<(length > 57u), apply<trait>, _apply>::type::template value<base58u, 57u>::type, typename _conditional<(length > 58u), apply<trait>, _apply>::type::template value<base59u, 58u>::type, typename _conditional<(length > 59u), apply<trait>, _apply>::type::template value<base60u, 59u>::type, typename _conditional<(length > 60u), apply<trait>, _apply>::type::template value<base61u, 60u>::type, typename _conditional<(length > 61u), apply<trait>, _apply>::type::template value<base62u, 61u>::type, typename _conditional<(length > 62u), apply<trait>, _apply>::type::template value<base63u, 62u>::type, typename _conditional<(length > 63u), apply<trait>, _apply>::type::template value<base64u, 63u>::type, typename _conditional<(length > 64u), apply<trait>, _apply>::type::template value<base65u, 64u>::type, typename _conditional<(length > 65u), apply<trait>, _apply>::type::template value<base66u, 65u>::type, typename _conditional<(length > 66u), apply<trait>, _apply>::type::template value<base67u, 66u>::type, typename _conditional<(length > 67u), apply<trait>, _apply>::type::template value<base68u, 67u>::type, typename _conditional<(length > 68u), apply<trait>, _apply>::type::template value<base69u, 68u>::type, typename _conditional<(length > 69u), apply<trait>, _apply>::type::template value<base70u, 69u>::type, typename _conditional<(length > 70u), apply<trait>, _apply>::type::template value<base71u, 70u>::type, typename _conditional<(length > 71u), apply<trait>, _apply>::type::template value<base72u, 71u>::type, typename _conditional<(length > 72u), apply<trait>, _apply>::type::template value<base73u, 72u>::type, typename _conditional<(length > 73u), apply<trait>, _apply>::type::template value<base74u, 73u>::type, typename _conditional<(length > 74u), apply<trait>, _apply>::type::template value<base75u, 74u>::type, typename _conditional<(length > 75u), apply<trait>, _apply>::type::template value<base76u, 75u>::type, typename _conditional<(length > 76u), apply<trait>, _apply>::type::template value<base77u, 76u>::type, typename _conditional<(length > 77u), apply<trait>, _apply>::type::template value<base78u, 77u>::type, typename _conditional<(length > 78u), apply<trait>, _apply>::type::template value<base79u, 78u>::type, typename _conditional<(length > 79u), apply<trait>, _apply>::type::template value<base80u, 79u>::type, typename _conditional<(length > 80u), apply<trait>, _apply>::type::template value<base81u, 80u>::type, typename _conditional<(length > 81u), apply<trait>, _apply>::type::template value<base82u, 81u>::type, typename _conditional<(length > 82u), apply<trait>, _apply>::type::template value<base83u, 82u>::type, typename _conditional<(length > 83u), apply<trait>, _apply>::type::template value<base84u, 83u>::type, typename _conditional<(length > 84u), apply<trait>, _apply>::type::template value<base85u, 84u>::type, typename _conditional<(length > 85u), apply<trait>, _apply>::type::template value<base86u, 85u>::type, typename _conditional<(length > 86u), apply<trait>, _apply>::type::template value<base87u, 86u>::type, typename _conditional<(length > 87u), apply<trait>, _apply>::type::template value<base88u, 87u>::type, typename _conditional<(length > 88u), apply<trait>, _apply>::type::template value<base89u, 88u>::type, typename _conditional<(length > 89u), apply<trait>, _apply>::type::template value<base90u, 89u>::type, typename _conditional<(length > 90u), apply<trait>, _apply>::type::template value<base91u, 90u>::type, typename _conditional<(length > 91u), apply<trait>, _apply>::type::template value<base92u, 91u>::type, typename _conditional<(length > 92u), apply<trait>, _apply>::type::template value<base93u, 92u>::type, typename _conditional<(length > 93u), apply<trait>, _apply>::type::template value<base94u, 93u>::type, typename _conditional<(length > 94u), apply<trait>, _apply>::type::template value<base95u, 94u>::type, typename _conditional<(length > 95u), apply<trait>, _apply>::type::template value<base96u, 95u>::type, typename _conditional<(length > 96u), apply<trait>, _apply>::type::template value<base97u, 96u>::type, typename _conditional<(length > 97u), apply<trait>, _apply>::type::template value<base98u, 97u>::type, typename _conditional<(length > 98u), apply<trait>, _apply>::type::template value<base99u, 98u>::type, typename _conditional<(length > 99u), apply<trait>, _apply>::type::template value<base100u, 99u>::type, typename _conditional<(length > 100u), apply<trait>, _apply>::type::template value<base101u, 100u>::type, typename _conditional<(length > 101u), apply<trait>, _apply>::type::template value<base102u, 101u>::type, typename _conditional<(length > 102u), apply<trait>, _apply>::type::template value<base103u, 102u>::type, typename _conditional<(length > 103u), apply<trait>, _apply>::type::template value<base104u, 103u>::type, typename _conditional<(length > 104u), apply<trait>, _apply>::type::template value<base105u, 104u>::type, typename _conditional<(length > 105u), apply<trait>, _apply>::type::template value<base106u, 105u>::type, typename _conditional<(length > 106u), apply<trait>, _apply>::type::template value<base107u, 106u>::type, typename _conditional<(length > 107u), apply<trait>, _apply>::type::template value<base108u, 107u>::type, typename _conditional<(length > 108u), apply<trait>, _apply>::type::template value<base109u, 108u>::type, typename _conditional<(length > 109u), apply<trait>, _apply>::type::template value<base110u, 109u>::type, typename _conditional<(length > 110u), apply<trait>, _apply>::type::template value<base111u, 110u>::type, typename _conditional<(length > 111u), apply<trait>, _apply>::type::template value<base112u, 111u>::type, typename _conditional<(length > 112u), apply<trait>, _apply>::type::template value<base113u, 112u>::type, typename _conditional<(length > 113u), apply<trait>, _apply>::type::template value<base114u, 113u>::type, typename _conditional<(length > 114u), apply<trait>, _apply>::type::template value<base115u, 114u>::type, typename _conditional<(length > 115u), apply<trait>, _apply>::type::template value<base116u, 115u>::type, typename _conditional<(length > 116u), apply<trait>, _apply>::type::template value<base117u, 116u>::type, typename _conditional<(length > 117u), apply<trait>, _apply>::type::template value<base118u, 117u>::type, typename _conditional<(length > 118u), apply<trait>, _apply>::type::template value<base119u, 118u>::type, typename _conditional<(length > 119u), apply<trait>, _apply>::type::template value<base120u, 119u>::type, typename _conditional<(length > 120u), apply<trait>, _apply>::type::template value<base121u, 120u>::type, typename _conditional<(length > 121u), apply<trait>, _apply>::type::template value<base122u, 121u>::type, typename _conditional<(length > 122u), apply<trait>, _apply>::type::template value<base123u, 122u>::type, typename _conditional<(length > 123u), apply<trait>, _apply>::type::template value<base124u, 123u>::type, typename _conditional<(length > 124u), apply<trait>, _apply>::type::template value<base125u, 124u>::type, typename _conditional<(length > 125u), apply<trait>, _apply>::type::template value<base126u, 125u>::type, typename _conditional<(length > 126u), apply<trait>, _apply>::type::template value<base127u, 126u>::type> type;
            };

            // ...
            template <std::size_t index>
            struct at final {
              private:
                typedef constant<bool, (index < length), true> invalid_collection_index;

              public:
                static_assert(invalid_collection_index::value, "Out-of-bounds indexing of `collection<...>` trait");
                typedef typename _conditional<invalid_collection_index::value, typename _at<invalid_collection_index::value ? index : 0u>::type, null>::type type;
            };

            // ...
            template <class subcollection>
            struct concatenate final {
              private:
                typedef constant<bool, 0u == sizeof(defer::template type<subcollection>), true> invalid_collection_concatenation;

              public:
                static_assert(invalid_collection_concatenation::value, "Unable to concatenate with `collection<...>` trait");
            };

            template <typename subbase1u, typename subbase2u, typename subbase3u, typename subbase4u, typename subbase5u, typename subbase6u, typename subbase7u, typename subbase8u, typename subbase9u, typename subbase10u, typename subbase11u, typename subbase12u, typename subbase13u, typename subbase14u, typename subbase15u, typename subbase16u, typename subbase17u, typename subbase18u, typename subbase19u, typename subbase20u, typename subbase21u, typename subbase22u, typename subbase23u, typename subbase24u, typename subbase25u, typename subbase26u, typename subbase27u, typename subbase28u, typename subbase29u, typename subbase30u, typename subbase31u, typename subbase32u, typename subbase33u, typename subbase34u, typename subbase35u, typename subbase36u, typename subbase37u, typename subbase38u, typename subbase39u, typename subbase40u, typename subbase41u, typename subbase42u, typename subbase43u, typename subbase44u, typename subbase45u, typename subbase46u, typename subbase47u, typename subbase48u, typename subbase49u, typename subbase50u, typename subbase51u, typename subbase52u, typename subbase53u, typename subbase54u, typename subbase55u, typename subbase56u, typename subbase57u, typename subbase58u, typename subbase59u, typename subbase60u, typename subbase61u, typename subbase62u, typename subbase63u, typename subbase64u, typename subbase65u, typename subbase66u, typename subbase67u, typename subbase68u, typename subbase69u, typename subbase70u, typename subbase71u, typename subbase72u, typename subbase73u, typename subbase74u, typename subbase75u, typename subbase76u, typename subbase77u, typename subbase78u, typename subbase79u, typename subbase80u, typename subbase81u, typename subbase82u, typename subbase83u, typename subbase84u, typename subbase85u, typename subbase86u, typename subbase87u, typename subbase88u, typename subbase89u, typename subbase90u, typename subbase91u, typename subbase92u, typename subbase93u, typename subbase94u, typename subbase95u, typename subbase96u, typename subbase97u, typename subbase98u, typename subbase99u, typename subbase100u, typename subbase101u, typename subbase102u, typename subbase103u, typename subbase104u, typename subbase105u, typename subbase106u, typename subbase107u, typename subbase108u, typename subbase109u, typename subbase110u, typename subbase111u, typename subbase112u, typename subbase113u, typename subbase114u, typename subbase115u, typename subbase116u, typename subbase117u, typename subbase118u, typename subbase119u, typename subbase120u, typename subbase121u, typename subbase122u, typename subbase123u, typename subbase124u, typename subbase125u, typename subbase126u, typename subbase127u>
            struct concatenate<collection<subbase1u, subbase2u, subbase3u, subbase4u, subbase5u, subbase6u, subbase7u, subbase8u, subbase9u, subbase10u, subbase11u, subbase12u, subbase13u, subbase14u, subbase15u, subbase16u, subbase17u, subbase18u, subbase19u, subbase20u, subbase21u, subbase22u, subbase23u, subbase24u, subbase25u, subbase26u, subbase27u, subbase28u, subbase29u, subbase30u, subbase31u, subbase32u, subbase33u, subbase34u, subbase35u, subbase36u, subbase37u, subbase38u, subbase39u, subbase40u, subbase41u, subbase42u, subbase43u, subbase44u, subbase45u, subbase46u, subbase47u, subbase48u, subbase49u, subbase50u, subbase51u, subbase52u, subbase53u, subbase54u, subbase55u, subbase56u, subbase57u, subbase58u, subbase59u, subbase60u, subbase61u, subbase62u, subbase63u, subbase64u, subbase65u, subbase66u, subbase67u, subbase68u, subbase69u, subbase70u, subbase71u, subbase72u, subbase73u, subbase74u, subbase75u, subbase76u, subbase77u, subbase78u, subbase79u, subbase80u, subbase81u, subbase82u, subbase83u, subbase84u, subbase85u, subbase86u, subbase87u, subbase88u, subbase89u, subbase90u, subbase91u, subbase92u, subbase93u, subbase94u, subbase95u, subbase96u, subbase97u, subbase98u, subbase99u, subbase100u, subbase101u, subbase102u, subbase103u, subbase104u, subbase105u, subbase106u, subbase107u, subbase108u, subbase109u, subbase110u, subbase111u, subbase112u, subbase113u, subbase114u, subbase115u, subbase116u, subbase117u, subbase118u, subbase119u, subbase120u, subbase121u, subbase122u, subbase123u, subbase124u, subbase125u, subbase126u, subbase127u> > final {
              private:
                typedef constant<bool, (collection<subbase1u, subbase2u, subbase3u, subbase4u, subbase5u, subbase6u, subbase7u, subbase8u, subbase9u, subbase10u, subbase11u, subbase12u, subbase13u, subbase14u, subbase15u, subbase16u, subbase17u, subbase18u, subbase19u, subbase20u, subbase21u, subbase22u, subbase23u, subbase24u, subbase25u, subbase26u, subbase27u, subbase28u, subbase29u, subbase30u, subbase31u, subbase32u, subbase33u, subbase34u, subbase35u, subbase36u, subbase37u, subbase38u, subbase39u, subbase40u, subbase41u, subbase42u, subbase43u, subbase44u, subbase45u, subbase46u, subbase47u, subbase48u, subbase49u, subbase50u, subbase51u, subbase52u, subbase53u, subbase54u, subbase55u, subbase56u, subbase57u, subbase58u, subbase59u, subbase60u, subbase61u, subbase62u, subbase63u, subbase64u, subbase65u, subbase66u, subbase67u, subbase68u, subbase69u, subbase70u, subbase71u, subbase72u, subbase73u, subbase74u, subbase75u, subbase76u, subbase77u, subbase78u, subbase79u, subbase80u, subbase81u, subbase82u, subbase83u, subbase84u, subbase85u, subbase86u, subbase87u, subbase88u, subbase89u, subbase90u, subbase91u, subbase92u, subbase93u, subbase94u, subbase95u, subbase96u, subbase97u, subbase98u, subbase99u, subbase100u, subbase101u, subbase102u, subbase103u, subbase104u, subbase105u, subbase106u, subbase107u, subbase108u, subbase109u, subbase110u, subbase111u, subbase112u, subbase113u, subbase114u, subbase115u, subbase116u, subbase117u, subbase118u, subbase119u, subbase120u, subbase121u, subbase122u, subbase123u, subbase124u, subbase125u, subbase126u, subbase127u>::length + length <= maximum), true> invalid_collection_concatenation;

              public:
                static_assert(invalid_collection_concatenation::value, "Unable to evaluate concatenated `collection<...>` traits");
                typedef typename _concatenate<collection<subbase1u, subbase2u, subbase3u, subbase4u, subbase5u, subbase6u, subbase7u, subbase8u, subbase9u, subbase10u, subbase11u, subbase12u, subbase13u, subbase14u, subbase15u, subbase16u, subbase17u, subbase18u, subbase19u, subbase20u, subbase21u, subbase22u, subbase23u, subbase24u, subbase25u, subbase26u, subbase27u, subbase28u, subbase29u, subbase30u, subbase31u, subbase32u, subbase33u, subbase34u, subbase35u, subbase36u, subbase37u, subbase38u, subbase39u, subbase40u, subbase41u, subbase42u, subbase43u, subbase44u, subbase45u, subbase46u, subbase47u, subbase48u, subbase49u, subbase50u, subbase51u, subbase52u, subbase53u, subbase54u, subbase55u, subbase56u, subbase57u, subbase58u, subbase59u, subbase60u, subbase61u, subbase62u, subbase63u, subbase64u, subbase65u, subbase66u, subbase67u, subbase68u, subbase69u, subbase70u, subbase71u, subbase72u, subbase73u, subbase74u, subbase75u, subbase76u, subbase77u, subbase78u, subbase79u, subbase80u, subbase81u, subbase82u, subbase83u, subbase84u, subbase85u, subbase86u, subbase87u, subbase88u, subbase89u, subbase90u, subbase91u, subbase92u, subbase93u, subbase94u, subbase95u, subbase96u, subbase97u, subbase98u, subbase99u, subbase100u, subbase101u, subbase102u, subbase103u, subbase104u, subbase105u, subbase106u, subbase107u, subbase108u, subbase109u, subbase110u, subbase111u, subbase112u, subbase113u, subbase114u, subbase115u, subbase116u, subbase117u, subbase118u, subbase119u, subbase120u, subbase121u, subbase122u, subbase123u, subbase124u, subbase125u, subbase126u, subbase127u> >::type type;
            };

            // ...
            template <typename base>
            struct has final {
              static bool const value = not is_null<base>::value and (is_same<base, base1u>::value or is_same<base, base2u>::value or is_same<base, base3u>::value or is_same<base, base4u>::value or is_same<base, base5u>::value or is_same<base, base6u>::value or is_same<base, base7u>::value or is_same<base, base8u>::value or is_same<base, base9u>::value or is_same<base, base10u>::value or is_same<base, base11u>::value or is_same<base, base12u>::value or is_same<base, base13u>::value or is_same<base, base14u>::value or is_same<base, base15u>::value or is_same<base, base16u>::value or is_same<base, base17u>::value or is_same<base, base18u>::value or is_same<base, base19u>::value or is_same<base, base20u>::value or is_same<base, base21u>::value or is_same<base, base22u>::value or is_same<base, base23u>::value or is_same<base, base24u>::value or is_same<base, base25u>::value or is_same<base, base26u>::value or is_same<base, base27u>::value or is_same<base, base28u>::value or is_same<base, base29u>::value or is_same<base, base30u>::value or is_same<base, base31u>::value or is_same<base, base32u>::value or is_same<base, base33u>::value or is_same<base, base34u>::value or is_same<base, base35u>::value or is_same<base, base36u>::value or is_same<base, base37u>::value or is_same<base, base38u>::value or is_same<base, base39u>::value or is_same<base, base40u>::value or is_same<base, base41u>::value or is_same<base, base42u>::value or is_same<base, base43u>::value or is_same<base, base44u>::value or is_same<base, base45u>::value or is_same<base, base46u>::value or is_same<base, base47u>::value or is_same<base, base48u>::value or is_same<base, base49u>::value or is_same<base, base50u>::value or is_same<base, base51u>::value or is_same<base, base52u>::value or is_same<base, base53u>::value or is_same<base, base54u>::value or is_same<base, base55u>::value or is_same<base, base56u>::value or is_same<base, base57u>::value or is_same<base, base58u>::value or is_same<base, base59u>::value or is_same<base, base60u>::value or is_same<base, base61u>::value or is_same<base, base62u>::value or is_same<base, base63u>::value or is_same<base, base64u>::value or is_same<base, base65u>::value or is_same<base, base66u>::value or is_same<base, base67u>::value or is_same<base, base68u>::value or is_same<base, base69u>::value or is_same<base, base70u>::value or is_same<base, base71u>::value or is_same<base, base72u>::value or is_same<base, base73u>::value or is_same<base, base74u>::value or is_same<base, base75u>::value or is_same<base, base76u>::value or is_same<base, base77u>::value or is_same<base, base78u>::value or is_same<base, base79u>::value or is_same<base, base80u>::value or is_same<base, base81u>::value or is_same<base, base82u>::value or is_same<base, base83u>::value or is_same<base, base84u>::value or is_same<base, base85u>::value or is_same<base, base86u>::value or is_same<base, base87u>::value or is_same<base, base88u>::value or is_same<base, base89u>::value or is_same<base, base90u>::value or is_same<base, base91u>::value or is_same<base, base92u>::value or is_same<base, base93u>::value or is_same<base, base94u>::value or is_same<base, base95u>::value or is_same<base, base96u>::value or is_same<base, base97u>::value or is_same<base, base98u>::value or is_same<base, base99u>::value or is_same<base, base100u>::value or is_same<base, base101u>::value or is_same<base, base102u>::value or is_same<base, base103u>::value or is_same<base, base104u>::value or is_same<base, base105u>::value or is_same<base, base106u>::value or is_same<base, base107u>::value or is_same<base, base108u>::value or is_same<base, base109u>::value or is_same<base, base110u>::value or is_same<base, base111u>::value or is_same<base, base112u>::value or is_same<base, base113u>::value or is_same<base, base114u>::value or is_same<base, base115u>::value or is_same<base, base116u>::value or is_same<base, base117u>::value or is_same<base, base118u>::value or is_same<base, base119u>::value or is_same<base, base120u>::value or is_same<base, base121u>::value or is_same<base, base122u>::value or is_same<base, base123u>::value or is_same<base, base124u>::value or is_same<base, base125u>::value or is_same<base, base126u>::value or is_same<base, base127u>::value);
            };

            // ...
            template <typename base>
            struct index final {
              private:
                typedef constant<bool, has<base>::value, true> invalid_collection_search;

              public:
                static_assert(invalid_collection_search::value, "Out-of-bounds searching of `collection<...>` trait");
                static std::size_t const value = is_null<base>::value ? static_cast<std::size_t>(-1) : _index<base>::value;
            };

            // ...
            template <typename base>
            struct remove final {
              typedef typename conditional<
                has<base>::value,
                collection<typename _conditional<(_index<base>::value <= 0u), base2u, base1u>::type, typename _conditional<(_index<base>::value <= 1u), base3u, base2u>::type, typename _conditional<(_index<base>::value <= 2u), base4u, base3u>::type, typename _conditional<(_index<base>::value <= 3u), base5u, base4u>::type, typename _conditional<(_index<base>::value <= 4u), base6u, base5u>::type, typename _conditional<(_index<base>::value <= 5u), base7u, base6u>::type, typename _conditional<(_index<base>::value <= 6u), base8u, base7u>::type, typename _conditional<(_index<base>::value <= 7u), base9u, base8u>::type, typename _conditional<(_index<base>::value <= 8u), base10u, base9u>::type, typename _conditional<(_index<base>::value <= 9u), base11u, base10u>::type, typename _conditional<(_index<base>::value <= 10u), base12u, base11u>::type, typename _conditional<(_index<base>::value <= 11u), base13u, base12u>::type, typename _conditional<(_index<base>::value <= 12u), base14u, base13u>::type, typename _conditional<(_index<base>::value <= 13u), base15u, base14u>::type, typename _conditional<(_index<base>::value <= 14u), base16u, base15u>::type, typename _conditional<(_index<base>::value <= 15u), base17u, base16u>::type, typename _conditional<(_index<base>::value <= 16u), base18u, base17u>::type, typename _conditional<(_index<base>::value <= 17u), base19u, base18u>::type, typename _conditional<(_index<base>::value <= 18u), base20u, base19u>::type, typename _conditional<(_index<base>::value <= 19u), base21u, base20u>::type, typename _conditional<(_index<base>::value <= 20u), base22u, base21u>::type, typename _conditional<(_index<base>::value <= 21u), base23u, base22u>::type, typename _conditional<(_index<base>::value <= 22u), base24u, base23u>::type, typename _conditional<(_index<base>::value <= 23u), base25u, base24u>::type, typename _conditional<(_index<base>::value <= 24u), base26u, base25u>::type, typename _conditional<(_index<base>::value <= 25u), base27u, base26u>::type, typename _conditional<(_index<base>::value <= 26u), base28u, base27u>::type, typename _conditional<(_index<base>::value <= 27u), base29u, base28u>::type, typename _conditional<(_index<base>::value <= 28u), base30u, base29u>::type, typename _conditional<(_index<base>::value <= 29u), base31u, base30u>::type, typename _conditional<(_index<base>::value <= 30u), base32u, base31u>::type, typename _conditional<(_index<base>::value <= 31u), base33u, base32u>::type, typename _conditional<(_index<base>::value <= 32u), base34u, base33u>::type, typename _conditional<(_index<base>::value <= 33u), base35u, base34u>::type, typename _conditional<(_index<base>::value <= 34u), base36u, base35u>::type, typename _conditional<(_index<base>::value <= 35u), base37u, base36u>::type, typename _conditional<(_index<base>::value <= 36u), base38u, base37u>::type, typename _conditional<(_index<base>::value <= 37u), base39u, base38u>::type, typename _conditional<(_index<base>::value <= 38u), base40u, base39u>::type, typename _conditional<(_index<base>::value <= 39u), base41u, base40u>::type, typename _conditional<(_index<base>::value <= 40u), base42u, base41u>::type, typename _conditional<(_index<base>::value <= 41u), base43u, base42u>::type, typename _conditional<(_index<base>::value <= 42u), base44u, base43u>::type, typename _conditional<(_index<base>::value <= 43u), base45u, base44u>::type, typename _conditional<(_index<base>::value <= 44u), base46u, base45u>::type, typename _conditional<(_index<base>::value <= 45u), base47u, base46u>::type, typename _conditional<(_index<base>::value <= 46u), base48u, base47u>::type, typename _conditional<(_index<base>::value <= 47u), base49u, base48u>::type, typename _conditional<(_index<base>::value <= 48u), base50u, base49u>::type, typename _conditional<(_index<base>::value <= 49u), base51u, base50u>::type, typename _conditional<(_index<base>::value <= 50u), base52u, base51u>::type, typename _conditional<(_index<base>::value <= 51u), base53u, base52u>::type, typename _conditional<(_index<base>::value <= 52u), base54u, base53u>::type, typename _conditional<(_index<base>::value <= 53u), base55u, base54u>::type, typename _conditional<(_index<base>::value <= 54u), base56u, base55u>::type, typename _conditional<(_index<base>::value <= 55u), base57u, base56u>::type, typename _conditional<(_index<base>::value <= 56u), base58u, base57u>::type, typename _conditional<(_index<base>::value <= 57u), base59u, base58u>::type, typename _conditional<(_index<base>::value <= 58u), base60u, base59u>::type, typename _conditional<(_index<base>::value <= 59u), base61u, base60u>::type, typename _conditional<(_index<base>::value <= 60u), base62u, base61u>::type, typename _conditional<(_index<base>::value <= 61u), base63u, base62u>::type, typename _conditional<(_index<base>::value <= 62u), base64u, base63u>::type, typename _conditional<(_index<base>::value <= 63u), base65u, base64u>::type, typename _conditional<(_index<base>::value <= 64u), base66u, base65u>::type, typename _conditional<(_index<base>::value <= 65u), base67u, base66u>::type, typename _conditional<(_index<base>::value <= 66u), base68u, base67u>::type, typename _conditional<(_index<base>::value <= 67u), base69u, base68u>::type, typename _conditional<(_index<base>::value <= 68u), base70u, base69u>::type, typename _conditional<(_index<base>::value <= 69u), base71u, base70u>::type, typename _conditional<(_index<base>::value <= 70u), base72u, base71u>::type, typename _conditional<(_index<base>::value <= 71u), base73u, base72u>::type, typename _conditional<(_index<base>::value <= 72u), base74u, base73u>::type, typename _conditional<(_index<base>::value <= 73u), base75u, base74u>::type, typename _conditional<(_index<base>::value <= 74u), base76u, base75u>::type, typename _conditional<(_index<base>::value <= 75u), base77u, base76u>::type, typename _conditional<(_index<base>::value <= 76u), base78u, base77u>::type, typename _conditional<(_index<base>::value <= 77u), base79u, base78u>::type, typename _conditional<(_index<base>::value <= 78u), base80u, base79u>::type, typename _conditional<(_index<base>::value <= 79u), base81u, base80u>::type, typename _conditional<(_index<base>::value <= 80u), base82u, base81u>::type, typename _conditional<(_index<base>::value <= 81u), base83u, base82u>::type, typename _conditional<(_index<base>::value <= 82u), base84u, base83u>::type, typename _conditional<(_index<base>::value <= 83u), base85u, base84u>::type, typename _conditional<(_index<base>::value <= 84u), base86u, base85u>::type, typename _conditional<(_index<base>::value <= 85u), base87u, base86u>::type, typename _conditional<(_index<base>::value <= 86u), base88u, base87u>::type, typename _conditional<(_index<base>::value <= 87u), base89u, base88u>::type, typename _conditional<(_index<base>::value <= 88u), base90u, base89u>::type, typename _conditional<(_index<base>::value <= 89u), base91u, base90u>::type, typename _conditional<(_index<base>::value <= 90u), base92u, base91u>::type, typename _conditional<(_index<base>::value <= 91u), base93u, base92u>::type, typename _conditional<(_index<base>::value <= 92u), base94u, base93u>::type, typename _conditional<(_index<base>::value <= 93u), base95u, base94u>::type, typename _conditional<(_index<base>::value <= 94u), base96u, base95u>::type, typename _conditional<(_index<base>::value <= 95u), base97u, base96u>::type, typename _conditional<(_index<base>::value <= 96u), base98u, base97u>::type, typename _conditional<(_index<base>::value <= 97u), base99u, base98u>::type, typename _conditional<(_index<base>::value <= 98u), base100u, base99u>::type, typename _conditional<(_index<base>::value <= 99u), base101u, base100u>::type, typename _conditional<(_index<base>::value <= 100u), base102u, base101u>::type, typename _conditional<(_index<base>::value <= 101u), base103u, base102u>::type, typename _conditional<(_index<base>::value <= 102u), base104u, base103u>::type, typename _conditional<(_index<base>::value <= 103u), base105u, base104u>::type, typename _conditional<(_index<base>::value <= 104u), base106u, base105u>::type, typename _conditional<(_index<base>::value <= 105u), base107u, base106u>::type, typename _conditional<(_index<base>::value <= 106u), base108u, base107u>::type, typename _conditional<(_index<base>::value <= 107u), base109u, base108u>::type, typename _conditional<(_index<base>::value <= 108u), base110u, base109u>::type, typename _conditional<(_index<base>::value <= 109u), base111u, base110u>::type, typename _conditional<(_index<base>::value <= 110u), base112u, base111u>::type, typename _conditional<(_index<base>::value <= 111u), base113u, base112u>::type, typename _conditional<(_index<base>::value <= 112u), base114u, base113u>::type, typename _conditional<(_index<base>::value <= 113u), base115u, base114u>::type, typename _conditional<(_index<base>::value <= 114u), base116u, base115u>::type, typename _conditional<(_index<base>::value <= 115u), base117u, base116u>::type, typename _conditional<(_index<base>::value <= 116u), base118u, base117u>::type, typename _conditional<(_index<base>::value <= 117u), base119u, base118u>::type, typename _conditional<(_index<base>::value <= 118u), base120u, base119u>::type, typename _conditional<(_index<base>::value <= 119u), base121u, base120u>::type, typename _conditional<(_index<base>::value <= 120u), base122u, base121u>::type, typename _conditional<(_index<base>::value <= 121u), base123u, base122u>::type, typename _conditional<(_index<base>::value <= 122u), base124u, base123u>::type, typename _conditional<(_index<base>::value <= 123u), base125u, base124u>::type, typename _conditional<(_index<base>::value <= 124u), base126u, base125u>::type, typename _conditional<(_index<base>::value <= 125u), base127u, base126u>::type, typename _conditional<(_index<base>::value <= 126u), null, base127u>::type>,
                collection<base1u, base2u, base3u, base4u, base5u, base6u, base7u, base8u, base9u, base10u, base11u, base12u, base13u, base14u, base15u, base16u, base17u, base18u, base19u, base20u, base21u, base22u, base23u, base24u, base25u, base26u, base27u, base28u, base29u, base30u, base31u, base32u, base33u, base34u, base35u, base36u, base37u, base38u, base39u, base40u, base41u, base42u, base43u, base44u, base45u, base46u, base47u, base48u, base49u, base50u, base51u, base52u, base53u, base54u, base55u, base56u, base57u, base58u, base59u, base60u, base61u, base62u, base63u, base64u, base65u, base66u, base67u, base68u, base69u, base70u, base71u, base72u, base73u, base74u, base75u, base76u, base77u, base78u, base79u, base80u, base81u, base82u, base83u, base84u, base85u, base86u, base87u, base88u, base89u, base90u, base91u, base92u, base93u, base94u, base95u, base96u, base97u, base98u, base99u, base100u, base101u, base102u, base103u, base104u, base105u, base106u, base107u, base108u, base109u, base110u, base111u, base112u, base113u, base114u, base115u, base116u, base117u, base118u, base119u, base120u, base121u, base122u, base123u, base124u, base125u, base126u, base127u>
              >::type type;
            };

            // ...
            template <std::size_t count>
            struct shrink final {
              typedef collection<typename _conditional<(length > count and (length - count) > 0u), base1u, null>::type, typename _conditional<(length > count and (length - count) > 1u), base2u, null>::type, typename _conditional<(length > count and (length - count) > 2u), base3u, null>::type, typename _conditional<(length > count and (length - count) > 3u), base4u, null>::type, typename _conditional<(length > count and (length - count) > 4u), base5u, null>::type, typename _conditional<(length > count and (length - count) > 5u), base6u, null>::type, typename _conditional<(length > count and (length - count) > 6u), base7u, null>::type, typename _conditional<(length > count and (length - count) > 7u), base8u, null>::type, typename _conditional<(length > count and (length - count) > 8u), base9u, null>::type, typename _conditional<(length > count and (length - count) > 9u), base10u, null>::type, typename _conditional<(length > count and (length - count) > 10u), base11u, null>::type, typename _conditional<(length > count and (length - count) > 11u), base12u, null>::type, typename _conditional<(length > count and (length - count) > 12u), base13u, null>::type, typename _conditional<(length > count and (length - count) > 13u), base14u, null>::type, typename _conditional<(length > count and (length - count) > 14u), base15u, null>::type, typename _conditional<(length > count and (length - count) > 15u), base16u, null>::type, typename _conditional<(length > count and (length - count) > 16u), base17u, null>::type, typename _conditional<(length > count and (length - count) > 17u), base18u, null>::type, typename _conditional<(length > count and (length - count) > 18u), base19u, null>::type, typename _conditional<(length > count and (length - count) > 19u), base20u, null>::type, typename _conditional<(length > count and (length - count) > 20u), base21u, null>::type, typename _conditional<(length > count and (length - count) > 21u), base22u, null>::type, typename _conditional<(length > count and (length - count) > 22u), base23u, null>::type, typename _conditional<(length > count and (length - count) > 23u), base24u, null>::type, typename _conditional<(length > count and (length - count) > 24u), base25u, null>::type, typename _conditional<(length > count and (length - count) > 25u), base26u, null>::type, typename _conditional<(length > count and (length - count) > 26u), base27u, null>::type, typename _conditional<(length > count and (length - count) > 27u), base28u, null>::type, typename _conditional<(length > count and (length - count) > 28u), base29u, null>::type, typename _conditional<(length > count and (length - count) > 29u), base30u, null>::type, typename _conditional<(length > count and (length - count) > 30u), base31u, null>::type, typename _conditional<(length > count and (length - count) > 31u), base32u, null>::type, typename _conditional<(length > count and (length - count) > 32u), base33u, null>::type, typename _conditional<(length > count and (length - count) > 33u), base34u, null>::type, typename _conditional<(length > count and (length - count) > 34u), base35u, null>::type, typename _conditional<(length > count and (length - count) > 35u), base36u, null>::type, typename _conditional<(length > count and (length - count) > 36u), base37u, null>::type, typename _conditional<(length > count and (length - count) > 37u), base38u, null>::type, typename _conditional<(length > count and (length - count) > 38u), base39u, null>::type, typename _conditional<(length > count and (length - count) > 39u), base40u, null>::type, typename _conditional<(length > count and (length - count) > 40u), base41u, null>::type, typename _conditional<(length > count and (length - count) > 41u), base42u, null>::type, typename _conditional<(length > count and (length - count) > 42u), base43u, null>::type, typename _conditional<(length > count and (length - count) > 43u), base44u, null>::type, typename _conditional<(length > count and (length - count) > 44u), base45u, null>::type, typename _conditional<(length > count and (length - count) > 45u), base46u, null>::type, typename _conditional<(length > count and (length - count) > 46u), base47u, null>::type, typename _conditional<(length > count and (length - count) > 47u), base48u, null>::type, typename _conditional<(length > count and (length - count) > 48u), base49u, null>::type, typename _conditional<(length > count and (length - count) > 49u), base50u, null>::type, typename _conditional<(length > count and (length - count) > 50u), base51u, null>::type, typename _conditional<(length > count and (length - count) > 51u), base52u, null>::type, typename _conditional<(length > count and (length - count) > 52u), base53u, null>::type, typename _conditional<(length > count and (length - count) > 53u), base54u, null>::type, typename _conditional<(length > count and (length - count) > 54u), base55u, null>::type, typename _conditional<(length > count and (length - count) > 55u), base56u, null>::type, typename _conditional<(length > count and (length - count) > 56u), base57u, null>::type, typename _conditional<(length > count and (length - count) > 57u), base58u, null>::type, typename _conditional<(length > count and (length - count) > 58u), base59u, null>::type, typename _conditional<(length > count and (length - count) > 59u), base60u, null>::type, typename _conditional<(length > count and (length - count) > 60u), base61u, null>::type, typename _conditional<(length > count and (length - count) > 61u), base62u, null>::type, typename _conditional<(length > count and (length - count) > 62u), base63u, null>::type, typename _conditional<(length > count and (length - count) > 63u), base64u, null>::type, typename _conditional<(length > count and (length - count) > 64u), base65u, null>::type, typename _conditional<(length > count and (length - count) > 65u), base66u, null>::type, typename _conditional<(length > count and (length - count) > 66u), base67u, null>::type, typename _conditional<(length > count and (length - count) > 67u), base68u, null>::type, typename _conditional<(length > count and (length - count) > 68u), base69u, null>::type, typename _conditional<(length > count and (length - count) > 69u), base70u, null>::type, typename _conditional<(length > count and (length - count) > 70u), base71u, null>::type, typename _conditional<(length > count and (length - count) > 71u), base72u, null>::type, typename _conditional<(length > count and (length - count) > 72u), base73u, null>::type, typename _conditional<(length > count and (length - count) > 73u), base74u, null>::type, typename _conditional<(length > count and (length - count) > 74u), base75u, null>::type, typename _conditional<(length > count and (length - count) > 75u), base76u, null>::type, typename _conditional<(length > count and (length - count) > 76u), base77u, null>::type, typename _conditional<(length > count and (length - count) > 77u), base78u, null>::type, typename _conditional<(length > count and (length - count) > 78u), base79u, null>::type, typename _conditional<(length > count and (length - count) > 79u), base80u, null>::type, typename _conditional<(length > count and (length - count) > 80u), base81u, null>::type, typename _conditional<(length > count and (length - count) > 81u), base82u, null>::type, typename _conditional<(length > count and (length - count) > 82u), base83u, null>::type, typename _conditional<(length > count and (length - count) > 83u), base84u, null>::type, typename _conditional<(length > count and (length - count) > 84u), base85u, null>::type, typename _conditional<(length > count and (length - count) > 85u), base86u, null>::type, typename _conditional<(length > count and (length - count) > 86u), base87u, null>::type, typename _conditional<(length > count and (length - count) > 87u), base88u, null>::type, typename _conditional<(length > count and (length - count) > 88u), base89u, null>::type, typename _conditional<(length > count and (length - count) > 89u), base90u, null>::type, typename _conditional<(length > count and (length - count) > 90u), base91u, null>::type, typename _conditional<(length > count and (length - count) > 91u), base92u, null>::type, typename _conditional<(length > count and (length - count) > 92u), base93u, null>::type, typename _conditional<(length > count and (length - count) > 93u), base94u, null>::type, typename _conditional<(length > count and (length - count) > 94u), base95u, null>::type, typename _conditional<(length > count and (length - count) > 95u), base96u, null>::type, typename _conditional<(length > count and (length - count) > 96u), base97u, null>::type, typename _conditional<(length > count and (length - count) > 97u), base98u, null>::type, typename _conditional<(length > count and (length - count) > 98u), base99u, null>::type, typename _conditional<(length > count and (length - count) > 99u), base100u, null>::type, typename _conditional<(length > count and (length - count) > 100u), base101u, null>::type, typename _conditional<(length > count and (length - count) > 101u), base102u, null>::type, typename _conditional<(length > count and (length - count) > 102u), base103u, null>::type, typename _conditional<(length > count and (length - count) > 103u), base104u, null>::type, typename _conditional<(length > count and (length - count) > 104u), base105u, null>::type, typename _conditional<(length > count and (length - count) > 105u), base106u, null>::type, typename _conditional<(length > count and (length - count) > 106u), base107u, null>::type, typename _conditional<(length > count and (length - count) > 107u), base108u, null>::type, typename _conditional<(length > count and (length - count) > 108u), base109u, null>::type, typename _conditional<(length > count and (length - count) > 109u), base110u, null>::type, typename _conditional<(length > count and (length - count) > 110u), base111u, null>::type, typename _conditional<(length > count and (length - count) > 111u), base112u, null>::type, typename _conditional<(length > count and (length - count) > 112u), base113u, null>::type, typename _conditional<(length > count and (length - count) > 113u), base114u, null>::type, typename _conditional<(length > count and (length - count) > 114u), base115u, null>::type, typename _conditional<(length > count and (length - count) > 115u), base116u, null>::type, typename _conditional<(length > count and (length - count) > 116u), base117u, null>::type, typename _conditional<(length > count and (length - count) > 117u), base118u, null>::type, typename _conditional<(length > count and (length - count) > 118u), base119u, null>::type, typename _conditional<(length > count and (length - count) > 119u), base120u, null>::type, typename _conditional<(length > count and (length - count) > 120u), base121u, null>::type, typename _conditional<(length > count and (length - count) > 121u), base122u, null>::type, typename _conditional<(length > count and (length - count) > 122u), base123u, null>::type, typename _conditional<(length > count and (length - count) > 123u), base124u, null>::type, typename _conditional<(length > count and (length - count) > 124u), base125u, null>::type, typename _conditional<(length > count and (length - count) > 125u), base126u, null>::type, typename _conditional<(length > count and (length - count) > 126u), base127u, null>::type> type;
            };

            // ...
            template <std::size_t begin, std::size_t end = length>
            struct slice final {
              private:
                typedef constant<bool, (begin <= end and begin <= length), true> invalid_collection_indexes;

              public:
                static_assert(invalid_collection_indexes::value, "Out-of-bounds slicing of `collection<...>` trait");
                typedef typename _slice<(begin < length ? begin : length)>::type::template shrink<length - (end < length ? end : length)>::type type;
            };

            /* ... */
            typedef typename _at<0u>                     ::type first;
            typedef typename _at<length - (0u != length)>::type last;
            typedef typename shrink<1u>                  ::type pop;
            typedef typename _reverse<>                  ::type reverse;

            // collection::concatenate;
        };
      #endif

      // ... ->> Evaluates if type is (based on) an integer type
      template <typename base, bool enumerable>
      struct is_integer final {
        static bool const value = conditional<enumerable, constant<bool, false, true>, is_enum<base> >::type::value;
      };

      template <bool enumerable>
      struct is_integer<bool, enumerable> final {
        static bool const value = true;
      };

      template <bool enumerable>
      struct is_integer<char, enumerable> final {
        static bool const value = true;
      };

      template <bool enumerable>
      struct is_integer<int, enumerable> final {
        static bool const value = true;
      };

      template <bool enumerable>
      struct is_integer<long, enumerable> final {
        static bool const value = true;
      };

      template <bool enumerable>
      struct is_integer<short, enumerable> final {
        static bool const value = true;
      };

      template <bool enumerable>
      struct is_integer<signed char, enumerable> final {
        static bool const value = true;
      };

      template <bool enumerable>
      struct is_integer<unsigned char, enumerable> final {
        static bool const value = true;
      };

      template <bool enumerable>
      struct is_integer<unsigned int, enumerable> final {
        static bool const value = true;
      };

      template <bool enumerable>
      struct is_integer<unsigned long, enumerable> final {
        static bool const value = true;
      };

      template <bool enumerable>
      struct is_integer<unsigned short, enumerable> final {
        static bool const value = true;
      };

      template <bool enumerable>
      struct is_integer<wchar_t, enumerable> final {
        static bool const value = true;
      };

      #if CPP_VERSION >= 2011uL
        template <bool enumerable>
        struct is_integer<long long, enumerable> final {
          static bool const value = true;
        };

        template <bool enumerable>
        struct is_integer<unsigned long long, enumerable> final {
          static bool const value = true;
        };
      #endif

      #ifdef __cpp_char8_t // --> 201811L
        template <bool enumerable>
        struct is_integer<char8_t /* --> unsigned char */, enumerable> final {
          static bool const value = true;
        };
      #endif

      #ifdef __cpp_lib_byte // --> 201603L
        template <bool enumerable>
        struct is_integer<std::byte /* --> unsigned char */, enumerable> final {
          static bool const value = true;
        };
      #endif

      #ifdef __cpp_unicode_characters // --> 200704L
        template <bool enumerable>
        struct is_integer<char16_t /* --> std::uint_least16_t */, enumerable> final {
          static bool const value = true;
        };

        template <bool enumerable>
        struct is_integer<char32_t /* --> std::uint_least32_t */, enumerable> final {
          static bool const value = true;
        };
      #endif

      #ifdef int128_t
        template <bool enumerable>
        struct is_integer<int128_t, enumerable> final {
          static bool const value = true;
        };
      #endif

      #ifdef uint128_t
        template <bool enumerable>
        struct is_integer<uint128_t, enumerable> final {
          static bool const value = true;
        };
      #endif

      template <std::size_t width>
      struct is_integer<bit<width>, false> final {
        static bool const value = true;
      };

      template <typename base, bool enumerable>
      struct is_integer<base const, enumerable> final {
        static bool const value = is_integer<base, enumerable>::value;
      };

      template <typename base, bool enumerable>
      struct is_integer<base const volatile, enumerable> final {
        static bool const value = is_integer<base, enumerable>::value;
      };

      template <typename base, bool enumerable>
      struct is_integer<base volatile, enumerable> final {
        static bool const value = is_integer<base, enumerable>::value;
      };

      // ... ->> Constant of specified type preferably instantiated at compile-time
      #ifdef __cpp_constexpr // --> 200704L
        template <typename base, base constantValue, bool = false>
        struct constant final {
          constexpr static base value = constantValue;
        };
      #else
        template <typename base, base constantValue, bool = is_integer<base>::value>
        struct constant final {
          static base const value = constantValue;
        };

        template <typename base, base constantValue>
        struct constant<base, constantValue, false> final {
          static base const value;
        };
          template <typename base, base value>
          base const constant<base, value, false>::value = value;
      #endif

      // ... ->> Type signedness
      template <typename>
      struct is_signed final {
        static bool const value = false;
      };

      template <>
      struct is_signed<signed char> final {
        static bool const value = true;
      };

      template <>
      struct is_signed<signed int> final {
        static bool const value = true;
      };

      template <>
      struct is_signed<signed long> final {
        static bool const value = true;
      };

      template <>
      struct is_signed<signed short> final {
        static bool const value = true;
      };

      #if CHAR_MIN - 0
        template <>
        struct is_signed<char> final {
          static bool const value = true;
        };
      #endif

      #if CPP_VERSION >= 2011uL
        template <>
        struct is_signed<signed long long> final {
          static bool const value = true;
        };
      #endif

      #ifdef int128_t
        template <>
        struct is_signed<int128_t> final {
          static bool const value = true;
        };
      #endif

      // ... ->> Enumeration type diagnostics
      struct enumtypeinfo final {
        template <typename>
        friend struct enuminfo;

        private:
          typedef unsigned char      metadata_t;
          typedef bool               signedness_t;
          typedef uintmax_template_t size_t;

          /* ... */
          static unsigned char const METADATA_WIDTH   = 3u;
          static unsigned char const SIGNEDNESS_WIDTH = 1u;
          static unsigned char const SIZE_WIDTH       = (CHAR_BIT * sizeof(size_t)) - (METADATA_WIDTH + SIGNEDNESS_WIDTH);

          /* ... */
          template <typename, sfinaeptr_t = sfinaeptr> struct metadataof                  final { static metadata_t const value = 0u; };
          template <sfinaeptr_t sfinae>                struct metadataof<bool,    sfinae> final { static metadata_t const value = 1u; };
          template <sfinaeptr_t sfinae>                struct metadataof<char,    sfinae> final { static metadata_t const value = 2u; };
          template <sfinaeptr_t sfinae>                struct metadataof<wchar_t, sfinae> final { static metadata_t const value = 1u; };
          #ifdef __cpp_char8_t // --> 201811L
            template <sfinaeptr_t sfinae> struct metadataof<char8_t, sfinae> final { static metadata_t const value = 3u; };
          #endif
          #ifdef __cpp_lib_byte // --> 201603L
            template <sfinaeptr_t sfinae> struct metadataof<std::byte, sfinae> final { static metadata_t const value = 4u; };
          #endif
          #ifdef __cpp_unicode_characters // --> 200704L
            template <sfinaeptr_t sfinae> struct metadataof<char16_t, sfinae> final { static metadata_t const value = 1u; };
            template <sfinaeptr_t sfinae> struct metadataof<char32_t, sfinae> final { static metadata_t const value = 1u; };
          #endif

          // ...
          template <std::size_t base>
          struct decode final {
            private:
              static metadata_t   const metadata   = (base >> 0u)                                  & ((((1u << (METADATA_WIDTH   - 1u)) - 1u) << 1u) + 1u);
              static signedness_t const signedness = (base >> METADATA_WIDTH)                      & ((((1u << (SIGNEDNESS_WIDTH - 1u)) - 1u) << 1u) + 1u);
              static size_t       const size       = (base >> (METADATA_WIDTH + SIGNEDNESS_WIDTH)) & ((((1u << (SIZE_WIDTH       - 1u)) - 1u) << 1u) + 1u);

            public:
              typedef
                typename conditional<metadata == metadataof<bool>   ::value and size == sizeof(bool),    bool,
                typename conditional<metadata == metadataof<char>   ::value and size == sizeof(char),    char,
                typename conditional<metadata == metadataof<wchar_t>::value and size == sizeof(wchar_t), wchar_t,

                typename conditional<
                #ifdef __cpp_char8_t // --> 201811L
                  metadata == metadataof<char8_t>::value and size == sizeof(char8_t), char8_t,
                #else
                  false, null,
                #endif

                typename conditional<
                #ifdef __cpp_lib_byte // --> 201603L
                  metadata == metadataof<std::byte>::value and size == sizeof(std::byte), std::byte,
                #else
                  false, null,
                #endif

                typename conditional<
                #ifdef __cpp_unicode_characters // --> 200704L
                  metadata == metadataof<char16_t>::value and size == sizeof(char16_t), char16_t,
                #else
                  false, null,
                #endif

                typename conditional<
                #ifdef __cpp_unicode_characters // --> 200704L
                  metadata == metadataof<char32_t>::value and size == sizeof(char32_t), char32_t,
                #else
                  false, null,
                #endif

                  typename conditional<signedness, typename int_t<size>::type, typename uint_t<size>::type>::type
                >::type>::type>::type>::type>::type>::type>::type
              type;
          };

          // ...
          template <typename base, metadata_t metadata = 0u>
          struct encode final {
            private:
              typedef constant<bool, 0u == (sizeof(base) >> SIZE_WIDTH)> unrepresentable_enum_underlying_type;
              static_assert(unrepresentable_enum_underlying_type::value, "Expected enumeration underlying type to be of smaller size");

            public:
              static std::size_t const value = (
                ((0u != metadata ? metadata : metadataof<base>::value & ((((1u << (METADATA_WIDTH   - 1u)) - 1u) << 1u) + 1u)) << 0u)             |
                ((static_cast<unsigned char>(is_signed<base>::value)  & ((((1u << (SIGNEDNESS_WIDTH - 1u)) - 1u) << 1u) + 1u)) << METADATA_WIDTH) |
                ((sizeof(base)                                        & ((((1u << (SIZE_WIDTH       - 1u)) - 1u) << 1u) + 1u)) << (METADATA_WIDTH + SIGNEDNESS_WIDTH))
              );
          };

          /* ... ->> Disambiguate underlying type of enumeration via overload resolution */
          constfunc(true) static byte (&(typeof)(bool           const) noexcept)[enumtypeinfo::encode<bool>          ::value];
          constfunc(true) static byte (&(typeof)(char           const) noexcept)[enumtypeinfo::encode<char>          ::value];
          constfunc(true) static byte (&(typeof)(int            const) noexcept)[enumtypeinfo::encode<int>           ::value];
          constfunc(true) static byte (&(typeof)(long           const) noexcept)[enumtypeinfo::encode<long>          ::value];
          constfunc(true) static byte (&(typeof)(short          const) noexcept)[enumtypeinfo::encode<short>         ::value];
          constfunc(true) static byte (&(typeof)(signed char    const) noexcept)[enumtypeinfo::encode<signed char>   ::value];
          constfunc(true) static byte (&(typeof)(unsigned       const) noexcept)[enumtypeinfo::encode<unsigned>      ::value];
          constfunc(true) static byte (&(typeof)(unsigned char  const) noexcept)[enumtypeinfo::encode<unsigned char> ::value];
          constfunc(true) static byte (&(typeof)(unsigned long  const) noexcept)[enumtypeinfo::encode<unsigned long> ::value];
          constfunc(true) static byte (&(typeof)(unsigned short const) noexcept)[enumtypeinfo::encode<unsigned short>::value];
          constfunc(true) static byte (&(typeof)(wchar_t        const) noexcept)[enumtypeinfo::encode<wchar_t>       ::value];
          #if CPP_VERSION >= 2011uL
            constfunc(true) static byte (&(typeof)(long long          const) noexcept)[enumtypeinfo::encode<long long>         ::value];
            constfunc(true) static byte (&(typeof)(unsigned long long const) noexcept)[enumtypeinfo::encode<unsigned long long>::value];
          #endif
          #ifdef __cpp_char8_t // --> 201811L
            constfunc(true) static byte (&(typeof)(char8_t const) noexcept)[enumtypeinfo::encode<char8_t>::value];
          #endif
          #ifdef __cpp_lib_byte // --> 201603L
            constfunc(true) static byte (&(typeof)(std::byte const) noexcept)[enumtypeinfo::encode<std::byte>::value];
          #endif
          #ifdef __cpp_unicode_characters // --> 200704L
            constfunc(true) static byte (&(typeof)(char16_t const) noexcept)[enumtypeinfo::encode<char16_t>::value];
            constfunc(true) static byte (&(typeof)(char32_t const) noexcept)[enumtypeinfo::encode<char32_t>::value];
          #endif
          #ifdef int128_t
            constfunc(true) static byte (&(typeof)(int128_t const) noexcept)[enumtypeinfo::encode<int128_t>::value];
          #endif
          #ifdef uint128_t
            constfunc(true) static byte (&(typeof)(uint128_t const) noexcept)[enumtypeinfo::encode<uint128_t>::value];
          #endif
          constfunc(true) static byte (&(typeof)(...) noexcept)[enumtypeinfo::encode<uintmax_t>::value + 1u];
      };

      template <typename base>
      struct enuminfo final {
        typedef typename enumtypeinfo::template decode<sizeof((enumtypeinfo::typeof)(instanceof<base>())) / sizeof(byte)>::type type;
        static bool const value =
          #if CPP_VERSION >= 2011uL
            std::is_enum<base>::value or
          #elif CPP_COMPILER == CPP_MSVC_COMPILER
            __is_enum(base) or
          #elif CPP_COMPILER == CPP_CIRCLE_COMPILER or CPP_COMPILER == CPP_CLANG_COMPILER or CPP_COMPILER == CPP_GNUC_COMPILER or CPP_COMPILER == CPP_INTEL_COMPILER or CPP_COMPILER == CPP_LLVM_COMPILER or CPP_COMPILER == CPP_NVCC_COMPILER
          # ifdef __has_builtin // --> `__is_enum(...)` may still exist otherwise
          #   if __has_builtin(__is_enum)
                __is_enum(base) or
          #   endif
          # endif
          #endif
        not (classinfo<base>::value or is_integer<base, true>::value);
      };

      // ... ->> Fastest floating-point type with at least specified size
      template <std::size_t size>
      struct float_fast_t final {
        typedef typename float_fast_width_t<CHAR_BIT * size>::type type;
      };

      // ... ->> Fastest floating-point type with at least specified bit width
      template <std::size_t width>
      struct float_fast_width_t final {
        typedef typename conditional<
          width <= widthof(double()), double, // ->> Assume a `double` is the "fastest" type
          typename float_least_width_t<width>::type
        >::type type;
      };

      // ... ->> Smallest floating-point type with at least specified size
      template <std::size_t size>
      struct float_least_t final {
        typedef typename float_least_width_t<CHAR_BIT * size>::type type;
      };

      // ... ->> Smallest floating-point type with at least specified bit width
      template <std::size_t width>
      struct float_least_width_t final {
        typedef
          typename conditional<width <= widthof(static_cast<float>      (0.0)), float,
          typename conditional<width <= widthof(static_cast<double>     (0.0)), double,
          typename conditional<width <= widthof(static_cast<long double>(0.0)), long double,
          #ifndef float16_t
            void
          #else
            typename conditional<width <= widthof(static_cast<float16_t>(0.0)), float16_t,
            #ifndef float32_t
              void
            #else
              typename conditional<width <= widthof(static_cast<float32_t>(0.0)), float32_t,
              #ifndef float64_t
                void
              #else
                typename conditional<width <= widthof(static_cast<float64_t>(0.0)), float64_t,
                #ifndef float128_t
                  void
                #else
                  typename conditional<width <= widthof(static_cast<float128_t>(0.0)), float128_t, void>::type
                #endif
                >::type
              #endif
              >::type
            #endif
            >::type
          #endif
          >::type>::type>::type
        type;
      };

      // ... ->> Floating-point type of exact specified size
      template <std::size_t size>
      struct float_t final {
        typedef typename float_width_t<CHAR_BIT * size>::type type;
      };

      // ... ->> Floating-point type of exact specified bit width
      template <std::size_t width>
      struct float_width_t final {
        private:
          template <typename base, bool = is_same<base, void>::value>
          struct valueof final {
            typedef typename conditional<width == widthof(static_cast<base>(0.0)), base, void>::type type;
          };

          template <typename base>
          struct valueof<base, true> final {
            typedef base type;
          };

        public:
          typedef typename valueof<typename float_least_width_t<width>::type>::type type;
      };

      // ... ->> Function type diagnostics
      template <typename base>
      struct functioninfo final {
        static bool const value = false;
      };

      #ifdef __cpp_variadic_templates // --> 200704L
        template <typename baseType, typename... bases>
        struct functioninfo<baseType (bases...)> final {
          template <std::size_t index>
          struct at final {};

          struct is_const    final { static bool const value = false; };
          struct is_volatile final { static bool const value = false; };

          typedef baseType base;

          static std::size_t const arity    = sizeof...(bases);
          static bool        const except   = false;
          static bool        const lvalued  = false;
          static bool        const rvalued  = false;
          static bool        const variadic = false;
        };

        #ifdef __cpp_noexcept_function_type // --> 201510L
        #endif
      #else
      #endif

      // ... ->> Fastest signed integer type with at least specified size
      template <std::size_t size>
      struct int_fast_t final {
        typedef typename int_fast_width_t<CHAR_BIT * size>::type type;
      };

      // ... ->> Fastest signed integer type with at least specified bit width
      template <std::size_t width>
      struct int_fast_width_t final {
        typedef typename signedof<typename uint_fast_width_t<width>::type>::type type;
      };

      // ... ->> Smallest signed integer type with at least specified size
      template <std::size_t size>
      struct int_least_t final {
        typedef typename int_least_width_t<CHAR_BIT * size>::type type;
      };

      // ... ->> Smallest signed integer type with at least specified bit width
      template <std::size_t width>
      struct int_least_width_t final {
        typedef typename signedof<typename uint_least_width_t<width>::type>::type type;
      };

      // ... ->> Signed integer type of exact specified size
      template <std::size_t size>
      struct int_t final {
        typedef typename int_width_t<CHAR_BIT * size>::type type;
      };

      // ... ->> Signed integer type of exact specified bit width
      template <std::size_t width>
      struct int_width_t final {
        typedef typename signedof<typename uint_width_t<width>::type>::type type;
      };

      // ... ->> Evaluates if type is a class or union type
      template <typename base>
      struct is_class final {
        static bool const value = classinfo<base>::value;
      };

      // ... ->> Type const-qualifier check
      template <typename base>
      struct is_const final {
        static bool const value = false;
      };

      template <typename base>
      struct is_const<base const> final {
        static bool const value = true;
      };

      // ... ->> Evaluates if type is an enumeration type
      template <typename base>
      struct is_enum final {
        static bool const value = enuminfo<base>::value;
      };

      // ... ->> Evaluates if type is a class or union type
      template <typename base>
      struct is_final final {
        static bool const value = not is_class<base>::value or not classinfo<base>::derivable;
      };

      // ... ->> Evaluates if type is a function type
      template <typename base>
      struct is_function final {
        static bool const value = functioninfo<base>::value; // --> not (is_const<base const>::value or is_reference<base>::value)
      };

      // ...
      template <typename>
      struct is_null final {
        static bool const value = false;
      };

      template <>
      struct is_null<null> final {
        static bool const value = true;
      };

      // ... ->> Type equality
      template <typename, typename>
      struct is_same final {
        static bool const value = false;
      };

      template <typename base>
      struct is_same<base, base> final {
        static bool const value = true;
      };

      // ... ->> Type (expression) similarity
      template <typename base>
      struct is_similar final {
        template <typename type>
        constfunc(true) static typename conditional<is_same<base const volatile, type const volatile>::value, boolean_true, boolean_false>::type (value)(type nodecay) noexcept;
      };

      template <typename base>
      struct is_similar<base&> final {
        template <typename type> constfunc(true) static typename conditional<is_same<base, type>               ::value, boolean_true, boolean_false>::type (value)(type&)                noexcept;
        template <typename type> constfunc(true) static typename conditional<is_same<base, type const>         ::value, boolean_true, boolean_false>::type (value)(type const&)          noexcept;
        template <typename type> constfunc(true) static typename conditional<is_same<base, type const volatile>::value, boolean_true, boolean_false>::type (value)(type const volatile&) noexcept;
        template <typename type> constfunc(true) static typename conditional<is_same<base, type       volatile>::value, boolean_true, boolean_false>::type (value)(type       volatile&) noexcept;
      };

      #ifdef __cpp_rvalue_references // --> 200610L
        template <typename base>
        struct is_similar<base&&> final {
          constfunc(true)                          static typename conditional<is_same<base, typename remove_const_volatile<base>::type>               ::value, boolean_true, boolean_false>::type (value)(typename remove_const_volatile<base>::type&&)                noexcept;
          constfunc(true)                          static typename conditional<is_same<base, typename remove_const_volatile<base>::type const>         ::value, boolean_true, boolean_false>::type (value)(typename remove_const_volatile<base>::type const&&)          noexcept;
          constfunc(true)                          static typename conditional<is_same<base, typename remove_const_volatile<base>::type const volatile>::value, boolean_true, boolean_false>::type (value)(typename remove_const_volatile<base>::type const volatile&&) noexcept;
          constfunc(true)                          static typename conditional<is_same<base, typename remove_const_volatile<base>::type       volatile>::value, boolean_true, boolean_false>::type (value)(typename remove_const_volatile<base>::type       volatile&&) noexcept;
          template <typename type> constfunc(true) static boolean_false                                                                                                                            (value)(type const volatile&)                                        noexcept;
        };
      #endif

      // ... ->> Evaluates if type is a union type
      template <typename base>
      struct is_union final {
        static bool const value = classinfo<base>::value and classinfo<base>::variant;
      };

      // ... ->> Type un-signedness
      template <typename>
      struct is_unsigned final {
        static bool const value = false;
      };

      template <>
      struct is_unsigned<unsigned char> final {
        static bool const value = true;
      };

      template <>
      struct is_unsigned<unsigned int> final {
        static bool const value = true;
      };

      template <>
      struct is_unsigned<unsigned long> final {
        static bool const value = true;
      };

      template <>
      struct is_unsigned<unsigned short> final {
        static bool const value = true;
      };

      #if CHAR_MIN - 0
      #else
        template <>
        struct is_unsigned<char> final {
          static bool const value = true;
        };
      #endif

      #if CPP_VERSION >= 2011uL
        template <>
        struct is_unsigned<unsigned long long> final {
          static bool const value = true;
        };
      #endif

      #ifdef uint128_t
        template <>
        struct is_unsigned<uint128_t> final {
          static bool const value = true;
        };
      #endif

      // ... ->> Type volatile-qualifier check
      template <typename base>
      struct is_volatile final {
        static bool const value = false;
      };

      template <typename base>
      struct is_volatile<base volatile> final {
        static bool const value = true;
      };

      // ...
      template <typename>
      struct maxof {};

      // ...
      template <typename>
      struct minof final {};

      // ...
      template <typename>
      struct nilof final {};

      // ... ->> Operation diagnostics
      struct opinfo final {
        struct membered final {};

        // ...
        struct nonmembered final {};

        // ...
        struct nonoverloaded final {};

        // ... ->> Dis-junction of `member` and `nonmember` traits
        struct overloaded final {};
      };

      // ... ->> Type topmost const-qualifier removal
      template <typename base>
      struct remove_const final {
        typedef base type;
      };

      template <typename base>
      struct remove_const<base const> final {
        typedef base type;
      };

      // ... ->> Type topmost cv-qualifier removal
      template <typename base>
      struct remove_const_volatile final {
        typedef base type;
      };

      template <typename base>
      struct remove_const_volatile<base const> final {
        typedef base type;
      };

      template <typename base>
      struct remove_const_volatile<base const volatile> final {
        typedef base type;
      };

      template <typename base>
      struct remove_const_volatile<base volatile> final {
        typedef base type;
      };

      // ... ->> Type topmost volatile-qualifier removal
      template <typename base>
      struct remove_volatile final {
        typedef base type;
      };

      template <typename base>
      struct remove_volatile<base volatile> final {
        typedef base type;
      };

      // ... ->> Sign integer type
      template <typename base>
      struct signedof final {
        typedef base type;
      };

      template <>
      struct signedof<unsigned char> final {
        typedef signed char type;
      };

      template <>
      struct signedof<unsigned int> final {
        typedef signed int type;
      };

      template <>
      struct signedof<unsigned long> final {
        typedef signed long type;
      };

      #if CPP_VERSION >= 2011uL
        template <>
        struct signedof<unsigned long long> final {
          typedef signed long long type;
        };
      #endif

      #ifdef uint128_t
        template <>
        struct signedof<uint128_t> final {
          #ifdef int128_t
            typedef int128_t type;
          #else
            typedef void type;
          #endif
        };
      #endif

      // ... ->> Fastest unsigned integer type with at least specified size
      template <std::size_t size>
      struct uint_fast_t final {
        typedef typename uint_fast_width_t<CHAR_BIT * size>::type type;
      };

      // ... ->> Fastest unsigned integer type with at least specified bit width
      template <std::size_t width>
      struct uint_fast_width_t final {
        typedef
          typename conditional<width <= widthof(static_cast<uint_fast8_t> (0u)), uint_fast8_t,
          typename conditional<width <= widthof(static_cast<uint_fast16_t>(0u)), uint_fast16_t,
          typename conditional<width <= widthof(static_cast<uint_fast32_t>(0u)), uint_fast32_t,
          typename conditional<width <= widthof(static_cast<uint_fast64_t>(0u)), uint_fast64_t,
          typename conditional<width <= widthof(static_cast<unsigned>     (0u)), unsigned,
          #ifndef uint128_t
            void
          #else
            typename conditional<width <= widthof(static_cast<uint128_t>(0u)), uint128_t, void>::type
          #endif
          >::type>::type>::type>::type>::type
        type;
      };

      // ... ->> Smallest unsigned integer type with at least specified size
      template <std::size_t size>
      struct uint_least_t final {
        typedef typename uint_least_width_t<CHAR_BIT * size>::type type;
      };

      // ... ->> Smallest unsigned integer type with at least specified bit width
      template <std::size_t width>
      struct uint_least_width_t final {
        typedef
          typename conditional<width <= widthof(static_cast<unsigned char> (0u)), unsigned char,
          typename conditional<width <= widthof(static_cast<unsigned short>(0u)), unsigned short,
          typename conditional<width <= widthof(static_cast<unsigned int>  (0u)), unsigned int,
          typename conditional<width <= widthof(static_cast<unsigned long> (0u)), unsigned long,
          #if CPP_VERSION < 2011uL
            void
          #else
            typename conditional<width <= widthof(static_cast<unsigned long long>(0u)), unsigned long long,
            #ifndef uint128_t
              void
            #else
              typename conditional<width <= widthof(static_cast<uint128_t>(0u)), uint128_t, void>::type
            #endif
            >::type
          #endif
          >::type>::type>::type>::type
        type;
      };

      // ... ->> Unsigned integer type of exact specified size
      template <std::size_t size>
      struct uint_t final {
        typedef typename uint_width_t<CHAR_BIT * size>::type type;
      };

      // ... ->> Unsigned integer type of exact specified bit width
      template <std::size_t width>
      struct uint_width_t final {
        private:
          template <typename base, bool = is_same<base, void>::value>
          struct valueof final {
            typedef typename conditional<width == widthof(static_cast<base>(0u)), base, void>::type type;
          };

          template <typename base>
          struct valueof<base, true> final {
            typedef base type;
          };

        public:
          typedef typename valueof<typename uint_least_width_t<width>::type>::type type;
      };

      // ... ->> Unsign integer type
      template <typename base>
      struct unsignedof final {
        typedef base type;
      };

      template <>
      struct unsignedof<signed char> final {
        typedef unsigned char type;
      };

      template <>
      struct unsignedof<signed int> final {
        typedef unsigned int type;
      };

      template <>
      struct unsignedof<signed long> final {
        typedef unsigned long type;
      };

      #if CPP_VERSION >= 2011uL
        template <>
        struct unsignedof<signed long long> final {
          typedef unsigned long long type;
        };
      #endif

      #ifdef int128_t
        template <>
        struct unsignedof<int128_t> final {
          #ifdef uint128_t
            typedef uint128_t type;
          #else
            typedef void type;
          #endif
        };
      #endif

      /* Alias > ... */
      typedef float_fast_width_t <8u>  ::type                                 float_fast8_t;
      typedef float_fast_width_t <16u> ::type                                 float_fast16_t;
      typedef float_fast_width_t <32u> ::type                                 float_fast32_t;
      typedef float_fast_width_t <64u> ::type                                 float_fast64_t;
      typedef float_fast_width_t <128u>::type                                 float_fast128_t;
      typedef float_least_width_t<8u>  ::type                                 float_least8_t;
      typedef float_least_width_t<16u> ::type                                 float_least16_t;
      typedef float_least_width_t<32u> ::type                                 float_least32_t;
      typedef float_least_width_t<64u> ::type                                 float_least64_t;
      typedef float_least_width_t<128u>::type                                 float_least128_t;
      typedef float_least_width_t<widthof(static_cast<void*>(nullptr))>::type floatptr_t;

      #ifdef float16_t
        typedef conditional<sizeof(float) <= sizeof(float16_t), float, float16_t>::type floatmin_t;
      #else
        typedef float_width_t<16u>::type float16_t;
        typedef float                    floatmin_t;
      #endif

      #ifndef float32_t
        typedef float_width_t<32u>::type float32_t;
      #endif

      #ifndef float64_t
        typedef float_width_t<64u>::type float64_t;
      #endif

      #ifndef float128_t
        typedef float_width_t<128u>::type float128_t;
      #endif

      typedef
        conditional<not is_same<float_least128_t, void>::value, float_least128_t,
        conditional<not is_same<float_least64_t,  void>::value, float_least64_t,
        conditional<not is_same<float_least32_t,  void>::value, float_least32_t,
        conditional<not is_same<float_least16_t,  void>::value, float_least16_t,
        conditional<not is_same<float_least8_t,   void>::value, float_least8_t,
          void
        >::type>::type>::type>::type>::type
      floatmax_t;

      // ...
      typedef uint_fast8_t                                                   uint_fast8_t;
      typedef uint_fast16_t                                                  uint_fast16_t;
      typedef uint_fast32_t                                                  uint_fast32_t;
      typedef uint_fast64_t                                                  uint_fast64_t;
      typedef uint_fast_width_t <128u>::type                                 uint_fast128_t;
      typedef uint_least_width_t<8u>  ::type                                 uint_least8_t;
      typedef uint_least_width_t<16u> ::type                                 uint_least16_t;
      typedef uint_least_width_t<32u> ::type                                 uint_least32_t;
      typedef uint_least_width_t<64u> ::type                                 uint_least64_t;
      typedef uint_least_width_t<128u>::type                                 uint_least128_t;
      typedef uint_width_t      <8u>  ::type                                 uint8_t;
      typedef uint_width_t      <16u> ::type                                 uint16_t;
      typedef uint_width_t      <32u> ::type                                 uint32_t;
      typedef uint_width_t      <64u> ::type                                 uint64_t;
      typedef unsigned char                                                  uintmin_t;
      typedef uint_least_width_t<widthof(static_cast<void*>(nullptr))>::type uintptr_t;

      #ifndef uint128_t
        typedef uint_width_t<128u>::type uint128_t;
      #endif

      typedef
        conditional<not is_same<uint_least128_t, void>::value, uint_least128_t,
        conditional<not is_same<uint_least64_t,  void>::value, uint_least64_t,
        conditional<not is_same<uint_least32_t,  void>::value, uint_least32_t,
        conditional<not is_same<uint_least16_t,  void>::value, uint_least16_t,
        conditional<not is_same<uint_least8_t,   void>::value, uint_least8_t,
          void
        >::type>::type>::type>::type>::type
      uintmax_t;

      // ...
      typedef signedof<uint_fast8_t>   ::type int_fast8_t;
      typedef signedof<uint_fast16_t>  ::type int_fast16_t;
      typedef signedof<uint_fast32_t>  ::type int_fast32_t;
      typedef signedof<uint_fast64_t>  ::type int_fast64_t;
      typedef signedof<uint_fast128_t> ::type int_fast128_t;
      typedef signedof<uint_least8_t>  ::type int_least8_t;
      typedef signedof<uint_least16_t> ::type int_least16_t;
      typedef signedof<uint_least32_t> ::type int_least32_t;
      typedef signedof<uint_least64_t> ::type int_least64_t;
      typedef signedof<uint_least128_t>::type int_least128_t;
      typedef signedof<uint8_t>        ::type int8_t;
      typedef signedof<uint16_t>       ::type int16_t;
      typedef signedof<uint32_t>       ::type int32_t;
      typedef signedof<uint64_t>       ::type int64_t;
      typedef signedof<uintmax_t>      ::type intmax_t;
      typedef signedof<uintmin_t>      ::type intmin_t;
      typedef signedof<uintptr_t>      ::type intptr_t;

      #ifndef int128_t
        typedef signedof<uint128_t>::type int128_t;
      #endif

      /* Class > Bit */
      template <std::size_t width>
      struct bit final {
        private:
          typename uint_least_width_t<width>::type value : width;

        public:
      };

      template <>
      struct bit<0u> final {
        constfunc(true) bit(uintmin_t const) noexcept discard;

        /* ... --- TODO (Lapys) */
        template <typename type> constfunc(true)        bit&          operator =  (type nodecay) member_lref          noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value,          "Assignment of empty type `bit<0zu>`"); return const_cast<bit&>         (*this); }
        template <typename type> constfunc(true)        bit volatile& operator =  (type nodecay) volatile member_lref noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value,          "Assignment of empty type `bit<0zu>`"); return const_cast<bit volatile&>(*this); }
        template <typename type> constfunc(true) friend bit&          operator += (bit&          bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit volatile& operator += (bit volatile& bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit&          operator -= (bit&          bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit volatile& operator -= (bit volatile& bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit&          operator *= (bit&          bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit volatile& operator *= (bit volatile& bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit&          operator /= (bit&          bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit volatile& operator /= (bit volatile& bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit&          operator %= (bit&          bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit volatile& operator %= (bit volatile& bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit&          operator &= (bit&          bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit volatile& operator &= (bit volatile& bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit&          operator |= (bit&          bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit volatile& operator |= (bit volatile& bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit&          operator ^= (bit&          bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit volatile& operator ^= (bit volatile& bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit&          operator <<=(bit&          bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit volatile& operator <<=(bit volatile& bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit&          operator >>=(bit&          bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }
        template <typename type> constfunc(true) friend bit volatile& operator >>=(bit volatile& bit, type nodecay)   noexcept { typedef constant<bool, 0u == sizeof(defer::template type<type>)> invalid_bit_assignment; static_assert(invalid_bit_assignment::value, "Compound assignment of empty type `bit<0zu>`"); return bit; }

        constfunc(true) operator uintmin_t() const noexcept discard;
      };
    }

    namespace Traits {
      // ... ->> For configurable function code paths (eg: `Memory::allocate(...)`, ...) or generic data structures (eg: `Array`, ...)
      // enumint(uint_least16_t, control_parameter) {
      //   DYNAMIC     = 0x0000u,
      //   HEAP        = 0x0000u,

      //   AUTOMATIC   = 0x0001u,
      //   BUFFERED    = 0x0002u,
      //   CLEARED     = 0x0004u,
      //   EXECUTABLE  = 0x0008u,
      //   MAXIMUM     = 0xF000u,
      //   NON_DYNAMIC = 0x0010u,
      //   STACK       = 0x0020u,
      //   VIEWABLE    = 0x0040u
      // };
    }

    /* Function > As ->> Permissibly converts between types; amalgam of `reinterpret_cast`, `static_cast`, and `std::bit_cast<>` */
  }

  /* Definition > Maximum Size */
  #if CPP_COMPILER != CPP_MSVC_COMPILER
  # undef CPP_MAX_SIZE
    template <std::size_t size, std::size_t increment = size, std::size_t = size>
    struct CPP_MAX_SIZE final {
      private:
        template <std::size_t subsize>
        constfunc(true) static unsigned char (&(valueof)(unsigned char const, CPP_MAX_SIZE<subsize>* const = NULL) noexcept)[subsize];

        template <std::size_t>
        constfunc(true) static unsigned char (&(valueof)(...) noexcept)[size];

      public:
        typename ::Lapys::Traits::conditional<
          size == sizeof(valueof<size + increment>(0x00u)) / sizeof(unsigned char),
          typename ::Lapys::Traits::conditional<(increment > 1u), CPP_MAX_SIZE<size, increment / 2u>, unsigned char[size]>::type,
          CPP_MAX_SIZE<sizeof(valueof<size + increment>(0x00u)) / sizeof(unsigned char), increment == size ? increment + increment : increment>
        >::type _;
    };

    template <std::size_t increment, std::size_t size> struct CPP_MAX_SIZE<0u,       increment, size> final {};
    template <std::size_t increment, std::size_t size> struct CPP_MAX_SIZE<SIZE_MAX, increment, size> final { unsigned char _[size]; };
  # define CPP_MAX_SIZE (sizeof(::CPP_MAX_SIZE<1u>) / sizeof(unsigned char)) // --> UINT_MAX <= x <= PTRDIFF_MAX
  #endif

  // Current Goals
  // • Ensure `apply(…)` macro works as intended
  // • Ensure `CPP_ENDIAN` works validly with `as` (does it need `std::memcpy(...)`?)
  // • Provide declarations for traits used here (such as `opinfo::cast<>`)
  //
  // Design Goals
  // • Auto-diagnose memory allocations with `__FILE__` and `__LINE__` (and optionally `__COUNTER__`) via macros
  // • Beware of `SIZE_MAX` (or such) for bounded ranges, such as the ones for memory allocators
  // • Overload literal operators (since C++11) for string methods (`"…"indexOf(…)`, `L"…"hash`, …) and custom string types (`"…"s`, …)
  // • Overload literal operators for unit measurements (`0cm`, `0px`, …)
  // • Prefer `__STDCPP_BFLOAT16_T__`, `__STDCPP_FLOAT16_T__`, `__STDCPP_FLOAT32_T__`, `__STDCPP_FLOAT64_T__`, and `__STDCPP_FLOAT128_T__` (since C++23 from `<stdfloat>`) for fixed-size floating-point arithmetic
  // • Prefer `double_t` and `float_t` (since C++11 from `<cmath>`) for floating-point arithmetic
  // • Prefer `UI::createWindow().append(UI::createButton(), UI::createText())` over `Window{}.append(Button{}, Text{})`
  // • Prefer factory functions & methods over stateful constructors & member functions eg: `System::createFile(…)` evaluates to `class File*` or `NULL`
  // • Standard
  //   ⚬ arbitrary-precision,
  //   ⚬ array, (first member is the actual array, explicitly convertible to pointers, implicitly convertible to arrays)
  //   ⚬ audio,
  //   ⚬ data structure, (linked list, map, set, …)
  //   ⚬ dynamic function, (`Function<…>(nullptr)` creates undefined function; `Function<…>("…")` creates instructions; `Memory::instantiate<Function<…> >("…")` creates callable functions; explicit `Function<…>(…)` takes any callable and wraps 'em)
  //   ⚬ geolocation,
  //   ⚬ 2D/ 3D graphics rendering, (software rendering MUST be guaranteed to be available)
  //   ⚬ events, (keyboard, pointer, touch, vibration, …)
  //   ⚬ font parsing,
  //   ⚬ hardware diagnostics, (battery, gamepad, graphics card, keyboard, stylus, USB, …)
  //   ⚬ HTML parsing,
  //   ⚬ image parsing, (APNG, AVIF, GIF, JPEG, PNG, SVG, WEBP)
  //   ⚬ internationalization/ locale,
  //   ⚬ math.,
  //   ⚬ memory management, (fixed-size allocations are sorted in buckets, not generalized; `Memory::allocate(…)` evaluates to `class MemoryBuffer` which decays to a pointer — there´s also `Memory::instantiate<>(…)`; `Memory::allocate(…)` may also allocate from "memory-mapped" files)
  //       Page align for bigger allocation blocks,
  //       C++ `std::aligned_alloc(…)`,
  //       MSVC `_aligned_malloc(…)` (used with `_aligned_free(…)` instead), and
  //       POSIX `posix_memalign(…)`
  //       WinAPI `VirtualAlloc2(…)`
  //
  //       `std::align(…)`, or otherwise manually align for `alignof T < alignof max_align_t`
  //   ⚬ multi-threading, (background workers and spawning threads)
  //   ⚬ networking, (TCP/IP, UDP, …)
  //   ⚬ parallelization, (OpenMP or SIMD support?)
  //   ⚬ program-specific features,
  //   ⚬ QR,
  //   ⚬ string, (codepoints, SSO, ropes, UTF-8 default, …)
  //   ⚬ system diagnostics/ query, (clipboard, filesystem, screen, …)
  //   ⚬ tuple,
  //   ⚬ URL/ path,
  //   ⚬ user-interface,
  //   ⚬ variant, and
  //   ⚬ video
  //   APIs
  // • Use `template <auto = []{}>` (since C++20 or `function([]{})` since C++11) for stateful template metaprogramming otherwise use `__COUNTER__` aliased via macros
#endif
