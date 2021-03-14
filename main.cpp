#include<stdio.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <random>
#include <vector>
#include <filesystem>
#include <windows.h>
#include <ctime>
using namespace std;
vector<int> data_vector;
vector<vector<string>> tasks;
vector<vector<string>> results;
string data_file_name = "";
int data_amount = 0;
string results_file_name = "";

void generate_data(string file_name,int amount){
    fstream fout;
    fout.open("data.csv",ios::out);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-1000000, 1000000);
    for(int i = 0; i < amount; i++){
        fout<<dis(gen)<<"\n";
    }
}

bool load_data(string file_name, int amount){
    ifstream fin;
    fin.open(file_name,ios::in);
    if(fin.fail()){
        cout<<"file not exist"<<endl;
        return false;
    }
    string line;
    int data_loaded = 0;
    for(int i = 0; i < amount; i++){
        fin>>line;
        if(!fin.eof()){
            data_vector.push_back(stoi(line));
        }else{
            cout<<"not enought elements"<<endl;
            return false;
        } 
        data_loaded++;
    }
    cout<<"data laoded"<<data_loaded<<endl;
    return true;
}

bool load_config(){
    ifstream fin;
    fin.open("config.ini",ios::in);
    if(fin.fail()){
        cout<<"config not exist"<<endl;
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
    //CREATE OPERATION
    clock_t t_start = clock();
    int *test_array = new int[size_of_array];
    for(int i = 0; i < size_of_array; i++){
        test_array[i] = data_vector[i];
    }
    clock_t t_end = clock();
    //Time in miliseconds
    double t_create = 1000*(t_end - t_start)/CLOCKS_PER_SEC;
    cout<<t_start<<endl;
    cout<<t_end<<endl;
    cout<<t_create<<endl;
    vector<string> this_restult = {"array","create",to_string(size_of_array),to_string(t_create)};
    results.push_back(this_restult);
    //SEARCH OPERATION
    srand(time(NULL));
    int random_index = rand() % size_of_array;
    int searched_value = data_vector[random_index];
    bool found = false;
    t_start = clock();
    for(int i = 0; i < size_of_array; i++){
        if(test_array[i] == data_vector[i]){
            t_end = clock();
            found = true;
            break;
        }
    }
    if(!found){
        cout<<"Array searching error"<<endl;
        t_end = clock();
    }
    double t_search = 1000*(t_end - t_start)/CLOCKS_PER_SEC;
    this_restult = {"array","search",to_string(size_of_array),to_string(t_search)};
    results.push_back(this_restult);
    //PUT OPERATION
    random_index = rand() % size_of_array;
    t_start = clock();
    test_array[random_index] = 0;
    t_end = clock();
    test_array[random_index] = data_vector[random_index];
    double t_put = 1000*(t_end - t_start)/CLOCKS_PER_SEC;
    this_restult = {"array","put",to_string(size_of_array),to_string(t_put)};
    results.push_back(this_restult);
    //ADD OPERATION
    int *temp_test_array = test_array;
    int random_value = rand() % 1000000;
    t_start = clock();
    int *temp_array = new int[(size_of_array+1)];
    for(int i = 0;i < size_of_array; i++){
        temp_array[i] = test_array[i];
    }
    temp_array[size_of_array] = random_value;
    test_array = temp_array;
    delete temp_array;
    t_end = clock();
    double t_add = 1000*(t_end - t_start)/CLOCKS_PER_SEC;
    test_array = temp_test_array;
    this_restult = {"array","add",to_string(size_of_array),to_string(t_add)};
    results.push_back(this_restult);
    //DELETE OPERATION
    random_index = rand() % size_of_array;
    random_index = 1;
    t_start = clock();
    temp_array = new int[(size_of_array-1)];
    for(int i = 0;i < random_index; i++){
        temp_array[i] = test_array[i];
    }
    for(int i = random_index+1; i<size_of_array;i++){
        temp_array[(i-1)] = test_array[i];
    }
    test_array = temp_array;
    t_end = clock();
    double t_delete = 1000*(t_end - t_start)/CLOCKS_PER_SEC;
    this_restult = {"array","delete",to_string(size_of_array),to_string(t_delete)};
    results.push_back(this_restult);
}

void save_results(string results_file_name){
    fstream fout;
    fout.open(results_file_name,ios::out);
    fout<<"data_strucutre,operation,size_of_structure,time_of_operation_ns"<<endl;
    cout<<"results size: "<<results.size()<<endl;
    for(int i = 0; i < results.size(); i++){
        fout<<results[i][0]<<","<<results[i][1]<<","<<results[i][2]<<","<<results[i][3]<<endl;
    }
}

int main(){
    load_config();
    if(!load_data(data_file_name,data_amount)){
        generate_data(data_file_name,data_amount);
        load_data(data_file_name,data_amount);
    }
    // for(int i = 0; i <data_vector.size();i++){
    //     cout<<data_vector[i]<<endl;
    // }
    //print_config();
    array_operations(999999);
    save_results(results_file_name);
    return 0;

}