#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>

class Session;

enum ActionStatus{
    PENDING, COMPLETED, ERROR
};


class BaseAction{
public:
    //Constructor
    BaseAction();

    //Destructor
    virtual ~BaseAction();

    //Methods
    ActionStatus getStatus() const;
    virtual void act(Session& sess)=0;
    virtual std::string toString() const=0;
    virtual BaseAction* clone()=0;
protected:
    void complete();
    void error(const std::string& errorMsg);
    std::string getErrorMsg() const;
    std::string* getErrorMsgPointer();
    std::string statusToString() const;

private:
    //Fields
    std::string errorMsg;
    ActionStatus status;
};

class CreateUser  : public BaseAction {
public:
    CreateUser(std::string name, std::string algo);
    virtual ~CreateUser();
    virtual void act(Session& sess);
    virtual std::string toString() const;
    BaseAction* clone() override;
private:
    std::string userName;
    std::string userAlgo;
};

class ChangeActiveUser : public BaseAction {
public:
    explicit ChangeActiveUser(std::string name);
    virtual ~ChangeActiveUser();
    virtual void act(Session& sess) ;
    virtual std::string toString() const;
    BaseAction* clone() override;
private:
    std::string userName;
};

class DeleteUser : public BaseAction {
public:
    explicit DeleteUser(std::string name);
    virtual ~DeleteUser();
    virtual void act(Session & sess);
    virtual std::string toString() const;
    BaseAction* clone() override;
private:
    std::string userName;
};

class DuplicateUser : public BaseAction {
public:
    DuplicateUser(std::string originalName, std::string newName);
    virtual ~DuplicateUser();
    virtual void act(Session & sess);
    virtual std::string toString() const;
    BaseAction* clone() override;
private:
    std::string originalUserName;
    std::string newUserName;
};

class PrintContentList : public BaseAction {
public:
    PrintContentList();
    virtual ~PrintContentList();
    virtual void act (Session& sess);
    virtual std::string toString() const;
    BaseAction* clone() override;
};

class PrintWatchHistory : public BaseAction {
public:
    PrintWatchHistory();
    virtual ~PrintWatchHistory();
    virtual void act (Session& sess);
    virtual std::string toString() const;
    BaseAction* clone() override;
};

class Watch : public BaseAction {
public:
    explicit Watch(long contentId);
    virtual ~Watch();
    virtual void act(Session& sess);
    virtual std::string toString() const;
    BaseAction* clone() override;

private:
    long contentId;
};

class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
    virtual ~PrintActionsLog();
    virtual void act(Session& sess);
    virtual std::string toString() const;
    BaseAction* clone() override;
};

class Exit : public BaseAction {
public:
    Exit();
    virtual ~Exit();
    virtual void act(Session& sess);
    virtual std::string toString() const;
    BaseAction* clone() override;
};
#endif