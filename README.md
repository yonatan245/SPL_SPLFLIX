# SPL_SPLFLIX
1st assignment in SPL course, CS department, Ben Gurion University, fall of 2020.

The assignment is about memory handling and alloction, and written in C++.
The project is SPLFLIX, a simulation of content streaming app.
Once openning the app, a session is created with a deafult user, and the repository is created 
using the input json file (as in the include directory).

There are 3 kinds of users, which differ only by the recommendation algorithm:

Length Recommender – This algorithm is based on the assumption that users prefer to watch content in a similar length.
                      It will recommend the content whose length is closest to the average length of thecontent in the
                      user's watch history, and which isn'tin the user's watch history.(3-letter code–len)
                      
Rerun Recommender – This algorithm is intended for users who don't like new stuff. It will recommend content based on
                    this user's watching history. Starting from the first watchable content, in a cyclic order.
                    That is –the first watchable to be recommended is the first watchable watched by the user.
                    Afterwards, if the last watchable that was recommended by the algorithm was at index 𝑖in the history,
                    and the history is of length 𝑛the next content to be recommended is at index (𝑖+1)𝑚𝑜𝑑𝑛.(3-letter code–rer)
                    
Similar Genre – This algorithm will recommend content based on the mostpopular tag in the user's watch history.
                 If a set of tags has the same popularity, the algorithm will use lexicographic order to pick between them.
                 It will recommend a content which is tagged by the most popular tag in the user's history, which wasn't already
                 watched by this user. If no such content exists, it will try with the second most popular tag, and so on.(3-letter code–gen)


The available actions are described the assignment specifications, section 3.4 in page 6. 
