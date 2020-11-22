<H1 align="center"> METHODOLOGY </H1>

The methodology involved in the project consists of file handling in C language, in order to import a image. A function in C is created in order to find the symbols (i.e. pixel value which is not repeated) in continuation a function is created to find the probability of each symbol. With the use of Huffman algorithm, a special code will be formulated for each pixel value. Now the image is the form of bit structure (i.e. consisting of a series of 0 and 1). Further this compressed image will be sent send using TCP/IP protocols by means of socket programming will be transferred to another station where it can be decrypted.

STEP1: Start the program 
STEP2: Read the Image into a 2D array(image)
STEP3:Create a Histogram of the pixel intensity values present in the Image
STEP4: Find the number of pixel intensity values having non-zero probability of occurrence
STEP5: Calculating the maximum length of Huffman code words
STEP6: Define a struct which will contain the pixel intensity values(pix)
STEP7: Define another Struct which will contain the pixel intensity values(pix), their corresponding probabilities(freq) and an additional field, which will be used for storing the position of new generated nodes(arrloc).
STEP8:Declaring an array of structs. Each element of the array corresponds to a node in the Huffman Tree.
STEP9: Initialize the two arrays pix_freq and huffcodes with information of the leaf nodes.
STEP10: Sorting the huffcodes array according to the probability of occurrence of the pixel intensity values
STEP11: Building the Huffman Tree
STEP12: Encode the Image
STEP13: Stop the program. 

## FLOWCHART:
![FlowChart](https://1.bp.blogspot.com/-jGKQrIf3pF0/X7qdJaoPwQI/AAAAAAAAAIk/xn5H2eA5IekGgg98FK9dd_XCeh9T_MZpgCLcBGAsYHQ/s583/Screenshot%2B%2528369%2529.png)
