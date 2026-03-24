/*ONOMATEPONYMO: AIKATERINH PAPOUTSOGLOU 
  AEM: 03682*/
//HOMEWORK 2:

#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include "hw2.h"

void lower(char *word) ;
int read_synonyms(char *filename, char synonyms[][MAX_WORD_LEN*2]) ;

//main function
int main (int argc, char *argv[]) 
{
    char Words_Array[MAX_WORDS][MAX_WORD_LEN]={{'\0'}}, *Order_of_Words_Array[MAX_WORDS][2]={{NULL}};
    int i, valid_choice, Frequency_Words_Array[MAX_WORDS]={0};
    
    saving_words_function( Words_Array, Order_of_Words_Array);

    /*Choice from the command line*/
    //stadio 0
    for(i=1; i<argc; i++)
    {
        valid_choice=0;
        if(strcmp(argv[i],"-p")==0)
        {
            valid_choice=1;
        
            saving_words_function(Words_Array, *Order_of_Words_Array);
            print_text_function (*Order_of_Words_Array[MAX_WORDS][2],MAX_WORD_LEN);
        }
        if(strcmp(argv[i],"-m")==0)
            {
                valid_choice=1;
            } 
        if(strcmp(argv[i],"-r")==0)
            {
                valid_choice=1;
            }
        if(valid_choice==0)
            {
                printf("Incorrect command-line arguments!");
            }
        }
    
    return 0;
    }
/*read and save the text into the arrays*/
//stadio 1

void saving_words_function(char Words_Array[MAX_WORDS][MAX_WORD_LEN], 
                           char *Order_of_Words_Array[MAX_WORDS][2])
{
    int j, k, l=0, already_exists, exit;
    char format[8], Whole_Words_Array[MAX_WORDS][MAX_WORD_LEN];

    sprintf(format,"%%%ds",MAX_WORD_LEN-1);

    for (j=0; j<MAX_WORDS; j++)
    {   
       exit=scanf(format , Whole_Words_Array[j]);
            if(exit==EOF)
            {
                break;
            }
        lower(Words_Array[j]);
        lower(Whole_Words_Array[j]);
    }

    for(j=0; j<MAX_WORDS; j++)
    {   
        already_exists=0;

        for(k=0; k<j; k++)
        {
            if(strcmp(Whole_Words_Array[j],Whole_Words_Array[k])==0)
            {
                Order_of_Words_Array[j][0]=Whole_Words_Array[k];
                already_exists=1;
                break;
            }
        }
        if(already_exists==0)
        {
            l++;
            strcpy(Words_Array[l],Whole_Words_Array[j]);
            Order_of_Words_Array[j][0]= Whole_Words_Array[l];  
        }
    }
    return;
}
/*print the words */   
//stadio 2

 void print_text_function (char *Order_of_Words_Array[MAX_WORDS][2],int linelen)
    {
         int i;
            for(i=0; i<MAX_WORDS; i++)
            {
                toupper(*(Order_of_Words_Array + i)[0]);
                printf("%s", *(Order_of_Words_Array + i)[0]);
            }
     }

/**/
//stadio 3


/****************************************
 Converts the given string to lowercase 
*****************************************/
void lower(char *word)
{
    while (*word)
    {
        *word = tolower(*word);
        word++;
    }
}
    
/************************************************************
 Reads pairs of words and their synonyms from the given file
 and stores them in the table, one pair per line.
 The words of a pair are separated by a '\0'.

  Assumes the table has MAX_SYNONYMS rows.

  Returns 1 on success, 0 on failure.
*************************************************************/
int read_synonyms(char *filename, char synonyms[][MAX_WORD_LEN*2]) {
    int i;
    char word[MAX_WORD_LEN]={'\0'}, word_synonym[MAX_WORD_LEN]={'\0'};
    char format[30];
    FILE *fp;
  
    fp = fopen(filename, "r");
    if(!fp) {
        fprintf(stderr, "Error: Could not open file \"%s\" for reading\n", filename);
        return 0;
    }
  
    sprintf(format, "%%%ds", MAX_WORD_LEN-1);
    memset(synonyms, 0, MAX_SYNONYMS*MAX_WORD_LEN*2);  

    i=0;
    while(i < MAX_SYNONYMS && EOF != fscanf(fp, format, word)) {
        lower(word);
        strcpy(synonyms[i], word);
        if (EOF == fscanf(fp, format, word_synonym))  {   
            fclose(fp);
            fprintf(stderr, "Error: Missing synonym for word \"%s\"\n", word);
            return 0;
        }
        lower(word_synonym);
        strcpy(synonyms[i]+strlen(word)+1, word_synonym);
        i++;
    }
    fclose(fp);
    return 1;
}
