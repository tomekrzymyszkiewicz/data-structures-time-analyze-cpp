#include<stdio.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<random>
#include<vector>
#include<filesystem>
#include<windows.h>
#include<ctime>
#include<ratio>
#include<conio.h>
#include<chrono>
#include<cstring>
#include<algorithm>
using namespace std;
vector<int> data_vector;
vector<vector<string>> tasks;
vector<string> results;
string data_file_name = "";
int data_amount = 0;
string results_file_name = "";

struct Result{
    string data_structure;
    string operation;
    int size_of_structure;
    double time_span;
    int averages_denominator;
    Result(string data_structure, string operation, int size_of_structure, double time_span, int averages_denominator){
        this->data_structure = data_structure;
        this->operation = operation;
        this->size_of_structure = size_of_structure;
        this->time_span = time_span;
        this->averages_denominator = averages_denominator;
    }
    Result(string data_structure, string operation, int size_of_structure, double time_span){
        this->data_structure = data_structure;
        this->operation = operation;
        this->size_of_structure = size_of_structure;
        this->time_span = time_span;
        this->averages_denominator = 1;
    }
    string toString(){
        return(data_structure+","+operation+","+to_string(size_of_structure)+","+to_string(time_span)+","+to_string(averages_denominator));
    }

};

class List
{
private: 
	typedef struct Node
	{
		int data;
		Node *nextNode;
	} * node_ptr;

	node_ptr head;

	size_t sz;

	void incrementSize(){
        this->sz++;
    }
	void decrementSize(){
        this->sz--;
    }

public:
	List(){
        this->head = nullptr;   //utwórz wskaźnik na null
	    this->sz = 0;           //ustaw rozmiar na 0
    }
    bool find(int data){
        node_ptr currentNodePtr = this->head;     //utwórz bieżący węzeł równy head
	    while (currentNodePtr != nullptr)         //dopóki bieżący węzeł wskazuje na kolejny
	    {
            if((currentNodePtr->data) == data){   //jeśli wartość bieżącego węzła = szukany element, zakończ
                return true;
            }
		    currentNodePtr = currentNodePtr->nextNode; //bieżący węzeł = element na który wskazuje bieżący węzeł
	    }
        return false;
    }

	void add(int data){
        node_ptr newNodePtr = new Node;          //utwórz nowy węzeł
	    newNodePtr->data = data;                 //przypisz wartość do węzła
	    newNodePtr->nextNode = nullptr;			//ustaw wskaźnik węzła na null
    	if (isEmpty())
	    {
		    this->head = newNodePtr;            //jeśli lista pusta ustaw węzeł jako head
	    } 
    	else 
	    {	                                    //jeśli nie
		    node_ptr prevHeadPtr = this->head;	//head przechowaj w jako prev_head
		    this->head = newNodePtr;			//ustaw nowy węzeł jako head
		    newNodePtr->nextNode = prevHeadPtr; //ustaw wskaźnik nowego węzła na prev_head
    	}
	    incrementSize();
    
    }
	bool remove(int data){
        node_ptr prevNodePtr = nullptr;     //utwórz zmienną pomocniczą poprzedni węzeł i ustaw jego wskaźnik na null
	    node_ptr currentNodePtr = head;     //utwórz zmienną pomocniczą bieżący węzeł

	    if (isEmpty())                      //jeżeli lista pusta zakończ
	    {
	    	return false;
	    }
    	while (currentNodePtr != nullptr)    //wykonuj pętle do czasu aż bieżący element wskazuje na kolejny element
    	{
    		if (data == currentNodePtr->data)                               //jeżeli bieżący węzeł = wartość do usunięcia
    		{
    			node_ptr nodeAfterCurrentPtr = currentNodePtr->nextNode;    //utwórz zmienną pomocniczą węzeł kolejny po usuwanym
    			if (prevNodePtr == nullptr)                                 //jeśli poprzedni węzeł skazuje na null ustaw węzeł kolejny po usuwanym jako head
    			{
    				this->head = nodeAfterCurrentPtr;
    			}
    			else
    			{                                                           //jeśli nie to ustaw wskaźnik poprzedniego węzła na węzeł kolejny po usuwanym
    				prevNodePtr->nextNode = nodeAfterCurrentPtr;
    			}
    			delete currentNodePtr;      //dealokuj pamięć
    			decrementSize();            //zmniejsz rozmiar listy
    			return true;
    		}
    		prevNodePtr = currentNodePtr;
    		currentNodePtr = currentNodePtr->nextNode;
        }
        return false;
    }
	bool isEmpty(){
        return this->head == nullptr;
    }

	void emptyList(){
        node_ptr currentNodePtr;
    	while (this->head != nullptr)
    	{
    		currentNodePtr = this->head;
    		this->head = this->head->nextNode;	
    		delete currentNodePtr;
    	}
    	this->sz = 0;
    }

	size_t size(){
        return this->sz;
    }

	~List(){
        this->emptyList();
    }
};

class Stack
{
    private:
        int *num;
        int top;
    public:
        Stack(){
            top=-1;
            num = new int[10000000];
        }
        ~Stack(){
            delete[] num;
        }
        int push(int n){   
            if(isFull()){  //jeśli wskaźnik stosu = rozmiar stosu - 1
                return 0;  //zwróć 0
            }
            ++top;         //zwiększ wskaźnik stosu o 1
            num[top]=n;    //element na wierzchu stosu = dodawany element
            return n;      //zwróć element
        }
        int pop(){
            int temp;       //utwórz wartość tymczasową
            if(isEmpty())   //jeśli wskaźnik stosu = rozmiar stosu - 1
                return 0;   //zwróć 0
            temp=num[top];  //wartość z wierzchołka stosu przypisz to wartości tymczasowej
            --top;          //dekrementuj wysokość stosu
            return temp;    //zwróć wartość tymczasową
        }
        int isEmpty(){
            if(top==-1)
                return 1;
            else
                return 0; 
        }
        int isFull(){
            if(top==(9999999))
                return 1;
            else
                return 0;
        }
        int peek(){
            if(isEmpty()) //jeśli wskaźnik stosu = rozmiar stosu - 1
                return 0;//zwróć 0
            return num[top]; //zwróć wartość z wierzchołku stosu
        }
};

class Queue {
public:
    int front, rear, size;
    unsigned capacity;
    int* array;
    ~Queue(){
        delete[] array;
    }
};

Queue* createQueue(unsigned capacity)
{
    Queue* queue = new Queue();                 //utwórz obiekt kolejki
    queue->capacity = capacity;                 //ustaw pojemność
    queue->front = queue->size = 0;             //ustaw początek kolejki i rozmiar kolejki na 0
    queue->rear = capacity - 1;                 //ustaw koniec kolejki na pojemność kolejki - 1 
    queue->array = new int[queue->capacity];    //zaalokuj pamięć o pojemności kolejki
    return queue;
}

void deleteQueue(Queue* queue){
    delete queue;
}
 
int isFull(Queue* queue)
{
    return (queue->size == queue->capacity);
}
 
int isEmpty(Queue* queue)
{
    return (queue->size == 0);
}
 
void enqueue(Queue* queue, int item)
{
    if (isFull(queue))                  //jeśli rozmiar kolejki = pojemność kolejki
        return;                         //zakończ
    queue->rear = (queue->rear + 1)     //koniec kolejki = koniec+1 modulo pojemność
                  % queue->capacity;
    queue->array[queue->rear] = item;   //tab[koniec] = element dodawany
    queue->size = queue->size + 1;      //rozmiar kolejki ++
}
 
int dequeue(Queue* queue)
{
    if (isEmpty(queue))                     //jeśli rozmiar kolejki = 0 zwróć INT MIN
        return INT_MIN;
    int item = queue->array[queue->front];  //utwórz zmienną tymczasową i przypisz jej wartość elementu z początku kolejki
    queue->front = (queue->front + 1)       //ustaw początek kolejki na początek kolejki+1modulo pojemność kolejki
                   % queue->capacity;
    queue->size = queue->size - 1;          //dekrementuj rozmiar kolejki
    return item;                            //zwróć wartość zmiennej tymczasowej
}
 
int front(Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}
 
int rear(Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->rear];
}

void generate_data(string file_name,int amount){
    cout<<"Generating "<<amount<<" numbers to data file "<<file_name<<endl;
    fstream fout;
    fout.open(file_name,ios::out);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-1000000, 1000000);
    for(int i = 0; i < amount; i++){
        int generated_number =  dis(gen);
        fout<<generated_number<<"\n";
    }
    fout.close();
    cout<<"Data generated correctly"<<endl;
}

bool load_data(string file_name, int amount){
    cout<<"Loading data from "<<file_name<<" file"<<endl;
    ifstream fin;
    fin.open(file_name,ios::in);
    if(fin.fail()){
        cout<<"Data file "<<file_name<<" not exist"<<endl;
        fin.close();
        return false;
    }
    string line;
    int data_loaded = 0;
    for(int i = 0; i < amount; i++){
        fin>>line;
        if(!fin.eof()){
            data_vector.push_back(stoi(line));
        }else{
            cout<<"Not enough elements in data file "<<file_name<<endl;
            return false;
        } 
        data_loaded++;
    }
    cout<<"Loaded correctly "<<data_loaded<<" numbers"<<endl;
    fin.close();
    return true;
}

bool load_config(){
    cout<<"Loading config.ini"<<endl;
    ifstream fin;
    fin.open("config.ini",ios::in);
    if(fin.fail()){
        cout<<"Config.ini not found"<<endl;
        fin.close();
        return false;
    }
    vector<string> row;
    string line;
    fin >> data_file_name >> data_amount;
    fin >> results_file_name;
    while(!fin.eof()){
        string structure, operation, start_range, end_range, step, time;
        fin>>structure>>operation>>start_range>>end_range>>step>>time;
        if(structure.size() == 0 || operation.size() == 0 || start_range.size() == 0 || end_range.size() == 0 || step.size() == 0 || time.size() == 0){
            break;
        }
        vector<string> task;
        task.push_back(structure);
        task.push_back(operation);
        task.push_back(start_range);
        task.push_back(end_range);
        task.push_back(step);
        task.push_back(time);
        tasks.push_back(task);
    }
    fin.close();
    cout<<"Config loaded correctly"<<endl;
    return true;
}

void print_config(){
    cout<<"data file: "<<data_file_name<<endl;
    cout<<"data amount: "<<data_amount<<endl;
    cout<<"results file: "<<results_file_name<<endl;
    cout<<"number of tasks: "<<tasks.size()<<endl;
    cout<<"tasks: "<<endl;
    for(int i = 0; i < tasks.size(); i++){
        cout<<tasks[i][0]<<" "<<tasks[i][1]<<" "<<tasks[i][2]<<" "<<tasks[i][3]<<" "<<tasks[i][4]<<" "<<endl;
    }
}

void save_results(string results_file_name){
    cout<<"Saving results"<<endl;
    fstream fout;
    fout.open(results_file_name,ios::out);
    fout<<"data_structure,operation,size_of_structure,time_of_operation_s,number_of_repetitions"<<endl;
    for(int i = 0; i < results.size(); i++){
        fout<<results[i]<<endl;
        //fout<<results[i][0]<<","<<results[i][1]<<","<<results[i][2]<<","<<results[i][3]<<endl;
    }
    fout.close();
    cout<<"Correctly saved "<<results.size()<<" results"<<endl;

}

void array_create_operation(int size_of_array, int number_of_repeats){
    using namespace std::chrono;
    duration<double> time_span = duration<double>(0);
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        t_start = high_resolution_clock::now();
        int *test_array = new int[size_of_array];   //utwórz wskaźnik na tablicę i alokuj pamięć o rozmiarze size_of_array * sizeof(int)
        for(int i = 0; i < size_of_array; i++){     //dla każdego elementu tablicy od 0 to size_of_array - 1
            test_array[i] = data_vector[i];         //wstaw do tablicy element ze zbioru danych testowych
        }
        t_end = high_resolution_clock::now();
        time_span += duration_cast<duration<double>>(t_end - t_start);
        delete[] test_array;
    }
    Result array_create_result = Result("array","create",size_of_array,time_span.count(),number_of_repeats);
    results.push_back(array_create_result.toString());
}

void array_put_operation(int size_of_array, int number_of_repeats){
    using namespace std::chrono;
    int *test_array = new int[size_of_array];
    for(int i = 0; i < size_of_array; i++){
        test_array[i] = data_vector[i];
    }
    int random_value = rand() % 1000000;
    int random_index = rand() % size_of_array;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        test_array[random_index] = random_value;       //wstaw losową wartość testową
    }
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t_end - t_start);
    Result array_put_result = Result("array","put",size_of_array,time_span.count(),number_of_repeats);
    results.push_back(array_put_result.toString());
}

void array_search_operation(int size_of_array, int number_of_repeats){
    using namespace std::chrono;
    int *test_array = new int[size_of_array];
    for(int i = 0; i < size_of_array; i++){
        test_array[i] = data_vector[i];
    }
    srand(time(NULL));
    int random_index = rand() % size_of_array;
    int searched_value = data_vector[random_index];
    bool found = false;
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    duration<double> time_span = duration<double>(0);
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        int random_index = rand() % size_of_array;
        int searched_value = data_vector[random_index];
        t_start = high_resolution_clock::now();
        for(int i = 0; i < size_of_array; i++){             //powtarzaj w zakresie od 0 do rozmiar tablicy
            if(test_array[i] == searched_value){            // jeśli tab[i] = szukany element zakończ, przeciwnie i++
                t_end = high_resolution_clock::now();
                found = true;
                break;
            }
        }
        if(!found){
            cout<<"Array searching error"<<endl;
            t_end = high_resolution_clock::now();
        }
        time_span += duration_cast<duration<double>>(t_end - t_start);
    }
    Result array_search_result = Result("array","search",size_of_array,time_span.count(),number_of_repeats);
    results.push_back(array_search_result.toString());
    delete[] test_array;
}

void array_delete_operation(int size_of_array, int number_of_repeats){
    using namespace std::chrono;
    duration<double> time_span = duration<double>(0);
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        int *test_array = new int[size_of_array];
        for(int i = 0; i < size_of_array; i++){
            test_array[i] = data_vector[i];
        }
        t_start = high_resolution_clock::now();
        size_t temp_delete_array_size = size_of_array-1;                                //utwórz rozmiar tablicy tymczasowej równy romziarowy aktualnej tablicy pomniejszony o 1
        int *temp_delete_array = new int[temp_delete_array_size];                       //utwórz wskaźnik na tablicę tymczasową i alokuj pamięć o rozmiarze tablicy tymczasowej
        memcpy(temp_delete_array, test_array, temp_delete_array_size * sizeof(int));    //kopiuj zawartość aktualnej tablicy do tablicy tablicy tymczasowej w zakresie rozmiaru tablicy tymczasowej
        delete[] test_array;                                                            //usuń aktualną tablicę
        test_array = temp_delete_array;                                                 //ustaw watość wskaźnika aktualnej tablicy na tablicę tymczasową
        t_end = high_resolution_clock::now();
        time_span += duration_cast<duration<double>>(t_end - t_start);
        delete[] temp_delete_array; 
    }
    Result array_delete_result = Result("array","delete",size_of_array,time_span.count(),number_of_repeats);
    results.push_back(array_delete_result.toString());
}

void array_add_operation(int size_of_array, int number_of_repeats){
    using namespace std::chrono;
    duration<double> time_span = duration<double>(0);
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        int *test_array = new int[size_of_array];
        for(int i = 0; i < size_of_array; i++){
            test_array[i] = data_vector[i];
        }
        int random_value = rand() % 1000000;
        t_start = high_resolution_clock::now();
        size_t temp_add_array_size = size_of_array+1;                       //ustal rozmiar nowej tablicy jako rozmiar poprzedniej powiększony o 1
        int *temp_add_array = new int[temp_add_array_size];                 //utwórz wskaźnik na tablicę tymczasową i alokuj pamięć o rozmiarze o 1 większym od aktualnej tablicy
        memcpy(temp_add_array, test_array, size_of_array * sizeof(int));    //kopiuj zawartość tablicy do tablicy tymczasowej
        temp_add_array[size_of_array] = random_value;                       //do ostatniego elementu tblicy tymczasowej dodaj wartość testową
        delete[] test_array;                                                //usuń aktualną tablicą i dealokuj pamięć
        test_array = temp_add_array;                                        //ustaw wartość wskaźnika tablicy na tablicę tymczasową
        t_end = high_resolution_clock::now();
        time_span += duration_cast<duration<double>>(t_end - t_start);
        delete[] temp_add_array;
    }
    Result array_add_result = Result("array","add",size_of_array,time_span.count(),number_of_repeats);
    results.push_back(array_add_result.toString());
}

void stack_create_operation(int size_of_stack, int number_of_repeats){
    using namespace std::chrono;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        Stack test_stack = Stack();                 //utwórz stos
        for(int i = 0; i < size_of_stack; i++){     //powtarzaj od 0 do rozmiar stosu
            test_stack.push(data_vector[i]);        //umieść wartość testową na stosie
        }
    }
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t_end - t_start);
    Result stack_create_result = Result("stack","create",size_of_stack,time_span.count(),number_of_repeats);
    results.push_back(stack_create_result.toString());
}

void stack_search_operation(int size_of_stack, int number_of_repeats){
    using namespace std::chrono;
    Stack test_stack = Stack();
    for(int i = 0; i < size_of_stack; i++){
        test_stack.push(data_vector[i]);
    }
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration<double>(0);
    srand(time(NULL));
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        int random_index = rand() % size_of_stack;
        int searched_value = data_vector[random_index];
        bool found = false;
        t_start = high_resolution_clock::now();
        int temp_stack_deep = 0;                        //tworzymy zmienną przechowującą wysokość stosu tymczasowego
        Stack temp_search_stack = Stack();              //tworzymy stos tymczasowy
        for(int i = 0; i < size_of_stack; i++){         //powtarzaj od 0 do rozmiar stosu
            if(test_stack.peek() == searched_value){    //jeśli wartość na wierzchołku stosu
                t_end = high_resolution_clock::now();   //zakończ pętlę
                found = true;
                break;
            }else{                                        //jeśli nie
                temp_search_stack.push(test_stack.pop()); //przełóż wartość ze stosu na stos tymczasowy
                temp_stack_deep++;                        //iteruj zmienną przechowującą wysokość stosu tymczasowego
            }
        }
        for(int i = 0; i < temp_stack_deep; i++){    //powtarzaj od 0 do wysokość stosu tymczasowego
            test_stack.push(temp_search_stack.pop());//przełóż wartość ze stosu tymczasowego na stos
        }
        if(!found){
            cout<<"Stack searching error"<<endl;
            t_end = high_resolution_clock::now();
        }
        time_span += duration_cast<duration<double>>(t_end - t_start);
    }
    Result stack_search_result = Result("stack","search",size_of_stack,time_span.count(),number_of_repeats);
    results.push_back(stack_search_result.toString());
}

void stack_push_operation(int size_of_stack, int number_of_repeats){
    using namespace std::chrono;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration<double>(0);
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        Stack test_stack = Stack();
        for(int i = 0; i < size_of_stack; i++){ 
            test_stack.push(data_vector[i]);
        }
        int random_value = rand() % 1000000;   
        t_start = high_resolution_clock::now();
        test_stack.push(random_value);              //dodaj element na stos
        t_end = high_resolution_clock::now();
        time_span += duration_cast<duration<double>>(t_end - t_start);
    }
    Result stack_push_result = Result("stack","push",size_of_stack,time_span.count(),number_of_repeats);
    results.push_back(stack_push_result.toString());
}

void stack_pop_operation(int size_of_stack, int number_of_repeats){
    using namespace std::chrono;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration<double>(0);
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        Stack test_stack = Stack();
        for(int i = 0; i < size_of_stack; i++){
            test_stack.push(data_vector[i]);
        }
        t_start = high_resolution_clock::now();
        test_stack.pop();                       //pobierz wartość ze stosu
        t_end = high_resolution_clock::now();
        time_span += duration_cast<duration<double>>(t_end - t_start);
    }
    Result stack_pop_result = Result("stack","pop",size_of_stack,time_span.count(),number_of_repeats);
    results.push_back(stack_pop_result.toString());
}

void stack_put_operation(int size_of_stack, int number_of_repeats){
    using namespace std::chrono;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration<double>(0);
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        Stack test_stack = Stack();
        for(int i = 0; i < size_of_stack; i++){
            test_stack.push(data_vector[i]);
        }
        int test_deep = size_of_stack/2;
        int random_value = rand() % 1000000;
        t_start = high_resolution_clock::now();
        Stack temp_put_stack = Stack();             //utwórz stos tymczasowy
        for(int i = 0; i < test_deep; i++){       //powtarzaj glebokosc_stosu razy
            temp_put_stack.push(test_stack.pop());  //zdejmij element ze stosu i wstaw do stosu tymczasowego
        }
        test_stack.push(random_value);              //wstaw element na stos
        for(int i = 0; i < test_deep; i++){       //powtarzaj glebokosc_stosu razy
            test_stack.push(temp_put_stack.pop());  //zdejmij element ze stosu tymczasowego i wstaw do stosu 
        }
        t_end = high_resolution_clock::now();
        time_span += duration_cast<duration<double>>(t_end - t_start);
    }
    Result stack_pop_result = Result("stack","put",size_of_stack,time_span.count(),number_of_repeats);
    results.push_back(stack_pop_result.toString());
}

void list_create_operation(int size_of_list, int number_of_repeats){
    using namespace std::chrono;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        List test_list;                         //utwórz listę
        for(int i = 0; i < size_of_list; i++){
            test_list.add(data_vector[i]);      //dodawaj element testowy w pętli
        }
    }
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t_end - t_start);
    Result list_create_result = Result("list","create",size_of_list,time_span.count(),number_of_repeats);
    results.push_back(list_create_result.toString());
}

void list_search_operation(int size_of_list, int number_of_repeats){
    using namespace std::chrono;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration<double>(0);
    srand(time(NULL));
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        List test_list;
        for(int i = 0; i < size_of_list; i++){
            test_list.add(data_vector[i]);
        }
        int random_index = rand() % size_of_list;
        int searched_value = data_vector[random_index];
        t_start = high_resolution_clock::now();
        if(!test_list.find(searched_value)){    //szukaj elementu searched_value w liście
            cout<<" find error ";
        }
        t_end = high_resolution_clock::now();
        time_span += duration_cast<duration<double>>(t_end - t_start);
    }
    Result list_search_result = Result("list","search",size_of_list,time_span.count(),number_of_repeats);
    results.push_back(list_search_result.toString());
}

void list_add_operation(int size_of_list, int number_of_repeats){
    using namespace std::chrono;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration<double>(0);
    srand(time(NULL));
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        List test_list;
        for(int i = 0; i < size_of_list; i++){
            test_list.add(data_vector[i]);
        }
        int random_value = rand() % 1000000;
        t_start = high_resolution_clock::now();
        test_list.add(random_value);               //dodaj element losowy do listy
        t_end = high_resolution_clock::now();
        time_span += duration_cast<duration<double>>(t_end - t_start);
    }
    Result list_add_result = Result("list","add",size_of_list,time_span.count(),number_of_repeats);
    results.push_back(list_add_result.toString());
}

void list_delete_operation(int size_of_list, int number_of_repeats){
    using namespace std::chrono;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration<double>(0);
    srand(time(NULL));
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        List test_list;
        for(int i = 0; i < size_of_list; i++){
            test_list.add(data_vector[i]);
        }
        int random_index = rand() % size_of_list;
        int random_value = data_vector[random_index];
        t_start = high_resolution_clock::now();
        if(!test_list.remove(random_value)){        //usuń losową wartość z listy
            cout<<" delete error ";             
        }
        t_end = high_resolution_clock::now();
        time_span += duration_cast<duration<double>>(t_end - t_start);
    }
    Result list_delete_result = Result("list","delete",size_of_list,time_span.count(),number_of_repeats);
    results.push_back(list_delete_result.toString());
}

void queue_create_operation(int size_of_queue, int number_of_repeats){
    using namespace std::chrono;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        Queue* test_queue = createQueue(size_of_queue);  //utwórz kolejkę na tablicy o rozmiarze size_of_queue
        for(int i = 0; i < size_of_queue; i++){          //powtarzaj od 0 do size_of_queue
            enqueue(test_queue,data_vector[i]);          //wstaw do kolejki element ze zbioru testowego
        }
    }
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t_end - t_start);
    Result queue_create_result = Result("queue","create",size_of_queue,time_span.count(),number_of_repeats);
    results.push_back(queue_create_result.toString());
}

void queue_search_operation(int size_of_queue, int number_of_repeats){
    using namespace std::chrono;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    srand(time(NULL));
    duration<double> time_span = duration<double>(0);
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        Queue* test_queue = createQueue(size_of_queue);
        for(int i = 0; i < size_of_queue; i++){
            enqueue(test_queue,data_vector[i]);
        }
        int random_index = rand() % size_of_queue;
        int searched_value = data_vector[random_index];
        t_start = high_resolution_clock::now();
        Queue* temp_search_queue = createQueue(size_of_queue); //utwórz kolejkę tymczasową o pojemności rozmiaru kolejki
        int temp_queue_len = 0; //utwórz zmiennę tymczasową rozmiar kolejki
        bool found = false;
        for(int i = 0; i < size_of_queue; i++){  //powtarzaj od 0 do rozmiar kolejki
            if(front(test_queue) == searched_value){  //jeśli element na początku kolejki = szukany element
                found = true;
                break;                              //przerwij szukanie
            }else{
                enqueue(temp_search_queue,dequeue(test_queue));  //jeśli nie, przełóż element z początku kolejki na koniec kolejki tymczasowej
            }
            temp_queue_len++;
        }
        for(int i = 0; i < temp_queue_len; i++){   //powtarzaj od 0 do długość kolejki tymczasowej
            enqueue(test_queue,dequeue(temp_search_queue));   //przełóż element z początku kolejki tymczasowej na koniec kolejki
        }
        if(!found){
            cout<<" queue search error "<<endl;
        }
        t_end = high_resolution_clock::now();
        time_span += duration_cast<duration<double>>(t_end - t_start);
        deleteQueue(test_queue);
        deleteQueue(temp_search_queue);

    }
    Result queue_search_result = Result("queue","search",size_of_queue,time_span.count(),number_of_repeats);
    results.push_back(queue_search_result.toString());
}

void queue_enqueue_operation(int size_of_queue, int number_of_repeats){
    using namespace std::chrono;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    srand(time(NULL));
    duration<double> time_span = duration<double>(0);
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        Queue* test_queue = createQueue(size_of_queue);
        for(int i = 0; i < size_of_queue; i++){
            enqueue(test_queue,data_vector[i]);
        }
        int random_value = rand() % 1000000;
        t_start = high_resolution_clock::now();
        enqueue(test_queue,random_value); //dodaj element do kolejki
        t_end = high_resolution_clock::now();
        time_span += duration_cast<duration<double>>(t_end - t_start);
        deleteQueue(test_queue);
    }
    Result queue_enqueue_result = Result("queue","enqueue",size_of_queue,time_span.count(),number_of_repeats);
    results.push_back(queue_enqueue_result.toString());
}

void queue_dequeue_operation(int size_of_queue, int number_of_repeats){
    using namespace std::chrono;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration<double>(0);
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        Queue* test_queue = createQueue(size_of_queue);
        for(int i = 0; i < size_of_queue; i++){
            enqueue(test_queue,data_vector[i]);
        }
        t_start = high_resolution_clock::now();
        dequeue(test_queue);                    //usun element z kolejki
        t_end = high_resolution_clock::now();
        time_span += duration_cast<duration<double>>(t_end - t_start);
        deleteQueue(test_queue);
    }
    Result queue_dequeue_result = Result("queue","dequeue",size_of_queue,time_span.count(),number_of_repeats);
    results.push_back(queue_dequeue_result.toString());
}

int main(){
    load_config();
    if(!load_data(data_file_name,data_amount)){
        generate_data(data_file_name,data_amount);
        load_data(data_file_name,data_amount);
    }
    for(int i = 0;i < tasks.size(); i++){
        string structure = tasks[i][0];
        string operation = tasks[i][1]; 
        int start_range = stoi(tasks[i][2]);
        int end_range = stoi(tasks[i][3]);
        int step = stoi(tasks[i][4]);
        int time_repeat = stoi(tasks[i][5]);
        cout<<"Task "<<operation<<" on "<<structure<<" in range from "<<start_range<<" to "<<end_range<<" with step "<<step<<" made "<<time_repeat<<" times"<<endl;
        if(start_range<1||end_range>data_vector.size()||time_repeat < 1){
            cout<<"Cannot execute task in this range"<<endl;
        }
        else{
            if(tasks[i][0] == "array"){
                for(int j = start_range; j <= end_range; j += step){
                    cout<<"Array operation "<<operation<<" with "<<j<<" elements ";
                    if(operation == "create"){
                        array_create_operation(j,time_repeat);
                    }else if(operation == "search"){
                        array_search_operation(j,time_repeat);
                    }else if(operation == "put"){
                        array_put_operation(j,time_repeat);
                    }else if(operation == "delete"){
                        array_delete_operation(j,time_repeat);
                    }else if(operation == "add"){
                        array_add_operation(j,time_repeat);
                    }else{
                        cout<<endl<<"Operation not recognized"<<endl;
                    }
                    cout<<"done"<<endl;
                }
                cout<<"Task done"<<endl;
            }else if(tasks[i][0] == "list"){
                for(int j = start_range; j <= end_range; j += step){
                    cout<<"List operation "<<operation<<" with "<<j<<" elements ";
                    if(operation == "create"){
                        list_create_operation(j,time_repeat);
                    }else if(operation == "search"){
                        list_search_operation(j,time_repeat);

                    }else if(operation == "delete"){
                        list_delete_operation(j,time_repeat);

                    }else if(operation == "add"){
                        list_add_operation(j,time_repeat);
                    }else{
                        cout<<endl<<"Operation not recognized"<<endl;
                    }
                    cout<<"done"<<endl;
                }
                cout<<"Task done"<<endl;
            }else if(tasks[i][0] == "stack"){
                for(int j = start_range; j <= end_range; j += step){
                    cout<<"Stack operation "<<operation<<" with "<<j<<" elements ";
                    if(operation == "create"){
                        stack_create_operation(j,time_repeat);
                    }else if(operation == "search"){
                        stack_search_operation(j,time_repeat);
                    }else if(operation == "put"){
                        stack_put_operation(j,time_repeat);
                    }else if(operation == "pop"){
                        stack_pop_operation(j,time_repeat);
                    }else if(operation == "push"){
                        stack_push_operation(j,time_repeat);
                    }else{
                        cout<<endl<<"Operation not recognized"<<endl;
                    }
                    cout<<"done"<<endl;
                }
                cout<<"Task done"<<endl;
            }else if(tasks[i][0] == "queue"){
                for(int j = start_range; j <= end_range; j += step){
                    cout<<"Queue operation "<<operation<<" with "<<j<<" elements ";
                    if(operation == "create"){
                        queue_create_operation(j,time_repeat);
                    }else if(operation == "search"){
                        queue_search_operation(j,time_repeat);
                    }else if(operation == "enqueue"){
                        queue_enqueue_operation(j,time_repeat);
                    }else if(operation == "dequeue"){
                        queue_dequeue_operation(j,time_repeat);
                    }else{
                        cout<<endl<<"Operation not recognized"<<endl;
                    }
                    cout<<"done"<<endl;
                }
                cout<<"Task done"<<endl;
            }else{
                cout<<"Cannot recognize "<<tasks[i][0]<<" structure";
            }
        }
    }
    save_results(results_file_name);
    cout<<"Press any key to continue...";
    getch();
    return 0;
}