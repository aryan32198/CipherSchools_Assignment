#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class student{

   int rollno;
   char name[50];
   int marks[6];
   float cgp;
   float percentage;
public:
   void getData();
   void showData() const;
   float calculate();
   int retRollno();
   void showdetailsOfStudents() const;
};
void student::getData(){

   cout<<"\nEnter the roll number :";
   cin>>rollno;
   cout<<"\nEnter the Student Name :";
   cin.ignore();
   cin.getline(name,50); 
   cout<<"Enter marks ::"<<endl;
   for(int i=0;i<6;i++){
       if(i==0)
       cout<<"English :";
       else if(i==1)
       cout<<"Social  :";
       else if(i==2)
       cout<<"Hindi   :";
       else if(i==3)
       cout<<"Maths   :";
       else if(i==4)
       cout<<"Biology :";
       else if(i==5)
       cout<<"Science :";
       cin>>marks[i];
   }
   percentage=calculate();
   if(percentage>=90)
   cgp=10;
   if(percentage>=80&&percentage<90)
   cgp=9;
   if(percentage>=70&&percentage<80)
   cgp=8;
   if(percentage>=60&&percentage<70)
   cgp=7;
   if(percentage>=50&&percentage<60)
   cgp=6;
   if(percentage<50)
   cgp=5;
    
}
void student::showData() const{
    
   
    cout<<"\nRollno :"<<rollno<<endl;
    cout<<"Name :";
    cout<<name;
    cout<<"\nMarks :"<<endl;
    for(int i=0;i<6;i++){
       if(i==0)
       cout<<"English :";
       else if(i==1)
       cout<<"Social  :";
       else if(i==2)
       cout<<"Hindi   :";
       else if(i==3)
       cout<<"Maths   :";
       else if(i==4)
       cout<<"Biology :";
       else if(i==5)
       cout<<"Science :";
       cout<<marks[i]<<endl;
   }
   
   cout<<"The percentage is :"<<percentage<<endl;
    
   cout<<"CGPA is :"<<cgp<<endl;
}
void student::showdetailsOfStudents() const{
    cout<<rollno<<" ."<<name<<endl;
}
float student::calculate(){
   
   int total=0;
   for(int i=0;i<6;i++)
   total+=marks[i];
   return(total/6);
}  
int student::retRollno(){
    return rollno;
}
//*************************************************************************
void create_student();
void display_sp(int );
void display_all();
void delete_student(int);
void change_student(int);
void intro();
//*************************************************************************
int main(){
    char ch;
    int num;
    system("cls");
    intro();

    do
    {
        system("cls");
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. ADD Student";
        cout<<"\n\n\t02. EDIT student Details";
        cout<<"\n\n\t03. Student Details";
        cout<<"\n\n\t04. ALL Students LIST";
        cout<<"\n\n\t05. Remove Student";
        cout<<"\n\n\t08. EXIT";
        cout<<"\n\n\tSelect Your Option (1-8) ";
        cin>>ch;
        system("cls");
        switch(ch)
        {
        case '1':
            create_student();
            break;
        case '2':
            cout<<"\n\n\tEnter The Roll No. : "; cin>>num;
            change_student(num);
            break;
      
        case '3':
            cout<<"\n\n\tEnter The Roll No. : "; cin>>num;
            display_sp(num);
            break;
        case '4':
            display_all();
            break;
        case '5':
            cout<<"\n\n\tEnter The Roll No. : "; cin>>num;
            delete_student(num);
            break;
      
         case '6':
            cout<<"\n\n\tStudent date is preserved safely";
            break;
         default :cout<<"a";
        }
        cin.ignore();
        cin.get();
    }while(ch!='6');
    
    return 0;
}
void create_student()
{
    student s1;
    ofstream outFile;
    outFile.open("s.txt",ios::binary|ios::app);
    s1.getData();
    outFile.write(reinterpret_cast<char *> (&s1), sizeof(student));
    outFile.close();
}

void display_sp(int n) 
{
    student s;
    bool flag=false;
    ifstream inFile;
    inFile.open("s.txt",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    cout<<"\n DETAILSn";

        while(inFile.read(reinterpret_cast<char *> (&s), sizeof(student)))
    {
        if(s.retRollno()==n)
        {
            s.showData();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
        cout<<"\n\nAccount number does not exist";
}
void display_all()
{
    student s;
    ifstream inFile;
    inFile.open("s.txt",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        
        return;
    }
     cout<<"\nStudent Details :"<<endl;
    while(inFile.read(reinterpret_cast<char *> (&s), sizeof(student)))
    {
        s.showdetailsOfStudents();
    }
    inFile.close();
}
void delete_student(int n)
{
    student s;
    ifstream inFile;
    ofstream outFile;
    inFile.open("s.txt",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.txt",ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&s), sizeof(student)))
    {
        if(s.retRollno()!=n)
        {
            outFile.write(reinterpret_cast<char *> (&s), sizeof(student));
        }
    }
    inFile.close();
    outFile.close();
    remove("s.txt");
    rename("Temp.txt","s.txt");
    cout<<"\n\n\tRecord Deleted ..";
}
void change_student(int num){
     bool found=false;
    student s;
    fstream File;
    File.open("s.txt",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&s), sizeof(student));
        if(s.retRollno()==num)
        {
            s.showData();
            cout<<"\n\nEnter The New Details of Student"<<endl;
            s.getData();
            int pos=(-1)*static_cast<int>(sizeof(student));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&s), sizeof(student));
            cout<<"\n\n\t Record Updated";
            found=true;
          }
    }
    File.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";

}
void intro(){
    system("cls");
    cout<<"STUDENT MANAGEMENT SYSTEM";
    cin.ignore();
    cin.get();
}
