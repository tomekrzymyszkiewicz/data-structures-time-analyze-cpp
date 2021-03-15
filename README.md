# Data structures time analyze C++
Program that checks the time of operations on data structures such as:

- array
- list
- stack
- queue

---

## Using a program

Set properties in configuration file:

- choose file with example data and amount of data
- choose file when the results will be saved
- enter a series of task to test by the program
---

## config.ini syntax

```
<data_source (*.csv)> <amount of data>
<results_destination (*.csv)>
<task>
<task>
.
.
.
```
Task syntax
```
<structure>, <range start value (min. 1)>, <range stop value>, <step value>, <number of repeat>
```

Example config.ini
```
data.csv 1000000
results.csv
array 1 1000 2 10 
stack 5 200 5 1
list 1 100000 100 20
queue 10 10000 10 1
```
Run the program and read the current information.

Then you are able to load results and analyze them (e.g. in Excel).
