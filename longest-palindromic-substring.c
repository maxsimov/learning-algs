#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


char *mkResult(char *s, int len)
{
    char *result = malloc(sizeof(char)*(len+1));
    
    if (result == 0)
        return 0;
    
    strncpy(result, s, len);
    result[len] = 0;
    
    return result;
}

void _longestPalindrome(char *s, int len, int *h, int *pL, int *pR, bool even)
{
    int pLen = (*pR-*pL)+1;
    int curLen = 0;
    
    int c = 0, r = 0;
    
    h[0] = 1 - (even?1:0);
        
    for (int e=1; e<len; ++e)
    {   
        if (e > r)
        {
            int i = e-1, j = e + 1 - (even?1:0);

            while (i>=0 && j<len && s[i] == s[j])
                i--, j++;
            
            curLen = j - i - 1;
            
            h[e] = curLen; 
            
            c = e;
            r = j-1;
        } else {
            int mirrorIndex = 2*c - e - (even?1:0);
            int mirSize = h[mirrorIndex]/2;
            int maxMirSize = r-e;
            
            if (mirSize > maxMirSize)
                mirSize = maxMirSize;
            
            int i = e-mirSize-1, j = e + mirSize + 1 - (even?1:0);

            while (i>=0 && j<len && s[i] == s[j])
                i--, j++;

            curLen = j - i - 1;
            h[e] = curLen;
            
            if (j-1 > r)
            {
                c = e;
                r = j-1;                    
            }
        }
        
        if (curLen > pLen)
        {
            pLen = curLen;
            *pL = e - pLen/2;
            *pR = e + pLen/2 - (even? 1: 0);                
        }
    }
}
    
char *longestPalindrome(char * s)
{
    int len = 0;
    
    while (s[len])
        ++len;
        
    if (len < 2)
        return mkResult(s, len);

    int *h = malloc(sizeof(int)*len);
    int pL = 0;
    int pR = 0;

    _longestPalindrome(s, len, h, &pL, &pR, true);
    _longestPalindrome(s, len, h, &pL, &pR, false);
    
    free(h);
    
    return mkResult(s+pL, pR-pL+1);
}
