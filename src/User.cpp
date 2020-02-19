#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include "../include/User.h"
#include "../include/Watchable.h"
#include "../include/Session.h"

using namespace std;
//---------------------------USER-------------------------------
//PUBLIC
//Constructors
User::User(const std::string&  name): history(vector<Watchable*>()), name(std::move(name)){}

//Rule of 5
User::~User(){
    history.clear();

} //destructor


void User::copy(vector<Watchable*> other_history){
history = other_history; // NOLINT(performance-unnecessary-value-param)
}

//Methods
std::string User::getName() const{ return name;}
std::vector<Watchable*> User::get_history() const{
    vector<Watchable*> output = history;
    return output;
}
void User::printWatchHistory(){
    cout << "Watch history for " << name << "!\n";
    int index = 1;
    for(auto watchable : history) {
        std::string toString = watchable->toString();
        cout << index << ". " << toString << endl;
        index++;
    }
}
void User::watch(Watchable* watchable, Session& session){

    string toString = watchable->toString();
    cout << "Watching " << toString << "!" << endl;

    addWatchableToHistory(watchable);
    additionalWatchActions(watchable);

    Watchable* watchNext = watchable->getNextWatchable(session);
    if(watchNext == nullptr) watchNext = getRecommendation(session);

    if(watchNext != nullptr) {
        string answer;
        cout << "We recommend watching " << watchNext->toString() << ", continue watching? [y/n]\n";
        cin >> answer;
        if (answer == "y") {
            choseRec();
            auto *watchRec = new Watch(watchNext->getId());
            watchRec->act(session);
        }

        while (!(answer == "y" || answer == "n")) {
            cout << "Invalid input. Continue watching? [y/n]";
            cin >> answer;

            if (answer == "y") {
                choseRec();
                auto *watchRec = new Watch(watchNext->getId());
                watchRec->act(session);
            }
        }
    }

    else cout << "No more recommended content available! Go to sleep!" << endl;
}
void User::clearHistory() {history.clear();}
void User::addWatchableToHistory(Watchable* watchable) {
    if(!isWatchableInHistory(watchable)) history.push_back(watchable);
}
//PROTECTED
//Methods
bool User::isWatchableInHistory(Watchable* watchable){
    if(history.empty()) return false;
    else return (std::find(history.begin(), history.end(), watchable) != history.end());
}
void User::setHistory(vector<Watchable*> newHistory){ history = newHistory;} // NOLINT(performance-unnecessary-value-param)



//------------------------------------LengthRecommenderUser------------------------------------
//PUBLIC
//Constructors
LengthRecommenderUser::LengthRecommenderUser(const std::string& name): User(name), avgLength(0){}

//Rule of 5
LengthRecommenderUser::~LengthRecommenderUser(){
    avgLength = 0;
} //destructor
LengthRecommenderUser::LengthRecommenderUser(LengthRecommenderUser& other, const string& name): User(name), avgLength(other.getAvgLength()){
    setHistory(other.get_history());
} //copy constructor
LengthRecommenderUser& LengthRecommenderUser::operator=(LengthRecommenderUser& other){
    if(this != &other){
        this->clearHistory();
        this->setHistory(other.get_history());
        this->setAvgLength(other.getAvgLength());
    }

    return (*this);
} //copy assignment operator //
LengthRecommenderUser::LengthRecommenderUser(LengthRecommenderUser&& other, const string& name): User(name), avgLength(other.avgLength){
    setHistory(other.get_history());
    other.clearHistory();
} //move constructor
LengthRecommenderUser& LengthRecommenderUser::operator=(LengthRecommenderUser&& other){
    if(this != &other){
        clearHistory();
        history = other.get_history();
        avgLength = other.avgLength;
    }
    return *this;
} //move assignment operator

//Methods
Watchable* LengthRecommenderUser::getRecommendation(Session& s){
    vector<Watchable*> content = s.getContent();
    Watchable* bestMatch = nullptr;
    double bestMatchDiff = 99999999999;
    double currentDiff;

    for(auto current : content){
        if(!isWatchableInHistory(current)) {

            if(bestMatch == nullptr){
                bestMatch = current;
                bestMatchDiff = abs(current->getLength() - avgLength);
            }
            else {
                currentDiff = abs(current->getLength() - avgLength);
                if (currentDiff < bestMatchDiff) {
                    bestMatch = current;
                    bestMatchDiff = currentDiff;
                }
                if (currentDiff == bestMatchDiff && (*current).toString().compare(bestMatch->toString()) < 0) {
                    bestMatch = current;
                    bestMatchDiff = currentDiff;
                }
            }
        }
    }

    return bestMatch;
}
std::string LengthRecommenderUser::getCode(){
    return "len";
}
double LengthRecommenderUser::getAvgLength() { return avgLength;}
User* LengthRecommenderUser::clone(){
    auto newClone = new LengthRecommenderUser(*this, getName());
    return newClone;
}

//PROTECTED
void LengthRecommenderUser::additionalWatchActions(Watchable* watchable){
    long hSizeL = history.size(); //History vector size
    int hSize=(int) hSizeL;
    int wLen = watchable->getLength(); //Length of the recently watched watchable

    avgLength = ((avgLength *(hSize-1) +wLen) /hSize);
}
void LengthRecommenderUser::setAvgLength(double newAvg) {avgLength = newAvg;}
void LengthRecommenderUser::choseRec() {}

//-------------------------------RerunRecommenderUser-------------------------
//PUBLIC
//Constructors
RerunRecommenderUser::RerunRecommenderUser(const std::string &name): User(name), lastRecommended(0) {}

//Rule of 5
RerunRecommenderUser::RerunRecommenderUser(const RerunRecommenderUser& other, const string &name): User(name), lastRecommended(other.lastRecommended) {
    history = other.get_history();
} //copy constructor
RerunRecommenderUser::~RerunRecommenderUser() {lastRecommended=0;}; //destructor
RerunRecommenderUser& RerunRecommenderUser::operator=(const RerunRecommenderUser& other){
    if(this != &other){
        lastRecommended = other.lastRecommended;
        clearHistory();
        history.assign(other.get_history().begin(), other.get_history().end());
    }

    return (*this);
} //copy assignment operator
RerunRecommenderUser::RerunRecommenderUser(RerunRecommenderUser&& other): User(other.getName()), lastRecommended(other.lastRecommended)
{
    setHistory(other.get_history());
    other.clearHistory();
    other.lastRecommended = 0;
} //move constructor
RerunRecommenderUser& RerunRecommenderUser::operator=(RerunRecommenderUser&& other){
    if(this != &other){
        history = other.get_history();
        lastRecommended = other.lastRecommended;

        other.clearHistory();
    }
    return *this;
} //move assignment operator

//Methods
Watchable* RerunRecommenderUser::getRecommendation(Session& s){
    return history.at(lastRecommended %history.size());
}
User* RerunRecommenderUser::clone(){
    auto newClone = new RerunRecommenderUser(*this, getName());
    return newClone;
}
std::string RerunRecommenderUser::getCode(){
    return "rer";
}

//PROTECTED
//Methods
void RerunRecommenderUser::additionalWatchActions(Watchable* watchable){watchable->getId();}
void RerunRecommenderUser::choseRec() { lastRecommended++;}


//---------------------------------GenreRecommenderUser----------------------------------------
//PUBLIC
//Constructor
GenreRecommenderUser::GenreRecommenderUser(const std::string& name): User(name),tagsByPopularity(std::set<pair<int, string>>()){}

//Rule of 5
GenreRecommenderUser::~GenreRecommenderUser(){
    tagsByPopularity.clear();
} //destructor
GenreRecommenderUser::GenreRecommenderUser(const GenreRecommenderUser& other, const string& name): User(name), tagsByPopularity(other.tagsByPopularity){} //copy constructor
GenreRecommenderUser& GenreRecommenderUser::operator=(const GenreRecommenderUser& other){
    if(this != &other){
        this->setHistory(other.get_history());
        tagsByPopularity = other.tagsByPopularity;
    }

    return *this;
} //copy assignment operator
GenreRecommenderUser::GenreRecommenderUser(GenreRecommenderUser&& other): User(other.getName()), tagsByPopularity(other.tagsByPopularity){
    setHistory(other.get_history());
    other.clearHistory();
    tagsByPopularity.clear();
} //move constructor
GenreRecommenderUser& GenreRecommenderUser::operator=(GenreRecommenderUser&& other){
    if(this != &other){
        clearHistory();
        history = other.get_history();
        tagsByPopularity = other.tagsByPopularity;
        other.tagsByPopularity.clear();
    }

    return *this;
}

//Methods
Watchable* GenreRecommenderUser::getRecommendation(Session& s){
    bool done = false;
    Watchable* recommendation = nullptr;
    vector<Watchable*> contentInSession;

    for(auto iterator1 = tagsByPopularity.begin(); iterator1 != tagsByPopularity.end() && !done; iterator1++){
        pair<int, string> tag = *iterator1;
        contentInSession = s.getContentByTags()[tag.second];

        for(auto iterator2 = contentInSession.begin(); iterator2 != contentInSession.end() && !done; iterator2++){
            Watchable* watchable = *iterator2;
            if(!isWatchableInHistory(watchable)){
                recommendation = watchable;
                done = true;
            }
        }
    }

    return recommendation;
}
User* GenreRecommenderUser::clone(){
    auto newClone = new GenreRecommenderUser(*this, getName());
    return newClone;
}
std::string GenreRecommenderUser::getCode(){
    return "gen";
}

//PROTECTED
//Methods
void GenreRecommenderUser::additionalWatchActions(Watchable* watchable){
    const vector<string>& tagsList = watchable->getTags();
    for(auto iterator = tagsList.rbegin(); iterator != tagsList.rend(); iterator++) {
        string tag = *iterator;
        bool isFound = false;

        //find tag in tagsByPopularity
        if (tagsByPopularity.empty()) tagsByPopularity.insert({make_pair(1000000, tag)}); //if it's the first tag of the first movie, automaticly add the tag
        else {

            for(const auto& tagPair : tagsByPopularity){
                if(tagPair.second == tag){
                    tagsByPopularity.insert(make_pair(tagPair.first-1, tag));
                    tagsByPopularity.erase(tagPair);
                    isFound = true;
                }

                if(isFound) break;
            }
        }

        if(!isFound) tagsByPopularity.insert({make_pair(1000000, tag)});
        }

    }

void GenreRecommenderUser::choseRec() {}

bool Comp::operator() (const pair<int, string>& lhs, const pair<int, string>& rhs) const{
    if(lhs.first > rhs.first) return true;
    if(lhs.first < rhs.first) return false;
    return lhs.second.compare(rhs.second) < 0;
}