#include<iostream>
#define RESET    "\033[0m"
#define BG_DARK  "\033[48;5;94m"
#define BG_LIGHT "\033[48;5;223m"
#define BLACK_PIECE "\033[30m"
#define WHITE_PIECE "\033[38;5;111m"

using namespace std;
class Piece
{
protected:
	int row;
	int col;
public:
	Piece(int r, int c) :row(r),col(c)
	{
		 
	}
	virtual bool CanMove(int r,int col,char c[8][8]) = 0;

};
class Pawn:public Piece
{
public:

	Pawn(int r,int c):Piece(r,c)
	{

	}
	bool CanMove(int r, int col, char c[8][8]) override {
		return true;
	}
};
class Rook :public Piece
{
public:

	Rook(int r, int c) :Piece(r, c)
	{

	}
	bool CanMove(int r, int col, char c[8][8]) override
	{

		return true;
	}
};
class Bishop :public Piece
{
public:
	Bishop(int r, int c) :Piece(r, c)
	{

	}
	bool CanMove(int r, int col, char c[8][8]) override 
	{
		if (isupper(c[r][col]) && isupper(c[this->row][this->col]))
		{
			cout << "\nIt cannor kill its own piece " << endl;
			return false;
		}
		if (islower(c[r][col]) && islower(c[this->row][this->col]))
		{
			cout << "\nIt cannor kill its own piece " << endl;
			return false;
		}
		bool isblack;
		if (isupper(c[this->row][this->col]))
		{
			isblack = false;
		}
		else
			isblack = true;
		int rdiff = r - this->row;
		int cdiff = col - this->col;
		bool check=true;
		rdiff = rdiff < 0 ? -rdiff : rdiff;
		cdiff = cdiff < 0 ? -cdiff : cdiff;
		if (cdiff==rdiff)
		{
			for (int i = this->row; i < r; i++)
			{
				for (int j = this->col; j < col; j++)
				{
					if (c[i][j] != ' ')
					{
						check = false;
						break;
					}
				}
				if (check == false)
				{
					break;
					return false;
				}
				
			}
			c[this->row][this->col] = ' ';
			this->row = r;
			this->col = col;
			if (isblack == true)
				c[this->row][this->col] = 'b';
			else
				c[this->row][this->col] = 'B';
			return true;
		}
		return false;
	}
};
class King :public Piece
{
public:
	King(int r, int c) :Piece(r, c)
	{

	}

	bool CanMove(int r, int col, char c[8][8]) override
	{
		if (isupper(c[r][col]) && isupper(c[this->row][this->col]))
		{
			cout << "\nIt cannor kill its own piece " << endl;
			return false;
		}
		if (islower(c[r][col]) && islower(c[this->row][this->col]))
		{
			cout << "\nIt cannor kill its own piece " << endl;
			return false;
		}
		bool isblack;
		if (isupper(c[this->row][this->col]))
		{
			isblack = false;
		}
		else
			isblack = true;
		int rdiff = r - this->row;
		int cdiff = col - this->col;
		if (((rdiff >= -1 && rdiff <= 1) && (cdiff >= -1 && cdiff >= 1)) )
		{
			c[this->row][this->col] = ' ';
			this->row=r;
			this->col = col;
			if (isblack == true)
				c[this->row][this->col] = 'k';
			else
				c[this->row][this->col] = 'K';
			return true;
		}
		
		return false;
	}
};
class Queen :public Piece
{
public:
	Queen(int r, int c) :Piece(r, c)
	{

	}
	bool CanMove(int r, int col, char c[8][8]) override
	{

		return true;
	}
};
class Knight :public Piece
{
public:
	Knight(int r, int c) :Piece(r, c)
	{

	}
	bool CanMove(int r, int col, char c[8][8]) override
	{
		return true;
	}
};
class Board
{
	char arr[8][8];
	Knight n[4]{ Knight(0,1), Knight(0,6), Knight(7,1), Knight(7,6) };
	Queen Q[2]{ Queen(0,3),  Queen(7,3) };
	King K[2]{ King(0,4),   King(7,4) };
	Bishop B[4]{ Bishop(0,2), Bishop(0,5), Bishop(7,2), Bishop(7,5) };
	Rook R[4]{ Rook(0,0),   Rook(0,7),   Rook(7,0),   Rook(7,7) };
	Pawn P[16]{ Pawn(1,0),Pawn(1,1),Pawn(1,2),Pawn(1,3),Pawn(1,4),Pawn(1,5),Pawn(1,6),Pawn(1,7),Pawn(6,0),Pawn(6,1),Pawn(6,2),Pawn(6,3),Pawn(6,4),Pawn(6,5),Pawn(6,6),Pawn(6,7) };
public:
	Board()
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				arr[i][j] = ' ';
			}
		}
		for (int i = 0; i < 8; i++)
		{
			arr[1][i] = 'P';
		}
		for (int i = 0; i < 8; i++)
		{
			arr[6][i] = 'p';
		}
		arr[0][0] = arr[0][7] = 'R';
		arr[7][0] = arr[7][7] = 'r';
		arr[0][1] = arr[0][6] = 'N';
		arr[7][1] = arr[7][6] = 'n';
		arr[0][2] = arr[0][5] = 'B';
		arr[7][2] = arr[7][5] = 'b';
		arr[0][3] ='Q';
		arr[0][4] = 'K';
		arr[7][3] = 'q';
		arr[7][4] = 'k';
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if ((i + j) % 2 == 0)
					cout << BG_LIGHT;
				else
					cout << BG_DARK;

				if (islower(arr[i][j]))
					cout << BLACK_PIECE << arr[i][j] << " " << RESET;
				else if (isupper(arr[i][j]))
					cout << WHITE_PIECE << arr[i][j] << " " << RESET;
				else
					cout << "  " << RESET;
			}
			cout << endl;
		}
	}
};
int main()
{
	Board b;
	system("pause");
}