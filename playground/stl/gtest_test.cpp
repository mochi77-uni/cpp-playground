
#include <gtest/gtest.h>
#include <queue>

// If "gtest_main" library is used, on windows WinMain() is expected,
// that for windows.h need to be included
#include <windows.h>

TEST(HelloTest, BassicAssertions) {
	EXPECT_STRNE("Hello", "World");
}

class QueueTest : public testing::Test {
protected:
	std::queue<int> q0;
	std::queue<int> q1;

	void SetUp() override {
		q1.push(1);
	}
};

TEST_F(QueueTest, IsEmptyInitially) {
	EXPECT_EQ(q0.size(), 0);
}

/* If "gtest" library is used, need to provide main()

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
*/
