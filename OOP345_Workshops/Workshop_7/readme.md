# Workshop 7: STL Algorithms

In this workshop, you use the Algorithm category of the Standard Template Library.

Your assignment is to create an application that manages a collection of cities from around the world and the number of COVID cases/deaths from each city in a given year.



## Learning Outcomes

Upon successful completion of this workshop, you will have demonstrated the abilities to:

- copy data from a file into a sequential container
- use the numeric library to accumulate data values
- use a lambda expression to specify an operation on each value in a data set
- use the algorithm library to sort data values




## Submission Policy

The workshop is divided into two coding parts and one non-coding part:

- *Part 1*: worth 0% of the workshop's total mark, is optional and designed to assist you in completing the second part.
- *Part 2*: worth 100% of the workshop's total mark, is due on **Sunday at 23:59:59** of the week of your scheduled lab.  Submissions of *Part 2* that do not contain the *reflection* are not considered valid submissions and are ignored.
- *reflection*: non-coding part, to be submitted together with *Part 2*. The reflection does not have marks associated to it but can incur a **penalty of max 40% of the whole workshop's mark** if your professor deems it insufficient (you make your marks from the code, but you can lose some on the reflection).

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
- `w7` (supplied)
- `CovidCollection`

Enclose all your source code within the `sdds` namespace and include the necessary guards in each header file.

In the specs below, functions marked with `DO NOT USE MANUAL LOOPS` should not use `for` or `while` in the implementation; these functions should use STL Algorithms.  The STL Algorithms you choose should use lambda expressions to process the collection; the lambdas should **capture the necessary variables from context only by value** (the stream object is the only one allowed to be captured by reference). Check course notes to identify which algorithm is appropriate in each situation.  Using manual loops will lead to **rejection** of the workshop or **severe penalties** (at the discretion of your professor).





### `CovidCollection` Module

This module defines a simple structure called `Covid`, capable of storing the following information about a covid details for a particular city:
- country (as a string)
- city (as a string)
- variant (as a string)
- year (as an integer)
- number of cases (as an unsigned integer)
- number of deaths (as an unsigned integer)

No need to add any member functions to this structure. Choose appropriate types for each attribute.


Also, define a class called `CovidCollection` that manages a collection of objects of type `Covid`. Choose an appropriate STL container to store the collection.

***Public Members for `CovidCollection`***

- a custom constructor that receives as a parameter the name of the file containing the information about the covid details of various cities to be added to the collection. This function should load into the attributes all the covid details in the file.

  If the filename is incorrect, this constructor should raise an exception.

  Each line from the file contains covid information about a single city in the following format:
  ```
  COUNTRY CITY VARIANT YEAR CASES DEATHS
  ```
  The fields are not separated by delimiters; each field has a fixed size: `COUNTRY`, `CITY` and `VARIANT` have **exactly** 25 characters; while `YEAR`, `CASES` and `DEATHS` have **exactly** 5 characters.


  Any blank space at the beginning/end of a token is not part of the token and should be removed.

- `void CovidCollection::display(std::ostream& out) const`: print the content of the collection into the parameter (one city details / line). Use the insertion operator (see below). ***DO NOT USE MANUAL LOOPS!***



***Free Helpers***

- `std::ostream& operator<<(std::ostream& out, const Covid& theCovid)`: inserts one `Covid` object into the first parameter, using the following format (the width of each field is specified in brackets):
  ```
  | COUNTRY(21) | CITY(15) | VARIANT(20) | YEAR(6) | CASES(4) | DEATHS(3) |
  ```

  Look in the sample output to see how the numbers should be formatted and the alignment of each field.


**Add any other private member that is required by your design!**







### `w7` Module (supplied)


The tester module for the first portion of the workshop has been supplied. **Do not modify the existing code!**

When doing the workshop, you are encouraged to write your own tests, focusing on a single implemented feature at the time, until you get all functionality in place.



### Sample Output

When the program is started with the command (the file `covids.txt` is provided):
```
ws covids.txt
```
the output should look like the one from the `sample_output.txt` file.




### Test Your Code

To test the execution of your program, use the same data as shown in the output example above.

Upload your source code to your `matrix` account. Compile and run your code using the latest version of the `g++` compiler (available at `/usr/local/gcc/10.2.0/bin/g++`) and make sure that everything works properly.

Then, run the following command from your account (replace `profname.proflastname` with your professor’s Seneca userid):
```
~profname.proflastname/submit 345_w7_p1
```
and follow the instructions.

***This part represents a milestone in completing the workshop and is not marked!***










## Part 2 (100%)

The second part of this workshop upgrades your solution to include more functionality in the `CovidCollection` module.

**:warning:Important:** An algorithm used for one task should not be used to accomplish a second task. Using an algorithm for more than one task will lead to **rejection** of the workshop or **severe penalties** (at the discretion of your professor).



### `CovidCollection` Module

Update the `Covid` structure to include a field representing severity status of the infection in a city (as a string); this field should be initialized to `General`. When printed, this field should use 8 characters.

Update the custom type `CovidCollection` as described below.


***Public Members for `CovidCollection`***

- `void display(std::ostream& out, const std::string& country) const`
  - This function represents **Task #1** -- ***DO NOT USE MANUAL LOOPS!***
  - Update this function's prototype to receive a second parameter `country`. This parameter should have the default value `ALL` if the client doesn't provide it (don't overload the function).
  - Implement the function to print only the information about the country specified in the second parameter. If the parameter has the value `ALL`, then print information for all countries.
  - This function should also calculate the percentage of cases/deaths in the specified country from the world total. If the second parameter is `ALL`, then this function should print the number of cases/deaths in the world. See the sample output for the format.

- `void sort(const std::string& field)`:
  - This function represents **Task #2** -- ***DO NOT USE MANUAL LOOPS!***
  - Sort the collection of `Covid` objects in ascending order based on the field received as parameter.
  - The parameter should have a default value of `country` (do not overload this function).
  - If two `Covid` objects have the same value for the specified field, then the object with lower deaths is considered smaller.

- `bool inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const`
  - This function represents **Task #3** -- ***DO NOT USE MANUAL LOOPS!***
  - Search in the collection for a city in the specified country where the variant from the first parameter has caused more deaths than the last parameter. Return `true` if such an object exists, `false` otherwise.

- `std::list<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const`:
  - This function represents **Task #4** -- ***DO NOT USE MANUAL LOOPS!***
  - Create and return a collection of `Covid` objects from the current instance where the number of deaths is at least as the value specified as parameter.

- `void CovidCollection::updateStatus()`:
  - This function represents **Task #5** -- ***DO NOT USE MANUAL LOOPS!***
  - updates the status of each city.  If the number of deaths is greater than 300, the status should be `EPIDEMIC`, if it is less than 50, it should be `EARLY`; for anything else, the status should be `MILD`.








### `w7` Module


The tester module has been supplied. **Do not modify the existing code!**

When doing the workshop, you are encouraged to write your own tests, focusing on a single implemented feature at the time, until you get all functionality in place.



### Sample Output

When the program is started with the command (the input file is provided):
```
ws covids.txt
```
the output should look like the one from the `sample_output.txt` file.




### Reflection

Study your final solution, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this workshop. **This should take no less than 30 minutes of your time and the result is suggested to be at least 150 words in length.**


Create a **text** file named `reflect.txt` that contains your detailed description of the topics that you have learned in completing this particular workshop and mention any issues that caused you difficulty and how you solved them. Include in your explanation—**but do not limit it to**—the following points:
- list all the STL functions that you have used in this workshop; explain your reasoning for choosing each one, and not another.
- present the advantages of using STL algorithms vs. implementing the functionality by yourself using loops.
- the function that sorts the collection of objects receives as a parameter the field name to use; this can create errors if the client specifies an invalid field (or misspells it). How would you redesign that function to prevent the client from specifying an invalid string, allowing any error to be detected by the compiler?

To avoid deductions, refer to code in your solution as examples to support your explanations.





### Submission

To test and demonstrate execution of your program use the same data as shown in the output example above.

Upload the source code and the reflection file to your `matrix` account. Compile and run your code using the latest version of the `g++` compiler (available at `/usr/local/gcc/10.2.0/bin/g++`) and make sure that everything works properly.

Then, run the following command from your account (replace `profname.proflastname` with your professor’s Seneca userid):
```
~profname.proflastname/submit 345_w7_p2
```
and follow the instructions.

**:warning:Important:** Please note that a successful submission does not guarantee full credit for this workshop. If the professor is not satisfied with your implementation, your professor may ask you to resubmit. Resubmissions will attract a penalty.
