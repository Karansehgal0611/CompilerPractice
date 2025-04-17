#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

vector<char> terms;
vector<char> nonTerms;

bool inTerms(char x){
    for(int i=0; i<terms.size(); i++){
        if(terms[i] == x) return true;
    }
    return false;
}

bool innonTerms(char x){
    for(int i=0; i<nonTerms.size(); i++){
        if(nonTerms[i] == x) return true;
    }
    return false;
}

int findindex(char symbol, string identity){
    if(identity=="term" || identity=="Term"){
        for(int i=0; i<terms.size(); i++){
            if(terms[i] == symbol) return i;
        }
    }
    else if(identity == "nonterm" || identity =="Nonterm" || identity=="nonTerm"){
        for(int i=0; i<nonTerms.size(); i++){
            if(nonTerms[i] == symbol) return i;
        }
    }
    return -1;
}

bool isfirst(char term, char nonterm, vector<vector<char> > first){
    int index;
    for(int i=0; i<nonTerms.size(); i++){
        if(nonTerms[i] == nonterm) index = i;
    }

    for(int i=0; i<first[index].size(); i++){
        if(first[index][i] == term) return true;
    }
    return false;
}

bool isfollow(char term, char nonterm, vector<vector<char> > follow){
    int index;
    index = findindex(nonterm, "nonterm");

    for(int i=0; i<follow[index].size(); i++){
        if(follow[index][i] == term) return true;
    }
    return false;
}

void printStack(vector<char> temp){
    int size = temp.size();
    for(int i=size-1; i>=0; i--){
        cout<<temp[i];
    }
}
void printInBuffer(string input, int ptr){
    int size = input.length();
    for(int i=ptr; i<size; i++){
        cout<<input[i];
    }
}

int main(){
    int prodNum = 8;
    char start = 'E';
    int startSym;
    int temp, templhs;

    string productions[8][2] = {
                                {"E", "TA"},
                                {"A", "*TA"},
                                {"A", "^"},
                                {"T", "FB"},
                                {"B", "+FB"},
                                {"B", "^"},
                                {"F", "(E)"},
                                {"F", "i"}
                             };

    for(int i=0; i<prodNum; i++){
        if(!innonTerms(productions[i][0][0])) nonTerms.push_back(productions[i][0][0]);
    }

    for(int i=0; i<prodNum; i++){
        temp = productions[i][1].length();
        for(int j=0; j<temp; j++){
            if(!innonTerms(productions[i][1][j]) && !inTerms(productions[i][1][j])){
                terms.push_back(productions[i][1][j]);
            }
        }
    }
    startSym = findindex(start, "nonterm");
    cout<<"terms:"<<endl;
    for(int i=0; i<terms.size(); i++){
        cout<<terms[i]<<" ";
    }
    cout<<endl;
    cout<<"nonterms:"<<endl;
    for(int i=0; i<nonTerms.size(); i++){
        cout<<nonTerms[i]<<" ";
    }
    cout<<endl;

    terms.push_back('$');

    vector<vector<char> > first(nonTerms.size());
    vector<vector<char> > follow(nonTerms.size());

    bool nochange = false;
    while(!nochange){
        nochange = true;
        for(int i=prodNum-1; i>=0; i--){
            if(inTerms(productions[i][1][0])){
                if(!isfirst(productions[i][1][0], productions[i][0][0], first)){
                    templhs = findindex(productions[i][0][0], "nonterm");
                    first[templhs].push_back(productions[i][1][0]);
                    nochange = false;
                }
            }
            else if(innonTerms(productions[i][1][0])){
                templhs = findindex(productions[i][0][0], "nonterm");
                temp = findindex(productions[i][1][0], "nonterm");
                for(int j=0; j<first[temp].size(); j++){
                    if(!isfirst(first[temp][j], nonTerms[templhs], first)){
                        first[templhs].push_back(first[temp][j]);
                        nochange = false;
                    }
                }
            }
        }
    }
    for(int i=0; i<nonTerms.size(); i++){
        cout<<nonTerms[i]<<" firsts : ";
        for(int j=0; j<first[i].size(); j++){
            cout<<first[i][j]<<" ";
        }
        cout<<endl;
    }

    follow[startSym].push_back('$');

    bool nochange_follow = false;
    while(!nochange_follow){
        nochange_follow = true;
        for(int i=0; i<prodNum; i++){
            string rhs = productions[i][1];
            for(int j=0; j<rhs.length(); j++){
                if(innonTerms(rhs[j])){
                    templhs = findindex(productions[i][0][0], "nonterm");
                    if(j+1 < rhs.length()){
                        if(inTerms(rhs[j+1])){
                            if(!isfollow(rhs[j+1], rhs[j], follow)){
                                follow[findindex(rhs[j], "nonterm")].push_back(rhs[j+1]);
                                nochange_follow = false;
                            }
                        }
                        else if(innonTerms(rhs[j+1])){
                            int nextNonTermIndex = findindex(rhs[j+1], "nonterm");
                            for(char f : first[nextNonTermIndex]){
                                if(f != '^' && !isfollow(f, rhs[j], follow)){
                                    follow[findindex(rhs[j], "nonterm")].push_back(f);
                                    nochange_follow = false;
                                }
                            }
                            if(isfirst('^', rhs[j+1], first)){
                                for(char f : follow[templhs]){
                                    if(!isfollow(f, rhs[j], follow)){
                                        follow[findindex(rhs[j], "nonterm")].push_back(f);
                                        nochange_follow = false;
                                    }
                                }
                            }
                        }
                    }
                    else {
                        for(char f : follow[templhs]){
                            if(!isfollow(f, rhs[j], follow)){
                                follow[findindex(rhs[j], "nonterm")].push_back(f);
                                nochange_follow = false;
                            }
                        }
                    }
                }
            }
        }
    }

    for(int i=0; i<nonTerms.size(); i++){
        cout << nonTerms[i] << " follows : ";
        for(int j=0; j<follow[i].size(); j++){
            cout << follow[i][j] << " ";
        }
        cout << endl;
    }

    vector<vector<int> > parseTable(nonTerms.size(), vector<int>(terms.size(), -1));
    int termindex;
    int followtermindex;
    int nontermindex;
    for(int i=0; i<nonTerms.size(); i++){
        for(int j=0; j<first[i].size(); j++){
            if(first[i][j] != '^'){
                termindex = findindex(first[i][j], "term");
                nontermindex = i;
                for(int k=0; k<prodNum; k++){
                    if(findindex(productions[k][0][0], "nonterm") == nontermindex){
                        if(innonTerms(productions[k][1][0])){
                            if(isfirst(first[i][j], productions[k][1][0], first)){
                                parseTable[nontermindex][termindex] = k;
                            }
                        }
                        else if(inTerms(productions[k][1][0])){
                            if(productions[k][1][0] == first[i][j]){
                                parseTable[nontermindex][termindex] = k;
                            }
                        }
                    }
                }
            }
            else if(first[i][j] == '^'){
                nontermindex = i;
                for(int k=0; k<follow[i].size(); k++){
                    followtermindex = findindex(follow[i][k], "term");
                    for(int l=0; l<prodNum; l++){
                        if(findindex(productions[l][0][0], "nonterm")==nontermindex && productions[l][1][0]=='^'){
                            parseTable[nontermindex][followtermindex] = l;
                        }
                    }
                }
            }
        }
    }

    for(int i=0; i<nonTerms.size(); i++){
        for(int j=0; j<terms.size(); j++){
            cout<<parseTable[i][j]<<" ";
        }
        cout<<endl;
    }

    string input = "(i*i)+i*(i+i)";
    input += '$';

    vector<char> mystack;
    mystack.push_back('$');
    mystack.push_back(start);

    bool check = true;
    bool valid = false;
    int ptr = 0;

    cout<<"stack"<<"     "<<"input buffer"<<endl;
    while(check && !valid){
        if(inTerms(mystack.back())){
            if(mystack.back() == '^'){
                mystack.pop_back();
            } else if(mystack.back() == input[ptr]){
                mystack.pop_back();
                ptr++;
            } else {
                check = false;
            }
        } else if(innonTerms(mystack.back())){
            int x = findindex(mystack.back(), "nonterm");
            int y = findindex(input[ptr], "term");
            if(parseTable[x][y] != -1){
                mystack.pop_back();
                string temp = productions[parseTable[x][y]][1];
                for(int i = temp.length() - 1; i >= 0; i--){
                    mystack.push_back(temp[i]);
                }
            } else {
                check = false;
            }
        }

        printStack(mystack);
        cout<<"       ";
        printInBuffer(input, ptr);
        cout<<endl;

        if(mystack.back() == '$' && input[ptr] == '$') valid = true;
    }

    if(valid) cout<<"string is valid!"<<endl;
    else cout<<"string is invalid!"<<endl;

    return 0;
}
