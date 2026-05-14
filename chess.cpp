#include "chess.h"

Piece::Piece(int r, int c) : row(r), col(c)
{
	
}
int Piece::getRow()
{
	return row;
}
int Piece::getCol()
{
	return col;
}

Pawn::Pawn(int r, int c) : Piece(r, c) {}

bool Pawn::CanMove(int r, int col, char c[8][8])
{
	
	int rdiff = r - this->row;
	int coldiff = col - this->col;
	if (rdiff < -2 || rdiff>2 || coldiff < -1 || coldiff>1)
	{
		throw invalid_argument("invalid arguemnt");
	}
	if (r < 0 || r>7 || col < 0 || col>7)
	{
		throw  out_of_range("\n out of range");
	}
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

Rook::Rook(int r, int c) : Piece(r, c) {}

bool Rook::CanMove(int r, int col, char c[8][8])
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
	bool isblack = isupper(c[this->row][this->col]) ? false : true;
	if (r == this->row || col == this->col)
	{
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
			cout << c[r][col] << "Got killed !" << endl;
		if (islower(c[r][col]) && isupper(c[this->row][this->col]))
			cout << c[r][col] << "Got killed !" << endl;
		c[this->row][this->col] = ' ';
		this->row = r;
		this->col = col;
		c[this->row][this->col] = isblack ? 'r' : 'R';
		return true;
	}
	return false;
}

Bishop::Bishop(int r, int c) : Piece(r, c) {}

bool Bishop::CanMove(int r, int col, char c[8][8])
{
	if (isupper(c[r][col]) && isupper(c[this->row][this->col]))
	{
		cout << "It cannot kill its own piece." << endl;
		return false;
	}
	if (islower(c[r][col]) && islower(c[this->row][this->col]))
	{
		cout << "It cannot kill its own piece." << endl;
		return false;
	}
	bool isblack = isupper(c[this->row][this->col]) ? false : true;
	int rdiff = r - this->row;
	int cdiff = col - this->col;
	rdiff = rdiff < 0 ? -rdiff : rdiff;
	cdiff = cdiff < 0 ? -cdiff : cdiff;
	if (cdiff == rdiff)
	{
		int rdir = (r > this->row) ? 1 : -1;
		int cdir = (col > this->col) ? 1 : -1;
		int i = this->row + rdir;
		int j = this->col + cdir;
		while (i != r && j != col)
		{
			if (c[i][j] != ' ')
			{
				cout << "Path is blocked." << endl;
				return false;
			}
			i += rdir;
			j += cdir;
		}
		if (isupper(c[r][col]) && islower(c[this->row][this->col]))
			cout << c[r][col] << " Got killed!" << endl;
		if (islower(c[r][col]) && isupper(c[this->row][this->col]))
			cout << c[r][col] << " Got killed!" << endl;
		c[this->row][this->col] = ' ';
		this->row = r;
		this->col = col;
		c[this->row][this->col] = isblack ? 'b' : 'B';
		return true;
	}
	return false;
}

King::King(int r, int c) : Piece(r, c) {}

bool King::CanMove(int r, int col, char c[8][8])
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
	bool isblack = isupper(c[this->row][this->col]) ? false : true;
	int rdiff = r - this->row;
	int cdiff = col - this->col;
	if (((rdiff >= -1 && rdiff <= 1) && (cdiff >= -1 && cdiff >= 1)))
	{
		c[this->row][this->col] = ' ';
		this->row = r;
		this->col = col;
		c[this->row][this->col] = isblack ? 'k' : 'K';
		return true;
	}
	return false;
}

Queen::Queen(int r, int c) : Piece(r, c) {}

bool Queen::CanMove(int r, int col, char c[8][8])
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
	bool isblack = isupper(c[this->row][this->col]) ? false : true;
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
			cout << c[r][col] << "Got killed !" << endl;
		if (islower(c[r][col]) && isupper(c[this->row][this->col]))
			cout << c[r][col] << "Got killed !" << endl;
		c[this->row][this->col] = ' ';
		this->row = r;
		this->col = col;
		c[this->row][this->col] = isblack ? 'q' : 'Q';
		return true;
	}
	return false;
}

Knight::Knight(int r, int c) : Piece(r, c) {}

bool Knight::CanMove(int r, int col, char c[8][8])
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
	bool isblack = isupper(c[this->row][this->col]) ? false : true;
	int rdiff = r - this->row;
	int cdiff = col - this->col;
	if (rdiff < 0) rdiff = -rdiff;
	if (cdiff < 0) cdiff = -cdiff;
	if ((rdiff == 2 && cdiff == 1) || (rdiff == 1 && cdiff == 2))
	{
		if (isupper(c[r][col]) && islower(c[this->row][this->col]))
			cout << c[r][col] << "Got killed !" << endl;
		if (islower(c[r][col]) && isupper(c[this->row][this->col]))
			cout << c[r][col] << "Got killed !" << endl;
		c[this->row][this->col] = ' ';
		this->row = r;
		this->col = col;
		c[this->row][this->col] = isblack ? 'n' : 'N';
		return true;
	}
	return false;
}

Board::Board() :
	n{ Knight(0,1), Knight(0,6), Knight(7,1), Knight(7,6) },
	Q{ Queen(0,3),  Queen(7,3) },
	K{ King(0,4),   King(7,4) },
	B{ Bishop(0,2), Bishop(0,5), Bishop(7,2), Bishop(7,5) },
	R{ Rook(0,0),   Rook(0,7),   Rook(7,0),   Rook(7,7) },
	P{ Pawn(1,0),Pawn(1,1),Pawn(1,2),Pawn(1,3),Pawn(1,4),Pawn(1,5),Pawn(1,6),Pawn(1,7),
	   Pawn(6,0),Pawn(6,1),Pawn(6,2),Pawn(6,3),Pawn(6,4),Pawn(6,5),Pawn(6,6),Pawn(6,7) }
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			arr[i][j] = ' ';

	for (int i = 0; i < 8; i++)
		arr[1][i] = 'P';
	for (int i = 0; i < 8; i++)
		arr[6][i] = 'p';

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

bool Board::capture(int kr, int kc, char c[8][8])
{
	if (kr < 0 || kr > 7 || kc < 0 || kc > 7)
		throw out_of_range("King position out of board range");
	int i = kr - 1;
	int j = kc - 1;
	while (i >= 0 && j >= 0)
	{
		if (c[i][j] != ' ')
		{
			if (isupper(c[kr][kc]) && (c[i][j] == 'b' || c[i][j] == 'q')) 
			{
				cout << "\n king is underattack";
				return true; 
			}
			if (islower(c[kr][kc]) && (c[i][j] == 'B' || c[i][j] == 'Q'))
			{
				cout << "\n king is underattack"; 
				return true; 
			}
			break;
		}
		i--; j--;
	}
	i = kr + 1; j = kc + 1;
	while (i < 8 && j < 8)
	{
		if (c[i][j] != ' ')
		{
			if (isupper(c[kr][kc]) && (c[i][j] == 'b' || c[i][j] == 'q')) 
			{
				cout << "\n king is underattack"; 
				return true; 
			}
			if (islower(c[kr][kc]) && (c[i][j] == 'B' || c[i][j] == 'Q')) 
			{
				cout << "\n king is underattack"; 
				return true; 
			}
			break;
		}
		i++; j++;
	}
	i = kr + 1; j = kc - 1;
	while (i < 8 && j >= 0)
	{
		if (c[i][j] != ' ')
		{
			if (isupper(c[kr][kc]) && (c[i][j] == 'b' || c[i][j] == 'q'))
			{
				cout << "\n king is underattack";
				return true; 
			}
			if (islower(c[kr][kc]) && (c[i][j] == 'B' || c[i][j] == 'Q'))
			{ 
				cout << "\n king is underattack";
				return true; 
			}
			break;
		}
		i++; j--;
	}
	i = kr - 1; j = kc + 1;
	while (i >= 0 && j < 8)
	{
		if (c[i][j] != ' ')
		{
			if (isupper(c[kr][kc]) && (c[i][j] == 'b' || c[i][j] == 'q')) 
			{
				cout << "\n king is underattack";
				return true;
			}
			if (islower(c[kr][kc]) && (c[i][j] == 'B' || c[i][j] == 'Q'))
			{
				cout << "\n king is underattack";
				return true;
			}
			break;
		}
		i--; j++;
	}
	for (int i = kr + 1; i < 8; i++)
	{
		if (c[i][kc] != ' ')
		{
			if (isupper(c[kr][kc]) && (c[i][kc] == 'r' || c[i][kc] == 'q')) 
			{
				cout << "\n king is underattack";
				return true; 
			}
			if (islower(c[kr][kc]) && (c[i][kc] == 'R' || c[i][kc] == 'Q'))
			{
				cout << "\n king is underattack";
				return true;
			}
			break;
		}
	}
	for (int i = kr - 1; i >= 0; i--)
	{
		if (c[i][kc] != ' ')
		{
			if (isupper(c[kr][kc]) && (c[i][kc] == 'r' || c[i][kc] == 'q')) 
			{
				cout << "\n king is underattack";
				return true; 
			}
			if (islower(c[kr][kc]) && (c[i][kc] == 'R' || c[i][kc] == 'Q')) 
           {   
				cout << "\n king is underattack";
				return true; 
			}
			break;
		}
	}
	for (int i = kc + 1; i < 8; i++)
	{
		if (c[kr][i] != ' ')
		{
			if (isupper(c[kr][kc]) && (c[kr][i] == 'r' || c[kr][i] == 'q')) 
			{ 
				cout << "\n king is underattack";
			return true;
			}
			if (islower(c[kr][kc]) && (c[kr][i] == 'R' || c[kr][i] == 'Q')) 
			{
				cout << "\n king is underattack"; 
				return true;
			}
			break;
		}
	}
	for (int i = kc - 1; i >= 0; i--)
	{
		if (c[kr][i] != ' ')
		{
			if (isupper(c[kr][kc]) && (c[kr][i] == 'r' || c[kr][i] == 'q'))
			{
				cout << "\n king is underattack";
				return true; 
			}
			if (islower(c[kr][kc]) && (c[kr][i] == 'R' || c[kr][i] == 'Q'))
			{
				cout << "\n king is underattack";
				return true; 
			}
			break;
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

bool Board::checkmate(int kr, int kc, char c[8][8])
{
	if (kr < 0 || kr > 7 || kc < 0 || kc > 7)
		throw out_of_range("King position out of board range");
	if (!capture(kr, kc, c))
		return false;
	int moves[8][2] = {
		{kr - 1, kc}, {kr + 1, kc},
		{kr, kc - 1}, {kr, kc + 1},
		{kr - 1, kc - 1}, {kr - 1, kc + 1},
		{kr + 1, kc - 1}, {kr + 1, kc + 1}
	};
	for (int i = 0; i < 8; i++)
	{
		int newr = moves[i][0];
		int newcol = moves[i][1];
		if (newr < 0 || newr >= 8 || newcol < 0 || newcol >= 8)
		{
			continue;
		}
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
		
	}
	return true;
}

void Board::display()
{
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

int Board::gameplay(int sr, int sc, int dr, int dc, bool& whiteTurn)
{
	if (sr < 0 || sr > 7 ||sc < 0 || sc > 7 ||dr < 0 || dr > 7 ||dc < 0 || dc > 7)
	{
		throw out_of_range("Index out of range");
	}
	if (whiteTurn && (islower(arr[sr][sc])))
	{
		cout << "\n please move your correct piece;";
		return 0;

	}
	
	
	if (!whiteTurn && ( isupper(arr[sr][sc])))
	
	{
		cout << "\n please move your correct piece;";
		return 0;

	}
	char piece = arr[sr][sc];
	if (piece == ' ')
		throw invalid_argument("No piece selected");
	bool ans = true;
	if (piece == 'P' || piece == 'p')
	{
		for (int i = 0; i < 16; i++)
			if (P[i].getRow() == sr && P[i].getCol() == sc)
			{
				try
				{
					ans = P[i].CanMove(dr, dc, arr);

					if (ans == false)
						return 0;
					break;

				}
				catch (const exception& e) 
				{
					cout << "Pawn error: " << e.what() << endl;
					return 0;
				}
			}
	}
	else if (piece == 'R' || piece == 'r')
	{
		for (int i = 0; i < 4; i++)
		{
			if (R[i].getRow() == sr && R[i].getCol() == sc)
			{
				ans=R[i].CanMove(dr, dc, arr);
				if (ans == false)
					return 0;

				break;

			}
		}
	}
	else if (piece == 'N' || piece == 'n')
	{
		for (int i = 0; i < 4; i++)
			if (n[i].getRow() == sr && n[i].getCol() == sc)
			{
				ans=n[i].CanMove(dr, dc, arr);
				if (ans == false)
					return 0;
				break;
			}
	}
	else if (piece == 'B' || piece == 'b')
	{
		for (int i = 0; i < 4; i++)
			if (B[i].getRow() == sr && B[i].getCol() == sc)
			{
				ans=B[i].CanMove(dr, dc, arr);
				if (ans == false)
					return 0;
				break;
			}
	}
	else if (piece == 'Q' || piece == 'q')
	{
		for (int i = 0; i < 2; i++)
			if (Q[i].getRow() == sr && Q[i].getCol() == sc)
			{
				ans=Q[i].CanMove(dr, dc, arr);
				if (ans == false)
					return 0;
				break;
			}
	}
	else if (piece == 'K' || piece == 'k')
	{
		for (int i = 0; i < 2; i++)
			if (K[i].getRow() == sr && K[i].getCol() == sc)
			{
				ans=K[i].CanMove(dr, dc, arr);
				if (ans == false)
					return 0;
				break;
			}
	}
	cout << "\n\n\n";
	display();
	cout << "\n\n\n";
	if (whiteTurn)
		
	{
		try
		{
			capture(K[0].getRow(), K[0].getCol(), arr);
			bool a = checkmate(K[0].getRow(), K[0].getCol(), arr);
			if (a == true)
			{
				cout << "#################################################\n";
				cout << "#                                               #\n";
				cout << "#               GAME ENDED                      #\n";
				cout << "#                 BLACK WON                     #\n";
				cout << "#                                               #\n";
				cout << "#################################################\n";
				cout << "\n";
				cout << "\t             CHECKMATE \n";
				cout << "\n";
				return -1;
			}
		}
		catch(const exception& e)
		{
			cout << e.what();
		}
	}
	if (!whiteTurn)
	{
		try
		{
			capture(K[1].getRow(), K[1].getCol(), arr);
			bool a = checkmate(K[0].getRow(), K[0].getCol(), arr);
			if (a == true)
			{
				cout << "#################################################\n";
				cout << "#                                               #\n";
				cout << "#               GAME ENDED                      #\n";
				cout << "#                 WHITE WON                     #\n";
				cout << "#                                               #\n";
				cout << "#################################################\n";
				cout << "\n";
				cout << "\t             CHECKMATE \n";
				cout << "\n";
				return -1;
			}
		}
		catch (const exception& e)
		{
			cout << e.what();
		}
	}

	cout << "\n\n\n";
	display();
	if (whiteTurn)
		whiteTurn = false;
	else
		whiteTurn = true;

	return 1;
}
