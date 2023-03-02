/*
    Nashib Limbu

    The code works but it isn't in order of probability but is instead random, I tested 5 different ciphers alongside my own and here are the keys to find them on the list:

    RTJJHZTHPMCTUMFNHMFXUNXQT A:3 B:7       --this is the the cipher given to crack

    IPFIVEAPAVENMRJSGVYJIVPINP  -- A:11 B:8
    VQKQKQZTVYGMNGZUTFYQN   -- A:3 B:0
    FAPSIBFZAANKFDNRXKWOCBFLFMXDK    -- A:17 B:23
    CHSPZKXKFSQEQEQZVUQCEUXCUGDKXKFSBEXMKXLTHUKWEXM     -- A:9 B:10
    IHQOZVJFBVSBICDPSLIUBZXHXFALOTDXCFMFSBRUFSF     -- A:5 B:11
*/
#include<stdio.h>
#include<string.h>
#include<ctype.h>

//function prototypes
void bruteforce();
void decrypt(char ciphertext[], int alphakey, int inverse);
int inversemod (int a);
int exteuclideanalgorithm (int a, int b, int *x, int * y);

//Main function where user inputs ciphertext, converts to uppercase and calls bruteforce function
int main(void)
{
    char ciphertext[500];
    int i = 0;
    int j = 0;

    //Enter the cipher text.
    printf("Enter the ciphertext:\n");
    //scanf("%s",ciphertxt);
    fgets(ciphertext, 500, stdin);
    ciphertext[strlen(ciphertext)-1] = '\0';

    //Converts each index of the array into uppercase using 'toupper'
    for (i=0, j=0; ciphertext[i]!='\0'; i++){
        if (ciphertext[i] != ' '){
            ciphertext[j] = (toupper(ciphertext[j]));
            j++;
        }else{
            ciphertext[j] = ' ';
            j++;
        }
    }
    printf("Entered string is : %s \n",ciphertext);

    //function to begin the bruteforcing attempt
  bruteforce(ciphertext);


 return 0;
}

//takes alpha, beta and pointers to addresses and uses recursion to work out the GCD
int exteuclideanalgorithm (int a, int b, int *x, int * y){
    int mod = 26;
    int x1;
    int y1;

    //Ends the recursive GCD and starts the the operations.
    if ( a==0){
        *x = 0;
        *y = 1;
        return b;
    }
    //recursive function with pointers to store values from EEA
    int gcd = exteuclideanalgorithm (b%a, a, &x1, &y1);
    
    *x = y1 - (b/a) * x1;
    *y = x1;
    
    return gcd;
}

//function to calculate modular inverse, only need 1 input because we are always working in mod 26 from ax+by=1
int inversemod (int a){
    int mod = 26;
    int x, y, calculations;
    //We find the modular inverse by using the extended euclidean algorithm as a function and if the inverse = 1 then we return the modular inverse using (x % mod + mod) % mod
    int inverse = exteuclideanalgorithm(a, mod, &x, &y);
    if (inverse == 1){
        calculations = (x % mod + mod) % mod;
        
    }
    else{
        calculations = 0;
    }
    return calculations;
}

//function that bruteforces the cipher by trying all combination of Alpha with Beta keys 
void bruteforce(char ciphertext[]){
    int inv;
    int a = 0;

    //Runs through all possible combinations of Alpha key with Beta key
    while(a<26){
        //checks to see if the alpha has an inverse, we do this by checking it is relative prime gcd(a,mod) = 1
        inv=inversemod(a);
            if(inv != 0){
                decrypt(ciphertext, a, inv);
            }
        a++;
    } 

}

//function that does the decryption and iterates through the Beta key using the Alpha provided
void decrypt(char ciphertext[], int alphakey, int inverse){
    char decrypted [500];
    int i = 0;
    int b = 0;
    int j = 0;
    int strlength = strlen(ciphertext);
    int decryption[500];
    int conversion[500];


    // converts strings to ascii value
    for(j=0;j<strlength;j++){
        conversion[j] = ciphertext[j] + (int)'A';
    }
    

    //Iterates through Beta key using the Alpha provided
     for(b=0;b<26;b++){                   
                    printf("\n\nDecryption for keys A:%d B:%d\n", alphakey, b); 
                    //Goes through the index of the ciphertext
                    for(i=0;i<strlength;i++){
                        //checks for white space
                        if(decryption[i]!= ' '){
                            //affine cipher decryption using combination of Beta and Alpha with mod 26 
                            decrypted[i]=(inverse*(conversion[i]-b))%26;
                            printf("%c",(decrypted[i]+ (int)'A'));         
                        }else{
                            //prints white space if the cipher has it
                            printf(" ");      
                        }
                    }
                }   

}


