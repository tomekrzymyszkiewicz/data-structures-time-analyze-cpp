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
#include <ratio>
#include<chrono>
using namespace std;
vector<int> data_vector;
vector<vector<string>> tasks;
vector<vector<string>> results;
string data_file_name = "";
int data_amount = 0;
string results_file_name = "";

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
    //Time in miliseconds
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

}
void list_operations(int size_of_list){

}
void queue_operations(int size_of_queue){

}

void save_results(string results_file_name){
    cout<<"Saving results"<<endl;
    fstream fout;
    fout.open(results_file_name,ios::out);
    fout<<"data_strucutre,operation,size_of_structure,time_of_operation_ns"<<endl;
    for(int i = 0; i < results.size(); i++){
        fout<<results[i][0]<<","<<results[i][1]<<","<<results[i][2]<<","<<results[i][3]<<endl;
    }
    cout<<"Correctly saved "<<results.size()<<" results"<<endl;

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
                        array_operations(j);
                    }
                }
                cout<<"Done"<<endl;
            }else if(tasks[i][0] == "list"){
                for(int j = start_range; j <= end_range; j += step){
                    for(int k = 0; k < time_repeat; k++){
                        list_operations(j);
                    }
                }
                cout<<"Done"<<endl;
            }else if(tasks[i][0] == "stack"){
                for(int j = start_range; j <= end_range; j += step){
                    for(int k = 0; k < time_repeat; k++){
                        stack_operations(j);
                    }
                }
                cout<<"Done"<<endl;
            }else if(tasks[i][0] == "queue"){
                for(int j = start_range; j <= end_range; j += step){
                    for(int k = 0; k < time_repeat; k++){
                        queue_operations(j);
                    }
                }
                cout<<"Done"<<endl;
            }else{
                cout<<"Cannot recognize "<<tasks[i][0]<<" structure";
            }
        }
    }
    save_results(results_file_name);
    return 0;
}