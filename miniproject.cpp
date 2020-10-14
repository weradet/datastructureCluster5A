 #include<iostream>
#include<string>
#include<iostream>
#include<fstream>
#include<time.h>
using namespace std;
class CustomerUser{   
     private: 
      string Username,Password,Name,Lastname,Tel,Idcard;
     public:
      CustomerUser *next;
      CustomerUser(){
          next = NULL;
      }
      CustomerUser(string user_name,string pass,string name,string lname,string tel,string id_card){
       //setup user
          Username = user_name;
          Password = pass;
          Name = name;
          Lastname = lname;
          Tel = tel;
          Idcard = id_card;
          next = NULL;
      }
   
     string getUsername(){
          return Username; 
     } //getusername
      string getpassword(){
          return Password; 
     } //getusername
     string getName(){
         return Name;
     }
     string getLastname(){
         return Lastname;
     }
     string getTel(){
         return Tel;
     }
     string getIdCard(){
         return Idcard;
     }
};
class CustomerControler{
     private:
        CustomerUser *head;
        CustomerUser *tail;  
     public:
        CustomerControler(){
            head = NULL;
            tail = NULL;
            Loaddata();
        }
        bool LogginCustomer(string user_name,string pass){
           //get parameter username and pass for check 
           // is true return true 
              CustomerUser *cur = head;
             while(cur!=NULL){
                if(cur->getUsername()==user_name&&cur->getpassword()==pass){
                    //เช็คว่าชื่อกับรหัสผ่านว่าตรงกันไหม
                   return true; 
                   break;
                 }
                 cur = cur->next; 
             }//while
                   return false;  
        }
        
        void ResigerUser(string user,string pass,string name,string last,string tel,string id_card){
              //เพิ่มNode
               CustomerUser *User = new CustomerUser(user,pass,name,last,tel,id_card); // add ไปใน node 
                if(head == NULL){ 
                    head = User;
                    tail = User;
                }else{
                    tail->next = User;
                    tail=User;
                }
                //writefile(user,pass,name,last,tel); //เรียกใช้การเขียนไฟล์     
        }//Register
        void Loaddata(){
            //โหลดข้อมูลจากไฟล์เข้าสู่Linkedlist
           string line,user_name,pass,name,lastname,tel,id_card;
           ifstream data("data.txt",ios::in);
           if(data.is_open()){
                  while(getline(data,line)){ 
                user_name =  line.substr(0,line.find(','));
                               line.erase(0,line.find(',')+1);  
                   pass   =  line.substr(0,line.find(','));
                               line.erase(0,line.find(',')+1);   
                   name   =  line.substr(0,line.find(','));
                               line.erase(0,line.find(',')+1);  
                 lastname =  line.substr(0,line.find(','));
                               line.erase(0,line.find(',')+1);   
                  tel =      line.substr(0,line.find(','));
                               line.erase(0,line.find(',')+1);   
                  id_card =  line.substr(0,string::npos);
                               line.erase(0,string::npos);                                                 
                  ResigerUser(user_name,pass,name,lastname,tel,id_card);
            }//while
          }else{
             cout << "Error File!!" << endl;
          } 
        }//loaddata
        bool CheckUserName(string username){
             //เช็คว่า ชื่อผู้ใช้ว่าตรงกันไหม
               CustomerUser *cur = head;
                 while(cur != NULL){
                    if(username == cur->getUsername()){
                       cout << "\t\t\t\t\tUsername already in use" << endl;
                       return true;
                       break;  
                    }//if  
                    cur = cur->next;
                 } //while
                       return false;               
        }//check
        bool CheckIdCard(string Idcard){
              //เช็คว่าบัตรประชน
            CustomerUser *cur = head;
              while(cur != NULL){
                   if(Idcard == cur->getIdCard()){
                       cout << "\t\t\t\t\tId Card already in use" << endl;
                       return true;
                       break; 
                   }
                   cur = cur->next;   
              } //while
        }//checkcard
        void show(){
            CustomerUser *cur = head;
            while(cur != NULL){
                cout << cur->getUsername() << endl;
                cur = cur->next;
            }
        }
         void writefile(){
             //เขียนไฟล์
            ofstream file("data.txt",ios::out); // เขียนไฟล์
            CustomerUser *cur = head;
            while(cur != NULL){
                 file << cur->getUsername()<<","+cur->getpassword()<<","+cur->getName()<<","+cur->getLastname()<<","
                 <<cur->getTel()<<","<<cur->getIdCard() << endl; // เขียนรายละเอียดลลงไปในไฟล์
                 cur=cur->next;
            }
            file.close(); // ปิดไฟล์
        }
};
class Ticket{

};
class Round{
    private:

    public:
        void loaddata(){
                
        }
};
void printmenu(){
    //แสดงหน้าเมนูหลัก
    ifstream  file("menu.txt",ios::in);
    string line;
    if(file.is_open()){
        while(getline(file,line)){
                cout << line << endl;
            }   
    }else{
        cout << "Error Show Menu!!" << endl;
    }
}
int main(){
    CustomerControler *customerControl = new CustomerControler(); //obj customerconntroler
    //main Program
    int main_menu;
  customerControl->show();
  do{
      // customerControl->show();
       //system("cls");
       printmenu();
    try{
       cout <<  "Choose Menu (1-5) : "; cin >> main_menu; //user Input
       if (!cin){
         throw main_menu;
       }//if
       else if(main_menu == 1){
           //user Loggin
         int menu_login;  
         string username,user_pass;
          do{
           cout << "\t\t\t\t\t+========================+" << endl;
           cout << "\t\t\t\t\t+       Login            +" << endl;
           cout << "\t\t\t\t\t+========================+" << endl;
           cout << "\t\t\t\t\t+ 1.Login                +" << endl;
           cout << "\t\t\t\t\t+ 2.Back                 +" << endl;
           cout << "\t\t\t\t\t+========================+" << endl;  
           cout << "Please Enter Choice : "; cin >> menu_login;
             if(menu_login==1){
                 cout << "\t\t\t\t\tPlease Enter Username : "; cin >> username; //ใส่ username
                 cout << "\t\t\t\t\tPlease Enter Password : "; cin >> user_pass; //ใส่รหัสผ่าน
                 if(customerControl->LogginCustomer(username,user_pass)){
                     int member_menu;
                     do{
                         //menu Flights Booking
                         cout << " 1. Flights Booking" << endl;
                         cout << " 2. Advance Booking" << endl;
                         cout << " 3. Exchange points" << endl;
                         cout << " 4. Back to loggin " << endl;
                       while(member_menu!=3);
                 }
             }//if
          }while(menu_login != 2);
       }//else if
       else if(main_menu == 2){
          //user register
          string username,user_pass,name,lastname,tel,id_card; //ประกาศตัวแปร
          char commit;
          cout << "\t\t\t\t\t==========================" << endl;
          cout << "\t\t\t\t\t+       Register         +" << endl;
          cout << "\t\t\t\t\t+========================+" << endl;
          cout << "\t\t\t\t\t+Please Enter Information+" << endl;
          cout << "\t\t\t\t\t+========================+" << endl;
             do{
              cout << "\t\t\t\t\tPlease Enter Username : "; cin >> username; //ใส่ username
             }while(customerControl->CheckUserName(username)!=false);
          cout << "\t\t\t\t\tPlease Enter Password : ";            cin >> user_pass; //ใส่รหัสผ่าน
          cout << "\t\t\t\t\tPlease Enter Name : ";                cin >> name; // กรอกชื่อ
          cout << "\t\t\t\t\tPlease Enter Lastname : ";            cin >> lastname;  // กรอกนามสกุล
          cout << "\t\t\t\t\tPlease Enter Identification Card : "; cin >> id_card; 
          cout << "\t\t\t\t\tPlease Enter Telephone Number : ";    cin >> tel;  // กรอกนามสกุล
          cout << "\t\t\t\t\tDo you want to continue? (y/n) : ";  cin >> commit;
             while(commit!='y'&&commit!='n'){
                 //ถ้าผู้ใช้ไม่กด y และ n จะให้กรอกไหม่
                  cout << "Please Enter (y,n)" << endl;
                  cout << "\t\t\t\t\tDo you want to continue? (y/n) : ";  cin >> commit;
             }//while
             if(commit == 'y'){
                 customerControl->ResigerUser(username,user_pass,name,lastname,tel,id_card);  
                 cout << "Save Complete" << endl;
             }
             else if(commit == 'n'){
                 cout << "Cannot Save" << endl;
             }
       }
    }catch(int x){  
         cin.clear(); 
         cin.ignore(100, '\n'); 
    }
  }while(main_menu!=5);
  customerControl->writefile();
}//main