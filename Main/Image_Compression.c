// C code #Image Compression#

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function to calculate word length
int Code_length(char* code)
{
    int l = 0;
    while (*(code + l) != '\0')
        l++;
    return l;
}


// function to concatenate the words
void Str_concat(char* str, char* parentcode, char add)
{
    int i = 0;
    while (*(parentcode + i) != '\0')
    {
        *(str + i) = *(parentcode + i);
        i++;
    }

    if (add != '2')
    {
        str[i] = add;
        str[i + 1] = '\0';
    }

    else
        str[i] = '\0';
}



// function to find fibonacci number

int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}



// MAIN BLOCK: 
int main()
{
    int i, j;
    char filename[] = "MARIO.bmp";
    int DATA = 0, OFFSET_VALUE, Bits_Pixel = 0, WIDTH, HEIGHT;
    long BMP_Format_Size = 0, BMP_Data_Offset = 0;
    int** Image;
    int temp = 0;

    // Reading the BMP File
    FILE* Inserted_Image;
    Inserted_Image = fopen(filename, "rb");

    if (Inserted_Image == NULL)
    {
       printf("Error Opening File!!");
       exit(1);
    }

    else
    {
        printf("Image is now processing plzz wait................loading.....loading.......\n");

       // Set file position of the stream to the beginning Contains file signature or ID "BM"
        OFFSET_VALUE = 0;
       // Set OFFSET_VALUE to 2, which contains size of BMP File
        OFFSET_VALUE = 2;

        fseek(Inserted_Image, OFFSET_VALUE, SEEK_SET);

       // Getting size of BMP File
        fread(&BMP_Format_Size, 4, 1, Inserted_Image);

       // Getting OFFSET_VALUE where the pixel array starts Since the information is at OFFSET_VALUE 10   //from the start, as given in BMP Header
        OFFSET_VALUE = 10;
        fseek(Inserted_Image, OFFSET_VALUE, SEEK_SET);

       // Bitmap data OFFSET_VALUE
        fread(&BMP_Data_Offset, 4, 1, Inserted_Image);

     // Getting HEIGHT and WIDTH of the Image WIDTH is stored at OFFSET_VALUE 18 and

       // HEIGHT at OFFSET_VALUE 22, each of 4 bytes
        fseek(Inserted_Image, 18, SEEK_SET);

        fread(&WIDTH, 4, 1, Inserted_Image);
        fread(&HEIGHT, 4, 1, Inserted_Image);

       // Number of bits per pixel
        fseek(Inserted_Image, 2, SEEK_CUR);

        fread(&Bits_Pixel, 2, 1, Inserted_Image);

       // Setting OFFSET_VALUE to start of pixel data
        fseek(Inserted_Image, BMP_Data_Offset, SEEK_SET);

       // Creating Image array
        Image = (int**)malloc(HEIGHT * sizeof(int*));
        for (i = 0; i< HEIGHT; i++)
        {
            Image[i] = (int*)malloc(WIDTH * sizeof(int));
        }


       // int Image[HEIGHT][WIDTH]

       // can also be done Number of bytes in the Image pixel array
        int numbytes = (BMP_Format_Size - BMP_Data_Offset) / 3;

       // Reading the BMP File into Image Array
        for (i = 0; i< HEIGHT; i++)
        {
           for (j = 0; j < WIDTH; j++)
           {
               fread(&temp, 3, 1, Inserted_Image);
               temp = temp & 0x0000FF;
               Image[i][j] = temp;
            }

        }

    }




    // Finding the probability of occurence
    int Histogram[256];
    for (i = 0; i< 256; i++)
        Histogram[i] = 0;

    for (i = 0; i< HEIGHT; i++)

        for (j = 0; j < WIDTH; j++)

            Histogram[Image[i][j]] += 1;



    // Finding number of non-zero occurences
    int nodes = 0;
    for (i = 0; i< 256; i++)
         if (Histogram[i] != 0)
             nodes += 1;


    // Calculating minimum probability
    float p = 1.0, ptemp;
    for (i = 0; i< 256; i++)
    {
       ptemp = (Histogram[i] / (float)(HEIGHT * WIDTH));
       if (ptemp> 0 &&ptemp<= p)
           p = ptemp;
    }



    // Calculating max length of code word
    i = 0;
    while ((1 / p) > fib(i))
         i++;
    int maxCode_length = i - 3;


    // Defining Structures Pixel_Frequency
    struct Pixel_Frequency
    {
        int Pixel, Left_array_Location, Right_array_Location;
        float freq;
        struct Pixel_Frequency *left, *right;
        char code[maxCode_length];
    };



    // Defining Structures huffcode
    struct huffcode
    {
        int Pixel, Array_Location;
        float freq;
    };



    // Declaring structs
    struct Pixel_Frequency* Pixel_freq;
    struct huffcode* huffcodes;
    int totalnodes = 2 * nodes - 1;

    Pixel_freq = (struct Pixel_Frequency*)malloc(sizeof(struct Pixel_Frequency) * totalnodes);

    huffcodes = (struct huffcode*)malloc(sizeof(struct huffcode) * nodes);



    // Initializing
    j = 0;
    int Total_Pixel = HEIGHT * WIDTH;
    float tempprob;
    for (i = 0; i< 256; i++)
    {
       if (Histogram[i] != 0)
       {
           // pixel intensity value
           huffcodes[j].Pixel = i;
           Pixel_freq[j].Pixel = i;


           // location of the node in the Pixel_freq array
           huffcodes[j].Array_Location = j;

          // probability of occurrence
           tempprob = (float)Histogram[i] / (float)Total_Pixel;
           Pixel_freq[j].freq = tempprob;
           huffcodes[j].freq = tempprob;

          // Declaring the child of leaf node as NULL pointer
           Pixel_freq[j].left = NULL;
           Pixel_freq[j].right = NULL;

          // initializing the code word as end of line
           Pixel_freq[j].code[0] = '\0';
            j++;
            }
            }



    // Sorting the Histogram
     struct huffcode temphuff;
     

    // Sorting w.r.t probability of occurence

    for (i = 0; i< nodes; i++)

    {
        for (j = i + 1; j < nodes; j++)
        {
           if (huffcodes[i].freq<huffcodes[j].freq)
              {
                temphuff = huffcodes[i];

                huffcodes[i] = huffcodes[j];

                huffcodes[j] = temphuff;

            }

        }

    }



    // Building Huffman Tree

    float sumprob;
    int sumPixel;
    int n = 0, k = 0;
    int nextnode = nodes;

    // Since total number of nodes in Huffman Tree is 2*nodes-1
    while (n < nodes - 1)
    {
        // Adding the lowest two probabilities
        sumprob = huffcodes[nodes - n - 1].freq + huffcodes[nodes - n - 2].freq;
        
        sumPixel = huffcodes[nodes - n - 1].Pixel + huffcodes[nodes - n - 2].Pixel;

        // Appending to the Pixel_freq Array
        Pixel_freq[nextnode].Pixel = sumPixel;

        Pixel_freq[nextnode].freq = sumprob;

        Pixel_freq[nextnode].left = &Pixel_freq[huffcodes[nodes - n - 2].Array_Location];

        Pixel_freq[nextnode].right = &Pixel_freq[huffcodes[nodes - n - 1].Array_Location];

        Pixel_freq[nextnode].code[0] = '\0';

        i = 0;
        // Sorting and Updating the huffcodes array simultaneously New position of the combined node
        while (sumprob<= huffcodes[i].freq)
            i++;

        // Inserting the new node in the huffcodes array
        for (k = nodes; k >= 0; k--)
        {
            if (k == i)
            {
                huffcodes[k].Pixel = sumPixel;

                huffcodes[k].freq = sumprob;

                huffcodes[k].Array_Location = nextnode;
            }

            else if (k >i)
            
                    // Shifting the nodes below the new node by 1
                    //For inserting the new node at the updated position k
                    huffcodes[k] = huffcodes[k - 1];

        }

        n += 1;
        nextnode += 1;

    }


    // Assigning Code through backtracking
    char left = '0';
    char right = '1';
    int index;

    for (i = totalnodes - 1; i>= nodes; i--)
    {
        if (Pixel_freq[i].left != NULL)
            Str_concat(Pixel_freq[i].left->code, Pixel_freq[i].code, left);

        if (Pixel_freq[i].right != NULL)
            Str_concat(Pixel_freq[i].right->code, Pixel_freq[i].code, right);
    }


    // Printing Huffman Codes
    printf("Huffmann Codes::\n\n");

    printf("pixel values -> Code\n\n");

    for (i = 0; i< nodes; i++) 
    {
        if (snprintf(NULL, 0, "%d", Pixel_freq[i].Pixel) == 2)
            printf("     %d     -> %s\n", Pixel_freq[i].Pixel, Pixel_freq[i].code);

        else
            printf(" %d     -> %s\n", Pixel_freq[i].Pixel, Pixel_freq[i].code);
    }


    // Encode the Image
    printf("\n\n The Encoded  Image with pixel intensity is :\n\n");

    FILE* textfile;

    textfile=fopen("encoded_Image.txt","wb");

    int Pixel_val;
    int l;
    
    //char encode[]="";
    for (i = 0; i< HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            Pixel_val = Image[i][j];
            for (l = 0; l < nodes; l++)

                if (Pixel_val == Pixel_freq[l].Pixel)

                {
                    printf("%s ", Pixel_freq[l].code);

                    fprintf(textfile,"%s ", Pixel_freq[l].code);
                    //strcat(encode,Pixel_freq[l].code);
                }

        }

        printf("\n");

        fprintf(textfile,"\n");

    }

    fclose(textfile);
    //printf("\n\n%s",encode);
}

// 60% CREDITS TO GEEKFORGEEKS
// DONE BY VIDIT GOEL

