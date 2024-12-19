#include<iostream>
#include<string>
using namespace std;
//我直接将它做成一个管理系统，是针对于字符串的管理系统，因为我们无论是存储图片还是文本，最后都将其转化为字符串进行
//哈夫曼压缩了，这个管理系统实现了对于字符串的增，删，改，查功能，将题目中的查询和更新全部实现
int repeat(int i, int j, int next[], string in_test){
    //repeat函数主要用来递归计算next数组，就是采用最常规的next数组的计算方法
    if(i== 0){
        return 0;
    }else{
        i--;
        i= next[i];
        if(in_test[i]== in_test[j]){
            return i;
        }else{
            i= repeat(i, j, next, in_test);
            return i;
        }
    }
}
string search(string test, string in_test){
    int next[in_test.size()]= {0};
    int i=0, j=1;
    //计算next数组
    while(j<= in_test.size()){
        if(in_test[j]== in_test[i]){
            next[j]= i+1;
            i++;
            j++;
        }else{
            if(i== 0){
                j++;
            }else{
                i= repeat(i, j, next, in_test);
            }
        }
    }
    i=0, j=0;
    int judge= 0;
    string posion= "";
    while(j<= test.size()){
        if(i== in_test.size()){
            judge++;
            posion+= to_string(j-in_test.size());
            posion+="_";
            i= 0;
        }else{
            if(test[j]== in_test[i]){
                i++;
                j++;
            }else{
                if(i== 0){
                    j++;
                }else{
                    i= next[i-1];
                    if(test[j]== in_test[i]){
                        i++;
                    }
                    j++;
                }
            }
        }
    }
    posion+= to_string(judge);
    return posion;
}
string get_total_part(string test, int *p, int count, string in_test){
    if(count== 0){
        return "";
    }else{
        cout<<"该语句存在于以下字符串中，请选择您想进行操作的语句后："<<endl;
    }
    int j= 0;
    string part1, part2;
    string final_all= "";
    for(j=0; j<count; j++){
        if(p[j]-5> 0){
            part1= test.substr(p[j]-5, 5);
            if(p[j]+5< test.size()){
                part2= test.substr(p[j]+in_test.size(), 5);
            }else{
                part2= test.substr(p[j]+in_test.size());
            }
        }else{
            part1= test.substr(0, p[j]);
            if(p[j]+5< test.size()){
                part2= test.substr(p[j]+in_test.size(), 5);
            }else{
                part2= test.substr(p[j]+in_test.size());
            }
        }    
        //cout<<j+1<<"."<<"\033[31m"<<part1<<" "<<"\033[33m"<<part2<<"\033[0m"<<endl;
        final_all+= (to_string(j+1)+ "."+ part1 +"("+in_test+")"+part2+ "\n");
    }
    cout<<final_all;
    return final_all;
}
string add(string test, string in_test, int *p, int count){
    int judge= get_total_part(test, p, count, in_test).size();
    if(judge== 0){
        cout<<"不存在";
        return test;
    }
    cout<<"请输入增加的内容："<<endl;
    string new_test;
    cin>>new_test;
    cout<<"请输入增加的位置："<<endl;
    string number;
    cin>>number;
    for(int i= 0;i<number.size(); i++){
        if(number[i]<47||number[i]>57){
            cout<<"输入错误"<<endl;
            return test;
        }
    }
    if(stoi(number)>count){
        cout<<"输入错误"<<endl;
        return test;
    }
    string part1= test.substr(0, p[stoi(number)-1]);
    string part2= test.substr(p[stoi(number)-1]);
    string end_test= part1+new_test+part2;
    return end_test;
}
string re_move(string test, string in_test, int *p, int count){
    int judge= get_total_part(test, p, count, in_test).size();
    if(judge== 0){
        cout<<"不存在";
        return test;
    }
    cout<<"请输入删除的位置："<<endl;
    string number;
    cin>>number;
    for(int i= 0;i<number.size(); i++){
        if(number[i]<47||number[i]>57){
            cout<<"输入错误"<<endl;
            return test;
        }
    }
    if(stoi(number)>count){
        cout<<"输入错误"<<endl;
        return test;
    }
    string part1= test.substr(0, p[stoi(number)-1]);
        //cout<<part1<<endl;
    string part2= test.substr(p[stoi(number)-1]+in_test.size());
        //cout<<part2<<endl;
    string end_test= part1+part2;
    return end_test;
    
}
int count_num_of_same(string test, string in_test){
    int j=0, k=0;
    string posion= search(test, in_test);
    while(posion[j]!= '\0'){
        if(posion[j]== '_'){
            k= j;
        }
        j++;
    }
    if(k== 0){
        return 0;
    }else{
        string num_of_posion= posion.substr(k+1);
        return (stoi(num_of_posion));
    }
}
void posion_of_number(int *p, string test, string in_test){
    string posion= search(test, in_test);
    string temp_posion= "";
    int j=0,k= 0;
    while(posion[j]!= '\0'){
        if(posion[j]!= '_'){
            temp_posion+= posion[j];
        }else{
            p[k]= stoi(temp_posion);
            k++;
            temp_posion= "";
        }
        j++;
    }
}
int main()
{
    string test= "abxabcabcaby";
    string in_test= "abc";
    //对位置进行切割，找到该字符串出现的所有位置
    int count= count_num_of_same(test, in_test);
    int *p= new int(count);
    posion_of_number(p, test, in_test);
    cout<<"请输入想进行的操作1.查找 2.增加 3.删除 4.退出"<<endl;
    string choice;
    cin>>choice;
    while(choice[0]!= '\0'){
        if(choice== "1"){
            string posion= search(test, in_test);
            if(posion!= "" &&posion!= "0"){
                cout<<"存在"<<endl;
            }else{
                cout<<"不存在"<<endl;
            }
        }else if(choice== "2"){
            int count= count_num_of_same(test, in_test);
            int *p= new int(count);
            posion_of_number(p, test, in_test);
            test= add(test, in_test, p, count);
            cout<<test<<endl;
        }else if(choice== "3"){
            int count= count_num_of_same(test, in_test);
            int *p= new int(count);
            posion_of_number(p, test, in_test);
            test= re_move(test, in_test, p, count);
            cout<<"删除后的字符串为："<<test<<endl;
        }else if(choice== "4"){
            break;
        }else{
            cout<<"输入格式不对"<<endl;
        }
        cout<<"请输入想进行的操作1.查找 2.增加 3.删除 4.退出"<<endl;
        cin>>choice;
    }
    
    return 0;
}