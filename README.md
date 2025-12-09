[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=21680965)
# ELEC2645 Unit 2 Project Engineering Caclulator

This is my engineering calculator.

From this program, the first function will take a list of number separated by spaces and return key statistical info, like count, mean, median, standard deviation and variance.

The second function will take a list of numbers and return a fast fourier transform in a separate csv file, which you can plot in any plotting software of your choice. It also returns peak-to-peak and RMS.

The third function will give you the option to select a wave type, amplitude and frequency and return a plot to a csv, which you can also plot to any external software you like.

Note, locate the CSV in the file explorer if your using an online IDE and download the CSV files. If you download the zip of the program and run the program from your device, the file will already on your PC to access.



### 1 Run code

You can build the code as we have been using in the labs with 
`gcc main.c funcs.c kissfft/kiss_fft.c -I kissfft -o main.out -lm` (the `-lm` is required to link the math library). You can also use `make -B` to force a rebuild using the provided `Makefile`.

Then run the code with `./main.out`


### 2 The assignment

Please read the assignment brief on the Minerva page for details of what you need to implement. 



### 3 Test command

The `test.sh` script is provided to check that your code compiles correctly. This is what the autograder will use to check your submission. You can run it with `bash test.sh` or `./test.sh` or just `make test`. 

You do not need to modify this script, but you can look at it to see what it does.


### 4 Submit Solution

Use the same method as previous labs to commit and push your code to your GitHub repository for the autograder to check. 

In your final journal post, please include a link to your GitHub repository containing your code  *and* a zip file of your code as an attachment.
