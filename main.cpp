#include<stdio.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <random>
#include <vector>
#include <filesystem>
#include <windows.h>
using namespace std;
vector<int> data_vector;
vector<vector<string>> tasks;
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
    for(int i = 0; i < amount; i++){
        fin>>line;
        //cout<<line<<endl;
       if(!fin.eof()){
            data_vector.push_back(stoi(line));
        }else{
            cout<<"not enought elements"<<endl;
            return false;
        } 
    }
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
    cout<<"tasks: "<<endl;
    for(int i = 0; i < tasks.size(); i++){
        cout<<tasks[i][0]<<" "<<tasks[i][1]<<" "<<tasks[i][2]<<" "<<tasks[i][3]<<" "<<tasks[i][4]<<" "<<endl;
    }
}


int main(){

    // generate_data("data.csv",50);
    // load_data("data.csv",10);
    // for(int i = 0; i <data_vector.size();i++){
    //     cout<<data_vector[i]<<endl;
    // }
    load_config();
    print_config();
    return 0;

}