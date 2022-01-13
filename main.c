#include <stdio.h>
#include <stdlib.h> // system 함수를 사용을 위한 해더파일
#include <string.h> // memset 함수를 사용하기 위한 해더파일
#include <conio.h> // getch, khbit 함수를 사용하기 위한 해더파일

int lobby();
void draw_lobby(int select);
void draw_game(int y, int x);
int press(int y, int x);
int who_win();
void draw_end(int win);

int field[3][3];
int turn;
int turn_cnt;

char table[4] = { ' ', 'X', 'O', 'V' };

int main() {
	while (1) {
		memset(field, 0, sizeof(field));
		turn_cnt = 0;
		turn = 0;

		int select = lobby();
		if (select == 1) return 0;

		int x = 1, y = 1;
		int win = 0;
		draw_game(y, x);
		while (1) {
			// 키 입력을 받지 않은 경우
			// continue를 사용하는 명령어를 작성해주세요.

			int key = getch();
			if (key == 's' && y < 2) y += 1;
			if (key == 'w' && y > 0) y -= 1;
			if (key == 'd' && x < 2) x += 1;
			if (key == 'a' && x > 0) x -= 1;
			if (key == ' ') win = press(y, x);

			if (win) break;
			draw_game(y, x);
		}

		draw_end(win);
		// 키 입력을 기다리는 코드를 작성해주세요.
		int key = getch();
	}
}

int lobby() {
	int select = 0;
	draw_lobby(select);
	while (1) {
		// 키 입력을 받지 않은 경우 continue를 사용하는 명령어를 작성해주세요.

		// key 변수에 입력받은 키 값을 넣는 명령어를 작성해주세요.
		if (key == 'w') select -= 1;
		if (key == 's') select += 1;
		if (key == ' ') break;

		select = (select + 2) % 2;
		draw_lobby(select);
	}
	return select;
}

int who_win() {
	// 반복문을 사용하여 누가 이겼는지를 리턴해주는 코드를 작성하세요.
	// 아무도 이긴 상태가 아니라면 0, X가 이겼다면 1, O가 이겼다면 2를 리턴
	// 대각선 방향도 생각하는거 잊지 말아주세요!
}

void draw_lobby(int select) {
	system("cls");
	// 로비부분의 출력 화면을 작성하세요.
	// select 값에 따라 start, exit로 선택이 되도록 만들어주세요.
}

void draw_end(int win) {
	draw_game(-1, -1);
	printf("\n\n");
	if (win == 1) // X가 이긴 경우를 출력하는 부분
	if (win == 2) // O가 이긴 경우를 출력하는 부분
	if (win == 3) // 비긴 경우를 출력하는 부분
	printf("\n\npress any key to go lobby..");
}

void draw_game(int y, int x) {
	system("cls");
	char output[3][3][3] = {	// 3차원 배열을 쓰게 된 이유
								// "─"는 아스키코드에 포함되어있지 않아 문자열이고
								// 2차원 배열에 문자열을 담아야 했기 때문에
								// 2차원에 1차원 값을 넣어 3차원 배열이 되었습니다.
		{"─","─","─"},
		{"─","─","─"},
		{"─","─","─"}
	};
	output[y][x][0] = 'V';
	output[y][x][1] = '\0'; // 선택해둔 좌표에 V를 출력하도록 함
	printf("┌─%s┬─%s┬─%s┐", output[0][0], output[0][1], output[0][2]);  printf("\t% c turn\n", (turn == 0) ? 'X' : 'O');
	// 테이블의 1번에는 X, 2번에는 O가 있기 때문에 X와 O를 field값에 따라 출력 할 수 있게 됩니다.
	printf("│"); for (int i = 0; i < 3; i++) printf(" %c│", table[field[0][i]]);
	printf("\n├─%s┼─%s┼─%s┤\n", output[1][0], output[1][1], output[1][2]);
	printf("│"); for (int i = 0; i < 3; i++) printf(" %c│", table[field[1][i]]);
	printf("\n├─%s┼─%s┼─%s┤\n", output[2][0], output[2][1], output[2][2]);
	printf("│"); for (int i = 0; i < 3; i++) printf(" %c│", table[field[2][i]]);
	printf("\n└──┴──┴──┘");
}

int press(int y, int x) { // 해당 좌표에 돌이 없다면 돌을 놓는 함수
	if (field[y][x] != 0) return 0;
	field[y][x] = 1 + turn;
	turn = (turn + 1) % 2;
	turn_cnt++;

	int w = who_win();
	if (w) return w;
	if (turn_cnt == 9) return 3;
	return 0;
}
