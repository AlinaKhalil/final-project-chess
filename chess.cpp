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
	Piece(int r, int c) :row(r), col(c)
	{

	}
	virtual bool CanMove(int r, int col, char c[8][8]) = 0;

};
class Pawn :public Piece
{
public:

	Pawn(int r, int c) :Piece(r, c)
	{

	}
	bool CanMove(int r, int col, char c[8][8]) override {
		int rdiff = r - this->row;
		int coldiff = col - this->col;
		if (rdiff == -1 && (coldiff == 0 || coldiff == 1 || coldiff == -1) && isupper(c[this->row][this->col]))
		{
			cout << "\n you cannot move backward";
			return false;
		}
		if (rdiff == 1 && (coldiff == 0 || coldiff == 1 || coldiff == -1) && islower(c[this->row][this->col]))
		{
			cout << "\n you cannot move backward";
			return false;
		}

		if ((rdiff == 1 && coldiff == 0) && isupper(c[r][col]) && isupper(c[this->row][this->col]))
		{
			cout << "\n it cannnot kill its own piece";
			return false;
		}
		if ((rdiff == -1 && coldiff == 0) && islower(c[r][col]) && islower(c[this->row][this->col]))
		{
			cout << "\n it cannnot kill its own piece";
			return false;
		}

		if (rdiff == 2 && coldiff == 0 && isupper(c[this->row][this->col]) && this->row == 1 && c[r][col] == ' ')
		{
			if (c[this->row + 1][this->col] == ' ' && c[r][col] == ' ')
			{
				c[this->row][this->col] = ' ';
				this->row = r;
				this->col = col;
				c[this->row][this->col] = 'P';
				cout << "\n correct move";
			}
		}



		if (rdiff == -2 && coldiff == 0 && islower(c[this->row][this->col]) && this->row == 6 && c[r][col] == ' ')
		{
			if (c[this->row - 1][this->col] == ' ' && c[r][col] == ' ')
			{
				c[this->row][this->col] = ' ';
				this->row = r;
				this->col = col;
				c[this->row][this->col] = 'p';
				cout << "\n correct move";
			}

		}

		if (rdiff == 1 && coldiff == 0 && isupper(c[this->row][this->col]) && (c[r][col] == ' '))
		{


			c[this->row][this->col] = ' ';
			this->row = r;
			this->col = col;
			c[r][col] = 'P';
			cout << "\n your piece has been moved";


		}
		if (rdiff == -1 && coldiff == 0 && islower(c[this->row][this->col]) && (c[r][col] == ' '))
		{

			c[this->row][this->col] = ' ';

			this->row = r;
			this->col = col;
			c[r][col] = 'p';
			cout << "\n your piece has been moved";


		}
		if (isupper(c[this->row][this->col]) && rdiff == 1 && (coldiff == 1 || coldiff == -1))
		{
			if (islower(c[r][col]))
			{
				c[this->row][this->col] = ' ';
				this->row = r;
				this->col = col;
				c[this->row][this->col] = 'P';
			}
		}
		if (islower(c[this->row][this->col]) && rdiff == -1 && (coldiff == 1 || coldiff == -1))
		{
			if (isupper(c[r][col]))
			{
				c[this->row][this->col] = ' ';
				this->row = r;
				this->col = col;
				c[this->row][this->col] = 'p';
			}
		}
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
		if (r == this->row || col == this->col)
		{
			int rdiff = r - this->row;
			int cdiff = col - this->col;
			int rdir = (r > this->row) ? 1 : (r < this->row) ? -1 : 0;
			int cdir = (col > this->col) ? 1 : (col < this->col) ? -1 : 0;
			int i = this->row + rdir;
			int j = this->col + cdir;
			while (i != r || j != col)
			{
				if (c[i][j] == ' ')
				{
					i += rdir;
					j += cdir;
				}
				else
					return false;

			}
			if (isupper(c[r][col]) && islower(c[this->row][this->col]))
			{
				cout << c[r][col] << "Got killed !" << endl;
			}
			if (islower(c[r][col]) && isupper(c[this->row][this->col]))
			{
				cout << c[r][col] << "Got killed !" << endl;
			}
			c[this->row][this->col] = ' ';
			this->row = r;
			this->col = col;
			if (isblack == true)
				c[this->row][this->col] = 'r';
			else
				c[this->row][this->col] = 'R';
			return true;
		}
		return false;
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
		bool check = true;
		rdiff = rdiff < 0 ? -rdiff : rdiff;
		cdiff = cdiff < 0 ? -cdiff : cdiff;
		if (cdiff == rdiff)
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
		if (((rdiff >= -1 && rdiff <= 1) && (cdiff >= -1 && cdiff >= 1)))
		{
			c[this->row][this->col] = ' ';
			this->row = r;
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
		rdiff = rdiff < 0 ? -rdiff : rdiff;
		cdiff = cdiff < 0 ? -cdiff : cdiff;
		if (cdiff == 0 || rdiff == 0 || cdiff == rdiff)
		{
			int rdir = (r > this->row) ? 1 : (r == this->row) ? 0 : -1;
			int cdir = (col > this->col) ? 1 : (col == this->col) ? 0 : -1;
			int i = this->row + rdir;
			int j = this->col + cdir;
			while (i != r || j != col)
			{
				if (c[i][j] == ' ')
				{
					i += rdir;
					j += cdir;
				}
				else
					return false;
			}
			if (isupper(c[r][col]) && islower(c[this->row][this->col]))
			{
				cout << c[r][col] << "Got killed !" << endl;
			}
			if (islower(c[r][col]) && isupper(c[this->row][this->col]))
			{
				cout << c[r][col] << "Got killed !" << endl;
			}
			c[this->row][this->col] = ' ';
			this->row = r;
			this->col = col;
			if (isblack == true)
				c[this->row][this->col] = 'q';
			else
				c[this->row][this->col] = 'Q';
			return true;
		}
		return false;
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
		if (rdiff < 0) rdiff = -rdiff;
		if (cdiff < 0) cdiff = -cdiff;

		if ((rdiff == 2 && cdiff == 1) || (rdiff == 1 && cdiff == 2))
		{
			if (isupper(c[r][col]) && islower(c[this->row][this->col]))
			{
				cout << c[r][col] << "Got killed !" << endl;
			}
			if (islower(c[r][col]) && isupper(c[this->row][this->col]))
			{
				cout << c[r][col] << "Got killed !" << endl;
			}
			c[this->row][this->col] = ' ';
			this->row = r;
			this->col = col;
			if (isblack == true)
				c[this->row][this->col] = 'n';
			else
				c[this->row][this->col] = 'N';
			return true;
		}
		return false;
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
		arr[0][3] = 'Q';
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
	bool capture(int kr, int kc, char c[8][8])
	{
		int i = kr - 1;
		int j = kc - 1;
		while (i >= 0 && j >= 0)
		{
			if (c[i][j] != ' ') {
				if (isupper(c[kr][kc]) && (c[i][j] == 'b' || (c[i][j] == 'q')))
				{
					cout << "\n king is underattack";
					return true;

				}
				if (islower(c[kr][kc]) && (c[i][j] == 'B' || (c[i][j] == 'Q')))
				{
					cout << "\n king is underattack";
					return true;
				}


			}
			i--;
			j--;
		}
		i = kr + 1;
		j = kc + 1;
		while (i < 8 && j < 8)
		{
			if (c[i][j] != ' ') {
				if (isupper(c[kr][kc]) && (c[i][j] == 'b' || (c[i][j] == 'q')))
				{
					cout << "\n king is underattack";
					return true;

				}
				if (islower(c[kr][kc]) && (c[i][j] == 'B' || (c[i][j] == 'Q')))
				{
					cout << "\n king is underattack";
					return true;
				}


			}
			i++;
			j++;
		}
		i = kr + 1;
		j = kc - 1;
		while (i < 8 && j >= 0)
		{
			if (c[i][j] != ' ') {
				if (isupper(c[kr][kc]) && (c[i][j] == 'b' || (c[i][j] == 'q')))
				{
					cout << "\n king is underattack";
					return true;

				}
				if (islower(c[kr][kc]) && (c[i][j] == 'B' || (c[i][j] == 'Q')))
				{
					cout << "\n king is underattack";
					return true;
				}


			}
			i++;
			j--;
		}
		i = kr - 1;
		j = kc + 1;
		while (i >= 0 && j < 8)
		{
			if (c[i][j] != ' ') {
				if (isupper(c[kr][kc]) && (c[i][j] == 'b' || (c[i][j] == 'q')))
				{
					cout << "\n king is underattack";
					return true;

				}
				if (islower(c[kr][kc]) && (c[i][j] == 'B' || (c[i][j] == 'Q')))
				{
					cout << "\n king is underattack";
					return true;
				}


			}
			j++;
			i--;
		}

		for (int i = kr + 1; i < 8; i++)
		{
			if (c[i][kc] != ' ')
			{
				if (isupper(c[kr][kc]) && ((c[i][kc]) == 'r' || c[i][kc] == 'q'))
				{
					cout << "\n king is underattack";
					return true;

				}
				if (islower(c[kr][kc]) && ((c[i][kc]) == 'R' || c[i][kc] == 'Q'))
				{
					cout << "\n king is underattack";
					return true;

				}

			}
		}
		for (int i = kr - 1; i >= 0; i--)
		{
			if (c[i][kc] != ' ')
			{
				if (isupper(c[kr][kc]) && ((c[i][kc]) == 'r' || c[i][kc] == 'q'))
				{
					cout << "\n king is underattack";
					return true;

				}
				if (islower(c[kr][kc]) && ((c[i][kc]) == 'R' || c[i][kc] == 'Q'))
				{
					cout << "\n king is underattack";
					return true;
				}

			}
		}
		for (int i = kc + 1; i < 8; i++)
		{
			if (c[kr][i] != ' ')
			{
				if (isupper(c[kr][kc]) && ((c[kr][i]) == 'r' || c[kr][i] == 'q'))
				{
					cout << "\n king is underattack";
					return true;

				}
				if (islower(c[kr][kc]) && ((c[kr][i]) == 'R' || c[kr][i] == 'Q'))
				{
					cout << "\n king is underattack";
					return true;

				}

			}
		}
		for (int i = kc - 1; i >= 0; i--)
		{
			if (c[kr][i] != ' ')
			{
				if (isupper(c[kr][kc]) && ((c[kr][i]) == 'r' || c[kr][i] == 'q'))
				{
					cout << "\n king is underattack";
					return true;

				}
				if (islower(c[kr][kc]) && ((c[kr][i]) == 'R' || c[kr][i] == 'Q'))
				{
					cout << "\n king is underattack";
					return true;

				}

			}
		}
		if (c[kr][kc] == 'K')
		{
			if (kr + 1 < 8 && kc + 1 < 8 && c[kr + 1][kc + 1] == 'p')
				return true;

			if (kr + 1 < 8 && kc - 1 >= 0 && c[kr + 1][kc - 1] == 'p')
				return true;
		}
		if (c[kr][kc] == 'k')
		{
			if (kr - 1 >= 0 && kc + 1 < 8 && c[kr - 1][kc + 1] == 'P')
				return true;

			if (kr - 1 >= 0 && kc - 1 >= 0 && c[kr - 1][kc - 1] == 'P')
				return true;
		}
		if (c[kr][kc] == 'K')
		{
			if (kr - 2 >= 0 && kc - 1 >= 0 && c[kr - 2][kc - 1] == 'n')
				return true;

			if (kr - 2 >= 0 && kc + 1 < 8 && c[kr - 2][kc + 1] == 'n')
				return true;

			if (kr + 2 < 8 && kc - 1 >= 0 && c[kr + 2][kc - 1] == 'n')
				return true;

			if (kr + 2 < 8 && kc + 1 < 8 && c[kr + 2][kc + 1] == 'n')
				return true;

			if (kr - 1 >= 0 && kc - 2 >= 0 && c[kr - 1][kc - 2] == 'n')
				return true;

			if (kr + 1 < 8 && kc - 2 >= 0 && c[kr + 1][kc - 2] == 'n')
				return true;

			if (kr - 1 >= 0 && kc + 2 < 8 && c[kr - 1][kc + 2] == 'n')
				return true;

			if (kr + 1 < 8 && kc + 2 < 8 && c[kr + 1][kc + 2] == 'n')
				return true;
		}
		if (c[kr][kc] == 'k')
		{
			if (kr - 2 >= 0 && kc - 1 >= 0 && c[kr - 2][kc - 1] == 'N')
				return true;

			if (kr - 2 >= 0 && kc + 1 < 8 && c[kr - 2][kc + 1] == 'N')
				return true;

			if (kr + 2 < 8 && kc - 1 >= 0 && c[kr + 2][kc - 1] == 'N')
				return true;

			if (kr + 2 < 8 && kc + 1 < 8 && c[kr + 2][kc + 1] == 'N')
				return true;

			if (kr - 1 >= 0 && kc - 2 >= 0 && c[kr - 1][kc - 2] == 'N')
				return true;

			if (kr + 1 < 8 && kc - 2 >= 0 && c[kr + 1][kc - 2] == 'N')
				return true;

			if (kr - 1 >= 0 && kc + 2 < 8 && c[kr - 1][kc + 2] == 'N')
				return true;

			if (kr + 1 < 8 && kc + 2 < 8 && c[kr + 1][kc + 2] == 'N')
				return true;
		}
		return false;
	}
	bool checkmate(int kr, int kc, char c[8][8])
	{
		if (!capture(kr, kc, c))
			return false;
		int moves[8][2] = { {kr - 1,kc},
			{kr + 1,kc},
			{kr,kc - 1},
			{kr,kc + 1},
			{kr - 1,kc - 1},
			{kr - 1,kc + 1},
			{kr + 1,kc - 1},
			{kr + 1,kc + 1}
		};
		for (int i = 0; i < 8; i++)
		{
			int newr = moves[i][0];
			int newcol = moves[i][1];
			if (newr < 0 || newr >= 8 || newcol < 0 || newcol >= 8)
				continue;
			if (isupper(c[kr][kc]) && isupper(c[newr][newcol]))
				continue;
			if (islower(c[kr][kc]) && islower(c[newr][newcol]))
				continue;
			char temp = c[newr][newcol];
			c[newr][newcol] = c[kr][kc];
			c[kr][kc] = ' ';
			bool check = capture(newr, newcol, c);
			c[kr][kc] = c[newr][newcol];
			c[newr][newcol] = temp;
			if (!check)
				return false;

			return true;
		}
	}
};
int main()
{
	Board b;
	system("pause");
}