
#include <unity.h>
#include <gol/grid.h>
#include <raylib.h>

void setUp(void) {}
void tearDown(void) {}

void grid_create_should_returnDummyGridOnErr(){
    const grid_s G1 = grid_create(0, (Vector2){0,0});
    TEST_ASSERT_EQUAL_UINT(1,G1.size);
    TEST_ASSERT_EQUAL_UINT(0,G1.offset.x);
    TEST_ASSERT_EQUAL_UINT(0,G1.offset.y);
}

void grid_create_should_returnValidGrid(){
    const grid_s G1 = grid_create(10, (Vector2) {50, 0});
    const grid_s G2 = grid_create(16, (Vector2) {0, 200});
    const grid_s G3 = grid_create(16, (Vector2) {-30, 0});
    
    TEST_ASSERT_EQUAL_UINT ( 10,  G1.size);
    TEST_ASSERT_EQUAL_FLOAT( 50,  G1.offset.x);
    TEST_ASSERT_EQUAL_FLOAT( 0,   G1.offset.y);

    TEST_ASSERT_EQUAL_UINT ( 16,  G2.size);
    TEST_ASSERT_EQUAL_FLOAT( 0,   G2.offset.x);
    TEST_ASSERT_EQUAL_FLOAT( 200, G2.offset.y);

    TEST_ASSERT_EQUAL_UINT ( 16,  G3.size);
    TEST_ASSERT_EQUAL_FLOAT(-30,  G3.offset.x);
    TEST_ASSERT_EQUAL_FLOAT( 0,   G3.offset.y);
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(grid_create_should_returnDummyGridOnErr);
    RUN_TEST(grid_create_should_returnValidGrid);
    return UNITY_END();
}