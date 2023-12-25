#include <iostream>
#include <fstream>
#include <string>
#include<iomanip>
#include <algorithm>
#include <vector>
#include <sstream>
#include <utility>
#include <stdlib.h>
//#include <curses.h>
using namespace std;

int Searchh(int);
struct node *insert_into_FP_Tree(int,struct node *);

int Total_item=-1;
vector<pair<string, int>> words_freq;
vector<pair<int,int>> words_freq1;
vector<pair<int, int>> sorted_transaction;
struct node *root=NULL;

// FP-Tree structure
struct node
{
public:
    
    int item_name;
    int count;
    node * parents;
    node * child;
    node * sibling;
    node * same_item;
    
    node(int s) //constructor for node
    {
        item_name=s;
        count=1;
        parents=NULL;
        child=NULL;
        sibling=NULL;
        same_item=NULL;
        
    }
};
int count_nodes(node* root) {
    if (root == nullptr) {
        return 0;
    }

    int nodecount = 1; // count the root node
    node* child = root->child;
    while (child != nullptr) {
        nodecount += count_nodes(child);
        child = child->sibling;
    }

    return nodecount;
}



struct header
{
public:
    int item;
    int count;
    node * link=NULL;
    
};

struct header Header_Table[1050];
//vector<struct header> Header_Table;


// helper function to compare two pairs by their second element( frequency
bool compare_frequency(const pair<string, int>& a, const pair<string, int>& b)
{
    return a.second > b.second;
}

bool sort_value(const pair<string, int>& a, const pair<string, int>& b)
{
    return a.first > b.first;
}




void freqq(string str) // function to get frequency of each element and sort in descending order
{
    
        stringstream ss(str);
        string word;

        while (getline(ss, word, ' ')) {
            // remove leading and trailing whitespaces from the word
            word.erase(0, word.find_first_not_of(" \n\r\t"));
            word.erase(word.find_last_not_of(" \n\r\t") + 1);
            
            // check if the word is already in the vector
            bool found = false;
            for (int i = 0; i < words_freq.size(); i++) {
                if (words_freq[i].first == word) {
                    words_freq[i].second++;
                    found = true;
                    break;
                }
            }
            // if the word is not in the vector, add it with a frequency of 1
                   if (!found) {
                       words_freq.push_back(make_pair(word, 1));
                   }
               }

               // sort the vector in descending order by frequency
               sort(words_freq.begin(), words_freq.end(), compare_frequency);

               // print the words and their frequencies
               for (int i = 0; i < words_freq.size(); i++) {
                   cout <<" |"<< words_freq[i].first << "| :-> |" << words_freq[i].second <<"|"<< endl;
                   Total_item++;
               }
    cout<<"Total no of items:- "<<Total_item<<endl;


}


int searchh(int item)
{
    for(int i=0;i<words_freq.size();i++)
    {
        if(Header_Table[i].item==item)
        {
            return i;
        }
    }
    return -1;
}






struct node * insert_into_FP_Tree(int j,struct node *temp_root,vector<int> a)
{
    struct node *temp1=NULL,*temp2=NULL,*temp3=NULL,*temp4=NULL;
    
        if(temp_root->child==NULL)
        {
            temp1=new node(a[j]);
            temp_root->child=temp1;
            temp1->parents=temp_root;
            Header_Table[j].link=temp1;
        }
        else
        {
            temp2=temp_root->child;
            while(temp2!=NULL)
            {
                if(temp2->item_name==a[j])
                {
                    temp2->count+=1;
                    Header_Table[searchh(temp2->item_name)].count+=1;
                    return temp2;
                }
                else
                {
                    temp3=temp2;
                    temp2=temp2->sibling;
                }
            }
            if(temp2==NULL)
            {
                temp1=new node(a[j]);
                temp1->parents=temp_root;
                temp3->sibling=temp1;
            }
        }
    if(Header_Table[a[j]].link!=NULL)
    {
        temp4=Header_Table[a[j]].link;
        temp1->same_item=temp4;
        Header_Table[a[j]].link=temp1;
    }
    Header_Table[a[j]].count+=1;
    return temp1;
}




int main()
{
    time_t start,end;
    time(&start);
    ios_base::sync_with_stdio(false);
    
    struct node *temp_root;
    
    ifstream innfile("kosarak.txt");
    int a=0;
    string line,s;
    if(innfile.is_open())
    {
        
            if(getline(innfile,line))
            {
                s=s+line;
                a++;
            }
            
        
        innfile.close();
    }
    else
        cout<<"unable to open file"<<endl;
    
    
    cout<<"Total no. of transaction="<<a<<endl<<endl;
    cout<<"Calculating frequency of each item...Finished"<<endl<<endl<<"Arranging Items in Descending Order with frequency..."<<endl;
    cout<<" |ITEMS|:->|FREQ|"<<endl<<endl;
    
    freqq(s);
    cout<<"please ENTER to header process";
    //cin>>a;
    
    for(int i=0;i<words_freq.size()-1;i++)
    {
        header * H= new header();
        H->item=stoi(words_freq[i].first);
        H->count=0;
        
        Header_Table[i]=*H;
    }
    
    cout<<"Elements in header table"<<endl<<endl;
    cout<<"|Items|->|freq|"<<endl;
    for(int i=0;i<words_freq.size();i++)
    {
        cout<<"|"<<Header_Table[i].item<<"|:->|"<<Header_Table[i].count<<"|"<<endl;
    }
    
    cout<<"-----------next process----------"<<endl;
    
    
    
    /*
     for(int i=0;i<Total_item-1;i++)
     {
     cout<<"|"<<words_freq1[i].first<<"|->|"<<words_freq1[i].second<<"|"<<endl;
     }
     */
    
    
    
    cout<<"----------------transactions item-----------------"<<endl;
    
   // cin>>a;
    
    
    
    ifstream infile("kosarak.txt");
    vector<pair<int,string>> str_digits;
    string str_digit;
    int i=0;
    
    if(infile.is_open())
    {
        while(getline(infile, str_digit))
            //if(getline(infile, str_digit))
            {
                pair<int,string> p(i,str_digit);
                str_digits.push_back(p);
                i++;
            }
        infile.close();
    }
    root=new node(0);
    vector<int> arr;
    for(int i=0;i<str_digits.size();i++)
    {
        stringstream ss(str_digits[i].second);
        int num;
        while (ss >> num)
        {
            arr.push_back(num);
        }
        
        vector<int> a(870,-1);
        
        //cout<<"Transaction "<<i<<"Done!"<<endl;
       // cout<<"|Items|->|index|"<<endl;
        
        
        
        for(int x=0;x<arr.size();x++)
        {
            for(int y=0;y<words_freq.size();y++)
            {
                if(arr[x]==Header_Table[y].item)
                {
                    a[y]=arr[x];
                }
            }
        }
        
        vector<int> a1;
        
        
        
        for(int ii=0;ii<a.size();ii++)
        {
            if(a[ii]!=-1)
            {
                a1.push_back(a[ii]);
            }
        }
        
        

         temp_root=root;
         
         for(int j=0;j<a1.size();j++)
         {
         temp_root=insert_into_FP_Tree(j,temp_root,a1);
         }
        
        cout<<endl;
         
     
        // sorted_transaction.clear();
         arr.clear();
         a1.clear();
         cout<<endl;
    }
        
         time(&end);
         double taken= double(end-start);
         //cout<<endl<<endl;
         cout<<"time taken = "<<fixed<<taken<< setprecision(5);
         cout<<"sec"<<endl;
        
        
         for(int j=0;j<arr.size();j++)
         {
         cout<<j<<"->"<<arr[j]<<endl;
         }
        
        int num_nodes = count_nodes(root);
        cout << "Number of nodes: " << num_nodes << endl;

        return 0;
}
