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

## Data structures and allowed operations

Array:

- create
- search
- add
- delete
- put

Stack: 
- create
- search
- push
- pop
- put

Queue:
- create
- search
- enqueue
- dequeue
  
List:
- create
- search
- add
- delete

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
<structure>,<operation> ,<range start value (min. 1)>, <range stop value>, <step value>, <number of repeat>
```

Example config.ini
```
data.csv 1000000
results.csv
array create 1 1000 2 10 
stack push 5 200 5 1
list search 1 100000 100 20
queue enqueue 10 10000 10 1
```
Run the program and read the current information.

Then you are able to load results and analyze them (e.g. in Excel).

---
## Results
After taking the measurements, the program saves the results in the following format

```
<data_structure>,<operation>,<size_of_structure>,<time_of_operation_s>,<averages_denominator>
```

