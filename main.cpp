#include <bits/stdc++.h>
#include <cstdlib>
#include <fstream>
# include<windows.h>
# include<time.h>
using namespace std;
#define size1 26
void ClearConsoleToColors(int,int);
void ClearScreen()
    {
    int n;
    for (n = 0; n < 10; n++)
      printf( "\n\n\n\n\n\n\n\n\n\n" );
    }


struct sales_info{
    string fname;
    string lname;
    int age;
    int quantity;
    struct sales_info* next;
};


struct medic_name{
    string name;
    medic_name *next;
};

struct diseases{
    string d_name;
    medic_name* medics;
    diseases* next;
};


struct info{
    string med_name;
    string mfd;
    int quantity;
    string expiry_date;
    int cost;
    info* next;
};

diseases* data = NULL;

struct Node{
    Node *name[size1];
    info* m;
    sales_info*k;
    bool isend;
};

void searchmedicine_bystring(Node*, string, int);

Node* createNode() {
     Node*tmp=new Node;
     tmp->isend=false;
     for(int i=0;i<size1;i++){
        tmp->name[i]=NULL;
     }
     return tmp;
}

info* insert_med_info(string name, int q, string mfg, string expiry,int c){
    info*m=new info;
    m->med_name=name;
    m->quantity=q;
    m->mfd=mfg;
    m->expiry_date=expiry;
    m->cost=c;
    return m;
}

sales_info* insert_sales_info(struct sales_info* root,string f, string l, int age, int q){

    sales_info* m=new sales_info;
    m->age = age;
    m->fname = f;
    m->lname = l;
    m->quantity=q;
    if(root==NULL){
        root=m;
        root->next=NULL;
    }
    else{
        m->next=root;
        root=m;
    }
    return root;
}

Node* Insert(struct Node* root,struct info* node,string key){

    Node* tmp=root;
    for(int i=0;i<key.length();i++) {
        int index=key[i]-'a';
        if(!tmp->name[index])
            tmp->name[index]=createNode();
        tmp=tmp->name[index];
    }
       tmp->isend=true;
       tmp->m=node;
       tmp->k=NULL;
}

void print_info(struct info* root, struct sales_info* sroot){
    cout<<"Name Of Medicine"<<"-"<<root->med_name<<'\n';
    cout<<"Cost"<<"-"<<root->cost<<'\n';
    while(sroot){
        cout<<"Name Of Person  "<<sroot->fname<<" "<<sroot->lname<<'\n';
        cout<<"Age Of Person "<<sroot->age<<endl;
        cout<<"Quantity"<<"  "<<sroot->quantity<<'\n';
        sroot=sroot->next;
    }
}

void print_med_info(struct info* root){
   cout<<"Name Of Medicine"<<"-"<<root->med_name<<'\n';
   cout<<"Cost"<<"-"<<root->cost<<'\n';
   cout<<"Manufacturing Date"<<"-"<<root->mfd<<'\n';
   cout<<"Expiry Date"<<"-"<<root->expiry_date<<'\n';
   cout<<"Quantity"<<"-"<<root->quantity<<'\n';
}

Node* is_present(struct Node *root,string key){
    Node*tmp=root;
    for(int i=0;i<key.length();i++){
        int index=key[i]-'a';
        if(!tmp->name[index])
            return NULL;
         tmp=tmp->name[index];
    }
    if(tmp!=NULL&&tmp->isend)
        return tmp;
    else
       return NULL;
}


//loads data from file and makes a multilinkedlist;
void loadData(){
    ifstream dfile;
    dfile.open("diseases.txt");
    string str;
    while (getline(dfile, str)) {
        char temp[20];
        vector<string> s;
        int k=0;
        for(int i=0; i<str.length(); i++){
            k=0;
            while(str[i]!=' ' && i<str.length()){
                temp[k] = str[i];
                i++;
                k++;
            }
            temp[k] = '\0';
            s.push_back(string(temp));
        }
        diseases* ptr = new diseases;
        medic_name *med = new medic_name;
        med->name = s[1];
        med->next = NULL;
        ptr->d_name = s[0];
        ptr->next = NULL;
        ptr->medics = med;
        if(data==NULL)
            data = ptr;
        else{
            diseases* temp = data;
            while(temp->next!=NULL)
                temp = temp->next;
            temp->next = ptr;
        }

        for(int i=2; i<s.size(); i++){
           medic_name *ptr2 = new medic_name;
           ptr2->name = s[i];
           ptr2->next=  NULL;
           med->next = ptr2;
           med = med->next;
        }
    }

}

//prints data from multilinkedlist;
void printalldata(){
diseases *ptr = data;
medic_name *ptr2;
while(ptr!=NULL){
    ptr2 = ptr->medics;
    cout<<ptr->d_name<<" ";
    while(ptr2!=NULL){
        cout<<ptr2->name<<" ";
        ptr2 = ptr2->next;
    }
    cout<<endl;
    ptr= ptr->next;
}
}
void searchmedicine_bydesease(struct Node* root){
askingDisease:
        cout<<"Tell us about your disease we will offer you some medicines"<<endl;
        string d;
        cin>>d;
        diseases *ptr = data;
        while(ptr!=NULL && ptr->d_name!=d)
            ptr = ptr->next;
        if(ptr!=NULL){
            medic_name *ptr2 = ptr->medics;
            while(ptr2!=NULL){
                cout<<ptr2->name<<" ";
                ptr2 = ptr2->next;
            }
            cout<<endl;
            cout<<"Type the medicine name you want and its quantity: "<<endl;
            string medname;
            int q;
            cin>>medname>>q;
            searchmedicine_bystring(root, medname, q);
            cout<<"Transaction was a success!! Your order will be delivered soon"<<endl;

        }
        else{
            cout<<"Sorry your disease is not listed in our database try again!!"<<endl;
            goto askingDisease;
        }


    }


void searchmedicine_bystring(struct Node* root, string medname, int q) {
search_byname:
    char name[20];
    char fname[20],lname[20];
    int age,quantity=q;
    int i=0;
    for(i=0; i<medname.length(); i++)
        name[i] = medname[i];
    name[i] = '\0';
    struct Node*m1=is_present(root,name);
    if(m1){ print_med_info(m1->m);
    cout<<"Press '1' to buy"<<'\n';
    cout<<"Press '2' to quit"<<'\n';
    char c;
    cin>>c;
    if(c=='1'){
    cout<<"Enter Your First Name"<<'\n';
    cin>>fname;
    cout<<"Enter Your Last Name"<<'\n';
    cin>>lname;
    cout<<"Enter Your Age"<<'\n';
    cin>>age;
    m1->m->quantity-= quantity;
    FILE *buyer_info = fopen("buyer.txt", "a");
    fprintf(buyer_info, "%s %s %s %d %d\n", name, fname, lname, age, quantity);
    fclose(buyer_info);
    struct sales_info*tmp=NULL;
    tmp=insert_sales_info(tmp,fname,lname,age,quantity);
    m1->k=tmp;
    cout<<"Transaction was a success!! Your order will be delivered soon"<<endl;

      }
    if(c=='2'){
        return;
    }
   }
    else{
    int c;
    cout<<"This Medicine Is Not Available"<<'\n';
    cout<<"Press '1' To Search Another Medicine"<<'\n';
    cout<<"Press '2' To Quit"<<'\n';
    cin>>c;
    if(c==1)
        goto search_byname;
    else
        return;
   }
}




void serchmedicine_byname(struct Node*root) {
search_byname:
    char name[20];
    char fname[20],lname[20];
    int age,quantity;
    cout<<"Enter medicine name"<<'\n';
    cin>>name;
    struct Node*m1=is_present(root,name);
    if(m1){ print_med_info(m1->m);
    cout<<"Press '1' to buy"<<'\n';
    cout<<"Press '2' to quit"<<'\n';
    char c;
    cin>>c;
    if(c=='1'){
    cout<<"Enter Quantity"<<'\n';
    cin>>quantity;
    cout<<"Enter Your First Name"<<'\n';
    cin>>fname;
    cout<<"Enter Your Last Name"<<'\n';
    cin>>lname;
    cout<<"Enter Your Age"<<'\n';
    cin>>age;
    m1->m->quantity-= quantity;
    FILE *buyer_info = fopen("buyer.txt", "a");
    fprintf(buyer_info, "%s %s %s %d %d\n", name, fname, lname, age, quantity);
    fclose(buyer_info);
    struct sales_info*tmp=NULL;
    tmp=insert_sales_info(tmp,fname,lname,age,quantity);
    m1->k=tmp;
    cout<<"Transaction was a success!! Your order will be delivered soon"<<endl;

      }
    if(c=='2'){
        return;
    }
   }
    else{
    int c;
    cout<<"This Medicine Is Not Available"<<'\n';
    cout<<"Press '1' To Search Another Medicine"<<'\n';
    cout<<"Press '2' To Quit"<<'\n';
    cin>>c;
    if(c==1)
        goto search_byname;
    else
        return;
   }
}
void search_medicineseller(struct Node*root){
    search_byname:
    string name;
    cout<<"Enter medicine name"<<'\n';
    cin>>name;
    struct Node*m1=is_present(root,name);
    if(m1){
    print_info(m1->m,m1->k);
      }
    else{
    int c;
    cout<<"This Medicine Is Not Available"<<'\n';
    cout<<"Press '1' To Search Another Medicine"<<'\n';
    cout<<"Press '2' To Quit"<<'\n';
    cin>>c;
    if(c==1)
        goto search_byname;
    else
        return;
   }
}
void user_page(struct Node*root)
{
    char input;
    cout<<"Press '1' to buy medicine"<<'\n';
    //cout<<"Press '2' to view buy history"<<'\n';
    cin>>input;
    if(input=='1'){
        char input1;
        cout<<"Press 1 to search medicine by disease"<<'\n';
        cout<<"Press 2 to search medicine by name"<<'\n';
        cin>>input1;
        if(input1=='1')
            searchmedicine_bydesease(root);
        if(input1=='2')
            serchmedicine_byname(root);
    }
}
void seller_page(struct Node*root){
char input;
cout<<"Press '1' To Check Medicine Records"<<'\n';
cin>>input;
if(input=='1')
    search_medicineseller(root);
}
bool loginCustomer(struct Node*root){
    FILE *loginfile = fopen("login.txt", "r");
    char loginid[20], password[20], fname[20], lname[20];
    int age, quantity;
    string tempid, temppass;
    cout<<"Enter your user name:"<<endl;
    cin>>tempid;
    cout<<"Enter your password:"<<endl;
    cin>>temppass;
    if (loginfile==NULL) {
        cout << "Unable to open file login.txt"<<endl;
        return false;
    }
    bool flag = true;
    while (!feof(loginfile)) {
        fscanf(loginfile, "%s %s %s %s %d %d\n", loginid, password, fname, lname, &age, &quantity);
        if(tempid==loginid && temppass==password){
            flag = false;
            break;
        }
    }
    if(flag==false){
        cout<<"Hello, "<<tempid<<endl;
        user_page(root);
    }
    else{
        cout<<"User not found!!"<<endl;
        fclose(loginfile);
        return false;
    }
    fclose(loginfile);
    return true;
}

bool registerCustomer(){

    FILE *loginfile = fopen("login.txt", "a");
    char loginid[20], password[20], fname[20], lname[20];
    int age, quantity;
    cout<<"Enter your user name:"<<endl;
    cin>>loginid;
    cout<<"Enter your password:"<<endl;
    cin>>password;
    cout<<"Enter your First Name:"<<endl;
    cin>>fname;
    cout<<"Enter your Last Name:"<<endl;
    cin>>lname;
    cout<<"Enter your Age:"<<endl;
    cin>>age;
    cout<<"Enter quantity of medicine required:"<<endl;
    cin>>quantity;
    if (loginfile==NULL) {
        cout << "Unable to open file login.txt"<<endl;
        return false;
    }
    fprintf(loginfile, "%s %s %s %s %d %d\n", loginid, password, fname, lname, age, quantity);
    fclose(loginfile);
    return true;
}

bool loginSeller(struct Node*root){
    FILE *loginfile = fopen("loginseller.txt", "r");
    char loginid[20], password[20], fname[20], lname[20];
    int age;
    string tempid, temppass;
    cout<<"Enter your user name:"<<endl;
    cin>>tempid;
    cout<<"Enter your password:"<<endl;
    cin>>temppass;
    if (loginfile==NULL) {
        cout << "Unable to open file login.txt"<<endl;
        return false;
    }
    bool flag = true;
    while (!feof(loginfile)) {
        fscanf(loginfile, "%s %s %s %s %d\n", loginid, password, fname, lname, &age);
        if(tempid==loginid && temppass==password){
            flag = false;
            break;
        }
    }
    if(flag==false){
        cout<<"Hello, "<<tempid<<endl;
        seller_page(root);
    }
    else{
        cout<<"User not found!!"<<endl;
        fclose(loginfile);
        return false;
    }
    fclose(loginfile);
    return true;
}

bool registerSeller(){

    FILE *loginfile = fopen("loginseller.txt", "a");
    char loginid[20], password[20], fname[20], lname[20];
    int age;
    cout<<"Enter your user name:"<<endl;
    cin>>loginid;
    cout<<"Enter your password:"<<endl;
    cin>>password;
    cout<<"Enter your First Name:"<<endl;
    cin>>fname;
    cout<<"Enter your Last Name:"<<endl;
    cin>>lname;
    cout<<"Enter your Age:"<<endl;
    cin>>age;

    if (loginfile==NULL) {
        cout << "Unable to open file login.txt"<<endl;
        return false;
    }
    bool flag = true;
    fprintf(loginfile, "%s %s %s %s %d\n", loginid, password, fname, lname, age);
    fclose(loginfile);
    return true;
}
void load_data_in_trie(struct Node*root){
 FILE *loginfile = fopen("medicines.txt", "r");
    char med_name[20], exp_date[20], mfd_date[20];
    int cost,q;
    while (!feof(loginfile)) {
        fscanf(loginfile, "%s %s %d %s %d\n", med_name, exp_date, &q, mfd_date, &cost);
        info* tmp=NULL;
        tmp=insert_med_info(med_name,q,exp_date,mfd_date,cost);
         Insert(root,tmp,med_name);
    }
    fclose(loginfile);
    FILE *buyer_info = fopen("buyer.txt", "r");
    char fname[20], lname[20];
    int age;
    while (!feof(buyer_info)) {
        fscanf(buyer_info, "%s %s %s %d %d\n", med_name, fname, lname, &age, &q);
        struct sales_info*tmp=NULL;
        struct Node* m=is_present(root,med_name);
        tmp=insert_sales_info(m->k,fname,lname,age,q);
        if(m){
            m->k=tmp;
        }
    }
    fclose(buyer_info);
}


void updatemedicinedata(Node* root){
char name[100], mfdate[100], expdate[100], medname[100];
FILE *ptr = fopen("medicines.txt", "w");
diseases* d = data;
medic_name * d1 = d->medics;
while(d!=NULL){
    d1 = d->medics;
    while(d1!=NULL){
        string temp =d1->name;
        int i;
        for(i=0; i<temp.length(); i++)
            name[i] = temp[i];
        name[i] = '\0';
        Node* m1 = is_present(root, name);
        info * m = m1->m;

        temp =m->med_name;
        for(i=0; i<temp.length(); i++)
            medname[i] = temp[i];
        medname[i] = '\0';
        temp =m->mfd;
        for(i=0; i<temp.length(); i++)
            mfdate[i] = temp[i];
        mfdate[i] = '\0';
        temp =m->expiry_date;
        for(i=0; i<temp.length(); i++)
            expdate[i] = temp[i];
        expdate[i] = '\0';
        fprintf(ptr, "%s %s %d %s %d\n", medname, mfdate, m->quantity, expdate, m->cost);
        d1= d1->next;
    }
    d = d->next;
}

}



int main() {
    loadData();
    struct Node*root=createNode();
    load_data_in_trie(root);
    
    char input;
    sellorcust:
    system("cls");
    ClearConsoleToColors(1,15);
    cout<<"WELCOME TO INDIGO PHARMACY!!"<<endl<<endl;
    cout<<"Press 'q' at any state of program to exit"<<endl<<endl;
    cout<<"Are u a customer or a seller:"<<endl;
    cout<<"Press '1' for CUSTOMER or '2' for SELLER"<<endl;
    cin>>input;
    if(input=='1'){
        // customer
        accoutinfo1:
        char haveAnAccount  = 'y';
        cout<<"Do u have an account? (y/n)"<<endl;
        cin>>haveAnAccount;
        if(haveAnAccount=='y'){
            // customer has an account;
            bool res = loginCustomer(root);
            if(res==false){
                goto accoutinfo1;
            }
        }
        else if(haveAnAccount=='n'){
            // customer does not have an account;
            bool res = registerCustomer();
            if(res==false)
                goto accoutinfo1;
        }
        else if(haveAnAccount=='q')
            exit(0);
        else{
            goto accoutinfo1;
        }
        cout<<"press any key to continue";
        string abc;
        cin>>abc;
        goto sellorcust;

     }
    else if(input=='2'){
        // seller
        accoutinfo2:
        char haveAnAccount  = 'y';
        cout<<"Do u have an account? (y/n)"<<endl;
        cin>>haveAnAccount;
        if(haveAnAccount=='y'){
            // seller has an account;
            bool res = loginSeller(root);
            if(res ==false)
                goto accoutinfo2;
        }
        else if(haveAnAccount=='n'){
            // seller does not have an account;
            bool res = registerSeller();
            if(res ==true)
                loginSeller(root);
        }
        else if(haveAnAccount=='q')
            exit(0);
        else{
            goto accoutinfo2;
        }
        cout<<"press any key to continue";
        string abc;
        cin>>abc;
        goto sellorcust;

    }
    else if(input=='q')
        exit(0);
    else
        goto sellorcust;
    updatemedicinedata(root);
}


void ClearConsoleToColors(int ForgC, int BackC)
 {
 WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
 HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
 COORD coord = {0, 0};

   DWORD count;
 CONSOLE_SCREEN_BUFFER_INFO csbi;
 SetConsoleTextAttribute(hStdOut, wColor);
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
      FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

      FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
      SetConsoleCursorPosition(hStdOut, coord);
 }
 return;
}
