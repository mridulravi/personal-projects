/* rand example: guess the number */
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main ()
{
  int iSecret;// iGuess;

  /* initialize random seed: */
  srand ( time(NULL) );

  /* generate secret number: */
  iSecret = rand() % 10+1;
  std::cout<<iSecret<<std::endl;
/*
  do {
    printf ("Guess the number (1 to 10): ");
    scanf ("%d",&iGuess);
    if (iSecret<iGuess) puts ("The secret number is lower");
    else if (iSecret>iGuess) puts ("The secret number is higher");
  } while (iSecret!=iGuess);

  puts ("Congratulations!");*/
  return 0;
}
