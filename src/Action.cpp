#include "../include/Action.h"
#include "../include/Session.h"
#include <string>
#include <iostream>
#include <utility>

//---------------------------------------BASE ACTION--------------------------------------
BaseAction::BaseAction():errorMsg(""), status(PENDING){}
BaseAction::~BaseAction()=default;
ActionStatus BaseAction::getStatus() const { return status;}
void BaseAction::complete() {status = COMPLETED;}
void BaseAction::error(const std::string& errMsg){
    status = ERROR;
    std::cout << errMsg << std::endl;
}
std::string BaseAction::getErrorMsg() const { return errorMsg;}
std::string* BaseAction::getErrorMsgPointer() { return &errorMsg;}
std::string BaseAction::statusToString() const {
    if(status == COMPLETED) return "COMPLETED";
    if(status == ERROR) return "ERROR";
    if(status == PENDING) return "PENDING";
    return "";
}


//CreateUser
CreateUser::CreateUser(std::string name, std::string algo): BaseAction(), userName(std::move(name)), userAlgo(std::move(algo)){}

void CreateUser::act(Session &sess) {
    sess.addAction(this);
    sess.createUser(userName, userAlgo, getErrorMsgPointer());
    if(!(getErrorMsg().empty())) {
        error(getErrorMsg());
    }
    else complete();
}
CreateUser::~CreateUser()=default;
std::string CreateUser::toString() const {
    std::string output = "CreateUser " +statusToString();
    if(getStatus() == ERROR) output = output +": " +getErrorMsg();
    return output;
}
BaseAction* CreateUser::clone(){
    auto newClone = new CreateUser(*this);
    return newClone;
}


//ChangeActiveUser
ChangeActiveUser::ChangeActiveUser(std::string name): BaseAction(), userName(std::move(name)){}
void ChangeActiveUser::act(Session& sess){
    sess.addAction(this);
    sess.changeActiveUser(userName, getErrorMsgPointer());
    if(!(getErrorMsg().empty())) error(getErrorMsg());
    else complete();
}
ChangeActiveUser::~ChangeActiveUser()=default;
std::string ChangeActiveUser::toString() const{
    std::string output = "ChangeActiveUser " +statusToString();
    if(getStatus() == ERROR) output = output +": " +getErrorMsg();
    return output;
}
BaseAction* ChangeActiveUser::clone(){
    auto newClone = new ChangeActiveUser(*this);
    return newClone;
}

//DeleteUser
DeleteUser::DeleteUser(std::string name): BaseAction(), userName(std::move(name)){}
DeleteUser::~DeleteUser() =default;
void DeleteUser::act(Session &sess) {
    sess.addAction(this);
    sess.deleteUser(userName, getErrorMsgPointer());
    if(!getErrorMsg().empty()) error(getErrorMsg());
    else complete();
}
std::string DeleteUser::toString() const {
    std::string output = "DeleteUser " +statusToString();
    if(getStatus() == ERROR) output = output +": " +getErrorMsg();
    return output;
}
BaseAction* DeleteUser::clone(){
    auto newClone = new DeleteUser(*this);
    return newClone;
}

//DuplicateUser
DuplicateUser::DuplicateUser(std::string originalName, std::string newName): BaseAction(), originalUserName(std::move(originalName)), newUserName(std::move(newName)){}
DuplicateUser::~DuplicateUser()=default;
void DuplicateUser::act(Session &sess) {
    sess.addAction(this);
    sess.duplicateUser(originalUserName, newUserName, getErrorMsgPointer());
    if(!getErrorMsg().empty()) error(getErrorMsg());
    else complete();
}
std::string DuplicateUser::toString() const {
    std::string output = "DuplicateUser " +statusToString();
    if(getStatus() == ERROR) output = output +": " +getErrorMsg();
    return output;
}
BaseAction* DuplicateUser::clone(){
    auto newClone = new DuplicateUser(*this);
    return newClone;
}

//PrintContentList
PrintContentList::PrintContentList(): BaseAction(){}
PrintContentList::~PrintContentList()=default;
void PrintContentList::act(Session &sess) {
    sess.addAction(this);
    sess.printContentList(getErrorMsgPointer());
    if(!getErrorMsg().empty()) error(getErrorMsg());
    else complete();
}
std::string PrintContentList::toString() const {
    std::string output = "PrintContentList " +statusToString();
    if(getStatus() == ERROR) output = output +": " +getErrorMsg();
    return output;
}
BaseAction* PrintContentList::clone(){
    auto newClone = new PrintContentList(*this);
    return newClone;
}

//PrintWatchHistory
PrintWatchHistory::PrintWatchHistory(): BaseAction(){}
PrintWatchHistory::~PrintWatchHistory() =default;
void PrintWatchHistory::act(Session &sess) {
    sess.addAction(this);
    sess.printActiveUserWatchHistory(getErrorMsgPointer());
    if(!getErrorMsg().empty()) error(getErrorMsg());
    else complete();
}
std::string PrintWatchHistory::toString() const {
    std::string output = "PrintWatchHistory " +statusToString();
    if(getStatus() == ERROR) output = output +": " +getErrorMsg();
    return output;
}
BaseAction* PrintWatchHistory::clone(){
    auto newClone = new PrintWatchHistory(*this);
    return newClone;
}

//Watch
Watch::Watch(long id): BaseAction(), contentId(id){}
Watch::~Watch()=default;
void Watch::act(Session &sess) {
    sess.addAction(this);
    sess.watch(contentId, getErrorMsgPointer(),sess);
    if(!getErrorMsg().empty()) error(getErrorMsg());
    else complete();
}
std::string Watch::toString() const {
    std::string output = "Watch " +statusToString();
    if(getStatus() == ERROR) output = output +": " +getErrorMsg();
    return output;
}
BaseAction* Watch::clone(){
    auto newClone = new Watch(*this);
    return newClone;
}

//PrintActionsLog
PrintActionsLog::PrintActionsLog(): BaseAction(){}
PrintActionsLog::~PrintActionsLog()=default;
void PrintActionsLog::act(Session &sess) {
    sess.addAction(this);
    sess.printActionsLog(getErrorMsgPointer());
    if(!getErrorMsg().empty()) error(getErrorMsg());
    else complete();
}
std::string PrintActionsLog::toString() const {
    std::string output = "PrintActionsLog " +statusToString();
    if(getStatus() == ERROR) output = output +": " +getErrorMsg();
    return output;
}
BaseAction* PrintActionsLog::clone(){
    auto newClone = new PrintActionsLog(*this);
    return newClone;
}

Exit::Exit():BaseAction() {}
Exit::~Exit()=default;
void Exit::act(Session &sess) {
    sess.addAction(this);
    if(!getErrorMsg().empty()) error(getErrorMsg());
    else complete();
}
std::string Exit::toString() const {
    std::string output = "Exit " +statusToString();
    if(getStatus() == ERROR) output = output +": " +getErrorMsg();
    return output;
}
BaseAction* Exit::clone(){
    auto newClone = new Exit(*this);
    return newClone;
}

