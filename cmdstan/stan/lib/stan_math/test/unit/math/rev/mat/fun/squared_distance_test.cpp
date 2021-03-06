#include <stan/math/rev/mat.hpp>
#include <gtest/gtest.h>
#include <test/unit/math/rev/mat/fun/util.hpp>
#include <test/unit/math/rev/mat/util.hpp>

TEST(AgradRevMatrix, squared_distance_vector_vector) {
  using stan::math::vector_d;
  using stan::math::vector_v;

  vector_d vd_1(3), vd_2(3);
  vector_v vv_1(3), vv_2(3);
  
  vd_1 << 1, 3, -5;
  vv_1 << 1, 3, -5;
  vd_2 << 4, -2, -1;
  vv_2 << 4, -2, -1;

  EXPECT_FLOAT_EQ(50, stan::math::squared_distance(vv_1, vd_2).val());
  EXPECT_FLOAT_EQ(50, stan::math::squared_distance(vd_1, vv_2).val());
  EXPECT_FLOAT_EQ(50, stan::math::squared_distance(vv_1, vv_2).val());
}
TEST(AgradRevMatrix, squared_distance_vector_vector_exception) {
  using stan::math::vector_d;
  using stan::math::vector_v;

  vector_d d1(3);
  vector_v v1(3);
  vector_d d2(2);
  vector_v v2(4);

  EXPECT_THROW(stan::math::squared_distance(v1, d2), std::invalid_argument);
  EXPECT_THROW(stan::math::squared_distance(d1, v2), std::invalid_argument);
  EXPECT_THROW(stan::math::squared_distance(v1, v2), std::invalid_argument);
}
TEST(AgradRevMatrix, squared_distance_rowvector_vector) {
  using stan::math::vector_d;
  using stan::math::vector_v;
  using stan::math::row_vector_d;
  using stan::math::row_vector_v;

  row_vector_d d1(3);
  row_vector_v v1(3);
  vector_d d2(3);
  vector_v v2(3);
  
  d1 << 1, 3, -5;
  v1 << 1, 3, -5;
  d2 << 4, -2, -1;
  v2 << 4, -2, -1;

  EXPECT_FLOAT_EQ(50, stan::math::squared_distance(v1, d2).val());
  EXPECT_FLOAT_EQ(50, stan::math::squared_distance(d1, v2).val());
  EXPECT_FLOAT_EQ(50, stan::math::squared_distance(v1, v2).val());
}
TEST(AgradRevMatrix, squared_distance_rowvector_vector_exception) {
  using stan::math::vector_d;
  using stan::math::vector_v;
  using stan::math::row_vector_d;
  using stan::math::row_vector_v;

  row_vector_d d1(3);
  row_vector_v v1(3);
  vector_d d2(2);
  vector_v v2(4);

  EXPECT_THROW(stan::math::squared_distance(v1, d2), std::invalid_argument);
  EXPECT_THROW(stan::math::squared_distance(d1, v2), std::invalid_argument);
  EXPECT_THROW(stan::math::squared_distance(v1, v2), std::invalid_argument);
}
TEST(AgradRevMatrix, squared_distance_vector_rowvector) {
  using stan::math::vector_d;
  using stan::math::vector_v;
  using stan::math::row_vector_d;
  using stan::math::row_vector_v;

  vector_d d1(3);
  vector_v v1(3);
  row_vector_d d2(3);
  row_vector_v v2(3);
  
  d1 << 1, 3, -5;
  v1 << 1, 3, -5;
  d2 << 4, -2, -1;
  v2 << 4, -2, -1;
  
  EXPECT_FLOAT_EQ(50, stan::math::squared_distance(v1, d2).val());
  EXPECT_FLOAT_EQ(50, stan::math::squared_distance(d1, v2).val());
  EXPECT_FLOAT_EQ(50, stan::math::squared_distance(v1, v2).val());
}
TEST(AgradRevMatrix, squared_distance_vector_rowvector_exception) {
  using stan::math::vector_d;
  using stan::math::vector_v;
  using stan::math::row_vector_d;
  using stan::math::row_vector_v;

  vector_d d1(3);
  vector_v v1(3);
  row_vector_d d2(2);
  row_vector_v v2(4);

  EXPECT_THROW(stan::math::squared_distance(v1, d2), std::invalid_argument);
  EXPECT_THROW(stan::math::squared_distance(d1, v2), std::invalid_argument);
  EXPECT_THROW(stan::math::squared_distance(v1, v2), std::invalid_argument);
}
TEST(AgradRevMatrix, squared_distance_rowvector_rowvector) {
  using stan::math::row_vector_d;
  using stan::math::row_vector_v;

  row_vector_d d1(3), d2(3);
  row_vector_v v1(3), v2(3);
  
  d1 << 1, 3, -5;
  v1 << 1, 3, -5;
  d2 << 4, -2, -1;
  v2 << 4, -2, -1;

  EXPECT_FLOAT_EQ(50, stan::math::squared_distance(v1, d2).val());
  EXPECT_FLOAT_EQ(50, stan::math::squared_distance(d1, v2).val());
  EXPECT_FLOAT_EQ(50, stan::math::squared_distance(v1, v2).val());
}
TEST(AgradRevMatrix, squared_distance_rowvector_rowvector_exception) {
  using stan::math::row_vector_d;
  using stan::math::row_vector_v;

  row_vector_d d1(3), d2(2);
  row_vector_v v1(3), v2(4);

  EXPECT_THROW(stan::math::squared_distance(v1, d2), std::invalid_argument);
  EXPECT_THROW(stan::math::squared_distance(d1, v2), std::invalid_argument);
  EXPECT_THROW(stan::math::squared_distance(v1, v2), std::invalid_argument);
}

TEST(AgradRevMatrix, squared_distance_vv) {
  using stan::math::vector_v;

  vector_v a(3), b(3);
  AVAR c;
  for (int i = -1; i < 2; i++) { // a = (-1, 0, 1), b = (1, 2, 3)
    a(i+1) = i;
    b(i+1) = i + 2;
  }
  c = squared_distance(a, b);
  EXPECT_FLOAT_EQ(12, c.val());
  AVEC ab;
  VEC grad;
  for (size_t i = 0; i < 3; i++) {
    ab.push_back(a[i]);
    ab.push_back(b[i]);
  }
  c.grad(ab, grad);
  EXPECT_FLOAT_EQ(2*(a(0).val() - b(0).val()), grad[0]);
  EXPECT_FLOAT_EQ(-2*(a(0).val() - b(0).val()), grad[1]);
  EXPECT_FLOAT_EQ(2*(a(1).val() - b(1).val()), grad[2]);
  EXPECT_FLOAT_EQ(-2*(a(1).val() - b(1).val()), grad[3]);
  EXPECT_FLOAT_EQ(2*(a(2).val() - b(2).val()), grad[4]);
  EXPECT_FLOAT_EQ(-2*(a(2).val() - b(2).val()), grad[5]);
}
TEST(AgradRevMatrix, squared_distance_dv) {
  using stan::math::vector_d;
  using stan::math::vector_v;

  vector_d a(3);
  vector_v b(3);
  AVAR c;
  for (int i = -1; i < 2; i++) { // a = (-1, 0, 1), b = (1, 2, 3)
    a(i+1) = i;
    b(i+1) = i + 2;
  }
  c = squared_distance(a, b);
  EXPECT_FLOAT_EQ(12, c.val());
  AVEC bv;
  VEC grad;
  for (size_t i = 0; i < 3; i++) {
    bv.push_back(b[i]);
  }
  c.grad(bv, grad);
  EXPECT_FLOAT_EQ(-2*(a(0) - b(0).val()), grad[0]);
  EXPECT_FLOAT_EQ(-2*(a(1) - b(1).val()), grad[1]);
  EXPECT_FLOAT_EQ(-2*(a(2) - b(2).val()), grad[2]);
}
TEST(AgradRevMatrix, squared_distance_vd) {
  using stan::math::vector_d;
  using stan::math::vector_v;

  vector_v a(3);
  vector_d b(3);
  AVAR c;
  for (int i = -1; i < 2; i++) { // a = (-1, 0, 1), b = (1, 2, 3)
    a(i+1) = i;
    b(i+1) = i + 2;
  }
  c = squared_distance(a, b);
  EXPECT_FLOAT_EQ(12, c.val());
  AVEC av;
  VEC grad;
  for (size_t i = 0; i < 3; i++) {
    av.push_back(a[i]);
  }
  c.grad(av, grad);
  EXPECT_FLOAT_EQ(2*(a(0).val() - b(0)), grad[0]);
  EXPECT_FLOAT_EQ(2*(a(1).val() - b(1)), grad[1]);
  EXPECT_FLOAT_EQ(2*(a(2).val() - b(2)), grad[2]);
}
TEST(AgradRevMatrix, check_varis_on_stack) {
  using stan::math::to_var;
  stan::math::vector_d v1(3), v2(3);
  
  v1 << 1, 3, -5;
  v2 << 4, -2, -1;
  
  test::check_varis_on_stack(stan::math::squared_distance(to_var(v1), to_var(v2)));
  test::check_varis_on_stack(stan::math::squared_distance(to_var(v1), v2));
  test::check_varis_on_stack(stan::math::squared_distance(v1, to_var(v2)));
}
