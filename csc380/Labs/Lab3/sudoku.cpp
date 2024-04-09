
#include "sudoku.h"
#include <iostream>
#include <sstream>
using namespace std;

string Sudoku::Read_From_Stdin()
{
  int i, j;
  char c;
  ostringstream oss;        // This is to build an error string.

  /* Read 81 characters, error checking for legal characters, and EOF.
 *      The try/catch is nice because you want to clear the grid on all errors. */

  Grid.clear();
  Grid.resize(9);

  try {
    for (i = 0; i < 9; i++) {
      for (j = 0; j < 9; j++) {

        /* Handle EOF -- if nothing was read, return "EOF"; otherwise return an error. */

        if (!(cin >> c)) {
          if (i == 0 && j == 0 && cin.eof()) throw((string) "EOF");
          throw((string) "Bad Sudoku File -- not enough entries");
        }

        /* Error check the digit. */

        if (c == '-' || (c >= '0' && c <= '9')) {
          Grid[i].push_back(c);
        } else {
          oss << "Bad character at row " << i << ", column " << j << ": " << c ;
          throw(oss.str());
        }
      }
    }

    /* Now error check for bad rows columns and panels */

    for (i = 0; i < 9; i++) {
      if (!Is_Row_Valid(i)) {
        oss << "Duplicate entry in row " << i;
        throw(oss.str());
      }
    }
    for (i = 0; i < 9; i++) {
      if (!Is_Col_Valid(i)) {
        oss << "Duplicate entry in column " << i;
        throw(oss.str());
      }
    }
    for (i = 0; i < 9; i += 3) {
      for (j = 0; j < 9; j += 3) {
        if (!Is_Panel_Valid(i, j)) {
          oss << "Duplicate entry in panel starting at row " << i << " and column " << j;
          throw(oss.str());
        }
      }
    }

    /* Clear the grid when you get an error. */

  } catch (const string s) {
    Grid.clear();
    return s;
  }


  /* Otherwise, return "" on success. */

  return "";
}

/* Print_Screen() prints the grid, putting a space between characters, an extra
 *    space between panel columns, and an extra line between panel rows. */

void Sudoku::Print_Screen() const
{
  size_t i, j;

  for (i = 0; i < Grid.size(); i++) {
    for (j = 0; j < Grid[i].size(); j++) {
      if (j != 0) cout << " ";
      cout << Grid[i][j];
      if (j == 2 || j == 5) cout << " ";
    }
    cout << endl;
    if (i == 2 || i == 5) cout << endl;
  }
}

void Sudoku::Print_Convert() const
{
}

bool Sudoku::Solve()
{
  return Recursive_Solve(0, 0);
}

void Sudoku::Clear()
{
  Grid.clear();
}

/* I use a boolean vector called check to check for row validity.  For each digit i,
 *    check[i] is false if I haven't seen the digit, and true if I have.  That way,
 *       I can identify when I have seen a digit twice. */

bool Sudoku::Is_Row_Valid(int r) const
{
  size_t i;
  vector <bool> check;
  char c;

  check.resize(9, false);
  for (i = 0; i < 9; i++) {
    c = Grid[r][i];
    if (c != '-') {
      c -= '1';
      if (check[c]) return false;
      check[c] = true;
    }
  }
  return true;
}

bool Sudoku::Is_Col_Valid(int col) const
{
  size_t i;
  vector <bool> check;
  char c;

  check.resize(9, false);
  for (i = 0; i < 9; i++) {
    c = Grid[i][col];
    if (c != '-') {
      c -= '1';
      if (check[c]) return false;
      check[c] = true;
    }
  }
  return true;
}

bool Sudoku::Is_Panel_Valid(int sr, int sc) const
{
  int r;
  int c;
  vector <bool> check;
  char ch;

  check.resize(9, false);
  for (r = sr; r < sr+3; r++) {
    for (c = sc; c < sc+3; c++) {
      ch = Grid[r][c];
      if (ch != '-') {
        ch -= '1';
        if (check[ch]) return false;
        check[ch] = true;
      }
    }
  }
  return true;
}

/* Recursive_Solve assumes that all elements in rows less than r, and in
 *    row r less than c, have been filled in and the grid has been tested.
 *       This will find the first empty cell, and then test every digit, calling
 *          Recursive_Solve() recursively, to see if the puzzle can be solved with
 *             that digit. */

bool Sudoku::Recursive_Solve(int r, int c)
{
  int i;

  if (Grid.size() == 0) return false;

  /* Skip all non-dash characters */

  while (r < 9 && Grid[r][c] != '-') {
    c++;
    if (c == 9) {
      r++;
      c = 0;
    }
  }

  /* Base case -- we're done.  Return success! */

  if (r == 9) return true;

  /* Try each value.  If successful, then return true. */

  for (i = '1'; i <= '9'; i++) {
    Grid[r][c] = i;
    if (Is_Row_Valid(r) &&
        Is_Col_Valid(c) &&
        Is_Panel_Valid(r-r%3, c-c%3) &&
        Recursive_Solve(r, c)) {
      return true;
    }
  }

  /* If unsuccessful, reset the element and return false. */

  Grid[r][c] = '-';
  return false;
}
