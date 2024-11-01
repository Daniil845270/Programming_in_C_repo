#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

void shufflet_seed(void);
void shuffler(int playlist[], int songs_num);
void printer(int playlist[], int songs_num);
void playlist_init(int playlist[], int songs_num);

int main(void)
{
    shufflet_seed();

    int songs_num;
    printf("How many songs requred? ");
    scanf("%i", &songs_num);

    int playlist[songs_num];

    playlist_init(playlist, songs_num);
    
    printer(playlist, songs_num);
    
    shuffler(playlist, songs_num);
    
    printer(playlist, songs_num);

    return 0;
}

void playlist_init(int playlist[], int songs_num)
{
    
    for (int i = 0; i < songs_num; i++) 
    {
        playlist[i] = i + 1;
    }
}

void shufflet_seed(void)
{
	srand(time(NULL));
}

void shuffler(int playlist[], int songs_num)
{
    int randomiser = 3;
    for (int i = 0; i < randomiser; i++)
    {
        for (int j = 0; j < songs_num; j++)
        {
            int num1, num2, buffer;
            num1 = rand() % songs_num; num2 = rand() % songs_num;
            buffer = playlist[num1]; playlist[num1] = playlist[num2]; playlist[num2] = buffer;
        }
    }
}

void printer(int playlist[], int songs_num)
{
    for (int i = 0; i < songs_num; i++) //here I just create a playlist
    {
        printf("%i ", playlist[i]);
    }
    printf("\n");
}
