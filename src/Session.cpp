#include <vector>
#include <unordered_map>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <json.hpp>
#include "../include/Action.h"
#include "../include/Session.h"
#include "../include/User.h"
#include "../include/Watchable.h"

using namespace std;
using json=nlohmann::json;
//-----------------------------------------SESSION---------------------------------------
//PUBLIC
//Constructors
Session::Session(const std::string &configFilePath): content(std::vector<Watchable *>()), actionsLog(std::vector<BaseAction *>()), userMap(unordered_map<std::string, User *>()), activeUser(
        nullptr), contentByTags(std::map<std::string,std::vector<Watchable*>>()) {

    auto* def = new LengthRecommenderUser("default");
    userMap.insert(make_pair("default",def));
    activeUser = def;

        ifstream l(configFilePath);
        json k;
        l >> k;
        string s=k.dump(1);
        l.close();
        long id=1;
        for(auto &n: k["movies"].items()) {
            string name = n.value()["name"];
            int length = n.value()["length"];
            vector<string> tags;
            for (const auto& tag:n.value()["tags"].items()) {
                tags.push_back(tag.value());
            }
            content.push_back(new Movie(id, name, length, tags));
            id++;
        }
            for(auto &n: k["tv_series"].items()) {
                string name = n.value()["name"];
                int length = n.value()["episode_length"];
                vector<string> tags;
                for (const auto& tag:n.value()["tags"].items()) {
                    tags.push_back(tag.value());
                }
                int seasonCount = 1;
                for (const auto& season:n.value()["seasons"].items()) {
                    int seasonSize = season.value();
                    for (int episode = 1; episode <=seasonSize; episode++) {
                        content.push_back(new Episode(id, name, length, seasonCount, episode, tags));
                        id++;
                    }
                    seasonCount++;
                }

                Watchable* lastOfSeason = content.at(content.size()-1);
                lastOfSeason->setNextEpisodeId(-1);
            }

            for(auto p=content.begin(); p!=content.end();p++){
                OrderTagsByPop(p.operator*());
            }
}

//Rule of 5
//Destructor
Session::~Session(){
    destroy();
}

//Copy Constructor
Session::Session(const Session &other):content(std::vector<Watchable *>()), actionsLog(std::vector<BaseAction *>()), userMap(unordered_map<std::string, User *>()),activeUser(
        nullptr), contentByTags(std::map<std::string,std::vector<Watchable*>>())  {

    //copy content
    for(auto iter : other.content){
       content.push_back(iter->clone());
    }

    //copy userMap
    for(const auto & iter : other.userMap){
        userMap.insert({iter.second->getName(), iter.second->clone()});
    }

    //copy active user
    std::string activeUserName = other.activeUser->getName();
    activeUser = userMap[activeUserName];

    //copy actions log
    for(auto iter : other.actionsLog){
        actionsLog.push_back(iter->clone());
    }

    //order content by tags
    for(auto p=content.begin(); p!=content.end();p++){
        OrderTagsByPop(p.operator*());
    }
}

//Move constructor
Session::Session(Session &&other): content(other.content), actionsLog(other.actionsLog), userMap(other.userMap), activeUser(other.activeUser), contentByTags(other.contentByTags){
    other.content.clear();
    other.actionsLog.clear();
    other.userMap.clear();
    other.contentByTags.clear();
}

// Copy Assignment
Session& Session::operator=(const Session &other){
    if (this != &other)
    {
        destroy();
        this->copy(other);
    }
    return *this;
}

// Move Assignment
Session& Session::operator=(Session &&other){
    if (this != &other)
    {
        destroy();
        this->copy(other);
        other.destroy();
    }
    return *this;
}

//Methods
void Session::start(){
    auto& refToSess = *this;

    cout<<"SPLFLIX is now on!\n";
    string input;
    cin >> input;
    while(input!="exit") {
        if (input == "createuser"){
            cin >> input;
            string username=input;
            cin >> input;
            string code=input;
            auto* create = new CreateUser(username,code) ;
            create->act(refToSess);
        }
        if(input == "changeuser"){
            cin >> input;
            string change=input;
            auto* changeAU = new ChangeActiveUser({change});
            changeAU->act(refToSess);
        }
        if(input=="deleteuser") {
            cin >> input;
            string toDelete=input;
            auto* deleteU = new DeleteUser({toDelete});
            deleteU->act(refToSess);
        }
        if(input=="dupuser") {
            cin >> input;
            string ToDuplicate=input;
            cin >> input;
            string newDuplicate=input;

            auto* dupU = new DuplicateUser(ToDuplicate,newDuplicate);
            dupU->act(refToSess);
        }
        if(input == "content") {
            auto* printCL = new PrintContentList();
            printCL->act(refToSess);
        }
        if(input == "watchhist") {
            auto* printH = new PrintWatchHistory();
            printH->act(refToSess);
        }
        if(input=="watch"){
            cin >> input;
            string watch=input;
            long id=std::stol(watch);
            auto* watch1 = new Watch(id);
            watch1->act(refToSess);
        }
        if(input=="log"){
            auto* printAL = new PrintActionsLog();
            printAL->act(refToSess);
        }
         cin >> input;
    }
    auto* exit=new Exit();
    exit->act(refToSess);
}

std::vector<Watchable*> Session::getContent(){ return content;}
void Session::printContentList(std::string* ErrMsg) {
    try {
        for (auto watchable : content) {
            cout << watchable->getId() << ". "
                 << watchable->toString() << " "
                 << watchable->getLength() << " minutes [";

            vector<string> tagsOut = watchable->getTags();
            for(auto tagIter = tagsOut.begin(); tagIter != tagsOut.end()-1; tagIter++){
                string tag = *tagIter;
                cout << tag << ",";
            }
            string finalTag = *(watchable->getTags().end()-1);
            cout << finalTag << "]\n";


        }
    } catch(exception&) {*ErrMsg = "Could not print content";}
}
void Session::printActionsLog(std::string* ErrMsg) {
    if (!(actionsLog).empty()) {
        for (auto action = actionsLog.begin(); action != actionsLog.end(); action++) {
            BaseAction* base = *action;
            cout << base->toString() << endl;
        }
    } else {
        *ErrMsg = "Actions Log is empty";
    }
}
User* Session::getActiveUser(){
    return activeUser;
}
void Session::addAction(BaseAction* base){
    actionsLog.push_back(base);
}
std::unordered_map<std::string, User*> Session::getUserMap(){
    return userMap;
}
void Session::createUser(const std::string& userName,const std::string& Code,std::string* ErrMsg){

    if(getUserMap().find(userName) == getUserMap().end() && (Code=="rer"||Code=="gen"||Code=="len")) {
        if(Code=="rer"){
            userMap.insert({userName,new RerunRecommenderUser(userName)});
        }
        else if(Code=="len"){
            userMap.insert({userName,new LengthRecommenderUser(userName)});
        }
        else if(Code=="gen"){
            userMap.insert({userName,new GenreRecommenderUser(userName)});
        }

    }
    else if(this->getUserMap().find(userName)!=this->getUserMap().end())
    {
        *ErrMsg = "Username already exists";
    }
    else if(Code!="rer" && Code!="gen" && Code!="len")
    {
        *ErrMsg="Wrong Recommendation Code";
    }

}
std::map<std::string,std::vector<Watchable*>> Session::getContentByTags(){return contentByTags;}
void Session::OrderTagsByPop(Watchable* watchable){
    vector<string> tags=watchable->getTags();
    for (const auto& newTag : tags){
        if(contentByTags.find(newTag)==contentByTags.end())
        {
            std::vector<Watchable*> toAdd;
            contentByTags.insert({newTag,toAdd});
            contentByTags[newTag].push_back(watchable);
        }
        else
        {
            contentByTags[newTag].push_back(watchable);
        }
    }

}
void Session::deleteUser(const std::string& userName,std::string* ErrMsg){
    if(DoesUserExist(userName)){
        auto& toDelete = userMap.find(userName)->second;
        delete toDelete;
        userMap.erase(userName);
    }
    else
    {
        *ErrMsg = "User does not exist";
    }
}
bool Session::DoesUserExist(const std::string& userName){
    return this->getUserMap().find(userName) != this->getUserMap().end();
}
void Session::duplicateUser(const std::string& userName,const std::string& newName,std::string* ErrMsg){
    if(DoesUserExist(userName)&&!DoesUserExist(newName)){
    createUser(newName,userMap.find(userName).operator*().second->getCode(),ErrMsg);
    userMap.find(newName).operator*().second->copy(userMap.find(userName).operator*().second->get_history());
    } else if(!DoesUserExist(userName)){
        *ErrMsg = "User does not exist";
    }
    else if(DoesUserExist(newName))
    {
        *ErrMsg="Username already taken";
    }
}
void Session::changeActiveUser(const std::string& name,std::string* ErrMsg)
{
    if(getUserMap().find(name) != getUserMap().end()){
        activeUser=this->getUserMap().find(name)->second;
    }
    else
    {
        *ErrMsg = "User does not exist";
    }
}
void Session::printActiveUserWatchHistory(std::string* ErrMsg){
    if (!(getActiveUser()->get_history().empty())) {
        getActiveUser()->printWatchHistory();
    }
    else
    {
        *ErrMsg = "History List is Empty";
    }
}
void Session::watch(long id, std::string* ErrMsg,Session& s){
    unsigned long a=id;
    if(a <= content.size()) {
        Watchable *watchable = getContent().at(unsigned (abs (id-1)));
        activeUser->watch(watchable, s);
    }
    else *ErrMsg = "Failed to watch";
}
void Session::copy(const Session &other) {
    //copy content
    for(auto& watchable: other.content){
        content.push_back(watchable->clone());
    }

    //copy content by tags
    for(auto& contentbt: other.contentByTags){
        string tag = contentbt.first;
        vector<Watchable*> list = vector<Watchable*>();

        for(auto iter = contentbt.second.begin(); iter != contentbt.second.end(); iter++){
            auto watchable = *iter;
            list.push_back(watchable);
        }

        contentByTags.insert(make_pair(tag, list));
    }

    //copy actions log
    for(auto &log : other.actionsLog){
        this->actionsLog.push_back(log->clone());
    }

    //copty user map
    for(auto &users : other.userMap){
        this->userMap[users.first]=users.second->clone();
    }

    //assigning active user to new address
    string activeUserName = other.activeUser->getName();
    activeUser = userMap.find(activeUserName)->second;
}
void Session::destroy(){

    //clear content by tags
    for(auto contentByTag : contentByTags){
        contentByTag.second.clear();
    }
    contentByTags.clear();

    //clear content
    for(auto &watchable : content) {
        watchable->destroy();
        watchable = nullptr;
    }

    content.clear();
    content.shrink_to_fit();

    //clear actions log
    for(auto &action : actionsLog) {
        delete action;
    }
    actionsLog.clear();
    actionsLog.shrink_to_fit();

    //clear users
    for(auto &user : userMap) {
        delete user.second;
    }
    userMap.clear();

    activeUser = nullptr;
}


