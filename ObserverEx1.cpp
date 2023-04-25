#include <iostream>
#include <string>
#include <list>

using namespace std;

class ObserverInterface{
    public:
        virtual ~ObserverInterface(){};
        
        virtual void update(const string &messageFromSubject) = 0;
};

class SubjectInterface{
    public:
        virtual ~SubjectInterface(){};
        
        virtual void subcribe(ObserverInterface *o) = 0;
        virtual void unsubcribe(ObserverInterface *o) = 0;
        virtual void notify() = 0;
};

class MySubject: public SubjectInterface{
    private: list<ObserverInterface *> observerList; string message; 
    public:
        virtual ~MySubject(){ cout << "Goodbye, I was the Subject.\n"; };
        
        void subcribe(ObserverInterface *o){ observerList.push_back(o); }
        void unsubcribe(ObserverInterface *o){ observerList.remove(o); }
        void notify(){ list<ObserverInterface *>::iterator iterator = observerList.begin();
            HowManyObserver();
            while(iterator != observerList.end()){
                (*iterator)->update(message);
                ++iterator;
            }
        }
        
        void HowManyObserver(){ cout << "There are " << observerList.size() << " observers in the list.\n"; }
        void createMessage(string message){ this->message = message; notify(); }
        void someBussinessLogic(){
            this->message = "change message message";
            notify();
            cout << "I'm about to do some thing important\n";
        }
};

class MyObserver: public ObserverInterface{
    private:
        string messageFromSubject;
        MySubject &subject;
        static int staticNumber;
        int number;
    public:
        MyObserver(MySubject &subject_): subject(subject_){
            this->subject.subcribe(this);
            cout << "Hi, I'm the Observer \"" << ++MyObserver::staticNumber << "\".\n";
            this->number = MyObserver::staticNumber;
        }
        virtual ~MyObserver(){ cout << "Goodbye, I was the Observer \"" << this->number << "\".\n";}
        
        void update(const string &subjectMessage){ messageFromSubject = subjectMessage; printInfo(); }
        
        void removeMeFromTheList(){
            subject.unsubcribe(this);
            cout << "Observer \"" << number << "\" removed from the list.\n";
        }
        
        void printInfo(){
            cout << "Observer \"" << this->number << "\": a new message is available --> " << this->messageFromSubject << "\n";
        }
};

int MyObserver::staticNumber = 0;

void ClientCode(){
    MySubject *subject = new MySubject;
    MyObserver *o1 = new MyObserver(*subject);
    MyObserver *o2 = new MyObserver(*subject);
    MyObserver *o3 = new MyObserver(*subject);
    MyObserver *o4;
    
    subject->createMessage("Hello new day!");
    o3->removeMeFromTheList();
    
    subject->createMessage("Today on our news");
    o4 = new MyObserver(*subject);
      
    subject->createMessage("Messi has just won the 2023 World Cup");
    
      delete o4;
      delete o3;
      delete o2;
      delete o1;
      delete subject;
}

int main()
{
    ClientCode();
    return 0;
}
