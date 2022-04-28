#include <wchar.h>
#include <errno.h>
#include <locale.h>
#include <stdint.h>

//All system variables the cipher depends on
const wchar_t* SYS_0 = L"abcdefghijklmnopqrstuvwxyz";
const wchar_t* SYS_1 = L"abcd01efgh45ijkl23mnopqr89stuv6wxyz7";
const wchar_t* SYS_2 = L"ab cd01ef?,gh45ij@#$kl23mn.%&opqr89stuv6wx!yz7*";

//Spacing range:
//SYS_0 (0~25) | SYS_1 (0~35) | SYS_2 (0~46)
//Any spacing out of boundary may lead to issues
//Note: the results will be allocated back to the given text pointer
void encrypt(uint8_t system, uint8_t spacing, wchar_t* text) {
  setlocale(LC_ALL, "");
  wprintf(L"\nCheck 1!\n");
  wchar_t temp[2];
  unsigned int i, loop;
  size_t text_size = wcslen(text);
  wprintf(L"\n\nSIZE: %ld\n\n", text_size);
  wprintf(L"\nCheck 2!\n");
  wchar_t result[text_size+1];
  switch (system) {
    case 0:
      wprintf(L"\nCheck 3!\n");
      wprintf(L"result var: %ls", result);
      for (loop=0; loop<text_size+1; loop++) {
        //26 refers to the length of SYS_0
        wprintf(L"\nChar: %lc\n", text[loop]);
        wprintf(L"\nCode err: %d\n", errno);
        for (i=0; i<26; i++) {
          wprintf(L"\nCheck 4!\n");
          wprintf(L"TEMP: %ls", temp);
          wprintf(L"\nSYS Char: %lc\n", SYS_0[i]);
          wprintf(L"\nNum: %d\n", i);
          if (SYS_0[i]==text[loop]) {
            wprintf(L"\nCheck 5!\n");
            if (i+spacing<26) i += spacing;
            else i = i+spacing-26;
            wprintf(L"\nCheck 6!\n");
            swprintf(temp, 2, L"%lc", SYS_0[i]);
            wprintf(L"\nCheck 7!\n");
            wcscat(result, temp);
            break;
            //The -32 will return the capital version of the char
          } else if (SYS_0[i]-32==text[loop]) {
            wprintf(L"\nCheck 6_2!\n");
            if (i+spacing<26) i += spacing;
            else i = i+spacing-26;
            wprintf(L"\nCheck 7_2!\n");
            swprintf(temp, 2, L"%lc", SYS_0[i]-32);
            wprintf(L"\nCheck 8_2!\n");
            wcscat(result, temp);
            wprintf(L"\nCheck 9_2!\n");
            break;
          }
        }
        wprintf(L"\n\nSIZEOFRESULT: %ld\n\n", wcslen(result));
        if (wcslen(result)<loop+1) {
          wprintf(L"\nCheck 5_3!\n");
          swprintf(temp, 2, L"%lc", text[loop]);
          wprintf(L"\nCheck 6_3!\n");
          wcscat(result, temp);
          wprintf(L"\nCheck 7_3!\n");
          wprintf(L"%ls", result);
        }
      }
      break;
    case 1:
      for (loop=0; loop<text_size; loop++) {
        //36 refers to the length of SYS_1
        for (i=0; i<36; i++) {
          if (SYS_1[i]==text[loop]) {
            if (i+spacing<36) i += spacing;
            else i = i+spacing-36;
            swscanf(temp, L"%c", SYS_1[i]);
            wcscat(result, temp);
          } else {
            //The -32 will return the capital version of the char
            if (SYS_1[i]-32==text[loop]) {
              if (i+spacing<36) i += spacing;
              else i = i+spacing-36;
              swscanf(temp, L"%c", SYS_1[i]-32);
              wcscat(result, temp);
            } else {
              swscanf(temp, L"%c", text[loop]);
              wcscat(result, temp);
            }
          }
        }
      }
      break;
    case 2:
      for (loop=0; loop<text_size; loop++) {
        //47 refers to the length of SYS_2
        for (i=0; i<47; i++) {
          if (SYS_2[i]==text[loop]) {
            if (i+spacing<47) i += spacing;
            else i = i+spacing-47;
            swscanf(temp, L"%c", SYS_2[i]);
            wcscat(result, temp);
          } else {
            //The -32 will return the capital version of the char
            if (SYS_2[i]-32==text[loop]) {
              if (i+spacing<47) i += spacing;
              else i = i+spacing-47;
              swscanf(temp, L"%c", SYS_2[i]-32);
              wcscat(result, temp);
            } else {
              swscanf(temp, L"%c", text[loop]);
              wcscat(result, temp);
            }
          }
        }
      }
      break;
  }
  wcscpy(text, result);
}

//Spacing range:
//SYS_0 (0~25) | SYS_1 (0~35) | SYS_2 (0~46)
//Any spacing out of boundary may lead to issues
//Note: the results will be allocated back to the given text pointer
void decrypt(uint8_t system, uint8_t spacing, wchar_t* text) {
  wchar_t temp[2];
  unsigned int i, loop;
  size_t text_size = wcslen(text);
  wchar_t result[text_size];
  switch (system) {
    case 0:
      for (loop=0; loop<text_size; loop++) {
        //26 refers to the length of SYS_0
        for (i=0; i<26; i++) {
          if (SYS_0[i]==text[loop]) {
            if (i-spacing>-1) i -= spacing;
            else i = i-spacing+26;
            swscanf(temp, L"%c", SYS_0[i]);
            wcscat(result, temp);
          } else {
            //The -32 will return the capital version of the char
            if (SYS_0[i]-32==text[loop]) {
              if (i-spacing>-1) i -= spacing;
              else i = i-spacing+26;
              swscanf(temp, L"%c", SYS_0[i]-32);
              wcscat(result, temp);
            } else {
              swscanf(temp, L"%c", text[loop]);
              wcscat(result, temp);
            }
          }
        }
      }
      break;
    case 1:
      for (loop=0; loop<text_size; loop++) {
        //36 refers to the length of SYS_1
        for (i=0; i<36; i++) {
          if (SYS_1[i]==text[loop]) {
            if (i-spacing>-1) i -= spacing;
            else i = i-spacing+36;
            swscanf(temp, L"%c", SYS_1[i]);
            wcscat(result, temp);
          } else {
            //The -32 will return the capital version of the char
            if (SYS_1[i]-32==text[loop]) {
              if (i-spacing>-1) i -= spacing;
              else i = i-spacing+36;
              swscanf(temp, L"%c", SYS_1[i]-32);
              wcscat(result, temp);
            } else {
              swscanf(temp, L"%c", text[loop]);
              wcscat(result, temp);
            }
          }
        }
      }
      break;
    case 2:
      for (loop=0; loop<text_size; loop++) {
        //47 refers to the length of SYS_2
        for (i=0; i<47; i++) {
          if (SYS_2[i]==text[loop]) {
            if (i-spacing>-1) i -= spacing;
            else i = i-spacing+47;
            swscanf(temp, L"%c", SYS_2[i]);
            wcscat(result, temp);
          } else {
            //The -32 will return the capital version of the char
            if (SYS_2[i]-32==text[loop]) {
              if (i-spacing>-1) i -= spacing;
              else i = i-spacing+47;
              swscanf(temp, L"%c", SYS_2[i]-32);
              wcscat(result, temp);
            } else {
              swscanf(temp, L"%c", text[loop]);
              wcscat(result, temp);
            }
          }
        }
      }
      break;
  }
  wcscpy(text, result);
}
