#include <iostream>
#include <string>
using namespace std;


class Node{
private:
    Node* next;
    string data;
    Node(string d){
        data = d;
    }
    friend class textEditor;
};


class textEditor{
private:
    Node* head;
    int lineCount;

public:
    textEditor();    //Constructor
    void insertAtLineN(string s, int line);      
    void insertAtEnd(string s);
    void deleteAtLineN(int n);
    void moveNtoM(int lineN,int lineM);
    void replaceTextInLineN (string s, int n);
    void printAll();
};


textEditor:: textEditor(){
    head = NULL;
    lineCount = 1;
    int choose;
    while(true){
        cout << "====TEXT EDITOR====" << endl;
        cout << "\n" << endl;
        cout << "Please choose what you want to do" << endl;
        cout << "1. Insert the text into line N" << endl;
        cout << "2. Delete line N" << endl;
        cout << "3. Move the line N into line M" << endl;
        cout << "4. Replace text in line N" << endl;
        cout << "5. Print all lines" << endl;
        cout << "6. Exit" << endl;
        cin >> choose;
        if (choose == 1){
            cout << "Enter the line at which you want the text to be placed: ";
            int line;
            cin >> line;
            cout << "Enter the text: ";
            string s;
            cin.ignore();
            getline(cin,s);
            if(line<=lineCount+1 && line>0){
                insertAtLineN(s,line);
            }
            else{
                cout << "The line is out of bounds, inserting the line at the end" << endl;
                insertAtEnd(s);
            }
        }
        else if (choose == 2){
            int delete_line;
            cout << "Enter the line number you wish to delete: ";
            cin >> delete_line;
            if(delete_line>0 && delete_line <= lineCount)
                deleteAtLineN(delete_line);
            else    
                cout << "The line number is out of bounds, Please enter a number which is within the range" << endl;
        }
        else if (choose == 3){
            int lineN, lineM;
            cout << "Enter the line number which you want to replace: ";
            cin >> lineN;
            cout << "Enter the line number where you want to replace it: ";
            cin >> lineM;
            if(lineN>0 && lineN<= lineCount && lineM>0 && lineM<=lineCount)
                moveNtoM(lineN,lineM);
            else
                cout << "Out of bounds, please enter the correct line number" << endl;
        }
        else if (choose == 4){
            int lineN;
            cout << "Enter the line number which you want to replace: ";
            cin >> lineN;
            cout << "Enter the text which you want the line to be replaced with: ";
            string s;
            cin.ignore();
            getline(cin,s);
            if(lineN > 0 && lineN <= lineCount)
                replaceTextInLineN(s,lineN);
            else
                cout << "Out of bounds, please enter the correct line number" << endl;
        }
        else if (choose == 5){
            printAll();  // Prints all the lines 
        }
        else if (choose == 6){
            cout << "Thankyou for using the Text Editor" << endl;
            break;  // exits the while loop
        }
        else{
            cout << "The entered number is not valid, Please choose numbers between 1-6" << endl;
        }
    }
}


void textEditor:: insertAtEnd(string s){
    Node* new_Node = new Node(s);
    if(head==NULL){
        new_Node->next = head;
        head = new_Node;
        lineCount++;
        return;
    }
    Node* temp = head;
    while(temp->next!=NULL){
        temp = temp -> next;
    }
    new_Node -> next = temp->next;
    temp->next = new_Node;
    lineCount++;
}


void textEditor:: insertAtLineN(string s, int line){
    if (line == 1){
        Node* new_node = new Node(s);
        new_node -> next = head; 
        head = new_node; 
        lineCount++;
    }
    else if(line <= lineCount){
        Node* temp = head;
        Node* new_Node = new Node(s);
        for(int i = 0 ; i < (line-2) ; i++){
            temp = temp-> next;
        }
        new_Node->next = temp->next;
        temp -> next = new_Node;
        lineCount++;
    }
    else{
        cout << "Out of bounds. Inserting at the end" << endl;
        insertAtEnd(s);
    }
}


void textEditor:: deleteAtLineN (int n){
    if(head == NULL){
        cout << "Nothing to delete. It's already empty" << endl;
    }
    else if(n == 1 && lineCount == 1){
        Node* temp = head;
        free(temp);
        head = NULL;
        lineCount--;
    }
    else if (n==1 && lineCount>1){
        Node* temp = head;
        head = temp->next;
        free(temp);
        lineCount--;
    }
    else if(n>1 && n<=lineCount){
        Node* temp = head;
        for (int i = 1 ; i <= n-2 ; i++){
            temp = temp -> next;
        }
        Node* after = temp->next->next;
        free(temp->next);
        temp->next = after;
        lineCount--;
    }
    else
        cout << "Out of bounds. Please enter correct value of the line number you want to delete" << endl;
}


void textEditor:: moveNtoM(int n , int m){
    if(n==1 && (m>0 && m <= lineCount)){
        Node* temp = head;
        string s = temp -> data;
        head = temp -> next;
        free(temp);
        lineCount--;
        insertAtLineN(s,m-1);
    }
    else if (n <= lineCount && (m>0 && m <= lineCount)){
        Node* temp = head;
        for(int i = 0 ; i < n-2 ; i++){
            temp = temp -> next;
        }
        string s = temp -> next -> data;
        temp -> next = temp -> next -> next;
        free(temp->next);
        lineCount--;
        insertAtLineN(s,m-1);
    }
    else{
        cout << "Out of bounds. Please enter the correct line a" << endl;
    }
}


void textEditor:: replaceTextInLineN(string s, int n){
    if (n<1 || n>lineCount){
        cout << "Out of bounds. Please enter the correct line number you want to replace" << endl;
    }
    else{
        Node* temp = head;
        for (int  i = 0 ; i <= n-2 ; i++){
            temp = temp->next;
        }
        string beforeReplace = temp->data;
        temp->data = s;
    }  
}


void textEditor:: printAll(){
    if(head == NULL){
        cout << "The text editor is empty, please add some text" << endl;
    }

    Node* temp = head;
    while(temp!=NULL){
        cout << temp -> data << endl;
        temp = temp -> next;
    }
    cout << "\n";
}


int main (){
    textEditor obj; // instantiating an object, which will run the constructor created
    return 0;
}