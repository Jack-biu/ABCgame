#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>/* include standard library stdio.h for use of scanf() and printf() */ 
#include<windows.h> /*  for use of exit() and system*/ 
#include<stdlib.h> /* include standard library stdlib.h for use of exit() */ 
#include<string.h>/* for use of scan player_name*/ 
#include<time.h>/* for use of srand() and time() rand() */ 
struct Accounts {
	char username[50];
	char password[50];
	int history[5];
	/*
			(i) Number of rounds in a game
			(ii) Number of player wins
			(iii) Number of computer wins
			(iv) Number of draws
			(v) Whether or not the game was overall a win(1) draw or loss(-1)or even(0);
	*/
};

int main() {
	FILE* fp;
	int Game_accounts_number(); /*return the total number of accounts£¬if don't have the Game_Data file ,return -1 */
	struct Accounts* Register(int total_number, struct Accounts* p);/*To create an account,return the pointer of the new struct array */
	int Login(int total_number, struct Accounts* p);/*if username doesn't exist,return -1;else return the number of account*/
	void Menu();
	void Start_a_new_game(int n, struct Accounts* p);/*play  game*/
	void Review_your_game_history(int n, struct Accounts* p);
	void Clear_your_game_history(int n, struct Accounts* p);
	void Logout(int total_accounts_number, struct Accounts* p);/* the whole array will be written to the file*/

	printf("\nA-B-C game against the computer\n");/*if return -1,there is no user;else return number of user*/
	int total_number = Game_accounts_number();
	if (total_number < 1)
		total_number = 1;

	struct Accounts* p = (struct Accounts*)malloc(total_number * sizeof(struct Accounts));/*allocate space for the data*/
	/*if the file don't exist,create a file */
	if (Game_accounts_number() == -1) {
		fp = fopen("Game_Data.dat", "wb");
		fclose(fp);
	}
	/*if the file exists,open file and append data */
	else {
		fp = fopen("Game_Data.dat", "rb");
		fread(p, sizeof(struct Accounts), total_number, fp);
		fclose(fp);
	}

	int t = 0;/*To make the decision to register or login*/
	while (1) {
		int n = -1;/*the number of the account*/
		printf("\n1.Register         2.Login        3.Exit \n");
		printf("\nplease input the relevant number:");
		scanf("%d", &t);
		switch (t) {
		case 1:
			p = Register(total_number, p);
			total_number += 1;
			break;
		case 2:
			if (n = Login(total_number, p) != -1) {
				int stop = 0;
				while (stop != 1) {
					printf("\n1.Start a new name \n2.Review your game history \n3.Clear your game history\n4.Logout\n");
					printf("\nplease input the relevant number:");
					scanf("%d", &t);
					system("cls");
					switch (t) {
					case 1:Start_a_new_game(n, p); break;
					case 2:Review_your_game_history(n, p); break;
					case 3:Clear_your_game_history(n, p); break;
					case 4:Logout(total_number, p); stop = 1; break;
					default:printf("error"); break;
					}
				}
			}
			break;
		case 3:exit(0); break;
		default:printf("\nerror\n"); break;
		}
	}
	return 0;
}
struct Accounts* Register(int n, struct Accounts* p) {/*To create an account */
	struct Accounts* new = (struct Accounts*)malloc(sizeof(struct Accounts) * (n + 1));
	for (int i = 0; i < n; i++) {/*copy data to new struct array*/
		for (int j = 0; j < 5; j++)
			(new + i)->history[j] = (p + i)->history[j];
		strcpy((new + i)->username, (p + i)->username);
		strcpy((new + i)->password, (p + i)->password);
	}
	printf("\nplease input your username:");
	scanf("%s", (new + n)->username);
	printf("\nplease input your password:");
	scanf("%s", (new + n)->password);

	/* initialize data*/
	for (int i = 0; i < 5; i++) {
		(new + n)->history[i] = 0;
	}
	return new;
}
int Login(int total_number, struct Accounts* p) {/*if username doesn't exist,return -1;else return the number of account*/
	int n = -1;/*the number of account*/
	printf("\nplease input your username:");
	char t[50];
	scanf("%s", t);
	for (int i = 0; i < total_number; i++) {
		if (strcmp(p[i].username, t) == 0) {
			char t_password[50];
	
			do {
				printf("\nplease input your password:");
				scanf("%s", t_password);
				if (strcmp(p[i].password, t_password) != 0)
					printf("\nPassword Incorrect!\n");
			} while (strcmp(p[i].password, t_password) != 0);

			printf("\nLogin successful!\n");
			Sleep(1000);/* stop for a second*/
			system("cls");
			n = i;
			break;
		}
	}
	if (n == -1) {
		printf("\nThis username doesn't exist!   Please register!\n");
	}
	return n;
}
void Start_a_new_game(int n, struct Accounts* p) {
	srand((unsigned int)time(NULL));/* generate seed for rand()*/
	int Generate_computer_selection();/* output the selection of computer return  1(A)  2(B) 3(C)*/
	void Output_selection(int selection);/* draw the picture :  1(A)  2(B) 3(C)*/
	int selection_player = -1;
	while (1) {/* do a loop for restart game*/
		printf("\nA-B-C game against the computer\n");
		printf("\n1.A         2.B            3.C           4.Quit\n");
		printf("Please enter your selection:");
		scanf("%d", &selection_player);
		if (selection_player == 4) {
			break;
		}
		if (selection_player < 0 || selection_player > 4) {
			printf("\nInvalid input!!!\n");
			break;
		}
		Output_selection(selection_player);
		printf("\n333333333333333333333333333333333333333333333\n");
		Sleep(1000);/* stop for a second*/
		printf("\n222222222222222222222222222222222222222222222\n");
		Sleep(1000);/* stop for a second*/
		printf("\n111111111111111111111111111111111111111111111\n");
		Sleep(1000);/* stop for a second*/

		switch (Generate_computer_selection()) {/* output the selection of computer return  1(A)  2(B) 3(C)*/
		case 1:
			if (selection_player == 3) {
				
				p[n].history[1] += 1;
				break;
			}
			if (selection_player == 2) {
				printf("\nYou lose!!          Computer win!! \n");
				p[n].history[2] += 1;
				break;
			}
			if (selection_player == 1) {
				printf("\nYou and  Computer ended in a draw!!\n");
				p[n].history[3] += 1;
				break;
			}
		case 2:
			if (selection_player == 3) {
				printf("\nYou lose!!          Computer win!! \n");
				p[n].history[2] += 1;
				break;
			}
			if (selection_player == 2) {
				printf("\nYou and  Computer ended in a draw!!\n");
				p[n].history[3] += 1;
				break;
			}
			if (selection_player == 1) {
				printf("\nYou win!!           Computer lose!!\n");
				p[n].history[1] += 1;
				break;
			}
		case 3:
			if (selection_player == 3) {
				printf("\nYou and  Computer ended in a draw!!\n");
				p[n].history[3] += 1;
				break;
			}
			if (selection_player == 2) {
				printf("\nYou win!!           Computer lose!!\n");
				p[n].history[1] += 1;
				break;
			}
			if (selection_player == 1) {
				printf("\nYou lose!!          Computer win!! \n");
				p[n].history[2] += 1;
				break;
			}
		default:printf("\nerror\n"); break;
		}

		p[n].history[0] += 1;
		if (p[n].history[1] > p[n].history[2])
			p[n].history[4] = 1;
		else if (p[n].history[1] < p[n].history[2])
			p[n].history[4] = -1;
		else if (p[n].history[1] == p[n].history[2])
			p[n].history[4] = 0;
		int temp = p[n].history[0] - p[n].history[3];
		if (temp == 0) {
			temp = 1;
		}
		double  overall_win_percentages = (p[n].history[1] * 1.0) / temp * 100;
		printf("\nYour overall win percentages:%2.2f%%\n", overall_win_percentages);
		Sleep(1000);
		system("cls");
	}
}
void Review_your_game_history(int n, struct Accounts* p) {
	printf("\nNumber of rounds in a game:%d\n", p[n].history[0]);
	printf("\nNumber of player wins:%d\n", p[n].history[1]);
	printf("\nNumber of computer wins:%d\n", p[n].history[2]);
	printf("\nNumber of draws:%d\n", p[n].history[3]);
	int temp = p[n].history[0] - p[n].history[3];
	if (temp == 0)
		temp = 1;
	double  overall_win_percentages = (p[n].history[1] * 1.0) / temp * 100;
	printf("\nYour overall win percentages:%2.2f%%\n", overall_win_percentages);
	switch (p[n].history[4]) {
	case -1:printf("\nthe game was overall a loss\n"); break;
	case 0:printf("\nthe game was overall a even\n"); break;
	case 1:printf("\nthe game was overall a win\n"); break;
	default: printf("error"); break;
	}
}
void Clear_your_game_history(int n, struct Accounts* p) {
	for (int i = 0; i < 6; i++)
		p[n].history[i] = 0;
	printf("\nClear your game history successfully\n");
}
void Logout(int total_accounts_number, struct Accounts* p) {/* the whole array is written to the file*/
	FILE* fp = fopen("Game_Data.dat", "wb");
	fwrite(p, sizeof(struct Accounts), total_accounts_number, fp);
	fclose(fp);
}
int Game_accounts_number() {/*get the total number of accounts£¬if don't have the Game_Data file ,return -1 */
	FILE* fp = fopen("Game_Data.dat", "rb");
	if (!fp)/*if don't have the Game_Data file ,return -1 */
		return -1;
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp) / sizeof(struct Accounts);
	fclose(fp);
	return size;
}
int Generate_computer_selection() { /* output the selection of computer return  1(A)  2(B) 3(C)*/
	int i;
	i = rand() % 3 + 1;/* generate the computer selection*/
	switch (i) {
	case 1:
		printf("\nThe computer selection is A\n");
		break;
	case 2:
		printf("\nThe computer selection is B\n");
		break;
	case 3:
		printf("\nThe computer selection is C\n");
		break;
	default:
		printf("\nerror\n"); break;
	}
	Sleep(1000);/* stop for a second*/
	return i;
}
void Output_selection(int selection) {
	switch (selection) {
	case 1:
		printf("\nYour selection is A\n");
		break;
	case 2:
		printf("\nYour selection is B\n");
		break;
	case 3:
		printf("\nYour selection is C\n");
		break;
	default:
		printf("\nerror\n"); break;
	}
	Sleep(1000);/* stop for a second*/
}
void Output_result(int t) {
	if (t == 1) {
		printf("\nYou win!!           Computer lose!!\n");
	}
}

