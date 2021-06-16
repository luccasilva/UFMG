//Bibliotecas
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include <math.h>
//----------------------------------------------------------------------------//

//Defines
#define SCREEN_W 480
#define SCREEN_H 656
#define INFO_H 56
#define FPS 60
#define MARGIN 7

#define MAX_MOVES 10

#define BACKGROUND_FILE "background.jpg"
#define SCOREPIC_FILE "scorepic.jpg"

#define N_TYPES 5
#define N_COLS 6
#define N_LINHAS 9

const int COL_W = SCREEN_W/N_COLS;
const int LIN_W = (SCREEN_H - INFO_H)/N_LINHAS;
//----------------------------------------------------------------------------//

//Cria o struct do doce
typedef struct Candy{
	int type;
	int active;
	ALLEGRO_COLOR cor;
} Candy;

//Fonte
ALLEGRO_FONT *size_f;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *scorepic = NULL;

Candy M[N_LINHAS][N_COLS];

int moves = MAX_MOVES;
int score = 0;
int game_running = 1;
char my_score[100], my_moves[100];
//----------------------------------------------------------------------------//

//Funcoes

///////////--// Funcao de delay //--///////////
void pause(ALLEGRO_TIMER *timer, float seconds)
{
	al_stop_timer(timer);
	al_rest(seconds);
	al_start_timer(timer);
}

///////////--// Funcao que repoe os candy na tela //--///////////
void replaceCandy(){
	int i,j;
	Candy aux;
	for(j=N_COLS-1; j>=0; j--){
		for(i=N_LINHAS-1; i>=0; i--){
			//se tiver algum candy type 0
			if (M[i][j].active==0) {
				//troca por um aleatorio
				M[i][j].type = rand()%5+1;
				M[i][j].active = 1;
				if (M[i][j].type == 1) {
					M[i][j].cor = al_map_rgb(140, 88, 36);
				}
				if (M[i][j].type == 2) {
					M[i][j].cor = al_map_rgb(131, 0, 0);
				}
				if (M[i][j].type == 3) {
					M[i][j].cor = al_map_rgb(89, 0, 179);
				}
				if (M[i][j].type == 4) {
					M[i][j].cor = al_map_rgb(20, 94, 32);
				}
				if (M[i][j].type == 5) {
					M[i][j].cor = al_map_rgb(149, 153, 29);
				}
			}
		}
	}
}

///////////--// Funcao que desce os candy na tela //--///////////
void dropCandy(){
	int i,j,existe=1;
	Candy aux;
	//Enquanto tiver candy na tela
	while (existe!=0) {
	existe=0;
	//desce todos os candy 0 excluindo a primeira linha
	for(j=N_COLS-1; j>=0; j--){
		for(i=N_LINHAS-1; i>0; i--){
			//se tiver algum candy active 0
			if ((M[i][j].active==0)&&(M[i-1][j].active!=0)) {
				existe=existe+1;
				//troca com o de cima
				aux = M[i][j];
				M[i][j] = M[i-1][j];
				M[i-1][j] = aux;
				}
			}
		}
	}
}

///////////--// Funcao que destroi os candy da sequencia //--///////////
void destroyCandy(int* score){
	int i,j;
	//Verifica todas as Combinacoes na Horizontal (sem ser cominação de 0)
	for(i=0; i<N_LINHAS; i++){
		for(j=0; j<N_COLS-2; j++){
			if ((M[i][j].type==M[i][j+1].type)&&(M[i][j+1].type==M[i][j+2].type)) {
				//PONTUAÇÃO
				*score = *score + 100;
				M[i][j].active = 0;
				M[i][j].cor = al_map_rgb(211,211,211);
				M[i][j+1].active = 0;
				M[i][j+1].cor = al_map_rgb(211,211,211);
				M[i][j+2].active = 0;
				M[i][j+2].cor = al_map_rgb(211,211,211);
			}
		}

 	}
 	//Verifica todas as Combinacoes na Vertical
 for(i=0; i<N_LINHAS-2; i++){
	 for(j=0; j<N_COLS; j++){
		 if ((M[i][j].type==M[i+1][j].type)&&(M[i+1][j].type==M[i+2][j].type)) {
			 //PONTUAÇÃO
			 *score = *score + 100;
			 M[i][j].active = 0;
			 M[i][j].cor = al_map_rgb(211,211,211);
			 M[i+1][j].active = 0;
			 M[i+1][j].cor = al_map_rgb(211,211,211);
			 M[i+2][j].active = 0;
			 M[i+2][j].cor = al_map_rgb(211,211,211);
		 }
	 }
	}
}


///////////--// Funcao que Verifica se existe alguma combinacao //--///////////
int verifyCombination(){
	int i,j;
	int validate;
	validate = 0;
	//Verifica todas as Combinacoes na Horizontal
	for(i=0; i<N_LINHAS; i++){
		for(j=0; j<N_COLS-2; j++){
			if ((M[i][j].type!=0)&&(M[i][j].type==M[i][j+1].type)&&(M[i][j+1].type==M[i][j+2].type)) {
				validate = validate + 1;
			}
		}
 	}
 	//Verifica todas as Combinacoes na Vertical
 for(i=0; i<N_LINHAS-2; i++){
	 for(j=0; j<N_COLS; j++){
		 if ((M[i][j].type!=0)&&(M[i][j].type==M[i+1][j].type)&&(M[i+1][j].type==M[i+2][j].type)) {
			 validate = validate + 1;
		  }
	  }
	}
	return validate;
}


///////////--// Funcao de preenchimento da matriz com candies aleatorios //--///////////
void initCandies(){
	int i,j;
	for(i=0; i<N_LINHAS; i++){
		for(j=0; j<N_COLS; j++){
			M[i][j].type = rand()%5+1;
			M[i][j].active = 1;
			if (M[i][j].type == 1) {
				M[i][j].cor = al_map_rgb(140, 88, 36);
			}
			if (M[i][j].type == 2) {
				M[i][j].cor = al_map_rgb(131, 0, 0);
			}
			if (M[i][j].type == 3) {
				M[i][j].cor = al_map_rgb(89, 0, 179);
			}
			if (M[i][j].type == 4) {
				M[i][j].cor = al_map_rgb(20, 94, 32);
			}
			if (M[i][j].type == 5) {
				M[i][j].cor = al_map_rgb(149, 153, 29);
			}
		}
	}
}

///////////--// Funcoes que pega o inicio das coordenadas //--///////////
//INICIO NO AL e SEMPRE TOP-LEFT
int getXCoord(int col){
	return col*COL_W;
	}
int getYCoord(int lin){
	return lin*LIN_W;
	}

///////////--// Funcao pra desenhar candies //--///////////
void desenhaCandy(Candy c,int lin,int col){
	int x = getXCoord(col);
	int y = getYCoord(lin);

	if(c.type == 1){
		al_draw_filled_triangle(x + MARGIN, y + LIN_W - MARGIN, x + COL_W - MARGIN, y + LIN_W - MARGIN, x + COL_W / 2, y + MARGIN, c.cor);
	}

	else if(c.type == 2){
		al_draw_filled_rectangle(x + 2*MARGIN, y + 2*MARGIN, x - 2*MARGIN + COL_W, y - 2*MARGIN + LIN_W, c.cor);
	}

	else if(c.type == 3){
		al_draw_filled_ellipse(x + COL_W / 2, y + LIN_W / 2, COL_W / 2 - 1.5*MARGIN, LIN_W / 2 - 1.5*MARGIN, c.cor);
	}

	else if(c.type == 4){
		al_draw_filled_rounded_rectangle(x + MARGIN, y + MARGIN, x+COL_W - MARGIN, y+LIN_W- MARGIN, COL_W/3, LIN_W/3, c.cor);	}

	else if (M[lin][col].type == 5){
	  al_draw_filled_triangle(x + 2*MARGIN, y + 2*MARGIN, x + COL_W - 2*MARGIN, y + 2*MARGIN, x + COL_W / 2, y + LIN_W - 2*MARGIN, c.cor);
	}

}

int newRecord(int score, int *record) {
	FILE *arq = fopen("record.txt", "r");
	*record = -1;
	if (arq != NULL) {
		fscanf(arq, "%d", record);
		fclose(arq);
	}
	if (score > *record) {
		arq = fopen("record.txt", "w");
		fprintf(arq, "%d", score);
		fclose(arq);
		return 1;
	}
	return 0;
}

void endGame(ALLEGRO_TIMER **timer, int* playing)
{
	int flag = 0;
	pause(*timer, 1);
	int record;
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(scorepic, 0, 0, 0);
	sprintf(my_score, "PONTUAÇÃO FINAL: %d", score);
	al_draw_text(size_f, al_map_rgb(0, 0, 0), SCREEN_W / 3.5, SCREEN_H / 2 - 200, 0, my_score);
	if (newRecord(score, &record)) {
		al_draw_text(size_f, al_map_rgb(0, 0, 0), SCREEN_W / 3.5, SCREEN_H / 2 - 150, 0, "NEW RECORD!");
	} else {
		sprintf(my_score, "RECORD: %d", record);
		al_draw_text(size_f, al_map_rgb(0, 0, 0), SCREEN_W / 3.5, SCREEN_H / 2 - 150, 0, my_score);
	}
	al_draw_text(size_f, al_map_rgb(255, 0, 0), SCREEN_W / 3.5, SCREEN_H / 2 - 100, 0, "Aperte ESC para sair");
	al_flip_display();
	pause(*timer, 5);
}
///////////--// Funcao pra ser chamada para desenhar algo //--///////////
void draw_scenario(ALLEGRO_DISPLAY *display) {

	// limpa a tela de Preto
	ALLEGRO_COLOR BKG_COLOR = al_map_rgb(0,0,0);
	al_set_target_bitmap(al_get_backbuffer(display));
	al_clear_to_color(BKG_COLOR);

	al_draw_bitmap(background, 0, 0, 0);

	//Desenha o placar
	sprintf(my_score, "PONTUAÇÃO: %d", score);
	al_draw_text(size_f, al_map_rgb(255, 255, 255), 10, LIN_W*N_LINHAS + (INFO_H / 2.5), 0, my_score);
	sprintf(my_moves, "MOVIMENTOS: %d", moves);
	al_draw_text(size_f, al_map_rgb(255, 255, 255), SCREEN_W - 180,  LIN_W*N_LINHAS + (INFO_H / 2.5), 0, my_moves);

	int i,j;
	for(i=0; i<N_LINHAS; i++){
		for(j=0; j<N_COLS; j++){
			desenhaCandy(M[i][j], i, j);
		}
	}

}

///////////--// Funcao que pega qual celula foi clikada //--///////////
void getCell(int x, int y, int *lin, int *col){
	*lin = y/LIN_W;
	*col = x/COL_W;
	printf("%d %d\n", y/LIN_W,x/COL_W);
	}

///////////--// Funcao que troca os doces //--///////////
void swap(int lin_src,int col_src,int lin_dst,int col_dst,int *score, ALLEGRO_SAMPLE **wrongSound){
	Candy aux;
	int validate = 0;
	//verifica se o movimento foi feito na vertical e de dist 1
	if((lin_src-lin_dst==1||lin_src-lin_dst==-1)&&(col_src-col_dst==0)){
		validate = validate + 1;
	}
	//verifica se o movimento foi feito na horizontal e de dist 1
	if((col_src-col_dst==1||col_src-col_dst==-1)&&(lin_src-lin_dst==0)){
		validate = validate + 1;
	}
	//verifica se o movimento nao foi feito na diagonal
	if (validate==1) {
	//Troca os doces
		aux = M[lin_src][col_src];
		M[lin_src][col_src] = M[lin_dst][col_dst];
		M[lin_dst][col_dst] = aux;
		//Verifica se a troca resultou em alguma combinacao
	//	if(verifyCombination()==0){
			//Caso nao tenha resultado, volta ao estado original
	//		aux = M[lin_src][col_src];
	//		M[lin_src][col_src] = M[lin_dst][col_dst];
//			M[lin_dst][col_dst] = aux;
//			//se o user movimenta errado perde ponto
	//		*score = *score - 10;
	//		al_play_sample(*wrongSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
//		}
	}
	else{
		//se o user movimenta errado perde ponto
		*score = *score - 10;
		al_play_sample(*wrongSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}

int main(int argc, char **argv){

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_SAMPLE *musicSound = NULL;
	ALLEGRO_SAMPLE *scoreMusic = NULL;
	ALLEGRO_SAMPLE *wrongSound = NULL;
	ALLEGRO_SAMPLE *moveSound = NULL;

	//----------------------- rotinas de inicializacao ---------------------------------------
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	if(!al_install_mouse())
		fprintf(stderr, "failed to initialize mouse!\n");


	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	if (!al_init_image_addon()) {
		fprintf(stderr, "failed to initialize images!\n");
				return -1;
	}
	background = al_load_bitmap(BACKGROUND_FILE);
	scorepic = al_load_bitmap(SCOREPIC_FILE);

		if (!background) {
		fprintf(stderr, "failed to load background bitmap!\n");
		return -1;
		}

		if (!scorepic) {
		fprintf(stderr, "failed to load scorepic bitmap!\n");
		return -1;
		}

		if (!al_install_audio()) {
			fprintf(stderr, "failed to initialize audio!\n");
	        return -1;
	    }
		if (!al_init_acodec_addon()) {
			fprintf(stderr, "failed to initialize audio codecs!\n");
	        return -1;
	    }

		musicSound = al_load_sample("music.wav");
		if (!musicSound) {
			fprintf(stderr, "audio clip move not loaded!\n");
			return -1;
		}

		scoreMusic = al_load_sample("scoremusic.wav");
		if (!scoreMusic) {
			fprintf(stderr, "audio clip move not loaded!\n");
			return -1;
		}

		wrongSound = al_load_sample("wrong.wav");
		if (!wrongSound) {
			fprintf(stderr, "audio clip move not loaded!\n");
			return -1;
		}

		moveSound = al_load_sample("move.wav");
		if (!moveSound) {
			fprintf(stderr, "audio clip move not loaded!\n");
			return -1;
		}

		if (!al_reserve_samples(3)) {
			fprintf(stderr, "failed to reserve samples!\n");
			return -1;
		}

//Inicializa FONTE
	al_init_font_addon();
	al_init_ttf_addon();
	size_f = al_load_font("arial.ttf", 20, 1);
	al_install_keyboard();
   //registra na fila de eventos que eu quero identificar quando a tela foi alterada
	al_register_event_source(event_queue, al_get_display_event_source(display));
   //registra na fila de eventos que eu quero identificar quando o tempo alterou de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//registra o teclado na fila de eventos:
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	//registra mouse na fila de eventos:
	al_register_event_source(event_queue, al_get_mouse_event_source());
   //inicia o temporizador
	al_start_timer(timer);

	//Faz com q S rand seja sempre aleatorio
	//srand(time(NULL));

	//----------------------------------------------------------------------------//
	//----------------------- rotinas de inicializacao ---------------------------------------
	//----------------------------------------------------------------------------//

	//Inicializa a matriz
	initCandies();
	//Faz com que a matriz inicial comece sem Combinacoes ja feitas
	while (verifyCombination()!=0) {
		initCandies();
	}

	int playing = 1;
	//enquanto playing for verdadeiro, faca:
	ALLEGRO_EVENT ev;

	int lin_src, col_src, lin_dst, col_dst;
	int x_src, x_dst, y_src, y_dst;

	al_play_sample(musicSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	while(playing) {
	  //espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

		//Se registrar alguma key, verifica se foi esc para sair

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				playing = 0;
			}
		//Se apertar um botão do mouse
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			printf("\nclicou em (%d, %d)", ev.mouse.x, ev.mouse.y);
			getCell(ev.mouse.x, ev.mouse.y, &lin_src, &col_src);
		}
		//Se soltar um botão do mouse
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			printf("\nsoltou em (%d, %d)", ev.mouse.x, ev.mouse.y);
			getCell(ev.mouse.x, ev.mouse.y, &lin_dst, &col_dst);
			if (lin_src!=lin_dst || col_src!=col_dst) {
				swap(lin_src, col_src, lin_dst, col_dst, &score, &wrongSound);
				moves = moves-1;
				if(M[8][0].type==4){
					score=score+1000;
				}
					while (verifyCombination()!=0) {
						destroyCandy(&score);
						al_play_sample(moveSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
						//Fazer a animação do destroy
						draw_scenario(display);
						al_flip_display();
						pause(timer, 0.8);
						dropCandy();
						replaceCandy();
						draw_scenario(display);
						al_flip_display();
						pause(timer, 0.2);
				}
			}
		}
	    //se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		else if(ev.type == ALLEGRO_EVENT_TIMER) {
		    draw_scenario(display);
				al_flip_display();
		}
	    //se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}

		if (moves == 0) {
				al_destroy_sample(musicSound);
		  	al_play_sample(scoreMusic, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				endGame(&timer, &playing);

				while (playing==1) {
				al_wait_for_event(event_queue, &ev);
				if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
					if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
						playing = 0;
					}
			}
		}
	}
	}
	//----------------------- rotinas de finalização ---------------------------------------
	al_rest(1);

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}
