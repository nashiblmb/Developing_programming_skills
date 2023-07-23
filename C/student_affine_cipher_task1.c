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

/*
    Nashib Limbu
    Affine Cipher Project during University
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
void convert_string_to_upper(char string[]);
char affine_encryption (char plaintext, int a_key, int b_key);
void perform_encryption(char plaintext[]);

void perform_decryption(char ciphertext[]);
char affine_decryption (char ciphertext, int a_key, int b_key, int inv);
int compute_inverse_mod (int a_key);
int extended_euclidean_algorithm (int a, int b, int *x, int *y);

int main(){
    char text[500];
    char user_choice;
    int continue_loop = 0;

    printf("Enter the text or cipher that you need to encrypt/decrypt\n");
    fgets(text, sizeof(text), stdin);
    
    convert_string_to_upper(text);
    text[strlen(text)-1] = '\0'; // Remove the trailing newline character

    while (continue_loop==0){
        printf("Type: E for encrypt, D for decrypt, N to exit: \n");
        scanf("%c", &user_choice);

        if (user_choice =='E' || user_choice == 'e'){
            perform_encryption(text);
            continue_loop = 1;
        }
        else if (user_choice == 'D' || user_choice == 'd'){
            perform_decryption(text);
            continue_loop = 1;
        }
        else if (user_choice == 'N' || user_choice == 'n' ){
            printf("Exiting program");
            continue_loop = 1;
        }
    }

    return 0;
}

void convert_string_to_upper(char string[]){
    int i, j;
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

char affine_encryption (char plaintext, int a_key, int b_key){
    int encrypted_val;
    char encrypted_char;
    int ascii_offset;

    ascii_offset =  plaintext - (int)'A';
    encrypted_val = (a_key*ascii_offset+b_key)  % 26;
    encrypted_char = encrypted_val + (int)'A';
  
    return encrypted_char;
}

void perform_encryption(char plaintext[]){
    int alpha_key, beta_key;
    char encrypted_text[500];
    int i = 0;

    printf("Choose your alpha key: ");
    scanf("%d", &alpha_key);
    printf("Choose your beta key: ");
    scanf("%d", &beta_key);

    while (plaintext[i] != '\0'){
        if (plaintext[i] != ' '){
            encrypted_text[i] = affine_encryption(plaintext[i], alpha_key, beta_key);
        }else{
            encrypted_text[i] = ' ';
        }
        i++;
    }

    printf("Your ciphertext: %s\n", encrypted_text);
}

int extended_euclidean_algorithm (int a, int b, int *x, int *y){
    int x1, y1;

    if ( a==0){
        *x = 0;
        *y = 1;
        return b;
    }

    int gcd = extended_euclidean_algorithm (b%a, a, &x1, &y1);
    *x = y1 - (b/a) * x1;
    *y = x1;
    
    return gcd;
}

int compute_inverse_mod (int a_key){
    int mod = 26;
    int x, y;
    int inverse = extended_euclidean_algorithm(a_key, mod, &x, &y);
    if (inverse == 1){
        return (x % mod + mod) % mod;
    }
    else{
        printf("There is no mod inverse");
        return -1;
    }
}

char affine_decryption (char ciphertext, int a_key, int b_key, int inv){
    int decrypted_val;
    int ascii_offset;
    char decrypted_char;

    ascii_offset = ciphertext - (int)'A';
    decrypted_val = (inv * (ascii_offset - b_key)) % 26;
    decrypted_char = decrypted_val + (int)'A';

    return decrypted_char;
}

void perform_decryption(char ciphertext[]){
    int alpha_key, beta_key;
    char decrypted_text[500];
    int i = 0;
    int inverse;

    printf("Choose your alpha key: ");
    scanf("%d", &alpha_key);
    printf("Choose your beta key: ");
    scanf("%d", &beta_key);
    
    inverse = compute_inverse_mod(alpha_key);
    printf("Modular inverse is: %d ", inverse);
   
    while (ciphertext[i] != '\0'){
        if (ciphertext[i] != ' '){
            decrypted_text[i] = affine_decryption(ciphertext[i], alpha_key, beta_key, inverse);
        }else{
            decrypted_text[i] = ' ';
        }
        i++;
    }
    
    printf("\nYour decrypted text: %s\n", decrypted_text);
}
