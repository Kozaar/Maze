#include <gtest/gtest.h>
#include <exception>
#include "Maze/Model/cave.h"
#include "Maze/Model/maze.h"

TEST(Cave, Cave_test1) {
    Cave a;
    a.openFile("examples/cave/1.txt");
    a.createNewGeneration(3, 2);
    std::vector<std::vector<bool>> my_res = *(a.getCave());
    a.openFile("examples/cave/test1.txt");
    std::vector<std::vector<bool>> current_res = *(a.getCave());
}

TEST(Cave, Cave_test2) {
    Cave a;
    a.openFile("examples/cave/2.txt");
    a.createNewGeneration(2, 3);
    std::vector<std::vector<bool>> my_res = *(a.getCave());
    a.openFile("examples/cave/test2.txt");
    std::vector<std::vector<bool>> current_res = *(a.getCave());
    ASSERT_TRUE(my_res == current_res);
}

TEST(Cave, Cave_test_save_file) {
    Cave a;
    a.generateNewCave(2, 2, 100);
    a.saveArea("examples/cave/3.txt");
    std::vector<std::vector<bool>> my_res = *(a.getCave());
    a.openFile("examples/cave/test3.txt");
    std::vector<std::vector<bool>> current_res = *(a.getCave());
    ASSERT_TRUE(my_res == current_res);
}

TEST(Cave, Cave_test_file_wrong_file_1) {
    Cave a;
    ASSERT_FALSE(a.openFile("examples/cave/test_bad.txt"));
}

TEST(Cave, Cave_test_file_wrong_file_2) {
    Cave a;
    ASSERT_FALSE(a.openFile("examples/cave/test_bad1.txt"));
}

TEST(Maze, Maze_test_1) {
    Maze maze;
    maze.generate(6, 6);
    ASSERT_EQ(maze.getSize().first, 6);
    ASSERT_EQ(maze.getSize().second, 6);
    for (int i = 0; i < maze.getSize().first; i++) {
        for (int j = 0; j < maze.getSize().second; j++) {
            ASSERT_TRUE(maze.findSolution(0, 0, i, j));
        }
    }
}

TEST(Maze, Maze_test_2) {
    Maze maze;
    maze.generate(3, 16);
    ASSERT_EQ(maze.getSize().first, 3);
    ASSERT_EQ(maze.getSize().second, 16);
    for (int i = 0; i < maze.getSize().first; i++) {
        for (int j = 0; j < maze.getSize().second; j++) {
            ASSERT_TRUE(maze.findSolution(0, 0, j, i));
        }
    }
}

TEST(Maze, Maze_test_3) {
    Maze maze;
    maze.generate(3, 1);
    ASSERT_EQ(maze.getSize().first, 3);
    ASSERT_EQ(maze.getSize().second, 1);
    for (int i = 0; i < maze.getSize().first; i++) {
        for (int j = 0; j < maze.getSize().second; j++) {
            ASSERT_TRUE(maze.findSolution(0, 0, j, i));
        }
    }
}

TEST(Maze, Maze_test_open_file) {
    Maze maze;
    maze.openFile("examples/maze/maze_test_file_1.txt");
    ASSERT_EQ(maze.getSize().first, 16);
    ASSERT_EQ(maze.getSize().second, 16);
    for (int i = 0; i < maze.getSize().first; i++) {
        for (int j = 0; j < maze.getSize().second; j++) {
            ASSERT_TRUE(maze.findSolution(0, 0, j, i));
        }
    }
}

TEST(Maze, Maze_test_save_file) {
    Maze maze;
    maze.generate(10, 10);
    std::vector<std::vector<std::pair<bool, bool> > > my_res = *maze.getMaze();
    maze.saveInFile("examples/maze/maze_test_file_2.txt");
    maze.openFile("examples/maze/maze_test_file_2.txt");
    ASSERT_EQ(maze.getSize().first, my_res.size());
    ASSERT_EQ(maze.getSize().second, my_res.at(0).size());
    for (int i = 0; i < maze.getSize().first; i++) {
        for (int j = 0; j < maze.getSize().second; j++) {
            ASSERT_EQ(maze.getMaze()->at(i).at(j).first, my_res.at(i).at(j).first);
            ASSERT_EQ(maze.getMaze()->at(i).at(j).second, my_res.at(i).at(j).second);
        }
    }
}


int main(int argc, char ** argv) {
  testing :: InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
