#include "blocks.cpp"
#include <iostream>
#include <string>
using namespace std;

// 哈夫曼树类
class HuffTree{
protected: // 设置为保护，方便继承
    Node* tree_table; // 哈夫曼树静态链表
    string text; // 从字符串中提取的字符集合，比如aabbbc的字符集合就是abc
    void get_min2(int* min2); // 获取权重最小的两个节点
public:
    HuffTree(const string& content); // 哈夫曼树的构造函数，输入字符串，构建哈夫曼树
    void build_huff_tree(); // 构建哈夫曼树
    void print_huff(); // 打印哈夫曼树
};

// 得到字符集合
string get_chars_set(const string& content){
    string tmp = ""; // 初始化字符集合为空集
    for(size_t i=0;i<content.length();++i){
        if(tmp.find(string(1, content[i]))==string::npos){
            tmp += string(1, content[i]); // 如果没有在字符集合中，就加上这个字符
        }
    }
    // cout << tmp << endl;
    return tmp;
}

// 哈夫曼树构造函数
HuffTree::HuffTree(const string &content){
    text = get_chars_set(content); // 获取字符集合
    tree_table = new Node[2 * text.length() - 1]; // 初始化哈夫曼树的静态二叉树表，前n个位置是每个对应字符，后n-1是n-1次操作中每次操作后创建新节点
    for(size_t i=0;i<content.length();++i){
        char tmp = content[i];
        tree_table[text.find(tmp)].weight++; // 根据字符在字符集合中的位置找到静态表对应的位置，将权重（该字符出现的次数+1）
        // cout << tmp << '\t' << tree_table[text.find(tmp)].weight << endl;
    }
}

// 获取两个权重最小的节点下标
void HuffTree::get_min2(int* min_list){
    // 初始化下标为-1
    int min1 = -1;
    int min2 = -1;
    // 找到权重不为-1的最先遇到的两个节点
    for(size_t i=0;;++i){
        if(tree_table[i].weight!=-1 && min1==-1){
            min1 = i;
        }
        else if(tree_table[i].weight!=-1){
            min2 = i;
            break;
        }
    }
    for(size_t i=0;tree_table[i].weight!=0;++i){
        if(tree_table[i].weight!=-1){
            if(tree_table[i].weight < tree_table[min1].weight){
                // 把旧的最小值赋给min2，保证min2大于等于min1
                min2 = min1;
                min1 = i;
            }
            else if(tree_table[i].weight < tree_table[min2].weight && i!=min1){
                // 如果处于min1和min2之间，并且min1不能等于min2（不然就是同一个节点了）
                min2 = i;
            }
        }
    }
    // 传到输出的数组里
    min_list[0] = min1;
    min_list[1] = min2;
    // printf("min2idx:%d, %d\n", min1, min2);
}

// 构建哈夫曼二叉树
void HuffTree::build_huff_tree(){
    // print_huff();
    for(size_t i=text.length();i<2*text.length()-1;++i){
        int tmp[2];
        get_min2(tmp);
        tree_table[i].weight = tree_table[tmp[0]].weight + tree_table[tmp[1]].weight; // 新节点的权重是最小的两个权重之和
        tree_table[i].left = tmp[0]; // 设置新节点为最小权重的两个节点的父节点
        tree_table[i].right = tmp[1];
        tree_table[tmp[0]].parent = i;
        tree_table[tmp[1]].parent = i;
        tree_table[tmp[0]].weight = -1; // 将最小权重的两个节点的权重设为-1，已经操作过了，不能再进行最小值的比较（要比也是父节点和其他节点比较）
        tree_table[tmp[1]].weight = -1;
        // print_huff();
    }
}

// 打印哈夫曼树表
void HuffTree::print_huff(){
    for(size_t i=0;i<2*text.length()-1;++i){
        printf("%lu\t%d\t%d\t%d\t%d\n", i, tree_table[i].weight, tree_table[i].parent, tree_table[i].left, tree_table[i].right);
    }
}

// 哈夫曼表类，继承哈夫曼树
class EncoderTable : public HuffTree{
private:
    void build_huff_table(); // 构造哈夫曼编译表
    string encoder(size_t idx); // 编译每个字符
public:
    TableBlock* huff_table; // 哈夫曼编译表
    EncoderTable(const string& c): HuffTree(c){ // 哈夫曼表类构造函数，初始化哈夫曼树类
        huff_table = new TableBlock[text.length()]; // 初始化哈夫曼编译表
        build_huff_tree(); // 构建哈夫曼树
        build_huff_table(); // 构建哈夫曼编译表
    }
    void print_huff_table(); // 打印哈夫曼编译表
    string get_text(){return text;} // 返回字符集的公开接口
};

// 构造哈夫曼编译表
void EncoderTable::build_huff_table(){
    for(size_t i=0;i<text.length();++i){
        huff_table[i].key = text[i]; // 键是字符
        huff_table[i].value = encoder(i); // 值是编译的二进制码（0、1字符串）
    }
}

// 编译字符
string EncoderTable::encoder(size_t idx){
    string code = ""; // 初始化每个字符的编译码为空
    for(size_t i = idx;tree_table[i].parent!=-1;i=tree_table[i].parent){
        if(tree_table[tree_table[i].parent].left==i){
            code = "0" + code; // 从叶子节点开始往根节点回溯，如果一个节点的父节点的左孩子为该节点，那么在这个编译码前面加“0”，相当于从根节点开始查找到叶子节点经过的路径，左孩子为0，右孩子为1，只不过从叶子节点开始往回（因为字符都在叶子上好找）
        }
        if(tree_table[tree_table[i].parent].right==i){
            code = "1" + code;
        }
    }
    return code;
}

// 打印哈夫曼编译表
void EncoderTable::print_huff_table(){
    for(size_t i=0;i<text.length();++i){
        cout << huff_table[i].key << '\t' << huff_table[i].value << endl;
    }
}

// 编码字符串，输出哈夫曼编译表、编译后的“二进制码”
void encode(const string& content, string* encode_pair){
    // 构建一个哈夫曼表实例
    EncoderTable huff = EncoderTable(content);
    printf("table:\n");
    huff.print_huff_table();
    printf("tree:\n");
    huff.print_huff();
    // 初始化字符串的编码为空、表的字符串表示为空
    string codes = "";
    string table_string = "";
    // 查表编译
    for(size_t i=0;i<content.length();++i){
        codes += huff.huff_table[huff.get_text().find(content[i])].value;
    }
    // 根据特定规则（如A:01,B:10=>A_01 B_10）输出表的字符串表示（方便传输）
    for(size_t i=0;i<huff.get_text().length();++i){
        table_string += string(1, huff.huff_table[i].key) + "_" + huff.huff_table[i].value + " ";
    }
    table_string.pop_back(); // 删掉最后一个空白字符
    // 放到输出的列表中
    encode_pair[0] = table_string;
    encode_pair[1] = codes;
}

// pair[0]为哈夫曼表字符串，pair[1]为编码内容
string decode(string pair[2]){
    //总体思路是截取哈夫曼表字符串，按照规律截取，即下划线前是源文本字符，后是哈夫曼编码，且哈夫曼编码是以字符型的0与1组成
    //后面是空格然后是下一组，使用tableblock类型的a数组来存储截取的哈夫曼表，将来用来比对。使用judge来挨个读取编码内容并立
    //即进行匹配，得益于哈夫曼表独特的优势不会出现模糊的情况，然后遍历a数组直到匹配，将匹配的字符存到origin_content中
    string origin_content= "";//初始化为空
    string judge= "";
    TableBlock a[100];
    int j= 0;
    for(int i= 0; i<pair[0].size(); i++){
        int n= 2;
        a[j].key= pair[0][i];//录入字符
        while(pair[0][i+n]=='1'||pair[0][i+n]=='0'){
            a[j].value+= pair[0][i+n];//录入编码
            n++;
        }
        i+= n;
        j++;
    }
    for(int i=0; i<pair[1].size(); i++){
        judge+= pair[1][i];
        for(int k=0; k<j; k++){//遍历哈夫曼编码
            if(judge== a[k].value){
                origin_content+= a[k].key;//找到匹配并将其存入origin_content
                judge= "";//还原judge为空
                break;
            }
        }
    }
    return origin_content;
}

// test
// int main(){
//     string list[2];
//     encode("  Hello\nworld!", list);
//     cout << list[0] <<endl << list[1] << endl;
//     cout<<decode(list)<<endl;
//     return 0;
// }