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
    int size_of_strucutre;
    double time_span;
    int averages_denominator;
    Result(string data_structure, string operation, int size_of_strucutre, double time_span, int averages_denominator){
        this->data_structure = data_structure;
        this->operation = operation;
        this->size_of_strucutre = size_of_strucutre;
        this->time_span = time_span;
        this->averages_denominator = averages_denominator;
    }
    Result(string data_structure, string operation, int size_of_strucutre, double time_span){
        this->data_structure = data_structure;
        this->operation = operation;
        this->size_of_strucutre = size_of_strucutre;
        this->time_span = time_span;
        this->averages_denominator = 1;
    }
    string toString(){
        return(data_structure+","+operation+","+to_string(size_of_strucutre)+","+to_string(time_span)+","+to_string(averages_denominator));
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
        this->head = nullptr;
	    this->sz = 0;
    }
    bool find(int data){
        node_ptr currentNodePtr = this->head;
	    while (currentNodePtr != nullptr)
	    {
            if((currentNodePtr->data) == data){
                return true;
            }
		    currentNodePtr = currentNodePtr->nextNode;
	    }
        return false;
    }

	void add(int data){
        node_ptr newNodePtr = new Node;
	    newNodePtr->data = data; 
	    newNodePtr->nextNode = nullptr;			
    	if (isEmpty())
	    {
		    this->head = newNodePtr;
	    } 
    	else 
	    {	
		    node_ptr prevHeadPtr = this->head;	
		    this->head = newNodePtr;			
		    newNodePtr->nextNode = prevHeadPtr; 
    	}
	    incrementSize();
    
    }
	bool remove(int data){
        node_ptr prevNodePtr = nullptr;
	    node_ptr currentNodePtr = head;

	    if (isEmpty())
	    {
	    	return false;
	    }
    	while (currentNodePtr != nullptr)
    	{
    		if (data == currentNodePtr->data)
    		{
    			node_ptr nodeAfterCurrentPtr = currentNodePtr->nextNode;
    			if (prevNodePtr == nullptr)
    			{
    				this->head = nodeAfterCurrentPtr;
    			}
    			else
    			{
    				prevNodePtr->nextNode = nodeAfterCurrentPtr;
    			}
    			delete currentNodePtr;
    			decrementSize();
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
            if(isFull()){
                return 0;
            }
            ++top;
            num[top]=n;
            return n;
        }
        int pop(){
            int temp;
            if(isEmpty())
                return 0;
            temp=num[top];
            --top;
            return temp;
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
            if(isEmpty())
                return 0;
            return num[top];
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
    Queue* queue = new Queue();
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = new int[queue->capacity];
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
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}
 
int dequeue(Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
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
    fout.open("data.csv",ios::out);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-1000000, 1000000);
    for(int i = 0; i < amount; i++){
        fout<<dis(gen)<<"\n";
    }
    cout<<"Data generated correctly"<<endl;
}

bool load_data(string file_name, int amount){
    cout<<"Loading data from "<<file_name<<" file"<<endl;
    ifstream fin;
    fin.open(file_name,ios::in);
    if(fin.fail()){
        cout<<"Data file "<<file_name<<" not exist"<<endl;
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
    return true;
}

bool load_config(){
    cout<<"Loading config.ini"<<endl;
    ifstream fin;
    fin.open("config.ini",ios::in);
    if(fin.fail()){
        cout<<"Config.ini not found"<<endl;
        return false;
    }
    vector<string> row;
    string line;
    fin >> data_file_name >> data_amount;
    fin >> results_file_name;
    while(!fin.eof()){
        string structure, start_range, end_range, step, time;
        fin>>structure>>start_range>>end_range>>step>>time;
        if(structure.size() == 0 || start_range.size() == 0 || end_range.size() == 0 || step.size() == 0 || time.size() == 0){
            break;
        }
        vector<string> task;
        task.push_back(structure);
        task.push_back(start_range);
        task.push_back(end_range);
        task.push_back(step);
        task.push_back(time);
        tasks.push_back(task);
    }
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
    fout<<"data_structure,operation,size_of_structure,time_of_operation_s,averages_denominator"<<endl;
    for(int i = 0; i < results.size(); i++){
        fout<<results[i]<<endl;
        //fout<<results[i][0]<<","<<results[i][1]<<","<<results[i][2]<<","<<results[i][3]<<endl;
    }
    cout<<"Correctly saved "<<results.size()<<" results"<<endl;
}

void array_create_operation(int size_of_array, int number_of_repeats){
    using namespace std::chrono;
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        int *test_array = new int[size_of_array];
        for(int i = 0; i < size_of_array; i++){
            test_array[i] = data_vector[i];
        }
        delete[] test_array;
    }
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t_end - t_start);
    Result array_create_result = Result("array","create",size_of_array,time_span.count()/(double)number_of_repeats,number_of_repeats);
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
        test_array[random_index] = random_value;
    }
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t_end - t_start);
    Result array_put_result = Result("array","put",size_of_array,time_span.count()/(double)number_of_repeats,number_of_repeats);
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
    for(int repeat = 0; repeat < number_of_repeats; repeat++){
        for(int i = 0; i < size_of_array; i++){
            if(test_array[i] == searched_value){
                t_end = high_resolution_clock::now();
                found = true;
                break;
            }
        }
        if(!found){
            cout<<"Array searching error"<<endl;
            t_end = high_resolution_clock::now();
        }
    }
    duration<double> time_span = duration_cast<duration<double>>(t_end - t_start);
    Result array_search_result = Result("array","search",size_of_array,time_span.count()/number_of_repeats,number_of_repeats);
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
        size_t temp_delete_array_size = size_of_array-1;
        int *temp_delete_array = new int[temp_delete_array_size];
        memcpy(temp_delete_array, test_array, temp_delete_array_size * sizeof(int));
        delete[] test_array;
        test_array = temp_delete_array;
        t_end = high_resolution_clock::now();
        time_span = time_span + duration_cast<duration<double>>(t_end - t_start);
        delete[] temp_delete_array; 
    }
    Result array_delete_result = Result("array","delete",size_of_array,time_span.count()/(double)number_of_repeats,number_of_repeats);
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
        size_t temp_add_array_size = size_of_array+1;
        int *temp_add_array = new int[temp_add_array_size];
        memcpy(temp_add_array, test_array, size_of_array * sizeof(int));
        temp_add_array[size_of_array] = random_value;
        delete[] test_array;
        test_array = temp_add_array;
        t_end = high_resolution_clock::now();
        time_span += duration_cast<duration<double>>(t_end - t_start);
        delete[] temp_add_array;
    }
    Result array_add_result = Result("array","add",size_of_array,time_span.count()/(double)number_of_repeats,number_of_repeats);
    results.push_back(array_add_result.toString());
}

void array_operations(int size_of_array){
    using namespace std::chrono;
    //CREATE OPERATION
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    int *test_array = new int[size_of_array];
    for(int i = 0; i < size_of_array; i++){
        test_array[i] = data_vector[i];
    }
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t_end - t_start);
    Result array_create_result = Result("array","create",size_of_array,time_span.count());
    results.push_back(array_create_result.toString());
    //SEARCH OPERATION
    srand(time(NULL));
    int random_index = rand() % size_of_array;
    int searched_value = data_vector[random_index];
    bool found = false;
    t_start = high_resolution_clock::now();
    for(int i = 0; i < size_of_array; i++){
        if(test_array[i] == searched_value){
            t_end = high_resolution_clock::now();
            found = true;
            break;
        }
    }
    if(!found){
        cout<<"Array searching error"<<endl;
        t_end = high_resolution_clock::now();
    }
    time_span = duration_cast<duration<double>>(t_end - t_start);
    Result array_search_result = Result("array","search",size_of_array,time_span.count());
    results.push_back(array_search_result.toString());
    //PUT OPERATION
    random_index = rand() % size_of_array;
    t_start = high_resolution_clock::now();
    test_array[random_index] = random_index;
    t_end = high_resolution_clock::now();
    test_array[random_index] = data_vector[random_index];
    time_span = duration_cast<duration<double>>(t_end - t_start);
    Result array_put_result = Result("array","put",size_of_array,time_span.count());
    results.push_back(array_put_result.toString());
    //ADD OPERATION
    int *temp_test_array = test_array;
    int random_value = rand() % 1000000;
    t_start = high_resolution_clock::now();
    size_t temp_add_array_size = size_of_array+1;
    int *temp_add_array = new int[temp_add_array_size];
    memcpy(temp_add_array, test_array, size_of_array * sizeof(int));
    temp_add_array[size_of_array] = random_value;
    delete[] test_array;
    test_array = temp_add_array;
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    test_array = temp_test_array;
    Result array_add_result = Result("array","add",size_of_array,time_span.count());
    results.push_back(array_add_result.toString());
    delete[] temp_add_array;
    //DELETE OPERATION
    int *test_delete_array = new int[size_of_array];
    for(int i = 0; i < size_of_array; i++){
        test_delete_array[i] = data_vector[i];
    }
    t_start = high_resolution_clock::now();
    size_t temp_delete_array_size = size_of_array-1;
    int *temp_delete_array = new int[temp_delete_array_size];
    memcpy(temp_delete_array, test_delete_array, temp_delete_array_size * sizeof(int));
    delete[] test_delete_array;
    test_delete_array = temp_delete_array;
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    Result array_delete_result = Result("array","delete",size_of_array,time_span.count());
    results.push_back(array_delete_result.toString());
    delete[] temp_delete_array;
}

void stack_operations(int size_of_stack){
    using namespace std::chrono;
    //CREATE OPERATION
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    Stack test_stack = Stack();
    for(int i = 0; i < size_of_stack; i++){
        test_stack.push(data_vector[i]);
    }
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t_end - t_start);
    Result stack_create_result = Result("stack","create",size_of_stack,time_span.count());
    results.push_back(stack_create_result.toString());
    //SEARCH OPERATION
    srand(time(NULL));
    int random_index = rand() % size_of_stack;
    int searched_value = data_vector[random_index];
    bool found = false;
    t_start = high_resolution_clock::now();
    int temp_stack_deep = 0;
    Stack temp_search_stack = Stack();
    for(int i = (size_of_stack-1); i >= 0; i--){
        if(test_stack.peek() == searched_value){
            t_end = high_resolution_clock::now();
            found = true;
            break;
        }else{
            temp_search_stack.push(test_stack.pop());
            temp_stack_deep++;
        }
    }
    for(int i = 0; i < temp_stack_deep; i++){
        test_stack.push(temp_search_stack.pop());
    }
    if(!found){
        cout<<"Stack searching error"<<endl;
        t_end = high_resolution_clock::now();
    }
    time_span = duration_cast<duration<double>>(t_end - t_start);
    Result stack_search_result = Result("stack","search",size_of_stack,time_span.count());
    results.push_back(stack_search_result.toString());
    //PUSH OPERATION
    int random_value = rand() % 1000000;
    t_start = high_resolution_clock::now();
    test_stack.push(random_value);
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    Result stack_push_result = Result("stack","push",size_of_stack,time_span.count());
    results.push_back(stack_push_result.toString());
    //POP OPERATION
    t_start = high_resolution_clock::now();
    test_stack.pop();
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    Result stack_pop_result = Result("stack","pop",size_of_stack,time_span.count());
    results.push_back(stack_pop_result.toString());
    //PUT OPERATION
    srand(time(NULL));
    int random_deep = rand() % size_of_stack;
    random_value = rand() % 1000000;
    t_start = high_resolution_clock::now();
    Stack temp_put_stack = Stack();
    for(int i = 0; i < random_deep; i++){
        int temp = test_stack.pop();
        temp_put_stack.push(temp);
    }
    test_stack.push(random_value);
    for(int i = 0; i < random_deep; i++){
        test_stack.push(temp_put_stack.pop());
    }
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    Result stack_put_result = Result("stack","put",size_of_stack,time_span.count());
    results.push_back(stack_put_result.toString());
}

void list_operations(int size_of_list){
    using namespace std::chrono;
    //CREATE OPERATION
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    List test_list;
    for(int i = 0; i < size_of_list; i++){
        test_list.add(data_vector[i]);
    }
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t_end - t_start);
    Result list_create_result = Result("list","create",size_of_list,time_span.count());
    results.push_back(list_create_result.toString());
    //SEARCH OPERATION
    int random_index = rand() % size_of_list;
    int searched_value = data_vector[random_index];
    t_start = high_resolution_clock::now();
    if(!test_list.find(searched_value)){
        cout<<" find error ";
    }
    t_end = high_resolution_clock::now();
    Result list_search_result = Result("list","search",size_of_list,time_span.count());
    results.push_back(list_search_result.toString());
    //ADD OPERATION
    int random_value = rand() % 1000000;
    t_start = high_resolution_clock::now();
    test_list.add(random_value);
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    Result list_add_result = Result("list","add",size_of_list,time_span.count());
    results.push_back(list_add_result.toString());
    //DELETE OPERATION
    t_start = high_resolution_clock::now();
    if(!test_list.remove(random_value)){
        cout<<" delete error ";
    }
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    Result list_delete_result = Result("list","delete",size_of_list,time_span.count());
    results.push_back(list_delete_result.toString());
}

void queue_operations(int size_of_queue){
    using namespace std::chrono;
    //CREATE OPERATION
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    Queue* test_queue = createQueue(size_of_queue);
    for(int i = 0; i < size_of_queue; i++){
        enqueue(test_queue,data_vector[i]);
    }
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t_end - t_start);
    Result queue_create_result = Result("queue","create",size_of_queue,time_span.count());
    results.push_back(queue_create_result.toString());
    //SEARCH OPERATION
    int random_index = rand() % size_of_queue;
    int searched_value = data_vector[random_index];
    t_start = high_resolution_clock::now();
    Queue* temp_search_queue = createQueue(size_of_queue);
    int temp_queue_len = 0;
    bool found = false;
    for(int i = 0; i < size_of_queue; i++){
        if(front(test_queue) == searched_value){
            found = true;
            break;
        }else{
            enqueue(temp_search_queue,dequeue(test_queue));
        }
        temp_queue_len++;
    }
    for(int i = 0; i < temp_queue_len; i++){
        enqueue(test_queue,dequeue(temp_search_queue));
    }
    if(!found){
        cout<<" queue search error "<<endl;
    }
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    Result queue_searched_result = Result("queue","search",size_of_queue,time_span.count());
    results.push_back(queue_searched_result.toString());
    deleteQueue(temp_search_queue);
    //ADD OPERATION
    int random_value = rand() % 1000000;
    t_start = high_resolution_clock::now();
    enqueue(test_queue,random_value);
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    Result queue_enqueue_result = Result("queue","enqueue",size_of_queue,time_span.count());
    results.push_back(queue_enqueue_result.toString());
    //DELETE OPERATION
    t_start = high_resolution_clock::now();
    dequeue(test_queue);
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    Result queue_dequeue_result = Result("queue","dequeue",size_of_queue,time_span.count());
    results.push_back(queue_dequeue_result.toString());
    deleteQueue(test_queue);
    
}

int main(){
    load_config();
    if(!load_data(data_file_name,data_amount)){
        generate_data(data_file_name,data_amount);
        load_data(data_file_name,data_amount);
    }
    for(int i = 0;i < tasks.size(); i++){
        int start_range = stoi(tasks[i][1]);
        int end_range = stoi(tasks[i][2]);
        int step = stoi(tasks[i][3]);
        int time_repeat = stoi(tasks[i][4]);
        cout<<"Task on "<<tasks[i][0]<<" in range from "<<start_range<<" to "<<end_range<<" with step "<<step<<" made "<<time_repeat<<" times"<<endl;
        if(start_range<1||end_range>data_vector.size()||time_repeat < 1){
            cout<<"Cannot execute task in this range"<<endl;
        }
        else{
            if(tasks[i][0] == "array"){
                for(int j = start_range; j <= end_range; j += step){
                    // for(int k = 0; k < time_repeat; k++){
                    //     cout<<"Array operations with "<<j<<" elements ";
                    //     //array_operations(j);
                    //     array_create_operation(j,time_repeat);
                    //     cout<<"done"<<endl;
                    // }
                    cout<<"Array operations with "<<j<<" elements ";
                    array_create_operation(j,time_repeat);
                    array_search_operation(j,time_repeat);
                    array_put_operation(j,time_repeat);
                    array_delete_operation(j,time_repeat);
                    array_add_operation(j,time_repeat);
                    cout<<"done"<<endl;
                }
                cout<<"Task done"<<endl;
            }else if(tasks[i][0] == "list"){
                for(int j = start_range; j <= end_range; j += step){
                    for(int k = 0; k < time_repeat; k++){
                        cout<<"List operations with "<<j<<" elements ";
                        list_operations(j);
                        cout<<"done"<<endl;
                    }
                }
                cout<<"Task done"<<endl;
            }else if(tasks[i][0] == "stack"){
                for(int j = start_range; j <= end_range; j += step){
                    for(int k = 0; k < time_repeat; k++){
                        cout<<"Stack operations with "<<j<<" elements ";
                        stack_operations(j);
                        cout<<"done"<<endl;
                    }
                }
                cout<<"Task done"<<endl;
            }else if(tasks[i][0] == "queue"){
                for(int j = start_range; j <= end_range; j += step){
                    for(int k = 0; k < time_repeat; k++){
                        cout<<"Queue operations with "<<j<<" elements ";
                        queue_operations(j);
                        cout<<"done"<<endl;
                    }
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