/*
Resumo do que eu fiz pro bagulho funcionar:

1- Clicando lá em cima em Prject > Build Options > Search directories: Linkei o caminho para o include
(entrei na pasta include, mas nao cliquei no allegro5)

2- Ainda em Build Options, em cima a esquerda eu cliquei em Debug,
depois em Linker settings, e adicionei= ..\allegro\lib\liballegro_monolith-debug.dll.a

3- Depois, ainda em Build Options, cliquei em Reliase > Linker settings, e adcionei= ..\allegro\lib\liballegro_monolith.dll.a

4- Depois disso, dai de Build Options, criei um novo arquivo indo em File > New > File... > C/C++source > Linguagem C > Dexei marcado a opcao
e escolhi a pasta do projeto, alem de deixar o nome do arquivo de main

5- Com o arquivo criado, eu fui novamente em Project > Add files... e adicionei o arquivo ao projeto

6- Depois,  eu rodei o programa com um #include <allegro5/allegro5.h> no arquivo e ai da um erro. Depois de dar o erro,
vou ate a pasta do projeto > Bin > Debug apago tudo o que estiver la, provavelmente so vai ter o .exe,
e em seguida copio para la os arquivos=    allegro_monolith-5.2.dll    e    allegro_monolith-debug-5.2.dll
(sao arquivos que estao no Bin do Allegro)

7- E e isso, depois disso eu rodei esse codigo e foi.

*/

#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#define DISP_W 900
#define DISP_H 500

#define SEEN 1
#define RELEASED 2



//--------------------------------Cria o tipo dos "objetos"------------------------------------->
struct Circle
{
    int posX;
    int posY;
    int raio;
    int dir;
};
struct Rectangle
{
    //ponta superior esuqerda
    int UPEposX;
    int UPEposY;
    //ponta inferior direita
    int DOWDposX;
    int DOWDposY;
};
//--------------------------------------------------------------------------------------------//


int main(void){
    ALLEGRO_EVENT event;
    bool done = false;
    bool logic = false;
    int pontosP1 = 0;
    int pontosP2 = 0;
    int play = 0;
    int toques = 0;
    int contador = 0;
    int barVel = 5;
    int vel = 2;
    int mouseClickPositionX = 0;
    int mouseClickPositionY = 0;

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    al_init();

    al_init_font_addon();
    al_init_primitives_addon();

    al_install_keyboard();
    al_install_mouse();

    ALLEGRO_DISPLAY *display = al_create_display(DISP_W, DISP_H);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_FONT *font = al_create_builtin_font();
    ALLEGRO_TIMER *timer = al_create_timer(1.0/60.0); // 60 FPS


    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

//--------------------------------------Cria os objetos------------------------------------------------------->

    struct Circle circle = {DISP_W/2, DISP_H/2, 5, 1}; //Bolinha

                                                       //UPEposX , UPEposY , DOWDposX , DOWDposY
    struct Rectangle barPlayer1 = {70, 200, 100, 290}; //Barra do jogador 1 (esquerda)

    struct Rectangle barPlayer2 = {DISP_W-100, 200, DISP_W-70, 290}; //Barra do jogador 2 (direita)

//-----------------------------------------------------------------------------------------------------------//


    al_start_timer(timer); //Inicia o timer
    while (!done) {
        al_wait_for_event(queue, &event); //Espera por qualquer evento

        switch (event.type){
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;

            case ALLEGRO_EVENT_TIMER:
                logic = true;
            break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = SEEN | RELEASED;
                break;

            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= RELEASED;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(event.mouse.button & 1){
                    mouseClickPositionX = event.mouse.x;
                    mouseClickPositionY = event.mouse.y;
                }
                break;
        }

        if(logic){

            for(int i = 0; i<ALLEGRO_KEY_MAX; i++){
                key[i] &=SEEN;
            }

//-----------------------------------Controles------------------------------------------>

//-----------------------------controles da barra do Jogador 1(esquerda)-------------------------->

            if(key[ALLEGRO_KEY_S]){
                if(barPlayer1.DOWDposY<=DISP_H){
                    barPlayer1.UPEposY = barPlayer1.UPEposY + 6;
                    barPlayer1.DOWDposY = barPlayer1.DOWDposY + 6;
                }else{
                    barPlayer1.UPEposY = barPlayer1.UPEposY - 1;
                    barPlayer1.DOWDposY = barPlayer1.DOWDposY - 1;
                }
            }

            if(key[ALLEGRO_KEY_W]){
                if(barPlayer1.UPEposY>=0){
                    barPlayer1.UPEposY = barPlayer1.UPEposY - 6;
                    barPlayer1.DOWDposY = barPlayer1.DOWDposY - 6;
                }else{
                    barPlayer1.UPEposY = barPlayer1.UPEposY + 1;
                    barPlayer1.DOWDposY = barPlayer1.DOWDposY + 1;
                }
            }
//-----------------------------controles da barra do Jogador 2(direita)---------------------------->

            if(key[ALLEGRO_KEY_DOWN]){
                if(barPlayer2.DOWDposY<=DISP_H){
                    barPlayer2.UPEposY = barPlayer2.UPEposY + barVel;
                    barPlayer2.DOWDposY = barPlayer2.DOWDposY + barVel;
                }else{
                    barPlayer2.UPEposY = barPlayer2.UPEposY - 1;
                    barPlayer2.DOWDposY = barPlayer2.DOWDposY - 1;
                }
            }

            if(key[ALLEGRO_KEY_UP]){
                if(barPlayer2.UPEposY>=0){
                    barPlayer2.UPEposY = barPlayer2.UPEposY - barVel;
                    barPlayer2.DOWDposY = barPlayer2.DOWDposY - barVel;
                }else{
                    barPlayer2.UPEposY = barPlayer2.UPEposY + 1;
                    barPlayer2.DOWDposY = barPlayer2.DOWDposY + 1;
                }
            }
//------------------------------------------outros---------------------------------------->

            if(key[ALLEGRO_KEY_M]){ //move o circulo branco para onde clicar com o mouse
                circle.posX = mouseClickPositionX;
                circle.posY = mouseClickPositionY;
            }

            if(key[ALLEGRO_KEY_T]){ //muda entre play/pause. A bolinha fica parada ou se movendo.
                switch(play){
                case 1:
                    play = 0;
                break;
                case 0:
                    play = 1;
                break;
                }
            }


//---------------------------------------------------------------------------------------//

//----------------------------------------codigo da bolinha------------------------------------------------>

            if(play == 1){

                    if(toques==5 && vel<20){// velocidade dinamica bolinha
                        vel++;
                        toques=0;
                    }

                    switch(contador){// velocidade dinamicas barras
                        case 0:
                            if(vel >= 5){
                                barVel = barVel +1;
                                contador++;
                            }
                            break;
                        case 1:
                            if(vel >= 8){
                                barVel = barVel +2;
                                contador++;
                            }
                            break;
                        case 2:
                            if(vel >= 10){
                                barVel = barVel +3;
                                contador++;
                            }
                            break;
                        case 3:
                            if(vel >= 15){
                                barVel = barVel +4;
                                contador++;
                            }
                            break;
                    }


                switch(circle.dir){//<-----------------Direcao da bolinha
                    case 1:
                        circle.posX = circle.posX + vel;
                        break;
                    case 2:
                        circle.posX = circle.posX - vel;
                        break;
                    case 3:
                        circle.posX = circle.posX + vel;
                        circle.posY = circle.posY - vel;
                        break;
                    case 4:
                        circle.posX = circle.posX + vel;
                        circle.posY = circle.posY + vel;
                        break;
                    case 5:
                        circle.posX = circle.posX - vel;
                        circle.posY = circle.posY - vel;
                        break;
                    case 6:
                        circle.posX = circle.posX - vel;
                        circle.posY = circle.posY + vel;
                        break;
                    case 7:
                        circle.posX = circle.posX + vel;
                        circle.posX = circle.posX + vel;
                        circle.posY = circle.posY - vel;
                        break;
                    case 8:
                        circle.posX = circle.posX + vel;
                        circle.posX = circle.posX + vel;
                        circle.posY = circle.posY + vel;
                        break;
                    case 9:
                        circle.posX = circle.posX - vel;
                        circle.posX = circle.posX - vel;
                        circle.posY = circle.posY - vel;
                        break;
                    case 10:
                        circle.posX = circle.posX - vel;
                        circle.posX = circle.posX - vel;
                        circle.posY = circle.posY + vel;
                        break;
                }
//----------------------------------------------colisao com as barras------------------------------------------------------------->

            //  barra>>>   |   <(parte 1)
            //             |   <(parte 2)
            //             |   <(parte 3/meio)
            //             |   <(parte 4)
            //             |   <(parte 5)

                if(circle.posY<=barPlayer2.DOWDposY && circle.posX>=barPlayer2.UPEposX && circle.posY>=barPlayer2.UPEposY){
                    circle.dir = 2;//meio da barra
                    if(circle.posY<=barPlayer2.UPEposY+30){//parte 2 da bara
                        circle.dir = 6;
                        if(circle.posY<=barPlayer2.UPEposY+20){//parte 1 da bara
                            circle.dir = 10;
                        }
                    }
                    if(circle.posY>=barPlayer2.DOWDposY-30){//parte 4 da bara
                        circle.dir = 5;
                        if(circle.posY>=barPlayer2.DOWDposY-20){//parte 5 da bara
                            circle.dir = 9;
                        }
                    }
                    toques++;
                }

                if(circle.posY<=barPlayer1.DOWDposY && circle.posX<=barPlayer1.DOWDposX && circle.posY>=barPlayer1.UPEposY){
                    circle.dir = 1;//meio da barra
                    if(circle.posY<=barPlayer1.UPEposY+30){//parte 2 da bara
                        circle.dir = 4;
                        if(circle.posY<=barPlayer1.UPEposY+20){//parte 1 da bara
                            circle.dir = 8;
                        }
                    }
                    if(circle.posY>=barPlayer1.DOWDposY-30){//parte 4 da bara
                        circle.dir = 3;
                        if(circle.posY>=barPlayer1.DOWDposY-20){//parte 5 da bara
                            circle.dir = 7;
                        }
                    }
                    toques++;
                }
//------------------------------------------------------------------------------------------------------------------------------//


//----------------------------------------------colisao com os limites---------------------------------------------->

                if(circle.posY<0){//Colisao com o limite de cima
                    switch(circle.dir){
                        case 3:
                            circle.dir = 4;
                            break;
                        case 5:
                            circle.dir = 6;
                            break;
                        case 7:
                            circle.dir = 8;
                            break;
                        case 9:
                            circle.dir = 10;
                            break;
                    }
                }

                if(circle.posY>DISP_H){//Colisao com o limite de baixo
                    switch(circle.dir){
                        case 4:
                            circle.dir = 3;
                            break;
                        case 6:
                            circle.dir = 5;
                            break;
                        case 8:
                            circle.dir = 7;
                            break;
                        case 10:
                            circle.dir = 9;
                            break;
                    }
                }


                if(circle.posX>DISP_W){//Colisao com o limite direito
                    pontosP1++;
                    toques++;
                    circle.posX = DISP_W/2;
                    circle.posY = DISP_H/2;
                    circle.dir = 2;
                }
                if(circle.posX<0){//Colisao com o limite esuqerdo
                    pontosP2++;
                    toques++;
                    circle.posX = DISP_W/2;
                    circle.posY = DISP_H/2;
                    circle.dir = 1;
                }

//-----------------------------------------------------------------------------------------------------------------//

            }else{
                if(key[ALLEGRO_KEY_R]){//reiniciar
                    circle.posX = DISP_W/2;
                    circle.posY = DISP_H/2;
                    pontosP1 = 0;
                    pontosP2 = 0;
                    circle.dir = 1;
                    toques = 0;
                }
            }

//---------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------Desenha a tela e tudo nela----------------------------------------------------------------------------------->
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_line(DISP_W/2, DISP_H/6, DISP_W/2, DISP_H-DISP_H/6, al_map_rgb(255, 255, 255), 2);

            al_draw_filled_circle(circle.posX, circle.posY, circle.raio, al_map_rgb(255, 255, 255));

            al_draw_rectangle(barPlayer1.UPEposX, barPlayer1.UPEposY, barPlayer1.DOWDposX, barPlayer1.DOWDposY, al_map_rgb(200, 200, 255), 3);

            al_draw_rectangle(barPlayer2.UPEposX, barPlayer2.UPEposY, barPlayer2.DOWDposX, barPlayer2.DOWDposY, al_map_rgb(200, 255, 200), 3);

            al_draw_textf(font, al_map_rgb(255, 255, 255), DISP_W/2, 30, 1, "P1: %d   PLACAR   %d :P2", pontosP1, pontosP2);
            al_draw_textf(font, al_map_rgb(255, 255, 255), DISP_W/2, 480, 1, "T = play/pause");
            if(play == 0){
                al_draw_textf(font, al_map_rgb(255, 255, 255), DISP_W/2, 465, 1, "precione R para reiniciar");
                al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 45, 0, "Bolinha(velocidade):  %d", vel);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 55, 0, "Barras(velocidade):  %d", barVel);
            }



            al_flip_display();

//--------------------------------------------------------------------------------------------------------------------------------------------------------------//

            logic = false;
        }


    }
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_font(font);
    al_destroy_timer(timer);

    return 0;
}
