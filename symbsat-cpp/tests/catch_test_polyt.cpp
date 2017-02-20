#include <iostream>

#include "catch.hpp"

#include "monomt.h"
#include "polyt.h"

using namespace symbsat;

TEST_CASE("Poly Constructor", "[poly-constructor]") {
  Monoms::Monom32 a(0), b(1), c(2);

  Poly<Monoms::Monom32> p1;
  Poly<Monoms::Monom32> p2(a);
  Poly<Monoms::Monom32> p3({a, b, c});

  std::vector<Monoms::Monom32> monoms {b, c, a};
  Poly<Monoms::Monom32> p4(monoms);
}

TEST_CASE("Polynomial Leading Monomial", "[poly-lm]") {
  Monoms::Monom32 a(0), b(1), c(2);
  Monoms::Monom32 _0;

  Poly<Monoms::Monom32> p1({b, c, a});

  CHECK(p1.toStr() == "[ 0 ] [ 1 ] [ 2 ] ");
  REQUIRE(p1.lm() == a);

  Poly<Monoms::Monom32> p2;

  CHECK(p2.isZero());
  REQUIRE(p2.lm() == _0);
}

TEST_CASE("Polynomial Addition", "[poly-add]") {
  Monoms::Monom32 a(0), b(1);
  Poly<Monoms::Monom32> p_a(a), p_b(b), p_ab, p_aa;

  p_ab = p_a + p_b;
  p_aa = p_a + p_a;
  REQUIRE(p_aa.isZero());
}

TEST_CASE("Polynomial Multiplication", "[poly-mul]") {
  Monoms::Monom32 a(0), b(1), c(2);

  Poly<Monoms::Monom32> p_a(a), p_b(b), p_c(c), p_abc;

  p_abc = p_a + p_b + p_c;
  CHECK(p_abc.toStr() == "[ 0 ] [ 1 ] [ 2 ] ");

  Poly<Monoms::Monom32> p_res;
  p_res = p_abc * p_c;

  CHECK(p_abc.toStr() == "[ 0 ] [ 1 ] [ 2 ] ");
  REQUIRE(p_res.toStr() == "[ 0 2 ] [ 1 2 ] [ 2 ] ");

  Poly<Monoms::Monom32> p_zero;

  CHECK(p_zero.isZero());

  p_res *= p_zero;

  REQUIRE(p_res.isZero());

  SECTION("Multiply by Monom") {
    Monoms::Monom32 a(0), b(1), _0;
    Poly<Monoms::Monom32> p_a(a), p_res;

    p_res = p_a * b;

    REQUIRE(p_res.toStr() == "[ 0 1 ] ");

    p_res *= _0;

    REQUIRE(p_res.isZero());
  }
}