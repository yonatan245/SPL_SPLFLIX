#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <utility>
using namespace std;
class Watchable;
class Session;

class User{
public:
    //Constructors
    User(const std::string&  name);

    //Rule of 5
    virtual ~User();

    void copy(std::vector<Watchable*> history);

    //Methods
    virtual Watchable* getRecommendation(Session& s) = 0;
    std::string getName() const;
    std::vector<Watchable*> get_history() const;
    void printWatchHistory();
    void watch(Watchable* watchable, Session& session);
    virtual std::string getCode() = 0;
    virtual User* clone() = 0;

protected:
    //Methods
    void addWatchableToHistory(Watchable* watchable);
    bool isWatchableInHistory(Watchable* watchable);
    virtual void additionalWatchActions(Watchable* watchable) = 0;
    void setHistory(vector<Watchable*> newHistory);
    void clearHistory();
    virtual void choseRec() = 0;

    //Fields
    std::vector<Watchable*> history;

private:
    const std::string name;

};


class LengthRecommenderUser : public User {
public:
    //Constructors
    LengthRecommenderUser(const std::string& name);

    //Rule of 5
    virtual ~LengthRecommenderUser();
    LengthRecommenderUser(LengthRecommenderUser& other, const string& name);
    LengthRecommenderUser& operator=(LengthRecommenderUser& other);
    LengthRecommenderUser(LengthRecommenderUser&& other, const string& name);
    LengthRecommenderUser& operator=(LengthRecommenderUser&& other);

    //Methods
    virtual Watchable* getRecommendation(Session& s);
    std::string getCode() override;
    double getAvgLength();
    User* clone() override;

protected:
    //Methods
//    virtual void addWatchableToHistory(Watchable* watchable);
    void additionalWatchActions(Watchable* watchable) override;
    void setAvgLength(double newAvg);
    void choseRec() override;

private:
    //Fields
    double avgLength;
};

class RerunRecommenderUser : public User {
public:
    //Constructors
    RerunRecommenderUser(const std::string& name);

    //Rule of 5
    RerunRecommenderUser(const RerunRecommenderUser& other, const string &name);
    virtual ~RerunRecommenderUser();
    RerunRecommenderUser& operator=(const RerunRecommenderUser& other);
    RerunRecommenderUser(RerunRecommenderUser&& other);
    RerunRecommenderUser& operator=(RerunRecommenderUser&& other);

    //Methods
    virtual Watchable* getRecommendation(Session& s);
    std::string getCode() override;
    User* clone() override;

protected:
    //Methods
    void additionalWatchActions(Watchable* watchable) override;
    void choseRec() override;

private:
    //Fields
    int lastRecommended;
};

class GenreRecommenderUser : public User {
public:
    //Constructors
    GenreRecommenderUser(const std::string& name);

    //Rule of 5
    virtual ~GenreRecommenderUser();
    GenreRecommenderUser(const GenreRecommenderUser& other, const string& name);
    GenreRecommenderUser& operator=(const GenreRecommenderUser& other);
    GenreRecommenderUser(GenreRecommenderUser&& other);
    GenreRecommenderUser& operator=(GenreRecommenderUser&& other);

    //Methods
    virtual Watchable* getRecommendation(Session& s);
    std::string getCode() override;
    User* clone() override;

protected:
    //Methods
    void additionalWatchActions(Watchable* watchable) override;
    void choseRec() override;

private:
    //Fields
    mutable std::set<pair<int, string>> tagsByPopularity;
};


class Comp {
public:
    bool operator() (const pair<int, string>& lhs, const pair<int, string>& rhs) const;
};