#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <conio.h>
#include <ctime>
#include <sstream>
#include <iomanip>
using namespace std;

class Seat{
      protected:
        int seat_normal[6][10];
        double pice;
        int yourcol;
	    int yourrol;
      public:
        Seat(){
            for(int i=0;i<6;i++){
                for(int j=0;j<10;j++){
                   seat_normal[i][j] = 0;
                }
            }
        }
        void ShowMoreSeat(){
            system("cls");
            cout << "                                  __                                                            " << endl;
            cout << "                               //   |                                                           " << endl;
            cout << "                             //     |                                                           " << endl;
            cout << "                           //       |                                                                          __ " << endl;
            cout << "                         //         |                                                                        /   |" << endl;
            cout << "                       //           |                                                                      /-----|" << endl;
            cout << "                     //             |                                                                    /-------|" << endl;
            cout << "                   //               |                                                                  /         |" << endl;
            cout << "__________________________________________________________________________________________________________________" << endl;
            for(int i=0;i<6;i++){
                for(int j=0;j<10;j++){
                   if(seat_normal[i][j] == 0){
                       cout << "SEAT "  << i << j << ":" << "O" << "  ";
                   }else{
                       cout << "SEAT "  << i << j << ":" << "i" << "  ";
                   }
                }
                cout << endl;
            }
            cout << "__________________________________________________________________________________________________________________\n" << endl;
        }  
    void setseat(int s) { 
		int col = s / 10; // mod i
		int rol = s % 10; // mod j
		if (col >= 6 || rol > 10) {
			cout << "   Cannot reserve (there are not the seat)" << endl;
		}
		else {
			if (seat_normal[col][rol] == 0) {
				seat_normal[col][rol] = 1;
				yourcol = col;
				yourrol = rol;
				cout << "   Reserve completed\n" << endl; // set array = 1
				}
			else {
				cout << "   Cannot reserve\n"; // not 
			}
		}
    }
};
//roundlist
//roundlist
class TimeAir{
    public:
      string time;
      Seat normalseat;
      TimeAir(){

      } 
      TimeAir(string t){
         time = t;
      }
      void settime(string t){
         time = t;
      }  
      void showseatNormal(){
         normalseat.ShowMoreSeat();
      }
      string gettime(){
          return time; 
      }
    
};

class TimeQueue{
    /*
        Queue Time 
        รอบเวลาต่างๆในเที่ยวบิน
    */
     public:
       TimeAir *time;
       int max;
       int count;
       int font;
       int rear;
       TimeQueue(){
           // timeout = new string[5];
            time = new TimeAir[5];
            max = 5;
            count = 0;
            font = 0;
            rear = 0;
       } 
        void enqueue(string value){
            /*
              นำรอเวลาในเที่ยวบินทุกอันมาตัด
              แล้วนำเข้าใส่อาเรย์ในคิว
            */
                time[rear++].settime(value.substr(0,value.find(',')));
                value.erase(0,value.find(',')+1);  // เวลาชุดที่0
                count++;

                time[rear++].settime(value.substr(0,value.find(',')));
                value.erase(0,value.find(',')+1); // เวลาชุดที่1
                count++;

                time[rear++].settime(value.substr(0,value.find(',')));
                value.erase(0,value.find(',')+1);// เวลาชุดที่2
                count++;

                time[rear++].settime(value.substr(0,value.find(',')));
                value.erase(0,value.find(',')+1);// เวลาชุดที่3
                count++;

                time[rear++].settime(value.substr(0,value.find(',')));
                value.erase(0,value.find(',')+1);// เวลาชุดที่4
                count++;
        }

          void dequeue(){
             if(isempty()){
                font = 0;
             }else if(count == 1){
                //cout << "arr is Dequeue " <<  time[font++].gettime() << endl; 
                font++;
                count--;
                font = 0;
                rear = 0;
                }
             else{
                //cout << "arr is Dequeue " << time[font++].gettime() << endl;
                font++; 
                count--;
               }      
        }
        void show(){
            for(int i =font;i<rear;i++){
                 cout << "\t\t\t " << time[i].gettime() << endl;
            }
        } 
        bool isempty(){
            if(font==rear){
                 return true;
            }else{
                return false;
            }
        } 
        bool isfull(){
            if(max==rear){
                 return true;
            }else{
                return false;
            }  
        }
        TimeAir gettimeout(int index){
            return time[index];
        }
        int checkTime(string user_time){
            for(int i = font ; i<rear ; i++){
                 if(time[i].gettime().find(user_time) != string::npos){
                    return i;
                 }
            }
            return -1;
        }
};

class Roundlist{
   public:
        int i; //i = index
        string Departure,terminal,TravelTime,timeLine;  //array string TimeOut,TimeTo     
        //Seat normalseat;   
        Roundlist *next;
        TimeQueue timeout;
        double Price;
        Roundlist(string departure,string ter,string travel,string timeline,double price){
            //set station&time
            Departure = departure;
            terminal = ter;
            TravelTime = travel;
            timeLine = timeline;
            Price = price;
            timeout.enqueue(timeline);
            next = NULL;
        }
        Roundlist(){
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
        double getpice(){
            return Price;
        }
};

class Round{
    private:
         Roundlist *head;
         Roundlist *tail;
    public:
        Round(){
            head = NULL;
            tail = NULL;
            loaddata_Airport();
           //Addtimeline();
        }
        Roundlist* gethead(){
            return head;
        }
        void addround(string departure,string terminal,string time,string timeout,double price){
             Roundlist *newnode = new Roundlist(departure,terminal,time,timeout,price);
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
            string line,departure,terminal,time,timeout,price_str;
            double price;
             if(myfile.is_open()){
                while(getline(myfile,line)){
                      departure = line.substr(0,line.find(',')); 
                      line.erase(0,line.find(',')+1);
                      terminal = line.substr(0,line.find(',')); 
                      line.erase(0,line.find(',')+1);
                      time = line.substr(0,line.find(',')); 
                      line.erase(0,line.find(',')+1);
                      price_str =  line.substr(0,line.find(','));  
                      line.erase(0,line.find(',')+1); 
                      stringstream ss;
                      ss << price_str;
                      ss >> price;
                      timeout = line.substr(0,string::npos);
                    addround(departure,terminal,time,timeout,price);
                 }  
            }else{
               cout << "   Cannot Open File" << endl;
                 }
        }//loaddata

        void printlist(){
            Roundlist *cur=head;
            cout << "\t\t\t******************************** RoundList ********************************" << endl;
             while(cur != NULL){
                 if(cur->timeout.isempty()){
          
                 }else{
                 cout << "\t\t\t The Airport : " << setw(26) << left << cur->getDepature() << " --->> "+cur->getTerminal() << endl;
                 cout << "\t\t\t TimeOut - TimeTo : \n";
                 cur->timeout.show(); 
                 cout << "\t\t\t Total Time : " << cur->getTravelTime() << endl;
                 cout << "\t\t\t---------------------------------------------------------------------------" << endl;
                 cout << endl;
                 }
                 cur = cur->next;
             }
            cout << "\t\t\t***************************************************************************" << endl;
        }
        void SortAlphabetAscending(){
            Roundlist *cur=head;
            Roundlist *temp;
            while(cur!=NULL){
                Roundlist *min = cur;
               Roundlist *nextNode = cur->next;
                while(nextNode!=NULL){
                        if(min->getDepature().compare(nextNode->getDepature())>0){
                            min = nextNode;
                        }//if
                        nextNode=nextNode->next;
                    }//while 
                        string Departure = cur->Departure;
                        string Ter = cur->terminal;
                        string Traveltime = cur->TravelTime;
                        TimeQueue Timeq = cur->timeout; 

                        cur->Departure =  min->Departure;
                        cur->terminal = min->terminal;
                        cur->TravelTime =  min->TravelTime; 
                        cur->timeout = min->timeout;

                        min->Departure = Departure;
                        min->terminal = Ter;
                        min->TravelTime = Traveltime;    
                        min->timeout = Timeq;    
                        cur = cur->next;          
            } //while
        //////////////////////////////////////////////////
        }//Sort
        void SortAlphabeDescending(){
            Roundlist *cur=head;
            Roundlist *temp;
            while(cur!=NULL){
                Roundlist *min = cur;
               Roundlist *nextNode = cur->next;
                while(nextNode!=NULL){
                        if(min->getDepature().compare(nextNode->getDepature())<0){
                            min = nextNode;
                        }//if
                        nextNode=nextNode->next;
                    }//while 
                        string Departure = cur->Departure;
                        string Ter = cur->terminal;
                        string Traveltime = cur->TravelTime;
                        TimeQueue Timeq = cur->timeout; 

                        cur->Departure =  min->Departure;
                        cur->terminal = min->terminal;
                        cur->TravelTime =  min->TravelTime; 
                        cur->timeout = min->timeout;

                        min->Departure = Departure;
                        min->terminal = Ter;
                        min->TravelTime = Traveltime;    
                        min->timeout = Timeq;    
                        cur = cur->next;          
            } //while
        //////////////////////////////////////////////////
        }//Sort
        bool CheckDeparture(string departure){
            Roundlist *temp = head;
            while(temp != NULL){
                if(temp->Departure.find(departure) != string::npos){
                    return true;
                }
                temp = temp->next;
            }
            return false;
        }
        bool CheckTerminal(string terminal){
            Roundlist *temp = head;
            while(temp != NULL){
                if(temp->terminal.find(terminal) != string::npos){
                    return true;
                }
                temp = temp->next;
            }
            return false;
        }
        void CheckTimeOut(){
                time_t now = time(0); 
                tm *ltm = localtime(&now);
                    int Hour = ltm->tm_hour;
                    int Min = ltm->tm_min;
                    Roundlist *cur = head;
                    while(cur!=NULL){
                            for(int i = 0 ;i<5;i++){
                                TimeAir pre =  cur->timeout.gettimeout(i);
                                stringstream ss;
                                int hour,min;
                                ss <<  pre.gettime().substr(0,2);
                                ss >> hour;
                                if(Hour>hour){
                                    cur->timeout.dequeue();
                                }
                            }
                        cur = cur->next;
                    }
}

         void Searchround(string departure , string Terminal){
              Roundlist *cur = head;
              while(cur != NULL){
                 // cout << cur->Departure.find(departure) << endl;
                 if(cur->Departure.find(departure) != string::npos && cur->terminal.find(Terminal) != string::npos){
                    cout << "Round : " << cur->Departure << "->" << cur->terminal << endl;
                    cur->timeout.show();
                    cout << endl;
                    cout << "Price : " <<  cur->Price << endl;
                     return;
                 } 
                cur = cur->next;
              }
              cout << "   Can't Find" << endl;
         }
         void ShowlistDeparture(){
            Roundlist *temp = head;
            Roundlist *ptemp = head;
            cout << "\t ___________________________" << endl;
            cout << "\t|                           |" << endl;
            cout << "\t|  Departure Station List   |" << endl;
            cout << "\t|___________________________|\n" << endl;
            while(ptemp != NULL){     
                if(ptemp->next == NULL){
                    cout << "         " << ptemp->Departure << "\n" << endl;
                    break;
                }else if(ptemp->Departure != ptemp->next->Departure){
                    cout << "         " << ptemp->Departure << "\n" << endl;
                }
                ptemp = ptemp->next; 
            }
            
        }
         void ShowlistTerminal(string departure){
            Roundlist *temp = head;
            cout << "\t\t ___________________________" << endl;
            cout << "\t\t|                           |" << endl;
            cout << "\t\t|   Terminal Station List   |" << endl;
            cout << "\t\t|___________________________|\n" << endl;
            while(temp != NULL){
                if(temp->Departure.find(departure) != string::npos){         
                          cout << "        " << temp->Departure  << " -> " <<  temp->terminal << "\n" << endl;
                }                     
            temp = temp->next;
            }
        }
        Roundlist* BuyTicket(string daparture , string Termenal ){
             Roundlist *temp = head;
             while(temp != NULL){
                  if(temp->Departure.find(daparture) != string::npos && temp->terminal.find(Termenal) != string::npos){
                       return temp;
                  }
                  temp = temp->next;
             } 
             return NULL;
        }

};

class Ticket{
    public:
        string Name,Departure,Terminal,Time,Dategoto,Datereturn;
        int seatNo;
        double Pice;
    void set(string departure,string terminal,double pice,int seat,string time){
        Departure = departure;
        Terminal = terminal;
        seatNo = seat;
        Pice = pice;
        Time = time;
    }   
    void setRoundTripgoto(string date){
        Dategoto = date;
    } 
    void setRoundTripreturn(string date){
        Datereturn = date;
    }
    void setRoundTripAdvance(string dategoto,string datereturn){
        Dategoto = dategoto;
        Datereturn = datereturn;
    }

    void printTicket(){
        time_t now = time(0); 
        tm *ltm = localtime(&now);
        cout << "************************** Detail Ticket **************************" << endl;
        cout  << setw(40) << left << "Departure : "+Departure << "Seat No : " << seatNo << endl;
        cout  << setw(40) << left << "Terminal : "+Terminal << "DATE : " << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
        cout  << "Price : " << Pice << " Bath" << endl;
        cout << "*******************************************************************" << endl;
    }  
    void printRoundTrip(){
        time_t now = time(0); 
        tm *ltm = localtime(&now);
        cout << "************************** Detail Back Ticket **************************" << endl;
        cout  << setw(40) << left << "Departure : "+Terminal << "SeatNo : " << seatNo << endl;
        cout  << setw(40) << left << "Terminal : "+Departure << "DATE : " << Datereturn  << endl;
        cout  << "Price : " << Pice << " Bath" << endl;
        cout << "************************************************************************" << endl;
    } 
     void printAdvacereturn(){
        time_t now = time(0); 
        tm *ltm = localtime(&now);
        cout << "************************** Detail Advace Back Ticket **************************" << endl;
        cout  << setw(40) << left << "Departure : "+Departure << "SeatNo : " << seatNo << endl;
        cout  << setw(40) << left << "Terminal : "+Terminal << "DATE : " << Datereturn  << endl;
        cout  << "Price : " << Pice << " Bath" << endl;
        cout << "************************************************************************" << endl;
    }
    void printAdvacegoto(){
        time_t now = time(0); 
        tm *ltm = localtime(&now);
        cout << "************************** Detail Advace Goto Ticket **************************" << endl;
        cout  << setw(40) << left << "Departure : "+Departure << "SeatNo : " << seatNo << endl;
        cout  << setw(40) << left << "Terminal : "+Terminal << "DATE : " << Dategoto  << endl;
        cout  << "Price : " << Pice << " Bath" << endl;
        cout << "************************************************************************" << endl;
    }

};

class CustomerUser{   
     private: 
      string Username,Password,Name,Lastname,Tel,Idcard;
      int customer_point; 
     public:
      CustomerUser *next;
      Ticket *user_ticket;
      CustomerUser(){
          next = NULL;
      }
      CustomerUser(string user_name,string pass,string name,string lname,string tel,string id_card,int point){
       //setup user
          Username = user_name;
          Password = pass;
          Name = name;
          Lastname = lname;
          Tel = tel;
          Idcard = id_card;
          customer_point = point; 
          user_ticket = new Ticket;
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
     int getpoint(){
         return customer_point;
     }
     void Setpoint(int point){
         customer_point += point; 
     }
     void Payment(double price){
         double User_price;
         string code;
        do{
         cout << "Do you Use Code? (Enter 'no' for not use) : ";  cin >> code;
        }while(code != "no" && code != "GIFZFAQWQ" && code != "weradet" && code != "FLUK");    

        if(code == "GIFZFAQWQ"){
           price = price - 500; 
         } else if(code == "weradet"){
           price = price - 700; 
         } else if(code == "FLUK"){
           price = price - 2000; 
         }              
        if(price < 0){
             price = 0;
        }
        do{
          cout << "Total : " << price << " Bath"  << endl;
          cout << "Enter Money : "; cin >> User_price;
            if(User_price < price){
               cout << "Your Pirce Less than " << price << " Bath" << endl;
            }
        }while(User_price < price);
        Setpoint(100);  
     }
     bool checkpoint(int point){
           if(customer_point >= point){
              return true;
           }
           return false;
     }
     void Changepoint(int point){
         customer_point -= point;
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
        
        void ResigerUser(string user,string pass,string name,string last,string tel,string id_card,int point){
              //เพิ่มNode
               CustomerUser *User = new CustomerUser(user,pass,name,last,tel,id_card,point); // add ไปใน node 
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
           string line,user_name,pass,name,lastname,tel,id_card,point_str;
           ifstream data("data.txt",ios::in);
           if(data.is_open()){
                  while(getline(data,line)){ 
                    user_name =  line.substr(0,line.find(','));
                                 line.erase(0,line.find(',')+1);  
                    pass   =  line.substr(0,line.find(','));
                              line.erase(0,line.find(',')+1);   
                    name   =  line.substr(0,line.find(','));
                              line.erase(0,line.find(',')+1);  
                    lastname = line.substr(0,line.find(','));
                               line.erase(0,line.find(',')+1);   
                    tel =      line.substr(0,line.find(','));
                               line.erase(0,line.find(',')+1);   
                    id_card =  line.substr(0,line.find(','));
                               line.erase(0,line.find(',')+1);
                    point_str = line.substr(0,line.find(','));             
                                line.erase(0,string::npos);   

                 stringstream ss;
                 int point;
                 ss << point_str;
                 ss >> point;                                              
                  ResigerUser(user_name,pass,name,lastname,tel,id_card,point);
            }//while
          }else{
             cout << "   Error File!!" << endl;
          } 
        }//loaddata
        bool CheckUserName(string username){
             //เช็คว่า ชื่อผู้ใช้ว่าตรงกันไหม
               CustomerUser *cur = head;
                 while(cur != NULL){
                    if(username == cur->getUsername()){
                       cout << "\t\tUsername already in use" << endl;
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
                       cout << "\t\tId Card already in use" << endl;
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
                 <<cur->getTel()<<","<<cur->getIdCard() << "," << cur->getpoint() << endl; // เขียนรายละเอียดลลงไปในไฟล์
                 cur=cur->next;
            }
            file.close(); // ปิดไฟล์
        }
        CustomerUser* getname(string username){
            CustomerUser *cur = head;
            while(cur != NULL){
                 if(cur->getUsername() == username){
                    return cur;
                 } 
                 cur = cur->next;
            }
              return NULL;
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
        cout << "   Error Show Menu!!" << endl;
    }
}//print menu

int CountDate(string date){
      int count = 0;
      for(int i = 0 ; i < date.length() ; i++ ){
           if(date[i] == '/'){
              count++; 
           }
      } 
      return count;
}

bool CheckDatePresent(string Date){
        cout << "Date : " << Date << endl;
        string day_str,month_str,year_str;
        int day,month,year;
        day_str = Date.substr(0,Date.find("/"));
                  Date.erase(0,Date.find("/")+1);
        month_str = Date.substr(0,Date.find("/")); 
                 Date.erase(0,Date.find("/")+1);
        year_str = Date.substr(0,string::npos); 
                  Date.erase(0,Date.find("/")+1);
        stringstream ss,mm,yy;
        ss << day_str;
        ss >> day;
        mm << month_str;
        mm >> month;
        yy << year_str;
        yy >> year;
        //Gen Time
        cout << day << "/"<< month << "/" << year << endl;
        time_t now = time(0); 
        tm *ltm = localtime(&now);
        if(year < 1900 + ltm->tm_year){
             return false;
        }else if(year == 1900 + ltm->tm_year){
             if(day < ltm->tm_mday && month < 1 + ltm->tm_mon){
                return false;
             }else if(day < ltm->tm_mday && month > 1 + ltm->tm_mon){
                return true;
             }
        }
        return true;
}

string pass(){
  char ch = '\0',match[20];
  for(int i = 0;i >= 0;){
    ch = getch();
    if(ch != 8 && ch != 13){
      cout << "*";
      match[i] = ch;
      i++;
    }else if(ch == 8){ // if backspace is presssed
      if(i > 0){
        cout << "\b \b"; // moves cursor to the left print <space> again move cursor to left
        i--;
      }
    }else if(ch == 13){
      match[i] = '\0'; // if enter is pressed, last character in match[] becomes null
      break;          // for end of string
    }else{
      break;
    }
  }
  return match;
}
void Enter(){
  char enter = ' ';
  cout << "Please Enter to Continue . . . ";
  while((enter = getch()) != '\r'){  
    cin >> enter;
  }
}
int main(){
    CustomerControler *customerControl = new CustomerControler(); //obj customerconntroler
    //main Program
    int main_menu;
    Round *round = new Round();
    Ticket *ticket = new Ticket();
    time_t my_time = time(NULL); 
      //round->CheckTimeOut();
       round->CheckTimeOut();
  do{
       mainmenu: 
      // customerControl->show();
       //system("cls");
       printmenu();
       cout <<"  \t\t\t\t\t       " << ctime(&my_time);
    try{
       cout <<  "Choose Menu (1-4) : "; cin >> main_menu; //user Input
       if (!cin){
         throw main_menu;
       }//if
       else if(main_menu == 1){
           //user Loggin
         int menu_guest;  
         string username,user_pass = "";
         char star;
          do{
             system("cls");
           cout << endl;   
           cout << "\t\t+========================+" << endl;
           cout << "\t\t+         Guest          +" << endl;
           cout << "\t\t+========================+" << endl;
           cout << "\t\t+ 1.Buy Ticket           +" << endl;
           cout << "\t\t+ 2.Flights              +" << endl;
           cout << "\t\t+ 3.Back To Main Menu    +" << endl;
           cout << "\t\t+========================+\n" << endl;
           try
           {
                cout << "\t\tPlease Enter Choice : "; cin >> menu_guest;
                if(!cin)
                  throw menu_guest;
           }
           catch(int menu)///asdasdasd
           {
                cin.clear(); 
                cin.ignore(100, '\n'); 
           }
            if(menu_guest == 1){
                system("cls");
                     int menu_buy;
                cout << endl;   
                cout << "\t\t+========================+" << endl;
                cout << "\t\t+         Guest          +" << endl;
                cout << "\t\t+========================+" << endl;
                cout << "\t\t+ 1.One Way              +" << endl;
                cout << "\t\t+ 2.Round Trip           +" << endl;
                cout << "\t\t+ 3.Advance              +" << endl;
                cout << "\t\t+ 4.Back To Main Menu    +" << endl;
                cout << "\t\t+========================+\n" << endl;
                cout << "\t\tPlease Enter Choice : ";
                cin >> menu_buy;
                    if(menu_buy == 1){
                        string Departure,Terminal;
                        round->SortAlphabetAscending();
                         system("cls");
                        round->ShowlistDeparture();
                        do{
                        cout << "Choose Departure Staion (Abbreviation 3 Characture) : ";                      
                            cin >> Departure;
                            for(int i = 0; i< Departure.length() ; i++){
                                 Departure[i] = toupper(Departure[i]);
                               }
                            if(Departure.length() > 3 || Departure.length() < 3 || round->CheckDeparture(Departure) == false){
                                 cout << "   Abbreviation is 3 Characture! " << endl;
                            }
                        }while(Departure.length()>3 || Departure.length()<3 || round->CheckDeparture(Departure) == false);
                        round->SortAlphabetAscending();
                         system("cls");
                        round->ShowlistTerminal(Departure);
                        do{
                        cout << "Choose Terminal Staion (Abbreviation 3 Characture) : ";     
                            cin >> Terminal;
                            for(int i = 0; i< Terminal.length() ; i++){
                                Terminal[i] = toupper(Terminal[i]);
                               }
                            if(Terminal.length() > 3 || Terminal.length() < 3 || round->CheckTerminal(Terminal) == false){
                                 cout << "   Abbreviation is 3 Characture! " << endl;
                            }
                        }while(Terminal.length()>3 || Terminal.length()<3 || round->CheckTerminal(Terminal) == false);
                        
                            Roundlist *Buy = new Roundlist;
                            string time;
                            Buy = round->BuyTicket(Departure,Terminal);
                            if(Buy != NULL){
                            Buy->timeout.show();
                            cout << "Choose the Time : "; cin >> time;
                            if(Buy->timeout.checkTime(time) != -1){
                                int seat,preple,Total=0;
                                cout << "How People? : "; cin >> preple;
                                ///////////////////////
                                for(int i = 1 ; i <= preple ; i++){
                                Buy->timeout.time[Buy->timeout.checkTime(time)].showseatNormal();
                                do{
                                cout << "Input Seat Ex.(01) : "; cin >> seat;
                                  if(seat > 59 || seat < 0){
                                      cout << "   Threre are not Seat!! " << endl;
                                     }
                                  }while(seat > 59 || seat < 0);

                                Buy->timeout.time[Buy->timeout.checkTime(time)].normalseat.setseat(seat);
                                Buy->timeout.time[Buy->timeout.checkTime(time)].showseatNormal();
                                ticket->set(Buy->Departure,Buy->terminal,Buy->Price,seat,time);
                                ticket->printTicket();
                                Enter();
                                Total += Buy->Price;
                                    }
                                  cout << endl;
                                  cout << "\t\t ___________________________________" << endl;
                                  cout << "\t\t|                                   |" << endl;
                                  cout << "\t\t|  Total cost " << preple << " People = " << Total << " Bath  |" << endl;
                                  cout << "\t\t|___________________________________|\n" << endl;
                                  Enter();
                                 }else{
                                  cout << "   NOT TIME" << endl;
                               }
                            }else{
                                cout << "   Error" << endl;
                            }
                        //    Enter();
                    }
                    else if(menu_buy == 2){                     
                         string Departure,Terminal;
                        round->SortAlphabetAscending();
                          system("cls");
                        round->ShowlistDeparture();
                        do{
                        cout << endl;
                        cout << "Choose Departure Staion (Abbreviation 3 Characture) : ";                      
                            cin >> Departure;
                            for(int i = 0; i< Departure.length() ; i++){
                                 Departure[i] = toupper(Departure[i]);
                               }
                            if(Departure.length() > 3 || Departure.length() < 3 || round->CheckDeparture(Departure) == false){
                                 cout << "   Abbreviation is 3 Characture! " << endl;
                            }
                        }while(Departure.length()>3 || Departure.length()<3 || round->CheckDeparture(Departure) == false);
                        round->SortAlphabetAscending();
                          system("cls");
                        round->ShowlistTerminal(Departure);
                        do{
                        cout << "Choose Terminal Staion (Abbreviation 3 Characture) : ";     
                            cin >> Terminal;
                            for(int i = 0; i< Terminal.length() ; i++){
                                Terminal[i] = toupper(Terminal[i]);
                               }
                            if(Terminal.length() > 3 || Terminal.length() < 3 || round->CheckTerminal(Terminal) == false){
                                 cout << "   Abbreviation is 3 Characture! " << endl;
                            }
                        }while(Terminal.length()>3 || Terminal.length()<3 || round->CheckTerminal(Terminal) == false);                     
                            Roundlist *BuyGo = new Roundlist;
                            Roundlist *BuyBack = new Roundlist;
                            string timeto,timeback,date;
                            BuyGo = round->BuyTicket(Departure,Terminal);
                            BuyBack = round->BuyTicket(Terminal,Departure);
                            do{
                                loop:
                              cout << "Input Return date Ex.(1/05/2012) : "; cin >> date;
                                if(CheckDatePresent(date) == false){
                                      cout << "   Input again!! " << endl;
                                      goto loop;
                                  } 
                            
                            }while(CountDate(date) != 2);
                            
                            if(BuyGo != NULL){

                                    BuyGo->timeout.show();
                                    cout << "Choose the Time To : "; cin >> timeto;
                                    BuyBack->timeout.show();
                                    cout << "Choose the Time Back : "; cin >> timeback;

                                    if(BuyGo->timeout.checkTime(timeto) != -1 && BuyBack->timeout.checkTime(timeback)){
                                        int seat,preple,Total=0;
                                        cout << "How Preple? : "; cin >> preple;

                                        for(int i = 1 ; i <= preple ; i++){
                                        BuyGo->timeout.time[BuyGo->timeout.checkTime(timeto)].showseatNormal();

                                        do{
                                          cout << "Input Seat Ex.(01) : "; cin >> seat;
                                          if(seat > 59 || seat < 1){
                                            cout << "Threre are not Seat!! " << endl;
                                            }
                                        }while(seat > 59 || seat < 1);
                                        //linklist Total Round -> Queue Time -> time [ index ] -> Seat Normal -> Set Seat 
                                            BuyGo->timeout.time[BuyGo->timeout.checkTime(timeto)].normalseat.setseat(seat);
                                            BuyGo->timeout.time[BuyGo->timeout.checkTime(timeto)].showseatNormal();
                                            ticket->set(BuyGo->Departure,BuyGo->terminal,BuyGo->Price,seat,timeto);
                                            ticket->setRoundTripreturn(date);
                                            ticket->printTicket();
                                            ticket->printRoundTrip();
                                            Total += BuyGo->Price;
                                            Total *= 2;
                                            }
                                    // cout<< "test : " << Buy->timeout.checkTime(time) << endl;
                                        cout << "Total = " << Total << " Bath" << endl;
                                        Enter();
                                    }else{
                                        cout << "   NOT TIME" << endl;
                                    }
                            }else{
                                cout << "   Error" << endl;
                            }

                    }
                    else if(menu_buy == 3){
                        int menu_ad;
                        
                        do{
                            system ("cls");
                            cout << endl;
                            cout << "\t\t******************************" << endl;
                            cout << "\t\t*  1. Advance One Way        *" << endl;
                            cout << "\t\t*  2. Advance Round Trip     *" << endl;
                            cout << "\t\t*  3. Back to Menu           *" << endl;
                            cout << "\t\t******************************" << endl;
                            cout << "\t\tPlease Input the choice : "; cin >> menu_ad;
                            if(!cin){
                                cin.clear(); 
                                cin.ignore(100, '\n'); 
                            }else if(menu_ad == 1){
                              
                             string Departure,Terminal;
                             round->SortAlphabetAscending();
                             system("cls");
                             round->ShowlistDeparture();
                                    do{
                                    cout << "Choose Departure Staion (Abbreviation 3 Characture) : ";                      
                                        cin >> Departure;
                                        for(int i = 0; i< Departure.length() ; i++){
                                            Departure[i] = toupper(Departure[i]);
                                        }
                                        if(Departure.length() > 3 || Departure.length() < 3 || round->CheckDeparture(Departure) == false){
                                            cout << "   Abbreviation is 3 Characture! " << endl;
                                        }
                                    }while(Departure.length()>3 || Departure.length()<3 || round->CheckDeparture(Departure) == false);
                                    round->SortAlphabetAscending();
                                    system("cls");
                                    round->ShowlistTerminal(Departure);
                                    do{
                                    cout << "Choose Terminal Staion (Abbreviation 3 Characture) : ";     
                                        cin >> Terminal;
                                        for(int i = 0; i< Terminal.length() ; i++){
                                            Terminal[i] = toupper(Terminal[i]);
                                        }
                                        if(Terminal.length() > 3 || Terminal.length() < 3 || round->CheckTerminal(Terminal) == false){
                                            cout << "   Abbreviation is 3 Characture! " << endl;
                                        }
                                    }while(Terminal.length()>3 || Terminal.length()<3 || round->CheckTerminal(Terminal) == false);
                                        
                                        Roundlist *Buy = new Roundlist;
                                        string time,date;
                                        Buy = round->BuyTicket(Departure,Terminal);
                                            do{
                                            thisis:
                                              cout << "Input Return date Ex.(1/05/2012) : "; cin >> date;
                                                if(CheckDatePresent(date) == false){
                                                 cout << "   Input again!! " << endl;
                                                 goto thisis;                                              
                                                 } 
                                            }while(CountDate(date) != 2);
                                        if(Buy != NULL){
                                        Buy->timeout.show();
                                        cout << "Choose the Time : "; cin >> time;
                                        if(Buy->timeout.checkTime(time) != -1){
                                            int seat,preple,Total=0;
                                            cout << "How People? : "; cin >> preple;
                                            for(int i = 1 ; i <= preple ; i++){
                                            Buy->timeout.time[Buy->timeout.checkTime(time)].showseatNormal();
                                            do{
                                            cout << "Input Seat Ex.(01) : "; cin >> seat;
                                            if(seat > 59 || seat < 1){
                                                cout << "   Threre are not Seat!! " << endl;
                                                }
                                            }while(seat > 59 || seat < 1);
                                            //linklist Total Round -> Queue Time -> time [ index ] -> Seat Normal -> Set Seat 
                                            Buy->timeout.time[Buy->timeout.checkTime(time)].normalseat.setseat(seat);
                                            Buy->timeout.time[Buy->timeout.checkTime(time)].showseatNormal();
                                            ticket->set(Buy->Departure,Buy->terminal,Buy->Price,seat,time);
                                            ticket->setRoundTripgoto(date);
                                            ticket->printAdvacegoto();
                                            Total += Buy->Price;
                                                }
                                        // cout<< "test : " << Buy->timeout.checkTime(time) << endl;
                                            cout << "Total = " << Total << " Bath" << endl;
                                            Enter();
                                            }else{
                                            cout << "   NOT TIME" << endl;
                                        }
                                        }else{
                                            cout << "   Error" << endl;
                                        }
                            }else if(menu_ad == 2){
                                string Departure,Terminal;
                                round->SortAlphabetAscending();
                                system("cls");
                                round->ShowlistDeparture();
                                do{
                                cout << "Choose Departure Staion (Abbreviation 3 Characture) : ";                      
                                    cin >> Departure;
                                    for(int i = 0; i< Departure.length() ; i++){
                                        Departure[i] = toupper(Departure[i]);
                                    }
                                    if(Departure.length() > 3 || Departure.length() < 3 || round->CheckDeparture(Departure) == false){
                                        cout << "   Abbreviation is 3 Characture! " << endl;
                                    }
                                }while(Departure.length()>3 || Departure.length()<3 || round->CheckDeparture(Departure) == false);
                                round->SortAlphabetAscending();
                                system("cls");
                                round->ShowlistTerminal(Departure);
                                do{
                                cout << "Choose Terminal Staion (Abbreviation 3 Characture) : ";     
                                    cin >> Terminal;
                                    for(int i = 0; i< Terminal.length() ; i++){
                                        Terminal[i] = toupper(Terminal[i]);
                                    }
                                    if(Terminal.length() > 3 || Terminal.length() < 3 || round->CheckTerminal(Terminal) == false){
                                        cout << "   Abbreviation is 3 Characture! " << endl;
                                    }
                                }while(Terminal.length()>3 || Terminal.length()<3 || round->CheckTerminal(Terminal) == false);                     
                                    Roundlist *BuyGo = new Roundlist;
                                    Roundlist *BuyBack = new Roundlist;
                                    string timeto,timeback,dategoto,datereturn;
                                    BuyGo = round->BuyTicket(Departure,Terminal);
                                    BuyBack = round->BuyTicket(Terminal,Departure);
                                    do{
                                        loop2:
                                    cout << "Please enter the day you want to go Ex.(1/12/2020) : "; cin >> dategoto;
                                        if(CheckDatePresent(dategoto) == false){
                                            cout << "   Input again!! " << endl;
                                            goto loop2;
                                        }     
                                    }while(CountDate(dategoto) != 2);
                                    
                                    do{
                                        loop3:
                                    cout << "Please enter the day you want to back Ex.(1/12/2020) : "; cin >> datereturn;
                                        if(CheckDatePresent(datereturn) == false){
                                            cout << "   Input again!! " << endl;
                                            goto loop3;
                                        }     
                                    }while(CountDate(datereturn) != 2);

                                    if(BuyGo != NULL){

                                            BuyGo->timeout.show();
                                            cout << "Choose the Time To : "; cin >> timeto;
                                            BuyBack->timeout.show();
                                            cout << "Choose the Time Back : "; cin >> timeback;

                                            if(BuyGo->timeout.checkTime(timeto) != -1 && BuyBack->timeout.checkTime(timeback)){
                                                int seat,preple,Total=0;
                                                cout << "How Preple? : "; cin >> preple;

                                                for(int i = 1 ; i <= preple ; i++){
                                                BuyGo->timeout.time[BuyGo->timeout.checkTime(timeto)].showseatNormal();

                                                do{
                                                cout << "Input Seat Ex.(01) : "; cin >> seat;
                                                if(seat > 59 || seat < 1){
                                                    cout << "   Threre are not Seat!! " << endl;
                                                    }
                                                }while(seat > 59 || seat < 1);
                                                    BuyGo->timeout.time[BuyGo->timeout.checkTime(timeto)].normalseat.setseat(seat);
                                                    BuyGo->timeout.time[BuyGo->timeout.checkTime(timeto)].showseatNormal();
                                                    ticket->set(BuyGo->Departure,BuyGo->terminal,BuyGo->Price,seat,timeto);
                                                    ticket->setRoundTripgoto(dategoto);
                                                    ticket->setRoundTripreturn(datereturn);
                                                    ticket->printAdvacegoto();
                                                    ticket->printAdvacereturn();
                                                    Total += BuyGo->Price;
                                                    Total *= 2;
                                                    }                                          
                                                cout << "Total = " << Total << " Bath" << endl;
                                                Enter();
                                            }else{
                                                cout << "   NOT TIME" << endl;
                                            }
                                    }else{
                                        cout << "   Error" << endl;
                                    }
                                }
                        }while(menu_ad != 3);
                    }
            }
             if(menu_guest == 2){
                 int menu_view;
                 system ("cls");
                  do{
                     cout << "\t\t******************************" << endl;
                     cout << "\t\t*  1. Show ALL Filghts       *" << endl;
                     cout << "\t\t*  2. Search Filghts         *" << endl;  
                     cout << "\t\t*  3. Back to Main Menu      *" << endl;
                     cout << "\t\t******************************\n" << endl;
                     cout << "Please choose choice : ";
                     cin >> menu_view;
                        if(menu_view==1){
                             int menu_sort;
                            do{
                                system("cls");
                                cout << "\t\t************************************" << endl;
                                cout << "\t\t*  1.Sort By AlphaBet Descending   *" << endl;
                                cout << "\t\t*  2.Sort By AlphaBet Ascending    *" << endl; 
                                cout << "\t\t*  3.Back to Main Menu             *" << endl;
                                cout << "\t\t************************************\n" << endl;
                                cout << "Please choose choice : ";
                                cin >> menu_sort;
                                 if(menu_sort == 1){
                                     round->SortAlphabeDescending();
                                     round->printlist();
                                     Enter();
                                 }else if(menu_sort==2){
                                     round->SortAlphabetAscending();
                                     round->printlist();
                                     Enter();
                                 }                               
                            }while(menu_sort !=3);    
                        }  
                        else if(menu_view==2){
                            string departure,desination;
                            cin.ignore();
                            cout << "Please Input Departure : "; getline(cin,departure);
                            cout << "Please Input Termonal : ";getline(cin,desination);
                            round->Searchround(departure,desination);
                        }
                  }while(menu_view!=3);
             }
          }while(menu_guest != 3);
       }//else if
       else if(main_menu == 2){
           int member_menu;
           int member_loggin;
           string username,user_pass="";
           do{
            cout << endl;
            cout << "\t\tPlease Enter Username : "; cin >> username; //ใส่ username
            cout << "\t\tPlease Enter Password : ";  user_pass = pass();
             if(customerControl->LogginCustomer(username,user_pass)){
                  CustomerUser *temp = customerControl->getname(username);
                    do{
                        system("cls");
                        cout << endl; 
                        cout << "Welcome : " << temp->getName() << "\t" << temp->getLastname() << endl;
                        cout << endl;   
                        cout << "\t\t+========================+" << endl;
                        cout << "\t\t+         Member         +" << endl;
                        cout << "\t\t+========================+" << endl;
                        cout << "\t\t+ 1.Buy Ticket           +" << endl;
                        cout << "\t\t+ 2.Flights              +" << endl;
                        cout << "\t\t+ 3.Promotion            +" << endl;
                        cout << "\t\t+ 4.Point                +" << endl;
                        cout << "\t\t+ 5.Back to Main Menu    +" << endl;
                        cout << "\t\t+========================+\n" << endl; 
                        try{
                          cout << "\t\tPlease Enter Choice : "; cin >> member_menu;
                          if(!cin)
                          throw member_menu;
                          }
                        catch(int menu)
                         {
                        cin.clear(); 
                        cin.ignore(100, '\n'); 
                          }
                        if(member_menu == 1){

                            int menu_buy_member;
                          do{
                              system("cls");
                                cout << endl;   
                                cout << "\t\t+========================+" << endl;
                                cout << "\t\t+         Member         +" << endl;
                                cout << "\t\t+========================+" << endl;
                                cout << "\t\t+ 1.One Way              +" << endl;
                                cout << "\t\t+ 2.Round Trip           +" << endl;
                                cout << "\t\t+ 3.Advance              +" << endl;
                                cout << "\t\t+ 4.Back to Main Menu    +" << endl;
                                cout << "\t\t+========================+\n" << endl;
                                cout << "\t\tChoose your choice : ";
                                cin >> menu_buy_member;
                                if(!cin){
                                    cin.clear(); 
                                    cin.ignore(100, '\n'); 
                                }
                                else if(menu_buy_member == 1){
                                    string Departure,Terminal;
                                    round->SortAlphabetAscending();
                                    system("cls");
                                    round->ShowlistDeparture();
                                    do{
                                    cout << "Choose Departure Staion (Abbreviation 3 Characture) : ";                      
                                        cin >> Departure;
                                        for(int i = 0; i< Departure.length() ; i++){
                                            Departure[i] = toupper(Departure[i]);
                                        }
                                        if(Departure.length() > 3 || Departure.length() < 3 || round->CheckDeparture(Departure) == false){
                                            cout << "   Abbreviation is 3 Characture! " << endl;
                                        }
                                    }while(Departure.length()>3 || Departure.length()<3 || round->CheckDeparture(Departure) == false);
                                    round->SortAlphabetAscending();
                                    system("cls");
                                    round->ShowlistTerminal(Departure);
                                    do{
                                    cout << "Choose Terminal Staion (Abbreviation 3 Characture) : ";     
                                        cin >> Terminal;
                                        for(int i = 0; i< Terminal.length() ; i++){
                                            Terminal[i] = toupper(Terminal[i]);
                                        }
                                        if(Terminal.length() > 3 || Terminal.length() < 3 || round->CheckTerminal(Terminal) == false){
                                            cout << "   Abbreviation is 3 Characture! " << endl;
                                        }
                                    }while(Terminal.length()>3 || Terminal.length()<3 || round->CheckTerminal(Terminal) == false);
                                    
                                        Roundlist *Buy = new Roundlist;
                                        string time;
                                        Buy = round->BuyTicket(Departure,Terminal);
                                    if(Buy != NULL){
                                        Buy->timeout.show();
                                        cout << "Choose the Time : "; cin >> time;
                                        if(Buy->timeout.checkTime(time) != -1){
                                            int seat,preple,Total=0;
                                            cout << "How Preple? : "; cin >> preple;
                                            for(int i = 1 ; i <= preple ; i++){
                                            Buy->timeout.time[Buy->timeout.checkTime(time)].showseatNormal();
                                            do{
                                            cout << "Input Seat Ex.(01) : "; cin >> seat;
                                            if(seat > 59 || seat < 1){
                                                cout << "   Threre are not Seat!! " << endl;
                                                }
                                            }while(seat > 59 || seat < 1);
                                            //linklist Total Round -> Queue Time -> time [ index ] -> Seat Normal -> Set Seat 
                                            Buy->timeout.time[Buy->timeout.checkTime(time)].normalseat.setseat(seat);
                                            Buy->timeout.time[Buy->timeout.checkTime(time)].showseatNormal();
                                            temp->user_ticket->set(Buy->Departure,Buy->terminal,Buy->Price,seat,time);
                                            temp->user_ticket->printTicket();
                                            Total += Buy->Price;
                                                }
                                            cout << "Total = " << Total << " Bath" << endl;
                                            temp->Payment(Total);

                                            }else{
                                            cout << "   NOT TIME" << endl;
                                        }
                                    }else{
                                            cout << "   Error" << endl;
                                        }
                                        goto mainmenu;
                                } // if one way
                                else if(menu_buy_member == 2){

                                     string Departure,Terminal;
                                round->SortAlphabetAscending();
                                system("cls");
                                round->ShowlistDeparture();
                                do{
                                cout << "Choose Departure Staion (Abbreviation 3 Characture) : ";                      
                                    cin >> Departure;
                                    for(int i = 0; i< Departure.length() ; i++){
                                        Departure[i] = toupper(Departure[i]);
                                    }
                                    if(Departure.length() > 3 || Departure.length() < 3 || round->CheckDeparture(Departure) == false){
                                        cout << "   Abbreviation is 3 Characture! " << endl;
                                    }
                                }while(Departure.length()>3 || Departure.length()<3 || round->CheckDeparture(Departure) == false);
                                round->SortAlphabetAscending();
                                system("cls");
                                round->ShowlistTerminal(Departure);
                                do{
                                cout << "Choose Terminal Staion (Abbreviation 3 Characture) : ";     
                                    cin >> Terminal;
                                    for(int i = 0; i< Terminal.length() ; i++){
                                        Terminal[i] = toupper(Terminal[i]);
                                    }
                                    if(Terminal.length() > 3 || Terminal.length() < 3 || round->CheckTerminal(Terminal) == false){
                                        cout << "   Abbreviation is 3 Characture! " << endl;
                                    }
                                }while(Terminal.length()>3 || Terminal.length()<3 || round->CheckTerminal(Terminal) == false);                     
                                    Roundlist *BuyGo = new Roundlist;
                                    Roundlist *BuyBack = new Roundlist;
                                    string timeto,timeback,date;
                                    BuyGo = round->BuyTicket(Departure,Terminal);
                                    BuyBack = round->BuyTicket(Terminal,Departure);
                                    do{
                                        isloop:
                                    cout << "Input Return date Ex.(1/05/2012) : "; cin >> date;
                                        if(CheckDatePresent(date) == false){
                                            cout << "   Input again!! " << endl;
                                            goto isloop;
                                        } 
                                    
                                    }while(CountDate(date) != 2);
                                    
                                    if(BuyGo != NULL){

                                            BuyGo->timeout.show();
                                            cout << "Choose the Time To : "; cin >> timeto;
                                            BuyBack->timeout.show();
                                            cout << "Choose the Time Back : "; cin >> timeback;

                                            if(BuyGo->timeout.checkTime(timeto) != -1 && BuyBack->timeout.checkTime(timeback)){
                                                int seat,preple,Total=0;
                                                cout << "How Preple? : "; cin >> preple;

                                                for(int i = 1 ; i <= preple ; i++){
                                                   BuyGo->timeout.time[BuyGo->timeout.checkTime(timeto)].showseatNormal();

                                                  do{
                                                      cout << "Input Seat Ex.(01) :"; cin >> seat;
                                                      if(seat > 59 || seat < 1){
                                                        cout << "   Threre are not Seat!! " << endl;
                                                        }
                                                     }while(seat > 59 || seat < 1);
                                                //linklist Total Round -> Queue Time -> time [ index ] -> Seat Normal -> Set Seat 
                                                    BuyGo->timeout.time[BuyGo->timeout.checkTime(timeto)].normalseat.setseat(seat);
                                                    BuyGo->timeout.time[BuyGo->timeout.checkTime(timeto)].showseatNormal();
                                                    temp->user_ticket->set(BuyGo->Departure,BuyGo->terminal,BuyGo->Price,seat,timeto);
                                                    temp->user_ticket->setRoundTripreturn(date);
                                                    temp->user_ticket->printTicket();
                                                    temp->user_ticket->printRoundTrip();
                                                    Total += BuyGo->Price;
                                                    Total *= 2;
                                                    }//for
                                                  cout << "Total = " << Total << " Bath" << endl;
                                                  temp->Payment(Total);
                                                  Enter();
                                            }else{
                                                cout << "   NOT TIME" << endl;
                                            }
                                    }else{
                                        cout << "   Error" << endl;
                                    }
                                } // else if round trip
                                else if(menu_buy_member == 3){
                                    int menu_ad;
                                    do{
                                        system("cls");
                                        cout << endl;
                                        cout << "\t\t*****************************" << endl;
                                        cout << "\t\t*  1. Advance One Way       *" << endl;
                                        cout << "\t\t*  2. Advance Round Trip    *" << endl;
                                        cout << "\t\t*  3. Back to Menu          *" << endl;
                                        cout << "\t\t*****************************" << endl;
                                        cout << "\t\tPlease Input the choice : "; cin >> menu_ad;
                                        if(!cin){
                                            cin.clear(); 
                                            cin.ignore(100, '\n'); 
                                        }else if(menu_ad == 1){
                                       
                                        string Departure,Terminal;
                                        round->SortAlphabetAscending();
                                        system("cls");
                                        round->ShowlistDeparture();
                                                do{
                                                cout << "Choose Departure Staion (Abbreviation 3 Characture) : ";                      
                                                    cin >> Departure;
                                                    for(int i = 0; i< Departure.length() ; i++){
                                                        Departure[i] = toupper(Departure[i]);
                                                    }
                                                    if(Departure.length() > 3 || Departure.length() < 3 || round->CheckDeparture(Departure) == false){
                                                        cout << "   Abbreviation is 3 Characture! " << endl;
                                                    }
                                                }while(Departure.length()>3 || Departure.length()<3 || round->CheckDeparture(Departure) == false);
                                                round->SortAlphabetAscending();
                                                system("cls");
                                                round->ShowlistTerminal(Departure);
                                                do{
                                                cout << "Choose Terminal Staion (Abbreviation 3 Characture) : ";     
                                                    cin >> Terminal;
                                                    for(int i = 0; i< Terminal.length() ; i++){
                                                        Terminal[i] = toupper(Terminal[i]);
                                                    }
                                                    if(Terminal.length() > 3 || Terminal.length() < 3 || round->CheckTerminal(Terminal) == false){
                                                        cout << "   Abbreviation is 3 Characture! " << endl;
                                                    }
                                                }while(Terminal.length()>3 || Terminal.length()<3 || round->CheckTerminal(Terminal) == false);
                                                    
                                                    Roundlist *Buy = new Roundlist;
                                                    string time,date;
                                                    Buy = round->BuyTicket(Departure,Terminal);
                                                        do{
                                                        thisis2:
                                                        cout << "Input Return date Ex.(1/05/2012) : "; cin >> date;
                                                            if(CheckDatePresent(date) == false){
                                                            cout << "   Input again!! " << endl;
                                                            goto thisis2;                                              
                                                            } 
                                                        }while(CountDate(date) != 2);
                                                    if(Buy != NULL){
                                                    Buy->timeout.show();
                                                    cout << "Choose the Time : "; cin >> time;
                                                    if(Buy->timeout.checkTime(time) != -1){
                                                        int seat,preple,Total=0;
                                                        cout << "How Preple? : "; cin >> preple;
                                                        for(int i = 1 ; i <= preple ; i++){
                                                        Buy->timeout.time[Buy->timeout.checkTime(time)].showseatNormal();
                                                        do{
                                                        cout << "Input Seat Ex.(01) : "; cin >> seat;
                                                        if(seat > 59 || seat < 1){
                                                            cout << "   Threre are not Seat!! " << endl;
                                                            }
                                                        }while(seat > 59 || seat < 1);
                                                        //linklist Total Round -> Queue Time -> time [ index ] -> Seat Normal -> Set Seat 
                                                        Buy->timeout.time[Buy->timeout.checkTime(time)].normalseat.setseat(seat);
                                                        Buy->timeout.time[Buy->timeout.checkTime(time)].showseatNormal();
                                                        ticket->set(Buy->Departure,Buy->terminal,Buy->Price,seat,time);
                                                        ticket->setRoundTripgoto(date);
                                                        ticket->printAdvacegoto();
                                                        Total += Buy->Price;
                                                            }
                                                    // cout<< "test : " << Buy->timeout.checkTime(time) << endl;
                                                        cout << "Total = " << Total << " Bath" << endl;
                                                        temp->Payment(Total);
                                                        Enter();
                                                        }else{
                                                        cout << "   NOT TIME" << endl;
                                                        }
                                                    }else{
                                                        cout << "   Error" << endl;
                                                    }
                                        }else if(menu_ad == 2){
                                string Departure,Terminal;
                                round->SortAlphabetAscending();
                                Enter();
                                system("cls");
                                round->ShowlistDeparture();
                                Enter();
                                do{
                                cout << "Choose Departure Staion (Abbreviation 3 Characture) : ";                      
                                    cin >> Departure;
                                    for(int i = 0; i< Departure.length() ; i++){
                                        Departure[i] = toupper(Departure[i]);
                                    }
                                    if(Departure.length() > 3 || Departure.length() < 3 || round->CheckDeparture(Departure) == false){
                                        cout << "   Abbreviation is 3 Characture! " << endl;
                                    }
                                }while(Departure.length()>3 || Departure.length()<3 || round->CheckDeparture(Departure) == false);
                                round->SortAlphabetAscending();
                                system("cls");
                                round->ShowlistTerminal(Departure);
                                do{
                                cout << "Choose Terminal Staion (Abbreviation 3 Characture) : ";     
                                    cin >> Terminal;
                                    for(int i = 0; i< Terminal.length() ; i++){
                                        Terminal[i] = toupper(Terminal[i]);
                                    }
                                    if(Terminal.length() > 3 || Terminal.length() < 3 || round->CheckTerminal(Terminal) == false){
                                        cout << "   Abbreviation is 3 Characture! " << endl;
                                    }
                                }while(Terminal.length()>3 || Terminal.length()<3 || round->CheckTerminal(Terminal) == false);                     
                                    Roundlist *BuyGo = new Roundlist;
                                    Roundlist *BuyBack = new Roundlist;
                                    string timeto,timeback,dategoto,datereturn;
                                    BuyGo = round->BuyTicket(Departure,Terminal);
                                    BuyBack = round->BuyTicket(Terminal,Departure);
                                    do{
                                        loop5:
                                    cout << "Please enter the day you want to go Ex.(1/12/2020) : "; cin >> dategoto;
                                        if(CheckDatePresent(dategoto) == false){
                                            cout << "   Input again !! " << endl;
                                            goto loop5;
                                        }     
                                    }while(CountDate(dategoto) != 2);
                                    
                                    do{
                                        loop6:
                                    cout << "Please enter the day you want to back Ex.(1/12/2020) : "; cin >> datereturn;
                                        if(CheckDatePresent(datereturn) == false){
                                            cout << "   Input again !! " << endl;
                                            goto loop6;
                                        }     
                                    }while(CountDate(datereturn) != 2);

                                    if(BuyGo != NULL){

                                            BuyGo->timeout.show();
                                            cout << "Choose the Time To : "; cin >> timeto;
                                            BuyBack->timeout.show();
                                            cout << "Choose the Time Back : "; cin >> timeback;

                                            if(BuyGo->timeout.checkTime(timeto) != -1 && BuyBack->timeout.checkTime(timeback)){
                                                int seat,preple,Total=0;
                                                cout << "How Preple? : "; cin >> preple;

                                                for(int i = 1 ; i <= preple ; i++){
                                                BuyGo->timeout.time[BuyGo->timeout.checkTime(timeto)].showseatNormal();

                                                do{
                                                cout << "Input Seat Ex.(01) : "; cin >> seat;
                                                if(seat > 59 || seat < 1){
                                                    cout << "   Threre are not Seat!! " << endl;
                                                    }
                                                }while(seat > 59 || seat < 1);
                                                //linklist Total Round -> Queue Time -> time [ index ] -> Seat Normal -> Set Seat 
                                                    BuyGo->timeout.time[BuyGo->timeout.checkTime(timeto)].normalseat.setseat(seat);
                                                    BuyGo->timeout.time[BuyGo->timeout.checkTime(timeto)].showseatNormal();
                                                    ticket->set(BuyGo->Departure,BuyGo->terminal,BuyGo->Price,seat,timeto);
                                                    ticket->setRoundTripgoto(dategoto);
                                                    ticket->setRoundTripreturn(datereturn);
                                                    //ticket->printTicket();
                                                    ticket->printAdvacegoto();
                                                    ticket->printAdvacereturn();
                                                    Total += BuyGo->Price;
                                                    Total *= 2;
                                                    }                                          
                                            // cout<< "test : " << Buy->timeout.checkTime(time) << endl;
                                                cout << "Total = " << Total << " Bath" << endl;
                                                temp->Payment(Total);
                                                Enter();
                                            }else{
                                                cout << "   NOT TIME" << endl;
                                            }
                                    }else{
                                        cout << "   Error" << endl;
                                    }
                                }
                                    }while(menu_ad != 3);
                                }
                        }while(menu_buy_member != 4);
                    
                        }else if(member_menu == 2){
                               int menu_view;
                               system ("cls");
                                do{
                                    cout << endl;
                                    cout << "\t\t****************************" << endl;
                                    cout << "\t\t*  1. Show ALL Filghts     *" << endl;
                                    cout << "\t\t*  2. Search Filghts       *" << endl;  
                                    cout << "\t\t*  3. Back to Main Menu    *" << endl;
                                    cout << "\t\t****************************" << endl;
                                    cout << "Please choose : ";
                                    cin >> menu_view;
                                        if(menu_view==1){
                                            int menu_sort;
                                            do{
                                            system("cls");
                                            cout << endl;
                                            cout << "\t\t************************************" << endl;
                                            cout << "\t\t*  1.Sort By AlphaBet Descending   *" << endl;
                                            cout << "\t\t*  2.Sort By AlphaBet Ascending    *" << endl; 
                                            cout << "\t\t*  3.Back to Main Menu             *" << endl;
                                            cout << "\t\t************************************" << endl;
                                            cout << "Please choose : ";
                                            cin >> menu_sort;
                                                if(menu_sort == 1){
                                                    round->SortAlphabeDescending();
                                                    round->printlist();
                                                    Enter();
                                                }else if(menu_sort==2){
                                                    round->SortAlphabetAscending();
                                                    round->printlist();
                                                    Enter();
                                                }                               
                                            }while(menu_sort !=3);    
                                        }  
                                        else if(menu_view==2){
                                            string departure,desination;
                                            cin.ignore();
                                            cout << "Please Input Departure : "; getline(cin,departure);
                                            // cin.ignore();
                                            cout << "Please Input Terminal : ";getline(cin,desination);
                                            round->Searchround(departure,desination);
                                        }
                                }while(menu_view!=3);//

                        }else if(member_menu == 3){
                              CustomerUser *temp = customerControl->getname(username);
                            int answer;
                            do{
                                promotion:
                                system("cls");
                               cout << "\t\t________________________________________________________" << endl;
                               cout << "\t\t|                   All Promotions!!!                  |" << endl;
                               cout << "\t\t|   1. 3,000 Point Discount 500 Bath :                 |" << endl;
                               cout << "\t\t|   2. 5,000 Point Discount 700 Bath :                 |" << endl;
                               cout << "\t\t|   3. 10,000 Point Discount 2,000 Bath for family :   |" << endl;
                               cout << "\t\t|   4. Back to menu                                    |" << endl;
                               cout << "\t\t|______________________________________________________|" << endl;
                               cout << "Please Choose Promotion : "; cin >> answer;
                               if(!cin){
                                 cin.clear(); 
                                 cin.ignore(100, '\n'); 
                               }
                               switch (answer)
                               {
                               case 1:
                                   char commit; 
                                   cout << "Your Point is : " << temp->getpoint () << endl;
                                   cout << "Do you want to Commit Promotion? (y/n) : ";  cin >> commit;
                                    if(commit == 'y'){
                                        if(temp->checkpoint(3000)){
                                             cout << "Success!!" << endl;
                                             temp->Changepoint(3000); 
                                             cout << "Code : " << "GIFZFAQWQ" << endl;
                                             Enter();
                                        }else
                                        {
                                            cout << "   Cannot " << endl;
                                        }    
                                    }
                                    else{
                                        goto  promotion;
                                    }
                                   break;
                                 case 2:
                                   char commitPro2; 
                                   cout << "Your Point is : " << temp->getpoint () << endl;
                                   cout << "Do you want to Commit Promotion? (y/n) :";  cin >> commitPro2;
                                    if(commitPro2 == 'y'){
                                        if(temp->checkpoint(5000)){
                                             cout << "Success!!" << endl;
                                             temp->Changepoint(5000); 
                                             cout << "Code : " << "weradet" << endl;
                                             Enter();
                                        }else
                                        {
                                            cout << "   Cannot " << endl;
                                        }    
                                    }
                                    else{
                                        goto  promotion;
                                    }   
                                    break;
                                 case 3:
                                   char commitPro3; 
                                   cout << "Your Point is : " << temp->getpoint () << endl;
                                   cout << "Do you want to Commit Promotion? (y/n) :";  cin >> commitPro3;
                                    if(commitPro3 == 'y'){
                                        if(temp->checkpoint(10000)){
                                             cout << "Success!!" << endl;
                                             temp->Changepoint(10000); 
                                             cout << "Code : " << "FLUK" << endl;
                                             Enter();
                                        }else
                                        {
                                            cout << "   Cannot " << endl;
                                        }    
                                    }
                                    else{
                                        goto  promotion;
                                    }   
                                    break;   
                               
                               } // switch
                            }while(answer != 4);
                       

                        }else if(member_menu == 4){
                            cout << "Name : " << temp->getName() << "\t" << temp->getLastname() << endl;
                            cout << "Your Point is : " << temp->getpoint () << endl;
                            cout << endl;
                            Enter();
                        } 
                    }while(member_menu != 5);
                    goto mainmenu;
               }else{
                   cout << "    Invalid Username and Password" << endl;  
                   goto mainmenu;
               }
         }while(member_loggin != 2);
       }
       else if(main_menu == 3){
          //user register
          string username,user_pass = "",name,lastname,tel,id_card; //ประกาศตัวแปร
          char is_commit;
          system("cls");
          cout << endl;
          cout << "\t\t+==========================+" << endl;
          cout << "\t\t+         Register         +" << endl;
          cout << "\t\t+==========================+" << endl;
          cout << "\t\t+ Please Enter Information +" << endl;
          cout << "\t\t+==========================+" << endl;
             do{
                 //เช็คว่ามีชื่อผู้ใช้หรือไม่
              cout << "\t\tPlease Enter Username : "; cin >> username; //ใส่ username
             }while(customerControl->CheckUserName(username)!=false);
             string pass_again = "";
            do{
              cout << "\t\tPlease Enter Password : ";            cin >> user_pass; //ใส่รหัสผ่าน
              cout << "\t\tConfirm password again : ";    cin >> pass_again; //ใส่รหัสผ่าน
            }while(user_pass!=pass_again);
              cout << endl;
              cout << "\t\tYour Password ID is OK\n" << endl;
              cout << "\t\tPlease Enter Name : ";                cin >> name; // กรอกชื่อ
              cout << "\t\tPlease Enter Lastname : ";            cin >> lastname;  // กรอกนามสกุล
            
            do{
                 cout << "\t\tPlease Enter Identification Card : "; cin >> id_card;
                if(id_card.length()<13 || id_card.length()>13){
                    //เช็คว่าผู้ใช้ป้อนรหัสมา13หลักหรือไม่
                    cout << "   Identification Card At least 13 digit!!" << endl; 
                }
            }while(customerControl->CheckIdCard(id_card)!=false&&id_card.length()==13);
            
              cout << "\t\tPlease Enter Telephone Number : ";    cin >> tel;  // กรอกนามสกุล
              cout << "\t\tDo you want to continue? (y/n) : ";  cin >> is_commit;
             while(is_commit!='y'&&is_commit!='n'){
                 //ถ้าผู้ใช้ไม่กด y และ n จะให้กรอกไหม่
                  cout << "   Please Enter (y or n)" << endl;
                  cout << "\t\tDo you want to continue? (y/n) : ";  cin >> is_commit;
             }//while

             if(is_commit == 'y'){
                 customerControl->ResigerUser(username,user_pass,name,lastname,tel,id_card,0);  
                 customerControl->writefile();
                 cout << "   Save Complete!!" << endl;
                 Enter();
             }
             else if(is_commit == 'n'){
                 cout << "   Cannot Save" << endl;
                 Enter();
             }
       }//if Register
    }catch(int x){  
         cin.clear(); 
         cin.ignore(100, '\n'); 
    }
  }while(main_menu!=4);
   customerControl->writefile();
}//main
