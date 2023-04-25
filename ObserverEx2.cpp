#include <iostream>
#include <list>

using namespace std;

class Observer{
    public:
        virtual ~Observer(){};
        
        virtual void update(const string &temp, const string &humidity, int pressure) = 0;
};

class Subject{
    public:
        virtual ~Subject(){};
    
        virtual void registerObserver(Observer *o) = 0;
    	virtual void notifyObserver() = 0;
    	virtual void removeObserver(Observer *o) = 0;
};

class Display{
    public:
        virtual ~Display(){};
        
        virtual void display() = 0;
};

class WeatherData: public Subject{ private: list<Observer *> observerList; string temp; string humidity; int pressure;
    public:
        WeatherData(){}
        virtual ~WeatherData(){ cout << "Goodbye, I was the WeatherData.\n"; }
        
        void setMeasurements(string humidity, string temp, int pressure){
            this->temp = temp; this->humidity = humidity; this->pressure = pressure; 
            notifyObserver();
        }
        
        
        void registerObserver(Observer *o){ observerList.push_back(o); }
        void notifyObserver(){
		    list<Observer *>::iterator iterator = observerList.begin();
            HowManyObserver();
            while(iterator != observerList.end()){
                (*iterator)->update(temp, humidity, pressure);
                ++iterator;
            }
        }
        void removeObserver(Observer *o){ observerList.remove(o); }
        
        
        string getHumidity(){ return humidity; }; void setHumidity(string humidity){ this->humidity = humidity; notifyObserver(); }
        string getTemperature(){ return temp; }; void setTemperature(string temp){ this->temp = temp; notifyObserver(); }
        int getPressure(){ return pressure; }; void setPressure(int p){ this->pressure = pressure; notifyObserver(); }
        
        void HowManyObserver(){ cout << "There are " << observerList.size() << " observers in the list.\n"; }
};

class AnimeDisplay: public Observer, Display{
    private:
        string temp; string humidity; int pressure;
        WeatherData &subject;
        static int staticNumber;
        int number;
    public:
        AnimeDisplay(WeatherData &subject): subject(subject){
            this->subject.registerObserver(this);
            cout << "Hi, I'm the AnimeDisplay \"" << ++AnimeDisplay::staticNumber << "\".\n";
            this->number = AnimeDisplay::staticNumber;
        }
    
        virtual ~AnimeDisplay(){ cout << "Goodbye, I was the AnimeDisplay \"" << this->number << "\".\n"; };
        
        void removeMeFromTheList(){
            subject.removeObserver(this);
            cout << "AnimeDisplay \"" << number << "\" removed from the list.\n";
        }
        
        void update(const string &temp, const string &humidity, int pressure) {
    		this->humidity = humidity;
    		this->temp = temp;
    		this->pressure = pressure;
    	}
    	
    	void display(){
    	    cout << ("Today weather reoport by animation: ") << endl;
    		cout << "Bunch of beautiful animation ++++++ " << temp << " ++++++++ HuMidiTy" << humidity << endl;
    	}
};
int AnimeDisplay::staticNumber = 0;

class StatisticDisplay: public Observer, Display{
     private:
        string temp; string humidity; int pressure;
        WeatherData &subject;
        static int staticNumber;
        int number;
    public:
        StatisticDisplay(WeatherData &subject): subject(subject){
            this->subject.registerObserver(this);
            cout << "Hi, I'm the StatisticDisplay \"" << ++StatisticDisplay::staticNumber << "\".\n";
            this->number = StatisticDisplay::staticNumber;
        }
    
        virtual ~StatisticDisplay(){ cout << "Goodbye, I was the StatisticDisplay \"" << this->number << "\".\n"; };
        
        void removeMeFromTheList(){
            subject.removeObserver(this);
            cout << "StatisticDisplay \"" << number << "\" removed from the list.\n";
        }
        
        void update(const string &temp, const string &humidity, int pressure) {
    		this->humidity = humidity;
    		this->temp = temp;
    		this->pressure = pressure;
    	}
    	
    	void display(){
    	    cout << ("Today weather reoport: ") << endl;
    		cout << "Temperature: " << temp << " ----- Humidity: " << humidity << endl;
    	}
};
int StatisticDisplay::staticNumber = 0;

void ClientCode(){
    WeatherData *weatherData = new WeatherData;
    AnimeDisplay *o1 = new AnimeDisplay(*weatherData);
    AnimeDisplay *o2 = new AnimeDisplay(*weatherData);
    StatisticDisplay *o3 = new StatisticDisplay(*weatherData);
    StatisticDisplay *o4;
    
    weatherData->setMeasurements("30*C", "Very Wet", 10);
    o1->display();
    o2->display();
    o3->display();
    
    o1->removeMeFromTheList();
    o3->removeMeFromTheList();
    
    o4 = new StatisticDisplay(*weatherData);
		
	weatherData->setMeasurements("45*C", "Very Hot", 10);
    o4->display();
    
    delete weatherData;
    delete o1, o2, o3, o4;
}

int main()
{
    ClientCode();
    return 0;
}
