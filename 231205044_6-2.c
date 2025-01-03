/**
 * ã¯ã©ã¹?¼A
 * å­¦ç±çªå·?¼?231205044
 * æ°å?¼å²¡ç°é?ç?
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 1024 //bufferã®ãµã¤ãº

// ã¨ã©ã¼ã¡ã?ã»ã¼ã¸åºåé¢æ°
void error_message(const char *message)
{
    fprintf(stderr, "%s\n", message);
}

int main(int argc, char *argv[])
{
    // ã³ãã³ãã©ã¤ã³å¼æ°ãæ³å®å¤ã?®å ´å?
    if (argc != 3)
    {
        error_message("usage: 231205044_6-2 <input file> <output file>");
        return EXIT_FAILURE; //ãã­ã°ã©ã?ç°å¸¸ã®ããå¼·å¶çµäº?
    }
    /*input file, output fileã®ãã¡ã¤ã«ãã¤ã³ã¿ã¨input fileãæ?¼ç´ããbufferãå®£è¨*/
    FILE *input_file;
    FILE *output_file;
    char buffer[MAX_LEN];

    /*inputfileãéã?*/
    input_file = fopen(argv[1], "r");
    if (input_file == NULL) //ãã¡ã¤ã«ãéããªãã£ãå?´å?
    {
        error_message("å¥åãã¡ã¤ã«ãéãã¾ããã§ããã?");
        return 1; //ãã­ã°ã©ã?ç°å¸¸ã®ããå¼·å¶çµäº?
    }
    /*outputfileãéã?*/
    output_file = fopen(argv[2], "w");
    if (output_file == NULL) //ãã¡ã¤ã«ãéããªãã£ãå?´å?
    {
        error_message("åºåãã¡ã¤ã«ãéãã¾ããã§ããã?");
        fclose(input_file);
        return EXIT_FAILURE; //ãã­ã°ã©ã?ç°å¸¸ã®ããå¼·å¶çµäº?
    }

    // ãã¡ã¤ã«å?å®¹ãç©ºç½ã¾ãã?¯ã¿ãã§å?å²ãã¦åºåããå?¦ç?
    while (fgets(buffer, sizeof(buffer), input_file))
    {
        char *ptr = buffer; // ãããã¡æ¢ç´¢ããæ?å­å
        char tmp[MAX_LEN]; // æ¹è¡ã§å?å²ããæ?å­å?ãä¿æ
        int tmp_index = 0;

        while (*ptr != '\0')
        {
            if (isspace(*ptr)) // ç©ºç½ã¾ãã?¯ã¿ããæ¤å?º
            {
                if (tmp_index > 0) // æ¹è¡ã?®ã¿ã®è¡ãã¹ã­ã?ã?
                {
                    tmp[tmp_index] = '\0'; // ç¾å¨ã®æ?å­å?ãçµäº?
                    fprintf(output_file, "%s\n", tmp); // åºå?
                    tmp_index = 0; // åæå?
                }
            }
            else //ç©ºç½ã¾ãã?¯ã¿ãããªã?å ´å?
            {
                tmp[tmp_index] = *ptr; //é¨å?æ?å­å?ã«æ?å­ãè¿½å?
                tmp_index++; //æ¬¡ã®æ?å­ã?®æ ¼ç´å?´æã«ç§»è¡?
            }
            ptr++; //æ¬¡ã®æ?å­ã?®è§£æã«ç§»è¡?
        }

        /*æå¾ã¾ã§ç©ºç½ã¾ãã?¯ã¿ãããªãã£ãå?´åï¼ãã®ã¾ã¾ã®æ?å­å?ãæ ¼ç´?*/
        if (tmp_index > 0)
        {
            tmp[tmp_index] = '\0';
            fprintf(output_file, "%s\n", tmp);
        }
    }

    // ãã¡ã¤ã«ãéãã
    fclose(input_file);
    fclose(output_file);

    return 0;
}
