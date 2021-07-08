#ifndef SWITCHER_H
#define SWITCHER_H

const int BYTE_SIZE = 256;
char SWITCHER_ALPHABET[BYTE_SIZE];

inline void init_switcher()
{
    for (int i = 0; i < BYTE_SIZE; ++i)
        SWITCHER_ALPHABET[i] = i;

    for (int i = '0'; i <= '8'; ++i)
        SWITCHER_ALPHABET[i] = i + 1;
    SWITCHER_ALPHABET['9'] = '0';

    for (int i = 'a'; i <= 'z'; ++i)
        SWITCHER_ALPHABET[i] = i - 'a' + 'A';

    for (int i = 'A'; i <= 'Z'; ++i)
        SWITCHER_ALPHABET[i] = i - 'A' + 'a';
}

inline char switch_char(const char ch)
{
    return SWITCHER_ALPHABET[static_cast<int>(ch)];
}

#endif // SWITCHER_H
