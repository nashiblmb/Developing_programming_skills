/*
    Nashib Limbu
    Affine cipher project during university
*/


/*
The given code implements the Affine cipher, a type of monoalphabetic substitution cipher that uses mathematical equations to encrypt and decrypt messages. 
The Affine cipher is a combination of two mathematical equations, namely y = a*x + b mod 26 and x = (y - b) * a^-1 mod 26. 

The first equation is used for encryption, where y represents the encrypted letter, x represents the plaintext letter, a and b are the encryption keys, 
and mod 26 is used to ensure the resulting value is within the range of 0 to 25.
The second equation is used for decryption, where a^-1 is the modular inverse of a, and y represents the ciphertext letter.

The program takes user input for plaintext/ciphertext and allows the user to choose between encryption and decryption. 
The user can also choose the encryption keys for the affine cipher. 
The program uses functions to convert plaintext to uppercase letters, encrypt plaintext using the affine cipher, 
decrypt ciphertext using the affine cipher, and calculate the modular inverse of a using the extended Euclidean algorithm. 

The program also uses a loop to allow the user to repeatedly encrypt/decrypt or exit the program.

*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//function prototypes
void *stringstoupper(char string[]);
char encryption (char plaintext, int a, int b, int strlength);
void encrypt(char plaintext[]);

void decrypt(char ciphertext[]);
char decryption (char affinecipher, int a, int b, int inv, int strlength);
int inversemod (int a);
int exteuclideanalgorithm (int a, int b, int *x, int * y);

//Main function asks for user input for ciphertext/plaintext and runs loop option to encrypt/decrypt
int main(){
    char text[500];
    char option;
    int n = 0;

    //enter text/cipher that you need to encrypt//decrypt
    printf("Enter Text/Ciphert\n");
    fgets(text, 500, stdin);
    
    //Function call to change plaintext to uppercase letter
    stringstoupper(text);
    //we ran into problem where return key was being registered and encrypted/decrypted so we set last character as NULL character to remove the issue
    text[strlen(text)-1] = '\0';

    //The loop allows for option to either encrypt or decrypt using seperate functions
    while (n==0){
        printf("Type: E for encrypt, D for decrypt, N to exit: \n");
        scanf("%c", &option);
        //calls encrypt function
        if (option =='E' || option == 'e'){
            encrypt(text);
            n = 1;
        }
        //calls decrypt function
        else if (option == 'D' || option == 'd'){
            decrypt(text);
            n = 1;
        }
        //ends loop
        else if (option == 'N' || option == 'n' ){
            printf("Exiting program");
            n = 1;
        }
    }


    return 0;
}

//Function to change the user input string to uppercase
void  *stringstoupper(char string[]){
    int i = 0;
    int j = 0;
    //Using a for loop, goes through the indexes in the string array until NULL character is found, signifying end of array
    /*converts each index in the char array to uppercase letter, since the array is a pointer, it is changed in memory
    not just the function, hence no need to return anything. */
    for (i=0, j=0; string[i]!='\0'; i++){
        if (string[i] != ' '){
            string[j] = (toupper(string[j]));
            j++;
        }else{
            string[j] = ' ';
            j++;
        }
    }
   
}

//Affine encryption function
char encryption (char plaintext, int a, int b, int strlength){
    int affineencryption = 0;
    char decryptedletter;
    int conversion;

    //conversion of the character from ASCII no. into integer, maps uppercase alphabet to a number, done by typecasting 'A' to int which is 65
    conversion =  plaintext - (int)'A';
    
    //affine encryption = f(y) = a.x+b mod 26
    //y = cipher text, a = alpha key, b = beta key, x = plaintext alphabet mapped to number e.g A (ASCII 71) - 65 = 6, encryption = a*6+b
    affineencryption = (a*conversion+b)  % 26 ;
    decryptedletter = affineencryption + (int)'A';
    /*this returns the result back into the affinecipher variable but first it adds 65 to the value of affineencryption
    and typecasts it back into char to get the ascii,  */
    //e.g. 'R' = (ASCII VALUE):82-65 = 17 , a(ka=7)*17+b(kb=5) % 26 = 7*17+5 % 26  = 20, typecasting 20 + 65 = 85, ASCII for U, hence R encrypts into U 
    //returns decryptedletter after converting back from ascii value by typecasting (int) 'A'  
    return decryptedletter;
}

//Function takes alpha/beta key and calls encryption function to encrypt plaintext given
void encrypt(char plaintext[]){
    int alphakey, betakey;
    char affinecipher[500];
    int i = 0;
    int strlength;

    //User can choose keys for affine cipher encryption/decryption
    printf("Choose your key alpha: ");
    scanf("%d", &alphakey);
    printf("Choose your key beta: ");
    scanf("%d", &betakey);
    
    //takes strlength
    strlength = strlen(plaintext);

    //for each index of the user entered plaintext, encrypts using encryption function which is the affine cipher
    //Uses a while look to iterate through the array until a NULL character is found to mark end of array
    while (plaintext[i] != '\0'){
        if (plaintext[i] != ' '){
            affinecipher[i] = encryption(plaintext[i], alphakey, betakey, strlength);
        }else{
            affinecipher[i] = ' ';
        }
        i++;
    }
    //prints the newly encrypted ciphertext
    printf("Your ciphertext: %s\n", affinecipher);

}

//EEA = GCD(a,b) = ax+by 
int exteuclideanalgorithm (int a, int b, int *x, int * y){
    //Since we are working with affine cipher we will use mod 26
    int mod = 26;
    //used to hold memory location during each iteration of the recursion
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
    //Calls extended euclidean algorithm function to calculate inverse
    int inverse = exteuclideanalgorithm(a, mod, &x, &y);
    if (inverse == 1){
        calculations = (x % mod + mod) % mod;
        
    }
    else{
        printf("There is no mod inverse");
    }
    return calculations;
}

//Function to decrypt individual character of the ciphertext using the keys and inverse calculated
char decryption (char affinecipher, int a, int b, int inv, int strlength){
    int affinedecryption = 0;
    int conversion;
    char decryptedletter;

    //Converts to ascii value by typecasting 'A' with int, so (int) 'A' = 65
    conversion = affinecipher + (int)'A';
    //decrypts the letter
    affinedecryption = (inv * (conversion - b)) % 26;
    //Stores the letter and converts it back using (int) 'A'
    decryptedletter = affinedecryption + (int)'A';

    //Returns the stored decrypted letter
    return decryptedletter;
}

//Function takes alpha/beta key and calls decryption function to decrypt ciphertext given
void decrypt(char ciphertext[]){
    int alphakey, betakey;
    char decrypted [500];
    int i = 0;
    int inverse;
    int strlength = strlen(ciphertext);

    //User can choose keys for affine cipher encryption/decryption
    printf("Choose your key alpha: ");
    scanf("%d", &alphakey);
    printf("Choose your key beta: ");
    scanf("%d", &betakey);
    
    //Function to work out modular inverse of Alpha key
    inverse = inversemod(alphakey);
    printf("Modular inverse is \n%d ", inverse);
   
    //for each index of the user entered plaintext, encrypts using encryption function which is the affine cipher
    //Uses a while look to iterate through the array until a NULL character is found to mark end of array
    while (ciphertext[i] != '\0'){
        if (ciphertext[i] != ' '){
            decrypted[i] = decryption(ciphertext[i], alphakey, betakey, inverse, strlength);
        }else{
            decrypted[i] = ' ';
        }
        i++;
    }
    
    //prints the newly encrypted ciphertext
    printf("\nYour ciphertext: %s\n", decrypted);

}
