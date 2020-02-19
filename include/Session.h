#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include <map>
#include "Action.h"

class User;
class Watchable;

class Session {
private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string, User*> userMap;
    User *activeUser;
    std::map<std::string,std::vector<Watchable*>> contentByTags;

public:
    //Constructor
    Session(const std::string &configFilePath);

    //Rule of 5
    ~Session();//destructor
    Session(const Session& other);//copy constructor
    Session(Session &&other);//Move constructor

    // Copy Assignment
    Session& operator=(const Session &other);

    // Move Assignment
    Session& operator=(Session &&other);


    //Methods
    void start();
    std::vector<Watchable *> getContent();
    void printContentList(std::string* ErrMsg);
    void OrderTagsByPop(Watchable* watchable);
    void printActionsLog(std::string* ErrMsg);
    User* getActiveUser();
    void addAction(BaseAction*);
    std::unordered_map<std::string, User*> getUserMap();
    void createUser(const std::string& name,const std::string& code,std::string* ErrMsg);
    std::map<std::string,std::vector<Watchable*>> getContentByTags();
    void deleteUser(const std::string& name,std::string* ErrMsg);
    bool DoesUserExist(const std::string& name);
    void duplicateUser(const std::string& name,const std::string& newname,std::string* ErrMsg);
    void changeActiveUser(const std::string&,std::string* ErrMsg);
    void printActiveUserWatchHistory(std::string* ErrMsg);
    void watch(long id,std::string* ErrMsg,Session& s);
    void copy(const Session &other);
    void destroy();

};

#endif