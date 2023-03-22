
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


void grid_to_screen_should_produceCorrectCoordinate(){
    const grid_s G1 = grid_create(10, (Vector2) {50, 0});

    TEST_ASSERT_EQUAL_FLOAT( 150,  grid_to_screen(G1, (Vector2){10,10}).x);
    TEST_ASSERT_EQUAL_FLOAT( 100,  grid_to_screen(G1, (Vector2){10,10}).y);

    TEST_ASSERT_EQUAL_FLOAT( 155,  grid_to_screen(G1, (Vector2){10.5,10.5}).x);
    TEST_ASSERT_EQUAL_FLOAT( 105,  grid_to_screen(G1, (Vector2){10.5,10.5}).y);
}

void screen_to_grid_should_produceCorrectCoordinate(){
    const grid_s G1 = grid_create(10, (Vector2) {50, 0});

    TEST_ASSERT_EQUAL_FLOAT( 10,  screen_to_grid(G1, (Vector2){150,100}).x);
    TEST_ASSERT_EQUAL_FLOAT( 10,  screen_to_grid(G1, (Vector2){150,100}).y);

    TEST_ASSERT_EQUAL_FLOAT( 10,  screen_to_grid(G1, (Vector2){155,105}).x);
    TEST_ASSERT_EQUAL_FLOAT( 10,  screen_to_grid(G1, (Vector2){155,105}).y);
}

void screen_to_grid_exact_should_produceCorrectCoordinate(){
    const grid_s G1 = grid_create(10, (Vector2) {50, 0});

    TEST_ASSERT_EQUAL_FLOAT( 10,  screen_to_grid_exact(G1, (Vector2){150,100}).x);
    TEST_ASSERT_EQUAL_FLOAT( 10,  screen_to_grid_exact(G1, (Vector2){150,100}).y);
    
    TEST_ASSERT_EQUAL_FLOAT( 10.5,  screen_to_grid_exact(G1, (Vector2){155,105}).x);
    TEST_ASSERT_EQUAL_FLOAT( 10.5,  screen_to_grid_exact(G1, (Vector2){155,105}).y);
    
}

int main(){
    UNITY_BEGIN();
        RUN_TEST(grid_create_should_returnDummyGridOnErr);
        RUN_TEST(grid_create_should_returnValidGrid);
        RUN_TEST(grid_to_screen_should_produceCorrectCoordinate);
        RUN_TEST(screen_to_grid_should_produceCorrectCoordinate);
        RUN_TEST(screen_to_grid_exact_should_produceCorrectCoordinate);
    return UNITY_END();
}