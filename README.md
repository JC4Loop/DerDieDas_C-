# DerDieDas - Nominative - Accusative - Dative

A command line / terminal application displaying german sentences with the appropriate (the) article for each noun; english translation is displayed below each german sentence.
Both main files show articles for definite nouns then indefinite nouns.

Two separate main files, both using the same header and dddLibrary.cpp file.

Program makes use of arrays, pointers and inheritance, each noun and verb is selected randomly.

Respository also includes compiled executable files for linux.

Bug note - Whilst the nominative noun should not be the same as the accusative or dative noun, the nominative nouns of the next sentences should not be repeated, also the case for the dative nouns.
However there are cases with both accusative and dative applications, where the nouns are repeated. It requires a more sufficient way of the randomness working the way I want.

#### accusMain
Each displayed sentence includes nominative noun, verb then accusative noun.

![screenshot](/screenshots/accusativeSC1.png)

#### dativeMain
Displayed sentences include nominative noun, verb then dative noun.

![screenshot](/screenshots/dativeSC1.png)

##### DDDClasses.h
A header file containing classes, object and class methods.
Two forward references to functions within the dddLibrary file which will be called by the main programs.

##### dddLibrary.cpp
File contains functions for retrieving a random number, copying array and adding spaces to a string for neat display.
Most important functions are the PrepareOutputLines and OutputPairLine.

PrepareOutputLines receives the arrays, its size and boolean values for nouns to be definite and dative.
A loop is run for each item in nouns array.
Random numbers are retrieved to select which subject noun, verb and object noun.
OutputPairLine is called with the appropriate arguments that will ouput a sentence.
removeArray is then called to move the selected element in the array to the last element; after having shifted all other elements left.
The max integer is decreased by one so that the next loop will not select the same noun or verb.

OutputPairLine takes pointers of pointers to know which element of the array to use.
Depending on the values of the definite and dative booleans, the correct articles are retrieved for each noun.
getPadString is used for nouns and verbs to keep them aligned with the senteces above and / or below.
