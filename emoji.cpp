#include "include/emoji.hpp"

skin::skin skiny[] = {
        skin::skin("<:p00:986984735471443969>", 0, "steve", 0),
        skin::skin("<:p01:986984737337933864>", 1, "alex", 100),
        skin::skin("<:p02:986985585375871117>", 2, "luktvpl", 2000)
};

skin::skin skin::getSkin(int id){
    return skiny[id]; 
};