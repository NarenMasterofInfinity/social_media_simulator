#include "../user_db.hpp"
#include "../classes.hpp"
#include "../user_db.hpp"


    User *u1 = new User("naren", "naren3", "naren@gmail.com");
    User *u2 = new User("jan", "jan3", "jan@gmail.com");
    User *u3 = new User("jan3", "jan3", "jan@gmail.com");
    User *u4 = new User("nar1", "naren3", "nar1@gmail.com");
    User *u5 = new User("nar2", "nar2@gmail.com", "naren3");
    User *u6 = new User("nar3", "nar3@gmail.com", "naren3");
    User *u7 = new User("nar4", "nar4@gmail.com", "naren3");

    User *us[] = {u1, u2, u3, u4, u5, u6, u7};

    for (int i = 0; i < 6; i++)
    {
        store_user(us[i]);
    }
