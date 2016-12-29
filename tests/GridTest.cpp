#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/core_classes/Matrix.h"

using  testing::Eq;
namespace {
    class GridTest : public testing::Test {
    public:
        Matrix matrix;
        Grid *grid;
        GridTest() : matrix(10, 10) {
            grid = &matrix;
        }
    };
}

TEST_F(GridTest, initDistanceForAll){
    int d = 3;
    grid->initDistanceForAll(d);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            ASSERT_EQ(d, 3);
        }
    }
}