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
using namespace std;
vector<int> data_vector;
vector<vector<string>> tasks;
vector<vector<string>> results;
string data_file_name = "";
int data_amount = 0;
string results_file_name = "";

struct Node {
    int number;
    Node *next;
    Node(){
        next = 0;
    }
    int get_data(){
        return number;
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

class Queue
{
    Node *front, *rear;
public:
    Queue()
    {
        front = rear = NULL;
    }
    void enqueue(int number)
    {
        Node *newnode;
        newnode = new Node;
        newnode->number = number;
        newnode->next = NULL;
        if(front == NULL)
            front = rear = newnode;
        else
        {
            rear->next = newnode;
            rear = newnode;
        }
    }
    int dequeue()
    {
        Node *temp;
        if(front == NULL){
            cout<<"Queue is Empty";
            return 0;
        }
        else
        {
            temp= front;
            int temp_number = front->number;
            front = front->next;
            delete temp;
            return temp_number;
        }
    }
    int peek(){
        return front->number;
    }
};

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
    fout<<"data_structure,operation,size_of_structure,time_of_operation_s"<<endl;
    for(int i = 0; i < results.size(); i++){
        fout<<results[i][0]<<","<<results[i][1]<<","<<results[i][2]<<","<<results[i][3]<<endl;
    }
    cout<<"Correctly saved "<<results.size()<<" results"<<endl;
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
    vector<string> this_restult = {"array","create",to_string(size_of_array),to_string(time_span.count())};
    results.push_back(this_restult);
    //SEARCH OPERATION
    srand(time(NULL));
    int random_index = rand() % size_of_array;
    int searched_value = data_vector[random_index];
    bool found = false;
    t_start = high_resolution_clock::now();
    for(int i = 0; i < size_of_array; i++){
        if(test_array[i] == data_vector[i]){
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
    this_restult = {"array","search",to_string(size_of_array),to_string(time_span.count())};
    results.push_back(this_restult);
    //PUT OPERATION
    random_index = rand() % size_of_array;
    t_start = high_resolution_clock::now();
    test_array[random_index] = 0;
    t_end = high_resolution_clock::now();
    test_array[random_index] = data_vector[random_index];
    time_span = duration_cast<duration<double>>(t_end - t_start);
    this_restult = {"array","put",to_string(size_of_array),to_string(time_span.count())};
    results.push_back(this_restult);
    //ADD OPERATION
    int *temp_test_array = test_array;
    int random_value = rand() % 1000000;
    t_start = high_resolution_clock::now();
    int *temp_array = new int[(size_of_array+1)];
    for(int i = 0;i < size_of_array; i++){
        temp_array[i] = test_array[i];
    }
    temp_array[size_of_array] = random_value;
    test_array = temp_array;
    delete temp_array;
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    test_array = temp_test_array;
    this_restult = {"array","add",to_string(size_of_array),to_string(time_span.count())};
    results.push_back(this_restult);
    //DELETE OPERATION
    random_index = rand() % size_of_array;
    random_index = 1;
    t_start = high_resolution_clock::now();
    temp_array = new int[(size_of_array-1)];
    for(int i = 0;i < random_index; i++){
        temp_array[i] = test_array[i];
    }
    for(int i = random_index+1; i<size_of_array;i++){
        temp_array[(i-1)] = test_array[i];
    }
    test_array = temp_array;
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    this_restult = {"array","delete",to_string(size_of_array),to_string(time_span.count())};
    results.push_back(this_restult);
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
    vector<string> this_restult = {"stack","create",to_string(size_of_stack),to_string(time_span.count())};
    results.push_back(this_restult);
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
    this_restult = {"stack","search",to_string(size_of_stack),to_string(time_span.count())};
    results.push_back(this_restult);
    //PUSH OPERATION
    int random_value = rand() % 1000000;
    t_start = high_resolution_clock::now();
    test_stack.push(random_value);
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    this_restult = {"stack","push",to_string(size_of_stack),to_string(time_span.count())};
    results.push_back(this_restult);
    //POP OPERATION
    t_start = high_resolution_clock::now();
    test_stack.pop();
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    this_restult = {"stack","pop",to_string(size_of_stack),to_string(time_span.count())};
    results.push_back(this_restult);
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
    this_restult = {"stack","put",to_string(size_of_stack),to_string(time_span.count())};
    results.push_back(this_restult);
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
    vector<string> this_restult = {"list","create",to_string(size_of_list),to_string(time_span.count())};
    results.push_back(this_restult);
    //SEARCH OPERATION
    int random_index = rand() % size_of_list;
    int searched_value = data_vector[random_index];
    t_start = high_resolution_clock::now();
    if(!test_list.find(searched_value)){
        cout<<" find error ";
    }
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    this_restult = {"list","search",to_string(size_of_list),to_string(time_span.count())};
    results.push_back(this_restult);
    //ADD OPERATION
    int random_value = rand() % 1000000;
    t_start = high_resolution_clock::now();
    test_list.add(random_value);
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    this_restult = {"list","add",to_string(size_of_list),to_string(time_span.count())};
    results.push_back(this_restult);
    //DELETE OPERATION
    t_start = high_resolution_clock::now();
    if(!test_list.remove(random_value)){
        cout<<" delete error ";
    }
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    this_restult = {"list","delete",to_string(size_of_list),to_string(time_span.count())};
    results.push_back(this_restult);
}

void queue_operations(int size_of_queue){
    using namespace std::chrono;
    //CREATE OPERATION
    high_resolution_clock::time_point t_start = high_resolution_clock::now();
    Queue test_queue;
    for(int i = 0; i < size_of_queue; i++){
        test_queue.enqueue(data_vector[i]);
    }
    high_resolution_clock::time_point t_end = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t_end - t_start);
    vector<string> this_restult = {"queue","create",to_string(size_of_queue),to_string(time_span.count())};
    results.push_back(this_restult);
    //SEARCH OPERATION
    int random_index = rand() % size_of_queue;
    int searched_value = data_vector[random_index];
    t_start = high_resolution_clock::now();
    Queue temp_search_queue;
    int temp_queue_len = 0;
    bool found = false;
    for(int i = 0; i < size_of_queue; i++){
        if(test_queue.peek() == searched_value){
            found = true;
            break;
        }else{
            temp_search_queue.enqueue(test_queue.dequeue());
        }
        temp_queue_len++;
    }
    for(int i = 0; i < temp_queue_len; i++){
        test_queue.enqueue(temp_search_queue.dequeue());
    }
    if(!found){
        cout<<" queue search error "<<endl;
    }
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    this_restult = {"queue","search",to_string(size_of_queue),to_string(time_span.count())};
    results.push_back(this_restult);
    //ADD OPERATION
    int random_value = rand() % 1000000;
    t_start = high_resolution_clock::now();
    test_queue.enqueue(random_value);
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    this_restult = {"queue","enqueue",to_string(size_of_queue),to_string(time_span.count())};
    results.push_back(this_restult);
    //DELETE OPERATION
    t_start = high_resolution_clock::now();
    test_queue.dequeue();
    t_end = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t_end - t_start);
    this_restult = {"queue","dequeue",to_string(size_of_queue),to_string(time_span.count())};
    results.push_back(this_restult);
    
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
                    for(int k = 0; k < time_repeat; k++){
                        cout<<"Array operations with "<<j<<" elements ";
                        array_operations(j);
                        cout<<"done"<<endl;
                    }
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