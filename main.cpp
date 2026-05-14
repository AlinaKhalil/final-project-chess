#include"chess.h"

int main()
{

	cout << "\n\n";
	cout << "#################################################\n";
	cout << "#                                               #\n";
	cout << "#             WELCOME TO THE                    #\n";
	cout << "#                CHESS GAME                     #\n";
	cout << "#                                               #\n";
	cout << "#################################################\n";
	cout << "\n";
	cout << "\t                                                \n";
	cout << "\n";
	cout << "\t      Prepare for Battle...\n";
	cout << "\n";

	system("pause");
	Board b;
	int sr, sc, dr, dc;
	bool wturn = true;
	bool bturn = false;
	int ans = 0;
	while (true)
	{
		if (wturn)
		{
			cout << "\n-------------------------------------------------\n";
			cout << "            WHITE'S TURN  (UPPERCASE)         \n";
			cout << "-------------------------------------------------\n";
		}
		else
		{
			cout << "\n-------------------------------------------------\n";
			cout << "            BLACK'S TURN  (lowercase)        \n";
			cout << "-------------------------------------------------\n";
		}

		cout << "Enter source row, source col, dest row, dest col: ";
		cin >> sr >> sc >> dr >> dc;

		try
		{
			ans = b.gameplay(sr, sc, dr, dc, wturn);
		}
		catch (const exception& e)
		{
			cout << e.what();
		}
		if (ans == -1)
		{
			system("pause");
			return 0;
		}

	}






}

