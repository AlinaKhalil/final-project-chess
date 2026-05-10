
#pragma once
#include <iostream>
#include<exception>
#include<stdexcept>

#define RESET       "\033[0m"
#define BG_DARK     "\033[48;5;94m"
#define BG_LIGHT    "\033[48;5;223m"
#define BLACK_PIECE "\033[30m"
#define WHITE_PIECE "\033[38;5;111m"

using namespace std;

class Piece
{
protected:
    int row;
    int col;
public:
    int getRow();
    int getCol();
    Piece(int r, int c);
    virtual bool CanMove(int r, int col, char c[8][8]) = 0;
};

class Pawn : public Piece
{
public:
    Pawn(int r, int c);
    bool CanMove(int r, int col, char c[8][8]) override;
};

class Rook : public Piece
{
public:
    Rook(int r, int c);
    bool CanMove(int r, int col, char c[8][8]) override;
};

class Bishop : public Piece
{
public:
    Bishop(int r, int c);
    bool CanMove(int r, int col, char c[8][8]) override;
};

class King : public Piece
{
public:
    King(int r, int c);
    bool CanMove(int r, int col, char c[8][8]) override;
};

class Queen : public Piece
{
public:
    Queen(int r, int c);
    bool CanMove(int r, int col, char c[8][8]) override;
};

class Knight : public Piece
{
public:
    Knight(int r, int c);
    bool CanMove(int r, int col, char c[8][8]) override;
};

class Board
{

    char arr[8][8];
    Knight n[4];
    Queen  Q[2];
    King   K[2];
    Bishop B[4];
    Rook   R[4];
    Pawn   P[16];
public:
    Board();
    bool capture(int kr, int kc, char c[8][8]);
    bool checkmate(int kr, int kc, char c[8][8]);
    void display();
    int gameplay(int sr, int sc, int dr, int dc, bool &whiteTurn);
};