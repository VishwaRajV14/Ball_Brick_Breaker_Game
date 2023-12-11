#include<SDL2/SDL.h>
#include<iostream>

bool quit_game=false;
SDL_Event event;
//ball parameters
int ball_x=300;
int ball_y=30;
int ball_velx=1;
int ball_vely=1;

//wall or screen or window parameters
int bk_x=640;
int bk_y=480;
int bk_xmin=0;
int bk_ymin=0;

//bat parameters
int bat_x=bk_x/2;
int bat_y=bk_y-30;

void Event_handler()
{
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT)
     quit_game=true;
    else if (event.type == SDL_KEYDOWN)
    {
        if(event.key.keysym.sym == SDLK_LEFT && bat_x>0)
         bat_x=bat_x-1;
        
        if(event.key.keysym.sym == SDLK_RIGHT && bat_x < bk_x-60)
         bat_x=bat_x+1;       
    }

}

void moveBall()
{
    ball_x=ball_x+ball_velx;
    ball_y=ball_y+ball_vely;
}

void ball_collisions()
{
    if(ball_x < bk_xmin || ball_x > bk_x-30)
     ball_velx=-ball_velx;
    if(ball_y < bk_ymin || ball_y > bk_y-30)
     ball_vely=-ball_vely; 
    
    int ballscaling=30;
    if((ball_x+ballscaling>=bat_x && ball_x+ballscaling<=bat_x+60) && (ball_y+ballscaling>=bat_y && ball_y+ballscaling<=bat_y+30))
     ball_vely=-ball_vely;
}

int main(int argc, char** argv)
{
    //window initialisation
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window=SDL_CreateWindow("BRICK_GAME",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,480,0);
    SDL_Renderer *renderer=SDL_CreateRenderer(window,-1,0);
    
    //background image initialisation
    SDL_Rect bkrect={0,0,640,480};
    SDL_Surface *bk=SDL_LoadBMP("img/bk.bmp");
    SDL_Texture *bktexture= SDL_CreateTextureFromSurface(renderer,bk);
    
    //ball image initialisation
    SDL_Surface *ball=SDL_LoadBMP("img/ball.bmp");
    SDL_Texture *balltexture= SDL_CreateTextureFromSurface(renderer,ball);
   
    //bat image initialisation
    SDL_Surface *bat=SDL_LoadBMP("img/bat.bmp");
    SDL_Texture *battexture= SDL_CreateTextureFromSurface(renderer,bat);
    
    //close the game using X button
    //till that it keeps on running
    while(!quit_game)
    {
        Event_handler();//this also takes care of all the movement of bat
        moveBall();// takes care of the movement of the ball  
        ball_collisions();//ball&wall && ball&bat collision

        //the rendering of the images
        SDL_Rect ballrect={ball_x,ball_y,20,30};
        SDL_Rect batrect={bat_x,bat_y,60,30};
        SDL_RenderCopy(renderer,bktexture,NULL,&bkrect);
        SDL_RenderCopy(renderer,balltexture,NULL,&ballrect);
        SDL_RenderCopy(renderer,battexture,NULL,&batrect);
        SDL_RenderPresent(renderer);

        
        SDL_Delay(1);

    }
 
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}