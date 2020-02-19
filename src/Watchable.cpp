#include <string>
#include <vector>
    #include "../include/Session.h"
    #include "../include/Watchable.h"
    #include "../include/User.h"
    using namespace std;
    //-----------------------------------------WATCHABLE------------------------------------------
    //Constructor
        Watchable::Watchable(long id, int length, const std::vector<std::string>& tags) : id(id), length(length),tags(tags), nextEpisodeId(0){}

    //Copy Constructor
        Watchable::Watchable(const Watchable& other) = default;

    //Methods
        int Watchable::getLength(){
            return length;
        }
        std::vector<std::string> Watchable::getTags()
        {
            return tags;
        }
        long Watchable::getId() {
        return id;
        }
        void Watchable::setNextEpisodeId(long nextId) { nextEpisodeId = nextId;}
        long Watchable::getNextEpisodeId() const {return nextEpisodeId;}

    //Destructor
        Watchable::~Watchable(){
            tags.clear();
            tags.shrink_to_fit();
        }


    //---------------------------------------MOVIE------------------------------------------
    //Constructor
        Movie::Movie(long id, const std::string&  name, int length, const std::vector<std::string>& tags) : Watchable(id, length, tags), name(name) {setNextEpisodeId(-1);}

    //Copy Constructor
        Movie::Movie(const Movie &other): Watchable(other), name(other.name){}

    //Destructor
        Movie::~Movie() = default;

    //Methods
        std::string Movie::toString() const {
            return name;
        }
        Watchable *Movie::getNextWatchable(Session &) const {
            return nullptr;
        }
        Watchable* Movie:: clone(){
        auto newClone=new Movie(*this);
        return newClone;
    }
        void Movie::clear() {}
        void Movie::destroy() {delete this;}



     //--------------------------------------------------EPISODE-------------------------------------------------
    //Constructor
        Episode::Episode(long id, const std::string& seriesName, int length, int season, int episode,
                         const std::vector<std::string> &tags) : Watchable(id, length, tags), seriesName(seriesName), season(season), episode(episode) { setNextEpisodeId(id +1);}

    //Copy Constructor
    Episode::Episode(Episode &other): Watchable(other),seriesName(other.seriesName), season(other.season), episode(other.episode) {}

    //Destructor
        Episode::~Episode() = default;

    //Methods
        std::string Episode::toString() const {
            auto s = std::to_string(season);
            auto e = std::to_string(episode);
            return seriesName + " " + "S" + s + "E" + e;
        }
        Watchable* Episode:: clone(){
        auto newClone = new Episode(*this);
            return newClone;
    }
        Watchable *Episode::getNextWatchable(Session &s) const {
            long next=getNextEpisodeId();
            if(next != -1){
                return s.getContent().at(unsigned( abs(next -1)));
            }
            else return nullptr;

        }
        void Episode::clear(){}
        void Episode::destroy() {delete this;}





