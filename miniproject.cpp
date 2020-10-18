#include<iostream>
#include<string>
#include<fstream>
#include<time.h>
#include<conio.h>
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
                       return false;    //return flase           
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
                   cur = cur->next;   //next
              } //while
                       return false;
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
//roundlist
//roundlist
class Roundlist{
    private:
        int i; //i = index
        string Departure,terminal,TravelTime,TimeOut[5],timeLine;                                             //array string TimeOut,TimeTo        
    public:
        Roundlist *next;
        Roundlist(string departure,string ter,string travel,string timeline){
            //set station&time
            Departure = departure;
            terminal = ter;
            TravelTime = travel;
            timeLine = timeline;
            next = NULL;
        }
        string getDepature(){
            return Departure;//return string
        }
        string getTerminal(){
            return terminal;//return string
        }
        string getTravelTime(){
            return TravelTime;//return string
        }
        string Timeout(int i){
            return TimeOut[i];//return string array
        }
        /*string Timeto(int i){
            return TimeTo[i];//return string array
        }*/
        void printtime(){
            for(int i = 0;i<5;i++){
                cout << " " << TimeOut[i] << endl;
            }
        }
};
class Round{
    private:
         Roundlist *head;
         Roundlist *tail;
         string Timeline[5];
    public:
        Round(){
            head = NULL;
            tail = NULL;
            loaddata_Airport();
            for(int i =0;i<5;i++){
                Timeline[i] = ""; 
            }
           //Addtimeline();
        }
        void addround(string departure,string terminal,string time,string timeout){
             Roundlist *newnode = new Roundlist(departure,terminal,time,timeout);
             if(head==NULL){
                 head = newnode;
                 tail = newnode;
             }else{
                 tail->next = newnode;
                 tail = newnode;
             }
        }
        void loaddata_Airport(){
             //Roundlist *newnode;
            ifstream  myfile("flights.txt",ios::in);
            string line,departure,terminal,time,timeout;
             if(myfile.is_open()){
                while(getline(myfile,line)){
                      departure = line.substr(0,line.find(',')); 
                      line.erase(0,line.find(',')+1);
                      terminal = line.substr(0,line.find(',')); 
                      line.erase(0,line.find(',')+1);
                      time = line.substr(0,line.find(',')); 
                      line.erase(0,line.find(',')+1);
                      timeout = line.substr(0,string::npos);
                    addround(departure,terminal,time,timeout);
                 }  
            }else{
               cout << "Cannot Open File" << endl;
                 }
        }//loaddata
        void setuptime(string line){
             int i=0;
             Timeline[i++] = line;    
        }
        void Addtimeline(){
        	string line;
             for(int i =0 ;i<5;i++){
                    line = Timeline[i].substr(0,Timeline[i].find(','));             	 
			        Timeline[i].erase(0,Timeline[i].find(',')+1);     
			        
			 }           
        }
        void printlist(){
            Roundlist *cur=head;
             while(cur != NULL){
                 cout << cur->getDepature() << " " << cur->getTerminal() << cur->getTravelTime() << endl;
                 cout << endl;
                 cur = cur->next;
             }

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
    Round *round = new Round();
    //round->Addtimeline();
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
         string username,user_pass="";
         char star;
          do{
           cout << endl;   
           cout << "\t\t\t\t\t+========================+" << endl;
           cout << "\t\t\t\t\t+       Login            +" << endl;
           cout << "\t\t\t\t\t+========================+" << endl;
           cout << "\t\t\t\t\t+ 1.Login                +" << endl;
           cout << "\t\t\t\t\t+ 2.Back                 +" << endl;
           cout << "\t\t\t\t\t+========================+" << endl;  
           cout << "Please Enter Choice : "; cin >> menu_login;
             if(menu_login==1){
                 cout << "\t\t\t\t\tPlease Enter Username : "; cin >> username; //ใส่ username
                 cout << "\t\t\t\t\tPlease Enter Password : ";  star = _getch();
                 cin.ignore();
                 while(star!=13){
                    user_pass.push_back(star);
                       cout << '*';
                       star = _getch();
                 }
                 if(customerControl->LogginCustomer(username,user_pass)){
                     int member_menu;
                     do{
                         //menu Flights Booking
                         cout << endl;
                         cout << "\t\t\t\t\t 1. Flights Booking" << endl;
                         cout << "\t\t\t\t\t 2. Advance Booking" << endl;
                         cout << "\t\t\t\t\t 3. Exchange points" << endl;
                         cout << "\t\t\t\t\t 4. Back to loggin " << endl;
                         cout << "Please Enter Choice : "; cin >> member_menu;//member
                          if(member_menu == 1){
                             round->printlist();       
                          } 
                       }while(member_menu!=4);
                 }
             }//if
          }while(menu_login != 2);
       }//else if
       else if(main_menu == 2){
          //user register
          string username,user_pass="",name,lastname,tel,id_card; //ประกาศตัวแปร
          char is_commit;
          cout << "\t\t\t\t\t==========================" << endl;
          cout << "\t\t\t\t\t+       Register         +" << endl;
          cout << "\t\t\t\t\t+========================+" << endl;
          cout << "\t\t\t\t\t+Please Enter Information+" << endl;
          cout << "\t\t\t\t\t+========================+" << endl;
             do{
                 //เช็คว่ามีชื่อผู้ใช้หรือไม่
              cout << "\t\t\t\t\tPlease Enter Username : "; cin >> username; //ใส่ username
             }while(customerControl->CheckUserName(username)!=false);
             string pass_again = "";
            do{
              cout << "\t\t\t\t\tPlease Enter Password : ";            cin >> user_pass; //ใส่รหัสผ่าน
              cout << "\t\t\t\t\tPlease Enter Password Again!! : ";    cin >> pass_again; //ใส่รหัสผ่าน
            }while(user_pass!=pass_again);
              cout << "\t\t\t\t\tYour Password id Ok" << endl;
              cout << "\t\t\t\t\tPlease Enter Name : ";                cin >> name; // กรอกชื่อ
              cout << "\t\t\t\t\tPlease Enter Lastname : ";            cin >> lastname;  // กรอกนามสกุล
            
            do{
                 cout << "\t\t\t\t\tPlease Enter Identification Card : "; cin >> id_card;
                if(id_card.length()<13 || id_card.length()>13){
                    //เช็คว่าผู้ใช้ป้อนรหัสมา13หลักหรือไม่
                    cout << "Identification Card At least 13 digit !!" << endl; 
                }
            }while(customerControl->CheckIdCard(id_card)!=false&&id_card.length()==13);
            
              cout << "\t\t\t\t\tPlease Enter Telephone Number : ";    cin >> tel;  // กรอกนามสกุล
              cout << "\t\t\t\t\tDo you want to continue? (y/n) : ";  cin >> is_commit;
             while(is_commit!='y'&&is_commit!='n'){
                 //ถ้าผู้ใช้ไม่กด y และ n จะให้กรอกไหม่
                  cout << "Please Enter (y,n)" << endl;
                  cout << "\t\t\t\t\tDo you want to continue? (y/n) : ";  cin >> is_commit;
             }//while

             if(is_commit == 'y'){
                 customerControl->ResigerUser(username,user_pass,name,lastname,tel,id_card);  
                 cout << "Save Complete" << endl;
             }
             else if(is_commit == 'n'){
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
