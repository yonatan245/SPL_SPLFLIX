#ifndef WATCHABLE_H_
#define WATCHABLE_H_

#include <string>
#include <vector>


class Session;

class Watchable{
public:
    Watchable(long id, int length, const std::vector<std::string>&  tags);
    Watchable(const Watchable& other);
    virtual ~Watchable();
    virtual std::string toString() const = 0;
    virtual Watchable* getNextWatchable(Session&) const = 0;
    int getLength();
    std::vector<std::string> getTags();
    long getId();
    void setNextEpisodeId(long nextId);
    long getNextEpisodeId() const;
    virtual Watchable* clone() = 0;
    virtual void clear() = 0;
    virtual void destroy() = 0;

private:
    const long id;
    int length;
    std::vector<std::string> tags;
    long nextEpisodeId;

};

class Movie : public Watchable{
public:
    Movie(long id, const std::string&  name, int length, const std::vector<std::string>& tags);
    Movie(const Movie& other);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session&) const;
    virtual Watchable* clone();
    virtual ~Movie();
    virtual void clear();
    virtual void destroy();

private:
    std::string name;

};

class Episode: public Watchable{
public:
    Episode(long id, const std::string& seriesName ,int length, int season, int episode ,const std::vector<std::string>& tags);
    Episode(Episode& other);
    std::string toString() const override;
    Watchable* getNextWatchable(Session&) const override;
    virtual Watchable* clone();
    virtual ~Episode();
    virtual void clear();
    virtual void destroy();

private:
    std::string seriesName;
    int season;
    int episode;

};

#endif
