#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <vector>

std::vector<std::pair<int,int> > prod = {
        {2, 1},  {1,2},   {-1,2}, {-2,1},
        {-2,-1}, {-1,-2}, {1,-2}, {2, -1}
};

std::ofstream myfile;
typedef unsigned int u32;

u32 recursionCount = 0;
u32 lineCount = 1;


void OutputBoard(int* board, int size)
{
    std::cout << "Y, V ^" << std::endl;
    for(int i = size - 1; i >= 0; --i)
    {
        std::cout << " " << std::setfill(' ') << std::setw(3) << i + 1 << " | ";
        for(int j = 0; j < size; ++j)
        {
            std::cout << std::setfill(' ') << std::setw(3) << board[i * size + j];
        }
        std::cout << std::endl;
    }
    std::cout << "       ";
    for(int i = 0; i < size; ++i)
    {
        std::cout << "---";
    }
    std::cout << "> X, U";
    std::cout << std::endl;

    std::cout << "       ";
    for(int i = 0; i < size; ++i)
    {
        std::cout << std::setfill(' ') << std::setw(3) << i+1;
    }
    std::cout << std::endl;
}


int* Init(int size, int x, int y)
{
    int* board = nullptr;

    board = new int[size * size];
    for(int i = 0; i < size * size; ++i)
    {
        board[i] = 0;
    }

    board[y * size + x] = 1;
    return board;
}

bool Try(int* board, int size,int L, int X, int Y)
{

    recursionCount++;
    bool isFinished = false;
    int prodCount = 0;

    for( std::pair<int,int> p : prod)
    {
       prodCount++;


       int U = X + p.first;
       int V = Y + p.second;

       myfile << std::setfill(' ') << std::setw(5) << lineCount++ << ") ";
       for(int i  = 0 ; i < recursionCount - 1; ++i)
       {
           myfile << "-";
       }
       myfile << "R" << std::to_string(prodCount) << ". U=" << U + 1 <<", "<< "V=" << V + 1 << ". " << "L=" << L << ". ";

       if ( U >= 0 && U < size && V >= 0 && V < size )
       {
          if(board[V * size + U] == 0)
          {
              // FREE

             myfile <<"Free. BOARD[" << std::to_string(U + 1) << "," << std::to_string(V + 1) << "]:=" << L << std::endl;
             board[V * size + U] = L;

             if( L < size * size)
             {
                 isFinished = Try(board,size, L + 1,U,V);

                 if(!isFinished)
                 {
                     recursionCount--;
                     board[V * size + U] = 0;
                 }
             }
             else
             {
                 return true;
             }
          }
          else
          {
              // THREAD
              myfile <<"Thread." << std::endl;
          }
       }
       else
       {
           // OUT
           myfile <<"Out." << std::endl;
       }


        if(isFinished)
        {
            break;
        }
    }

    if(isFinished)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int GetInteger(const std::string& str, int lowerBound, int upperBound)
{
    int value = 0;
    std::cout << str;
    std::cin >> value;

    while(!std::cin || value < lowerBound || value > upperBound)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << " Invalid value\n";
        std::cout << str;
        std::cin >> value;
    }

    return value;
}

int main()
{
    int* board = nullptr;
    int size = 0;
    int X, Y = 0;

    // Production set

    myfile.open("OUTPUT.TXT");

    std::cout << "------ Chess knight problem ---" << std::endl;
    size = GetInteger(" Enter board size : ", 1,9);
    X = GetInteger(" Enter knights pos X : ", 0,size + 1);
    X -= 1;
    Y = GetInteger(" Enter knights pos Y : ", 0,size + 1);
    Y -= 1;

    std::cout << std::endl;
    std::cout << "PART 1. Data" << std::endl;
    std::cout << "    1) Board " << size << "x" << size << std::endl;
    std::cout << "    2) Initial position X=" << X+1 << " Y=" << Y+1 << ". " << "L=1." << std::endl;

    std::cout << std::endl;
    std::cout << "PART 2. Trace" << std::endl;
    std::cout << "     Trace is located OUTPUT.TXT" << std::endl;

    // INIT
    board = Init(size,X,Y);

    bool isFound = Try(board,size,2,X,Y);

    std::cout << std::endl;
    std::cout << "PART 3. Results" << std::endl;

    if(isFound)
    {
        std::cout << "  Path is found." << std::endl;
        std::cout << "  Path graphically" << std::endl;
        std::cout << std::endl;
        OutputBoard(board, size);
    }
    else
    {
        std::cout << "  Path is not found." << std::endl;
        OutputBoard(board,size);
    }

    std::cout << lineCount << std::endl;
    delete[] board;

    myfile.close();
    return 0;
}