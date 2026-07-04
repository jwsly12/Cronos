/*
Para criar uma função de comparação de string 
Primeiro vamos entender a lógica por trás dessa função

Conceito Metemático:

Para a comparação de string precisamos saber se o 
primeiro caractere da string A e B são iguais

A matemática por trás disso é que: Se uma string for
subtraida por ela mesma o resultado sempre será 0.

Exemplo:

test = 74 65 73 74 00 (HEX)
test - test = 0

Conceito Algortimico:

Só precisamos percorer as duas strings e
comparar se seus caracteres são iguais
Usando o calculo para nos guiar.

*/

int str_compare(char* str1, char* str2) {
    while (*str1 == *str2) {
        if (*str1 == '\0') {
            return 0;
        }
        str1++;
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}