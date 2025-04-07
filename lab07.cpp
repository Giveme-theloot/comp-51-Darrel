#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;
const int rows = 4;
const int cols = 4;
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
string dir[] = {"Right", "Down", "Left", "Up"};

bool issafe( int x, int y, char maze[MAX][MAX], bool visited[MAX][MAX])
{
    return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] != '#' && !visited[x][y]);
}

void findpaths(char maze[MAX][MAX], int x, int y, string pathsofar, bool visited[MAX][MAX], int& pathcount)
{
    if (maze[x][y] == 'E')
    {
        pathcount++;
        cout << "Path " << pathcount << ": " << pathsofar << endl;
        return;
    }
    
    visited[x][y] = true;

    for (int i = 0; i < 4; i++)
    {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (issafe(newX, newY, maze, visited))
        {
            string newpath = pathsofar;
            if (!newpath.empty())
            {
                newpath += ", ";
            }
            newpath += dir[i];
            findpaths(maze, newX, newY, newpath, visited, pathcount);
        }
    }
    visited[x][y] = false;
}

void solvemaze(char maze[MAX][MAX])
{
    int startx = -1;
    int starty = -1;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (maze[i][j] == 'S')
            {
                startx = i;
                starty = j;
                break;
            }   
        }   
    }
    if (startx == -1 || starty == -1)
    {
        cout << "Start point 'S' not found in the maze." << endl;
        return;
    }
    bool visited[MAX][MAX] = {false};
    int pathcount = 0;

    findpaths(maze, startx, starty, "", visited, pathcount);

    if (pathcount == 0)
    {
        cout << "No paths found from S to E." << endl;
    }
}

int main()
{
    char maze[MAX][MAX] = {
        {'S', '#', ' ', '#'},
        {' ', ' ', '#', ' '},
        {'#', ' ', ' ', '#'},
        {'#', '#', ' ', 'E'}
    };
    solvemaze(maze);
}