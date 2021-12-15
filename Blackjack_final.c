#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int idx = 0;
int money = 500;
int bet = 0;

struct Card {
	int type;
	int score;
}desk[52], cards[52];

struct Player{
	char name[50];
	int score;
	int number_of_card;
	struct Card cards[52];
 
}P1, P2;

int shuffle(struct Card cards[])
{
	int i, j;
	for (i=0;i<52;i++){
		desk[i].type = (i/13+3);
		desk[i].score = i%13 + 1;
	}
		
	srand(time(NULL));
	for (i = 0; i < 52; i++)
	{
		do{
			j = rand() % 52;
		} while (desk[j].score == 0);
		
		cards[i].type = desk[j].type;
		cards[i].score = desk[j].score;
		desk[j].score = 0;
	}

	return 0;
}

int convert_jkq(struct Card card)
{
	if((card.score==11) ||(card.score==12) ||(card.score==13)){
		return 10;
	}else{
		return card.score;
	}	
}

int get_score(struct Card card){
	int score;
	
	if(card.score == 1){
		score = 0;
	}else if(convert_jkq(card) == 10){
		score = 10;
	}else{
		score = card.score;
	}
	
	return score;
}

int chcek_ace(struct Card card){
	int i,d,score=0;
	if (card.score == 1){
		printf("choose A value of the card, input 'y' for 11 or 'n' for 1 : ");
		do{
			d = getchar();
		} while (d!='y' && d!='n');
		
		if (d == 'y'){
			printf("You've chosen value 11 for card A.\n");
			score = 11;
		}else if(d == 'n'){
			printf("You've chosen value 1 for card A.\n");
			score = 1;
		}
	}
	return score;
}
		
struct Card pick(char player_name[50]){
	
	if(strcmp(player_name, "P1") == 0){
		P1.number_of_card++;
		P1.cards[P1.number_of_card] = cards[idx];
		P1.score += get_score(cards[idx]);
	}else{
		P2.number_of_card++;
		P2.cards[P2.number_of_card] = cards[idx];
		P2.score += get_score(cards[idx]);
	}
	idx++;
	return cards[idx];
}

void display(struct Card card)
{
	if(card.score == 1 ){
		printf("*******\n");
		printf("*     *\n");
		printf("* %c   *\n", card.type);
		printf("*   A *\n");
		printf("*     *\n");
		printf("*******\n");
	}else if(card.score >= 2 && card.score <= 10){
		printf("*******\n");
		printf("*     *\n");
		printf("* %c   *\n", card.type);
		printf("*  %2d *\n", card.score);
		printf("*     *\n");
		printf("*******\n");
	}else if(card.score == 11){
		printf("*******\n");
		printf("*     *\n");
		printf("* %c   *\n", card.type);
		printf("*   J *\n");
		printf("*     *\n");
		printf("*******\n");
	}else if(card.score == 12){
		printf("*******\n");
		printf("*     *\n");
		printf("* %c   *\n", card.type);
		printf("*   Q *\n");
		printf("*     *\n");
		printf("*******\n");
	}else if(card.score == 13){
		printf("*******\n");
		printf("*     *\n");
		printf("* %c   *\n", card.type);
		printf("*   K *\n");
		printf("*     *\n");
		printf("*******\n");
	}
}


void record_history(struct Player winner, struct Player loser){
	FILE *append;
	append = fopen("history.txt","a");
	
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
  
  	int winner_score=0, loser_score=0;
  	int i;
  	
  	for(i=0; i<5; i++){
  		winner_score += convert_jkq(winner.cards[i]);
  		loser_score += convert_jkq(loser.cards[i]);
	}
	fprintf(append, "%s %d : %d %s : %d-%02d-%02d %02d:%02d:%02d %d\n", winner.name, winner_score, loser_score, loser.name, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec ,money);
}

int check_winner(){
	if(P1.score > 21){
		printf("Sum of player's cards now = %d\n\n",P1.score);
		printf("Computer win!\n");
		money = money - bet;
		record_history(P2, P1);
		return 1;
	}else if (P1.score == 21){
		printf("Sum of player's cards now = %d\n\n",P1.score);
		printf("Player win!\n");
		money = money + bet;
		record_history(P1, P2);
		return 1;
	}
	return 0;
}

int play(void)
{
	int i;
	int idx = 0;

	
	strcpy(P1.name, "Player");
	strcpy(P2.name, "Computer");
	P1.score = 0;
	P2.score = 0;
	P1.number_of_card = -1;
	P2.number_of_card = -1;
	
	for(i=0; i<52; i++){
		P1.cards[i].score = 0;	
		P2.cards[i].score = 0;
	}
	
	char go_on;
	char d;
		
	printf("\n===========BLACK JACK===========");
	printf("\n=====Press Enter to start=====");
	fflush(stdin);
	do{
	printf("\nEnter an amount you would like to bet.\n");
	printf("\nYour balance is: %d ",money);
	printf("\nEnter here: ", money);
	scanf("%d",&bet);
		} while (bet > money);
	do{
		go_on = getchar();
	} while (go_on != '\n');
	system("cls");
	
	shuffle(cards);
	
	for(i=0; i<2; i++){
		pick("P1");
		pick("P2");	
	}

	printf("Cards of computer:\n");
	display(P2.cards[0]);
	printf("\n");
	
	printf("Cards of player:\n");
	display(P1.cards[0]);
	display(P1.cards[1]);
	
	for(i=0; i<=P1.number_of_card; i++){
		P1.score += chcek_ace(P1.cards[i]);
	}
	
	if (check_winner() == 1){
		return 0;
	}
	
	printf("Your card total now = %d\n\n",P1.score);
	
	i=0;
	while(1){
		char j = 'n';
		
		printf("Want more cards? (y/n )");
		do{
			j = getchar();
		} while (j!='y' &&j!='n');
		
		if (j=='y'){
			printf("You've got another card now.\n");
			pick("P1");
			
			printf("and your card %d is:\n", P1.number_of_card+1);
			display(P1.cards[P1.number_of_card]);
			
			P1.score += chcek_ace(P1.cards[P1.number_of_card]);
			
			if (check_winner() == 1){
				return 0;
			}	
			
			printf("Your card total now = %d\n\n",P1.score);	
		
		}else{
			printf("Your card total now = %d\n\n",P1.score);
			break;
		}
	}
	
	printf("Computer's cards:\n");
	display(P2.cards[0]);
	display(P2.cards[1]);

	if (P2.cards[0].type == 1  && P2.cards[1].type == 1){
		P2.score = 12;
		printf("Computer card total now = %d\n\n", P2.score);
	}else if ((convert_jkq(P2.cards[0])) + (convert_jkq(P2.cards[1])) == 1){
		P2.score=21;
		printf("Computer card total now = %d\n\n", P2.score);
		printf("Computer win!\n");
		money = money - bet;
		record_history(P2, P1);
		return 1;
	}else if (P2.cards[0].type ==1 || P2.cards[1].type == 1){
		P2.score = (P2.cards[0].score + P2.cards[1].score)+(rand()%2)*10;
		printf("Computer card total now = %d\n\n", P2.score);
	}else{
		P2.score = (convert_jkq(P2.cards[0])) + (convert_jkq(P2.cards[1]));
		printf("Computer card total now = %d\n\n", P2.score);
	}
	
	while(1){
		if (P2.score>21 || P1.score>P2.score){
			printf("Congrats! You win.\n");
			money = money + bet;
			record_history(P1, P2);
			return 0;
		}else if (P1.score == P2.score){
			printf("Oh, player and computer get the same score!\n");
			money = money;
			record_history(P1, P2);
			return 0;
		}else if (P1.score < P2.score){
			printf("Computer win!\n");
			money = money - bet;
			record_history(P2, P1);
			return 0;
		}
		
		pick("P2");
		printf("Computer's card %d is:\n", P2.number_of_card+1);
		display(P2.cards[P2.number_of_card]);
		
		if (P2.cards[P2.number_of_card].type == 1){
			if (P2.score+11 <= 21){
				printf("Computer has chosen A as 11\n");
				P2.score = P2.score+11;
				printf("Computer card total now = %d\n\n", P2.score);
			}else{
				printf("Computer has chosen A as 1\n");
				P2.score = P2.score+1;
				printf("Computer card total now = %d\n\n", P2.score);
			}
		}else{
			P2.score = P2.score + convert_jkq(P2.cards[P2.number_of_card]);
			printf("Computer card total now = %d\n\n", P2.score);
		}		
	}
	bet = 0;
	return 0;
}

int main(void)
{
	char play_again;
  
	do{
		play();
		
		printf("\n Want to play again (y/n): ");
		fflush(stdin);
		do{
			play_again = getchar();
		} while (play_again!='y' && play_again!='n');
		
		if (play_again == 'y'){
			system("cls");
		}
	
	} while (play_again != 'n');
	system("cls");
	printf("\n=== GOOD LUCK ===\n");
	return 0;
}