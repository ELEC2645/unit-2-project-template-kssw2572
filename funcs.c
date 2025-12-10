#include <stdio.h>
#include "funcs.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include<math.h>
#include "kiss_fft.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void menu_item_1(void) {
    printf("\n>> Statistics Calculator\n");   //prints header
    
    char buffer[1024];            //defines initial variables
    double numbers[128];
    int count=0;
    
    printf("Enter a list of numbers separated by spaces:\n");

    if(!fgets(buffer, sizeof(buffer), stdin))   //Reads input line, and returns error if nothing entered
    {                           
        printf("Input Error");
        return;
    }
    buffer[strcspn(buffer,"\r\n")] = '\0';  //removes newline character to clean the input

    char *token = strtok(buffer, " ");       //reads the tokens by where there are spaces.
    while(token && count<128){             //loops through each token, up to 128 and stores numbers in array
        char *endptr;
        errno=0;
        double val = strtod(token,&endptr);

        if(errno == ERANGE || endptr==token|| (*endptr && *endptr  != '\0')){     //checks for invalid data and skips over it
            printf("Skipping over invalid input: %s\n", token);
        }
        else{
            numbers[count++] = val;      //increments count each cycle
        }
        token=strtok(NULL, " ");            


    }
    if(count==0){
        printf("No numbers entered\n");    //if no numbers entered, returns error
    }

    double sum=0.0;
    for(int i=0; i<count;i++){        //adds all numbers and divides by count
        sum+=numbers[i];
    }
    double mean=sum/count;

    for(int i=0;i<count;i++){
        for(int j=i+1; j<count;j++){
            if(numbers[j]<numbers[i]){                  //bubble sort to order the numbers
                double temp = numbers[i];
                numbers[i]=numbers[j];
                numbers[j]=temp;
            }
        }
    }
    double median=0;            //returns median based on even or odd count
    if (count%2==0){
        median = (numbers[count/2-1]+numbers[count/2]) / 2.0;

    }
    else{
        median=numbers[count/2];
    }
    double sum2=0.0;          // squares the sum of all numbers minus the mean
    for(int i=0;i<count;i++){
        double diff = numbers[i]- mean;
        sum2 += diff*diff;
    }
    double variance = sum2/count;         //calculates variance and std by rooting variance
    double stdev = sqrt(variance);

    printf("Count: %d\n", count);        //prints all results
    printf("Mean: %.4f\n", mean);
    printf("Median: %.4f\n", median);
    printf("Variance: %.4f\n", variance);
    printf("Standard Deviation: %.4f\n", stdev);



    
}











void menu_item_2(void) {
    //prints header nad prompts for input
    printf("\n>> Waveform Analyser\n");
    printf("Enter waveform samples separated by spaces:\n");
    
    //initialises variables
    char buffer[10048];
    double samples[2048];
    int count=0;

    //takes input and checks for errors
    if(!fgets(buffer, sizeof(buffer), stdin))
    {
        printf("Input Error");
        return;
    }
    buffer[strcspn(buffer,"\r\n")] = '\0';

    //loops through each token and separates them by space storing them in array
    char *token = strtok(buffer, " ");
    while(token && count<2048){
        char *endptr;
        errno=0;
        double val = strtod(token,&endptr);    
    //validates input
    if(errno == ERANGE || endptr==token|| (*endptr && *endptr  != '\0')){
            printf("Skipping over invalid input: %s\n", token);
        }
        else{
            samples[count++] = (double)val;
        }
        token=strtok(NULL, " ");
    }
    if(count==0){
        printf("No samples entered\n");
        return;
    }

    //calculates RMS
    double sumsquared=0.0;
    for (int i=0;i<count;i++){
        sumsquared += samples[i]*samples[i];
    }
    double rms = sqrt(sumsquared/count);

    //calculates p2p
    double min = samples[0];
    double max = samples[0];
    for(int i=1;i<count;i++){
        if(samples[i]<min){
            min=samples[i];
        }
        if(samples[i]>max){
            max=samples[i];
        }
    }

    double peaktopeak = max - min;

    //outputs the values
    printf("Count: %d\n", count);
    printf("RMS: %.4f\n", rms);
    printf("Peak-to-Peak: %.4f\n", peaktopeak);

    int fftnumber=count;

    //Defines input and output, allocates memory
    kiss_fft_cpx *in = malloc( sizeof(kiss_fft_cpx) * fftnumber );
    kiss_fft_cpx *out = malloc( sizeof(kiss_fft_cpx) * fftnumber);

    kiss_fft_cfg cfg = kiss_fft_alloc(fftnumber, 0, NULL, NULL);

    //creates array for FFT
    for(int i=0;i<fftnumber;i++){
        in[i].r = samples[i];
        in[i].i = 0.0;
    }
    
    //performs FFT
    kiss_fft(cfg, in, out);


    //writes all the output to CSV, and adds title, loops through all values
    FILE *fp = fopen("fft_output.csv", "w");
    if(!fp){
        printf("Error opening file for FFT output\n");
        free(in);
        free(out);
        free(cfg);
        return;
    }
    
    fprintf(fp, "Index,Magnitude\n");

    for(int i=0; i<fftnumber; i++){
        double real=out[i].r;
        double imaginary = out[i].i;
        double magnitude = sqrt(real*real + imaginary*imaginary);

        fprintf (fp, "%d,%f\n", i, magnitude);

    }

    fclose(fp);

    printf("FFT output written to fft_output.csv\n");

    free(in);
    free(out);
    free(cfg);


    

    
}

void menu_item_3(void) {
    printf("\n>> Waveform Generator\n");
    
    //initialises variable
    int wavetype=0;
    double frequency=0.0;
    double amplitude=0.0;
    

    char buffer[256];

    //ask for waveform type
    printf("Select waveform type:\n");
    printf("1. Sine Wave\n");
    printf("2. Square Wave\n");
    printf("3. Triangle Wave\n");
    printf("4. Sawtooth Wave\n");

    while(1){
        printf("Enter choice (1-4): ");
        if(!fgets(buffer, sizeof(buffer), stdin)){
            printf("Input Error\n");
            return;
        }
        
        buffer[strcspn(buffer,"\r\n")] = '\0';

        char *endptr;
        wavetype = (int)strtol(buffer, &endptr, 10);

        if(endptr==buffer || *endptr != '\0' || wavetype<1 || wavetype>4){
            printf("Invalid selection\n");
        }
        else{
            break;
        }
    }
    //ask for frequency
    while(1){
        printf("Enter frequency in Hz: ");
        if(!fgets(buffer, sizeof(buffer), stdin)){
            printf("Input Error\n");
            return;
            }
        buffer[strcspn(buffer,"\r\n")] = '\0';

        char *endptr;
        frequency = strtod(buffer, &endptr);

        if(endptr==buffer || *endptr != '\0' || frequency<=0){
            printf("Invalid frequency\n");
            }
        else{
            break;
            }
        }

        //ask for amplitude
    while(1){
        printf("Enter amplitude: ");
        if(!fgets(buffer, sizeof(buffer), stdin)){
            printf("Input Error\n");
            return;
        }
        buffer[strcspn(buffer,"\r\n")] = '\0';

        char *endptr;
        amplitude = strtod(buffer, &endptr);

        if(endptr==buffer || *endptr != '\0' || amplitude<=0){
            printf("Invalid amplitude\n");
        }
        else{
            break;
            }
        }

        //generate waveform samples
        const int samplerate = 100000;
        const double duration = 5.0;
        long totalsamples=(long)(samplerate * duration);

        double *samples = malloc (sizeof(double) * totalsamples);
        if(!samples){
            printf("Memory allocation error\n");
            return;
            }

        for(long i=0;i<totalsamples;i++){
            double t = (double)i / samplerate;
            double value=0.0;

            switch(wavetype){
                case 1: 
                    value = amplitude * sin(2.0 * M_PI * frequency * t);
                    break;
                case 2: 
                    value = (sin(2.0 * M_PI * frequency * t) >= 0) ? amplitude : -amplitude;
                    break;
                case 3: 
                    value= (2.0 * amplitude / M_PI) * asin(sin(2.0 * M_PI * frequency * t));       
                    break;
                case 4: 
                    value = (2.0 * amplitude / M_PI) * atan(tan(M_PI * frequency * t));                
                    break;
            
                  
            }
            samples[i]=value;
        }

        //write samples to CSV
        FILE *fp = fopen("waveform.csv", "w");

        if(!fp){
            printf("Error opening file for waveform output\n");
            free(samples);
            return;
        }

        fprintf (fp, "Time,Value\n");

        for(long i=0;i<totalsamples;i++){
            double t = (double)i / samplerate;
            fprintf(fp, "%f,%f\n", t, samples[i]);
        }

        fclose(fp);
        free(samples);

        printf("Waveform samples written to waveform.csv\n");
    }


