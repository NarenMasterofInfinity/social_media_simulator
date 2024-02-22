#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

#ifndef CLASSES_H
#define CLASSES_H

using namespace std;

#define POST_MAX 4  // 128
#define USER_MAX 3  // 512
#define COMM_MAX 2  // 512
#define LIKE_MAX 2  // 1024
#define SHARE_MAX 2 // 256
#define VIEW_MAX 2  // 2048
#define TAG_MAX 2   // 32
#define GROUP_MAX 3 // 16
#define MAX_C 10    // 1024

class User;
class Post;
class Conversation;
class Video;
class Audio;
class Text;
class Story;
class Image;
class Group;
class Comment;

void setSession(int *session)
{
    *session = 1;
}

class User
{
    string username, bio, password, email;
    Image *profile_picture;

public:
    User *Following[USER_MAX], *Followers[USER_MAX];
    Post *my_posts[POST_MAX], *saved_posts[POST_MAX];
    int saved_ptr;
    int post_ptr;
    User()
    {
        saved_ptr = 0;
        username = bio = password = "";
        for (int i = 0; i < USER_MAX; i++)
        {
            Following[i] = new User();
            Followers[i] = new User();
        }
    }

    User(string username, string password, string email)
    {
        saved_ptr=0;
        this->username = username;
        this->email = email;
        this->password = password;
    }

    User(string username)
    {
        saved_ptr = 0;
        this->username = username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter email: ";
        cin >> email;
    }

    User(User *user)
    {
        this->password = user->getPassword();
        this->email = user->getEmail();
        this->username = user->getUsername();
        for (int i = 0; i < USER_MAX; i++)
        {
            Following[i] = new User();
            Followers[i] = new User();
        }
    }
    ~User()
    {
        for (int i = 0; i < USER_MAX; i++)
        {
            delete Following[i];
            delete Followers[i];
        }
    }

    void setUsername(string);
    void setEmail(string);
    void setPassword(string);

    string getUsername();
    string getEmail();
    string getPassword();

    static User *search_user(string);

 void show_saved_post();
 void operator+(Post *);
};

class Post
{
    string content;
    Video *post_video;
    Image *post_image;

public:
    Comment *comments[COMM_MAX];
    int no_of_likes;
    User *Likes[LIKE_MAX];
    time_t time_of_creation;
    User *Shares[SHARE_MAX];
    int no_of_shares;
    string location;
    User *author;
    Post()
    {
        no_of_likes = no_of_shares = 0;
        location = content = "";
        cout << "Post created" << endl;
    }
    Post(string content, User *author)
    {
        this->author = author;
        this->content = content;
        cout << "Post created" << endl;
    }
    Post(Post & post){
        *this = post;
    }
    ~Post()
    {
        cout << "Post deleted" << endl;
    }

    string getContent();
    void setContent(string);
};

class Video
{
    string video_path;
    Audio *audio_for_video;
    const static int height = 300, width = 200;

public:
    int duration;
    Video()
    {
        duration = 0;
        video_path = "";
        cout << "Video created" << endl;
    }
    Video(int duration, string video_path)
    {
        this->duration = duration;
        this->video_path = video_path;
        cout << "Video created" << endl;
    }
    ~Video()
    {
        cout << "Video deleted" << endl;
    }
    bool isValidpath(string, string, User *);
};

class Comment
{
    string content;
    Post *belongs_to;

public:
    int no_of_likes;
    User *author;
    User *likes[LIKE_MAX];
    time_t time_of_creation;
    User *replied_to;

    Comment()
    {
        no_of_likes = 0;
        time_of_creation = time(NULL);
        cout << "Comment created" << endl;
    }
    Comment(User *author, string content)
    {
        this->author = author;
        this->content = content;
        time_of_creation = time(NULL);
        cout << "Comment created" << endl;
    }
    ~Comment()
    {
        cout << "Comment deleted" << endl;
    }
};

class Story
{
    Image *story_image;
    Video *story_video;

public:
    User *viewers[VIEW_MAX];
    time_t time_of_creation;
    Comment *comments[MAX_C];
    int no_of_likes;
    User *Tag[TAG_MAX], *Likes[LIKE_MAX], *author;
    Story()
    {
        no_of_likes = 0;
        time_of_creation = time(NULL);
        cout << "Story created" << endl;
    }
    Story(User *author)
    {
        no_of_likes = 0;
        time_of_creation = time(NULL);
        this->author = author;
        cout << "Story created" << endl;
    }
    ~Story()
    {
        cout << "Story deleted" << endl;
    }
};

class Image
{
    string image_path;
    Audio *audio_for_image;
    const static int height = 300, widht = 200;

public:
    Image()
    {
        image_path = "";
        cout << "Image constructed" << endl;
    }
    Image(string image_path)
    {
        this->image_path = image_path;
        cout << "Image constructed" << endl;
    }
    ~Image()
    {
        cout << "Image deleted" << endl;
    }
};

class Audio
{
    string audio_path;
    int duration, volume_level;

public:
    Audio()
    {
        duration = 0;
        volume_level = 50;
        cout << "Audio constructed" << endl;
    }
    Audio(string audio_path, int duration)
    {
        this->duration = duration;
        this->audio_path = audio_path;
        cout << "Audio constructed" << endl;
    }
    ~Audio()
    {
        cout << "Audio deleted" << endl;
    }
};

class Conversation
{
    int count;
    bool group_or_normal;
    User *creator;

public:
    User *participants[GROUP_MAX];
    int left_or_not[GROUP_MAX]; // 0 for left, 1 for active
    Text *chats_text[MAX_C];
    int text_ptr;
    Story *chats_stories[MAX_C];
    Image *chats_images[MAX_C];
    Video *chats_videos[MAX_C];
    time_t story_t[MAX_C], image_t[MAX_C], video_t[MAX_C];
    Conversation()
    {
        text_ptr = 0;
        group_or_normal = 0;
        count = 0;
        for (int i = 0; i < 2; i++)
        {
            this->participants[i] = new User();
        }
    }
    Conversation(bool g, int count, User *creator)
    {
        text_ptr = 0;
        this->creator = creator;
        group_or_normal = g;
        this->count = count;
        cout << "Conversation constructed" << endl;

        if (!g)
        {
            for (int i = 0; i < 2; i++)
            {
                this->participants[i] = new User();
            }
        }
        else
        {
            for (int i = 0; i < count; i++)
            {
                this->participants[i] = new User();
            }
        }
    }

    ~Conversation()
    {
        // for(int i = 0;i < count; i++){
        //     delete participants[i];
        // }
    }

    void add_participants(User *, User *);
    void add_participants(Group *);
    void display_participants();
    void create_interface_dm();

    void sendText(User *);

    static Conversation *search_dm_conversations(string, string);
    static Conversation *search_dm_conversations(User, User);
    static Conversation *search_dm_conversations(User *, User *);
};

class Group
{

protected:
    User *created_by;

private:
    Image *group_picture;
    string group_name;

public:
    User *users[GROUP_MAX];

    Group()
    {
        group_name = "test_group";
        cout << "Group constructed with the name " << group_name << endl;
    }

    // copy constructor
    Group(const Group &g)
    {
        this->group_name = g.group_name;
        this->created_by = g.created_by;
        for (int i = 0; i < GROUP_MAX; i++)
        {
            this->users[i] = (User *)malloc(sizeof(User));
            this->users[i] = g.users[i];
        }

        cout << "Group constructed with the name " << g.group_name << endl;
    }

    Group(User *creator, string group_name)
    {
        created_by = creator;
        this->group_name = group_name;

        for (int i = 0; i < GROUP_MAX; i++)
        {
            this->users[i] = (User *)malloc(sizeof(User));
        }
        cout << "Group constructed with the name " << group_name << endl;
    }
    Group(User *creator, User *users[GROUP_MAX], string group_name)
    {
        created_by = creator;
        for (int i = 0; i < GROUP_MAX; i++)
        {
            this->users[i] = (User *)malloc(sizeof(User));
            this->users[i] = users[i];
        }
        this->group_name = group_name;
        cout << "Group constructed with the name " << group_name << endl;
    }
    ~Group()
    {
        cout << "Group deleted" << endl;
    }

    void add_members(int);
};

class Text
{
    string content;
    User *author;

public:
    bool liked_or_not;
    time_t time_of_creation;
    User *replied_to;
    Text()
    {
        liked_or_not = false;
    }
    Text(User *author, string content)
    {
        this->author = author;
        this->content = content;
    }
    ~Text()
    {
        cout << "Text deleted" << endl;
    }

    User *getAuthor();
    string getContent();

    void setAuthor(User *);
    void setContent(string);
};

// int main(){}

#endif