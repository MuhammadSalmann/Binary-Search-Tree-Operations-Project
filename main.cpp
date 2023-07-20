#include <iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std;

class Node {
    int value;   Node* right;   Node* left;
    public:
    Node() { value=0;  right = left = NULL; }
		void setvalue(int value) { this->value = value; }
		int getvalue()  { return value; }
		void setrightNode(Node* right) {  this->right=right; }
		Node* getrightNode() { return right; }
        void setleftNode(Node* left) {  this->left=left; }
		Node* getleftNode() { return left; }
};

class BST{
    Node* root;
    Node* current;
    Node* lastcurrent;
    int nov;
    public:
    BST() { root = current = lastcurrent = NULL;  nov=0; }
    Node* GetRoot() { current = root;  return current; }

    void CreateTree() {
        int size, val;
        cout<<"How Many Nodes You Want In the Tress:  ";   cin>>size;
        for(int i = 1;i <= size; i++) {
            cout<<"Enter Element#"<<i<<" :  ";  cin>>val;    Insertion(val);
        }
    }

    void Insertion(int val) {
            Node* NN = new Node;    NN->setvalue(val);
            NN->setleftNode(NULL);  NN->setrightNode(NULL);
        if(root == NULL) { root = NN; }
        else {
            current = root;
            while(current != NULL) {
                lastcurrent = current;
                if(val < current->getvalue()) { current = current->getleftNode(); }
                else {  current = current->getrightNode();  }
            }
            if(lastcurrent->getvalue() < val) { lastcurrent->setrightNode(NN); }
            else {  lastcurrent->setleftNode(NN);  }   
        }
    }

    Node* MinValue(Node* Root) {
        if(Root != NULL) {
            int min;
            while(Root->getleftNode() != NULL) {
                Root = Root->getleftNode();
            }
            min = Root->getvalue();
            cout<<"\nMinimum Value is:  "<<min<<endl; 
            return Root;
        }
        else { cout<<"\nCreate the Tree First\n";  getch();  system("cls");  }
    }

    Node* MaxValue(Node* Root) {
        if(Root != NULL) {
            int max;
            while(Root->getrightNode() != NULL) {
                Root = Root->getrightNode();
            }
            max = Root->getvalue();
            cout<<"\nMaximum Value is:  "<<max<<endl;
            return Root;
        }
        else { cout<<"\nCreate the Tree First\n";  getch();  system("cls");  }
    }

    int Height(Node* Root) {
        if (Root != NULL) {
            int rightcounter=0, leftcounter=0;
            current = Root;
            while(current->getleftNode() != NULL) {
                current = current->getleftNode();
                leftcounter++;
            }
            current = Root;
            while(current->getrightNode() != NULL) {
                current = current->getrightNode();
                rightcounter++;
            }
            if(leftcounter >= rightcounter) { return leftcounter; }
            else return rightcounter;
        }
        else  { cout<<"\nCreate the Tree First\n";  getch();  system("cls");  }
    }

    void Deletion() {
        current = root;
        InOrder(current);
		Search();
        if(root != NULL) {
        //**********ROOT***************
        if(current == root) {

            if(current->getleftNode() == NULL && current->getrightNode()== NULL) {
                root = NULL;
            }

            else if(current->getleftNode() == NULL) {
                root = current->getrightNode();
                current = NULL;
            }
            else if(current->getrightNode() == NULL) {
                root = current->getleftNode();
                current = NULL;
            }
            else {
                Node* temp;  Node* newcurrent = root->getrightNode();
                if(newcurrent->getleftNode() == NULL ) {
                    newcurrent->setleftNode(root->getleftNode());
                    root = newcurrent;   delete current;
                }
                else {
                    temp = MinValue(newcurrent->getleftNode());
                    root->setvalue(temp->getvalue()); 

                while(newcurrent->getleftNode() != temp) {
                    newcurrent = newcurrent->getleftNode();
                }
                if(temp->getleftNode() == NULL && temp->getrightNode() == NULL) {
                    newcurrent->setleftNode(NULL);
                }
                else if(temp->getleftNode() == NULL) { 
                        newcurrent->setleftNode(temp->getrightNode());
                        temp->setrightNode(NULL);
                }
                else if((temp->getrightNode() == NULL)) { 
                        newcurrent->setleftNode(temp->getleftNode()); 
                        temp->setleftNode(NULL);  
                }
                }
                
            }
        }
        //********NODES***************
		else if(current->getleftNode() == NULL && current->getrightNode()== NULL) { 
            if(lastcurrent->getleftNode() == current)  lastcurrent->setleftNode(NULL); 
            if(lastcurrent->getrightNode() == current)  lastcurrent->setrightNode(NULL);
		}
		//Case 2: One child 
		else if(current->getleftNode() == NULL) {

            if(lastcurrent->getleftNode() == current) {
                lastcurrent->setleftNode(current->getrightNode());
                //delete current;
            }
            else {  
                lastcurrent->setrightNode(current->getrightNode()); 
            }
		}
		else if(current->getrightNode() == NULL) {

            if(lastcurrent->getleftNode() == current) {
                lastcurrent->setleftNode(current->getleftNode());
            }
            else {  
                lastcurrent->setrightNode(current->getleftNode()); 
            }
		}
		// case 3: 2 children     
		else { 
            Node* temp;  Node* newcurrent = current->getrightNode();   
                temp = MinValue(newcurrent->getleftNode());
                current->setvalue(temp->getvalue()); 

                while(newcurrent->getleftNode() != temp) {
                    newcurrent = newcurrent->getleftNode();
                }
                if(temp->getleftNode() == NULL && temp->getrightNode() == NULL) {
                    newcurrent->setleftNode(NULL);
                }
                else if(temp->getleftNode() == NULL) { 
                        newcurrent->setleftNode(temp->getrightNode());
                        temp->setrightNode(NULL);
                }
                else if((temp->getrightNode() == NULL)) { 
                        newcurrent->setleftNode(temp->getleftNode()); 
                        temp->setleftNode(NULL);  
                }
            }
        } 
        current = root;
        InOrder(current);
    }

    void DisplayMenu() {
        char choice;
        if(root != NULL) {
            do {
        cout<<"1-> PreOrder Display\n"
              "2-> InOrder Display\n"
              "3-> PostOrder Display\n"
              "4-> Even | Root | Odd Display\n"
              "5-> Back to Main Menu\n"
              "Choice = ";   cin>>choice;   system("cls");   
        switch(choice) {
            case '1': PreOrder(root);     getch();    system("cls");    break;
            case '2': InOrder(root);      getch();    system("cls");    break;
            case '3': PostOrder(root);    getch();    system("cls");    break;
            case '4': Even(root->getleftNode());  cout<<root->getvalue()<<" ";   Odd(root->getrightNode());     getch();    system("cls");    break;
            default:    system("cls");
        }
        }while(choice != '5');
        }
        else { cout<<"\nCreate the Tree First\n";  getch();  system("cls");  }
    }

    void PreOrder(Node* Root) {
        if(Root != NULL) {
            cout<<Root->getvalue()<<" ";
            PreOrder(Root->getleftNode());
            PreOrder(Root->getrightNode());
        }
    }

    void Even(Node* Root) {
        if(Root != NULL) {
            Even(Root->getrightNode());
            if(Root->getvalue() % 2 == 0) {
                cout<<Root->getvalue()<<" ";
            }
            Even(Root->getleftNode());
        }
    }

    void Odd(Node* Root) {
        if(Root != NULL) {
            Odd(Root->getleftNode());
            if(Root->getvalue() % 2 != 0) {
                cout<<Root->getvalue()<<" ";
            }
            Odd(Root->getrightNode());

        }
    }

    void InOrder(Node* Root) {
        if(Root != NULL) {
            InOrder(Root->getleftNode());
            cout<<Root->getvalue()<<" ";
            InOrder(Root->getrightNode());
        }
    }

    void PostOrder(Node* Root) {
        if(Root != NULL) {
            PostOrder(Root->getleftNode());
            PostOrder(Root->getrightNode());
            cout<<Root->getvalue()<<" ";
        }
    }

    int Search() {
        int flag=0;
        if(root != NULL) {
            current = root;    lastcurrent = NULL;
            int s;   cout<<"\nElement:  ";   cin>>s;
            if(current->getvalue() == s)  { cout<<"\nFound!!!"; flag++;  goto p; }
            lastcurrent = current;
            while(current != NULL) {
                if(s < current->getvalue()) {
                    current = current->getleftNode();
                    if(current != NULL) {
                        if(current->getvalue() == s) {   cout<<"\nFound!!!"; flag++; break; }
                        lastcurrent = current;
                    }
                    else{   cout<<"\nNot Found!!!";  flag++;  }
                }
                else {
                    current = current->getrightNode();
                    if(current != NULL) {
                        if(current->getvalue() == s) { cout<<"\nFound!!!"; flag++; break; }
                        lastcurrent = current;
                    }
                    else { cout<<"\nNot Found!!!";  flag++;  }
                }
            }
            p:
            if(flag == 0) { cout<<"\nNot Found!!!"; }     
        }
        else { cout<<"\nCreate the Tree First\n";  getch();  system("cls");  }
        
    }
};
int main() {
    BST T;  char choice;
    while(1) {
        cout<<"\n\tXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"                           
		      "\n\t\t       BST Operations         \n"
	          "\n\tXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n"
		      "\n\t\t        Main Menu               \n"
		      "\n\tXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n"
		      "\t1-> Insertion\n"
              "\t2-> Deletion\n"
              "\t3-> Display\n"
              "\t4-> Search\n"
              "\t5-> Minimum Value\n"
              "\t6-> Maximum Value\n"
              "\t7-> Height\n"
              "\t8-> Exit\n"
              "\t\t\t Choice = ";   cin>>choice;  system("cls");
            switch(choice) {
                case '1':   T.CreateTree();     break;
                case '2':   T.Deletion();       break;
                case '3':   T.DisplayMenu();    break;
                case '4':   T.Search();         break;
                case '5':   T.MinValue(T.GetRoot());       break;
                case '6':   T.MaxValue(T.GetRoot());       break;
                case '7':   cout<<"Height of Tree:  "<<T.Height(T.GetRoot());       break;
                case '8':   exit(0);
                deafult:        system("cls");
            }
    }
    return 0;
}