//#include <iostream>
//#include <cstring>
//using namespace std;
//void Red(char arr[][5], int r1, int c1, int r2, int c2, int& green, int& draw)
//{
//	//To handle invalid conditions
//	while (((r1 == r2) && (c1 == c2)) || (arr[r1][c1] == ' ') || (arr[r1][c1] == 'G') || ((arr[r2][c2] == 'R') || (arr[r2][c2] == 'G')) ||
//		((r1 < 0) || (r1 > 4)) || ((c1 < 0) || (c1 > 4)) || ((r2 < 0) || (r2 > 4)) || ((c2 < 0) || (c2 > 4)))
//	{
//		cout << "Invalid Input." << endl;
//		cout << "Player red/Enter the bead position(row and column) : ";
//		cin >> r1 >> c1;
//		cout << "Player red/Enter the desired position(row and column) : ";
//		cin >> r2 >> c2;
//	}
//
//	//Conditions for possible positions
//	//For movements along horizontal line
//	if (r2 == r1)
//	{
//		if ((c2 == (c1 - 1)) || (c2 == (c1 + 1)))
//		{
//			arr[r2][c2] = 'R';
//			arr[r1][c1] = ' ';
//		}
//		else if (c2 == (c1 - 2))
//		{
//			if (arr[r1][c1 - 1] == 'G')         //for elimination
//			{
//				green--;
//				arr[r1][c1 - 1] = ' ';
//			}
//			arr[r2][c2] = 'R';
//			arr[r1][c1] = ' ';
//		}
//		else if (c2 == (c1 + 2))
//		{
//			if (arr[r1][c1 + 1] == 'G')         //for elimination
//			{
//				green--;
//				arr[r1][c1 + 1] = ' ';
//			}
//			arr[r2][c2] = 'R';
//			arr[r1][c1] = ' ';
//		}
//		else                                                 //For invalid move
//		{
//			cout << "Invalid Input." << endl;
//			cout << "Player red/Enter the bead position(row and column) : ";
//			cin >> r1 >> c1;
//			cout << "Player red/Enter the desired position(row and column) : ";
//			cin >> r2 >> c2;
//			Red(arr, r1, c1, r2, c2, green, draw);
//		}
//	}
//	else if (c2 == c1)                         //For movements along vertical line
//	{
//		if ((r2 == (r1 - 1)) || (r2 == (r1 + 1)))
//		{
//			arr[r2][c2] = 'R';
//			arr[r1][c1] = ' ';
//		}
//		else if (r2 == (r1 - 2))
//		{
//			if (arr[r1 - 1][c1] == 'G')         //for elimination
//			{
//				green--;
//				arr[r1 - 1][c1] = ' ';
//			}
//			arr[r2][c2] = 'R';
//			arr[r1][c1] = ' ';
//		}
//		else if (r2 == (r1 + 2))
//		{
//			if (arr[r1 + 1][c1] == 'G')         //for elimination
//			{
//				green--;
//				arr[r1 + 1][c1] = ' ';
//			}
//			arr[r2][c2] = 'R';
//			arr[r1][c1] = ' ';
//		}
//		else                                                 //For invalid move
//		{
//			cout << "Invalid Input." << endl;
//			cout << "Player red/Enter the bead position(row and column) : ";
//			cin >> r1 >> c1;
//			cout << "Player red/Enter the desired position(row and column) : ";
//			cin >> r2 >> c2;
//			Red(arr, r1, c1, r2, c2, green, draw);
//		}
//	}                                                      //For movements along diagonal
//	else if ((r1 == c1) || ((r1 == 0) && (c1 == 2)) || ((r1 == 0) && (c1 == 4)) || ((r1 == 1) && (c1 == 1)) ||
//		((r1 == 1) && (c1 == 3)) || ((r1 == 2) && (c1 == 0)) || ((r1 == 2) && (c1 == 4)) || ((r1 == 3) && (c1 == 1)) ||
//		((r1 == 4) && (c1 == 0)) || ((r1 == 4) && (c1 == 2)))
//	{
//		if (((r2 == (r1 - 1)) && (c2 == (c1 + 1))) || ((r2 == (r1 + 1)) && (c2 == (c1 - 1))))
//		{
//
//			arr[r2][c2] = 'R';
//			arr[r1][c1] = ' ';
//		}
//		else if (((r2 == (r1 + 1)) && (c2 == (c1 + 1))) || ((r2 == (r1 - 1)) && (c2 == (c1 - 1))))
//		{
//			arr[r2][c2] = 'R';
//			arr[r1][c1] = ' ';
//		}
//		else if ((r2 == (r1 - 2)) && (c2 == (c1 + 2)))
//		{
//
//			if (arr[r1 - 1][c1 + 1] == 'G')                  //For elimination
//			{
//				green--;
//				arr[r1 - 1][c1 + 1] = ' ';
//			}
//			arr[r2][c2] = 'R';
//			arr[r1][c1] = ' ';
//		}
//		else if ((r2 == (r1 + 2)) && (c2 == (c1 - 2)))
//		{
//			if (arr[r1 + 1][c1 - 1] == 'G')                  //For elimination
//			{
//				green--;
//				arr[r1 + 1][c1 - 1] = ' ';
//			}
//
//			arr[r2][c2] = 'R';
//			arr[r1][c1] = ' ';
//		}
//		else if ((r2 == (r1 + 2)) && (c2 == (c1 + 2)))
//		{
//			if (arr[r1 + 1][c1 + 1] == 'G')                  //For elimination
//			{
//				green--;
//				arr[r1 + 1][c1 + 1] = ' ';
//			}
//			arr[r2][c2] = 'R';
//			arr[r1][c1] = ' ';
//		}
//		else if ((r2 == (r1 - 2)) && (c2 == (c1 - 2)))
//		{
//			if (arr[r1 - 1][c1 - 1] == 'G')                   //For elimination
//			{
//				green--;
//				arr[r1 - 1][c1 - 1] = ' ';
//			}
//			arr[r2][c2] = 'R';
//			arr[r1][c1] = ' ';
//		}
//		else                                                 //For invalid move
//		{
//			cout << "Invalid Input." << endl;
//			cout << "Player red/Enter the bead position(row and column) : ";
//			cin >> r1 >> c1;
//			cout << "Player red/Enter the desired position(row and column) : ";
//			cin >> r2 >> c2;
//			Red(arr, r1, c1, r2, c2, green, draw);
//		}
//	}
//	else
//	{
//		int invalid = 0;
//		for (int i = 0; i < 5; i++)
//		{
//			for (int j = 0; j < 5; j++)
//			{
//				if (arr[i][j] == ' ')
//				{
//					invalid++;
//				}
//			}
//		}
//		if (invalid == 1)                             //No further moves
//		{
//			draw = 1;
//		}
//		else                                          //Invalid position
//		{
//			cout << "Invalid Input." << endl;
//			cout << "Player red/Enter the bead position(row and column) : ";
//			cin >> r1 >> c1;
//			cout << "Player red/Enter the desired position(row and column) : ";
//			cin >> r2 >> c2;
//			Red(arr, r1, c1, r2, c2, green, draw);
//		}
//	}
//}
//void Green(char arr[][5], int r1, int c1, int r2, int c2, int& red, int& draw)
//{
//	//To handle invalid conditions
//	while (((r1 == r2) && (c1 == c2)) || (arr[r1][c1] == ' ') || (arr[r1][c1] == 'R') || ((arr[r2][c2] == 'R') || (arr[r2][c2] == 'G')) ||
//		((r1 < 0) || (r1 > 4)) || ((c1 < 0) || (c1 > 4)) || ((r2 < 0) || (r2 > 4)) || ((c2 < 0) || (c2 > 4)))
//	{
//		cout << "Invalid Input." << endl;
//		cout << "Player green/Enter the bead position(row and column) : ";
//		cin >> r1 >> c1;
//		cout << "Player green/Enter the desired position(row and column) : ";
//		cin >> r2 >> c2;
//	}
//
//	//Conditions for possible positions
//	//For movements along horizontal line
//	if (r2 == r1)
//	{
//		if ((c2 == (c1 - 1)) || (c2 == (c1 + 1)))
//		{
//			arr[r2][c2] = 'G';
//			arr[r1][c1] = ' ';
//		}
//		else if (c2 == (c1 - 2))
//		{
//			if (arr[r1][c1 - 1] == 'R')         //for elimination
//			{
//				red--;
//				arr[r1][c1 - 1] = ' ';
//			}
//			arr[r2][c2] = 'G';
//			arr[r1][c1] = ' ';
//		}
//		else if (c2 == (c1 + 2))
//		{
//			if (arr[r1][c1 + 1] == 'R')         //for elimination
//			{
//				red--;
//				arr[r1][c1 + 1] = ' ';
//			}
//			arr[r2][c2] = 'G';
//			arr[r1][c1] = ' ';
//		}
//		else                                                 //For invalid move
//		{
//			cout << "Invalid Input." << endl;
//			cout << "Player green/Enter the bead position(row and column) : ";
//			cin >> r1 >> c1;
//			cout << "Player green/Enter the desired position(row and column) : ";
//			cin >> r2 >> c2;
//			Green(arr, r1, c1, r2, c2, red, draw);
//		}
//	}
//	else if (c2 == c1)                         //For movements along vertical line
//	{
//		if ((r2 == (r1 - 1)) || (r2 == (r1 + 1)))
//		{
//			arr[r2][c2] = 'G';
//			arr[r1][c1] = ' ';
//		}
//		else if (r2 == (r1 - 2))
//		{
//			if (arr[r1 - 1][c1] == 'R')         //for elimination
//			{
//				red--;
//				arr[r1 - 1][c1] = ' ';
//			}
//			arr[r2][c2] = 'G';
//			arr[r1][c1] = ' ';
//		}
//		else if (r2 == (r1 + 2))
//		{
//			if (arr[r1 + 1][c1] == 'R')         //for elimination
//			{
//				red--;
//				arr[r1 + 1][c1] = ' ';
//			}
//			arr[r2][c2] = 'G';
//			arr[r1][c1] = ' ';
//		}
//		else                                                 //For invalid move
//		{
//			cout << "Invalid Input." << endl;
//			cout << "Player green/Enter the bead position(row and column) : ";
//			cin >> r1 >> c1;
//			cout << "Player green/Enter the desired position(row and column) : ";
//			cin >> r2 >> c2;
//			Green(arr, r1, c1, r2, c2, red, draw);
//		}
//	}                                         //For movements along diagonal
//	else if ((r1 == c1) || ((r1 == 0) && (c1 == 2)) || ((r1 == 0) && (c1 == 4)) || ((r1 == 1) && (c1 == 1)) ||
//		((r1 == 1) && (c1 == 3)) || ((r1 == 2) && (c1 == 0)) || ((r1 == 2) && (c1 == 4)) || ((r1 == 3) && (c1 == 1)) ||
//		((r1 == 4) && (c1 == 0)) || ((r1 == 4) && (c1 == 2)))
//	{
//		if (((r2 == (r1 - 1)) && (c2 == (c1 + 1))) || ((r2 == (r1 + 1)) && (c2 == (c1 - 1))))
//		{
//			arr[r2][c2] = 'G';
//			arr[r1][c1] = ' ';
//		}
//		else if (((r2 == (r1 + 1)) && (c2 == (c1 + 1))) || ((r2 == (r1 - 1)) && (c2 == (c1 - 1))))
//		{
//			arr[r2][c2] = 'G';
//			arr[r1][c1] = ' ';
//		}
//		else if ((r2 == (r1 - 2)) && (c2 == (c1 + 2)))
//		{
//			if (arr[r1 - 1][c1 + 1] == 'R')                  //For elimination
//			{
//				red--;
//				arr[r1 - 1][c1 + 1] = ' ';
//			}
//			arr[r2][c2] = 'G';
//			arr[r1][c1] = ' ';
//		}
//		else if ((r2 == (r1 + 2)) && (c2 == (c1 - 2)))
//		{
//			if (arr[r1 + 1][c1 - 1] == 'R')                  //For elimination
//			{
//				red--;
//				arr[r1 + 1][c1 - 1] = ' ';
//			}
//			arr[r2][c2] = 'G';
//			arr[r1][c1] = ' ';
//		}
//		else if ((r2 == (r1 + 2)) && (c2 == (c1 + 2)))
//		{
//			if (arr[r1 + 1][c1 + 1] == 'R')                  //For elimination
//			{
//				red--;
//				arr[r1 + 1][c1 + 1] = ' ';
//			}
//			arr[r2][c2] = 'G';
//			arr[r1][c1] = ' ';
//		}
//		else if ((r2 == (r1 - 2)) && (c2 == (c1 - 2)))
//		{
//			if (arr[r1 - 1][c1 - 1] == 'R')                   //For elimination
//			{
//				red--;
//				arr[r1 - 1][c1 - 1] = ' ';
//			}
//			arr[r2][c2] = 'G';
//			arr[r1][c1] = ' ';
//		}
//		else                                                 //For invalid move
//		{
//			cout << "Invalid Input." << endl;
//			cout << "Player green/Enter the bead position(row and column) : ";
//			cin >> r1 >> c1;
//			cout << "Player green/Enter the desired position(row and column) : ";
//			cin >> r2 >> c2;
//			Green(arr, r1, c1, r2, c2, red, draw);
//		}
//	}
//	else                                                 //No further possible moves
//	{
//		int invalid = 0;
//		for (int i = 0; i < 5; i++)
//		{
//			for (int j = 0; j < 5; j++)
//			{
//				if (arr[i][j] == ' ')
//				{
//					invalid++;
//				}
//			}
//		}
//		if (invalid == 1)
//		{
//			draw = 1;
//		}
//		else
//		{
//			cout << "Invalid Input." << endl;
//			cout << "Player green/Enter the bead position(row and column) : ";
//			cin >> r1 >> c1;
//			cout << "Player green/Enter the desired position(row and column) : ";
//			cin >> r2 >> c2;
//			Green(arr, r1, c1, r2, c2, red, draw);
//		}
//	}
//
//}
//int main()
//{
//	char arr[5][5];
//
//	for (int i = 0; i < 5; i++)
//	{
//		for (int j = 0; j < 5; j++)
//		{
//			if (i == 2)
//			{
//				if (j == 2)
//				{
//					arr[i][j] = 32;
//				}
//				else if (j < 2)
//				{
//					arr[i][j] = 'R';
//				}
//				else
//				{
//					arr[i][j] = 'G';
//				}
//			}
//			if (i < 2)
//			{
//				arr[i][j] = 'R';
//			}
//			if (i > 2)
//			{
//				arr[i][j] = 'G';
//			}
//		}
//	}
//	cout << "   /Game Display/  " << endl;
//	cout << "" << endl;
//	cout << "  ";
//	for (int i = 0; i < 5; i++)
//	{
//		cout << "  " << i;
//	}
//	cout << endl;
//	cout << "   --------------" << endl;
//	for (int i = 0; i < 5; i++)
//	{
//		cout << i << "|";
//		for (int j = 0; j < 5; j++)
//		{
//			cout << "  " << arr[i][j];
//		}
//		cout << endl;
//	}
//	cout << "" << endl;
//	int red = 12, green = 12, draw = 0;
//	int r1, c1, r2, c2;
//	int toss, choice;
//	string turn;
//	cout << "\nEnter who will choose the number (red/green) : ";
//	cin >> turn;
//	while ((turn != "red") && (turn != "green"))
//	{
//		cout << "Invalid input.Enter again:";
//		cin >> turn;
//	}
//	cout << "Player/" << turn << ": Choose a digit ( 0 or 1 ) : ";
//	cin >> choice;
//	while ((choice != 0) && (choice != 1))
//	{
//		cout << "Invalid input.Enter again:";
//		cin >> choice;
//	}
//	srand(time(0));
//	toss = rand() % 2;
//	if (toss == choice)
//	{
//		cout << "You won the toss" << endl;
//		if (turn == "red")
//		{
//			while ((red != 0) && (green != 0) && (draw != 1))
//			{
//				cout << "Player red/Enter the bead position(row and column) : ";
//				cin >> r1 >> c1;
//				cout << "Player red/Enter the desired position(row and column) : ";
//				cin >> r2 >> c2;
//				Red(arr, r1, c1, r2, c2, green, draw);
//				//Display
//				cout << "" << endl;
//				cout << "  ";
//				for (int i = 0; i < 5; i++)
//				{
//					cout << "  " << i;
//				}
//				cout << endl;
//				cout << "   --------------" << endl;
//				for (int i = 0; i < 5; i++)
//				{
//					cout << i << "|";
//					for (int j = 0; j < 5; j++)
//					{
//						cout << "  " << arr[i][j];
//					}
//					cout << endl;
//				}
//				cout << "" << endl;
//				if ((green == 0) || (draw == 1))
//				{
//					break;
//				}
//				cout << "Player green/Enter the bead position(row and column) : ";
//				cin >> r1 >> c1;
//				cout << "Player green/Enter the desired position(row and column) : ";
//				cin >> r2 >> c2;
//				Green(arr, r1, c1, r2, c2, red, draw);
//				//Display
//				cout << "" << endl;
//				cout << "  ";
//				for (int i = 0; i < 5; i++)
//				{
//					cout << "  " << i;
//				}
//				cout << endl;
//				cout << "   --------------" << endl;
//				for (int i = 0; i < 5; i++)
//				{
//					cout << i << "|";
//					for (int j = 0; j < 5; j++)
//					{
//						cout << "  " << arr[i][j];
//					}
//					cout << endl;
//				}
//				cout << "" << endl;
//			}
//		}
//		else if (turn == "green")
//		{
//			while ((red != 0) && (green != 0) && (draw != 1))
//			{
//				cout << "Player green/Enter the bead position(row and column) : ";
//				cin >> r1 >> c1;
//				cout << "Player green/Enter the desired position(row and column) : ";
//				cin >> r2 >> c2;
//				Green(arr, r1, c1, r2, c2, red, draw);
//				//Display
//				cout << "" << endl;
//				cout << "  ";
//				for (int i = 0; i < 5; i++)
//				{
//					cout << "  " << i;
//				}
//				cout << endl;
//				cout << "   --------------" << endl;
//				for (int i = 0; i < 5; i++)
//				{
//					cout << i << "|";
//					for (int j = 0; j < 5; j++)
//					{
//						cout << "  " << arr[i][j];
//					}
//					cout << endl;
//				}
//				cout << "" << endl;
//				if ((red == 0) || (draw == 1))
//				{
//					break;
//				}
//				cout << "Player red/Enter the bead position(row and column) : ";
//				cin >> r1 >> c1;
//				cout << "Player red/Enter the desired position(row and column) : ";
//				cin >> r2 >> c2;
//				Red(arr, r1, c1, r2, c2, green, draw);
//				//Display
//				cout << "" << endl;
//				cout << "  ";
//				for (int i = 0; i < 5; i++)
//				{
//					cout << "  " << i;
//				}
//				cout << endl;
//				cout << "   --------------" << endl;
//				for (int i = 0; i < 5; i++)
//				{
//					cout << i << "|";
//					for (int j = 0; j < 5; j++)
//					{
//						cout << "  " << arr[i][j];
//					}
//					cout << endl;
//				}
//				cout << "" << endl;
//			}
//		}
//	}
//	else
//	{
//		cout << "You lose the toss" << endl;
//		if (turn == "red")
//		{
//			while ((red != 0) && (green != 0) && (draw != 1))
//			{
//				cout << "Player green/Enter the bead position(row and column) : ";
//				cin >> r1 >> c1;
//				cout << "Player green/Enter the desired position(row and column) : ";
//				cin >> r2 >> c2;
//				Green(arr, r1, c1, r2, c2, red, draw);
//				//Display
//				cout << "" << endl;
//				cout << "  ";
//				for (int i = 0; i < 5; i++)
//				{
//					cout << "  " << i;
//				}
//				cout << endl;
//				cout << "   --------------" << endl;
//				for (int i = 0; i < 5; i++)
//				{
//					cout << i << "|";
//					for (int j = 0; j < 5; j++)
//					{
//						cout << "  " << arr[i][j];
//					}
//					cout << endl;
//				}
//				cout << "" << endl;
//				if ((red == 0) || (draw == 1))
//				{
//					break;
//				}
//				cout << "Player red/Enter the bead position(row and column) : ";
//				cin >> r1 >> c1;
//				cout << "Player red/Enter the desired position(row and column) : ";
//				cin >> r2 >> c2;
//				Red(arr, r1, c1, r2, c2, green, draw);
//				//Display
//				cout << "" << endl;
//				cout << "  ";
//				for (int i = 0; i < 5; i++)
//				{
//					cout << "  " << i;
//				}
//				cout << endl;
//				cout << "   --------------" << endl;
//				for (int i = 0; i < 5; i++)
//				{
//					cout << i << "|";
//					for (int j = 0; j < 5; j++)
//					{
//						cout << "  " << arr[i][j];
//					}
//					cout << endl;
//				}
//				cout << "" << endl;
//			}
//		}
//		else if (turn == "green")
//		{
//			while ((red != 0) && (green != 0) && (draw != 1))
//			{
//				cout << "Player red/Enter the bead position(row and column) : ";
//				cin >> r1 >> c1;
//				cout << "Player red/Enter the desired position(row and column) : ";
//				cin >> r2 >> c2;
//				Red(arr, r1, c1, r2, c2, green, draw);
//				//Display
//				cout << "" << endl;
//				cout << "  ";
//				for (int i = 0; i < 5; i++)
//				{
//					cout << "  " << i;
//				}
//				cout << endl;
//				cout << "   --------------" << endl;
//				for (int i = 0; i < 5; i++)
//				{
//					cout << i << "|";
//					for (int j = 0; j < 5; j++)
//					{
//						cout << "  " << arr[i][j];
//					}
//					cout << endl;
//				}
//				cout << "" << endl;
//				if ((green == 0) || (draw == 1))
//				{
//					break;
//				}
//				cout << "Player green/Enter the bead position(row and column) : ";
//				cin >> r1 >> c1;
//				cout << "Player green/Enter the desired position(row and column) : ";
//				cin >> r2 >> c2;
//				Green(arr, r1, c1, r2, c2, red, draw);
//				//Display
//				cout << "" << endl;
//				cout << "  ";
//				for (int i = 0; i < 5; i++)
//				{
//					cout << "  " << i;
//				}
//				cout << endl;
//				cout << "   --------------" << endl;
//				for (int i = 0; i < 5; i++)
//				{
//					cout << i << "|";
//					for (int j = 0; j < 5; j++)
//					{
//						cout << "  " << arr[i][j];
//					}
//					cout << endl;
//				}
//				cout << "" << endl;
//			}
//		}
//	}
//
//	if (draw == 1)
//	{
//		cout << "Game Draw" << endl;
//	}
//	else if (red == 0)
//	{
//		cout << "Player Green wins!" << endl;
//	}
//	else if (green == 0)
//	{
//		cout << "Player Red wins!" << endl;
//	}
//
//}