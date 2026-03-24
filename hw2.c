/*ONOMATEPONYMO: AIKATERINH PAPOUTSOGLOU 
  AEM: 03682*/
//HOMEWORK 2:

#include<string.h>
#include<stdio.h>
#include<ctype.h>
#include "hw2.h"

void lower(char *word) ;
int read_synonyms(char *filename, char synonyms[][MAX_WORD_LEN*2]) ;
void saving_words_function(char Whole_Words_Array[MAX_WORDS][MAX_WORD_LEN], 
                           char *Order_of_Words_Array[MAX_WORDS][2]);
void print_text_function (char *Order_of_Words_Array[MAX_WORDS][2],int linelen) ;
void frequency_function (char *Order_of_Words_Array[MAX_WORDS][2],int pinakas_akeraion[MAX_WORDS] ) ;
int Max_integer_Function(int pinakas_akeraion[MAX_WORDS] );
int Max_Frequency_function(char Words_Array[MAX_WORDS][MAX_WORD_LEN], char *Order_of_Words_Array[MAX_WORDS][2],
                           char Empty_Word_Array[MAX_WORDS][MAX_WORD_LEN]);
void Printing_function(char Words_Array[MAX_WORDS][MAX_WORD_LEN]);
void synonyms_function(char *Order_of_Words_Array[MAX_WORDS][2], char synonyms[MAX_SYNONYMS][MAX_WORD_LEN*2]);


//main function 
int main (int argc, char *argv[]) 
{
    char Words_Array[MAX_WORDS][MAX_WORD_LEN]={{'\0'}}, *Order_of_Words_Array[MAX_WORDS][2]={{NULL}},
        Empty_Word_Array[MAX_WORDS][MAX_WORD_LEN]={{'\0'}},
        synonyms[MAX_SYNONYMS][MAX_WORD_LEN*2];
    int i, valid_choice, p_choice=0, m_choice=0, r_choice=0, file_index;
    

    /*Choice from the command line*/
    //stadio 0
    if(argc==1)
    {
        printf("Incorrect command-line arguments!\n");
            return 1;
    }
    for(i=1; i<argc; i++)
    {
        //VALID CHOICE FLAG
        valid_choice=0;

        if(strcmp(argv[i],"-p")==0)
        {
            valid_choice=1;
            p_choice=1;      
        }
        if(strcmp(argv[i],"-m")==0)
        {
            valid_choice=1;
            m_choice=1;
        } 
        if(strcmp(argv[i],"-r")==0)
        {
            valid_choice=1;
            r_choice=1;
            file_index=++i;
        }
        if(valid_choice==0)
        {
            printf("Incorrect command-line arguments!\n");
            return 1;
        }
        }
saving_words_function(Words_Array, Order_of_Words_Array);
    //ARGUMENT VALID CHOICE
    if(m_choice==1)
    {
        Max_Frequency_function( Words_Array, Order_of_Words_Array, Empty_Word_Array);
    }
    if(r_choice==1)
    {
        read_synonyms(argv[file_index], synonyms);
        synonyms_function(Order_of_Words_Array, synonyms);
      //  print_text_function (Order_of_Words_Array, MAX_LINE_LEN);
    }
    if(p_choice==1)
    {
        print_text_function (Order_of_Words_Array,MAX_LINE_LEN);
    }
    

    return 0;
}
/*read and save the text into the arrays*/
//stadio 1
void saving_words_function(char Words_Array[MAX_WORDS][MAX_WORD_LEN], 
                           char *Order_of_Words_Array[MAX_WORDS][2])
{
    int j, k, l=0, already_exists, right_position;
    char format[16], Whole_Words_Array[MAX_WORDS][MAX_WORD_LEN]={{'\0'}};

    sprintf(format,"%%%ds",MAX_WORD_LEN-1);


    for(j=0; (j<MAX_WORDS) && (scanf(format , Whole_Words_Array[j]) != EOF); j++)
    {   
    
        lower(Words_Array[j]);
        lower(Whole_Words_Array[j]);
        already_exists=0;

        for(k=0; k<j; k++)
        {
            if(strcmp(Whole_Words_Array[j],Whole_Words_Array[k])==0)
            {
                right_position = (Order_of_Words_Array[k][0] - Order_of_Words_Array[0][0])/MAX_WORD_LEN;
                Order_of_Words_Array[j][0]=Words_Array[right_position]; 
                already_exists=1;
                break;
            }
        }
        if(already_exists==0)
        {
            strcpy(Words_Array[l],Whole_Words_Array[j]);
            Order_of_Words_Array[j][0]= Words_Array[l];  
            l++;
        }
    }
        return;  
}
 
 /*print the words */  
 //stadio 2 
void print_text_function (char *Order_of_Words_Array[MAX_WORDS][2],int linelen)
{
    int i, line_length=1 ;

        printf("\n");
        *Order_of_Words_Array[0][0]=toupper(*Order_of_Words_Array[0][0]);
        printf("%s", Order_of_Words_Array[0][0]);
         line_length+=strlen(Order_of_Words_Array[0][0]);
    
    //no synonyms case
    if (Order_of_Words_Array[0][1]!=NULL)
    {
        *Order_of_Words_Array[0][1]=toupper(*Order_of_Words_Array[0][1]);
         printf(" (%s)", Order_of_Words_Array[0][1]);
        line_length+=strlen(Order_of_Words_Array[0][0])+ strlen(Order_of_Words_Array[0][1])+ 3;
    }
     
    for(i=1; (i<MAX_WORDS) && (Order_of_Words_Array[i][0]!=NULL); i++)
    {  
       if (Order_of_Words_Array[i][1]==NULL)
        {
            if( (strcmp(Order_of_Words_Array[i-1][0],"!")==0) ||
                (strcmp(Order_of_Words_Array[i-1][0],".")==0) || 
                (strcmp(Order_of_Words_Array[i-1][0],"?")==0))
            {
                *Order_of_Words_Array[i][0]=toupper(*Order_of_Words_Array[i][0]);
            }
            else 
            {
                *Order_of_Words_Array[i][0]=tolower(*Order_of_Words_Array[i][0]);
            }
                    line_length+= strlen(Order_of_Words_Array[i][0])+1;

                    if(line_length>linelen)
                    {
                        printf("\n%s", Order_of_Words_Array[i][0]);
                        line_length=strlen(Order_of_Words_Array[i][0])+1;
                    }
                    else 
                    {
                        printf(" ");
                        printf("%s", Order_of_Words_Array[i][0]);
                    }    
                
        }
        //synonyms case
        else
        {
             if( (strcmp(Order_of_Words_Array[i-1][0],"!")==0) ||
                (strcmp(Order_of_Words_Array[i-1][0],".")==0) || 
                (strcmp(Order_of_Words_Array[i-1][0],"?")==0))
            {
                *Order_of_Words_Array[i][0]=toupper(*Order_of_Words_Array[i][0]);
                *Order_of_Words_Array[i][1]=toupper(*Order_of_Words_Array[i][1]);
            }
            else 
            {
                *Order_of_Words_Array[i][0]=tolower(*Order_of_Words_Array[i][0]);
                *Order_of_Words_Array[i][1]=tolower(*Order_of_Words_Array[i][1]);
            }
                        
            line_length+= strlen(Order_of_Words_Array[i][0]+strlen(Order_of_Words_Array[i][1]))+3;

            if(line_length>linelen)
            {
                if(line_length-strlen(Order_of_Words_Array[i][1])-2<=linelen)
                {
                    printf(" %s\n(%s)", Order_of_Words_Array[i][0], 
                                        Order_of_Words_Array[i][1]);
                    line_length=strlen(Order_of_Words_Array[i][1])+3;
                }
                else
                {
                    printf("\n%s (%s)", Order_of_Words_Array[i][0], Order_of_Words_Array[i][1]);
                    line_length=strlen(Order_of_Words_Array[i][0])+strlen(Order_of_Words_Array[i][1])+4;
                }
            }
            else 
            {
                printf(" ");
                printf("%s (%s)", Order_of_Words_Array[i][0], Order_of_Words_Array[i][1]);
            }    
        }
    }
        
        printf("\n");

         return;
}

/*calculcate the frequency of words and save it into an array */
//stadio 3

//calculating how many time does a word exist
void frequency_function (char *Order_of_Words_Array[MAX_WORDS][2],int pinakas_akeraion[MAX_WORDS] )
{
        int i, j, position,reps;
    for(i=0; ((i<MAX_WORDS) && (Order_of_Words_Array[i][0]!=NULL)); i++)
    {
        reps = 1;
        position=(Order_of_Words_Array[i][0]-
                    Order_of_Words_Array[0][0])/MAX_WORD_LEN;
        for(j=i+1; ((j<MAX_WORDS) && (Order_of_Words_Array[j][0]!=NULL)); j++)
        {
            if (Order_of_Words_Array[i][0]==Order_of_Words_Array[j][0])
            {
                pinakas_akeraion[j] = -1;
                reps++;
            }
        }
        if (pinakas_akeraion[i] >= 0)
        {
            pinakas_akeraion[position] = reps;
        }
    }
        return;
}

//function for finding the max number of an array
int Max_integer_Function(int pinakas_akeraion[MAX_WORDS] )
{
    int i, max;
       
     max=pinakas_akeraion[0];

    for(i=0; i<MAX_WORDS; i++)
    {
        if(pinakas_akeraion[i]>max)
        {
            max=pinakas_akeraion[i];
        }
    }
    return (max);
}

//organising the array with tha words that 
//are mostly frequent
int Max_Frequency_function(char Words_Array[MAX_WORDS][MAX_WORD_LEN], char *Order_of_Words_Array[MAX_WORDS][2],
                           char  Empty_Word_Array[MAX_WORDS][MAX_WORD_LEN])
{
        int pinakas_akeraion[MAX_WORDS]={0}, max, i, k=0;
        
        frequency_function(Order_of_Words_Array, pinakas_akeraion);
        max = Max_integer_Function(pinakas_akeraion);
        
        for(i=0; i<MAX_WORDS; i++)
        {

                if(pinakas_akeraion[i]==max)
                {
                    strcpy(Empty_Word_Array[k],Words_Array[i]);
                    k++;
                }
            
        }
        printf("Max: %d\n", max);
        Printing_function(Empty_Word_Array);

        return max;
}

//function for printing the most friquent words
void Printing_function(char Words_Array[MAX_WORDS][MAX_WORD_LEN])
    {
        int i;
        for(i=0; (i<MAX_WORDS && Words_Array[i][0]!='\0'); i++)
        {
            printf("%s\n", Words_Array[i]);
        }
            return;
    }
/*find the synonyms and print the text with them*/
//stadio 4
void synonyms_function(char *Order_of_Words_Array[MAX_WORDS][2], char synonyms[MAX_SYNONYMS][MAX_WORD_LEN*2])
{
        int i, j, syn_word_length;
        for (i=0; i<MAX_WORDS && Order_of_Words_Array[i][0]!=NULL; i++)
        {
            for (j=0; j<MAX_SYNONYMS && Order_of_Words_Array[i][0]!=NULL; j++)
            {
                if(strcmp(Order_of_Words_Array[i][0],synonyms[j])==0)
                {
                    syn_word_length=strlen(synonyms[j]);
                    Order_of_Words_Array[i][1]=&synonyms[j][syn_word_length+1];
                   
                }
            }
        }
        return;
}


/*
 Converts the given string to lowercase 
                                    */
void lower(char *word)
{
    while (*word)
    {
        *word = tolower(*word);
        word++;
    }
}
    
/*
 Reads pairs of words and their synonyms from the given file
 and stores them in the table, one pair per line.
 The words of a pair are separated by a '\0'.

  Assumes the table has MAX_SYNONYMS rows.

  Returns 1 on success, 0 on failure.
*/
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
