#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

int main(){
    int n[5] , sum[2];
    printf("Prediction_Sum_Game\n-->By Sir Karim Kazi\n");
    printf("Choose any 3-digit number:\n");
    printf("Your Turns are 1st, 2nd, 4th\nComputer's Turns are 3rd & 5th: \n");
    printf("Press any key to start: \n"); // system("PAUSE") ;
    getch();

    printf("Enter your 1st number: ");
    scanf("%d", &n[0] );
    sum[0] = 1998 + n[0] ;
    printf("Processing....(By applying Algorithms.)\n");
    Sleep(1000);
    printf("Predicted-Sum = %d \n", sum[0] );
    
    system("pause") ;
    printf("Enter your 2nd number: \n");
    scanf("%d", &n[1] );
    n[2] = 999 - n[1] ;
    printf("Now 3rd turn is of computer's.\n");
    Sleep(1000);
    printf("After the complex_algorithm calculation:\nComputer chose %d\n", n[2] );

    printf("Now make your LAST wild guess to beat computer_algorithm: ");
    scanf("%d", &n[3] );
    n[4] = 999 - n[3] ;
    printf("Processing.....\n");
    printf("\033[2J\033[1;1H");
    Sleep(1250) ;
    printf("Computer chose %d\n", n[4] );
    printf("Predicted-Sum was %d \n", sum[0] );

    sum [1] = n[0] +  n[1] +  n[2] +  n[3] +  n[4] ;
    if(sum[0] == sum[1]){
        printf("Computer-won as the sum is %d\nTold you can't beat him\n", sum[1] ); }
    else{
        printf("You cheecky figured the way-out\nSum-Predicted = %d\t\tSum-Found = %d",sum[0] , sum[1]);
    }
    

       
    return 0;
}