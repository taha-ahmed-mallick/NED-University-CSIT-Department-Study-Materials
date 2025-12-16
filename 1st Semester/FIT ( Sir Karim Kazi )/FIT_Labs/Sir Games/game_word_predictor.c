#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void printChars(void){
    int count = 0 ;
    for(int i=0 ; i < 7 ; i++) {
      for(int j=0 ; j < 4 ; j++) {
        if(i == 6 && ( j == 2 || j == 3) )
            continue ;

        printf("%c ", 'A' + count);
        count++ ;
      }
      printf("\n");
    }
}

// Function to print selected Column chars to Row
void printUpdatedChars(int count){
        int j = 0 ;
        for(char ch = 'A' + count - 1 ; ch <= 'Z'; ch+= 4){
            printf("%c ", ch);
            j++ ;
        }
        printf("\n") ;
    // int i = 0 ; // If wanna do in main so reinitialize for each Loop
    // while(i < n){
    //     int j = 0 ;
    //     for(char ch = 'A' + count - 1 ; ch <= 'Z'; ch+= 4){
    //         printf("%c ", ch);
    //         j++ ;
    //     }
    //     printf("\n") ;
    //     j = 0 ;
    //     i++ ;
    // }
}

int main() {

    printf("\t\tWelcome to WORD-GUESSING GAME\nPress a key to conitnue: \n");
    getch() ;
    int n; 
    printf("Enter the length of your word: ") ;
    scanf("%d", &n)  ;

    if(n < 0 || (char) n >= 'A' && (char) n <= 'z') { // Use char OR it will consider ASCII values and use for all ASCII's b/w A(65) to z(122)
        printf("Please Enter Valid Length.\n");
        return 1 ;
    }

    int count[2*n] , i = 0, a = 0;
    char guess[30] , alphabets; 

    while( i < n ) { 
            printChars() ;
            printf("Enter Column number for your %d character: ", 1 + i ) ;
            scanf("%d", &count[i] ) ;

            // Validate column number input (within the range of columns)
            if( count[i] > 4 || count[i] <= 0){
                printf("\nInvalid Column Number.\n\tTry Again!\n");
                i-- ; // Decrement for same character column input
                continue;
            }

            i++ ;
    }
    system("cls") ; // Included in stdlib system("clear") FOR UNIX, LINUX

    do{
        i = 0 ;  // To print selected chars everytime
        while(i < n){
            printUpdatedChars( count[i] ) ;
            i++ ;
        }

        printf("Now select from this Column number: ", i + 1) ;
        scanf("%d", &count[a + n] ) ;
        if(count[a + n] > 7 || count[a + n] < 0){
            printf("Invalid Column Number.\n\tTry Again!\n");
            a-- ; 
            continue;
        }


    // Assigning alphabets based on different column choices as Formula can't be made for each & every case
    if(count[a] == 1){ 
        char alpha[7][2] = { {'A'}, {'E'} , {'I'} ,{'M'}, {'Q'} , {'U'} , {'Y'} } ; // 2 spaces reserve cause 1 is for single character and other 1 for null-terminator in all
        alphabets = alpha[ count[a + n] - 1] [0] ;
        guess[a] = alphabets ;
    }
    else if(count[a] == 2){
        char alpha[7][2] = { {'B'}, {'F'}, {'J'}, {'N'}, {'R'}, {'V'}, {'Z'} };
        alphabets = alpha[ count[a + n] - 1] [0] ;
        guess[a] = alphabets ;
    }
    else if(count[a] == 3){
        char alpha[6][2] = { {'C'}, {'G'} , {'K'} ,{'O'}, {'S'} , {'W'} } ;
        alphabets = alpha[ count[a + n] - 1] [0] ;
        guess[a] = alphabets ;
    }
    else if(count[a] == 4){
        char alpha[6][2] = { {'D'}, {'H'} , {'L'} ,{'P'}, {'T'} , {'X'} } ;
        alphabets = alpha[ count[a + n] - 1] [0] ;
        guess[a] = alphabets ;
    }
        a++ ;
    } while(a < n) ; // Loop until all characters are selected Finally

    guess[n] = '\0' ; // Null-terminate the guess string
    printf("Word = %s", guess) ;

    char opinion ;
    printf("\nIs the guessed word correct Yes(Y) OR not(N).\nIf Not, provide the word\n");
    scanf(" %c", &opinion) ;

    if (opinion == 'y' || opinion == 'Y') {
        printf("Told Ya! Computers are smart nowadays.\n");

        time_t now;
        time(&now);
        struct tm *local = localtime(&now);

        FILE *ptr;
        ptr = fopen("records.txt", "a");

        if (ptr != NULL) {
            fprintf(ptr, "Guessed Word: %s\tTime: %s", guess, asctime(local) );
            fclose(ptr);
        } 
        else {
            printf("File could not be opened.\n");
        }
    } 
    else {
        char orig[50] ;
        printf("Please enter the word: ");
        scanf("%s", orig);

        FILE *ptr;
        ptr = fopen("records.txt", "a");

        if (ptr != NULL) {
        time_t mytime;
        mytime = time(NULL);
            // Write missed word from user input to the file
            fprintf(ptr, "Computer-guessed = %s Original Word: %s\tTime: %s\n", guess, orig, ctime(&mytime) );
            fclose(ptr);
        } 
        else {
            printf("File could not be opened.\n");
        }
    }
  return 0;
}
    // Can Also Do as This
    // char alpha[] = {'B', 'F', 'J', 'N', 'R', 'V', 'Z', '\0'};
    // printf("Alphabets: %c\n", alpha[0] );    
    

        // char alpha[7][2] = { {'B'}, {'F'}, {'J'}, {'N'}, {'R'}, {'V'}, {'Z'} };
    // // Access and print individual alphabets
    // printf("First alphabet: %c\n", alpha[0][0]); // Accessing 'B'
    // printf("Third alphabet: %c\n", alpha[2][0]); // Accessing 'J'
    // printf("Last alphabet: %c\n", alpha[6][0]); // Accessing 'Z'

// char str[27] = ""; // Initialize an empty string to store the concatenated characters

//     for (char ch = 'A'; ch <= 'Z'; ch++) {
//         char temp[2] = {ch, '\0'}; // Create a temporary string containing a single character
//         strcat(str, temp); // Concatenate the temporary string to the main string
//     }

//     // Display the concatenated string
//     printf("Concatenated string: %s\n", str);