#ifndef SWITCHER_H
#define SWITCHER_H

const int BYTE_SIZE = 256;
char ALPHABET[BYTE_SIZE];

inline void init_switcher()
{
    for (int i = 0; i < BYTE_SIZE; ++i)
        ALPHABET[i] = i;

    for (int i = '0'; i <= '8'; ++i)
        ALPHABET[i] = i + 1;
    ALPHABET['9'] = '0';

    for (int i = 'a'; i <= 'z'; ++i)
        ALPHABET[i] = i - 'a' + 'A';

    for (int i = 'A'; i <= 'Z'; ++i)
        ALPHABET[i] = i - 'A' + 'a';
}

inline char switch_char(const char ch)
{
    return ALPHABET[(int)ch];
}

#endif // SWITCHER_H
