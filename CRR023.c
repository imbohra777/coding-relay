#include <stdio.h>
#include <conio.h>  // For non-blocking input
#include <windows.h>  // For Windows OS - for coloring text

typedef struct {
    char songName[100];
    char singerName[50];
    char albumName[100];
    int songSizeMB;
    int yearReleased;
    char genre[50];
} Song;

typedef struct {
    Song currentlyPlaying;
    int volumeLevel;
} MusicPlayerDashboard;

void clearScreen() {
    system("cls");
}

void displayControls() {
    printf(" [P] Play / Pause [R] Rewind    [F] Fast Forward   V] Volume Up    [M] Volume Down\n");
}

void initMusicPlayerDashboard(MusicPlayerDashboard *dashboard) {
    dashboard->volumeLevel = 50;
    // Initialize other elements
}

void displayMusicPlayerDashboard(MusicPlayerDashboard dashboard) {
    clearScreen();
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃ Now Playing: %-30s┃\n", dashboard.currentlyPlaying.songName);
    printf("┃ Singer: %-37s┃\n", dashboard.currentlyPlaying.singerName);
    printf("┃ Album: %-38s┃\n", dashboard.currentlyPlaying.albumName);
    printf("┃ Size: %-4dMB     Year: %-6d Genre: %-s┃\n", dashboard.currentlyPlaying.songSizeMB, dashboard.currentlyPlaying.yearReleased, dashboard.currentlyPlaying.genre);
    printf("┃ Volume: ");
    for (int i = 0; i < dashboard.volumeLevel / 5; i++) {
        printf("\033[1;32m■");  // Green color for filled volume
    }
    for (int i = dashboard.volumeLevel / 5; i < 20; i++) {
        printf("\033[m□");  // Reset color for empty volume
    }
    printf("\033[m %d%%  ┃\n", dashboard.volumeLevel);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    displayControls();
}

int main() {
    MusicPlayerDashboard myDashboard;
    initMusicPlayerDashboard(&myDashboard);
    
    Song playlist[10];
    // User input for 10 songs
    for (int i = 0; i < 10; i++) {
        printf("Enter details for Song %d:\n", i + 1);
        printf("Song Name: ");
        fgets(playlist[i].songName, sizeof(playlist[i].songName), stdin);
        // Clear the input buffer
        if (strchr(playlist[i].songName, '\n') == NULL) {
            while (fgetc(stdin) != '\n');
        }
        printf("Singer Name: ");
        fgets(playlist[i].singerName, sizeof(playlist[i].singerName), stdin);
        if (strchr(playlist[i].singerName, '\n') == NULL) {
            while (fgetc(stdin) != '\n');
        }
        printf("Album Name: ");
        fgets(playlist[i].albumName, sizeof(playlist[i].albumName), stdin);
        if (strchr(playlist[i].albumName, '\n') == NULL) {
            while (fgetc(stdin) != '\n');
        }
        printf("Song Size (in MB): ");
        scanf("%d", &playlist[i].songSizeMB);
        printf("Year Released: ");
        scanf("%d", &playlist[i].yearReleased);
        printf("Genre: ");
        while (getchar() != '\n');  // Clear input buffer
        fgets(playlist[i].genre, sizeof(playlist[i].genre), stdin);
    }

    char input;
    int keyCount = 0;
    int currentSongIndex = 0;
    do {
        myDashboard.currentlyPlaying = playlist[currentSongIndex];
        displayMusicPlayerDashboard(myDashboard);
        if (kbhit()) {
            input = getch();
            switch (input) {
                case 'P':
                case 'p':
                    // Add play / pause functionality
                    printf("Toggling Play / Pause\n");
                    break;
                case 'R':
                case 'r':
                    // Add rewind functionality
                    printf("Rewinding\n");
                    break;
                case 'F':
                case 'f':
                    // Add fast forward functionality
                    printf("Fast Forwarding\n");
                    break;
                case 'V':
                case 'v':
                    // Add volume up functionality
  
                    printf("Volume Up\n");
                    // Add logic to increase volume
                    if (myDashboard.volumeLevel < 100) {
                        myDashboard.volumeLevel += 10;  // Increase volume by 10%
                    }
                    break;
                case 'M':
                case 'm':
                    // Add volume down functionality
                    printf("Volume Down\n");
                    // Add logic to decrease volume
                    if (myDashboard.volumeLevel > 0) {
                        myDashboard.volumeLevel -= 10;  // Decrease volume by 10%
                    }
                    break;
                case 'N':
                case 'n':
                    // Play the next song
                    currentSongIndex = (currentSongIndex + 1) % 10;  // Loop through the playlist
                    break;
                case 'Q':
                case 'q':
                    // Quit the music player
                    printf("Quitting the music player");
                    return 0;
                default:
                    printf("Invalid input\n");
                    break;
            }
        }
        Sleep(1000);  // Pause for 1 second before refreshing the display
    } while (input != 'Q' && input != 'q');  // Allow the user to quit by pressing 'Q' or 'q'

    return 0;
}
