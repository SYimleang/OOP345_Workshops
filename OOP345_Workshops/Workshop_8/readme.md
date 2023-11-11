# Workshop 8: Smart Pointers

In this workshop, you will exclude one collection from another and use smart pointers to ensure that memory is deallocated in the possible presence of an exception.



## Learning Outcomes

Upon successful completion of this workshop, you will have demonstrated the abilities to:

- create a program component of quadratic complexity
- use a smart pointer to move an object




## Submission Policy

The workshop is divided into two coding parts and one non-coding part:

- *Part 1*: worth 0% of the workshop's total mark, is optional and designed to assist you in completing the second part.
- *Part 2*: worth 100% of the workshop's total mark, is due on **Sunday at 23:59:59** of the week of your scheduled lab.  Submissions of *Part 2* that do not contain the *reflection* are not considered valid submissions and are ignored.
- *reflection*: non-coding part, to be submitted together with *Part 2*. The reflection does not have marks associated to it, but can incur a **penalty of max 40% of the whole workshop's mark** if your professor deems it insufficient (you make your marks from the code, but you can lose some on the reflection).

The workshop should contain ***only work done by you this term*** or provided by your professor.  Work done in another term (by you or somebody else), or work done by somebody else and not **clearly identified/cited** is considered plagiarism, in violation of the Academic Integrity Policy.

Every file that you submit must contain (as a comment) at the top **your name**, **your Seneca email**, **Seneca Student ID** and the **date** when you completed the work.

- If the file contains only your work, or work provided to you by your professor, add the following message as a comment at the top of the file:

    > I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

- If the file contains work that is not yours (you found it online or somebody provided it to you), **write exactly which parts of the assignment are given to you as help, who gave it to you, or which source you received it from.**  By doing this you will only lose the mark for the parts you got help for, and the person helping you will be clear of any wrong doing.



## Compiling and Testing Your Program

All your code should be compiled using this command on `matrix`:

```bash
/usr/local/gcc/10.2.0/bin/g++ -Wall -std=c++17 -g -o ws file1.cpp file2.cpp ...
```

- `-Wall`: compiler will report all warnings
- `-std=c++17`: the code will be compiled using the C++17 standard
- `-g`: the executable file will contain debugging symbols, allowing *valgrind* to create better reports
- `-o ws`: the compiled application will be named `ws`

After compiling and testing your code, run your program as following to check for possible memory leaks (assuming your executable name is `ws`):

```bash
valgrind --show-error-list=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ws
```

- `--show-error-list=yes`: show the list of detected errors
- `--leak-check=full`: check for all types of memory problems
- `--show-leak-kinds=all`: show all types of memory leaks identified (enabled by the previous flag)
- `--track-origins=yes`: tracks the origin of uninitialized values (`g++` must use `-g` flag for compilation, so the information displayed here is meaningful).

To check the output, use a program that can compare text files.  Search online for such a program for your platform, or use *diff* available on `matrix`.




## Part 1 (0%)

The first portion of this workshop consists of modules:
- `w8` (supplied)
- `Profile` (incomplete)
- `DataBase` (incomplete)
- `Utilities` (supplied header, incomplete implementation)

Your tasks for this part of the workshop are:
- Add a `validateAddress()` function to the `Profile` module
- Add an operator `+=` overload to the `DataBase` module using raw pointer syntax
- Complete the `excludeRaw()` function in the `Utilities` module using raw pointer syntax

See the `ToDo` comments in the files for more implementation details.



### `Profile` Module

The `Profile` module holds name, address, and age information about a person.
- The `Name` structure holds first name and last name of the profile.
- The `Address` structure holds street number, street name and postal code information.  
- The `Age`  holds the age of the person.


**Your Task:** Add a `validateAddress()` function to the `Profile` type. Your function reports an exception if the address’s number is negative or postal code does not follow [ANA NAN](https://en.wikipedia.org/wiki/Postal_codes_in_Canada) format. Your function receives no parameters.



### `DataBase` Module

The `DataBase` module defines a class that retrieves a collection of records about people stored in a text file, creates and stores the profile of each person found in the file in an STL vector, provides indexed access to the stored profiles, and displays the information to an output stream.

**Your Task:** Add an operator `+=` overload to the `DataBase` template. Your function receives as parameter **the address** of an object of template type `T` and copies the object into the collection attribute.


### `Utilities` Module

**Your Task:** Implement the `excludeRaw()` function. This function compares the profiles in the two received `DataBase` objects. Two profiles are considered same if they have same age and name.

For each profile from the first parameter that is not banned, your function allocates dynamic memory of `Profile` type and copies the profile. Your function then validates the `Profile` object (using `validateAddress()` you created above) and adds it to `result`. Your function returns a copy of `result`.






### `w8` Module (supplied)


The tester module has been supplied. **Do not modify the existing code!**

When doing the workshop, you are encouraged to write your own tests, focusing on a single implemented feature at the time, until you get all functionality in place.



### Sample Output


When the program is started with the command (the input files are provided):
```
ws AllProfiles.txt BadProfiles.txt GoodProfiles.txt
```
the output should look like the one from the `sample_output.txt` file.




### Test Your Code

To test the execution of your program, use the same data as shown in the output example above.

Upload your source code to your `matrix` account. Compile and run your code using the latest version of the `g++` compiler (available at `/usr/local/gcc/10.2.0/bin/g++`) and make sure that everything works properly.

Then, run the following command from your account (replace `profname.proflastname` with your professor’s Seneca userid):
```
~profname.proflastname/submit 345_w8_p1
```
and follow the instructions.

***This part represents a milestone in completing the workshop and is not marked!***










## Part 2 (100%)

The second part of this workshop upgrades your solution to use smart pointers.

Your tasks for this part of the workshop are:
- Add an operator `+=` overload to the `DataBase` module using smart pointer syntax
- Complete the `excludeSmart()` function in the `Utilities` module using smart pointer syntax

These functions should accomplish the same result as the equivalent functions you created in part 1, but this time using smart pointers instead of raw pointers.



### `w8` Module (supplied)


The tester module has been supplied. **Do not modify the existing code!**

When doing the workshop, you are encouraged to write your own tests, focusing on a single implemented feature at the time, until you get all functionality in place.



### Sample Output


When the program is started with the command (the input files are provided):
```
ws AllProfiles.txt BadProfiles.txt GoodProfiles.txt
```
the output should look like the one from the `sample_output.txt` file.




### Reflection

Study your final solution, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this workshop. **This should take no less than 30 minutes of your time and the result is suggested to be at least 150 words in length.**

Create a **text** file named `reflect.txt` that contains your detailed description of the topics that you have learned in completing this particular workshop and mention any issues that caused you difficulty and how you solved them. Include in your explanation—**but do not limit it to**—the following points:
- the advantage that smart pointer syntax provides. Use example from your code to support your explanation.
- the difference between raw and smart pointer syntax in your solution.
- look at the output when the profiles are excluded using raw/smart pointers: the objects are duplicated a lot of times (e.g., the object with ID `176` is duplicated into object `177`; then object `177` is duplicated into object `180` and `177` gets deleted; object `180` is duplicated into `183` and then is deleted, etc.).  **Explain why so many copies are created!**
  - **Hint** Put a breakpoint into function(s) `exclude...` and follow the execution of your code line by line. Check when the messages come into the output, and what operations trigger making so many copies.
  - How would you redesign the application to reduce the number of copies that are made?
- The class `Profile` doesn't provide an explicit move constructor.  What happens if in the `DataBase` you add objects into the collection attribute using `std:move()`? Do an experiment and report your findings.

To avoid deductions, refer to code in your solution as examples to support your explanations.





### Submission

To test and demonstrate execution of your program use the same data as shown in the output example above.

Upload the source code and the reflection file to your `matrix` account. Compile and run your code using the latest version of the `g++` compiler (available at `/usr/local/gcc/10.2.0/bin/g++`) and make sure that everything works properly.

Then, run the following command from your account (replace `profname.proflastname` with your professor’s Seneca userid):
```
~profname.proflastname/submit 345_w8_p2
```
and follow the instructions.

**:warning:Important:** Please note that a successful submission does not guarantee full credit for this workshop. If the professor is not satisfied with your implementation, your professor may ask you to resubmit. Resubmissions will attract a penalty.
