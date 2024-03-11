#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>

#ifndef CLASSES_H
#define CLASSES_H

using namespace std;

#define POST_MAX 8  // 128
#define USER_MAX 8  // 512
#define COMM_MAX 8  // 512
#define LIKE_MAX 8  // 1024
#define SHARE_MAX 8 // 256
#define VIEW_MAX 8  // 2048
#define TAG_MAX 8   // 32
#define GROUP_MAX 8 // 16
#define MAX_C 10    // 1024
#define NORMAL_CONV "n"
#define GROUP_CONV "g"
#define COMMUNITY_CONV "c"
#define TEXT_MSG "t"
#define IMAGE_MSG "i"
#define VIDEO_MSG "v"
#define AUDIO_MSG "a"

class Post;
class User;
class Conversation;
class DMConversation;
class GroupConversation;
class CommunityConversation;
class RequestBasedCommunity;
class FreeJoinCommunity;
class Message;
class Multimedia;
class Video;
class Audio;
template <typename T>
class Text;
class Story;
class Image;
class Group;
class Comment;
class String;
class Emoji;

// defining emojis
map<string, string> emojis = {
    {"happy", "😊"},
    {"heart_eyes", "😍"},
    {"smile","😁"},
    {"laugh", "😂"},
    {"cry", "😢"},
    {"angry", "😡"},
    {"surprised", "😮"},
    {"confused", "😕"},
    {"kiss", "😘"},
    {"sick", "🤢"},
    {"cool", "😎"},
    {"sleep", "😴"},
    {"worried", "😟"},
    {"sad", "😔"},
    {"unamused", "😒"},
    {"blush", "😊"},
    {"hug", "🤗"},
    {"wink", "😉"},
    {"grin", "😁"},
    {"tongue", "😋"},
    {"neutral", "😐"},
    {"smirk", "😏"},
    {"relieved", "😌"},
    {"pensive", "😔"},
    {"confounded", "😖"},
    {"disappointed", "😞"},
    {"persevere", "😣"},
    {"sweat", "😅"},
    {"weary", "😩"},
    {"sob", "😭"},
    {"joy", "😂"},
    {"scream", "😱"},
    {"rage", "😠"},
    {"yum", "😋"},
    {"demon", "😈"},
    {"demon_smile", "👿"}, 
    {"innocent", "😇"},
    {"clown", "🤡"},
    {"lying", "🤥"},
    {"shushing", "🤫"},
    {"thinking", "🤔"},
    {"zipper", "🤐"},
    {"eye_roll", "🙄"},
    {"sunglasses", "😎"},
    {"nerd", "🤓"},
    {"sick", "🤒"},
    {"bandage", "🤕"},
    {"thermometer", "🌡️"},
    {"sneezing", "🤧"},
    {"mask", "😷"},
    {"vomit", "🤮"},
    {"bull", "🐂"},
};

void setSession(int *session)
{
    *session = 1;
}
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
        // cout << "Post created" << endl;
    }
    Post(string content, User *author)
    {
        this->author = author;
        this->content = content;
        // cout << "Post created" << endl;
    }
    ~Post()
    {
        cout << "Post deleted" << endl;
    }

    string getContent();
    void setContent(string);
};
class User
{
    string username, bio, password, email;
    Image *profile_picture;

public:
    User *Following[USER_MAX], *Followers[USER_MAX];
    Post *my_posts[POST_MAX];
    Post *saved_posts[POST_MAX];
    int saved_ptr, post_ptr;
    User()
    {
        saved_ptr = 0;
        username = bio = password = "";
        for (int i = 0; i < USER_MAX; i++)
        {

            Following[i] = (User *)malloc(sizeof(User));
            Followers[i] = (User *)malloc(sizeof(User));
        }
        for (int i = 0; i < POST_MAX; i++)
        {
            saved_posts[i] = new Post();
        }
    }

    User(string username, string password, string email)
    {
        saved_ptr = 0;
        this->username = username;
        this->email = email;
        this->password = password;
        for (int i = 0; i < POST_MAX; i++)
        {
            saved_posts[i] = new Post();
        }
    }

    User(string username)
    {
        saved_ptr = 0;
        this->username = username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter email: ";
        cin >> email;
        for (int i = 0; i < POST_MAX; i++)
        {
            saved_posts[i] = new Post();
        }
    }

    User(User *user)
    {
        saved_ptr = 0;
        this->password = user->getPassword();
        this->email = user->getEmail();
        this->username = user->getUsername();
        for (int i = 0; i < USER_MAX; i++)
        {
            Following[i] = new User();
            Followers[i] = new User();
        }
        for (int i = 0; i < POST_MAX; i++)
        {
            saved_posts[i] = new Post();
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
    static void display(User);
    static void display(User, bool);

    // friend functions

    friend bool operator>(User, User);
};
class Message
{
public:
    User *author;
    Message(){};
    virtual void display() = 0;
    virtual string getType() = 0;
    virtual User *getAuthor() = 0;
    virtual string getContent() { return ""; }; // often not needed in multimedia objects
    virtual void setContent(string) = 0;
    virtual void setAuthor(User *) = 0;
};

class Multimedia : public Message
{
public:
    Multimedia(){};
    template <typename T>
    static bool validate(string path);
    void display(){};
    string getType() { return TEXT_MSG; }
    User *getAuthor() { return nullptr; }
    void setContent(string){};
    void setAuthor(User *){};
};

class Video : public Multimedia
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
    Video(string path)
    {
        video_path = path;
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
    void display();
    User *getAuthor()
    {
        return author;
    }
    void setAuthor(User *author)
    {
        this->author = author;
    }
    string getType()
    {
        return VIDEO_MSG;
    }
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

class Image : public Multimedia
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
        //  cout << "Image constructed" << endl;
    }
    ~Image()
    {
        //  cout << "Image deleted" << endl;
    }
    void display();
    User *getAuthor()
    {
        return author;
    }
    void setAuthor(User *author)
    {
        this->author = author;
    }
    string getType()
    {
        return IMAGE_MSG;
    }
};

class Audio : public Multimedia
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
    Audio(string path)
    {
        audio_path = path;
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
    void display();
    User *getAuthor()
    {
        return author;
    }
    void setAuthor(User *author)
    {
        this->author = author;
    }
    string getType()
    {
        return AUDIO_MSG;
    };
};
class Conversation
{

protected:
    User *participants[GROUP_MAX];
    int count;
    int left_or_not[GROUP_MAX];
    User *creator;

public:
    // 0 for left, 1 for active
    Message *chats_msgs[MAX_C];
    int text_ptr;
    int p_ptr;
    Story *chats_stories[MAX_C];
    // Image *chats_images[MAX_C]; //depreciated
    // Video *chats_videos[MAX_C]; //depreciated
    time_t story_t[MAX_C], image_t[MAX_C], video_t[MAX_C];

public:
    Conversation() { p_ptr = 0; }
    virtual void add_participants(User *, User *){};
    virtual void add_participants(int){};
    virtual void create_interface() = 0;
    virtual void sendText(User *){};
    virtual void sendMessage(Message *){};
    virtual void display_participants() = 0;
    virtual string getType() = 0;
    virtual ~Conversation(){};

    friend Conversation *search_dm_conversations(User, User);
    friend Conversation *search_dm_conversations(User *, User *);
    // too conflicting :(
    friend Conversation *search_dm_conversations(string user1, string user2);
};

class DMConversation : public Conversation
{
    // inherits participants from the Conversation class
private:
    time_t last_seen[2];
    vector<Message *> starred_messages;

public:
    DMConversation()
    {
        count = 2;
        text_ptr = 0;
        for (int i = 0; i < 2; i++)
        {
            participants[i] = new User();
        }
    }

    DMConversation(User *user1, User *user2)
    {
        count = 2;
        creator = user1;
        participants[0] = user1;
        participants[1] = user2;
    }

    ~DMConversation()
    {
        for (int i = 0; i < 2; i++)
        {
            delete participants[i];
        }
    }
    // inherits the create_dm_interface and addParticipants

    void exitConvo(User *);
    void starMessage(Message *);
    string getType();

    template <class T>
    void sendText(User *);

    void create_interface();
    void display_participants();

    void add_particpants(User *, User *);
};

class CommunityConversation : virtual public Conversation
{

protected:
    User *admins[GROUP_MAX];
    int admin_ptr;
    string community_name;
    string community_description;
    Image *community_picture;

public:
    CommunityConversation()
    {
        admin_ptr = 0;
        p_ptr = 0;
    }
    virtual ~CommunityConversation(){};

protected:
    bool authenticate(string username);

public:
    void setCommunityName(string, string);
    string getCommunityName();
    bool promoteToAdmin(string username);
    virtual void addMembers(string username, int count) = 0;
    virtual void addMembers(int){};
    void setCommunityDescription(string username, string desc);
    string getCommunityDescription();
    void sendText(User *){};
    string getType();
    virtual void joinCommunity(User *){};
    virtual void create_interface();
    virtual void display_participants();
    virtual void sendMessage(Message *msg);
    virtual void issueRequest(User *){};
    virtual void acceptRequest(User *){};
};
class RequestBasedCommunity : public CommunityConversation
{
private:
    User *request_queue[GROUP_MAX];
    int request_ptr;

public:
    RequestBasedCommunity()
    {
        request_ptr = 0;
        for (int i = 0; i < GROUP_MAX; i++)
        {
            participants[i] = new User();
        }
    }
    RequestBasedCommunity(User *creator)
    {
        request_ptr = 0;
        this->creator = creator;
        admins[admin_ptr++] = creator;
        participants[0] = new User();
        participants[0] = creator;
        for (int i = 1; i < GROUP_MAX; i++)
        {
            participants[i] = new User();
        }
        p_ptr++;
    }
    ~RequestBasedCommunity()
    {
        for (int i = 0; i < GROUP_MAX; i++)
        {
            delete participants[i];
        }
    }
    void acceptRequest(User *); // admin and request queue
    void addMembers(string username, int count);
    void issueRequest(User *);
    // string getType();
};

class FreeJoinCommunity : public CommunityConversation
{
public:
    FreeJoinCommunity()
    {
        for (int i = 0; i < GROUP_MAX; i++)
        {
            participants[i] = new User();
        }
    }
    FreeJoinCommunity(User *creator)
    {
        this->creator = creator;
        admins[admin_ptr++] = creator;
        participants[0] = new User();
        participants[0] = creator;
        p_ptr++;
    }
    void addMembers(string, int){};
    void addMembers(int);
    void joinCommunity(User *);
    // string getType();
};

class GroupConversation : public Conversation
{

private:
    Image *group_picture;
    string group_name;
    User *admins[GROUP_MAX];
    int admin_ptr;

public:
    GroupConversation()
    {
        admin_ptr = 0;
        group_name = "test_group";
        cout << "Group constructed with the name " << group_name << endl;
    }

    // copy constructor
    GroupConversation(const GroupConversation &g)
    {
        admin_ptr = 0;
        this->group_name = g.group_name;
        this->creator = g.creator;
        admins[admin_ptr++] = creator;
        for (int i = 0; i < g.count; i++)
        {
            this->participants[i] = new User();
            this->participants[i] = g.participants[i];
        }

        cout << "Group constructed with the name " << g.group_name << endl;
    }
    GroupConversation(User *creator, string group_name)
    {
        admin_ptr = 0;
        this->creator = creator;
        this->group_name = group_name;
        admins[admin_ptr++] = creator;
        for (int i = 0; i < GROUP_MAX; i++)
        {
            this->participants[i] = new User();
        }
        participants[0] = creator;
        cout << "Group constructed with the name " << group_name << endl;
    }
    GroupConversation(User *creator, User *users[GROUP_MAX], string group_name)
    {
        admin_ptr = 0;
        this->creator = creator;
        admins[admin_ptr++] = creator;
        for (int i = 0; i < GROUP_MAX; i++)
        {
            this->participants[i] = new User();
            this->participants[i] = participants[i];
        }
        this->group_name = group_name;
        cout << "Group constructed with the name " << group_name << endl;
    }
    ~GroupConversation()
    {
        cout << "Group deleted" << endl;
    }

    void add_participants(int);
    string getGroupName();
    void changeGroupName();
    string getType();
    void sendMessage(Message *);
    void sendText(User *){};
    void display_participants();
    void create_interface();
};
class String
{
    string content;

public:
    String(string content)
    {
        this->content = content;
    }
    String() { content = ""; }
    String(const String &other)
    {
        content = other.content;
    }
    void setContent(string);
    void display();
    string getContent();
};

class Emoji
{
    string content;
    string converted;
    string parse_and_replace(string);

public:
    Emoji()
    {
        content = "";
        converted = " ";
    }
    Emoji(string content) { this->content = converted = parse_and_replace(content); }
    Emoji(const Emoji &other)
    {
        content = other.content;
    }
    void display();
    void setContent(string);
    string getContent();
};

template <typename T = String>
class Text : public Message
{
    T content;
    User *author;

public:
    bool liked_or_not;
    time_t time_of_creation;
    User *replied_to;
    Text()
    {
        liked_or_not = false;
    }
    Text(string content)
    {
        this->content = T(content);
    }
    Text(User *author, string content)
    {
        this->author = author;
        this->content = T(content);
    }
    ~Text()
    {
        if (author)
        {
            delete author;
        }
    }

    User *getAuthor();
    // T getContent(){};
    string getContent();
    void setContent(string);

    void setAuthor(User *);
    //  void setContent(T){};
    void display();
    string getType();
};

#endif

// int main(){}
